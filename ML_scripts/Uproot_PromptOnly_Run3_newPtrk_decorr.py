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
import json
import tqdm 
import awkward0 as awkward 
import glob

import tensorflow as tf
from tensorflow import keras as keras

from tensorflow.keras.callbacks import EarlyStopping

from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler

from sklearn import metrics

from math import sqrt

import CNNblock
from CNNblock import CNN_block, GNN_block, GNN_block_shallow, GNN_ptrk_block

import dcor


from utils import *


#def custom_loss(y_true, y_pred):
#    return tf.py_function(_custom_loss, (y_true, y_pred), tf.float32) 

parser = argparse.ArgumentParser(description="Convert the ROOT files to HD5 files")
parser.add_argument("-s", "--signal", default="", help="The name of the signal input file")
parser.add_argument("-b", "--background", default="", help="The name of the background input file")
parser.add_argument("-o", "--output", default="test", help="The name of the output file")
parser.add_argument("-c", "--coeff", default=0.01, type=float, help="The coefficient of the correlation factor")
parser.add_argument("-e", "--epochs", default=150, type=int, help="The number of epoches for the training") 

args = parser.parse_args()

coeff = args.coeff

Ntrk=30
Nsv=6
Nptrk=20


def custom_loss(y_true, y_pred):
    bkg_mask = y_true[:,0]==0 #and y_pred[:, 0]>0.8 and y_pred[:, 1]>0.8
    #DNNp_mask = y_pred[:,0]>0.8
    #DNNd_mask = y_pred[:,1]>0.8
    #bkg_mask = tf.math.logical_and(bkg_mask, DNNp_mask)
    #bkg_mask = tf.math.logical_and(bkg_mask, DNNd_mask)
    #bkg_mask = #bkg_mask and y_pred[:,0]>0.8 and y_pred[:,1]>0.8
    bkg_pred = y_pred[bkg_mask]
    #distcorr = dist_corr(bkg_pred[:,0], bkg_pred[:,1])
    corr = corrweighted0p8(bkg_pred[:,0], bkg_pred[:,1])
    
    #corr_eff = corr(bkg_pred[:, 0], bkg_pred[:, 1])
    #corr_eff_power5 = corr(bkg_pred[:, 0]*bkg_pred[:, 0]*bkg_pred[:, 0]*bkg_pred[:, 0]*bkg_pred[:, 0], bkg_pred[:, 1]*bkg_pred[:, 1]*bkg_pred[:, 1]*bkg_pred[:, 1]*bkg_pred[:, 1]) 
    abcd_ratio = ABCD_ratio(bkg_pred[:, 0], bkg_pred[:, 1]) 
    bce = tf.keras.losses.BinaryCrossentropy()
    cross_entropy = bce(y_true, y_pred)
    return cross_entropy+coeff*corr#+0.01*abcd_ratio



inputvars={}

