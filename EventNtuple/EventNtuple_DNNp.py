#Script to produce ntuples for ML training


import ROOT

import sys
import numpy as np 

import argparse 
import array

from math import sqrt, fabs, sin, exp, log10, tanh


parser = argparse.ArgumentParser(description="generate flat ntuple for the new displaced-jet analysis")


parser.add_argument("-f", "--files", default="", help="The path to the analysis tree")
parser.add_argument("-o", "--output", default="output", help="The name of the output file")
parser.add_argument("-g", "--genmatch", default=True, action="store_false", help="perform the gen match to find the best dijet candidate")
parser.add_argument("-t", "--trigger", default=False, action="store_true", help="apply trigger filter")
parser.add_argument("--ht", default=False, action="store_true", help="apply HLT_HT425_v control trigger")
parser.add_argument("-m", "--muon", default=False, action="store_true", help="apply the HLT_L1Mu240_v control trigger")
parser.add_argument("-r", "--random", default=False, action="store_true", help="apply random selection for the candiate")
parser.add_argument("-p", "--ptcut", type=float, default=40.0, help="The value for the jet pt cut")
parser.add_argument("-s", "--slim", default=False, action="store_true", help="only save part of the branches to save data size")
parser.add_argument("-c", "--cut", default=False, action="store_true", help="apply preselections")

args = parser.parse_args()

pt_cut = args.ptcut

filenames = args.files.split(',')


tree = ROOT.TChain("myAnalyzerLabel/tree")
for filename in filenames:
    tree.AddFile(filename)

outname = args.output 

fout = ROOT.TFile("{0}.root".format(outname), "recreate")


h_evt = ROOT.TH1F("h_evt", "h_evt", 20, 0, 20)
h_evt.Sumw2()

newtree = ROOT.TTree("tree", "tree")

 
max_Ntrks= 30
max_Nptrk= 7
max_Nvtxs = 6
max_trkToSV = max_Ntrks*max_Nvtxs
max_svTosv  = max_Nvtxs*(max_Nvtxs-1) 



run = array.array("I", [0])
LS  = array.array("I", [0])
evt = array.array("L", [0])



nPU = array.array("d", [0])
CaloHT = array.array("d", [0])
ntrk_size = array.array("I", [0])
nptrk_size = array.array("I", [0])
nvtx_size = array.array("I", [0])
trkToSV_size = array.array("I", [0])
svTosv_size = array.array("I", [0])



Ntrk = array.array("I", [0])
Nptrk = array.array("I", [0])
Nvtx = array.array("I", [0])
NtrkToSV = array.array("I", [0])

jet1trkEnergy = array.array('d', [0])
jet2trkEnergy = array.array('d', [0])

jet1pt  = array.array('d', [0])
jet2pt  = array.array('d', [0])
jet1eta = array.array('d', [0])
jet2eta = array.array('d', [0])

dijetpt = array.array('d', [0])
dijetM  = array.array('d', [0])


SVDNNd = array.array('d', [0])
SVDNNp = array.array('d', [0])

DNNpass0p8 = array.array('I', [0])
DNNpass0p9 = array.array('I', [0])

dijetSVkappaSum = array.array('d', [0])
dijetnSV        = array.array('d', [0])


dijetnPtrk1 = array.array('d', [0])
dijetnPtrk2 = array.array('d', [0])


SVjet1maxPVPt  = array.array('d', [0])
SVjet2maxPVPt  = array.array('d', [0])
SVjet1maxPVPtFrac = array.array('d', [0])
SVjet2maxPVPtFrac = array.array('d', [0])
dijetPUPEjetFrac = array.array('d', [0])


svtrkEFracSum = array.array('d', [0])
sv1stIP2Dsig = array.array('d', [0])
sv2ndIP2Dsig = array.array('d', [0])

trkIP2D       = array.array('d', max_Ntrks*[0])
trkIP2Dsig    = array.array('d', max_Ntrks*[0])
trkIP3D       = array.array('d', max_Ntrks*[0])
trkIP3Dsig    = array.array('d', max_Ntrks*[0])
trkLxyExp     = array.array('d', max_Ntrks*[0])
trkEFracDijet = array.array('d', max_Ntrks*[0])
trkJet1       = array.array('I', max_Ntrks*[0])
trkJet2       = array.array('I', max_Ntrks*[0])
trkIP3Dminsig = array.array('d', max_Ntrks*[0])
trkenergy     = array.array('d', max_Ntrks*[0])
trkpt         = array.array('d', max_Ntrks*[0])
trkjetenergyfrac = array.array('d', max_Ntrks*[0])
trktrkenergyfrac = array.array('d', max_Ntrks*[0])

trkdRjet1     = array.array('d', max_Ntrks*[0])
trkdRjet2     = array.array('d', max_Ntrks*[0])


jet1_ptrkIP2D = array.array('d', max_Nptrk*[0])
jet1_ptrkIP2Dsig = array.array('d', max_Nptrk*[0])
jet1_ptrkIP3D = array.array('d', max_Nptrk*[0])
jet1_ptrkIP3Dsig = array.array('d', max_Nptrk*[0])
jet1_ptrkEFrac = array.array('d', max_Nptrk*[0])
jet1_ptrkIP3Dminsig = array.array('d', max_Nptrk*[0])

jet2_ptrkIP2D = array.array('d', max_Nptrk*[0])
jet2_ptrkIP2Dsig = array.array('d', max_Nptrk*[0])
jet2_ptrkIP3D = array.array('d', max_Nptrk*[0])
jet2_ptrkIP3Dsig = array.array('d', max_Nptrk*[0])
jet2_ptrkEFrac = array.array('d', max_Nptrk*[0])
jet2_ptrkIP3Dminsig = array.array('d', max_Nptrk*[0])



svnTrack      = array.array('I', max_Nvtxs*[0])
svmass        = array.array('d', max_Nvtxs*[0])
svpt          = array.array('d', max_Nvtxs*[0])

