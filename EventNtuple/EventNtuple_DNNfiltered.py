import sys
import ROOT
import numpy as np 

import argparse
import array


parser = argparse.ArgumentParser(description="filter out the low DNN events")

parser.add_argument("-f", "--files", default="", help="The input files")
parser.add_argument("-o", "--output", default="output", help="The name of the output file")
parser.add_argument("-p", "--DNNp", type=float, default=0.8, help="the cut on the DNNp")
parser.add_argument("-d", "--DNNd", type=float, default=0.8, help="the cut on the DNNd")

args = parser.parse_args()

filenames = args.files.split(',')

tree = ROOT.TChain("tree")
for filename in filenames:
    tree.AddFile(filename)

outname = args.output
fout = ROOT.TFile("{0}.root".format(outname), "recreate")

newtree = ROOT.TTree("tree", "tree")

jet1pt = array.array('d', [0])
jet2pt = array.array('d', [0])
jet1eta = array.array('d', [0])
jet2eta = array.array('d', [0])

SVjet1maxPVPt = array.array('d', [0])
SVjet2maxPVPt = array.array('d', [0])
SVjet1maxPVPtFrac = array.array('d', [0])
SVjet2maxPVPtFrac = array.array('d', [0])
dijetPUPEjetFrac = array.array('d', [0])

SVDNNd = array.array('d', [0])
SVDNNp = array.array('d', [0])

nentries = tree.GetEntries()

newtree = ROOT.TTree("tree", "tree")

newtree.Branch("jet1pt", jet1pt, "jet1pt/D")
newtree.Branch("jet2pt", jet2pt, "jet2pt/D")
newtree.Branch("jet1eta", jet1eta, "jet1eta/D")
newtree.Branch("jet2eta", jet2eta, "jet2eta/D")

newtree.Branch("SVjet1maxPVPt", SVjet1maxPVPt, "SVjet1maxPVPt/D")
newtree.Branch("SVjet2maxPVPt", SVjet2maxPVPt, "SVjet2maxPVPt/D")
newtree.Branch("SVjet1maxPVPtFrac", SVjet1maxPVPtFrac, "SVjet1maxPVPtFrac/D")
newtree.Branch("SVjet2maxPVPtFrac", SVjet2maxPVPtFrac, "SVjet2maxPVPtFrac/D")
newtree.Branch("dijetPUPEjetFrac", dijetPUPEjetFrac, "dijetPUPEjetFrac/D")

newtree.Branch("SVDNNd", SVDNNd, "SVDNNd/D")
newtree.Branch("SVDNNp", SVDNNp, "SVDNNp/D")


 

for iev in range(nentries):
    if iev%100000 ==1:
        print(iev)

    tree.GetEntry(iev)

    if tree.SVDNNd<args.DNNd or tree.SVDNNp<args.DNNp:
        continue

    jet1pt[0] = tree.jet1pt
    jet2pt[0] = tree.jet2pt
    jet1eta[0] = tree.jet1eta
    jet2eta[0] = tree.jet2eta
   
    SVjet1maxPVPt[0] = tree.SVjet1maxPVPt
    SVjet2maxPVPt[0] = tree.SVjet2maxPVPt
    SVjet1maxPVPtFrac[0] = tree.SVjet1maxPVPtFrac
    SVjet2maxPVPtFrac[0] = tree.SVjet2maxPVPtFrac
    dijetPUPEjetFrac[0] = tree.dijetPUPEjetFrac

    SVDNNd[0] = tree.SVDNNd
    SVDNNp[0] = tree.SVDNNp

    newtree.Fill()

    
fout.WriteTObject(newtree, "tree")
fout.Close()  