inputvars["observer"]  = ["dijetnSV"]
#inputvars["dijet_vars"] = ["dijetSVkappaSum", "dijetnSV"]
##inputvars["SV_vars"] = ["svnTrack", "svlxy", "svlxysig", "svtrkEFrac", "svkappa", "svchi2", "svdijetcostheta", "svntrk_jet1", "svntrk_jet2", "svntrk_efracjet1", "svntrk_efracjet2"]
##inputvars["SV_vars"] = ["svnTrack", "svlxy", "svlxysig", "svtrkEFrac", "svkappa", "svchi2", "svdijetcostheta", "svntrk_efracjet1", "svntrk_efracjet2", "svntrk_jet1", "svntrk_jet2", "svcosthetaPLxyz", "svmeancosthetatrks"]
#
#inputvars["SV_vars"] = ["svmass","svpt", "svnTrack", "svlxysig", "svkappa", "svchi2", "svdijetcostheta",  "svntrk_jet1", "svntrk_jet2", "svcosthetaPLxyz", "svmeancosthetatrks"]
##inputvars["SV_vars"] = ["svnTrack", "svlxy", "svlxysig", "svkappa", "svchi2", "svdijetcostheta",  "svntrk_jet1", "svntrk_jet2", "svcosthetaPLxyz", "svmeancosthetatrks"]
#inputvars["trk_vars"] = ["trkIP2Dsig", "trkIP3Dsig", "trkLxyExp",  "trkJet1", "trkJet2", "trkIP3Dminsig", "trkdRjet1", "trkdRjet2", "trkEFracDijet"]
##inputvars["trk_vars"] = ["trkIP2D", "trkIP2Dsig", "trkIP3D", "trkIP3Dsig", "trkLxyExp",  "trkJet1", "trkJet2", "trkIP3Dminsig", "trkdRjet1", "trkdRjet2"]
#inputvars["trkTosv_vars"] = ["trkTosv_ass", "trkTosvIP3Dtanh", "trkTosvIP3Dsigtanh", "trkTosvcostheta"]
#inputvars["jet1ptrk_vars"] = ["jet1_ptrkIP2D", "jet1_ptrkIP2Dsig", "jet1_ptrkIP3D", "jet1_ptrkIP3Dsig", "jet1_ptrkIP3Dminsig", "jet1_ptrkEFrac"]#, "jet1_ptrkdR"]
#inputvars["jet2ptrk_vars"] = ["jet2_ptrkIP2D", "jet2_ptrkIP2Dsig", "jet2_ptrkIP3D", "jet2_ptrkIP3Dsig", "jet2_ptrkIP3Dminsig", "jet2_ptrkEFrac"]#, "jet2_ptrkdR"]
inputvars["ptrk_vars"] = ['ptrkPVidx', 'ptrkIP2D', 'ptrkIP2Dsig', 'ptrkIP3Dminsig', 'ptrkjet1', 'ptrkjet2']
inputvars["SVDNNd"] = ["SVDNNd"]



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

variables = inputvars["observer"]+inputvars["ptrk_vars"]+inputvars["SVDNNd"]#inputvars["jet1ptrk_vars"]+inputvars["jet2ptrk_vars"]+inputvars["SVDNNd"] #inputvars["dijet_vars"]+inputvars["SV_vars"]+inputvars["trk_vars"]+inputvars["trkTosv_vars"]#+inputvars["jet1ptrk_vars"]+inputvars["jet2ptrk_vars"]



sig_input_path = args.signal 
bak_input_path = args.background
#
#sig_root_files = glob.glob("{0}/ggHbbbb_M*_Pt40_NewSep23/*.root".format(sig_input_path))

sig_root_files_M40 = glob.glob("{0}/ggHbbbb_postEE_M40_*mm_*QCD_NewPtrk0p3_full/*.root".format(sig_input_path))
sig_root_files_M55 = glob.glob("{0}/ggHbbbb_postEE_M55_*mm_*QCD_NewPtrk0p3_full/*.root".format(sig_input_path))
sig_root_files = sig_root_files_M40+sig_root_files_M55
#bak_root_files = glob.glob("{0}/TTbar*trigger_tt_random_withDNNd/*.root".format(bak_input_path))
#bak_root_files = glob.glob("/eos/uscms/store/user/lpcbril/TTbar_IVF_Flat_Run3/TTbar_trigger_newPtrk/*.root")
#bak_root_files = glob.glob("/eos/uscms/store/user/lpcbril/QCD_IVF_Flat_Run3/QCD_Pt170to300_Trigger_newPtrk_qcd_full/*.root")
bak_root_files = glob.glob("{0}/output_1*.root".format(bak_input_path))

sig_test_files = glob.glob("/eos/uscms/store/user/lpcbril/ggHbbbb_IVF_flat/ggHbbbb_M40_10mm/*.root")
bak_test_files = glob.glob("/eos/uscms/store/user/lpcbril/TTbar_IVF_flat/test_sample/*.root")
#
print("***Reading signal files***")
sig_arrays = read_files(sig_root_files, variables, show_progressbar=True)
print("***Reading background files***")
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
sig_data = create_data(sig_arrays, inputvars, Ntrk, Nsv, Nptrk)
bak_data = create_data(bak_arrays, inputvars, Ntrk ,Nsv, Nptrk)

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
print(total_data["observer"].shape)