svlxy         = array.array('d', max_Nvtxs*[0])
svlxysig      = array.array('d', max_Nvtxs*[0])
svlxyz        = array.array('d', max_Nvtxs*[0])
svlxyzsig     = array.array('d', max_Nvtxs*[0])
svtrkEFrac    = array.array('d', max_Nvtxs*[0])
svkappa       = array.array('d', max_Nvtxs*[0])
svchi2        = array.array('d', max_Nvtxs*[0])
svdijetcostheta = array.array('d', max_Nvtxs*[0])
svcosthetaPLxyz = array.array('d', max_Nvtxs*[0])
svmeancosthetatrks = array.array('d', max_Nvtxs*[0])

svntrk_jet1   = array.array('I', max_Nvtxs*[0])
svntrk_jet2   = array.array('I', max_Nvtxs*[0])
svntrk_efracjet1 = array.array('d', max_Nvtxs*[0])
svntrk_efracjet2 = array.array('d', max_Nvtxs*[0])


trkTosv_ass        = array.array('I', max_trkToSV*[0])
trkTosvIP3D        = array.array('d', max_trkToSV*[0])
trkTosvIP3Dsig     = array.array('d', max_trkToSV*[0])
trkTosvIP3Dtanh    = array.array('d', max_trkToSV*[0])
trkTosvIP3Dsigtanh = array.array('d', max_trkToSV*[0])
trkTosvcostheta    = array.array('d', max_trkToSV*[0])

svTosv_dist    = array.array('d', max_svTosv*[0])
svTosv_distsig = array.array('d', max_svTosv*[0])
svTosv_disttanh = array.array('d', max_svTosv*[0])
svTosv_distsigtanh = array.array('d', max_svTosv*[0])

svTosv_jet1dR  = array.array('d', max_svTosv*[0])
svTosv_jet2dR  = array.array('d', max_svTosv*[0])
svTosv_jet1costheta = array.array('d', max_svTosv*[0])  
svTosv_jet2costheta = array.array('d', max_svTosv*[0])



trignames = [#"HLT_HT200_v",
             #"HLT_HT275_v",
             "HLT_HT325_v",
             "HLT_IsoMu24_v",
             "HLT_HT425_v",
             #"HLT_Mu20_v", 
             "HLT_HT750_DisplacedDijet80_Inclusive_v",
             "HLT_HT650_DisplacedDijet80_Inclusive_v",
             "HLT_HT650_DisplacedDijet60_Inclusive_v",
             #"HLT_HT430_DisplacedDijet60_DisplacedTrack_v",
             #"HLT_HT350_DisplacedDijet40_DisplacedTrack_v",
             "HLT_HT430_DisplacedDijet40_DisplacedTrack_v",
             "HLT_HT500_DisplacedDijet40_Inclusive_v",
             "HLT_HT550_DisplacedDijet40_Inclusive_v"]
             #"HLT_VBF_DisplacedJet40_DisplacedTrack_v",               
             #"HLT_VBF_DisplacedJet40_DisplacedTrack_2TrackIP2DSig5_v",
             #"HLT_VBF_DisplacedJet40_TightID_DisplacedTrack_v",       
             #"HLT_VBF_DisplacedJet40_Hadronic_v",                     
             #"HLT_VBF_DisplacedJet40_Hadronic_2PromptTrack_v",        
             #"HLT_VBF_DisplacedJet40_TightID_Hadronic_v",             
             #"HLT_VBF_DisplacedJet40_VTightID_Hadronic_v",            
             #"HLT_VBF_DisplacedJet40_VVTightID_Hadronic_v",           
             #"HLT_VBF_DisplacedJet40_VTightID_DisplacedTrack_v",      
             #"HLT_VBF_DisplacedJet40_VVTightID_DisplacedTrack_v"]     

trigarray = {}
for name in trignames:
    trigarray[name]=array.array('I', [0])




newtree.Branch("run", run, "run/i")
newtree.Branch("evt", evt, "evt/l")
newtree.Branch("LS", LS, "LS/i")
newtree.Branch("CaloHT", CaloHT, "CaloHT/D")
newtree.Branch("nPU", nPU, "nPU/D")

newtree.Branch("ntrk_size", ntrk_size, "ntrk_size/i")
newtree.Branch("nptrk_size", nptrk_size, "nptrk_size/i")
newtree.Branch("nvtx_size", nvtx_size, "nvtx_size/i")
newtree.Branch("trkToSV_size", trkToSV_size, "trkToSV_size/i")
newtree.Branch("svTosv_size", svTosv_size, "svTosv_size/i") 

newtree.Branch("Ntrk", Ntrk, "Ntrk/i")
newtree.Branch("Nvtx", Nvtx, "Nvtx/i")
newtree.Branch("NtrkToSV", NtrkToSV, "NtrkToSV/i")


newtree.Branch("jet1trkEnergy", jet1trkEnergy, "jet1trkEnergy/D")
newtree.Branch("jet2trkEnergy", jet2trkEnergy, "jet2trkEnergy/D")
newtree.Branch("dijetSVkappaSum", dijetSVkappaSum, "dijetSVkappaSum/D")
newtree.Branch("dijetnSV",       dijetnSV,     "dijetnSV/D")
newtree.Branch("dijetnPtrk1",    dijetnPtrk1,   "dijetnPtrk1/D")
newtree.Branch("dijetnPtrk2",    dijetnPtrk2,   "dijetnPtrk2/D")


newtree.Branch("SVjet1maxPVPt", SVjet1maxPVPt, "SVjet1maxPVPt/D")
newtree.Branch("SVjet2maxPVPt", SVjet2maxPVPt, "SVjet2maxPVPt/D")
newtree.Branch("SVjet1maxPVPtFrac", SVjet1maxPVPtFrac, "SVjet1maxPVPtFrac/D")
newtree.Branch("SVjet2maxPVPtFrac", SVjet2maxPVPtFrac, "SVjet2maxPVPtFrac/D")
newtree.Branch("dijetPUPEjetFrac", dijetPUPEjetFrac, "dijetPUPEjetFrac/D")

