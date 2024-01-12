from CRABClient.UserUtilities import config#, getUsernameFromSiteDB
config = config()

config.General.requestName = 'QCD_Pt80_EDAN_Run3_dispprompt_NewPtrk_fullmodel_Mar25'
config.General.workArea = 'crab_projects'
config.General.transferOutputs = True
config.General.transferLogs = False

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'Anl_base_MC2022_IVFlike_Disp_tensornew_dispprompt_NewPtrk_QCD300_decorr1p0_corrweighted_power3_cfg.py' 

config.Data.inputDataset = '/QCD_PT-80to120_TuneCP5_13p6TeV_pythia8/Run3Summer22MiniAODv3-124X_mcRun3_2022_realistic_v12-v2/MINIAODSIM' 
#config.Data.inputDBS='phys03'
#config.Data.outputPrimaryDataset = 'HiggsPortal'
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 1
#NJOBS = 1  # This is not a configuration parameter, but an auxiliary variable that we use in the next line.
#config.Data.lumiMask = 'https://cms-service-dqm.web.cern.ch/cms-service-dqm/CAF/certification/Collisions16/13TeV/ReReco/Final/Cert_271036-284044_13TeV_23Sep2016ReReco_Collisions16_JSON.txt'
#config.Data.totalUnits = config.Data.unitsPerJob * NJOBS
config.Data.outLFNDirBase = '/store/group/lpcbril/QCD_EDAN_ntuple_Run3'
config.Data.publication = False
config.Data.outputDatasetTag = 'QCD_Pt80_Run3_dispprompt_NewPtrk_fullmodel_Mar25'

config.Site.storageSite = 'T3_US_FNALLPC'
#config.Site.whitelist=['T2_CH_CERN','T2_IT_Pisa','T2_UK_London_IC','T2_HU_Budapest']