#train_jet1, test_jet1, train_jet2, test_jet2, train_DNNd, test_DNNd, train_weights, test_weights, train_label, test_label = train_test_split(total_data["jet1ptrk_vars"], total_data["jet2ptrk_vars"], total_data["SVDNNd"], total_data["weights"], total_data["isSignal"], test_size=0.2, shuffle=True) 
train_ptrk, test_ptrk, train_DNNd, test_DNNd, train_weights, test_weights, train_label, test_label = train_test_split(total_data["ptrk_vars"], total_data["SVDNNd"], total_data["weights"], total_data["isSignal"], test_size=0.2, shuffle=True)

train_label = np.expand_dims(train_label, axis=1)
train_label = np.repeat(train_label, 2 , axis=1) 

test_label = np.expand_dims(test_label, axis=1)
test_label = np.repeat(test_label, 2 , axis=1)
 
from tensorflow.keras.models import Sequential, Model
from tensorflow.keras.optimizers import SGD, Adam
from tensorflow.keras.callbacks import ModelCheckpoint
from tensorflow.keras.layers import Input, Activation, Dense, Convolution2D, MaxPooling2D, Dropout, Flatten, BatchNormalization, LSTM, Concatenate


perepoch_model_check =  ModelCheckpoint("models/PromptOnlyNewPtrk_iter{epoch:02d}_Pt40_complete_decorr_"+args.output+".h5", monitor = "val_loss", verbose=1, save_best_only=False, save_weights_only=False, mode='auto', period=1)
best_model_check =  ModelCheckpoint("models/PromptOnlyNewPtrk_best_Pt40_complete_decorr_"+args.output+".h5", monitor = "val_loss", verbose=1, save_best_only=True, save_weights_only=False)

earlystop = EarlyStopping(monitor='val_loss', patience=10, verbose=1)

optimizer = Adam(lr = 0.001)


#input_dijet = Input(name='input_dijet', shape=(len(inputvars["dijet_vars"])))
#input_SV    = Input(name='input_sv',    shape=(Nsv, len(inputvars["SV_vars"])))
#input_trks  = Input(name='input_trks',  shape=(Ntrk, len(inputvars["trk_vars"])))
#input_trksvs = Input(name="input_trktosv", shape=(180, len(inputvars["trkTosv_vars"])))
#input_jet1    = Input(name='input_jet1',    shape=(Nptrk, len(inputvars["jet1ptrk_vars"])))
#input_jet2    = Input(name='input_jet2',    shape=(Nptrk, len(inputvars["jet2ptrk_vars"])))
#input_SVDNNd =  Input(name='input_SVDNNd',  shape=1)

input_ptrk = Input(name="input_ptrk", shape=(Nptrk, len(inputvars["ptrk_vars"])))
input_SVDNNd = Input(name="input_SVDNNd", shape=1)


cov_ptrk = GNN_ptrk_block(input_ptrk, nptrk=Nptrk)
#cov_jet1, cov_jet2 = CNN_block(input_jet1, input_jet2)
x   = LSTM(name="lstm_ptrk", units =35, go_backwards=True, implementation=2)(cov_ptrk)


batchmomentum=0.6
dropout = 0.1

#x = Concatenate()([lstm_jet1, lstm_jet2])

x= Dense(units=100, activation='selu', kernel_initializer='lecun_uniform', name='dense0_prompt')(x) 
x = BatchNormalization(momentum=batchmomentum, name = "dense_batchNorm_0_prompt")(x)
x = Dropout(dropout, name="dense_dropout0_prompt")(x)

x= Dense(units=64, activation='selu', kernel_initializer='lecun_uniform', name='dense1_prompt')(x) 
x = BatchNormalization(momentum=batchmomentum, name = "dense_batchNorm_1_prompt")(x)
x = Dropout(dropout, name="dense_dropout1_prompt")(x)


x= Dense(units=64, activation='selu', kernel_initializer='lecun_uniform', name='dense2_prompt')(x) 
x = BatchNormalization(momentum=batchmomentum, name = "dense_batchNorm_2_prompt")(x)
x = Dropout(dropout, name="dense_dropout2_prompt")(x)

x= Dense(units=64, activation='selu', kernel_initializer='lecun_uniform', name='dense3_prompt')(x) 
x = BatchNormalization(momentum=batchmomentum, name = "dense_batchNorm_3_prompt")(x)
x = Dropout(dropout, name="dense_dropout3_prompt")(x)
#
#
x= Dense(units=64, activation='selu', kernel_initializer='lecun_uniform', name='dense4_prompt')(x) 
x = BatchNormalization(momentum=batchmomentum, name = "dense_batchNorm_4_prompt")(x)
x = Dropout(dropout, name="dense_dropout4_prompt")(x)