newtree.Branch("svtrkEFracSum",  svtrkEFracSum, "svtrkEFracSum/D")
newtree.Branch("sv1stIP2Dsig",   sv1stIP2Dsig,  "sv1stIP2Dsig/D")
newtree.Branch("sv2ndIP2Dsig",   sv2ndIP2Dsig,  "sv2ndIP2Dsig/D")



newtree.Branch("jet1pt",         jet1pt,       "jet1pt/D")
newtree.Branch("jet2pt",         jet2pt,       "jet2pt/D")
newtree.Branch("jet1eta",        jet1eta,      "jet1eta/D")
newtree.Branch("jet2eta",        jet2eta,      "jet2eta/D")
newtree.Branch("dijetpt",        dijetpt,      "dijetpt/D")

newtree.Branch("SVDNNd",         SVDNNd,       "SVDNNd/D")
newtree.Branch("SVDNNp",         SVDNNp,       "SVDNNp/D")

newtree.Branch("DNNpass0p8",     DNNpass0p8,   "DNNpass0p8/i")
newtree.Branch("DNNpass0p9",     DNNpass0p9,   "DNNpass0p9/i")

if not args.slim:
    newtree.Branch("trkIP2D"        , trkIP2D        , "trkIP2D[ntrk_size]/D")       
    newtree.Branch("trkIP2Dsig"     , trkIP2Dsig     , "trkIP2Dsig[ntrk_size]/D") 
    newtree.Branch("trkIP3D"        , trkIP3D        , "trkIP3D[ntrk_size]/D")       
    newtree.Branch("trkIP3Dsig"     , trkIP3Dsig     , "trkIP3Dsig[ntrk_size]/D")    
    newtree.Branch("trkLxyExp"      , trkLxyExp      , "trkLxyExp[ntrk_size]/D")     
    newtree.Branch("trkEFracDijet"  , trkEFracDijet  , "trkEFracDijet[ntrk_size]/D") 
    newtree.Branch("trkJet1"        , trkJet1        , "trkJet1[ntrk_size]/i")       
    newtree.Branch("trkJet2"        , trkJet2        , "trkJet2[ntrk_size]/i")      
    newtree.Branch("trkIP3Dminsig"  , trkIP3Dminsig  , "trkIP3Dminsig[ntrk_size]/D")
    newtree.Branch("trkdRjet1"      , trkdRjet1      , "trkdRjet1[ntrk_size]/D")
    newtree.Branch("trkdRjet2"      , trkdRjet2      , "trkdRjet2[ntrk_size]/D")
    #newtree.Branch("trkenergy"      , trkenergy      , "trkenergy[ntrk_size]/D")
    #newtree.Branch("trkpt"          , trkpt          , "trkpt[ntrk_size]/D")
    #newtree.Branch("trkjetenergyfrac", trkjetenergyfrac, "trkjetenergyfrac[ntrk_size]/D")
    #newtree.Branch("trktrkenergyfrac", trktrkenergyfrac, "trktrkenergyfrac[ntrk_size]/D")
    
    newtree.Branch("jet1_ptrkIP2D" , jet1_ptrkIP2D, "jet1_ptrkIP2D[nptrk_size]/D")
    newtree.Branch("jet1_ptrkIP2Dsig", jet1_ptrkIP2Dsig, "jet1_ptrkIP2Dsig[nptrk_size]/D")
    newtree.Branch("jet1_ptrkIP3D", jet1_ptrkIP3D, "jet1_ptrkIP3D[nptrk_size]/D")
    newtree.Branch("jet1_ptrkIP3Dsig", jet1_ptrkIP3Dsig, "jet1_ptrkIP3Dsig[nptrk_size]/D")
    newtree.Branch("jet1_ptrkEFrac", jet1_ptrkEFrac, "jet1_ptrkEFrac[nptrk_size]/D")
    newtree.Branch("jet1_ptrkIP3Dminsig", jet1_ptrkIP3Dminsig, "jet1_ptrkIP3Dminsig[nptrk_size]/D")
    
    newtree.Branch("jet2_ptrkIP2D" , jet2_ptrkIP2D, "jet2_ptrkIP2D[nptrk_size]/D")
    newtree.Branch("jet2_ptrkIP2Dsig", jet2_ptrkIP2Dsig, "jet2_ptrkIP2Dsig[nptrk_size]/D")
    newtree.Branch("jet2_ptrkIP3D", jet2_ptrkIP3D, "jet2_ptrkIP3D[nptrk_size]/D")
    newtree.Branch("jet2_ptrkIP3Dsig", jet2_ptrkIP3Dsig, "jet2_ptrkIP3Dsig[nptrk_size]/D")
    newtree.Branch("jet2_ptrkEFrac", jet2_ptrkEFrac, "jet2_ptrkEFrac[nptrk_size]/D")
    newtree.Branch("jet2_ptrkIP3Dminsig", jet2_ptrkIP3Dminsig, "jet2_ptrkIP3Dminsig[nptrk_size]/D")
    
     
    
    newtree.Branch("svnTrack"   ,  svnTrack   , "svnTrack[nvtx_size]/i")
    newtree.Branch("svmass"     ,  svmass     , "svmss[nvtx_size]/D")
    newtree.Branch("svpt"       ,  svpt       , "svpt[nvtx_size]/D") 
    newtree.Branch("svlxy"      ,  svlxy      , "svlxy[nvtx_size]/D")      
    newtree.Branch("svlxysig"   ,  svlxysig   , "svlxysig[nvtx_size]/D")    
    newtree.Branch("svlxyz"     ,  svlxyz     , "svlxyz[nvtx_size]/D")      
    newtree.Branch("svlxyzsig"  ,  svlxyzsig  , "svlxyzsig[nvtx_size]/D")   
    newtree.Branch("svtrkEFrac" ,  svtrkEFrac , "svtrkEFrac[nvtx_size]/D")  
    newtree.Branch("svkappa"    ,  svkappa    , "svkappa[nvtx_size]/D")     
    newtree.Branch("svchi2"     ,  svchi2     , "svchi2[nvtx_size]/D")
    newtree.Branch("svdijetcostheta", svdijetcostheta, "svdijetcostheta[nvtx_size]/D")
    newtree.Branch("svcosthetaPLxyz", svcosthetaPLxyz, "svcosthetaPLxyz[nvtx_size]/D")
    newtree.Branch("svmeancosthetatrks", svmeancosthetatrks, "svmeancosthetatrks[nvtx_size]/D")
    
    newtree.Branch("svntrk_jet1",  svntrk_jet1, "svntrk_jet1[nvtx_size]/i")
    newtree.Branch("svntrk_jet2",  svntrk_jet2, "svntrk_jet2[nvtx_size]/i")
    newtree.Branch("svntrk_efracjet1", svntrk_efracjet1, "svntrk_efracjet1[nvtx_size]/D")
    newtree.Branch("svntrk_efracjet2", svntrk_efracjet2, "svntrk_efracjet2[nvtx_size]/D")


