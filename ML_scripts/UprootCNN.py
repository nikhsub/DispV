import os, sys
import time 
import getopt
import argparse
import ROOT as r
#import varsList
import numpy as np 
import uproot3 as uproot#uproot3 as uproot
import math
import pandas as pd
#import root_pandas
import h5py
import tqdm 
import json
import awkward0 as awkward 
import glob

import tensorflow as tf
from tensorflow import keras as keras

from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler

from sklearn import metrics

import CNNblock
from CNNblock import CNN_block, GNN_block


def _roc_auc(y_true, y_pred):
    try:
        return metrics.roc_auc_score(y_true, y_pred)
    except ValueError:
        return metrics.accuracy_score(y_true, np.rint(y_pred))

def roc_auc(y_true, y_pred):
    return tf.py_function(_roc_auc, (y_true, y_pred), tf.double)

def _clip(a, a_min, a_max):
    if isinstance(a, np.ndarray):
        return np.clip(a, a_min, a_max)
    else: 
        return awkward.JaggedArray.fromcounts(a.counts, np.clip(a.content, a_min, a_max))

def _pad(a, maxlen, value=0, dtype='float32'):
    if isinstance(a, np.ndarray) and a.ndim==1:
        return np.nan_to_num(a)
    if isinstance(a, np.ndarray) and a.ndim>=2 and a.shape[1] == maxlen:
        return np.nan_to_num(a)
    if isinstance(a, awkward.JaggedArray):
        return a.pad(maxlen, clip=True).fillna(value).regular().astype(dtype)
    else: 
        x = (np.ones((len(a), maxlen))*value).astype(dtype)
        for idx, s in enumerate(a):
            if not len(s):
                continue
            trunc = np.nan_to_num(s[:maxlen].astype(dtype))
            x[idx, :len(trunc)] = trunc
        return x

def _concat(arrays, axis=0):
    if len(arrays) == 0:
        return np.arrya([])
    if isinstance(arrays[0], np.ndarray):
        return np.concatenate(arrays, axis=axis)
    else:
        return awkward.concatenate(arrays, axis=axis)
  

def create_data(arrays, inputvars):

    input_data = {} 
    for var in inputvars["SV_vars"]:
        arrays[var] = _pad(arrays[var], 6)
    for var in inputvars["trk_vars"]:
        arrays[var] = _pad(arrays[var], 30)
    #for var in inputvars["trkTosv_vars"]:
    #    arrays[var] = _pad(arrays[var], 180)

#    for var in inputvars["SV_vars"]+inputvars["trk_vars"]:
#        nonzeros = arrays[var]>0
#        array_nonzero = arrays[var][nonzeros]
#        low, center, high = np.percentile(array_nonzero, [16, 50, 84])
#        print(var, low, center, high)
#        if not high == low:
#            arrays[var] = _clip(arrays[var], bounds[var][0], bounds[var][1])/(high-low)
    
    for k, names in inputvars.items():
        input_data[k] = np.stack([arrays[n] for n in names], axis=1)
        input_data[k] = np.nan_to_num(input_data[k])
        if(input_data[k].ndim>2):
            input_data[k] = np.swapaxes(input_data[k], 1, 2)
        print(k, "has nan", np.isnan(input_data[k]).any())

    input_data["isSignal"] = arrays["isSignal"]
    input_data["weights"] = arrays["weights"]

    return input_data

def read_root(filepath, branches, load_range=None, treename="tree"):
    with uproot.open(filepath) as f:
        tree = f[treename]
        if load_range is not None:
            start = math.trunc(load_range[0]*tree.numentries)
            stop = max(start+1, math.trunc(load_range[1]*tree.numentries))
        else:
            start, stop = None, None
        outputs = tree.arrays(branches, namedecode='utf-8', entrystart=start, entrystop=stop)
    return outputs

