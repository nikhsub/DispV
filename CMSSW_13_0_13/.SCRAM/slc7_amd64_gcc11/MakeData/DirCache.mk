ifeq ($(strip $(DisplacedDJ_MiniAOD/DJAnalyzerMini)),)
src_DisplacedDJ_MiniAOD_DJAnalyzerMini := self/DisplacedDJ_MiniAOD/DJAnalyzerMini
DisplacedDJ_MiniAOD/DJAnalyzerMini  := src_DisplacedDJ_MiniAOD_DJAnalyzerMini
src_DisplacedDJ_MiniAOD_DJAnalyzerMini_BuildFile    := $(WORKINGDIR)/cache/bf/src/DisplacedDJ_MiniAOD/DJAnalyzerMini/BuildFile
src_DisplacedDJ_MiniAOD_DJAnalyzerMini_LOC_USE := self  PhysicsTools/TensorFlow
src_DisplacedDJ_MiniAOD_DJAnalyzerMini_EX_USE   := $(foreach d,$(src_DisplacedDJ_MiniAOD_DJAnalyzerMini_LOC_USE),$(if $($(d)_EX_FLAGS_NO_RECURSIVE_EXPORT),,$d))
ALL_EXTERNAL_PRODS += src_DisplacedDJ_MiniAOD_DJAnalyzerMini
src_DisplacedDJ_MiniAOD_DJAnalyzerMini_INIT_FUNC += $$(eval $$(call EmptyPackage,src_DisplacedDJ_MiniAOD_DJAnalyzerMini,src/DisplacedDJ_MiniAOD/DJAnalyzerMini))
endif

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
ifeq ($(strip $(DisplacedDJ_MiniAOD/DataFormats)),)
ALL_COMMONRULES += src_DisplacedDJ_MiniAOD_DataFormats_src
src_DisplacedDJ_MiniAOD_DataFormats_src_parent := DisplacedDJ_MiniAOD/DataFormats
src_DisplacedDJ_MiniAOD_DataFormats_src_INIT_FUNC := $$(eval $$(call CommonProductRules,src_DisplacedDJ_MiniAOD_DataFormats_src,src/DisplacedDJ_MiniAOD/DataFormats/src,LIBRARY))
DisplacedDJ_MiniAODDataFormats := self/DisplacedDJ_MiniAOD/DataFormats
DisplacedDJ_MiniAOD/DataFormats := DisplacedDJ_MiniAODDataFormats
DisplacedDJ_MiniAODDataFormats_files := $(patsubst src/DisplacedDJ_MiniAOD/DataFormats/src/%,%,$(wildcard $(foreach dir,src/DisplacedDJ_MiniAOD/DataFormats/src ,$(foreach ext,$(SRC_FILES_SUFFIXES),$(dir)/*.$(ext)))))
DisplacedDJ_MiniAODDataFormats_BuildFile    := $(WORKINGDIR)/cache/bf/src/DisplacedDJ_MiniAOD/DataFormats/BuildFile
DisplacedDJ_MiniAODDataFormats_LOC_USE := self   CommonTools/Utils rootrflx 
DisplacedDJ_MiniAODDataFormats_LCGDICTS  := x 
DisplacedDJ_MiniAODDataFormats_PRE_INIT_FUNC += $$(eval $$(call LCGDict,DisplacedDJ_MiniAODDataFormats,src/DisplacedDJ_MiniAOD/DataFormats/src/classes.h,src/DisplacedDJ_MiniAOD/DataFormats/src/classes_def.xml,$(SCRAMSTORENAME_LIB),$(GENREFLEX_ARGS) $(root_EX_FLAGS_GENREFLEX_FAILES_ON_WARNS)))
DisplacedDJ_MiniAODDataFormats_EX_LIB   := DisplacedDJ_MiniAODDataFormats
DisplacedDJ_MiniAODDataFormats_EX_USE   := $(foreach d,$(DisplacedDJ_MiniAODDataFormats_LOC_USE),$(if $($(d)_EX_FLAGS_NO_RECURSIVE_EXPORT),,$d))
DisplacedDJ_MiniAODDataFormats_PACKAGE := self/src/DisplacedDJ_MiniAOD/DataFormats/src
ALL_PRODS += DisplacedDJ_MiniAODDataFormats
DisplacedDJ_MiniAODDataFormats_CLASS := LIBRARY
DisplacedDJ_MiniAOD/DataFormats_forbigobj+=DisplacedDJ_MiniAODDataFormats
DisplacedDJ_MiniAODDataFormats_INIT_FUNC        += $$(eval $$(call Library,DisplacedDJ_MiniAODDataFormats,src/DisplacedDJ_MiniAOD/DataFormats/src,src_DisplacedDJ_MiniAOD_DataFormats_src,$(SCRAMSTORENAME_BIN),,$(SCRAMSTORENAME_LIB),$(SCRAMSTORENAME_LOGS),))
endif
