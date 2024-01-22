#!/bin/sh

cd CMSSW_13_0_13/src
cmsenv
cd ../..
#echo $ROOTSYS
#source /cvmfs/cms.cern.ch/cmsset_default.sh
#export PATH=$ROOTSYS/bin:$PATH
source $ROOTSYS/bin/thisroot.sh