def read_files(filelist, branches, load_range=None, show_progressbar=False, treename="tree", signal=True):
    
    from collections import defaultdict
    branches = list(branches)
    table = defaultdict(list)
    if show_progressbar:
        filelist = tqdm.tqdm(filelist)
    for filepath in filelist:
        #try:
        a = read_root(filepath, branches, load_range=load_range, treename="tree")
        #except Exception as e:
        #    a = None
        #    print("problem with processing the file", filepath)
        nSVarray = a["dijetnSV"]
        selected = nSVarray>0
        if a is not None:
            for name in branches:
                table[name].append(a[name][selected].astype('float32'))
    table = {name:_concat(arrs) for name, arrs in table.items()}
    return table

def _write_root(file, table, treename='Events', compression=-1, step=1048576):
    if compression == -1:
        compression = uproot.write.compress.LZ4(4)

    with uproot.recreate(file, compression=compression) as fout:
        fout[treename] = uproot.newtree({k:v.dtype for k, v in table.items()})
        start = 0
        while start<len(list(table.values())[0]) -1:
            fout[treename].extend({k:v[start:start+step] for k, v in table.items()})
            start+=step




parser = argparse.ArgumentParser(description="Convert the ROOT files to HD5 files")
parser.add_argument("-s", "--signal", default="", help="The name of the signal input file")
parser.add_argument("-b", "--background", default="", help="The name of the background input file")
parser.add_argument("-o", "--output", default="test", help="The name of the output file")

args = parser.parse_args()

inputvars={}

inputvars["dijet_vars"] = ["dijetSVkappaSum", "dijetnSV"]
#inputvars["SV_vars"] = ["svnTrack", "svlxy", "svlxysig", "svtrkEFrac", "svkappa", "svchi2", "svdijetcostheta", "svntrk_jet1", "svntrk_jet2", "svntrk_efracjet1", "svntrk_efracjet2"]
inputvars["SV_vars"] = ["svnTrack", "svlxy", "svlxysig", "svtrkEFrac", "svkappa", "svchi2", "svdijetcostheta", "svntrk_efracjet1", "svntrk_efracjet2", "svntrk_jet1", "svntrk_jet2", "svcosthetaPLxyz", "svmeancosthetatrks"]
inputvars["trk_vars"] = ["trkIP2D", "trkIP2Dsig", "trkIP3D", "trkIP3Dsig", "trkLxyExp", "trkEFracDijet", "trkJet1", "trkJet2", "trkIP3Dminsig", "trkdRjet1", "trkdRjet2"]
#inputvars["trkTosv_vars"] = ["trkTosv_ass", "trkTosvIP3Dtanh", "trkTosvIP3Dsigtanh", "trkTosvcostheta"]



bounds={}
bounds["dijetSVkappaSum"] = [-5000, 5000]
bounds["dijetnSV"] = [0, 7]
bounds["trkIP2D"] = [-30, 30]
bounds["trkIP2Dsig"] = [-1000, 1000]
bounds["trkIP3D"] = [-30, 30]
bounds["trkIP3Dsig"] = [-5000, 5000]
bounds["trkLxyExp"] = [-1000, 10000]
bounds["trkEFracDijet"] = [0, 1]
bounds["trkIP3Dminsig"] = [0, 500]
bounds["trkdRjet1"] = [0, 5]
bounds["trkdRjet2"] = [0, 5]
bounds["svnTrack"] = [0, 10]
bounds["svlxy"] = [0, 60]
bounds["svlxysig"] = [0, 3000]
bounds["svtrkEFrac"] = [0, 1]
bounds["svkappa"] = [-5000, 5000]
bounds["svchi2"] = [0, 5]
bounds["svdijetcostheta"] = [-1, 1]
bounds["svntrk_jet1"] = [0, 7]
bounds["svntrk_jet2"] = [0, 7]
bounds["svntrk_efracjet1"] = [0, 1]
bounds["svntrk_efracjet2"] = [0, 1] 

variables = inputvars["dijet_vars"]+inputvars["SV_vars"]+inputvars["trk_vars"]#+inputvars["trkTosv_vars"]



sig_input_path = args.signal 
bak_input_path = args.background
#
sig_root_files = glob.glob("{0}/ggHbbbb_M40*/*.root".format(sig_input_path))
bak_root_files = glob.glob("{0}/*.root".format(bak_input_path))

