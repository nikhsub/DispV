import sys, os
import argparse
import math

from math import log10 

import ROOT
from ROOT import TFile, TCanvas, TH1F
from ROOT import gStyle
from ROOT import kGreen, kRed, kBlue


gStyle.SetOptStat(ROOT.kFALSE)

parser = argparse.ArgumentParser()

parser.add_argument("-s", "--signal", default="", help="The input file for signal")
parser.add_argument("-b", "--background", default="", help="The input file for background")
parser.add_argument("-o", "--output", default="", help="The name of the output file")

args = parser.parse_args()

tfile_sig = ROOT.TFile(args.signal)
tfile_bkg = ROOT.TFile(args.background)


can = ROOT.TCanvas("can", "can", 800, 800)
can.cd()
can.SetLogy()

fout = ROOT.TFile("ROC_"+args.output+".root", "RECREATE")

ttree_sig = tfile_sig.Get("Events")
ttree_bkg = tfile_bkg.Get("Events")

h_DNN_s = ROOT.TH1F("h_DNN_s", "h_DNN_s", 400, 0, 1)
h_DNN_b = ROOT.TH1F("h_DNN_b", "h_DNN_b", 400, 0, 1)

nevents_sig = ttree_sig.GetEntries()
for iev in range(nevents_sig):
    if iev%1000==1:
        print("processing signal", iev)
    ttree_sig.GetEntry(iev)
    h_DNN_s.Fill(ttree_sig.DNN)

nevents_bkg = ttree_bkg.GetEntries()
for iev in range(nevents_bkg):
    if iev%1000==1:
        print("processing background", iev)
    ttree_bkg.GetEntry(iev)
    h_DNN_b.Fill(ttree_bkg.DNN)

gra_ROC = ROOT.TGraph()
gra_ROC.GetXaxis().SetTitle("Signal Efficiency")
gra_ROC.GetYaxis().SetTitle("Background Efficiency")
gra_ROC.SetLineColor(ROOT.kBlue)
gra_ROC.GetXaxis().SetRangeUser(0, 1)
gra_ROC.GetYaxis().SetRangeUser(1e-6, 1)
gra_ROC.SetLineWidth(2)

ip = 0 
bkg_eff = 1.
sig_eff = 1.

aucscore = 0
for ibin in range(401):
    gra_ROC.SetPoint(ip, sig_eff, bkg_eff)
    bkg_eff -= float(h_DNN_b.GetBinContent(ibin))/float(h_DNN_b.Integral())
    sig_eff -= float(h_DNN_s.GetBinContent(ibin))/float(h_DNN_s.Integral())
    aucscore += float(sig_eff)*float(h_DNN_b.GetBinContent(ibin))/float(h_DNN_b.Integral())
    ip+=1

print("AUC score !!! = {}".format(aucscore))
gra_ROC.SetTitle("AUC = {0:.{1}f}".format(aucscore, 3))

gra_ROC.Draw("ACP")
can.SaveAs("testGNN.pdf")
fout.WriteTObject(gra_ROC, "gra_ROC")
fout.WriteTObject(h_DNN_b, "h_DNN_b")
fout.WriteTObject(h_DNN_s, "h_DNN_s")
fout.Close()

