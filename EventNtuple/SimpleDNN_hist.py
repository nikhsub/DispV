import ROOT
import sys
import numpy as np 
import argparse 


parser = argparse.ArgumentParser(description="produce some simple histograms")

parser.add_argument("-f", "--file", default="", help="The path to the analysis tree")
parser.add_argument("-o", "--output", default="output_hist", help="The name of the output file")


args = parser.parse_args()
#filenames = args.files.split(',')
filename = args.file

tfile = ROOT.TFile(filename)
ttree = tfile.Get("tree")
h_evt = tfile.Get("h_evt")

h_DNNd = ROOT.TH1F("h_DNNd", "h_DNNd", 100, 0, 1)
h_DNNd.Sumw2()

h_DNNp = ROOT.TH1F("h_DNNp", "h_DNNp", 100, 0, 1)
h_DNNp.Sumw2()


outname = args.output

fout = ROOT.TFile("{0}.root".format(outname), "recreate")


ttree.SetBranchStatus("*", 0)
ttree.SetBranchStatus("SVDNNd", 1)
ttree.SetBranchStatus("SVDNNp", 1)

nevents = ttree.GetEntries()

for iev in range(nevents):
    if iev%10000==1:
        print(iev)

    ttree.GetEntry(iev)

    h_DNNd.Fill(ttree.SVDNNd)
    h_DNNp.Fill(ttree.SVDNNp)


fout.WriteTObject(h_DNNd, "h_DNNd")
fout.WriteTObject(h_DNNp, "h_DNNp")
fout.WriteTObject(h_evt, "h_evt")

fout.Close()