sig_test_files = glob.glob("/eos/uscms/store/user/lpcbril/ggHbbbb_IVF_flat/ggHbbbb_M40_10mm/*.root")
bak_test_files = glob.glob("/eos/uscms/store/user/lpcbril/TTbar_IVF_flat/test_sample/*.root")
#
sig_arrays = read_files(sig_root_files, variables, show_progressbar=True)
bak_arrays = read_files(bak_root_files, variables, show_progressbar=True)

#sig_test_arrays = read_files(sig_test_files, variables, show_progressbar=True)
#bak_test_arrays = read_files(bak_test_files, variables, show_progressbar=True)

n_sig = len(sig_arrays['dijetnSV'])
label_sig = np.ones(n_sig).astype(int)
weight_sig = np.ones(n_sig)/float(n_sig)
sig_arrays["isSignal"] =label_sig
sig_arrays["weights"] = weight_sig

#n_test_sig = len(sig_test_arrays['dijetnSV'])
#label_test_sig = np.ones(n_test_sig).astype(int)
#weight_test_sig = np.ones(n_test_sig)/float(n_test_sig)
#sig_test_arrays["isSignal"] = label_test_sig
#sig_test_arrays["weights"] = weight_test_sig

n_bak = len(bak_arrays['dijetnSV'])
label_bak = np.zeros(n_bak).astype(int)
weight_bak = np.ones(n_bak)/float(n_bak)
bak_arrays["isSignal"] = label_bak
bak_arrays["weights"] = weight_bak

#n_test_bak = len(bak_test_arrays['dijetnSV'])
#label_test_bak = np.zeros(n_test_bak).astype(int)
#weight_test_bak = np.ones(n_test_bak)/float(n_test_bak)
#bak_test_arrays["isSignal"] = label_test_bak
#bak_test_arrays["weights"] = weight_test_bak

print(label_bak)
print(bak_arrays)
#print(sig_arrays)
sig_data = create_data(sig_arrays, inputvars)
bak_data = create_data(bak_arrays, inputvars)

#sig_test_data = create_data(sig_test_arrays, inputvars)
#bak_test_data = create_data(bak_test_arrays, inputvars)

print(sig_data["isSignal"].shape)
print(bak_data["isSignal"].shape)
#print(bak_data)

total_data = {}

for key in sig_data.keys():
    total_data[key] = np.concatenate((sig_data[key], bak_data[key]))

#test_data = {}
#for key in sig_test_data.keys():
#    test_data[key] = np.concatenate((sig_test_data[key], bak_test_data[key]))

print(total_data)
print(total_data["isSignal"].shape) 
print(total_data["dijet_vars"].shape)

train_dijet, test_dijet, train_svs, test_svs, train_trks, test_trks, train_weights, test_weights, train_label, test_label = train_test_split(total_data["dijet_vars"], total_data["SV_vars"], total_data["trk_vars"],  total_data["weights"], total_data["isSignal"], test_size=0.2, shuffle=True)


from tensorflow.keras.models import Sequential, Model
from tensorflow.keras.optimizers import SGD, Adam
from tensorflow.keras.callbacks import ModelCheckpoint
from tensorflow.keras.layers import Input, Activation, Dense, Convolution2D, MaxPooling2D, Dropout, Flatten, BatchNormalization, LSTM, Concatenate


best_model_check =  ModelCheckpoint("CNN_best.h5", monitor = "val_loss", verbose=1, save_best_only=True, save_weights_only=False)

optimizer = Adam(lr = 0.001)

input_dijet = Input(name='input_dijet', shape=(len(inputvars["dijet_vars"])))
input_SV    = Input(name='input_sv',    shape=(6, len(inputvars["SV_vars"])))
input_trks  = Input(name='input_trks',  shape=(30, len(inputvars["trk_vars"])))
#input_trksvs = Input(name="input_trktosv", shape=(180, len(inputvars["trkTosv_vars"])))


cov_sv, cov_trks = CNN_block(input_SV, input_trks)
#cov_sv, cov_trks = GNN_block(cov_sv, cov_trks, input_trksvs)
#lstm_sv = Flatten()(input_SV)
#lstm_trks = Flatten()(input_trks)

