import FWCore.ParameterSet.Config as cms
import FWCore.PythonUtilities.LumiList as LumiList
process = cms.Process("OWNPARTICLES")

process.load('Configuration.StandardSequences.Services_cff')
process.load('JetMETCorrections.Configuration.JetCorrectors_cff')
process.load("FWCore.MessageService.MessageLogger_cfi")
process.load("Configuration.StandardSequences.MagneticField_cff")
process.load("TrackingTools/TransientTrack/TransientTrackBuilder_cfi")
process.load("Configuration.StandardSequences.GeometryRecoDB_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.load('Configuration.StandardSequences.Reconstruction_cff')
process.load('RecoTracker.Configuration.RecoTracker_cff')
process.load('Configuration.StandardSequences.MagneticField_AutoFromDBCurrent_cff')
from Configuration.AlCa.autoCond import autoCond
process.GlobalTag.globaltag =  cms.string("124X_dataRun3_Prompt_v4")#autoCond["run2_mc"]#cms.string("94X_mc2017_realistic_v14")

#Jet Tracks Association
process.load('RecoJets.JetAssociationProducers.ak4JTA_cff')


#process.load("CondCore.DBCommon.CondDBCommon_cfi")
#from CondCore.DBCommon.CondDBSetup_cfi import *
#process.load("CondCore.CondDB.CondDB_cfi")
#process.load("JetMETCorrections.Modules.JetResolutionESProducer_cfi")
#from CondCore.CondDB.CondDB_cfi import *
#process.jec = cms.ESSource("PoolDBESSource",
#      DBParameters = cms.PSet(
#        messageLevel = cms.untracked.int32(0)
#        ),
#      timetype = cms.string('runnumber'),
#      toGet = cms.VPSet(
#      cms.PSet(
#            record = cms.string('JetCorrectionsRecord'),
#            tag    = cms.string('JetCorrectorParametersCollection_Spring16_23Sep2016V2_MC_AK4Calo'),
#            # tag    = cms.string('JetCorrectorParametersCollection_Fall15_25nsV2_MC_AK4PFchs'),
#            label  = cms.untracked.string('AK4Calo')
#            ),
#     # cms.PSet(
#     #       record = cms.string('JetCorrectionsRecord'),
#     #       tag    = cms.string('JetCorrectorParametersCollection_Fall15_V2_DATA_AK8PFPuppi'),
#     #       # tag    = cms.string('JetCorrectorParametersCollection_Fall15_25nsV2_MC_AK8PFPuppi'),
#     #       label  = cms.untracked.string('AK8PFPuppi')
#     #       ),
#      ## here you add as many jet types as you need
#      ## note that the tag name is specific for the particular sqlite file 
#      ), 
#      connect = cms.string('sqlite:python/Spring16_23Sep2016V2_MC.db')#('sqlite:/uscms_data/d3/jluo/work/JEC/Spring16_25nsV6_MC.db')
#     # uncomment above tag lines and this comment to use MC JEC
#     # connect = cms.string('sqlite:Fall15_25nsV2_DATA.db')
#)
#
### add an es_prefer statement to resolve a possible conflict from simultaneous connection to a global tag
#process.es_prefer_jec = cms.ESPrefer('PoolDBESSource','jec')
#
#from CondCore.DBCommon.CondDBSetup_cfi import *
#process.jer = cms.ESSource("PoolDBESSource",
#    CondDBSetup,
#    toGet = cms.VPSet(
#        cms.PSet(
#            record = cms.string('JetResolutionRcd'),
#            tag = cms.string('JR_Spring16_25nsV10_MC_PtResolution_AK4PFchs'),
#            label = cms.untracked.string('AK4PFchs_pt')
#        ),
#
#        cms.PSet(
#            record = cms.string('JetResolutionScaleFactorRcd'),
#            tag = cms.string('JR_Spring16_25nsV10_MC_SF_AK4PFchs'),
#            label = cms.untracked.string('AK4PFchs')
#
#        ),
#     ),
#     connect = cms.string('sqlite:python/Spring16_25nsV10_MC.db')
#)
#
#process.es_prefer_jer = cms.ESPrefer('PoolDBESSource', 'jer')


# Use PAT
#process.load("PhysicsTools.PatAlgos.patSequences_cff")
#from PhysicsTools.PatAlgos.patTemplate_cFg import *
#from Dijet.TrackAnalyzr.pattupe_cfg import *
#process.load("PhysicsTools.PatAlgos.patSequences_cff")


#process.load("PhysicsTools.PatAlgos.producersLayer1.patCandidates_cff")
#process.load("PhysicsTools.PatAlgos.selectionLayer1.selectedPatCandidates_cff")

# load the standard PAT config
#process.load("PhysicsTools.PatAlgos.patSequences_cff")
# MC removing
#from PhysicsTools.PatAlgos.tools.coreTools import *
#runOnData(process)
#removeMCMatching(process, ['All'])

process.load('JetMETCorrections.Configuration.JetCorrectors_cff')
process.load('JetMETCorrections.Configuration.CorrectedJetProducers_cff')
from JetMETCorrections.Configuration.CorrectedJetProducers_cff import *
from JetMETCorrections.Configuration.CorrectedJetProducers_cff import ak4PFCHSJetsL2

#process.ak4CaloCorrectedJets = cms.EDProducer('CorrectedCaloJetProducer',
#   src   = cms.InputTag('ak4CaloJets'),
#   correctors = cms.VInputTag('ak4CaloL1FastL2L3Corrector')
#)  

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

#from DisplacedDJ_MiniAOD.DJAnalyzerMini.DijetIVFMiniDefault_cfi import DijetIVFMiniDefault

ClusteringParam = cms.PSet(
          seedMax3DIPSignificance =  cms.double(9999.0),
          seedMax3DIPValue =  cms.double(9999.0),
          seedMin3DIPSignificance = cms.double(1.2),
          seedMin3DIPValue = cms.double(0.005),
          clusterMaxDistance = cms.double(2.0),
          clusterMaxSignificance = cms.double(10.0),
          distanceRatio = cms.double(10.0),
          clusterMinAngleCosine = cms.double(0.0),
          maxTimeSignificance = cms.double(3.5),
)

process.myAnalyzerLabel = cms.EDAnalyzer('DijetIVFMiniMLDisp_dispprompttensor', #DijetIVFMiniDefault.clone(
     #, trigJetFilter = cms.InputTag('hlt2CaloJet40', '', 'HLT')#('hltCaloJetCollection40Filter', '', 'HLT2')
     #, trigSummary = cms.InputTag('hltTriggerSummaryAOD', '', 'HLT')
     
      tracks = cms.untracked.InputTag('packedPFCandidates')
     , losttracks = cms.untracked.InputTag('lostTracks', '', "RECO")
  
     #, associatorCALO = cms.untracked.InputTag("ak4JTAatCAL")
     #, associatorVTX = cms.untracked.InputTag("ak4JTAatVX")
     , jets = cms.untracked.InputTag('slimmedCaloJets')
     , calojets = cms.untracked.InputTag('slimmedCaloJets')
     , primaryVertices = cms.untracked.InputTag('offlineSlimmedPrimaryVertices')
     , generator = cms.untracked.InputTag('generator')
     , addPileupInfo = cms.untracked.InputTag('addPileupInfo')
     , jetCorr = cms.untracked.InputTag('ak4CaloL1FastL2L3ResidualCorrector') 
     , TrackPtCut = cms.untracked.double(1.0)
     , vtxweight = cms.untracked.double(0.5)
     , vertexfitter = cms.untracked.PSet(
         finder = cms.string('avr')
     )
     , trigResults = cms.InputTag('TriggerResults::HLT')
     #, JTACALO = cms.untracked.bool(False)
     #, JTAVTX = cms.untracked.bool(False)
     #, JTACombine = cms.untracked.bool(True)
     , runtrigger = cms.untracked.bool(True)
     , isMC = cms.untracked.bool(False)
     , getgeninfo = cms.untracked.bool(False)
     , checkHitOpt = cms.untracked.bool(False)
     , genParticles = cms.untracked.InputTag("prunedGenParticles")
     , pdfReweight = cms.untracked.bool(False)
     , JECTag = cms.untracked.string("AK4Calo")
     , clusterizer = ClusteringParam
     #, graph_path=cms.FileInPath("DisplacedDJ_MiniAOD/DJAnalyzerMini/data/testgraph.pb") 
     #, graph_path=cms.FileInPath("DisplacedDJ_MiniAOD/DJAnalyzerMini/data/DispOnly_Run3_nojetpt_Pt120to170.pb") 
     , dispgraph_path=cms.FileInPath("DisplacedDJ_MiniAOD/DJAnalyzerMini/data/DispOnly_Run3_TTbar_Trigger_random_best.pb") 
     , promptgraph_path=cms.FileInPath("DisplacedDJ_MiniAOD/DJAnalyzerMini/data/PromptOnly_best_test.pb")
     #, ttreename = cms.untracked.string("tree")
    
)

    
process.TFileService = cms.Service("TFileService", 
        fileName = cms.string("test_output.root"),
)

#process.ak4JTAatVX = cms.EDProducer("JetTracksAssociatorAtVertex",
#        tracks = cms.InputTag("generalTracks"),
#        coneSize = cms.double(0.4),
#        useAssigned = cms.bool(False),
#        pvSrc = cms.InputTag("offlinePrimaryVerticesWithBS"),
#        jets = cms.InputTag("ak4CaloJets")
#)
#process.ak4JTAatCAL = cms.EDProducer("JetTracksAssociatorAtCaloFace",
#        tracks = cms.InputTag("generalTracks"),
#        extrapolations = cms.InputTag("trackExtrapolator"),
#        trackQuality = cms.string("goodIterative"),
#        coneSize = cms.double(0.4),
#        useAssigned = cms.bool(False),
#        jets = cms.InputTag("ak4CaloJets")
#)
process.p = cms.Path(

        ak4CaloL1FastL2L3ResidualCorrectorChain*
        ak4CaloL1FastL2L3ResidualCorrector*
        #process.ak4CaloCorrectedJets*
        #process.ak4JTAatVX*
        #process.ak4JTAatCAL*
        process.myAnalyzerLabel
)

#process.source = cms.Source('PoolSource', fileNames = cms.untracked.vstring('root://cmsxrootd.fnal.gov//store/mc/RunIIAutumn18MiniAOD/ggH_HToSSTobbbb_MH-125_MS-40_ctauS-1_pT75_TuneCP5_13TeV-powheg-pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/110000/BEECFCD9-42A0-8947-A9ED-61E7CBFD6091.root'))#('root://cmsxrootd.fnal.gov//store/mc/RunIIAutumn18MiniAOD/ggH_HToSSTobbbb_MH-125_MS-15_ctauS-10_pT75_TuneCP5_13TeV-powheg-pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/100000/23CA27BB-F781-324C-A275-F14781DBB072.root'))#('root://cmsxrootd.fnal.gov//store/mc/RunIIAutumn18MiniAOD/ggH_HToSSTobbbb_MH-125_MS-40_ctauS-10_pT75_TuneCP5_13TeV-powheg-pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/270000/105753CE-B21A-824B-990B-B2C15F926F36.root'))#('root://cmsxrootd.fnal.gov//store/mc/RunIIFall17MiniAODv2/VBFH_HToSSTobbbb_MH-125_MS-55_ctauS-10_pT100_TuneCP5_13TeV-powheg-pythia8/MINIAODSIM/PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/120000/E0EA443F-FC03-EB11-8725-485B398972FC.root'))#('root://cmsxrootd.fnal.gov//store/mc/RunIISummer16MiniAODv3/WminusH_HToSSTodddd_WToLNu_MH-125_MS-55_ctauS-10_TuneCUETP8M1_13TeV-powheg-pythia8/MINIAODSIM/PUMoriond17_94X_mcRun2_asymptotic_v3-v1/00000/708CEBC4-BFD0-E811-BB81-D0BF9CC18CE8.root'))
process.source = cms.Source('PoolSource', fileNames = cms.untracked.vstring('root://cmsxrootd.fnal.gov//store/data/Run2022D/DisplacedJet/MINIAOD/PromptReco-v2/000/357/734/00000/584133c2-95a1-4939-876d-1cecc2f4ff39.root'))
#process.source = cms.Source('PoolSource', fileNames = cms.untracked.vstring('file:/eos/uscms/store/user/lpcbril/MC_test/ggH4b_MINIAODSIM_Run3/HToLL_Run3/HToLLTo4b_Powheg_M40_10mm_CP5_13p6TeV_HPt100_MINIAODSIM_new/221226_041719/0000/step0_967.root'))
#process.source = cms.Source('PoolSource', fileNames = cms.untracked.vstring('file:/eos/uscms/store/mc/RunIIFall15DR76/QCD_Pt-15to7000_TuneCUETP8M1_Flat_13TeV_pythia8/AODSIM/PU25nsData2015v1_magnetOn_76X_mcRun2_asymptotic_v12-v1/20000/52522584-72A3-E511-AAD3-000F53273750.root'))
process.TFileService.fileName = cms.string('output_0_data_one_merge_tt_random_best.root')
#process.myAnalyzerLabel.JTACALO = cms.untracked.bool(False)
#process.myAnalyzerLabel.JTAVTX = cms.untracked.bool(True)
#process.myAnalyzerLabel.JTACombine = cms.untracked.bool(False)
#process.myAnalyzerLabel.checkHitOpt = cms.untracked.bool(False)
#process.ak4JTAatVX.coneSize = cms.double(0.5)
#process.ak4JTAatCAL.coneSize = cms.double(0.5)
