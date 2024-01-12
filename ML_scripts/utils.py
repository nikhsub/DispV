import os, sys
import time 
import getopt
import argparse
import ROOT as r
#import varsList
import numpy as np 
import uproot3 as uproot#uproot3 as uproot
import math
from math import sqrt, fabs
import pandas as pd
#import root_pandas
import h5py
import json
import tqdm 
import awkward0 as awkward 
import glob

import tensorflow as tf
from tensorflow import keras as keras

from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler

from sklearn import metrics

import CNNblock
from CNNblock import CNN_block, GNN_block


def corr(X, Y):
    x_mean = tf.math.reduce_mean(X)
    y_mean = tf.math.reduce_mean(Y)

    X_sub = X-x_mean
    Y_sub = Y-y_mean
    cov = tf.math.reduce_mean(X_sub*Y_sub)
    stdX = tf.math.reduce_std(X)
    stdY = tf.math.reduce_std(Y)
   
    return tf.math.abs(cov/stdX/stdY)

def corrweighted0p8(X, Y):

    #X_weights = X#tf.sigmoid(300*(X-0.8))
    #Y_weights = Y#tf.sigmoid(300*(Y-0.8))

    Weights = Y*Y
    sum_weights = tf.math.reduce_sum(Weights)

    X_new = Weights*X
    Y_new = Weights*Y
    
    X_mean_weighted = tf.math.reduce_sum(X_new)/sum_weights
    Y_mean_weighted = tf.math.reduce_sum(Y_new)/sum_weights

    X_sub = X-X_mean_weighted
    Y_sub = Y-Y_mean_weighted
    
    cov_weighted = tf.math.reduce_sum(X_sub*Y_sub*Weights)/sum_weights

    stdX_weighted = tf.math.reduce_sum(X_sub*X_sub*Weights)/sum_weights
    stdY_weighted = tf.math.reduce_sum(Y_sub*Y_sub*Weights)/sum_weights

    return tf.math.abs(cov_weighted)/tf.math.sqrt(stdX_weighted*stdY_weighted) 
    #X_new = tf.sigmoid(300*(X-0.8))*X
    #Y_new = tf.sigmoid(300*(Y-0.8))*Y
    
    #X_mean = tf.math.reduce_mean(X_new)
    #Y_mean = tf.math.reduce_mean(Y_new)
   


def custom_loss(y_true, y_pred):
    bkg_mask = y_true[:,0]==0
    bkg_pred = y_pred[bkg_mask]
    #distcorr = dist_corr(bkg_pred[:,0], bkg_pred[:,1])
    corr_eff = corr(bkg_pred[:, 0], bkg_pred[:, 1])
    bce = tf.keras.losses.BinaryCrossentropy()
    cross_entropy = bce(y_true, y_pred)
    return cross_entropy+10*corr_eff

def bkg_corr(y_true, y_pred):
    bkg_mask = y_true[:, 0]==0
    bkg_pred = y_pred[bkg_mask]
    return corr(bkg_pred[:, 0], bkg_pred[:, 1])

def ABCD_ratio(X, Y):
    DNN_cuts = [0.5, 0.6, 0.7, 0.8, 0.9]
    frac_sum = 0
    nfrac = 0
    for p_cut in DNN_cuts:
        for d_cut in DNN_cuts:
            nA = tf.reduce_sum(tf.sigmoid(100*(p_cut-X))*tf.sigmoid(100*(d_cut-Y)))
            nB = tf.reduce_sum(tf.sigmoid(100*(d_cut-Y))*tf.sigmoid(100*(X-p_cut)))
            nC = tf.reduce_sum(tf.sigmoid(100*(p_cut-X))*tf.sigmoid(100*(Y-d_cut)))
            nD = tf.reduce_sum(tf.sigmoid(100*(X-p_cut))*tf.sigmoid(100*(Y-d_cut)))
            frac_sum+=tf.math.abs(float(nB*nC)/float(nA)-float(nD))/tf.math.sqrt(float(nD))
            #print(nA, nB, nC, nD, frac_sum)
            nfrac+=1

    return frac_sum/nfrac


def bkg_abcd(y_true, y_pred):
    bkg_mask = y_true[:, 0]==0
    bkg_pred = y_pred[bkg_mask]
    return ABCD_ratio(bkg_pred[:, 0], bkg_pred[:, 1])
