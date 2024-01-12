from CRABClient.UserUtilities import config#, getUsernameFromSiteDB
config = config()

config.General.requestName = 'data_DisplacedJet2022D_v1_Run3_dispprompt_NewPtrk'
config.General.workArea = 'crab_projects'
config.General.transferOutputs = True
config.General.transferLogs = False

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'Anl_base_Data2022_IVFlike_Disp_tensornew_dispprompt_NewPtrk_tt_test_cfg.py'

config.Data.inputDataset = '/DisplacedJet/Run2022D-PromptReco-v1/MINIAOD' 
#config.Data.inputDBS='phys03'
#config.Data.outputPrimaryDataset = 'HiggsPortal'
config.Data.splitting = 'LumiBased'
config.Data.unitsPerJob = 40
#NJOBS = 1  # This is not a configuration parameter, but an auxiliary variable that we use in the next line.
config.Data.lumiMask = 'https://cms-service-dqmdc.web.cern.ch/CAF/certification/Collisions22/Cert_Collisions2022_355100_362760_Golden.json' 
#config.Data.totalUnits = config.Data.unitsPerJob * NJOBS
config.Data.outLFNDirBase = '/store/group/lpcbril/data_DisplacedJet_Run3'
config.Data.publication = False
config.Data.outputDatasetTag = 'data_DisplacedJet2022D_v1_Run3_dispprompt_NewPtrk'

config.Site.storageSite = 'T3_US_FNALLPC'
#config.Site.whitelist=['T2_CH_CERN','T2_IT_Pisa','T2_UK_London_IC','T2_HU_Budapest']