output_prompt = Dense(units=1, activation='sigmoid', name='output_prompt')(x)


#cov_sv, cov_trks = GNN_block(input_SV, input_trks, input_trksvs, ntrk=Ntrk, nsv=Nsv)
##cov_sv, cov_trks = GNN_block_shallow(cov_sv, cov_trks, input_trksvs, ntrk=Ntrk, nsv=Nsv)
#
#lstm_sv   = LSTM(name="lstm_sv", units = 12, go_backwards=True, implementation=2)(cov_sv)
#lstm_trks = LSTM(name="lstm_trks", units=60, go_backwards=True, implementation=2)(cov_trks)
#
#
#x2 = Concatenate()([input_dijet, lstm_sv, lstm_trks])
#
#x2 = Dense(units=128, activation='selu', kernel_initializer='lecun_uniform', name='dense0_disp')(x2)
#x2 = BatchNormalization(momentum=batchmomentum, name = "dense_batchNorm_0")(x2)
#x2 = Dropout(dropout, name="dense_dropout0")(x2)
#
#x2 = Dense(units=100, activation='selu', kernel_initializer='lecun_uniform', name='dense1_disp')(x2)
#x2 = BatchNormalization(momentum=batchmomentum, name = "dense_batchNorm_1")(x2)
#x2 = Dropout(dropout, name="dense_dropout1")(x2)
#
#
#x2 = Dense(units=100, activation='selu', kernel_initializer='lecun_uniform', name='dense2_disp')(x2)
#x2 = BatchNormalization(momentum=batchmomentum, name = "dense_batchNorm_2")(x2)
#x2 = Dropout(dropout, name="dense_dropout2")(x2)
#
#x2 = Dense(units=100, activation='selu', kernel_initializer='lecun_uniform', name='dense3_disp')(x2)
#x2 = BatchNormalization(momentum=batchmomentum, name = "dense_batchNorm_3")(x2)
#x2 = Dropout(dropout, name="dense_dropout3")(x2)
#
#output_disp = Dense(units=1, activation='sigmoid', name='output_disp')(x2)

output = Concatenate()([output_prompt, input_SVDNNd])


model=Model(name='model_CNN', inputs = [input_ptrk, input_SVDNNd], outputs = output)

#model.compile(optimizer = optimizer, loss = custom_loss, metrics=['accuracy', roc_auc, bkg_corr, 'binary_crossentropy'])
model.compile(optimizer = optimizer, loss = custom_loss, metrics=['accuracy', bkg_corr, roc_auc, 'binary_crossentropy'])
#model.compile(optimizer = optimizer, loss = 'BinaryCrossentropy', metrics=['accuracy', roc_auc, 'BinaryCrossentropy'])
model.summary()

#history = model.fit(x = [total_data["dijet_vars"], total_data["SV_vars"], total_data["trk_vars"], total_data["trkTosv_vars"]], y = total_data["isSignal"], sample_weight = total_data["weights"], epochs=100, batch_size=720, verbose=1, validation_data = ([test_data["dijet_vars"], test_data["SV_vars"], test_data["trk_vars"], test_data["trkTosv_vars"]], test_data["isSignal"]))

history = model.fit(x = [train_ptrk, train_DNNd], y = train_label, sample_weight = train_weights, epochs=args.epochs, batch_size=500, verbose=1, validation_data = (([test_ptrk, test_DNNd], test_label, test_weights)), callbacks=[perepoch_model_check, best_model_check, earlystop])


with open('PromptOnly_history_final_Pt40_complete_decorr_'+args.output+'.json', 'w') as f:
    json.dump(history.history, f)



model.save("models/PromptOnly_full_final_Pt40_complete_decorr_"+args.output+".h5")

#Output = model.predict([test_data["dijet_vars"], test_data["SV_vars"], test_data["trk_vars"], test_data["trkTosv_vars"]], use_multiprocessing=True)
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
#_write_root("test_write_GNN_full_new.root", new_data)
 

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

