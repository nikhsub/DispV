ALL_SUBSYSTEMS+=DisplacedDJ_MiniAOD
subdirs_src_DisplacedDJ_MiniAOD = src_DisplacedDJ_MiniAOD_DJAnalyzerMini src_DisplacedDJ_MiniAOD_DataFormats
subdirs_src += src_DisplacedDJ_MiniAOD
ALL_PACKAGES += DisplacedDJ_MiniAOD/DJAnalyzerMini
subdirs_src_DisplacedDJ_MiniAOD_DJAnalyzerMini := src_DisplacedDJ_MiniAOD_DJAnalyzerMini_plugins src_DisplacedDJ_MiniAOD_DJAnalyzerMini_python
ifeq ($(strip $(PyDisplacedDJ_MiniAODDJAnalyzerMini)),)
PyDisplacedDJ_MiniAODDJAnalyzerMini := self/src/DisplacedDJ_MiniAOD/DJAnalyzerMini/python
src_DisplacedDJ_MiniAOD_DJAnalyzerMini_python_parent := src/DisplacedDJ_MiniAOD/DJAnalyzerMini
ALL_PYTHON_DIRS += $(patsubst src/%,%,src/DisplacedDJ_MiniAOD/DJAnalyzerMini/python)
PyDisplacedDJ_MiniAODDJAnalyzerMini_files := $(patsubst src/DisplacedDJ_MiniAOD/DJAnalyzerMini/python/%,%,$(wildcard $(foreach dir,src/DisplacedDJ_MiniAOD/DJAnalyzerMini/python ,$(foreach ext,$(SRC_FILES_SUFFIXES),$(dir)/*.$(ext)))))
PyDisplacedDJ_MiniAODDJAnalyzerMini_LOC_USE := self   
PyDisplacedDJ_MiniAODDJAnalyzerMini_PACKAGE := self/src/DisplacedDJ_MiniAOD/DJAnalyzerMini/python
ALL_PRODS += PyDisplacedDJ_MiniAODDJAnalyzerMini
PyDisplacedDJ_MiniAODDJAnalyzerMini_INIT_FUNC        += $$(eval $$(call PythonProduct,PyDisplacedDJ_MiniAODDJAnalyzerMini,src/DisplacedDJ_MiniAOD/DJAnalyzerMini/python,src_DisplacedDJ_MiniAOD_DJAnalyzerMini_python))
else
$(eval $(call MultipleWarningMsg,PyDisplacedDJ_MiniAODDJAnalyzerMini,src/DisplacedDJ_MiniAOD/DJAnalyzerMini/python))
endif
ALL_COMMONRULES += src_DisplacedDJ_MiniAOD_DJAnalyzerMini_python
src_DisplacedDJ_MiniAOD_DJAnalyzerMini_python_INIT_FUNC += $$(eval $$(call CommonProductRules,src_DisplacedDJ_MiniAOD_DJAnalyzerMini_python,src/DisplacedDJ_MiniAOD/DJAnalyzerMini/python,PYTHON))
ALL_PACKAGES += DisplacedDJ_MiniAOD/DataFormats
subdirs_src_DisplacedDJ_MiniAOD_DataFormats := src_DisplacedDJ_MiniAOD_DataFormats_src
