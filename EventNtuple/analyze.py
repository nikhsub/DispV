from ROOT import *
import argparse
gStyle.SetOptStat(0)

parser = argparse.ArgumentParser(description='Analyze GNN performance')
parser.add_argument('-i', "--inputFile", default="", help="Path to slim hadded input file")
parser.add_argument('-o', "--outputFile", default="", help="Output file name")
parser.add_argument('-b', "--bkg", default=False, action="store_true", help="Is background sample?")
parser.add_argument('-s', "--saveGraphs", default =False, action="store_true", help="Save TGraphs to root file")
parser.add_argument('-t', "--tag", default = "test", help="Tag to save graphs")

args=parser.parse_args()

infile = TFile(args.inputFile, 'READ')
tree = infile.Get('tree')

GNNp = TH1F("GNNp", "GNNp", 30, 0 , 1)
GNNd = TH1F("GNNd", "GNNd", 30, 0 , 1)

GNNp.SetLineColor(2)
GNNd.SetLineColor(4)

for event in tree:
	GNNp.Fill(event.SVDNNp)
	GNNd.Fill(event.SVDNNd)

c = TCanvas()
if(args.bkg): x1=.65
else: x1=.15
y1=.7
x2=x1+.23
y2=y1+.175
leg = TLegend(x1,y1,x2,y2)
leg.AddEntry(GNNp, "Prompt Tagger", "l")
leg.AddEntry(GNNd, "Displaced Tagger", "l")

if(args.saveGraphs):
	saveFile = TFile("saveHists_"+args.tag+".root", "RECREATE")
	saveFile.WriteObject(GNNp, "prompt")
	saveFile.WriteObject(GNNd, "displaced")

if(args.bkg): GNNp.SetTitle("Background")
else: GNNp.SetTitle("Signal")

GNNp.Draw()
GNNd.Draw("SAME")
leg.Draw()
c.SaveAs(args.outputFile)