def dist_corr_sample(Xi, Yi):
   
    #leng = tf.size(Xi)
    #print("length", leng)
    #ratio = int(sqrt(leng))
    slice_ = tf.range(0, 2000, 1)
    
    X = tf.gather(Xi, slice_)
    Y = tf.gather(Yi, slice_)
    #print(X)
    #print(Y)
    #X = Xi[slice_, ]
    #Y = Yi[silce_, ]

    xx = tf.reshape(X, [-1, 1])
    xx = tf.tile(xx, [1, tf.size(X)])
 
    xx_t = tf.transpose(xx)
    amat = tf.math.abs(xx-xx_t)

    xx = tf.reshape(Y, [-1, 1])
    xx = tf.tile(xx, [1, tf.size(Y)])
    
    xx_t = tf.transpose(xx)
    bmat = tf.math.abs(xx-xx_t)

    amatavg = tf.reduce_mean(amat, axis=1)
    bmatavg = tf.reduce_mean(bmat, axis=1)

    minuend_1 = tf.tile(amatavg, [tf.size(X)])
    minuend_1 = tf.reshape(minuend_1, [tf.size(X), tf.size(X)])
    minuend_2 = tf.transpose(minuend_1)

    Amat = amat-minuend_1-minuend_2+tf.reduce_mean(amatavg)
    
    minuend_1 = tf.tile(bmatavg, [tf.size(X)])
    minuend_1 = tf.reshape(minuend_1, [tf.size(X), tf.size(X)])
    minuend_2 = tf.transpose(minuend_1)

    Bmat = bmat-minuend_1-minuend_2+tf.reduce_mean(bmatavg)

    ABavg = tf.reduce_mean(Amat*Bmat, axis=1)
    AAavg = tf.reduce_mean(Amat*Amat, axis=1)
    BBavg = tf.reduce_mean(Bmat*Bmat, axis=1)

    dCorr = tf.reduce_mean(ABavg)/tf.math.sqrt(tf.reduce_mean(AAavg)*tf.reduce_mean(BBavg))
    return dCorr
    
def dist_corr(X, Y):

    xx = tf.reshape(X, [-1, 1])
    xx = tf.tile(xx, [1, tf.size(X)])
 
    xx_t = tf.transpose(xx)
    amat = tf.math.abs(xx-xx_t)

    xx = tf.reshape(Y, [-1, 1])
    xx = tf.tile(xx, [1, tf.size(Y)])
    
    xx_t = tf.transpose(xx)
    bmat = tf.math.abs(xx-xx_t)

    amatavg = tf.reduce_mean(amat, axis=1)
    bmatavg = tf.reduce_mean(bmat, axis=1)

    minuend_1 = tf.tile(amatavg, [tf.size(X)])
    minuend_1 = tf.reshape(minuend_1, [tf.size(X), tf.size(X)])
    minuend_2 = tf.transpose(minuend_1)

    Amat = amat-minuend_1-minuend_2+tf.reduce_mean(amatavg)
    
    minuend_1 = tf.tile(bmatavg, [tf.size(X)])
    minuend_1 = tf.reshape(minuend_1, [tf.size(X), tf.size(X)])
    minuend_2 = tf.transpose(minuend_1)

    Bmat = bmat-minuend_1-minuend_2+tf.reduce_mean(bmatavg)

    ABavg = tf.reduce_mean(Amat*Bmat, axis=1)
    AAavg = tf.reduce_mean(Amat*Amat, axis=1)
    BBavg = tf.reduce_mean(Bmat*Bmat, axis=1)

    dCorr = tf.reduce_mean(ABavg)/tf.math.sqrt(tf.reduce_mean(AAavg)*tf.reduce_mean(BBavg))
    return dCorr
    


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
  

def create_data(arrays, inputvars, Ntrk=30, Nsv=6, Nptrk=7):

    input_data = {}
    try: 
        for var in inputvars["SV_vars"]:
            arrays[var] = _pad(arrays[var], Nsv)
    except:
        print("problem in creating SV data")
    try:
        for var in inputvars["trk_vars"]:
            arrays[var] = _pad(arrays[var], Ntrk)
    except:
        print("problem in creating track data")
    try:
        for var in inputvars["trkTosv_vars"]:
            arrays[var] = _pad(arrays[var], 180)
    except:
        print("problem in creating track to SV data")

    try:
        for var in inputvars["jet1ptrk_vars"]:
            arrays[var] = _pad(arrays[var], Nptrk)
    except:
        print("problem in creating jet 1 prompt track data")
        
    try:
        for var in inputvars["jet2ptrk_vars"]:
            arrays[var] = _pad(arrays[var], Nptrk)
    except:
        print("problem in creating jet 2 prompt track data")

    try: 
        for var in inputvars["ptrk_vars"]:
            arrays[var] = _pad(arrays[var], Nptrk)
    except:
        print("problem in creating dijet prompt track data")
        

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

def write_root(file, table, treename='Events', compression=-1, step=1048576):
    if compression == -1:
        compression = uproot.write.compress.LZ4(2)

    with uproot.recreate(file, compression=compression) as fout:
        fout[treename] = uproot.newtree({k:v.dtype for k, v in table.items()})
        start = 0
        while start<len(list(table.values())[0]) -1:
            fout[treename].extend({k:v[start:start+step] for k, v in table.items()})
            start+=step

