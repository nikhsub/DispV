from ROOT import *
import argparse
gStyle.SetOptStat(0)

parser = argparse.ArgumentParser(description='Analyze GNN performance')
parser.add_argument("-i1", "--inputFile1", default="", help="Input file 1")
parser.add_argument("-i2", "--inputFile2", default="", help="Input file 2")
parser.add_argument("-t", "--tag", default="test", help="Output tag")
parser.add_argument("-roc", "--roc", default=False, action="store_true", help="Read ROC curves") 
parser.add_argument("-l", "--log", default=False, action="store_true", help="Log scale")

args=parser.parse_args()

file1 = TFile(args.inputFile1, "READ")
file2 = TFile(args.inputFile2, "READ")

if(args.roc):
	gr1_disp = file1.Get("DispROC")
	gr1_prompt = file1.Get("PromptROC")
	gr2_disp = file2.Get("DispROC")
        gr2_prompt = file2.Get("PromptROC")
else:
	gr1_disp = file1.Get("displaced")
	gr1_prompt = file1.Get("prompt")
	gr2_disp = file2.Get("displaced")
	gr2_prompt = file2.Get("prompt")
	
gr1_disp.SetLineColor(kRed)
gr1_prompt.SetLineColor(kRed)
gr2_disp.SetLineColor(kBlue)
gr2_prompt.SetLineColor(kBlue)

c1 = TCanvas()
c2 = TCanvas()
if(args.log):
	c1.SetLogy()
	c2.SetLogy()
x1=.15
y1=.7
x2=x1+.23
y2=y1+.175
leg1 = TLegend(x1,y1,x2,y2)
leg2 = TLegend(x1,y1,x2,y2)
leg1.AddEntry(gr1_disp, "Old Tagger", "l")
leg1.AddEntry(gr2_disp, "New Tagger", "l")
leg2.AddEntry(gr1_prompt, "Old Tagger", "l")
leg2.AddEntry(gr2_prompt, "New Tagger", "l")

c1.cd()
gr1_disp.SetTitle("Displaced Tagger")
gr1_disp.Draw()
gr2_disp.Draw("SAME")
leg1.Draw()
if(args.roc):c1.SaveAs("DispTagger_"+args.tag+"_ROC.png")
else:c1.SaveAs("DispTagger_"+args.tag+".png")

c2.cd()
gr1_prompt.SetTitle("Prompt Tagger")
gr1_prompt.Draw()
gr2_prompt.Draw("SAME")
leg2.Draw()
if(args.roc):c2.SaveAs("PromptTagger_"+args.tag+"_ROC.png")
else:c2.SaveAs("PromptTagger_"+args.tag+".png")

