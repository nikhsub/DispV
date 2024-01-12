// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME tmpdIslc7_amd64_gcc11dIsrcdIDisplacedDJ_MiniAODdIDataFormatsdIsrcdIDisplacedDJ_MiniAODDataFormatsdIadIDisplacedDJ_MiniAODDataFormats_xr
#define R__NO_DEPRECATION

/*******************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define G__DICTIONARY
#include "RConfig.h"
#include "TClass.h"
#include "TDictAttributeMap.h"
#include "TInterpreter.h"
#include "TROOT.h"
#include "TBuffer.h"
#include "TMemberInspector.h"
#include "TInterpreter.h"
#include "TVirtualMutex.h"
#include "TError.h"

#ifndef G__ROOT
#define G__ROOT
#endif

#include "RtypesImp.h"
#include "TIsAProxy.h"
#include "TFileMergeInfo.h"
#include <algorithm>
#include "TCollectionProxyInfo.h"
/*******************************************************************/

#include "TDataMember.h"

// Header files passed as explicit arguments
#include "src/DisplacedDJ_MiniAOD/DataFormats/src/classes.h"

// Header files passed via #pragma extra_include

// The generated code does not explicitly qualify STL entities
namespace std {} using namespace std;

namespace ROOT {
   static TClass *edmcLcLWrapperlEvectorlEvectorlEintgRsPgRsPgR_Dictionary();
   static void edmcLcLWrapperlEvectorlEvectorlEintgRsPgRsPgR_TClassManip(TClass*);
   static void *new_edmcLcLWrapperlEvectorlEvectorlEintgRsPgRsPgR(void *p = nullptr);
   static void *newArray_edmcLcLWrapperlEvectorlEvectorlEintgRsPgRsPgR(Long_t size, void *p);
   static void delete_edmcLcLWrapperlEvectorlEvectorlEintgRsPgRsPgR(void *p);
   static void deleteArray_edmcLcLWrapperlEvectorlEvectorlEintgRsPgRsPgR(void *p);
   static void destruct_edmcLcLWrapperlEvectorlEvectorlEintgRsPgRsPgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::edm::Wrapper<vector<vector<int> > >*)
   {
      ::edm::Wrapper<vector<vector<int> > > *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::edm::Wrapper<vector<vector<int> > >));
      static ::ROOT::TGenericClassInfo 
         instance("edm::Wrapper<vector<vector<int> > >", ::edm::Wrapper<vector<vector<int> > >::Class_Version(), "DataFormats/Common/interface/Wrapper.h", 24,
                  typeid(::edm::Wrapper<vector<vector<int> > >), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &edmcLcLWrapperlEvectorlEvectorlEintgRsPgRsPgR_Dictionary, isa_proxy, 4,
                  sizeof(::edm::Wrapper<vector<vector<int> > >) );
      instance.SetNew(&new_edmcLcLWrapperlEvectorlEvectorlEintgRsPgRsPgR);
      instance.SetNewArray(&newArray_edmcLcLWrapperlEvectorlEvectorlEintgRsPgRsPgR);
      instance.SetDelete(&delete_edmcLcLWrapperlEvectorlEvectorlEintgRsPgRsPgR);
      instance.SetDeleteArray(&deleteArray_edmcLcLWrapperlEvectorlEvectorlEintgRsPgRsPgR);
      instance.SetDestructor(&destruct_edmcLcLWrapperlEvectorlEvectorlEintgRsPgRsPgR);

      ::ROOT::AddClassAlternate("edm::Wrapper<vector<vector<int> > >","edm::Wrapper<std::vector<std::vector<int> > >");

      ::ROOT::AddClassAlternate("edm::Wrapper<vector<vector<int> > >","edm::Wrapper<std::vector<std::vector<int, std::allocator<int> >, std::allocator<std::vector<int, std::allocator<int> > > > >");
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::edm::Wrapper<vector<vector<int> > >*)
   {
      return GenerateInitInstanceLocal((::edm::Wrapper<vector<vector<int> > >*)nullptr);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::edm::Wrapper<vector<vector<int> > >*)nullptr); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *edmcLcLWrapperlEvectorlEvectorlEintgRsPgRsPgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::edm::Wrapper<vector<vector<int> > >*)nullptr)->GetClass();
      edmcLcLWrapperlEvectorlEvectorlEintgRsPgRsPgR_TClassManip(theClass);
   return theClass;
   }

   static void edmcLcLWrapperlEvectorlEvectorlEintgRsPgRsPgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *edmcLcLWrapperlEvectorlEvectorlEboolgRsPgRsPgR_Dictionary();
   static void edmcLcLWrapperlEvectorlEvectorlEboolgRsPgRsPgR_TClassManip(TClass*);
   static void *new_edmcLcLWrapperlEvectorlEvectorlEboolgRsPgRsPgR(void *p = nullptr);
   static void *newArray_edmcLcLWrapperlEvectorlEvectorlEboolgRsPgRsPgR(Long_t size, void *p);
   static void delete_edmcLcLWrapperlEvectorlEvectorlEboolgRsPgRsPgR(void *p);
   static void deleteArray_edmcLcLWrapperlEvectorlEvectorlEboolgRsPgRsPgR(void *p);
   static void destruct_edmcLcLWrapperlEvectorlEvectorlEboolgRsPgRsPgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::edm::Wrapper<vector<vector<bool> > >*)
   {
      ::edm::Wrapper<vector<vector<bool> > > *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::edm::Wrapper<vector<vector<bool> > >));
      static ::ROOT::TGenericClassInfo 
         instance("edm::Wrapper<vector<vector<bool> > >", ::edm::Wrapper<vector<vector<bool> > >::Class_Version(), "DataFormats/Common/interface/Wrapper.h", 24,
                  typeid(::edm::Wrapper<vector<vector<bool> > >), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &edmcLcLWrapperlEvectorlEvectorlEboolgRsPgRsPgR_Dictionary, isa_proxy, 4,
                  sizeof(::edm::Wrapper<vector<vector<bool> > >) );
      instance.SetNew(&new_edmcLcLWrapperlEvectorlEvectorlEboolgRsPgRsPgR);
      instance.SetNewArray(&newArray_edmcLcLWrapperlEvectorlEvectorlEboolgRsPgRsPgR);
      instance.SetDelete(&delete_edmcLcLWrapperlEvectorlEvectorlEboolgRsPgRsPgR);
      instance.SetDeleteArray(&deleteArray_edmcLcLWrapperlEvectorlEvectorlEboolgRsPgRsPgR);
      instance.SetDestructor(&destruct_edmcLcLWrapperlEvectorlEvectorlEboolgRsPgRsPgR);

      ::ROOT::AddClassAlternate("edm::Wrapper<vector<vector<bool> > >","edm::Wrapper<std::vector<std::vector<bool> > >");

      ::ROOT::AddClassAlternate("edm::Wrapper<vector<vector<bool> > >","edm::Wrapper<std::vector<std::vector<bool, std::allocator<bool> >, std::allocator<std::vector<bool, std::allocator<bool> > > > >");
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::edm::Wrapper<vector<vector<bool> > >*)
   {
      return GenerateInitInstanceLocal((::edm::Wrapper<vector<vector<bool> > >*)nullptr);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::edm::Wrapper<vector<vector<bool> > >*)nullptr); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *edmcLcLWrapperlEvectorlEvectorlEboolgRsPgRsPgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::edm::Wrapper<vector<vector<bool> > >*)nullptr)->GetClass();
      edmcLcLWrapperlEvectorlEvectorlEboolgRsPgRsPgR_TClassManip(theClass);
   return theClass;
   }

   static void edmcLcLWrapperlEvectorlEvectorlEboolgRsPgRsPgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *edmcLcLWrapperlEvectorlEvectorlEfloatgRsPgRsPgR_Dictionary();
   static void edmcLcLWrapperlEvectorlEvectorlEfloatgRsPgRsPgR_TClassManip(TClass*);
   static void *new_edmcLcLWrapperlEvectorlEvectorlEfloatgRsPgRsPgR(void *p = nullptr);
   static void *newArray_edmcLcLWrapperlEvectorlEvectorlEfloatgRsPgRsPgR(Long_t size, void *p);
   static void delete_edmcLcLWrapperlEvectorlEvectorlEfloatgRsPgRsPgR(void *p);
   static void deleteArray_edmcLcLWrapperlEvectorlEvectorlEfloatgRsPgRsPgR(void *p);
   static void destruct_edmcLcLWrapperlEvectorlEvectorlEfloatgRsPgRsPgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::edm::Wrapper<vector<vector<float> > >*)
   {
      ::edm::Wrapper<vector<vector<float> > > *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::edm::Wrapper<vector<vector<float> > >));
      static ::ROOT::TGenericClassInfo 
         instance("edm::Wrapper<vector<vector<float> > >", ::edm::Wrapper<vector<vector<float> > >::Class_Version(), "DataFormats/Common/interface/Wrapper.h", 24,
                  typeid(::edm::Wrapper<vector<vector<float> > >), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &edmcLcLWrapperlEvectorlEvectorlEfloatgRsPgRsPgR_Dictionary, isa_proxy, 4,
                  sizeof(::edm::Wrapper<vector<vector<float> > >) );
      instance.SetNew(&new_edmcLcLWrapperlEvectorlEvectorlEfloatgRsPgRsPgR);
      instance.SetNewArray(&newArray_edmcLcLWrapperlEvectorlEvectorlEfloatgRsPgRsPgR);
      instance.SetDelete(&delete_edmcLcLWrapperlEvectorlEvectorlEfloatgRsPgRsPgR);
      instance.SetDeleteArray(&deleteArray_edmcLcLWrapperlEvectorlEvectorlEfloatgRsPgRsPgR);
      instance.SetDestructor(&destruct_edmcLcLWrapperlEvectorlEvectorlEfloatgRsPgRsPgR);

      ::ROOT::AddClassAlternate("edm::Wrapper<vector<vector<float> > >","edm::Wrapper<std::vector<std::vector<float> > >");

      ::ROOT::AddClassAlternate("edm::Wrapper<vector<vector<float> > >","edm::Wrapper<std::vector<std::vector<float, std::allocator<float> >, std::allocator<std::vector<float, std::allocator<float> > > > >");
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::edm::Wrapper<vector<vector<float> > >*)
   {
      return GenerateInitInstanceLocal((::edm::Wrapper<vector<vector<float> > >*)nullptr);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::edm::Wrapper<vector<vector<float> > >*)nullptr); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *edmcLcLWrapperlEvectorlEvectorlEfloatgRsPgRsPgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::edm::Wrapper<vector<vector<float> > >*)nullptr)->GetClass();
      edmcLcLWrapperlEvectorlEvectorlEfloatgRsPgRsPgR_TClassManip(theClass);
   return theClass;
   }

   static void edmcLcLWrapperlEvectorlEvectorlEfloatgRsPgRsPgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *edmcLcLWrapperlEvectorlEvectorlEvectorlEfloatgRsPgRsPgRsPgR_Dictionary();
   static void edmcLcLWrapperlEvectorlEvectorlEvectorlEfloatgRsPgRsPgRsPgR_TClassManip(TClass*);
   static void *new_edmcLcLWrapperlEvectorlEvectorlEvectorlEfloatgRsPgRsPgRsPgR(void *p = nullptr);
   static void *newArray_edmcLcLWrapperlEvectorlEvectorlEvectorlEfloatgRsPgRsPgRsPgR(Long_t size, void *p);
   static void delete_edmcLcLWrapperlEvectorlEvectorlEvectorlEfloatgRsPgRsPgRsPgR(void *p);
   static void deleteArray_edmcLcLWrapperlEvectorlEvectorlEvectorlEfloatgRsPgRsPgRsPgR(void *p);
   static void destruct_edmcLcLWrapperlEvectorlEvectorlEvectorlEfloatgRsPgRsPgRsPgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::edm::Wrapper<vector<vector<vector<float> > > >*)
   {
      ::edm::Wrapper<vector<vector<vector<float> > > > *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::edm::Wrapper<vector<vector<vector<float> > > >));
      static ::ROOT::TGenericClassInfo 
         instance("edm::Wrapper<vector<vector<vector<float> > > >", ::edm::Wrapper<vector<vector<vector<float> > > >::Class_Version(), "DataFormats/Common/interface/Wrapper.h", 24,
                  typeid(::edm::Wrapper<vector<vector<vector<float> > > >), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &edmcLcLWrapperlEvectorlEvectorlEvectorlEfloatgRsPgRsPgRsPgR_Dictionary, isa_proxy, 4,
                  sizeof(::edm::Wrapper<vector<vector<vector<float> > > >) );
      instance.SetNew(&new_edmcLcLWrapperlEvectorlEvectorlEvectorlEfloatgRsPgRsPgRsPgR);
      instance.SetNewArray(&newArray_edmcLcLWrapperlEvectorlEvectorlEvectorlEfloatgRsPgRsPgRsPgR);
      instance.SetDelete(&delete_edmcLcLWrapperlEvectorlEvectorlEvectorlEfloatgRsPgRsPgRsPgR);
      instance.SetDeleteArray(&deleteArray_edmcLcLWrapperlEvectorlEvectorlEvectorlEfloatgRsPgRsPgRsPgR);
      instance.SetDestructor(&destruct_edmcLcLWrapperlEvectorlEvectorlEvectorlEfloatgRsPgRsPgRsPgR);

      ::ROOT::AddClassAlternate("edm::Wrapper<vector<vector<vector<float> > > >","edm::Wrapper<std::vector<std::vector<std::vector<float> > > >");

      ::ROOT::AddClassAlternate("edm::Wrapper<vector<vector<vector<float> > > >","edm::Wrapper<std::vector<std::vector<std::vector<float, std::allocator<float> >, std::allocator<std::vector<float, std::allocator<float> > > >, std::allocator<std::vector<std::vector<float, std::allocator<float> >, std::allocator<std::vector<float, std::allocator<float> > > > > > >");
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::edm::Wrapper<vector<vector<vector<float> > > >*)
   {
      return GenerateInitInstanceLocal((::edm::Wrapper<vector<vector<vector<float> > > >*)nullptr);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::edm::Wrapper<vector<vector<vector<float> > > >*)nullptr); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *edmcLcLWrapperlEvectorlEvectorlEvectorlEfloatgRsPgRsPgRsPgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::edm::Wrapper<vector<vector<vector<float> > > >*)nullptr)->GetClass();
      edmcLcLWrapperlEvectorlEvectorlEvectorlEfloatgRsPgRsPgRsPgR_TClassManip(theClass);
   return theClass;
   }

   static void edmcLcLWrapperlEvectorlEvectorlEvectorlEfloatgRsPgRsPgRsPgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *edmcLcLWrapperlEvectorlEvectorlEROOTcLcLMathcLcLLorentzVectorlEROOTcLcLMathcLcLPxPyPzE4DlEfloatgRsPgRsPgRsPgRsPgR_Dictionary();
   static void edmcLcLWrapperlEvectorlEvectorlEROOTcLcLMathcLcLLorentzVectorlEROOTcLcLMathcLcLPxPyPzE4DlEfloatgRsPgRsPgRsPgRsPgR_TClassManip(TClass*);
   static void *new_edmcLcLWrapperlEvectorlEvectorlEROOTcLcLMathcLcLLorentzVectorlEROOTcLcLMathcLcLPxPyPzE4DlEfloatgRsPgRsPgRsPgRsPgR(void *p = nullptr);
   static void *newArray_edmcLcLWrapperlEvectorlEvectorlEROOTcLcLMathcLcLLorentzVectorlEROOTcLcLMathcLcLPxPyPzE4DlEfloatgRsPgRsPgRsPgRsPgR(Long_t size, void *p);
   static void delete_edmcLcLWrapperlEvectorlEvectorlEROOTcLcLMathcLcLLorentzVectorlEROOTcLcLMathcLcLPxPyPzE4DlEfloatgRsPgRsPgRsPgRsPgR(void *p);
   static void deleteArray_edmcLcLWrapperlEvectorlEvectorlEROOTcLcLMathcLcLLorentzVectorlEROOTcLcLMathcLcLPxPyPzE4DlEfloatgRsPgRsPgRsPgRsPgR(void *p);
   static void destruct_edmcLcLWrapperlEvectorlEvectorlEROOTcLcLMathcLcLLorentzVectorlEROOTcLcLMathcLcLPxPyPzE4DlEfloatgRsPgRsPgRsPgRsPgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::edm::Wrapper<vector<vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > > >*)
   {
      ::edm::Wrapper<vector<vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > > > *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::edm::Wrapper<vector<vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > > >));
      static ::ROOT::TGenericClassInfo 
         instance("edm::Wrapper<vector<vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > > >", ::edm::Wrapper<vector<vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > > >::Class_Version(), "DataFormats/Common/interface/Wrapper.h", 24,
                  typeid(::edm::Wrapper<vector<vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > > >), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &edmcLcLWrapperlEvectorlEvectorlEROOTcLcLMathcLcLLorentzVectorlEROOTcLcLMathcLcLPxPyPzE4DlEfloatgRsPgRsPgRsPgRsPgR_Dictionary, isa_proxy, 4,
                  sizeof(::edm::Wrapper<vector<vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > > >) );
      instance.SetNew(&new_edmcLcLWrapperlEvectorlEvectorlEROOTcLcLMathcLcLLorentzVectorlEROOTcLcLMathcLcLPxPyPzE4DlEfloatgRsPgRsPgRsPgRsPgR);
      instance.SetNewArray(&newArray_edmcLcLWrapperlEvectorlEvectorlEROOTcLcLMathcLcLLorentzVectorlEROOTcLcLMathcLcLPxPyPzE4DlEfloatgRsPgRsPgRsPgRsPgR);
      instance.SetDelete(&delete_edmcLcLWrapperlEvectorlEvectorlEROOTcLcLMathcLcLLorentzVectorlEROOTcLcLMathcLcLPxPyPzE4DlEfloatgRsPgRsPgRsPgRsPgR);
      instance.SetDeleteArray(&deleteArray_edmcLcLWrapperlEvectorlEvectorlEROOTcLcLMathcLcLLorentzVectorlEROOTcLcLMathcLcLPxPyPzE4DlEfloatgRsPgRsPgRsPgRsPgR);
      instance.SetDestructor(&destruct_edmcLcLWrapperlEvectorlEvectorlEROOTcLcLMathcLcLLorentzVectorlEROOTcLcLMathcLcLPxPyPzE4DlEfloatgRsPgRsPgRsPgRsPgR);

      ::ROOT::AddClassAlternate("edm::Wrapper<vector<vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > > >","edm::Wrapper<std::vector<std::vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > > >");

      ::ROOT::AddClassAlternate("edm::Wrapper<vector<vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > > >","edm::Wrapper<std::vector<std::vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> >, std::allocator<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > >, std::allocator<std::vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> >, std::allocator<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > > > > >");
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::edm::Wrapper<vector<vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > > >*)
   {
      return GenerateInitInstanceLocal((::edm::Wrapper<vector<vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > > >*)nullptr);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::edm::Wrapper<vector<vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > > >*)nullptr); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *edmcLcLWrapperlEvectorlEvectorlEROOTcLcLMathcLcLLorentzVectorlEROOTcLcLMathcLcLPxPyPzE4DlEfloatgRsPgRsPgRsPgRsPgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::edm::Wrapper<vector<vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > > >*)nullptr)->GetClass();
      edmcLcLWrapperlEvectorlEvectorlEROOTcLcLMathcLcLLorentzVectorlEROOTcLcLMathcLcLPxPyPzE4DlEfloatgRsPgRsPgRsPgRsPgR_TClassManip(theClass);
   return theClass;
   }

   static void edmcLcLWrapperlEvectorlEvectorlEROOTcLcLMathcLcLLorentzVectorlEROOTcLcLMathcLcLPxPyPzE4DlEfloatgRsPgRsPgRsPgRsPgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *edmcLcLWrapperlEvectorlEvectorlEvectorlEintgRsPgRsPgRsPgR_Dictionary();
   static void edmcLcLWrapperlEvectorlEvectorlEvectorlEintgRsPgRsPgRsPgR_TClassManip(TClass*);
   static void *new_edmcLcLWrapperlEvectorlEvectorlEvectorlEintgRsPgRsPgRsPgR(void *p = nullptr);
   static void *newArray_edmcLcLWrapperlEvectorlEvectorlEvectorlEintgRsPgRsPgRsPgR(Long_t size, void *p);
   static void delete_edmcLcLWrapperlEvectorlEvectorlEvectorlEintgRsPgRsPgRsPgR(void *p);
   static void deleteArray_edmcLcLWrapperlEvectorlEvectorlEvectorlEintgRsPgRsPgRsPgR(void *p);
   static void destruct_edmcLcLWrapperlEvectorlEvectorlEvectorlEintgRsPgRsPgRsPgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::edm::Wrapper<vector<vector<vector<int> > > >*)
   {
      ::edm::Wrapper<vector<vector<vector<int> > > > *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::edm::Wrapper<vector<vector<vector<int> > > >));
      static ::ROOT::TGenericClassInfo 
         instance("edm::Wrapper<vector<vector<vector<int> > > >", ::edm::Wrapper<vector<vector<vector<int> > > >::Class_Version(), "DataFormats/Common/interface/Wrapper.h", 24,
                  typeid(::edm::Wrapper<vector<vector<vector<int> > > >), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &edmcLcLWrapperlEvectorlEvectorlEvectorlEintgRsPgRsPgRsPgR_Dictionary, isa_proxy, 4,
                  sizeof(::edm::Wrapper<vector<vector<vector<int> > > >) );
      instance.SetNew(&new_edmcLcLWrapperlEvectorlEvectorlEvectorlEintgRsPgRsPgRsPgR);
      instance.SetNewArray(&newArray_edmcLcLWrapperlEvectorlEvectorlEvectorlEintgRsPgRsPgRsPgR);
      instance.SetDelete(&delete_edmcLcLWrapperlEvectorlEvectorlEvectorlEintgRsPgRsPgRsPgR);
      instance.SetDeleteArray(&deleteArray_edmcLcLWrapperlEvectorlEvectorlEvectorlEintgRsPgRsPgRsPgR);
      instance.SetDestructor(&destruct_edmcLcLWrapperlEvectorlEvectorlEvectorlEintgRsPgRsPgRsPgR);

      ::ROOT::AddClassAlternate("edm::Wrapper<vector<vector<vector<int> > > >","edm::Wrapper<std::vector<std::vector<std::vector<int> > > >");

      ::ROOT::AddClassAlternate("edm::Wrapper<vector<vector<vector<int> > > >","edm::Wrapper<std::vector<std::vector<std::vector<int, std::allocator<int> >, std::allocator<std::vector<int, std::allocator<int> > > >, std::allocator<std::vector<std::vector<int, std::allocator<int> >, std::allocator<std::vector<int, std::allocator<int> > > > > > >");
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::edm::Wrapper<vector<vector<vector<int> > > >*)
   {
      return GenerateInitInstanceLocal((::edm::Wrapper<vector<vector<vector<int> > > >*)nullptr);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::edm::Wrapper<vector<vector<vector<int> > > >*)nullptr); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *edmcLcLWrapperlEvectorlEvectorlEvectorlEintgRsPgRsPgRsPgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::edm::Wrapper<vector<vector<vector<int> > > >*)nullptr)->GetClass();
      edmcLcLWrapperlEvectorlEvectorlEvectorlEintgRsPgRsPgRsPgR_TClassManip(theClass);
   return theClass;
   }

   static void edmcLcLWrapperlEvectorlEvectorlEvectorlEintgRsPgRsPgRsPgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_edmcLcLWrapperlEvectorlEvectorlEintgRsPgRsPgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::edm::Wrapper<vector<vector<int> > > : new ::edm::Wrapper<vector<vector<int> > >;
   }
   static void *newArray_edmcLcLWrapperlEvectorlEvectorlEintgRsPgRsPgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::edm::Wrapper<vector<vector<int> > >[nElements] : new ::edm::Wrapper<vector<vector<int> > >[nElements];
   }
   // Wrapper around operator delete
   static void delete_edmcLcLWrapperlEvectorlEvectorlEintgRsPgRsPgR(void *p) {
      delete ((::edm::Wrapper<vector<vector<int> > >*)p);
   }
   static void deleteArray_edmcLcLWrapperlEvectorlEvectorlEintgRsPgRsPgR(void *p) {
      delete [] ((::edm::Wrapper<vector<vector<int> > >*)p);
   }
   static void destruct_edmcLcLWrapperlEvectorlEvectorlEintgRsPgRsPgR(void *p) {
      typedef ::edm::Wrapper<vector<vector<int> > > current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::edm::Wrapper<vector<vector<int> > >

namespace ROOT {
   // Wrappers around operator new
   static void *new_edmcLcLWrapperlEvectorlEvectorlEboolgRsPgRsPgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::edm::Wrapper<vector<vector<bool> > > : new ::edm::Wrapper<vector<vector<bool> > >;
   }
   static void *newArray_edmcLcLWrapperlEvectorlEvectorlEboolgRsPgRsPgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::edm::Wrapper<vector<vector<bool> > >[nElements] : new ::edm::Wrapper<vector<vector<bool> > >[nElements];
   }
   // Wrapper around operator delete
   static void delete_edmcLcLWrapperlEvectorlEvectorlEboolgRsPgRsPgR(void *p) {
      delete ((::edm::Wrapper<vector<vector<bool> > >*)p);
   }
   static void deleteArray_edmcLcLWrapperlEvectorlEvectorlEboolgRsPgRsPgR(void *p) {
      delete [] ((::edm::Wrapper<vector<vector<bool> > >*)p);
   }
   static void destruct_edmcLcLWrapperlEvectorlEvectorlEboolgRsPgRsPgR(void *p) {
      typedef ::edm::Wrapper<vector<vector<bool> > > current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::edm::Wrapper<vector<vector<bool> > >

namespace ROOT {
   // Wrappers around operator new
   static void *new_edmcLcLWrapperlEvectorlEvectorlEfloatgRsPgRsPgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::edm::Wrapper<vector<vector<float> > > : new ::edm::Wrapper<vector<vector<float> > >;
   }
   static void *newArray_edmcLcLWrapperlEvectorlEvectorlEfloatgRsPgRsPgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::edm::Wrapper<vector<vector<float> > >[nElements] : new ::edm::Wrapper<vector<vector<float> > >[nElements];
   }
   // Wrapper around operator delete
   static void delete_edmcLcLWrapperlEvectorlEvectorlEfloatgRsPgRsPgR(void *p) {
      delete ((::edm::Wrapper<vector<vector<float> > >*)p);
   }
   static void deleteArray_edmcLcLWrapperlEvectorlEvectorlEfloatgRsPgRsPgR(void *p) {
      delete [] ((::edm::Wrapper<vector<vector<float> > >*)p);
   }
   static void destruct_edmcLcLWrapperlEvectorlEvectorlEfloatgRsPgRsPgR(void *p) {
      typedef ::edm::Wrapper<vector<vector<float> > > current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::edm::Wrapper<vector<vector<float> > >

namespace ROOT {
   // Wrappers around operator new
   static void *new_edmcLcLWrapperlEvectorlEvectorlEvectorlEfloatgRsPgRsPgRsPgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::edm::Wrapper<vector<vector<vector<float> > > > : new ::edm::Wrapper<vector<vector<vector<float> > > >;
   }
   static void *newArray_edmcLcLWrapperlEvectorlEvectorlEvectorlEfloatgRsPgRsPgRsPgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::edm::Wrapper<vector<vector<vector<float> > > >[nElements] : new ::edm::Wrapper<vector<vector<vector<float> > > >[nElements];
   }
   // Wrapper around operator delete
   static void delete_edmcLcLWrapperlEvectorlEvectorlEvectorlEfloatgRsPgRsPgRsPgR(void *p) {
      delete ((::edm::Wrapper<vector<vector<vector<float> > > >*)p);
   }
   static void deleteArray_edmcLcLWrapperlEvectorlEvectorlEvectorlEfloatgRsPgRsPgRsPgR(void *p) {
      delete [] ((::edm::Wrapper<vector<vector<vector<float> > > >*)p);
   }
   static void destruct_edmcLcLWrapperlEvectorlEvectorlEvectorlEfloatgRsPgRsPgRsPgR(void *p) {
      typedef ::edm::Wrapper<vector<vector<vector<float> > > > current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::edm::Wrapper<vector<vector<vector<float> > > >

namespace ROOT {
   // Wrappers around operator new
   static void *new_edmcLcLWrapperlEvectorlEvectorlEROOTcLcLMathcLcLLorentzVectorlEROOTcLcLMathcLcLPxPyPzE4DlEfloatgRsPgRsPgRsPgRsPgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::edm::Wrapper<vector<vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > > > : new ::edm::Wrapper<vector<vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > > >;
   }
   static void *newArray_edmcLcLWrapperlEvectorlEvectorlEROOTcLcLMathcLcLLorentzVectorlEROOTcLcLMathcLcLPxPyPzE4DlEfloatgRsPgRsPgRsPgRsPgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::edm::Wrapper<vector<vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > > >[nElements] : new ::edm::Wrapper<vector<vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > > >[nElements];
   }
   // Wrapper around operator delete
   static void delete_edmcLcLWrapperlEvectorlEvectorlEROOTcLcLMathcLcLLorentzVectorlEROOTcLcLMathcLcLPxPyPzE4DlEfloatgRsPgRsPgRsPgRsPgR(void *p) {
      delete ((::edm::Wrapper<vector<vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > > >*)p);
   }
   static void deleteArray_edmcLcLWrapperlEvectorlEvectorlEROOTcLcLMathcLcLLorentzVectorlEROOTcLcLMathcLcLPxPyPzE4DlEfloatgRsPgRsPgRsPgRsPgR(void *p) {
      delete [] ((::edm::Wrapper<vector<vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > > >*)p);
   }
   static void destruct_edmcLcLWrapperlEvectorlEvectorlEROOTcLcLMathcLcLLorentzVectorlEROOTcLcLMathcLcLPxPyPzE4DlEfloatgRsPgRsPgRsPgRsPgR(void *p) {
      typedef ::edm::Wrapper<vector<vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > > > current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::edm::Wrapper<vector<vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > > >

namespace ROOT {
   // Wrappers around operator new
   static void *new_edmcLcLWrapperlEvectorlEvectorlEvectorlEintgRsPgRsPgRsPgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::edm::Wrapper<vector<vector<vector<int> > > > : new ::edm::Wrapper<vector<vector<vector<int> > > >;
   }
   static void *newArray_edmcLcLWrapperlEvectorlEvectorlEvectorlEintgRsPgRsPgRsPgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::edm::Wrapper<vector<vector<vector<int> > > >[nElements] : new ::edm::Wrapper<vector<vector<vector<int> > > >[nElements];
   }
   // Wrapper around operator delete
   static void delete_edmcLcLWrapperlEvectorlEvectorlEvectorlEintgRsPgRsPgRsPgR(void *p) {
      delete ((::edm::Wrapper<vector<vector<vector<int> > > >*)p);
   }
   static void deleteArray_edmcLcLWrapperlEvectorlEvectorlEvectorlEintgRsPgRsPgRsPgR(void *p) {
      delete [] ((::edm::Wrapper<vector<vector<vector<int> > > >*)p);
   }
   static void destruct_edmcLcLWrapperlEvectorlEvectorlEvectorlEintgRsPgRsPgRsPgR(void *p) {
      typedef ::edm::Wrapper<vector<vector<vector<int> > > > current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::edm::Wrapper<vector<vector<vector<int> > > >

namespace ROOT {
   static TClass *vectorlEvectorlEvectorlEintgRsPgRsPgR_Dictionary();
   static void vectorlEvectorlEvectorlEintgRsPgRsPgR_TClassManip(TClass*);
   static void *new_vectorlEvectorlEvectorlEintgRsPgRsPgR(void *p = nullptr);
   static void *newArray_vectorlEvectorlEvectorlEintgRsPgRsPgR(Long_t size, void *p);
   static void delete_vectorlEvectorlEvectorlEintgRsPgRsPgR(void *p);
   static void deleteArray_vectorlEvectorlEvectorlEintgRsPgRsPgR(void *p);
   static void destruct_vectorlEvectorlEvectorlEintgRsPgRsPgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<vector<vector<int> > >*)
   {
      vector<vector<vector<int> > > *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<vector<vector<int> > >));
      static ::ROOT::TGenericClassInfo 
         instance("vector<vector<vector<int> > >", -2, "vector", 389,
                  typeid(vector<vector<vector<int> > >), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEvectorlEvectorlEintgRsPgRsPgR_Dictionary, isa_proxy, 4,
                  sizeof(vector<vector<vector<int> > >) );
      instance.SetNew(&new_vectorlEvectorlEvectorlEintgRsPgRsPgR);
      instance.SetNewArray(&newArray_vectorlEvectorlEvectorlEintgRsPgRsPgR);
      instance.SetDelete(&delete_vectorlEvectorlEvectorlEintgRsPgRsPgR);
      instance.SetDeleteArray(&deleteArray_vectorlEvectorlEvectorlEintgRsPgRsPgR);
      instance.SetDestructor(&destruct_vectorlEvectorlEvectorlEintgRsPgRsPgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<vector<vector<int> > > >()));

      ::ROOT::AddClassAlternate("vector<vector<vector<int> > >","std::vector<std::vector<std::vector<int, std::allocator<int> >, std::allocator<std::vector<int, std::allocator<int> > > >, std::allocator<std::vector<std::vector<int, std::allocator<int> >, std::allocator<std::vector<int, std::allocator<int> > > > > >");
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<vector<vector<int> > >*)nullptr); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEvectorlEvectorlEintgRsPgRsPgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<vector<vector<int> > >*)nullptr)->GetClass();
      vectorlEvectorlEvectorlEintgRsPgRsPgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEvectorlEvectorlEintgRsPgRsPgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEvectorlEvectorlEintgRsPgRsPgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<vector<vector<int> > > : new vector<vector<vector<int> > >;
   }
   static void *newArray_vectorlEvectorlEvectorlEintgRsPgRsPgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<vector<vector<int> > >[nElements] : new vector<vector<vector<int> > >[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEvectorlEvectorlEintgRsPgRsPgR(void *p) {
      delete ((vector<vector<vector<int> > >*)p);
   }
   static void deleteArray_vectorlEvectorlEvectorlEintgRsPgRsPgR(void *p) {
      delete [] ((vector<vector<vector<int> > >*)p);
   }
   static void destruct_vectorlEvectorlEvectorlEintgRsPgRsPgR(void *p) {
      typedef vector<vector<vector<int> > > current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<vector<vector<int> > >

namespace ROOT {
   static TClass *vectorlEvectorlEvectorlEfloatgRsPgRsPgR_Dictionary();
   static void vectorlEvectorlEvectorlEfloatgRsPgRsPgR_TClassManip(TClass*);
   static void *new_vectorlEvectorlEvectorlEfloatgRsPgRsPgR(void *p = nullptr);
   static void *newArray_vectorlEvectorlEvectorlEfloatgRsPgRsPgR(Long_t size, void *p);
   static void delete_vectorlEvectorlEvectorlEfloatgRsPgRsPgR(void *p);
   static void deleteArray_vectorlEvectorlEvectorlEfloatgRsPgRsPgR(void *p);
   static void destruct_vectorlEvectorlEvectorlEfloatgRsPgRsPgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<vector<vector<float> > >*)
   {
      vector<vector<vector<float> > > *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<vector<vector<float> > >));
      static ::ROOT::TGenericClassInfo 
         instance("vector<vector<vector<float> > >", -2, "vector", 389,
                  typeid(vector<vector<vector<float> > >), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEvectorlEvectorlEfloatgRsPgRsPgR_Dictionary, isa_proxy, 4,
                  sizeof(vector<vector<vector<float> > >) );
      instance.SetNew(&new_vectorlEvectorlEvectorlEfloatgRsPgRsPgR);
      instance.SetNewArray(&newArray_vectorlEvectorlEvectorlEfloatgRsPgRsPgR);
      instance.SetDelete(&delete_vectorlEvectorlEvectorlEfloatgRsPgRsPgR);
      instance.SetDeleteArray(&deleteArray_vectorlEvectorlEvectorlEfloatgRsPgRsPgR);
      instance.SetDestructor(&destruct_vectorlEvectorlEvectorlEfloatgRsPgRsPgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<vector<vector<float> > > >()));

      ::ROOT::AddClassAlternate("vector<vector<vector<float> > >","std::vector<std::vector<std::vector<float, std::allocator<float> >, std::allocator<std::vector<float, std::allocator<float> > > >, std::allocator<std::vector<std::vector<float, std::allocator<float> >, std::allocator<std::vector<float, std::allocator<float> > > > > >");
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<vector<vector<float> > >*)nullptr); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEvectorlEvectorlEfloatgRsPgRsPgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<vector<vector<float> > >*)nullptr)->GetClass();
      vectorlEvectorlEvectorlEfloatgRsPgRsPgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEvectorlEvectorlEfloatgRsPgRsPgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEvectorlEvectorlEfloatgRsPgRsPgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<vector<vector<float> > > : new vector<vector<vector<float> > >;
   }
   static void *newArray_vectorlEvectorlEvectorlEfloatgRsPgRsPgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<vector<vector<float> > >[nElements] : new vector<vector<vector<float> > >[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEvectorlEvectorlEfloatgRsPgRsPgR(void *p) {
      delete ((vector<vector<vector<float> > >*)p);
   }
   static void deleteArray_vectorlEvectorlEvectorlEfloatgRsPgRsPgR(void *p) {
      delete [] ((vector<vector<vector<float> > >*)p);
   }
   static void destruct_vectorlEvectorlEvectorlEfloatgRsPgRsPgR(void *p) {
      typedef vector<vector<vector<float> > > current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<vector<vector<float> > >

namespace ROOT {
   static TClass *vectorlEvectorlEintgRsPgR_Dictionary();
   static void vectorlEvectorlEintgRsPgR_TClassManip(TClass*);
   static void *new_vectorlEvectorlEintgRsPgR(void *p = nullptr);
   static void *newArray_vectorlEvectorlEintgRsPgR(Long_t size, void *p);
   static void delete_vectorlEvectorlEintgRsPgR(void *p);
   static void deleteArray_vectorlEvectorlEintgRsPgR(void *p);
   static void destruct_vectorlEvectorlEintgRsPgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<vector<int> >*)
   {
      vector<vector<int> > *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<vector<int> >));
      static ::ROOT::TGenericClassInfo 
         instance("vector<vector<int> >", -2, "vector", 389,
                  typeid(vector<vector<int> >), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEvectorlEintgRsPgR_Dictionary, isa_proxy, 4,
                  sizeof(vector<vector<int> >) );
      instance.SetNew(&new_vectorlEvectorlEintgRsPgR);
      instance.SetNewArray(&newArray_vectorlEvectorlEintgRsPgR);
      instance.SetDelete(&delete_vectorlEvectorlEintgRsPgR);
      instance.SetDeleteArray(&deleteArray_vectorlEvectorlEintgRsPgR);
      instance.SetDestructor(&destruct_vectorlEvectorlEintgRsPgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<vector<int> > >()));

      ::ROOT::AddClassAlternate("vector<vector<int> >","std::vector<std::vector<int, std::allocator<int> >, std::allocator<std::vector<int, std::allocator<int> > > >");
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<vector<int> >*)nullptr); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEvectorlEintgRsPgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<vector<int> >*)nullptr)->GetClass();
      vectorlEvectorlEintgRsPgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEvectorlEintgRsPgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEvectorlEintgRsPgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<vector<int> > : new vector<vector<int> >;
   }
   static void *newArray_vectorlEvectorlEintgRsPgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<vector<int> >[nElements] : new vector<vector<int> >[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEvectorlEintgRsPgR(void *p) {
      delete ((vector<vector<int> >*)p);
   }
   static void deleteArray_vectorlEvectorlEintgRsPgR(void *p) {
      delete [] ((vector<vector<int> >*)p);
   }
   static void destruct_vectorlEvectorlEintgRsPgR(void *p) {
      typedef vector<vector<int> > current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<vector<int> >

namespace ROOT {
   static TClass *vectorlEvectorlEfloatgRsPgR_Dictionary();
   static void vectorlEvectorlEfloatgRsPgR_TClassManip(TClass*);
   static void *new_vectorlEvectorlEfloatgRsPgR(void *p = nullptr);
   static void *newArray_vectorlEvectorlEfloatgRsPgR(Long_t size, void *p);
   static void delete_vectorlEvectorlEfloatgRsPgR(void *p);
   static void deleteArray_vectorlEvectorlEfloatgRsPgR(void *p);
   static void destruct_vectorlEvectorlEfloatgRsPgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<vector<float> >*)
   {
      vector<vector<float> > *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<vector<float> >));
      static ::ROOT::TGenericClassInfo 
         instance("vector<vector<float> >", -2, "vector", 389,
                  typeid(vector<vector<float> >), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEvectorlEfloatgRsPgR_Dictionary, isa_proxy, 4,
                  sizeof(vector<vector<float> >) );
      instance.SetNew(&new_vectorlEvectorlEfloatgRsPgR);
      instance.SetNewArray(&newArray_vectorlEvectorlEfloatgRsPgR);
      instance.SetDelete(&delete_vectorlEvectorlEfloatgRsPgR);
      instance.SetDeleteArray(&deleteArray_vectorlEvectorlEfloatgRsPgR);
      instance.SetDestructor(&destruct_vectorlEvectorlEfloatgRsPgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<vector<float> > >()));

      ::ROOT::AddClassAlternate("vector<vector<float> >","std::vector<std::vector<float, std::allocator<float> >, std::allocator<std::vector<float, std::allocator<float> > > >");
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<vector<float> >*)nullptr); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEvectorlEfloatgRsPgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<vector<float> >*)nullptr)->GetClass();
      vectorlEvectorlEfloatgRsPgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEvectorlEfloatgRsPgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEvectorlEfloatgRsPgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<vector<float> > : new vector<vector<float> >;
   }
   static void *newArray_vectorlEvectorlEfloatgRsPgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<vector<float> >[nElements] : new vector<vector<float> >[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEvectorlEfloatgRsPgR(void *p) {
      delete ((vector<vector<float> >*)p);
   }
   static void deleteArray_vectorlEvectorlEfloatgRsPgR(void *p) {
      delete [] ((vector<vector<float> >*)p);
   }
   static void destruct_vectorlEvectorlEfloatgRsPgR(void *p) {
      typedef vector<vector<float> > current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<vector<float> >

namespace ROOT {
   static TClass *vectorlEvectorlEboolgRsPgR_Dictionary();
   static void vectorlEvectorlEboolgRsPgR_TClassManip(TClass*);
   static void *new_vectorlEvectorlEboolgRsPgR(void *p = nullptr);
   static void *newArray_vectorlEvectorlEboolgRsPgR(Long_t size, void *p);
   static void delete_vectorlEvectorlEboolgRsPgR(void *p);
   static void deleteArray_vectorlEvectorlEboolgRsPgR(void *p);
   static void destruct_vectorlEvectorlEboolgRsPgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<vector<bool> >*)
   {
      vector<vector<bool> > *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<vector<bool> >));
      static ::ROOT::TGenericClassInfo 
         instance("vector<vector<bool> >", -2, "vector", 389,
                  typeid(vector<vector<bool> >), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEvectorlEboolgRsPgR_Dictionary, isa_proxy, 4,
                  sizeof(vector<vector<bool> >) );
      instance.SetNew(&new_vectorlEvectorlEboolgRsPgR);
      instance.SetNewArray(&newArray_vectorlEvectorlEboolgRsPgR);
      instance.SetDelete(&delete_vectorlEvectorlEboolgRsPgR);
      instance.SetDeleteArray(&deleteArray_vectorlEvectorlEboolgRsPgR);
      instance.SetDestructor(&destruct_vectorlEvectorlEboolgRsPgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<vector<bool> > >()));

      ::ROOT::AddClassAlternate("vector<vector<bool> >","std::vector<std::vector<bool, std::allocator<bool> >, std::allocator<std::vector<bool, std::allocator<bool> > > >");
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<vector<bool> >*)nullptr); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEvectorlEboolgRsPgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<vector<bool> >*)nullptr)->GetClass();
      vectorlEvectorlEboolgRsPgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEvectorlEboolgRsPgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEvectorlEboolgRsPgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<vector<bool> > : new vector<vector<bool> >;
   }
   static void *newArray_vectorlEvectorlEboolgRsPgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<vector<bool> >[nElements] : new vector<vector<bool> >[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEvectorlEboolgRsPgR(void *p) {
      delete ((vector<vector<bool> >*)p);
   }
   static void deleteArray_vectorlEvectorlEboolgRsPgR(void *p) {
      delete [] ((vector<vector<bool> >*)p);
   }
   static void destruct_vectorlEvectorlEboolgRsPgR(void *p) {
      typedef vector<vector<bool> > current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<vector<bool> >

namespace ROOT {
   static TClass *vectorlEvectorlEROOTcLcLMathcLcLLorentzVectorlEROOTcLcLMathcLcLPxPyPzE4DlEfloatgRsPgRsPgRsPgR_Dictionary();
   static void vectorlEvectorlEROOTcLcLMathcLcLLorentzVectorlEROOTcLcLMathcLcLPxPyPzE4DlEfloatgRsPgRsPgRsPgR_TClassManip(TClass*);
   static void *new_vectorlEvectorlEROOTcLcLMathcLcLLorentzVectorlEROOTcLcLMathcLcLPxPyPzE4DlEfloatgRsPgRsPgRsPgR(void *p = nullptr);
   static void *newArray_vectorlEvectorlEROOTcLcLMathcLcLLorentzVectorlEROOTcLcLMathcLcLPxPyPzE4DlEfloatgRsPgRsPgRsPgR(Long_t size, void *p);
   static void delete_vectorlEvectorlEROOTcLcLMathcLcLLorentzVectorlEROOTcLcLMathcLcLPxPyPzE4DlEfloatgRsPgRsPgRsPgR(void *p);
   static void deleteArray_vectorlEvectorlEROOTcLcLMathcLcLLorentzVectorlEROOTcLcLMathcLcLPxPyPzE4DlEfloatgRsPgRsPgRsPgR(void *p);
   static void destruct_vectorlEvectorlEROOTcLcLMathcLcLLorentzVectorlEROOTcLcLMathcLcLPxPyPzE4DlEfloatgRsPgRsPgRsPgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > >*)
   {
      vector<vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > > *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > >));
      static ::ROOT::TGenericClassInfo 
         instance("vector<vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > >", -2, "vector", 389,
                  typeid(vector<vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > >), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEvectorlEROOTcLcLMathcLcLLorentzVectorlEROOTcLcLMathcLcLPxPyPzE4DlEfloatgRsPgRsPgRsPgR_Dictionary, isa_proxy, 4,
                  sizeof(vector<vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > >) );
      instance.SetNew(&new_vectorlEvectorlEROOTcLcLMathcLcLLorentzVectorlEROOTcLcLMathcLcLPxPyPzE4DlEfloatgRsPgRsPgRsPgR);
      instance.SetNewArray(&newArray_vectorlEvectorlEROOTcLcLMathcLcLLorentzVectorlEROOTcLcLMathcLcLPxPyPzE4DlEfloatgRsPgRsPgRsPgR);
      instance.SetDelete(&delete_vectorlEvectorlEROOTcLcLMathcLcLLorentzVectorlEROOTcLcLMathcLcLPxPyPzE4DlEfloatgRsPgRsPgRsPgR);
      instance.SetDeleteArray(&deleteArray_vectorlEvectorlEROOTcLcLMathcLcLLorentzVectorlEROOTcLcLMathcLcLPxPyPzE4DlEfloatgRsPgRsPgRsPgR);
      instance.SetDestructor(&destruct_vectorlEvectorlEROOTcLcLMathcLcLLorentzVectorlEROOTcLcLMathcLcLPxPyPzE4DlEfloatgRsPgRsPgRsPgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > > >()));

      ::ROOT::AddClassAlternate("vector<vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > >","std::vector<std::vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> >, std::allocator<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > >, std::allocator<std::vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> >, std::allocator<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > > > >");
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > >*)nullptr); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEvectorlEROOTcLcLMathcLcLLorentzVectorlEROOTcLcLMathcLcLPxPyPzE4DlEfloatgRsPgRsPgRsPgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > >*)nullptr)->GetClass();
      vectorlEvectorlEROOTcLcLMathcLcLLorentzVectorlEROOTcLcLMathcLcLPxPyPzE4DlEfloatgRsPgRsPgRsPgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEvectorlEROOTcLcLMathcLcLLorentzVectorlEROOTcLcLMathcLcLPxPyPzE4DlEfloatgRsPgRsPgRsPgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEvectorlEROOTcLcLMathcLcLLorentzVectorlEROOTcLcLMathcLcLPxPyPzE4DlEfloatgRsPgRsPgRsPgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > > : new vector<vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > >;
   }
   static void *newArray_vectorlEvectorlEROOTcLcLMathcLcLLorentzVectorlEROOTcLcLMathcLcLPxPyPzE4DlEfloatgRsPgRsPgRsPgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > >[nElements] : new vector<vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > >[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEvectorlEROOTcLcLMathcLcLLorentzVectorlEROOTcLcLMathcLcLPxPyPzE4DlEfloatgRsPgRsPgRsPgR(void *p) {
      delete ((vector<vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > >*)p);
   }
   static void deleteArray_vectorlEvectorlEROOTcLcLMathcLcLLorentzVectorlEROOTcLcLMathcLcLPxPyPzE4DlEfloatgRsPgRsPgRsPgR(void *p) {
      delete [] ((vector<vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > >*)p);
   }
   static void destruct_vectorlEvectorlEROOTcLcLMathcLcLLorentzVectorlEROOTcLcLMathcLcLPxPyPzE4DlEfloatgRsPgRsPgRsPgR(void *p) {
      typedef vector<vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > > current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > >

namespace ROOT {
   static TClass *vectorlEintgR_Dictionary();
   static void vectorlEintgR_TClassManip(TClass*);
   static void *new_vectorlEintgR(void *p = nullptr);
   static void *newArray_vectorlEintgR(Long_t size, void *p);
   static void delete_vectorlEintgR(void *p);
   static void deleteArray_vectorlEintgR(void *p);
   static void destruct_vectorlEintgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<int>*)
   {
      vector<int> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<int>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<int>", -2, "vector", 389,
                  typeid(vector<int>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEintgR_Dictionary, isa_proxy, 4,
                  sizeof(vector<int>) );
      instance.SetNew(&new_vectorlEintgR);
      instance.SetNewArray(&newArray_vectorlEintgR);
      instance.SetDelete(&delete_vectorlEintgR);
      instance.SetDeleteArray(&deleteArray_vectorlEintgR);
      instance.SetDestructor(&destruct_vectorlEintgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<int> >()));

      ::ROOT::AddClassAlternate("vector<int>","std::vector<int, std::allocator<int> >");
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<int>*)nullptr); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEintgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<int>*)nullptr)->GetClass();
      vectorlEintgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEintgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEintgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<int> : new vector<int>;
   }
   static void *newArray_vectorlEintgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<int>[nElements] : new vector<int>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEintgR(void *p) {
      delete ((vector<int>*)p);
   }
   static void deleteArray_vectorlEintgR(void *p) {
      delete [] ((vector<int>*)p);
   }
   static void destruct_vectorlEintgR(void *p) {
      typedef vector<int> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<int>

namespace ROOT {
   static TClass *vectorlEfloatgR_Dictionary();
   static void vectorlEfloatgR_TClassManip(TClass*);
   static void *new_vectorlEfloatgR(void *p = nullptr);
   static void *newArray_vectorlEfloatgR(Long_t size, void *p);
   static void delete_vectorlEfloatgR(void *p);
   static void deleteArray_vectorlEfloatgR(void *p);
   static void destruct_vectorlEfloatgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<float>*)
   {
      vector<float> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<float>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<float>", -2, "vector", 389,
                  typeid(vector<float>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEfloatgR_Dictionary, isa_proxy, 4,
                  sizeof(vector<float>) );
      instance.SetNew(&new_vectorlEfloatgR);
      instance.SetNewArray(&newArray_vectorlEfloatgR);
      instance.SetDelete(&delete_vectorlEfloatgR);
      instance.SetDeleteArray(&deleteArray_vectorlEfloatgR);
      instance.SetDestructor(&destruct_vectorlEfloatgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<float> >()));

      ::ROOT::AddClassAlternate("vector<float>","std::vector<float, std::allocator<float> >");
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<float>*)nullptr); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEfloatgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<float>*)nullptr)->GetClass();
      vectorlEfloatgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEfloatgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEfloatgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<float> : new vector<float>;
   }
   static void *newArray_vectorlEfloatgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<float>[nElements] : new vector<float>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEfloatgR(void *p) {
      delete ((vector<float>*)p);
   }
   static void deleteArray_vectorlEfloatgR(void *p) {
      delete [] ((vector<float>*)p);
   }
   static void destruct_vectorlEfloatgR(void *p) {
      typedef vector<float> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<float>

namespace ROOT {
   static TClass *vectorlEboolgR_Dictionary();
   static void vectorlEboolgR_TClassManip(TClass*);
   static void *new_vectorlEboolgR(void *p = nullptr);
   static void *newArray_vectorlEboolgR(Long_t size, void *p);
   static void delete_vectorlEboolgR(void *p);
   static void deleteArray_vectorlEboolgR(void *p);
   static void destruct_vectorlEboolgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<bool>*)
   {
      vector<bool> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<bool>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<bool>", -2, "vector", 596,
                  typeid(vector<bool>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEboolgR_Dictionary, isa_proxy, 4,
                  sizeof(vector<bool>) );
      instance.SetNew(&new_vectorlEboolgR);
      instance.SetNewArray(&newArray_vectorlEboolgR);
      instance.SetDelete(&delete_vectorlEboolgR);
      instance.SetDeleteArray(&deleteArray_vectorlEboolgR);
      instance.SetDestructor(&destruct_vectorlEboolgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<bool> >()));

      ::ROOT::AddClassAlternate("vector<bool>","std::vector<bool, std::allocator<bool> >");
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<bool>*)nullptr); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEboolgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<bool>*)nullptr)->GetClass();
      vectorlEboolgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEboolgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEboolgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<bool> : new vector<bool>;
   }
   static void *newArray_vectorlEboolgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<bool>[nElements] : new vector<bool>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEboolgR(void *p) {
      delete ((vector<bool>*)p);
   }
   static void deleteArray_vectorlEboolgR(void *p) {
      delete [] ((vector<bool>*)p);
   }
   static void destruct_vectorlEboolgR(void *p) {
      typedef vector<bool> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<bool>

namespace ROOT {
   static TClass *vectorlEROOTcLcLMathcLcLLorentzVectorlEROOTcLcLMathcLcLPxPyPzE4DlEfloatgRsPgRsPgR_Dictionary();
   static void vectorlEROOTcLcLMathcLcLLorentzVectorlEROOTcLcLMathcLcLPxPyPzE4DlEfloatgRsPgRsPgR_TClassManip(TClass*);
   static void *new_vectorlEROOTcLcLMathcLcLLorentzVectorlEROOTcLcLMathcLcLPxPyPzE4DlEfloatgRsPgRsPgR(void *p = nullptr);
   static void *newArray_vectorlEROOTcLcLMathcLcLLorentzVectorlEROOTcLcLMathcLcLPxPyPzE4DlEfloatgRsPgRsPgR(Long_t size, void *p);
   static void delete_vectorlEROOTcLcLMathcLcLLorentzVectorlEROOTcLcLMathcLcLPxPyPzE4DlEfloatgRsPgRsPgR(void *p);
   static void deleteArray_vectorlEROOTcLcLMathcLcLLorentzVectorlEROOTcLcLMathcLcLPxPyPzE4DlEfloatgRsPgRsPgR(void *p);
   static void destruct_vectorlEROOTcLcLMathcLcLLorentzVectorlEROOTcLcLMathcLcLPxPyPzE4DlEfloatgRsPgRsPgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > >*)
   {
      vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > >));
      static ::ROOT::TGenericClassInfo 
         instance("vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > >", -2, "vector", 389,
                  typeid(vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > >), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEROOTcLcLMathcLcLLorentzVectorlEROOTcLcLMathcLcLPxPyPzE4DlEfloatgRsPgRsPgR_Dictionary, isa_proxy, 4,
                  sizeof(vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > >) );
      instance.SetNew(&new_vectorlEROOTcLcLMathcLcLLorentzVectorlEROOTcLcLMathcLcLPxPyPzE4DlEfloatgRsPgRsPgR);
      instance.SetNewArray(&newArray_vectorlEROOTcLcLMathcLcLLorentzVectorlEROOTcLcLMathcLcLPxPyPzE4DlEfloatgRsPgRsPgR);
      instance.SetDelete(&delete_vectorlEROOTcLcLMathcLcLLorentzVectorlEROOTcLcLMathcLcLPxPyPzE4DlEfloatgRsPgRsPgR);
      instance.SetDeleteArray(&deleteArray_vectorlEROOTcLcLMathcLcLLorentzVectorlEROOTcLcLMathcLcLPxPyPzE4DlEfloatgRsPgRsPgR);
      instance.SetDestructor(&destruct_vectorlEROOTcLcLMathcLcLLorentzVectorlEROOTcLcLMathcLcLPxPyPzE4DlEfloatgRsPgRsPgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > >()));

      ::ROOT::AddClassAlternate("vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > >","std::vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> >, std::allocator<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > >");
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > >*)nullptr); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEROOTcLcLMathcLcLLorentzVectorlEROOTcLcLMathcLcLPxPyPzE4DlEfloatgRsPgRsPgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > >*)nullptr)->GetClass();
      vectorlEROOTcLcLMathcLcLLorentzVectorlEROOTcLcLMathcLcLPxPyPzE4DlEfloatgRsPgRsPgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEROOTcLcLMathcLcLLorentzVectorlEROOTcLcLMathcLcLPxPyPzE4DlEfloatgRsPgRsPgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEROOTcLcLMathcLcLLorentzVectorlEROOTcLcLMathcLcLPxPyPzE4DlEfloatgRsPgRsPgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > : new vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > >;
   }
   static void *newArray_vectorlEROOTcLcLMathcLcLLorentzVectorlEROOTcLcLMathcLcLPxPyPzE4DlEfloatgRsPgRsPgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > >[nElements] : new vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > >[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEROOTcLcLMathcLcLLorentzVectorlEROOTcLcLMathcLcLPxPyPzE4DlEfloatgRsPgRsPgR(void *p) {
      delete ((vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > >*)p);
   }
   static void deleteArray_vectorlEROOTcLcLMathcLcLLorentzVectorlEROOTcLcLMathcLcLPxPyPzE4DlEfloatgRsPgRsPgR(void *p) {
      delete [] ((vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > >*)p);
   }
   static void destruct_vectorlEROOTcLcLMathcLcLLorentzVectorlEROOTcLcLMathcLcLPxPyPzE4DlEfloatgRsPgRsPgR(void *p) {
      typedef vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > >

namespace {
  void TriggerDictionaryInitialization_DisplacedDJ_MiniAODDataFormats_xr_Impl() {
    static const char* headers[] = {
"0",
nullptr
    };
    static const char* includePaths[] = {
"/uscms_data/d3/nvenkata/DisplacedJets_New/CMSSW_13_0_13/src",
"/cvmfs/cms.cern.ch/slc7_amd64_gcc11/cms/cmssw/CMSSW_13_0_13/src",
"/cvmfs/cms.cern.ch/slc7_amd64_gcc11/external/pcre/8.43-5dcc901acc02f624b22dd9840b2357e8/include",
"/cvmfs/cms.cern.ch/slc7_amd64_gcc11/external/bz2lib/1.0.6-2c1f18484cb66c30aba7929f2be5e7d4/include",
"/cvmfs/cms.cern.ch/slc7_amd64_gcc11/external/gsl/2.6-fcf47bcbedd800ca8386c7e2920fa474/include",
"/cvmfs/cms.cern.ch/slc7_amd64_gcc11/external/libuuid/2.34-0451b31e1b9a58c6aeefab41c18eea34/include",
"/cvmfs/cms.cern.ch/slc7_amd64_gcc11/external/xz/5.2.5-83d0a00b575efd1701e07bedf7977343/include",
"/cvmfs/cms.cern.ch/slc7_amd64_gcc11/external/zlib/1.2.11-3dfb2715f3608466b74431b80eb9d788/include",
"/cvmfs/cms.cern.ch/slc7_amd64_gcc11/external/eigen/82dd3710dac619448f50331c1d6a35da673f764a-b0dc243d10365424e66e60c822ab818e/include/eigen3",
"/cvmfs/cms.cern.ch/slc7_amd64_gcc11/external/fmt/8.0.1-557ae4739f3cbc76e428d57162bae99b/include",
"/cvmfs/cms.cern.ch/slc7_amd64_gcc11/external/md5/1.0.0-e68283f2de2e2e709a0db99db3b53205/include",
"/cvmfs/cms.cern.ch/slc7_amd64_gcc11/external/OpenBLAS/0.3.15-26c67b8b638762cfd2e2bcfc936e3ec7/include",
"/cvmfs/cms.cern.ch/slc7_amd64_gcc11/external/tinyxml2/6.2.0-20b4f0dfd078828bfb8e7fdd5ba85221/include",
"/cvmfs/cms.cern.ch/slc7_amd64_gcc11/lcg/root/6.26.11-fec5b250e1cd56b91a094709de26e5b8/include/",
"/uscms_data/d3/nvenkata/DisplacedJets_New/CMSSW_13_0_13/",
nullptr
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "DisplacedDJ_MiniAODDataFormats_xr dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_AutoLoading_Map;
namespace std{template <typename _Tp> class __attribute__((annotate("$clingAutoload$bits/allocator.h")))  __attribute__((annotate("$clingAutoload$string")))  allocator;
}
namespace ROOT{namespace Math{template <class ScalarType = double> class __attribute__((annotate("$clingAutoload$Math/GenVector/PxPyPzE4D.h")))  __attribute__((annotate("$clingAutoload$Math/Vector4D.h")))  PxPyPzE4D;
}}
namespace ROOT{namespace Math{template <class CoordSystem> class __attribute__((annotate("$clingAutoload$Math/Vector4Dfwd.h")))  __attribute__((annotate("$clingAutoload$Math/Vector4D.h")))  LorentzVector;
}}
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "DisplacedDJ_MiniAODDataFormats_xr dictionary payload"

#ifndef CMS_DICT_IMPL
  #define CMS_DICT_IMPL 1
#endif
#ifndef _REENTRANT
  #define _REENTRANT 1
#endif
#ifndef GNUSOURCE
  #define GNUSOURCE 1
#endif
#ifndef __STRICT_ANSI__
  #define __STRICT_ANSI__ 1
#endif
#ifndef GNU_GCC
  #define GNU_GCC 1
#endif
#ifndef _GNU_SOURCE
  #define _GNU_SOURCE 1
#endif
#ifndef EIGEN_DONT_PARALLELIZE
  #define EIGEN_DONT_PARALLELIZE 1
#endif
#ifndef TBB_USE_GLIBCXX_VERSION
  #define TBB_USE_GLIBCXX_VERSION 110201
#endif
#ifndef TBB_SUPPRESS_DEPRECATED_MESSAGES
  #define TBB_SUPPRESS_DEPRECATED_MESSAGES 1
#endif
#ifndef TBB_PREVIEW_RESUMABLE_TASKS
  #define TBB_PREVIEW_RESUMABLE_TASKS 1
#endif
#ifndef TBB_PREVIEW_TASK_GROUP_EXTENSIONS
  #define TBB_PREVIEW_TASK_GROUP_EXTENSIONS 1
#endif
#ifndef BOOST_SPIRIT_THREADSAFE
  #define BOOST_SPIRIT_THREADSAFE 1
#endif
#ifndef PHOENIX_THREADSAFE
  #define PHOENIX_THREADSAFE 1
#endif
#ifndef BOOST_MATH_DISABLE_STD_FPCLASSIFY
  #define BOOST_MATH_DISABLE_STD_FPCLASSIFY 1
#endif
#ifndef BOOST_UUID_RANDOM_PROVIDER_FORCE_POSIX
  #define BOOST_UUID_RANDOM_PROVIDER_FORCE_POSIX 1
#endif
#ifndef CMSSW_GIT_HASH
  #define CMSSW_GIT_HASH "CMSSW_13_0_13"
#endif
#ifndef PROJECT_NAME
  #define PROJECT_NAME "CMSSW"
#endif
#ifndef PROJECT_VERSION
  #define PROJECT_VERSION "CMSSW_13_0_13"
#endif
#ifndef CMSSW_REFLEX_DICT
  #define CMSSW_REFLEX_DICT 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
// Inline headers
#ifndef DJ_CLASSES_H
#define DJ_CLASSES_H

#include "DataFormats/Common/interface/Wrapper.h"
#include "math.h"
#include "Math/Vector4D.h"
#include <vector>


namespace {

    struct dictionary {
    
        std::vector<std::vector<int> > dummy0;
        edm::Wrapper<std::vector<std::vector<int> > > dummy1;

	std::vector<std::vector<bool> > dammy0;
        edm::Wrapper<std::vector<std::vector<bool> > > dammy1;
     
        std::vector<std::vector<float> > dummi0; 
        edm::Wrapper<std::vector<std::vector<float> > > dummi1;
 
        std::vector<std::vector<std::vector<float> > > dumme0;
        edm::Wrapper<std::vector<std::vector<std::vector<float> > > > dumme1;

        ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > dumma0;
        std::vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > dumma1;
        std::vector<std::vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > >  dumma2;
        edm::Wrapper<std::vector<std::vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > > >  dumma3;

         
   
    };

}

#endif

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[] = {
"edm::Wrapper<std::vector<std::vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > > >", payloadCode, "@",
"edm::Wrapper<std::vector<std::vector<bool> > >", payloadCode, "@",
"edm::Wrapper<std::vector<std::vector<float> > >", payloadCode, "@",
"edm::Wrapper<std::vector<std::vector<int> > >", payloadCode, "@",
"edm::Wrapper<std::vector<std::vector<std::vector<float> > > >", payloadCode, "@",
"edm::Wrapper<std::vector<std::vector<std::vector<int> > > >", payloadCode, "@",
"edm::Wrapper<vector<vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > > >", payloadCode, "@",
"edm::Wrapper<vector<vector<bool> > >", payloadCode, "@",
"edm::Wrapper<vector<vector<float> > >", payloadCode, "@",
"edm::Wrapper<vector<vector<int> > >", payloadCode, "@",
"edm::Wrapper<vector<vector<vector<float> > > >", payloadCode, "@",
"edm::Wrapper<vector<vector<vector<int> > > >", payloadCode, "@",
nullptr
};
    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("DisplacedDJ_MiniAODDataFormats_xr",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_DisplacedDJ_MiniAODDataFormats_xr_Impl, {}, classesHeaders, /*hasCxxModule*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_DisplacedDJ_MiniAODDataFormats_xr_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_DisplacedDJ_MiniAODDataFormats_xr() {
  TriggerDictionaryInitialization_DisplacedDJ_MiniAODDataFormats_xr_Impl();
}
