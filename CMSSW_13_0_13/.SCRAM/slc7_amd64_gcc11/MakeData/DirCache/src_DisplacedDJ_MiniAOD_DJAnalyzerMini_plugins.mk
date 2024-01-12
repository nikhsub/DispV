ifeq ($(strip $(DisplacedDJ_MiniAODDJAnalyzerMiniAuto)),)
DisplacedDJ_MiniAODDJAnalyzerMiniAuto := self/src/DisplacedDJ_MiniAOD/DJAnalyzerMini/plugins
PLUGINS:=yes
DisplacedDJ_MiniAODDJAnalyzerMiniAuto_files := $(patsubst src/DisplacedDJ_MiniAOD/DJAnalyzerMini/plugins/%,%,$(wildcard $(foreach dir,src/DisplacedDJ_MiniAOD/DJAnalyzerMini/plugins ,$(foreach ext,$(SRC_FILES_SUFFIXES),$(dir)/*.$(ext)))))
DisplacedDJ_MiniAODDJAnalyzerMiniAuto_BuildFile    := $(WORKINGDIR)/cache/bf/src/DisplacedDJ_MiniAOD/DJAnalyzerMini/plugins/BuildFile
DisplacedDJ_MiniAODDJAnalyzerMiniAuto_LOC_USE := self   FWCore/Framework FWCore/PluginManager FWCore/ParameterSet PhysicsTools/TensorFlow DataFormats/TrackReco DataFormats/HLTReco DataFormats/PatCandidates DataFormats/GeometryCommonDetAlgo DataFormats/HepMCCandidate DataFormats/JetReco DataFormats/BTauReco DataFormats/Math DataFormats/Common PhysicsTools/UtilAlgos PhysicsTools/RecoUtils FWCore/ServiceRegistry SimTracker/TrackAssociation SimTracker/Records HLTrigger/HLTcore RecoVertex/VertexPrimitives TrackingTools/TransientTrack TrackingTools/Records TrackingTools/IPTools RecoVertex/ConfigurableVertexReco RecoVertex/AdaptiveVertexFinder SimDataFormats/PileupSummaryInfo SimDataFormats/GeneratorProducts CondFormats/JetMETObjects JetMETCorrections/Objects JetMETCorrections/JetCorrector JetMETCorrections/Modules lhapdf 
DisplacedDJ_MiniAODDJAnalyzerMiniAuto_PRE_INIT_FUNC += $$(eval $$(call edmPlugin,DisplacedDJ_MiniAODDJAnalyzerMiniAuto,DisplacedDJ_MiniAODDJAnalyzerMiniAuto,$(SCRAMSTORENAME_LIB),src/DisplacedDJ_MiniAOD/DJAnalyzerMini/plugins))
DisplacedDJ_MiniAODDJAnalyzerMiniAuto_PACKAGE := self/src/DisplacedDJ_MiniAOD/DJAnalyzerMini/plugins
ALL_PRODS += DisplacedDJ_MiniAODDJAnalyzerMiniAuto
DisplacedDJ_MiniAOD/DJAnalyzerMini_forbigobj+=DisplacedDJ_MiniAODDJAnalyzerMiniAuto
DisplacedDJ_MiniAODDJAnalyzerMiniAuto_INIT_FUNC        += $$(eval $$(call Library,DisplacedDJ_MiniAODDJAnalyzerMiniAuto,src/DisplacedDJ_MiniAOD/DJAnalyzerMini/plugins,src_DisplacedDJ_MiniAOD_DJAnalyzerMini_plugins,$(SCRAMSTORENAME_BIN),,$(SCRAMSTORENAME_LIB),$(SCRAMSTORENAME_LOGS),edm))
DisplacedDJ_MiniAODDJAnalyzerMiniAuto_CLASS := LIBRARY
else
$(eval $(call MultipleWarningMsg,DisplacedDJ_MiniAODDJAnalyzerMiniAuto,src/DisplacedDJ_MiniAOD/DJAnalyzerMini/plugins))
endif
ALL_COMMONRULES += src_DisplacedDJ_MiniAOD_DJAnalyzerMini_plugins
src_DisplacedDJ_MiniAOD_DJAnalyzerMini_plugins_parent := DisplacedDJ_MiniAOD/DJAnalyzerMini
src_DisplacedDJ_MiniAOD_DJAnalyzerMini_plugins_INIT_FUNC += $$(eval $$(call CommonProductRules,src_DisplacedDJ_MiniAOD_DJAnalyzerMini_plugins,src/DisplacedDJ_MiniAOD/DJAnalyzerMini/plugins,PLUGINS))
