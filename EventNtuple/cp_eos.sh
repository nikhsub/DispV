#!/bin/sh

for i in {1..20}
do
	xrdcp root://cmseos.fnal.gov//store/user/nvenkata/QCD_PT-800to1000_TuneCP5_13p6TeV_pythia8/MC_dataset_QCD800_nonslim_0911/231109_191337/0000/output_0_postEE_ggH_NewPtrk0p3_qcdmodel_PT300_decorr0p5_corrweighted_power2_${i}.root root://cmseos.fnal.gov//store/user/nvenkata/QCD_PT-800to1000_TuneCP5_13p6TeV_pythia8/MC_dataset_QCD800_nonslim_0911/231109_191337/0001/output_0_postEE_ggH_NewPtrk0p3_qcdmodel_PT300_decorr0p5_corrweighted_power2_${i}.root
done
