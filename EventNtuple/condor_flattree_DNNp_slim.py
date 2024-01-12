#submit batch jobs for selection plots

import sys, os
import shutil
import getpass
import glob
import argparse
import subprocess
#set paths

parser = argparse.ArgumentParser(description='Submit condor jobs')
parser.add_argument('-i', "--input", default="", help="The input directory where the analyzer output trees are")
parser.add_argument('-o', "--output", default="", help="The output directory for flat trees")
parser.add_argument("-a","--abs", default=False, action="store_true", help="use absolute path") 
parser.add_argument("-e","--eos", default="", help="EOS path to copy to")
parser.add_argument("-g","--gen", default=False, action="store_true", help="do not use gen match to select the best candidate")
parser.add_argument("-t","--trigger", default=False, action="store_true", help="apply trigger to filter the events")
parser.add_argument("--ht", "--ht", default=False, action="store_true", help="apply the HLT_HT425_v control trigger")
parser.add_argument("-s","--slim", default=False, action="store_true", help="Slim the event content -- only save the dijet-level information")
parser.add_argument("-c","--cut", default=False, action="store_true", help="apply preselection")
parser.add_argument("-p", "--perjob", default=10, type=int, help="Files per job")

args=parser.parse_args()

current=os.getcwd()
basefolder=args.input
bashjob="flat.csh"
pathbashjob="{0}/{1}".format(current, bashjob)
pyscript="EventNtuple_DNNp.py"
pathpyscript="{0}/{1}".format(current, pyscript)
eospath = args.eos
nperj = args.perjob
root_files = glob.glob("{0}/*.root".format(basefolder))
filegroups = {}
icount=1
currgroup = ""

if args.abs:
    root_files=glob.glob("/eos/uscms{0}/*/000*/*.root".format(basefolder))
    #root_files = subprocess.check_output(["eosls", "{0}/*.root".format(basefolder)])
for rootfile in root_files:
    rawfile = rootfile
    print("+look at the root file: {0}".format(rootfile))
    if args.abs:
        rootfile=rootfile[rootfile.find("/store"): ]
        rootfile="root://cmseos.fnal.gov/"+rootfile
    #rootfile = rootfile.lstrip("/eos/uscms")
    if currgroup!="":
        currgroup+=","+rootfile
    else:
        currgroup+=rootfile

    if icount%nperj==0: #or rawfile==root_files[-1]:
        filegroups[icount/nperj]=currgroup
        currgroup=""
    if rawfile == root_files[-1]:
        filegroups[icount/nperj+1]=currgroup
    icount+=1

for key in filegroups.keys():
 
    #folder0 = rootfile.split("/")[-1].rstrip(".root")
    #folder1 = rootfile.split("/")[-2]
    folder0 = "output_"+str(key)
    folder = args.output+"/"
    if not os.path.isdir(folder): os.mkdir(folder)
    folder = folder+folder0
    if not os.path.isdir(folder): os.mkdir(folder)

    os.chdir(folder)

    shutil.copyfile(pathpyscript, pyscript)
    shutil.copyfile(pathbashjob, bashjob)
     
    if args.gen:
        GEN="--genmatch"
    else:
        GEN=""

    if args.trigger:
        TRIG="--trigger"
    else:
        TRIG=""

    if args.slim:
        SLIM="--slim"
    else:
        SLIM=""

    if args.cut:
        CUT="--cut"
    else:
        CUT=""

    if args.ht:
        HT="--ht"
    else:
        HT=""

    condor_filename="analyze_condor_{0}".format(folder0)
    fcondor=open(condor_filename, "w")
    fcondor.write("Executable = {0}\n".format(bashjob))
    fcondor.write("Universe = vanilla\n")
    fcondor.write("transfer_input_files = {0}\n".format(pyscript))
    fcondor.write("should_transfer_files = YES\n")
    fcondor.write("Output = {0}/{1}/run_{2}.out\n".format(current, folder, folder0))
    fcondor.write("Error  = {0}/{1}/run_{2}.err\n".format(current, folder, folder0))
    fcondor.write("Log    = {0}/{1}/run_{2}.log\n".format(current, folder, folder0))
    if args.abs:
        #rootfile="root://cmsxrootd.fnal.gov/"+rootfile
        fcondor.write("Arguments = {0} {1} {2} {3} {4} {5} {6} {7} {8} {9}\n".format(pyscript, filegroups[key], folder0, eospath, current+"/"+folder, GEN, TRIG, SLIM, CUT, HT))
    else:
        fcondor.write("Arguments = {0} {1} {2} {3} {4} {5} {6} {7} {8} {9}\n".format(pyscript, current+"/"+rootfile, folder0,eospath, current+"/"+folder, GEN, TRIG, SLIM, CUT, HT))
    fcondor.write("Queue\n")
    fcondor.close()
    
    os.system("chmod +x {0} {1} analyze_condor_{2}".format(bashjob, pyscript, folder0))
    os.system("condor_submit analyze_condor_{0}".format(folder0))
 
    os.chdir(current)