for name in trignames:
    newtree.Branch(name, trigarray[name], name+"/i")


if not args.slim:
    newtree.Branch("trkTosv_ass"    , trkTosv_ass    , "trkTosv_ass[trkToSV_size]/i")     
    newtree.Branch("trkTosvIP3D"    , trkTosvIP3D    , "trkTosvIP3D[trkToSV_size]/D")    
    newtree.Branch("trkTosvIP3Dsig" , trkTosvIP3Dsig , "trkTosvIP3Dsig[trkToSV_size]/D") 
    newtree.Branch("trkTosvIP3Dtanh", trkTosvIP3Dtanh, "trkTosvIP3Dtanh[trkToSV_size]/D")
    newtree.Branch("trkTosvIP3Dsigtanh", trkTosvIP3Dsigtanh, "trkTosvIP3Dsigtanh[trkToSV_size]/D")
    newtree.Branch("trkTosvcostheta", trkTosvcostheta, "trkTosvcostheta[trkToSV_size]/D")
    
    newtree.Branch("svTosv_dist", svTosv_dist, "svTosv_dist[svTosv_size]/D")
    newtree.Branch("svTosv_distsig", svTosv_distsig, "svTosv_distsig[svTosv_size]/D")
    newtree.Branch("svTosv_jet1dR", svTosv_jet1dR,  "svTosv_jet1dR[svTosv_size]/D")
    newtree.Branch("svTosv_jet2dR", svTosv_jet2dR,  "svTosv_jet2dR[svTosv_size]/D")
    newtree.Branch("svTosv_disttanh", svTosv_disttanh, "svTosv_disttanh[svTosv_size]/D")
    newtree.Branch("svTosv_distsigtanh", svTosv_distsigtanh, "svTosv_distsigtanh[svTosv_size]/D")
    newtree.Branch("svTosv_jet1costheta", svTosv_jet1costheta, "svTosv_jet1costheta[svTosv_size]/D")
    newtree.Branch("svTosv_jet2costheta", svTosv_jet2costheta, "svTosv_jet2costheta[svTosv_size]/D")

branches = tree.GetListOfBranches()


for br in branches:
    brname = br.GetName()
    for name in trignames:
        if brname.find(name)!=-1:
            print name
            tree.SetBranchAddress(brname, trigarray[name]) 

nentries = tree.GetEntries()

hasvtx = 0

