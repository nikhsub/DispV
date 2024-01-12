import sys, os
import argparse
import math
from math import log10, sqrt


import ROOT
from ROOT import TFile, TCanvas, TH1F
from ROOT import gStyle
from ROOT import kGreen, kRed, kBlue

gStyle.SetOptStat(0)



h2_DNN_p_vs_d = ROOT.TH2D("h2", "h2", 50, 0., 1., 50, 0., 1.)
h2_DNN_p_vs_d.Sumw2()

parser = argparse.ArgumentParser(description="Background Prediction test")
parser.add_argument("-p", "--pcut", default=0.1, type=float, help="The cut on DNN_p")
parser.add_argument("-d", "--dcut", default=0.9, type=float, help="The cut on DNN_d")
parser.add_argument("-i", "--input", default="", help="The path for the input files")
#parser.add_argument("-o", "--output", default="test", help="The name of the output file")

args = parser.parse_args()

tfile = ROOT.TFile(args.input)#("QCD_test_GNN_Disp_noEFrac.root")
ttree = tfile.Get("Events")

nevts = ttree.GetEntries()

A_evt=0  
B_evt=0  
C_evt=0  
D_evt=0  
E_evt=0
F_evt=0
G_evt=0
H_evt=0

for iev in range(nevts):
    ttree.GetEntry(iev)
    h2_DNN_p_vs_d.Fill(ttree.DNN_p, ttree.DNN_d)   
    #sel1 = ttree.jet1nPtrk<=2
    #sel2 = ttree.jet2nPtrk<=2
    #sel3 = ttree.DNN_d>=args.dcut
   
    #if (not sel1) and (not sel2) and (not sel3):
    #    A_evt+=1
    #if sel1 and (not sel2) and (not sel3):
    #    B_evt+=1
    #if (not sel1) and sel2 and (not sel3):
    #    C_evt+=1
    #if (not sel1) and (not sel2) and sel3:
    #    D_evt+=1
    #if (not sel1) and sel2 and sel3:
    #    E_evt+=1
    #if sel1 and (not sel2) and sel3:
    #    F_evt+=1
    #if sel1 and sel2 and (not sel3):
    #    G_evt+=1
    #if sel1 and sel2 and sel3:
    #    H_evt+=1

    #if ttree.<args.pcut and ttree.DNN_d<args.dcut:
    if ttree.DNN_p<args.pcut and ttree.DNN_d<args.dcut:
        A_evt+=1
    elif ttree.DNN_p>=args.pcut and ttree.DNN_d<args.dcut:
        B_evt+=1
    elif ttree.DNN_p<args.pcut and ttree.DNN_d>=args.dcut:
        C_evt+=1
    elif ttree.DNN_p>=args.pcut and ttree.DNN_d>=args.dcut:
        D_evt+=1

pre_central = float(B_evt)*float(C_evt)/float(A_evt)
pre_err = pre_central*sqrt(1/float(B_evt)+1/float(C_evt)+1/float(A_evt))
#pre_central = float(G_evt)*float(D_evt+E_evt+F_evt)/float(A_evt+B_evt+C_evt) 
#pre_err = pre_central*sqrt(1/float(G_evt)+1/float(D_evt+E_evt+F_evt)+1/float(A_evt+B_evt+C_evt))

print("prediction: ", pre_central, "+-", pre_err)
print("observation: ", D_evt)
    #h2_nptrk_DNN.Fill(ttree.jet2nPtrk, ttree.DNN_d)
    #h2_DNN_p_vs_d.Fill(ttree.DNN_p, ttree.DNN_d)

#print(h2_nptrk_DNN.GetCorrelationFactor())
print(h2_DNN_p_vs_d.GetCorrelationFactor())
h2_DNN_p_vs_d.Draw("COLZ")



can.SaveAs("test_corr.pdf")
