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
