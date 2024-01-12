#!/bin/sh

#pyscript=$1
#inputfile=$2
#outputname=$3
#outputpath=$4

source /cvmfs/cms.cern.ch/cmsset_default.sh
#export ROOTSYS=/cvmfs/cms.cern.ch/slc6_amd64_gcc472/lcg/root/5.32.00-cms
export PATH=$ROOTSYS/bin:$PATH
current=$PWD
echo $current
scram p CMSSW CMSSW_13_0_13
cd CMSSW_13_0_13
cmsenv
source $ROOTSYS/bin/thisroot.sh
cd $current
rm -r CMSSW_13_0_13
#cd $6
#xrdcp root://cmseos.fnal.gov//store/user/jluo/Reweight/Material_Map_HIST.root ./
#eos root://cmseos.fnal.gov mkdir $5
#eosmkdir -p $5

export LD_LIBRARY_PATH=$ROOTSYS/lib/:$LD_LIBRARY_PATH
echo $LD_LIBRARY_PATH
python $1 -f $2 -o $3 $5 $6
#rm Material
#xrdcp *.root root://cmseos.fnal.gov/$4
#scp *.root $4
#rm *.root 