for iev in range(nentries):
 
    if iev%1000==1:
        print(iev)
    tree.GetEntry(iev)
    h_evt.Fill(0)
    run[0] = tree.run
    LS[0] = tree.lumi
    CaloHT[0] = tree.CaloHT
    nPU[0] = tree.nPU
    if tree.evt>=0:
        evt[0] = tree.evt
    else:
        evt[0] = tree.evt+2**32


    #if args.trigger and (not tree.HLT_HT430_DisplacedDijet40_DisplacedTrack_v):
    #    continue

    #if args.trigger and not (tree.HLT_HT430_DisplacedDijet40_DisplacedTrack_v or tree.HLT_HT430_DisplacedDijet30_Inclusive1PtrkShortSig5_v or tree.HLT_Mu6HT240_DisplacedDijet30_Inclusive0PtrkShortSig5_v or tree.HLT_Mu6HT240_DisplacedDijet30_Inclusive1PtrkShortSig5_DisplacedLoose_v or tree.HLT_HT430_DisplacedDijet35_Inclusive1PtrkShortSig5_v or tree.HLT_Mu6HT240_DisplacedDijet35_Inlcusive0PtrkShortSig5_v or tree.HLT_Mu6HT240_DisplacedDijet35_Inclusive1PtrkShortSig5_DisplacedLoose_v or tree.HLT_HT430_DisplacedDijet40_Inclusive1PtrkShortSig5_v or tree.HLT_Mu6HT240_DisplacedDijet40_Inclusive0PtrkShortSig5_v or tree.HLT_Mu6HT240_DisplacedDijet40_Inclusive1PtrkShortSig5_DisplacedLoose_v):
    #    continue


    if args.trigger and not (((tree.HLT_HT430_DisplacedDijet40_DisplacedTrack_v or tree.HLT_HT430_DisplacedDijet30_Inclusive1PtrkShortSig5_v or tree.HLT_HT430_DisplacedDijet35_Inclusive1PtrkShortSig5_v or tree.HLT_HT430_DisplacedDijet40_Inclusive1PtrkShortSig5_v) and tree.CaloHT>430) or ((tree.HLT_Mu6HT240_DisplacedDijet30_Inclusive0PtrkShortSig5_v or tree.HLT_Mu6HT240_DisplacedDijet30_Inclusive1PtrkShortSig5_DisplacedLoose_v or tree.HLT_Mu6HT240_DisplacedDijet35_Inlcusive0PtrkShortSig5_v or tree.HLT_Mu6HT240_DisplacedDijet35_Inclusive1PtrkShortSig5_DisplacedLoose_v or tree.HLT_Mu6HT240_DisplacedDijet40_Inclusive0PtrkShortSig5_v or tree.HLT_Mu6HT240_DisplacedDijet40_Inclusive1PtrkShortSig5_DisplacedLoose_v) and tree.CaloHT>240)):
        continue 

    #if args.trigger and not ((tree.HLT_HT430_DisplacedDijet40_DisplacedTrack_v or tree.HLT_HT430_DisplacedDijet30_Inclusive1PtrkShortSig5_v or tree.HLT_Mu6HT240_DisplacedDijet30_Inclusive0PtrkShortSig5_v or tree.HLT_Mu6HT240_DisplacedDijet30_Inclusive1PtrkShortSig5_DisplacedLoose_v or tree.HLT_HT430_DisplacedDijet35_Inclusive1PtrkShortSig5_v or tree.HLT_Mu6HT240_DisplacedDijet35_Inlcusive0PtrkShortSig5_v or tree.HLT_Mu6HT240_DisplacedDijet35_Inclusive1PtrkShortSig5_DisplacedLoose_v or tree.HLT_HT430_DisplacedDijet40_Inclusive1PtrkShortSig5_v or tree.HLT_Mu6HT240_DisplacedDijet40_Inclusive0PtrkShortSig5_v or tree.HLT_Mu6HT240_DisplacedDijet40_Inclusive1PtrkShortSig5_DisplacedLoose_v)):

    #continue 

    if args.ht and not tree.HLT_HT425_v: continue
    if args.muon and not tree.HLT_L1Mu6HT240_v: continue
    h_evt.Fill(1)

    Ndijet = tree.SVjet1Idx.size()

    best_idijet = -1
    mindistgenSV = 1e6
    mindRgenmom1 = 1e6
    mindRgenmom2 = 1e6

  
    max_ntrk = 0 
    min_sumChi2 = 1e10
    max_DNNd = 0 
    
    #if args.genmatch:
    #    for idj in range(Ndijet):
    #        if tree.SVjet1Pt.at(idj)<pt_cut or tree.SVjet2Pt.at(idj)<pt_cut:
    #            continue
    #        nvtx = tree.SVdistwrtgenSV1.at(idj).size()
    #        for ivtx in range(nvtx):
    #            distgen1 = tree.SVdistwrtgenSV1.at(idj).at(ivtx)
    #            distgen2 = tree.SVdistwrtgenSV2.at(idj).at(ivtx)
    #            dRgenmom1 = tree.SVdijetdRgenmom1.at(idj).at(ivtx)
    #            dRgenmom2 = tree.SVdijetdRgenmom2.at(idj).at(ivtx)

    #            if distgen1<mindistgenSV:
    #                mindistgenSV = distgen1
    #                mindRgenmom1 = dRgenmom1
    #                best_idijet=idj 
    #            elif distgen1==mindistgenSV:
    #                if dRgenmom1<=mindRgenmom1:
    #                    mindRgenmom1=dRgenmom1
    #                    best_idijet=idj
    #        
    #            if distgen2<mindistgenSV:
    #                mindistgenSV = distgen2
    #                mindRgenmom2 = dRgenmom2
    #                best_idijet=idj 
    #            elif distgen1==mindistgenSV:
    #                if dRgenmom2<=mindRgenmom2:
    #                    mindRgenmom2=dRgenmom2
    #                    best_idijet=idj
    
    if best_idijet==-1:

        DNNpass0p8[0] = 0
        DNNpass0p9[0] = 0
        for idijet in range(Ndijet):
            if tree.SVjet1Pt.at(idijet)<pt_cut or tree.SVjet2Pt.at(idijet)<pt_cut:
                continue
   
            
            #if tree.SVjet1Pt.at(idijet)<40 or tree.SVjet2Pt.at(idijet)<40:
            #    continue

            #if tree.TrueDijet.at(idijet):
            #    best_idijet = idijet
            #    break

            tmp_ntrk = 0
            tmp_sumChi2 = 0 
            nvtx = int(tree.SVnSV.at(idijet))
            if nvtx==0:
                continue 

            if tree.SVDNNd.at(idijet)>0.8 and tree.SVDNNp.at(idijet)>0.8:
                DNNpass0p8[0]+=1

            if tree.SVDNNd.at(idijet)>0.9 and tree.SVDNNp.at(idijet)>0.9:
                DNNpass0p9[0]+=1
            svtrkEFracSum_tmp = float(tree.SVtrkenergysum.at(idijet))/float((tree.jet1trackEnergy.at(idijet)+tree.jet2trackEnergy.at(idijet)))
            ntrk = tree.dijetIndices.at(idijet).size()
            
            fabs_ip2dsig_hasSV = []

            jet1PVpt = {}
            jet2PVpt = {}

            for itrk in range(ntrk):
                if tree.dijethasSV.at(idijet).at(itrk):
                    fabs_ip2dsig_hasSV.append(fabs(tree.dijetIP2D_sig.at(idijet).at(itrk)))

            #ntrk_full = tree.fullIndices.at(idijet).size()


            #for itrk in range(ntrk_full):
            #    pvidx = tree.fullIndices.at(idijet).at(itrk)
            #    if tree.fullIndices.at(idijet).at(itrk)==1 and tree.fullIP3Dminsig.at(idijet).at(itrk)<4.0:
            #        if not jet1PVpt.has_key(pvidx):
            #            jet1PVpt[pvidx] = tree.fullenergys.at(idijet).at(itrk)
            #        else:
            #            jet1PVpt[pvidx] += tree.fullenergys.at(idijet).at(itrk)
            #    if tree.fullIndices.at(idijet).at(itrk)==2 and tree.fullIP3Dminsig.at(idijet).at(itrk)<4.0:
            #        if not jet2PVpt.has_key(pvidx):
            #            jet2PVpt[pvidx] = tree.fullenergys.at(idijet).at(itrk)
            #        else:
            #            jet2PVpt[pvidx] += tree.fullenergys.at(idijet).at(itrk)
            #jet1maxpt=0
            #jet2maxpt=0
            #for key in jet1PVpt.keys():
            #    if jet1PVpt[key]>jet1maxpt:
            #        jet1maxpt = jet1PVpt[key]

            #for key in jet2PVpt.keys():
            #    if jet2PVpt[key]>jet2maxpt:
            #        jet2maxpt = jet2PVpt[key]

            ##print(jet1maxpt, jet2maxpt) 
            #dijetPUPEjetFrac_tmp = float(jet1maxpt+jet2maxpt)/float((tree.SVjet1Pt.at(idijet)+tree.SVjet2Pt.at(idijet)))
            ##print(dijetPUPEjetFrac_tmp)
            
            if len(fabs_ip2dsig_hasSV)>=1:
                sv1stIP2Dsig_tmp = fabs_ip2dsig_hasSV[0]
            else:
                sv1stIP2Dsig_tmp = 0

            if len(fabs_ip2dsig_hasSV)>=2:
                sv2ndIP2Dsig_tmp = fabs_ip2dsig_hasSV[1]
            else:
                sv2ndIP2Dsig_tmp =0

            
            #if args.cut and dijetPUPEjetFrac_tmp>0.5:#(svtrkEFracSum_tmp<0.15 or sv2ndIP2Dsig_tmp<20):
            #    continue



            tmp_DNN = tree.SVDNNp.at(idijet)
            if tmp_DNN> max_DNNd:
                best_idijet = idijet
                max_DNNd = tmp_DNN
                #dijetPUPEjetFrac[0] = dijetPUPEjetFrac_tmp
                sv1stIP2Dsig[0] = sv1stIP2Dsig_tmp
                sv2ndIP2Dsig[0] = sv2ndIP2Dsig_tmp
                svtrkEFracSum[0] = svtrkEFracSum_tmp

                
                #if tree.TrueDijet.at(idijet):
                #    best_idijet = idijet
                #    break
            #    tmp_ntrk+=tree.SVvtxnTrack.at(idijet).at(isv)
            #    tmp_sumChi2+=tree.SVvtxChi2.at(idijet).at(isv)


            #if tmp_ntrk>max_ntrk:
            #    best_idijet = idijet
            #    max_ntrk = tmp_ntrk 
            #    min_sumChi2 = tmp_sumChi2

            #elif (tmp_ntrk==max_ntrk and max_ntrk!=0 and tmp_sumChi2<min_sumChi2):
            #    best_idijet = idijet
            #    min_sumChi2 = tmp_sumChi2


    if best_idijet!=-1:
        h_evt.Fill(2)
        hasvtx+=1       
        ntrk_size[0] = int(max_Ntrks)
        dijetSVkappaSum[0] = tree.SVkappa_total.at(best_idijet)
        jet1trkEnergy[0] = tree.jet1trackEnergy.at(best_idijet)
        jet2trkEnergy[0] = tree.jet2trackEnergy.at(best_idijet)
        dijetnPtrk1[0]  = float(tree.SVnPrompttk1.at(best_idijet))
        dijetnPtrk2[0]  = float(tree.SVnPrompttk2.at(best_idijet)) 
        #dijetdRjet1[0]   = tree.dijetdRjet1.at(best_idijet)
        #dijetdRjet2[0]   = tree.dijetdRjet2.at(best_idijet)
        dijetnSV[0]      = tree.SVnSV.at(best_idijet)
        jet1pt[0]        = tree.SVjet1Pt.at(best_idijet)
        jet2pt[0]        = tree.SVjet2Pt.at(best_idijet)
        jet1eta[0]       = tree.SVjet1Eta.at(best_idijet)
        jet2eta[0]       = tree.SVjet2Eta.at(best_idijet)
        SVDNNd[0]        = tree.SVDNNd.at(best_idijet)
        SVDNNp[0]        = tree.SVDNNp.at(best_idijet)
        SVjet1maxPVPt[0] = tree.SVjet1maxPVPt.at(best_idijet)
        SVjet2maxPVPt[0] = tree.SVjet2maxPVPt.at(best_idijet)
        SVjet1maxPVPtFrac[0] = tree.SVjet1maxPVPt.at(best_idijet)/tree.SVjet1Pt.at(best_idijet)
        SVjet2maxPVPtFrac[0] = tree.SVjet2maxPVPt.at(best_idijet)/tree.SVjet2Pt.at(best_idijet)
        dijetPUPEjetFrac[0] = (tree.SVjet1maxPVPt.at(best_idijet)+tree.SVjet2maxPVPt.at(best_idijet))/(tree.SVjet1Pt.at(best_idijet)+tree.SVjet2Pt.at(best_idijet))
        #dijetpt[0]       = tree.SVvtxP4.at(best_idijet).Pt() 
    
        nptrk_size[0]  = int(max_Nptrk)
        
        Nptrk[0] = tree.promptIP2D.at(best_idijet).size()

        jet1_iptrk = 0
        jet2_iptrk = 0
        if not args.slim:
            promptIP2D = list(tree.promptIP2D.at(best_idijet))
            promptIP2Dsig = list(tree.promptIP2D_sig.at(best_idijet))
            promptIP3D = list(tree.promptIP3D.at(best_idijet))
            promptIP3Dsig = list(tree.promptIP3D_sig.at(best_idijet))
            promptEnergy = list(tree.promptenergys.at(best_idijet))
            promptIP3Dminsig = list(tree.promptIP3Dminsig.at(best_idijet)) 

            promptIP2D.reverse()
            promptIP2Dsig.reverse()
            promptIP3D.reverse()
            promptIP3Dsig.reverse()
            promptEnergy.reverse()
            promptIP3Dminsig.reverse()
   
            for iptrk in range(Nptrk[0]):
                if tree.promptIndices.at(best_idijet).at(iptrk)==1 and jet1_iptrk<max_Nptrk:
                    jet1_ptrkIP2D[jet1_iptrk] = tanh(promptIP2D[iptrk]*10)-1
                    jet1_ptrkIP2Dsig[jet1_iptrk] = tanh(promptIP2Dsig[iptrk]/10)-1
                    jet1_ptrkIP3D[jet1_iptrk] = tanh(promptIP3D[iptrk]*10)-1
                    jet1_ptrkIP3Dsig[jet1_iptrk] = tanh(promptIP3Dsig[iptrk]/10)-1
                    jet1_ptrkEFrac[jet1_iptrk] = tanh(promptEnergy[iptrk]/tree.SVjet1Pt.at(best_idijet))
                    jet1_ptrkIP3Dminsig[jet1_iptrk] = tanh(promptIP3Dminsig[iptrk]/10)-1 
                    #print(promptIP2D[iptrk])
                    jet1_iptrk+=1

                if tree.promptIndices.at(best_idijet).at(iptrk)==2 and jet2_iptrk<max_Nptrk:
                    jet2_ptrkIP2D[jet2_iptrk] = tanh(promptIP2D[iptrk]*10)-1
                    jet2_ptrkIP2Dsig[jet2_iptrk] = tanh(promptIP2Dsig[iptrk]/10)-1
                    jet2_ptrkIP3D[jet2_iptrk] = tanh(promptIP3D[iptrk]*10)-1
                    jet2_ptrkIP3Dsig[jet2_iptrk] = tanh(promptIP3Dsig[iptrk]/10)-1
                    jet2_ptrkEFrac[jet2_iptrk] = tanh(promptEnergy[iptrk]/tree.SVjet2Pt.at(best_idijet))
                    jet2_ptrkIP3Dminsig[jet2_iptrk] = tanh(promptIP3Dminsig[iptrk]/10)-1 
                    jet2_iptrk+=1

            if jet1_iptrk<max_Nptrk:
                for i in range(jet1_iptrk, max_Nptrk):
                    jet1_ptrkIP2D[i] = 0
                    jet1_ptrkIP2Dsig[i] = 0
                    jet1_ptrkIP3D[i] = 0
                    jet1_ptrkIP3Dsig[i] = 0
                    jet1_ptrkEFrac[i] = 0
                    jet1_ptrkIP3Dminsig[i] = 0
            
            if jet2_iptrk<max_Nptrk:
                for i in range(jet2_iptrk, max_Nptrk):
                    jet2_ptrkIP2D[i] = 0
                    jet2_ptrkIP2Dsig[i] = 0
                    jet2_ptrkIP3D[i] = 0
                    jet2_ptrkIP3Dsig[i] = 0
                    jet2_ptrkEFrac[i] = 0
                    jet2_ptrkIP3Dminsig[i] = 0
              
  

            Ntrk[0] = tree.dijetIndices.at(best_idijet).size()
            for itrk in range(max_Ntrks): 
                if itrk<Ntrk[0]:
                    trkIP2D[itrk] = tree.dijetIP2D.at(best_idijet).at(itrk)
                    trkIP2Dsig[itrk] = tree.dijetIP2D_sig.at(best_idijet).at(itrk)
                    trkIP3D[itrk] = tree.dijetIP3D.at(best_idijet).at(itrk)
                    trkIP3Dsig[itrk] = tree.dijetIP3D_sig.at(best_idijet).at(itrk)
                    trkLxyExp[itrk] = tree.dijetLxyexp.at(best_idijet).at(itrk)
                    trkEFracDijet[itrk] = tree.dijetenergys.at(best_idijet).at(itrk)/(tree.jet1trackEnergy.at(best_idijet)+tree.jet2trackEnergy.at(best_idijet))
                    trkIP3Dminsig[itrk] = tree.dijetIP3D_minsig.at(best_idijet).at(itrk)
                    #trkdRjet1[itrk]     = tree.dijetdRjet1.at(best_idijet).at(itrk)
                    #trkdRjet2[itrk]     = tree.dijetdRjet2.at(best_idijet).at(itrk)


                    if tree.dijetIndices.at(best_idijet).at(itrk)==1:
                        trkJet1[itrk] = 1
                        trkJet2[itrk] = 0
                    else: 
                        trkJet1[itrk] = 0
                        trkJet2[itrk] = 1
               
                else:
                    trkIP2D[itrk] = 0
                    trkIP2Dsig[itrk] = 0
                    trkIP3D[itrk] = 0
                    trkIP3Dsig[itrk] = 0
                    trkLxyExp[itrk] = 0
                    trkEFracDijet[itrk] = 0
                    trkIP3Dminsig[itrk] = 0
                    trkJet1[itrk] = 0
                    trkJet2[itrk] = 0
                    trkdRjet1[itrk] = 0
                    trkdRjet2[itrk] =  0
    
            #Vertex variables
            nvtx_size[0] = int(max_Nvtxs)
            Nvtx[0] = tree.SVvtxx.at(best_idijet).size()
            for ivtx in range(max_Nvtxs):
                if ivtx<Nvtx[0]:
                    svnTrack[ivtx] = tree.SVvtxnTrack.at(best_idijet).at(ivtx)
                    svmass[ivtx]   = tree.SVvtxP4.at(best_idijet).at(ivtx).M()
                    svpt[ivtx]     = tree.SVvtxP4.at(best_idijet).at(ivtx).Pt()
                    svlxy[ivtx]    = tree.SVvtxlxy.at(best_idijet).at(ivtx)
                    svlxysig[ivtx] = tree.SVvtxlxysig.at(best_idijet).at(ivtx)
                    svtrkEFrac[ivtx] = tree.SVtrksEnergyFrac.at(best_idijet).at(ivtx)
                    svkappa[ivtx] = tree.SVkappa.at(best_idijet).at(ivtx)
                    svchi2[ivtx]  = tree.SVvtxChi2.at(best_idijet).at(ivtx)
                    svdijetcostheta[ivtx] = tree.SVdijetcostheta.at(best_idijet).at(ivtx)
                    svcosthetaPLxyz[ivtx] = tree.SVcosthetaPLxyz.at(best_idijet).at(ivtx)
                    svmeancosthetatrks[ivtx] = tree.SVmeancosthetatrks.at(best_idijet).at(ivtx)
                    svntrk_jet1[ivtx] = tree.SVvtxntrk_jet1.at(best_idijet).at(ivtx)
                    svntrk_jet2[ivtx] = tree.SVvtxntrk_jet2.at(best_idijet).at(ivtx)
                    svntrk_efracjet1[ivtx] = tree.SVenergyfrac_jet1.at(best_idijet).at(ivtx)
                    svntrk_efracjet2[ivtx] = tree.SVenergyfrac_jet2.at(best_idijet).at(ivtx)
       
                else: 
                    svnTrack[ivtx] = 0
                    svmass[ivtx] = 0
                    svpt[ivtx] = 0 
                    svlxy[ivtx] = 0
                    svlxysig[ivtx] = 0   
                    svtrkEFrac[ivtx] = 0
                    svkappa[ivtx] = 0
                    svchi2[ivtx]  = 0
                    svdijetcostheta[ivtx] = 0
                    svcosthetaPLxyz[ivtx] = 0
                    svmeancosthetatrks[ivtx] = 0
                    svntrk_jet1[ivtx] = 0
                    svntrk_jet2[ivtx] = 0 
                    svntrk_efracjet1[ivtx] = 0
                    svntrk_efracjet2[ivtx] = 0

        trkToSV_size[0] = int(max_trkToSV)
 
        if not args.slim: 
        #Track to vertex variables
            for itrk in range(max_Ntrks):
                for ivtx in range(max_Nvtxs):
                    if itrk<Ntrk[0] and ivtx<Nvtx[0]:
                        trkTosv_ass[ivtx*max_Ntrks+itrk] = tree.dijet_assSV.at(best_idijet).at(itrk).at(ivtx)
                        trkTosvIP3D[ivtx*max_Ntrks+itrk] = tree.dijet_ip3dwrtSV.at(best_idijet).at(itrk).at(ivtx)
                        trkTosvIP3Dsig[ivtx*max_Ntrks+itrk] = tree.dijet_ip3dsigwrtSV.at(best_idijet).at(itrk).at(ivtx)
                        trkTosvIP3Dtanh[ivtx*max_Ntrks+itrk] = tree.dijet_ip3dwrtSVtanh.at(best_idijet).at(itrk).at(ivtx)
                        trkTosvIP3Dsigtanh[ivtx*max_Ntrks+itrk] = tree.dijet_ip3dsigwrtSVtanh.at(best_idijet).at(itrk).at(ivtx)
                        trkTosvcostheta[ivtx*max_Ntrks+itrk] = tree.dijet_costhetawrtSV.at(best_idijet).at(itrk).at(ivtx)

                    else:
                        trkTosv_ass[ivtx*max_Ntrks+itrk] = 0 
                        trkTosvIP3D[ivtx*max_Ntrks+itrk] = 0
                        trkTosvIP3Dsig[ivtx*max_Ntrks+itrk] = 0 
                        trkTosvIP3Dtanh[ivtx*max_Ntrks+itrk] = 0 
                        trkTosvIP3Dsigtanh[ivtx*max_Ntrks+itrk] = 0
                        trkTosvcostheta[ivtx*max_Ntrks+itrk] = 0


            svTosv_size[0] = int(max_svTosv)        

            for isvTosv in range(max_svTosv):
                if isvTosv<Nvtx[0]*(max_Nvtxs-1): 
                    svTosv_dist[isvTosv]    = tree.SVtoSVdist.at(best_idijet).at(isvTosv)
                    svTosv_distsig[isvTosv] = tree.SVtoSVdistsig.at(best_idijet).at(isvTosv)
                    svTosv_disttanh[isvTosv] = tree.SVtoSVdisttanh.at(best_idijet).at(isvTosv)
                    svTosv_distsigtanh[isvTosv] = tree.SVtoSVdistsigtanh.at(best_idijet).at(isvTosv)

                    svTosv_jet1dR[isvTosv]  = tree.SVtoSVjet1dR.at(best_idijet).at(isvTosv)
                    svTosv_jet2dR[isvTosv]  = tree.SVtoSVjet2dR.at(best_idijet).at(isvTosv)
                    svTosv_jet1costheta[isvTosv] = tree.SVtoSVjet1costheta.at(best_idijet).at(isvTosv)
                    svTosv_jet2costheta[isvTosv] = tree.SVtoSVjet2costheta.at(best_idijet).at(isvTosv)

                else: 
                    svTosv_dist[isvTosv]    = 0              
                    svTosv_distsig[isvTosv] = 0
                    svTosv_disttanh[isvTosv] = 0
                    svTosv_distsigtanh[isvTosv] = 0
                    svTosv_jet1dR[isvTosv]  = 0
                    svTosv_jet2dR[isvTosv]  = 0
                    svTosv_jet1costheta[isvTosv] = 0
                    svTosv_jet2costheta[isvTosv] = 0
                     
       
        newtree.Fill() 
     
    #h_ntrk.Fill(max_ntrk)

print(hasvtx, nentries)
fout.WriteTObject(h_evt, "h_evt")
fout.WriteTObject(newtree, "tree")
fout.Close()
        