#lstm_sv = tf.math.reduce_sum(cov_sv, axis=1)
#lstm_trks = tf.math.reduce_sum(cov_trks, axis=1)
lstm_sv   = LSTM(name="lstm_sv", units = 12, go_backwards=True, implementation=2)(cov_sv)
lstm_trks = LSTM(name="lstm_trks", units=60, go_backwards=True, implementation=2)(cov_trks)


batchmomentum=0.6
dropout = 0.1

x = Concatenate()([input_dijet, lstm_sv, lstm_trks])

x= Dense(units=128, activation='selu', kernel_initializer='lecun_uniform', name='dense0')(x) 
x = BatchNormalization(momentum=batchmomentum, name = "dense_batchNorm_0")(x)
x = Dropout(dropout, name="dense_dropout0")(x)

x= Dense(units=100, activation='selu', kernel_initializer='lecun_uniform', name='dense1')(x) 
x = BatchNormalization(momentum=batchmomentum, name = "dense_batchNorm_1")(x)
x = Dropout(dropout, name="dense_dropout1")(x)


x= Dense(units=100, activation='selu', kernel_initializer='lecun_uniform', name='dense2')(x) 
x = BatchNormalization(momentum=batchmomentum, name = "dense_batchNorm_2")(x)
x = Dropout(dropout, name="dense_dropout2")(x)

x= Dense(units=100, activation='selu', kernel_initializer='lecun_uniform', name='dense3')(x) 
x = BatchNormalization(momentum=batchmomentum, name = "dense_batchNorm_3")(x)
x = Dropout(dropout, name="dense_dropout3")(x)
#
#
x= Dense(units=100, activation='selu', kernel_initializer='lecun_uniform', name='dense4')(x) 
x = BatchNormalization(momentum=batchmomentum, name = "dense_batchNorm_4")(x)
x = Dropout(dropout, name="dense_dropout4")(x)

output = Dense(units=1, activation='sigmoid', name='output')(x)

model=Model(name='model_CNN', inputs = [input_dijet, input_SV, input_trks], outputs = output)

model.compile(optimizer = optimizer, loss = 'binary_crossentropy', metrics=['accuracy', roc_auc])
model.summary()

#history = model.fit(x = [total_data["dijet_vars"], total_data["SV_vars"], total_data["trk_vars"]], y = total_data["isSignal"], sample_weight = total_data["weights"], epochs=100, batch_size=2048, verbose=1)
history = model.fit(x = [train_dijet, train_svs, train_trks], y = train_label, sample_weight = train_weights, epochs=150, batch_size=2048, verbose=1, validation_data = (([test_dijet, test_svs, test_trks], test_label, test_weights)), callbacks=[best_model_check])


with open('history_CNN_test.json', 'w') as f:
    json.dump(history.history, f)

model.save("CNN_final.h5")

#Output = model.predict([test_data["dijet_vars"], test_data["SV_vars"], test_data["trk_vars"]], use_multiprocessing=True)
#
#
#print("prediction done!")
#print(Output)
#
#new_data = {}
#new_data["isSignal"] = test_data["isSignal"]
#
#new_data["DNN"] = Output
#
#_write_root("test_write_CNN_new_history.root", new_data)
 

#input_data = {}
#for var in inputvars["SV_vars"]:
#    sig_arrays[var] = _pad(sig_arrays[var], 6)
#for var in inputvars["trk_vars"]:
#    sig_arrays[var] = _pad(sig_arrays[var], 30)
#
#print(sig_arrays)
#
#for k,names in inputvars.items():
#   
#    input_data[k] = np.stack([sig_arrays[n] for n in names], axis=1)
#    print("shape:",k, np.shape(input_data[k]))
#    if(str(k)=="SV_vars" or str(k)=="trk_vars"):
#        print("yes") 
#        input_data[k]=np.swapaxes(input_data[k], 1, 2)
#    print("new shape:", np.shape(input_data[k]))

#print(sig_data)
    


#tree = uproot.open(infname)["tree"]
#arrays = tree.arrays(branches=variables, entrystop=None)


#print(arrays)

#df.to_hdf(args.output+".hd5", key="DJ", mode="w")

