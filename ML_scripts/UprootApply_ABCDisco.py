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

from utils import *





parser = argparse.ArgumentParser(description="Convert the ROOT files to HD5 files")
parser.add_argument("-i", "--input", default="", help="The path for the input files")
parser.add_argument("-m", "--model", default="ABCD_best.h5", help="The name of the input DNN model")
parser.add_argument("-o", "--output", default="test", help="The name of the output file")

args = parser.parse_args()

inputvars={}


inputvars["observers"] = ["dijetnPtrk1", "dijetnPtrk2"]
inputvars["dijet_vars"] = ["jet1pt", "jet2pt", "dijetSVkappaSum", "dijetnSV"]
#inputvars["SV_vars"] = ["svnTrack", "svlxy", "svlxysig", "svtrkEFrac", "svkappa", "svchi2", "svdijetcostheta", "svntrk_jet1", "svntrk_jet2", "svntrk_efracjet1", "svntrk_efracjet2"]
#inputvars["SV_vars"] = ["svnTrack", "svlxy", "svlxysig", "svtrkEFrac", "svkappa", "svchi2", "svdijetcostheta", "svntrk_efracjet1", "svntrk_efracjet2", "svntrk_jet1", "svntrk_jet2", "svcosthetaPLxyz", "svmeancosthetatrks"]
inputvars["SV_vars"] = ["svmass", "svpt", "svnTrack", "svlxy", "svlxysig",  "svkappa", "svchi2", "svdijetcostheta", "svntrk_jet1", "svntrk_jet2", "svcosthetaPLxyz", "svmeancosthetatrks"]
inputvars["trk_vars"] = ["trkIP2D", "trkIP2Dsig", "trkIP3D", "trkIP3Dsig", "trkLxyExp", "trkJet1", "trkJet2", "trkIP3Dminsig", "trkdRjet1", "trkdRjet2", "trkEFracDijet"]
inputvars["trkTosv_vars"] = ["trkTosv_ass", "trkTosvIP3Dtanh", "trkTosvIP3Dsigtanh", "trkTosvcostheta"]

inputvars["jet1ptrk_vars"] = ["jet1_ptrkIP2D", "jet1_ptrkIP2Dsig", "jet1_ptrkIP3D", "jet1_ptrkIP3Dsig",  "jet1_ptrkIP3Dminsig"]
inputvars["jet2ptrk_vars"] = ["jet2_ptrkIP2D", "jet2_ptrkIP2Dsig", "jet2_ptrkIP3D", "jet2_ptrkIP3Dsig",  "jet2_ptrkIP3Dminsig"]


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

variables = inputvars["observers"]+inputvars["dijet_vars"]+inputvars["SV_vars"]+inputvars["trk_vars"]+inputvars["trkTosv_vars"]+inputvars["jet1ptrk_vars"]+inputvars["jet2ptrk_vars"]



sig_input_path = args.input 
#bak_input_path = args.background
#
sig_root_files = glob.glob("{0}/*.root".format(sig_input_path))

#
sig_arrays = read_files(sig_root_files, variables, show_progressbar=True)

n_sig = len(sig_arrays['dijetnSV'])
label_sig = np.ones(n_sig).astype(int)
weight_sig = np.ones(n_sig)/float(n_sig)
sig_arrays["isSignal"] =label_sig
sig_arrays["weights"] = weight_sig

sig_data = create_data(sig_arrays, inputvars)


print(sig_data["isSignal"].shape)
#print(bak_data)


from tensorflow.keras.models import load_model 


custom_objects = {"roc_auc":roc_auc, "custom_loss":custom_loss, "bkg_corr":bkg_corr}

with keras.utils.custom_object_scope(custom_objects):
    model_ABCD = load_model(args.model)


output = model_ABCD.predict([sig_data["jet1ptrk_vars"], sig_data["jet2ptrk_vars"], sig_data["dijet_vars"], sig_data["SV_vars"], sig_data["trk_vars"], sig_data["trkTosv_vars"]], use_multiprocessing=True)



print("prediction done!")
#print(Output)

new_data = {}
new_data["isSignal"] = sig_data["isSignal"]
#print sig_data["observers"]
new_data["jet1nPtrk"] = sig_data["observers"][:, 0]
new_data["jet2nPtrk"] = sig_data["observers"][:, 1]
new_data["DNN_d"] = output[:,1]
new_data["DNN_p"] = output[:,0]

print(new_data["DNN_d"])

outputname = args.output+"_ABCD.root"
write_root(outputname, new_data)
 

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

