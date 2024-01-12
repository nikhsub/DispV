import sys, os

import argparse

import math
from math import log10

import ROOT

from ROOT import TFile, TCanvas, TH1F
from ROOT import gStyle

gStyle.SetOptStat(0)

can = ROOT.TCanvas("can", "can", 800, 800)
can.SetLogy()
can.SetTicky()

QCD_files = {
             "80to120": "QCD_Pt80to120_EE_Mar25_HT425_hist.root",
             "120to170": "QCD_Pt120to170_EE_Mar25_HT425_hist.root", 
             "170to300": "QCD_Pt170to300_EE_Mar25_HT425_hist.root",
             "300to470": "QCD_Pt300to470_EE_Mar25_HT425_hist.root",
             "470to600": "QCD_Pt470to600_EE_Mar25_HT425_hist.root",
             "600to800": "QCD_Pt600to800_EE_Mar25_HT425_hist.root"
            }



QCD_xsec = {
            "80to120":  2058420,
            "120to170": 471100,
            "170to300": 11798,
            "300to470": 7823,
            "470to600": 648.2,
            "600to800": 186.9}

tf_data = ROOT.TFile("Run2022F_Mar25_HT425_hist.root")
h_data = tf_data.Get("h_DNNp")

int_data = h_data.Integral()
h_data.Scale(1/float(int_data))

h_data.Rebin(4)
h_data.SetLineColor(ROOT.kRed)
h_data.SetLineWidth(2)


h_QCD_total = ROOT.TH1F("h_QCD", "h_QCD", 100, 0, 1)

for key in QCD_files.keys():
    tfile = ROOT.TFile(QCD_files[key])
    h_DNNp_tmp = tfile.Get("h_DNNp")
    h_evt_tmp = tfile.Get("h_evt")

    h_DNNp_tmp.SetDirectory(0)
    h_DNNp_tmp.Rebin(4)
    nevts = h_evt_tmp.GetBinContent(1)
    scale = float(QCD_xsec[key])/float(nevts)
    h_DNNp_tmp.Scale(scale)
    h_QCD_total.Add(h_DNNp_tmp)


Int_QCD = h_QCD_total.Integral()
h_QCD_total.Scale(1/float(Int_QCD))

h_QCD_total.SetTitle("")

h_QCD_total.GetYaxis().SetRangeUser(1e-4, 1)

h_QCD_total.GetXaxis().SetTitle("DNN")
h_QCD_total.SetLineWidth(2)
h_QCD_total.Draw("PE")
h_data.Draw("PE SAME")

can.SaveAs("test_DNNp_dataMC.pdf")


