from CRABClient.UserUtilities import config#, getUsernameFromSiteDB
config = config()

config.General.requestName = 'MC_bkg_postEE_QCD800_2201'
config.General.workArea = 'crab_projects'
config.General.transferOutputs = True
config.General.transferLogs = False

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'Anl_base_MC2022_IVFlike_Disp_tensornew_dispprompt_NewPtrk_postEE_qcd_300_decorr1p0_corrweighted_test_cfg.py'

config.Data.inputDataset = '/QCD_PT-800to1000_TuneCP5_13p6TeV_pythia8/Run3Summer22EEMiniAODv3-124X_mcRun3_2022_realistic_postEE_v1-v2/MINIAODSIM' 
#config.Data.inputDBS='phys03'
#config.Data.outputPrimaryDataset = 'HiggsPortal'
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 1
#NJOBS = 1  # This is not a configuration parameter, but an auxiliary variable that we use in the next line.
#config.Data.lumiMask = 'https://cms-service-dqmdc.web.cern.ch/CAF/certification/Collisions22/Cert_Collisions2022_355100_362760_Golden.json' 
#config.Data.totalUnits = config.Data.unitsPerJob * NJOBS
#config.Data.outLFNDirBase = '/store/group/lpcbril/data_DisplacedJet_Run3'
config.Data.publication = False
config.Data.outputDatasetTag = 'MC_QCD800_2201_myTaggers'

config.Site.storageSite = 'T3_US_FNALLPC'
#config.Site.whitelist=['T2_CH_CERN','T2_IT_Pisa','T2_UK_London_IC','T2_HU_Budapest']
