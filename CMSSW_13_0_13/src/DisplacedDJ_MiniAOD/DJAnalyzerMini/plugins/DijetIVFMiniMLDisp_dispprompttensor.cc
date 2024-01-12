// -*- C++ -*-
//
// Package:    DisplacedDJ_MiniAOD/DijetIVFMiniMLDisp_dispprompttensor
// Class:      DijetIVFMiniMLDisp_dispprompttensor
// 
/**\class DijetIVFMiniMLDisp_dispprompttensor DijetIVFMiniMLDisp_dispprompttensor.cc DisplacedDJ_MiniAOD/DijetIVFMiniMLDisp_dispprompttensor/plugins/DijetIVFMiniMLDisp_dispprompttensor.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Jingyu Luo
//         Created:  Mon, 22 Jan 2022 18:46:48 GMT
//
//


// system include files
#include <memory>

#include "DataFormats/Common/interface/AssociationVector.h"

// user include files
//#include "FWCore/Framework/interface/Frameworkfwd.h"
//#include "FWCore/Framework/interface/one/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DisplacedDJ_MiniAOD/DJAnalyzerMini/interface/DijetIVFMiniMLDisp_dispprompttensor.h"

#include "PhysicsTools/TensorFlow/interface/TensorFlow.h"

#include <numeric>
#include <algorithm>


using namespace std;

template <typename T> 
vector<size_t> inversesort_indexes(const vector<T> &v){

    vector<size_t> idx(v.size());
    iota(idx.begin(), idx.end(), 0);

    stable_sort(idx.begin(), idx.end(), [&v](size_t i1, size_t i2) {return v[i1] > v[i2];});
  
    return idx;
}



namespace LHAPDF {
      void initPDFSet(int nset, const std::string& filename, int member=0);
      int numberPDF(int nset);
      void usePDFMember(int nset, int member);
      double xfx(int nset, double x, double Q, int fl);
      double getXmin(int nset, int member);
      double getXmax(int nset, int member);
      double getQ2min(int nset, int member);
      double getQ2max(int nset, int member);
      void extrapolate(bool extrapolate=true);
}

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
DijetIVFMiniMLDisp_dispprompttensor::DijetIVFMiniMLDisp_dispprompttensor(const edm::ParameterSet& iConfig)
:

  theTTBToken(esConsumes(edm::ESInputTag("", "TransientTrackBuilder"))),
  genLumiHeaderToken_(consumes<GenLumiInfoHeader,edm::InLumi>(edm::InputTag("generator"))),
  
  TrackCollT_ (consumes<pat::PackedCandidateCollection>(iConfig.getUntrackedParameter<edm::InputTag>("tracks"))),
  LostTrackCollT_ (consumes<pat::PackedCandidateCollection>(iConfig.getUntrackedParameter<edm::InputTag>("losttracks"))),
  jet_collT_ (consumes<edm::View<reco::Jet> >(iConfig.getUntrackedParameter<edm::InputTag>("jets"))),
  calojet_collT_(consumes<edm::View<reco::CaloJet> >(iConfig.getUntrackedParameter<edm::InputTag>("calojets"))),
  PVCollT_ (consumes<reco::VertexCollection>(iConfig.getUntrackedParameter<edm::InputTag>("primaryVertices"))),
  genEvtInfoT_ (consumes<GenEventInfoProduct>(iConfig.getUntrackedParameter<edm::InputTag>("generator"))),
  genCollT_ (consumes<edm::View<reco::GenParticle>>(iConfig.getUntrackedParameter<edm::InputTag>("genParticles"))),
  PupInfoT_ (consumes<std::vector<PileupSummaryInfo>>(iConfig.getUntrackedParameter<edm::InputTag>("addPileupInfo"))),
  jetCorrT_ (consumes<reco::JetCorrector>(iConfig.getUntrackedParameter<edm::InputTag>("jetCorr"))),
  vtxconfig_(iConfig.getUntrackedParameter<edm::ParameterSet>("vertexfitter")),
  vtxmaker_(vtxconfig_),
  //JetPtCut_ (iConfig.getUntrackedParameter<double>("JetPtCut")),
  TrackPtCut_(iConfig.getUntrackedParameter<double>("TrackPtCut")),
  vtxweight_(iConfig.getUntrackedParameter<double>("vtxweight")),
  firstEvent_ (true),
  trigresultsToken_ (consumes<edm::TriggerResults>(iConfig.getParameter<edm::InputTag>("trigResults"))),
  //assocCALOToken_ (consumes<reco::JetTracksAssociationCollection>(iConfig.getUntrackedParameter<edm::InputTag>("associatorCALO"))),
  //assocVTXToken_ (consumes<reco::JetTracksAssociationCollection>(iConfig.getUntrackedParameter<edm::InputTag>("associatorVTX"))),
  //JTACALO_ (iConfig.getUntrackedParameter<bool>("JTACALO")),
  //JTAVTX_ (iConfig.getUntrackedParameter<bool>("JTAVTX")),
  //JTACombine_ (iConfig.getUntrackedParameter<bool>("JTACombine")),
  runtrigger_ (iConfig.getUntrackedParameter<bool>("runtrigger")),
  isMC_ (iConfig.getUntrackedParameter<bool>("isMC")),
  getgeninfo_ (iConfig.getUntrackedParameter<bool>("getgeninfo")),
  //checkHitOpt_ (iConfig.getUntrackedParameter<bool>("checkHitOpt")),
  pdfReweight_ (iConfig.getUntrackedParameter<bool>("pdfReweight")),
  JECTag_ (iConfig.getUntrackedParameter<std::string>("JECTag")),
  theJECToken (esConsumes(edm::ESInputTag("", JECTag_))),
  clusterizer(new TracksClusteringFromDisplacedSeed(iConfig.getParameter<edm::ParameterSet>("clusterizer"))),
  _DispgraphDef(tensorflow::loadGraphDef(iConfig.getParameter<edm::FileInPath>("dispgraph_path").fullPath())),
  _PromptgraphDef(tensorflow::loadGraphDef(iConfig.getParameter<edm::FileInPath>("promptgraph_path").fullPath())),
  _Dispsession(nullptr),
  _Promptsession(nullptr)
  //first_merging(new VertexMerging(iConfig.getParameter<edm::ParameterSet>("firstmerging"))) 

{

   //now do what ever initialization is needed
   edm::Service<TFileService> fs;
   //usesResource("TFileService");
   tree = fs->make<TTree>("tree", "tree");
   //LHAPDF::initPDFSet(0, "CT14lo.LHgrid");
   //LHAPDF::initPDFSet(1, "MMHT2014lo68cl.LHgrid");
   //LHAPDF::initPDFSet(2, "NNPDF30_lo_as_0118.LHgrid");
   tensorflow::setLogging("3");
   _Dispsession = tensorflow::createSession(_DispgraphDef);
   _Promptsession = tensorflow::createSession(_PromptgraphDef);

}


DijetIVFMiniMLDisp_dispprompttensor::~DijetIVFMiniMLDisp_dispprompttensor()
{

   if (_Dispsession != nullptr) {
          tensorflow::closeSession(_Dispsession);
          _Dispsession = nullptr;
      }
      delete _DispgraphDef;
      _DispgraphDef = nullptr;
 
   if (_Promptsession != nullptr) {
          tensorflow::closeSession(_Promptsession);
          _Promptsession = nullptr;
      }
      delete _PromptgraphDef;
      _PromptgraphDef = nullptr;
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
DijetIVFMiniMLDisp_dispprompttensor::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;
   using namespace pat;
   
   run_ = iEvent.id().run();
   lumi_ = iEvent.luminosityBlock();
   evt_ = iEvent.id().event();

   nPU=0;
   nPV=0; 
 
   CT14Weight0=0;
   MMHT2014Weight0=0;
   NNPDF30Weight0=0;

   CT14Weight.clear();
   MMHT2014Weight.clear();
   NNPDF30Weight.clear();

   genSVx.clear();
   genSVy.clear();
   genSVz.clear();
   genSVlxy.clear();
   genSVlxyz.clear();
   genSVctau0.clear();

   genpdgID.clear();
   genpt.clear();
   geneta.clear();
   genphi.clear();  
   genenergy.clear(); 

   genmompdgID.clear();
   genmompt.clear();
   genmometa.clear();
   genmomphi.clear();
   genmomenergy.clear();  
   //momvx.clear();
   //momvy.clear();   
   //momvz.clear();
   //momEta.clear();
   //momPhi.clear();
   //momPt.clear();
   //momBeta.clear();
   //momGamma.clear();
   //momEnergy.clear();
   //mompdgID.clear();
   //momCtau0.clear();


   //genLxy.clear();
   //genLxyz.clear();
   //genParticlePt.clear();


  
   CaloHT=0;
   CaloHTup=0;
   CaloHTdown=0;

   jetassociatedntrks_CALO.clear();
   jetassociatedntrks_VTX.clear();
   jetassociatedntrks_combine.clear();

   jetcorrfac.clear();
   jetpt.clear();
   jetenergy.clear();
   jeteta.clear();
   jetphi.clear();
   jetPtUp.clear();
   jetPtDown.clear(); 
  

   dijetIndices.clear();
   dijetIP2D.clear();
   dijetIP2D_sig.clear();
   dijetPreIndices.clear();
   dijetPreIP2D.clear();
   dijetPreIP2D_sig.clear();


   dijethasSV.clear();
   dijetpts.clear();
   dijetenergys.clear();
   dijetetas.clear();
   dijetphis.clear(); 
 
   dijetLxyexp.clear();

   fullIndices.clear();
   fullenergys.clear();
   fullpts.clear();
   fullIP2D.clear();
   fullIP2Dsig.clear();
   fullIP3D.clear();
   fullIP3Dsig.clear();
   fullIP3Dminsig.clear();
   fullPVindex.clear();
 
   dijetIP3D.clear();
   dijetIP3D_sig.clear();
   dijetIP3D_minsig.clear();
   dijetPVindex.clear();
   dijetdRjet1.clear();
   dijetdRjet2.clear();
   dijet_assSV.clear();
   dijet_ip3dwrtSV.clear();
   dijet_ip3dsigwrtSV.clear();
   dijet_ip3dwrtSVtanh.clear();
   dijet_ip3dsigwrtSVtanh.clear();
   dijet_costhetawrtSV.clear();

   promptIndices.clear();
   promptIP2D.clear();
   promptIP2D_sig.clear();
   promptIP3D.clear();
   promptIP3D_sig.clear();
   promptpts.clear();
   promptenergys.clear();
   promptIP3Dminsig.clear();
   promptPVidx.clear();
   promptdRjet1.clear();
   promptdRjet2.clear();
   
   SVdijetPhyP4.clear();
   SVdijetPhyPt.clear();
   SVPtFrac.clear();
   SVdphiDJVX.clear();
   SVdphiLxyVX.clear();

   TrueDijet.clear();
   jet1pdgID.clear();
   jet2pdgID.clear();
   jet1mompdgID.clear();
   jet2mompdgID.clear();
   jet1genpt.clear();
   jet1geneta.clear();
   jet1genphi.clear();
   jet1genenergy.clear();
   jet2genpt.clear();
   jet2geneta.clear();
   jet2genphi.clear();
   jet2genenergy.clear();
   dijetgenSVx1.clear();
   dijetgenSVy1.clear();
   dijetgenSVz1.clear();
   dijetgenSVlxy1.clear();
   dijetgenSVlxyz1.clear();
   dijetgenSVctau01.clear();

   dijetgenSVx2.clear();
   dijetgenSVy2.clear();
   dijetgenSVz2.clear();
   dijetgenSVlxy2.clear();
   dijetgenSVlxyz2.clear();
   dijetgenSVctau02.clear();
  


   SVjet1Idx.clear();
   SVjet2Idx.clear();
   SVPrejet1Pt.clear(); 
   SVjet1Pt.clear();
   SVjet1PtUp.clear();
   SVjet1PtDown.clear();
   SVjet1Eta.clear();
   SVjet1Phi.clear();
   SVPrejet2Pt.clear();
   SVjet2Pt.clear();  
   SVjet2PtUp.clear();
   SVjet2PtDown.clear();
   SVjet2Eta.clear();
   SVjet2Phi.clear();
   SVnSV.clear();
   SVjetEnergyFrac.clear();
   SVtrksEnergyFrac.clear();

   SVjetEnergyFrac_total.clear();
   SVtrksEnergyFrac_total.clear();

   SVdisptrksEnergyFrac.clear();
   SVtrksPtFrac.clear();
   SVdisptrksPtFrac.clear();   
     
   SVIP2D.clear();
   SVIP2D_sig.clear();
  
   SVIP3D.clear();
   SVIP3D_sig.clear();
   SVIP3D_minsig.clear();
   SVjetidx.clear();
   SVcharges.clear();
   SVtrkenergy.clear(); 

   SVtrkenergysum.clear();
   SVnPrompttk1.clear();
   SVnPrompttk2.clear();
   SVnPromptTracks.clear();

   SVpromptEnergy1.clear();
   SVpromptEnergy2.clear();
   SVpromptEnergy.clear();

   SVpromptEnergyfrac.clear();
   SVpromptEnergyfrac1.clear();
   SVpromptEnergyfrac2.clear();

   SVDNNp.clear();
   SVDNNd.clear();
   jet1trackEnergy.clear();
   jet1trackPt.clear();
   jet2trackEnergy.clear();
   jet2trackPt.clear();
   dijettrackEnergy.clear();
   jet1trackPrompt_EFrac.clear();
   jet2trackPrompt_EFrac.clear();
   dijettrackPrompt_EFrac.clear();

   SVsigpromptEnergyfrac.clear();
   SVsig30promptEnergyfrac.clear();

   SVDijetTag.clear();

   SVvtxx.clear();
   SVvtxy.clear();
   SVvtxz.clear();
   SVvtxlxy.clear();
   SVvtxlxysig.clear();

   SVcosthetaPLxyz.clear();
   SVmeancosthetatrks.clear();

   SVdistwrtgenSV1.clear();
   SVdistwrtgenSV2.clear();
  
   SVdistsigwrtgenSV1.clear();
   SVdistsigwrtgenSV2.clear();
  

   SVdijetdRgenmom1.clear();
   SVdijetdRgenmom2.clear(); 
  
   SVvtxP4.clear();
   SVvtxnTrack.clear();
   SVvtxntrk_jet1.clear();
   SVvtxntrk_jet2.clear();
   SVposnTrack.clear();
   SVenergyfrac_jet1.clear();
   SVenergyfrac_jet2.clear();
   
   SVvtxChi2.clear();
   SVkappa.clear();
   SVdijetdR.clear();
   SVdijetcostheta.clear();
   SVkappa_total.clear();
   SVhitsInFrontOfVert.clear();
   SVmissHitsAfterVert.clear();

   SVdijetbestglxyRMS.clear();
   SVdijetbestglxyAvg.clear();
   SVndijetcluster.clear();
   SVdijetbestN.clear();
   SVdijetbestN1.clear();
   SVdijetbestN2.clear();

   SVtoSVdist.clear();
   SVtoSVdistsig.clear();
   SVtoSVdisttanh.clear();
   SVtoSVdistsigtanh.clear();
   SVtoSVjet1dR.clear();
   SVtoSVjet2dR.clear();
   SVtoSVjet1costheta.clear();
   SVtoSVjet2costheta.clear();



   hltjetpt_.clear();
   hltjeteta_.clear();
   hltjetphi_.clear();
   hltjetmass_.clear();

   pass_HLT_IsoMu24_ = false;
   pass_HLT_IsoTkMu24_ = false;
   pass_HLT_HT200_ = false;
   pass_HLT_HT275_ = false;
   pass_HLT_HT325_ = false;
   pass_HLT_HT425_ = false;
   pass_HLT_HT575_ = false;
   pass_HLT_HT650_ = false;
   pass_HLT_L1Mu6HT240_ = false;

   pass_HLT_HT400_DisplacedDijet40_Inclusive_ = false;
   pass_HLT_HT430_DisplacedDijet40_DisplacedTrack_ = false;
   pass_HLT_HT430_DisplacedDijet60_DisplacedTrack_ = false;
   pass_HLT_HT500_DisplacedDijet40_Inclusive_ = false;
   pass_HLT_HT550_DisplacedDijet40_Inclusive_ = false;
   pass_HLT_HT650_DisplacedDijet60_Inclusive_ = false;
   pass_HLT_HT650_DisplacedDijet80_Inclusive_ = false;
   pass_HLT_HT750_DisplacedDijet80_Inclusive_ = false;

   pass_HLT_HT430_DisplacedDijet30_Inclusive1PtrkShortSig5_                   = false;  
   pass_HLT_HT430_DisplacedDijet35_Inclusive1PtrkShortSig5_                   = false;
   pass_HLT_HT430_DisplacedDijet40_Inclusive1PtrkShortSig5_                   = false;
   pass_HLT_Mu6HT240_DisplacedDijet30_Inclusive0PtrkShortSig5_                = false;
   pass_HLT_Mu6HT240_DisplacedDijet30_Inclusive1PtrkShortSig5_DisplacedLoose_ = false;
   pass_HLT_Mu6HT240_DisplacedDijet35_Inlcusive0PtrkShortSig5_                = false;
   pass_HLT_Mu6HT240_DisplacedDijet35_Inclusive1PtrkShortSig5_DisplacedLoose_ = false;
   pass_HLT_Mu6HT240_DisplacedDijet40_Inclusive0PtrkShortSig5_                = false;
   pass_HLT_Mu6HT240_DisplacedDijet40_Inclusive1PtrkShortSig5_DisplacedLoose_ = false;
   pass_HLT_HT430_DelayedJet40_DoubleDelay0p5nsTrackless_                     = false;
   pass_HLT_HT430_DelayedJet40_DoubleDelay1nsInclusive_                       = false;
   pass_HLT_HT430_DelayedJet40_SingleDelay1nsTrackless_                       = false;
   pass_HLT_HT430_DelayedJet40_SingleDelay2nsInclusive_                       = false;



  //initialize the tensors for ML
   std::vector<std::string> input_names_{"input_dijet:0", "input_sv:0", "input_trks:0", "input_trktosv:0"};
   
   std::vector<tensorflow::TensorShape> input_sizes{
       //{1, 7, 6}, 
       //{1, 7, 6}, 
       {1, 2}, 
       {1, 6, 11}, 
       {1, 30, 9},
       {1, 180, 4}
   };

   tensorflow::NamedTensorList _input_tensors;
    _input_tensors.resize(input_sizes.size());

    for (unsigned int i = 0; i < input_names_.size(); i++) {
        std::string group_name = input_names_[i];
        tensorflow::Tensor group_tensor(tensorflow::DT_FLOAT, input_sizes[i]);
        _input_tensors[i] = tensorflow::NamedTensor(group_name, group_tensor);
    }


   //for (unsigned int i = 0; i < input_sizes.size(); i++) {
   //     _input_tensors[i].second.flat<float>().setZero();
   // }

   //initialize the prompt track tensor 
   std::vector<std::string> input_prompt_names_{"input_jet1:0", "input_jet2:0", "input_SVDNNd:0"};

   std::vector<tensorflow::TensorShape> input_prompt_sizes{
       {1, 7, 6}, 
       {1, 7, 6}, 
       {1, 1}
   };

   tensorflow::NamedTensorList _input_prompt_tensors;
    _input_prompt_tensors.resize(input_prompt_sizes.size());

    for (unsigned int i = 0; i < input_prompt_names_.size(); i++) {
        std::string group_prompt_name = input_prompt_names_[i];
        tensorflow::Tensor group_prompt_tensor(tensorflow::DT_FLOAT, input_prompt_sizes[i]);
        _input_prompt_tensors[i] = tensorflow::NamedTensor(group_prompt_name, group_prompt_tensor);
    }


   Handle<PackedCandidateCollection> patcan;
   Handle<PackedCandidateCollection> losttracks;
   Handle<edm::View<reco::Jet> > jet_coll;
   Handle<edm::View<reco::CaloJet> > calojet_coll;
   Handle<reco::VertexCollection> pvHandle;

   Handle<edm::View<reco::GenParticle>> genParticles;
   Handle<reco::JetCorrector> jetCorr;
   
   std::vector<reco::Track> alltracks;

   iEvent.getByToken(TrackCollT_, patcan);
   iEvent.getByToken(LostTrackCollT_, losttracks);
   iEvent.getByToken(jet_collT_, jet_coll);
   iEvent.getByToken(calojet_collT_, calojet_coll);
   iEvent.getByToken(PVCollT_, pvHandle);
   iEvent.getByToken(jetCorrT_, jetCorr);

   //edm::ESHandle<TransientTrackBuilder> theB;
   
   //iSetup.get<TransientTrackRecord>().get("TransientTrackBuilder", theB);
   const auto& theB = &iSetup.getData(theTTBToken);

   

   const JetCorrectorParametersCollection &JetCorParColl = iSetup.getData(theJECToken);
   
   JetCorrectorParameters const & JetCorPar = JetCorParColl["Uncertainty"];
   JetCorrectionUncertainty *jetUnc = new JetCorrectionUncertainty(JetCorPar);

   reco::Vertex pv;
   nPV = int((*pvHandle).size());
   
   pv = (*pvHandle)[0];

   if(isMC_){
      iEvent.getByToken(genCollT_, genParticles);
      for (size_t i = 0; i<genParticles->size(); i++){
          reco::GenParticle p = (*genParticles)[i];
          if(p.status() == 23 && fabs(p.mother()->pdgId())==9000006){
              const reco::Candidate *mom = p.mother();
              genpdgID.push_back(p.pdgId());
              geneta.push_back(p.eta());
              genpt.push_back(p.pt());
              genphi.push_back(p.phi());
              genenergy.push_back(p.energy());
              genmompdgID.push_back(mom->pdgId());
              genmompt.push_back(mom->pt());
              genmometa.push_back(mom->eta());
              genmomphi.push_back(mom->phi());
              genmomenergy.push_back(mom->energy());
              genSVx.push_back(p.vx());
              genSVy.push_back(p.vy());
              genSVz.push_back(p.vz());
              
              float Lxy = sqrt((p.vx() - mom->vx())*(p.vx() - mom->vx()) + (p.vy() - mom->vy())*(p.vy() - mom->vy()));
              float Lxyz = sqrt(Lxy*Lxy+(p.vz() - mom->vz())*(p.vz() - mom->vz()));

              float mom_beta = mom->p()/mom->energy();
              float mom_gamma = mom->energy()/mom->mass();
              float mom_ctau0 = Lxyz/(mom_beta*mom_gamma);

              genSVlxy.push_back(Lxy);
              genSVlxyz.push_back(Lxyz);
              genSVctau0.push_back(mom_ctau0);

            
          }
      }
   }

   if(runtrigger_){
       edm::Handle<edm::TriggerResults> trigresults;
       iEvent.getByToken(trigresultsToken_, trigresults);
       const edm::TriggerNames& names = iEvent.triggerNames(*trigresults);

       for(size_t itrig = 0; itrig < names.size(); itrig++){
          TString trigname = names.triggerName(itrig);
          pass_HLT_IsoMu24_                                     = pass_HLT_IsoMu24_||(trigname.Contains("HLT_IsoMu24_v") && trigresults->accept(itrig));
          pass_HLT_IsoTkMu24_                                   = pass_HLT_IsoTkMu24_||(trigname.Contains("HLT_IsoTkMu24_v") && trigresults->accept(itrig));
          pass_HLT_HT200_                                       = pass_HLT_HT200_||(trigname.Contains("HLT_HT200_v") && trigresults->accept(itrig));             
          pass_HLT_HT275_                                       = pass_HLT_HT275_||(trigname.Contains("HLT_HT275_v") && trigresults->accept(itrig));             
          pass_HLT_HT325_                                       = pass_HLT_HT325_||(trigname.Contains("HLT_HT325_v") && trigresults->accept(itrig));             
          pass_HLT_HT425_                                       = pass_HLT_HT425_||(trigname.Contains("HLT_HT425_v") && trigresults->accept(itrig));             
          pass_HLT_HT575_                                       = pass_HLT_HT575_||(trigname.Contains("HLT_HT575_v") && trigresults->accept(itrig));             
          pass_HLT_HT650_                                       = pass_HLT_HT650_||(trigname.Contains("HLT_HT650_v") && trigresults->accept(itrig)); 
          pass_HLT_L1Mu6HT240_                                  = pass_HLT_L1Mu6HT240_||(trigname.Contains("HLT_L1Mu6HT240_v") && trigresults->accept(itrig));
     
          pass_HLT_HT400_DisplacedDijet40_Inclusive_            = pass_HLT_HT400_DisplacedDijet40_Inclusive_||(trigname.Contains("HLT_HT400_DisplacedDijet40_Inclusive_v") && trigresults->accept(itrig));                           
          pass_HLT_HT430_DisplacedDijet40_DisplacedTrack_       = pass_HLT_HT430_DisplacedDijet40_DisplacedTrack_ || (trigname.Contains("HLT_HT430_DisplacedDijet40_DisplacedTrack_v") && trigresults->accept(itrig));
          pass_HLT_HT430_DisplacedDijet60_DisplacedTrack_       = pass_HLT_HT430_DisplacedDijet60_DisplacedTrack_ || (trigname.Contains("HLT_HT430_DisplacedDijet60_DisplacedTrack_v") && trigresults->accept(itrig));
 
          pass_HLT_HT500_DisplacedDijet40_Inclusive_            = pass_HLT_HT500_DisplacedDijet40_Inclusive_||(trigname.Contains("HLT_HT500_DisplacedDijet40_Inclusive_v") && trigresults->accept(itrig));                      
          pass_HLT_HT550_DisplacedDijet40_Inclusive_            = pass_HLT_HT550_DisplacedDijet40_Inclusive_||(trigname.Contains("HLT_HT550_DisplacedDijet40_Inclusive_v") && trigresults->accept(itrig));                      
          pass_HLT_HT650_DisplacedDijet60_Inclusive_            = pass_HLT_HT650_DisplacedDijet60_Inclusive_||(trigname.Contains("HLT_HT650_DisplacedDijet60_Inclusive_v") && trigresults->accept(itrig));
 
          pass_HLT_HT650_DisplacedDijet80_Inclusive_            = pass_HLT_HT650_DisplacedDijet80_Inclusive_||(trigname.Contains("HLT_HT650_DisplacedDijet80_Inclusive_v") && trigresults->accept(itrig));                        
          pass_HLT_HT750_DisplacedDijet80_Inclusive_            = pass_HLT_HT750_DisplacedDijet80_Inclusive_||(trigname.Contains("HLT_HT750_DisplacedDijet80_Inclusive_v") && trigresults->accept(itrig));                                                   
    
          pass_HLT_HT430_DisplacedDijet30_Inclusive1PtrkShortSig5_                      = pass_HLT_HT430_DisplacedDijet30_Inclusive1PtrkShortSig5_                     ||(trigname.Contains("HLT_HT430_DisplacedDijet30_Inclusive1PtrkShortSig5_") && trigresults->accept(itrig));                      
          pass_HLT_HT430_DisplacedDijet35_Inclusive1PtrkShortSig5_                      = pass_HLT_HT430_DisplacedDijet35_Inclusive1PtrkShortSig5_                     ||(trigname.Contains("HLT_HT430_DisplacedDijet35_Inclusive1PtrkShortSig5_") && trigresults->accept(itrig));
          pass_HLT_HT430_DisplacedDijet40_Inclusive1PtrkShortSig5_                      = pass_HLT_HT430_DisplacedDijet40_Inclusive1PtrkShortSig5_                     ||(trigname.Contains("HLT_HT430_DisplacedDijet40_Inclusive1PtrkShortSig5_") && trigresults->accept(itrig));
          pass_HLT_Mu6HT240_DisplacedDijet30_Inclusive0PtrkShortSig5_                   = pass_HLT_Mu6HT240_DisplacedDijet30_Inclusive0PtrkShortSig5_                  ||(trigname.Contains("HLT_Mu6HT240_DisplacedDijet30_Inclusive0PtrkShortSig5_") && trigresults->accept(itrig));
          pass_HLT_Mu6HT240_DisplacedDijet30_Inclusive1PtrkShortSig5_DisplacedLoose_    = pass_HLT_Mu6HT240_DisplacedDijet30_Inclusive1PtrkShortSig5_DisplacedLoose_   ||(trigname.Contains("HLT_Mu6HT240_DisplacedDijet30_Inclusive1PtrkShortSig5_DisplacedLoose_") && trigresults->accept(itrig));
          pass_HLT_Mu6HT240_DisplacedDijet35_Inlcusive0PtrkShortSig5_                   = pass_HLT_Mu6HT240_DisplacedDijet35_Inlcusive0PtrkShortSig5_                  ||(trigname.Contains("HLT_Mu6HT240_DisplacedDijet35_Inlcusive0PtrkShortSig5_") && trigresults->accept(itrig));
          pass_HLT_Mu6HT240_DisplacedDijet35_Inclusive1PtrkShortSig5_DisplacedLoose_    = pass_HLT_Mu6HT240_DisplacedDijet35_Inclusive1PtrkShortSig5_DisplacedLoose_   ||(trigname.Contains("HLT_Mu6HT240_DisplacedDijet35_Inclusive1PtrkShortSig5_DisplacedLoose_") && trigresults->accept(itrig));
          pass_HLT_Mu6HT240_DisplacedDijet40_Inclusive0PtrkShortSig5_                   = pass_HLT_Mu6HT240_DisplacedDijet40_Inclusive0PtrkShortSig5_                  ||(trigname.Contains("HLT_Mu6HT240_DisplacedDijet40_Inclusive0PtrkShortSig5_") && trigresults->accept(itrig));
          pass_HLT_Mu6HT240_DisplacedDijet40_Inclusive1PtrkShortSig5_DisplacedLoose_    = pass_HLT_Mu6HT240_DisplacedDijet40_Inclusive1PtrkShortSig5_DisplacedLoose_   ||(trigname.Contains("HLT_Mu6HT240_DisplacedDijet40_Inclusive1PtrkShortSig5_DisplacedLoose_") && trigresults->accept(itrig));
          pass_HLT_HT430_DelayedJet40_DoubleDelay0p5nsTrackless_                        = pass_HLT_HT430_DelayedJet40_DoubleDelay0p5nsTrackless_                       ||(trigname.Contains("HLT_HT430_DelayedJet40_DoubleDelay0p5nsTrackless_") && trigresults->accept(itrig));
          pass_HLT_HT430_DelayedJet40_DoubleDelay1nsInclusive_                          = pass_HLT_HT430_DelayedJet40_DoubleDelay1nsInclusive_                         ||(trigname.Contains("HLT_HT430_DelayedJet40_DoubleDelay1nsInclusive_") && trigresults->accept(itrig));
          pass_HLT_HT430_DelayedJet40_SingleDelay1nsTrackless_                          = pass_HLT_HT430_DelayedJet40_SingleDelay1nsTrackless_                         ||(trigname.Contains("HLT_HT430_DelayedJet40_SingleDelay1nsTrackless_") && trigresults->accept(itrig));
          pass_HLT_HT430_DelayedJet40_SingleDelay2nsInclusive_                          = pass_HLT_HT430_DelayedJet40_SingleDelay2nsInclusive_                         ||(trigname.Contains("HLT_HT430_DelayedJet40_SingleDelay2nsInclusive_") && trigresults->accept(itrig));                         
          

 
       }
       
   }   





 
   std::vector<int> matched_genparton;
   //for (auto const& ijet: *jet_coll){
   for(size_t i=0; i<calojet_coll->size(); i++){
      edm::RefToBase<reco::Jet> ijet = jet_coll->refAt(i);
      double corrfac = jetCorr->correction(*ijet);
      float mindR=1000;
      int matched_idx = -1;
      for(size_t g=0; g<genpt.size(); g++){
          float dR = deltaR(ijet->phi(), ijet->eta(),genphi.at(g), geneta.at(g));
          if(dR<0.50 && dR<mindR && (ijet->pt()*corrfac-genpt.at(g))/genpt.at(g)<1.0 && (ijet->pt()*corrfac-genpt.at(g))/genpt.at(g)>-0.5){
              matched_idx = g;
              mindR = dR;
          }

      }
      matched_genparton.push_back(matched_idx);



      jetcorrfac.push_back(corrfac);
      jetpt.push_back(ijet->pt()*corrfac);
      jetenergy.push_back(ijet->energy()*corrfac);
      jeteta.push_back(ijet->eta());
      jetphi.push_back(ijet->phi());
      
      jetUnc->setJetEta(ijet->eta());
      jetUnc->setJetPt(ijet->pt()*corrfac);
      float unc = (float)jetUnc->getUncertainty(true);
      jetPtUp.push_back(ijet->pt()*corrfac*(1+unc));
      jetPtDown.push_back(ijet->pt()*corrfac*(1-unc));


      if(ijet->pt()*corrfac>40 and fabs(ijet->eta())<2.4){
          CaloHT+=ijet->pt()*corrfac;
      }

      if(ijet->pt()*corrfac*(1+unc)>40 and fabs(ijet->eta())<2.4){
          CaloHTup+=ijet->pt()*corrfac*(1+unc);
      }
    
      if(ijet->pt()*corrfac*(1-unc)>40 and fabs(ijet->eta())<2.4){
          CaloHTdown+=ijet->pt()*corrfac*(1+unc);
      }

   }
   
   
      
   for (auto const& itrack : *patcan){
       if (itrack.trackHighPurity() && itrack.hasTrackDetails()){
           reco::Track tmptrk = itrack.pseudoTrack();
           if (tmptrk.quality(reco::TrackBase::highPurity) && tmptrk.pt()> TrackPtCut_ && tmptrk.charge()!=0){
               alltracks.push_back(tmptrk);
           }
       }
   } 

   for (auto const& itrack : *losttracks){
       if (itrack.trackHighPurity() && itrack.hasTrackDetails()){
           reco::Track tmptrk = itrack.pseudoTrack();
           if (tmptrk.quality(reco::TrackBase::highPurity) && tmptrk.pt()> TrackPtCut_ && tmptrk.charge()!=0){
               alltracks.push_back(itrack.pseudoTrack());
           }
       }
   }
  
   //std::cout<<"number of tracks:"<<alltracks.size()<<std::endl;
   std::auto_ptr<JetTrks> jettracks_assoc (new JetTrks(reco::JetRefBaseProd(jet_coll)));
   jettracks(&*jettracks_assoc,  jet_coll, alltracks, 0.5);

   for(size_t i=0; i<calojet_coll->size()-1; i++){
      for(size_t k=i+1; k<calojet_coll->size(); k++){
              edm::RefToBase<reco::CaloJet> jet1_ref = calojet_coll->refAt(i);
              edm::RefToBase<reco::CaloJet> jet2_ref = calojet_coll->refAt(k);
              if (!(fabs(jet1_ref->eta())<2 && fabs(jet2_ref->eta())<2 )) continue;
 

               
             //std::vector<std::string> input_names_{"input_jet1:0", "input_jet2:0", "input_dijet:0", "input_sv:0", "input_trks:0", "input_trktosv:0"};
             //
             //std::vector<tensorflow::TensorShape> input_sizes{
             //    {1, 7, 7}, 
             //    {1, 7, 7}, 
             //    {1, 4}, 
             //    {1, 6, 12}, 
             //    {1, 30, 11},
             //    {1, 180, 4}
             //};

             //tensorflow::NamedTensorList _input_tensors;
             // _input_tensors.resize(input_sizes.size());

             // for (unsigned int i = 0; i < input_names_.size(); i++) {
             //     std::string group_name = input_names_[i];
             //     tensorflow::Tensor group_tensor(tensorflow::DT_FLOAT, input_sizes[i]);
             //     _input_tensors[i] = tensorflow::NamedTensor(group_name, group_tensor);
             // }

              for (unsigned int i = 0; i < input_sizes.size(); i++) {
                  _input_tensors[i].second.flat<float>().setZero();
              }

              for (unsigned int i= 0; i< input_prompt_sizes.size(); i++) {
                  _input_prompt_tensors[i].second.flat<float>().setZero();
              }

              reco::Candidate::LorentzVector p4 = jet1_ref->p4()*jetcorrfac.at(i) + jet2_ref->p4()*jetcorrfac.at(k);
              GlobalVector direction(p4.px(), p4.py(), p4.pz());
              direction = direction.unit();
              math::XYZVector jet1Dir = jet1_ref->momentum().Unit();
              math::XYZVector jet2Dir = jet2_ref->momentum().Unit();

              reco::TrackRefVector dijettrks = reco::JetTracksAssociation::getValue(*jettracks_assoc,  (edm::RefToBase<reco::Jet>)jet1_ref);
              reco::TrackRefVector dijettrks2 = reco::JetTracksAssociation::getValue(*jettracks_assoc,  (edm::RefToBase<reco::Jet>)jet2_ref);

               std::vector<int> erased_1;
               std::vector<int> erased_2;

               for(int q=0; q<int(dijettrks.size()); q++){
                   for(int t=0; t<int(dijettrks2.size()); t++){
                       if(dijettrks[q].index()==dijettrks2[t].index()){
                           float dR1 = deltaR(dijettrks[q]->eta(), dijettrks[q]->phi(), jet1_ref->eta(), jet1_ref->phi());
                           float dR2 = deltaR(dijettrks[q]->eta(), dijettrks[q]->phi(), jet2_ref->eta(), jet2_ref->phi());
                           if(dR1<dR2){
                               erased_2.push_back(t);
                               break;
                           }
                           else{
                               erased_1.push_back(q);
                               break;
                           }
                       }
                   }
               }


               std::sort(erased_1.begin(), erased_1.end());
               std::sort(erased_2.begin(), erased_2.end());
               reco::TrackRefVector dijettrks_clean;
               reco::TrackRefVector dijettrks2_clean;
               reco::TrackRefVector dijettrks_clean_ordered; 
               std::vector<int> indices_ordered;

               for(int n=0; n<int(dijettrks.size()); n++){
                   if(find(erased_1.begin(), erased_1.end(), n)==erased_1.end()){
                       dijettrks_clean.push_back(dijettrks[n]);
                   }
               }

               for(int m=0; m<int(dijettrks2.size()); m++){
                   if(find(erased_2.begin(), erased_2.end(), m)==erased_2.end()){
                       dijettrks2_clean.push_back(dijettrks2[m]);
                   }
               }

              for(size_t j = 0; j<dijettrks2_clean.size(); j++){
                 dijettrks_clean.push_back(dijettrks2_clean[j]);
               }

               std::vector<int> indices(dijettrks_clean.size());
               std::fill(indices.begin(), indices.end()-dijettrks2_clean.size(), 1);
               std::fill(indices.end()-dijettrks2_clean.size(), indices.end(), 2);
                
               std::vector<size_t> orders = OrderTracks(dijettrks_clean, pv, *theB);
               for(auto idx: orders){
                   dijettrks_clean_ordered.push_back(dijettrks_clean[idx]);
                   indices_ordered.push_back(indices[idx]);
               } 

               std::vector<reco::TransientTrack> t_tks_SV;
               std::vector<reco::Track> tks_SV;
               std::vector<int> indices_SV;
               std::vector<float> guess_Lxy_SV;

               //std::vector<float> ip2d_SV_assign;
               //std::vector<float> ip2d_sig_SV_assign;
               //std::vector<float> ip3d_SV_assign;
               //std::vector<float> ip3d_sig_SV_assign;
               //std::vector<float> ip3d_minsig_SV_assign;

               std::vector<float> ip2d_SV;
               std::vector<float> ip2d_sig_SV;
               std::vector<float> ip3d_SV;
               std::vector<float> ip3d_sig_SV;
               std::vector<float> ip3d_minsig_SV;

               std::vector<reco::TransientTrack> t_tks_dijet;
               std::vector<int> indices_dijet;
               std::vector<float> ip2d_dijet;
               std::vector<float> ip2d_sig_dijet;
               std::vector<float> Lxyexp_dijet;
               std::vector<float> pts_dijet;
               std::vector<float> etas_dijet;
               std::vector<float> phis_dijet;
               std::vector<float> energys_dijet;
               std::vector<float> ip3d_dijet;
               std::vector<float> ip3d_sig_dijet;
               std::vector<float> ip3d_minsig_dijet;
               std::vector<int> pvidx_dijet;
               std::vector<float> dRjet1_dijet;
               std::vector<float> dRjet2_dijet;

               std::vector<int> indices_full;
               std::vector<float> ip2d_full;
               std::vector<float> ip2dsig_full;
               std::vector<float> ip3d_full;
               std::vector<float> ip3dsig_full; 
               std::vector<float> ip3dminsig_full;
               std::vector<float> energys_full;
               std::vector<float> pts_full;
               std::vector<int> pvindex_full;
  

               std::vector<int>   indices_prompt;
               std::vector<float> ip2d_prompt;
               std::vector<float> ip2dsig_prompt;
               std::vector<float> ip3d_prompt; 
               std::vector<float> ip3dsig_prompt;
               std::vector<float> pts_prompt; 
               std::vector<float> energys_prompt;
               std::vector<float> ip3d_minsig_prompt;
               std::vector<int> pvidx_prompt;
               std::vector<float> dRjet1_prompt;
               std::vector<float> dRjet2_prompt;

               //std::vector<float> dR_dijet;

               int nPrompt_tk1 = 0;
               int nPrompt_tk2 = 0;
               int nPromptTracks = 0;

               float promptEnergy_1 = 0;
               float promptEnergy_2 = 0;
               float promptEnergy = 0;
               float sigpromptEnergy = 0;
               float sig30promptEnergy = 0;

               float trksEnergy_1 = 0;
               float trksPt_1 = 0;
               float trksEnergy_2 = 0;
               float trksPt_2 = 0;
               float trksEnergy = 0;
               float disptrksEnergy = 0;
               float trksPt = 0;
               float disptrksPt = 0;

               float promptEnergy_frac;
               float promptEnergy_frac_1;
               float promptEnergy_frac_2;

               float svtrkspt_frac;

               float sigpromptEnergy_frac;
               float sig30promptEnergy_frac;


               for(size_t j = 0; j<dijettrks_clean_ordered.size(); j++){
                   const reco::TrackRef trk = dijettrks_clean_ordered[j];
                   if(!trk->quality(reco::TrackBase::highPurity)) continue;
                   if(trk->pt() < TrackPtCut_) continue;
                   //if(indices[j]==1) dR_dijet.push_back(deltaR(trk->eta(), trk->phi(), jet1_ref->eta(), jet1_ref->phi()));
                   //else dR_dijet.push_back(deltaR(trk->eta(), trk->phi(), jet2_ref->eta(), jet2_ref->phi()));
                   math::XYZVector trkMom = trk->momentum();
   
                   reco::TransientTrack t_trk = (*theB).build(trk);
                   if (!(t_trk.isValid())) continue;
                   Measurement1D ip2d = IPTools::signedTransverseImpactParameter(t_trk, direction, pv).second;
                   Measurement1D ip3d = IPTools::signedImpactParameter3D(t_trk, direction, pv).second;

                   float ip3d_minsig = 1e10;
                   int pvidx = -1;
                   for (int ivtx = 0; ivtx<nPV; ivtx++){

                       Measurement1D ip3d_tmp = IPTools::signedImpactParameter3D(t_trk, direction, (*pvHandle)[ivtx]).second;
                       if(fabs(ip3d_tmp.significance())<ip3d_minsig){
                           ip3d_minsig=fabs(ip3d_tmp.significance());
                           pvidx = ivtx;
                       }
                   }

                   
                   float trk_energy = sqrt(trk->p()*trk->p()+0.13957018*0.13957018);
                   trksEnergy+=trk_energy;
                   trksPt+=trk->pt();

                   indices_full.push_back(indices_ordered[j]);
                   energys_full.push_back(trk_energy);
                   pts_full.push_back(trk->pt());
                   ip2d_full.push_back(ip2d.value());
                   ip2dsig_full.push_back(ip2d.significance());
                   ip3d_full.push_back(ip3d.value());
                   ip3dsig_full.push_back(ip3d.significance());
                   ip3dminsig_full.push_back(ip3d_minsig);
                   pvindex_full.push_back(pvidx);
                   
                   
                   if(indices_ordered[j]==1) {trksEnergy_1+=trk_energy; trksPt_1+=trk->pt();}
                   if(indices_ordered[j]==2) {trksEnergy_2+=trk_energy; trksPt_2+=trk->pt();}
                   if(fabs(ip3d.value())<0.03){
                       nPromptTracks += 1;
                       if(indices_ordered[j]==1) nPrompt_tk1 += 1;
                       if(indices_ordered[j]==2) nPrompt_tk2 += 1;
                   }

                   if(fabs(ip2d.significance())<50){

                       sigpromptEnergy += trk_energy;
                   }

                   if(fabs(ip2d.significance())<30){

                       sig30promptEnergy += trk_energy;
                   }
 

                   if(fabs(ip2d.value())<0.05 || fabs(ip2d.significance())<5.0){
                       if(fabs(ip2d.value())<0.05){
                           promptEnergy += trk_energy;
                           if(indices_ordered[j]==1) promptEnergy_1 += trk_energy;
                           if(indices_ordered[j]==2) promptEnergy_2 += trk_energy;
                    
                           indices_prompt.push_back(indices_ordered[j]); 
                           ip2d_prompt.push_back(ip2d.value());
                           ip2dsig_prompt.push_back(ip2d.significance());
                           ip3d_prompt.push_back(ip3d.value());
                           ip3dsig_prompt.push_back(ip3d.significance());
                           pts_prompt.push_back(trk->pt()); 
                           energys_prompt.push_back(trk_energy);
                           ip3d_minsig_prompt.push_back(ip3d_minsig);
                           pvidx_prompt.push_back(pvidx);
                           dRjet1_prompt.push_back(deltaR(trkMom, jet1Dir));
                           dRjet2_prompt.push_back(deltaR(trkMom, jet2Dir));
                       }
                       continue;
                   }

                   energys_dijet.push_back(trk_energy);
                   t_tks_dijet.push_back(t_trk);
                   ip2d_dijet.push_back(ip2d.value());
                   ip2d_sig_dijet.push_back(ip2d.significance());
                    
                   float R = 100*3.3*trk->pt()/3.8*trk->charge();
                   float dphi = trk->phi()-direction.phi();
                   float Lxyexp =  sqrt(R*R-(R-ip2d.value())*(R-ip2d.value())*cos(dphi)*cos(dphi))-(R-ip2d.value())*sin(dphi);
                   Lxyexp_dijet.push_back(Lxyexp);
                   
                   pts_dijet.push_back(trk->pt());
                   etas_dijet.push_back(trk->eta());
                   phis_dijet.push_back(trk->phi());
                   ip3d_dijet.push_back(ip3d.value());
                   ip3d_sig_dijet.push_back(ip3d.significance());
                   ip3d_minsig_dijet.push_back(ip3d_minsig);
                   pvidx_dijet.push_back(pvidx);
                   indices_dijet.push_back(indices_ordered[j]);
                   dRjet1_dijet.push_back(reco::deltaR(trkMom, jet1Dir));
                   dRjet2_dijet.push_back(reco::deltaR(trkMom, jet2Dir));

                   disptrksEnergy+=trk_energy;
                   disptrksPt+=trk->pt();


                   float r = 100*3.3*trk->pt()/3.8;
                   float gLxy = ip2d.value()/sin(trk->phi()-direction.phi())*(1-2.5*fabs(ip2d.value())/r);
                   ip2d_SV.push_back(ip2d.value());
                   ip2d_sig_SV.push_back(ip2d.significance());
                   ip3d_SV.push_back(ip3d.value());
                   ip3d_sig_SV.push_back(ip3d.significance());
                   ip3d_minsig_SV.push_back(ip3d_minsig);
                   t_tks_SV.push_back(t_trk);
                   tks_SV.push_back(*trk);
                   guess_Lxy_SV.push_back(gLxy);
                   indices_SV.push_back(indices_ordered[j]);

               }

               if (t_tks_SV.size()<2) continue;

               
              //Dijet Gen Info
              if(isMC_){
                   int idx1 = int(matched_genparton[i]);
                   int idx2 = int(matched_genparton[k]);
                   bool true_dijet = false;
                   int genpdgID1 = 0;
                   int genpdgID2 = 0;
                   int genmompdgID1 = 0;
                   int genmompdgID2 = 0;
                   float genpt1 = 0;
                   float geneta1 = 0;
                   float genphi1 = 0;
                   float genenergy1 = 0;
                   float genpt2 = 0;
                   float geneta2 = 0;
                   float genphi2 = 0;
                   float genenergy2 = 0;
                   float djgenSVx1 = 0;
                   float djgenSVy1 = 0;
                   float djgenSVz1 = 0;
                   float djgenSVlxy1 = 0;
                   float djgenSVlxyz1 = 0;
                   float djgenSVctau01 = 0;
                   float djgenSVx2 = 0;
                   float djgenSVy2 = 0;
                   float djgenSVz2 = 0;
                   float djgenSVlxy2 = 0;
                   float djgenSVlxyz2 = 0;
                   float djgenSVctau02 = 0;
 
                   if(idx1>=0 && idx2>=0) true_dijet = genmompdgID.at(idx1)==genmompdgID.at(idx2);
                   TrueDijet.push_back(true_dijet);

                   if(idx1>=0){
                       genpdgID1 = genpdgID.at(idx1);
                       genmompdgID1 = genmompdgID.at(idx1);
                       genpt1 = genpt.at(idx1);
                       geneta1 = geneta.at(idx1);
                       genphi1 = genphi.at(idx1);
                       genenergy1 = genenergy.at(idx1);
                       djgenSVx1 = genSVx.at(idx1);
                       djgenSVy1 = genSVy.at(idx1);
                       djgenSVz1 = genSVz.at(idx1);
                       djgenSVlxy1 = genSVlxy.at(idx1);
                       djgenSVlxyz1 = genSVlxyz.at(idx1);
                       djgenSVctau01 = genSVctau0.at(idx1); 
                   }

                   if(idx2>=0){
                       genpdgID2 = genpdgID.at(idx2);
                       genmompdgID2 = genmompdgID.at(idx2);
                       genpt2 = genpt.at(idx2);
                       geneta2 = geneta.at(idx2);
                       genphi2 = genphi.at(idx2);
                       genenergy2 = genenergy.at(idx2);
                       djgenSVx2 = genSVx.at(idx2);
                       djgenSVy2 = genSVy.at(idx2);
                       djgenSVz2 = genSVz.at(idx2);
                       djgenSVlxy2 = genSVlxy.at(idx2);
                       djgenSVlxyz2 = genSVlxyz.at(idx2);
                       djgenSVctau02 = genSVctau0.at(idx2); 
                   }
                 
                   jet1pdgID.push_back(genpdgID1);
                   jet1mompdgID.push_back(genmompdgID1);
                   jet1genpt.push_back(genpt1);
                   jet1geneta.push_back(geneta1);
                   jet1genphi.push_back(genphi1);
                   jet1genenergy.push_back(genenergy1);
                   dijetgenSVx1.push_back(djgenSVx1);
                   dijetgenSVy1.push_back(djgenSVy1);
                   dijetgenSVz1.push_back(djgenSVz1);
                   dijetgenSVlxy1.push_back(djgenSVlxy1);
                   dijetgenSVlxyz1.push_back(djgenSVlxyz1);
                   dijetgenSVctau01.push_back(djgenSVctau01);
               
                   jet2pdgID.push_back(genpdgID2);
                   jet2mompdgID.push_back(genmompdgID2);
                   jet2genpt.push_back(genpt2);
                   jet2geneta.push_back(geneta2);
                   jet2genphi.push_back(genphi2);
                   jet2genenergy.push_back(genenergy2);
                   dijetgenSVx2.push_back(djgenSVx2);
                   dijetgenSVy2.push_back(djgenSVy2);
                   dijetgenSVz2.push_back(djgenSVz2);
                   dijetgenSVlxy2.push_back(djgenSVlxy2);
                   dijetgenSVlxyz2.push_back(djgenSVlxyz2);
                   dijetgenSVctau02.push_back(djgenSVctau02);

    

              }
              






               std::vector<TracksClusteringFromDisplacedSeed::Cluster> clusters = clusterizer->clusters(pv, t_tks_SV);
               std::vector<TransientVertex> recoVertices;
               //auto recoVertices = std::make_unique<std::vector<TransientVertex> >();
               for (std::vector<TracksClusteringFromDisplacedSeed::Cluster>::iterator cluster = clusters.begin();
         cluster != clusters.end();
         ++cluster) {
                   if (cluster->tracks.size()<2) continue; 
                   
                   std::vector<TransientVertex> tmp_vertices = vtxmaker_.vertices(cluster->tracks);
                   for (std::vector<TransientVertex>::iterator v = tmp_vertices.begin(); v != tmp_vertices.end(); ++v) {
                    reco::Vertex tmpvtx(*v);
                    if(v->isValid() &&
                       !tmpvtx.isFake() &&
                       (tmpvtx.nTracks(vtxweight_)>1) &&
                       (tmpvtx.normalizedChi2()>0) &&
                       (tmpvtx.normalizedChi2()<5)) recoVertices.push_back(*v); 

                   }

            
              }
              //if(TrueDijet.back()){
              //std::cout<<"********************************************"<<std::endl;
              //std::cout<<"Number of vertices before merging:"<<recoVertices.size()<<std::endl;
              //}
              
              //if(TrueDijet.back()){
              //std::cout<<"Number of vertices after merging:"<<recoVertices.size()<<std::endl;
              ////recoVertices.clear();
              //}
              //first_merging->mergeVertex(recoVertices);
              
              
               std::vector<TransientVertex> vertices = vtxmaker_.vertices(t_tks_SV);
               for(std::vector<TransientVertex>::iterator isv = vertices.begin(); isv!=vertices.end(); ++isv){
                   if(!isGoodVtx(*isv)) isv = vertices.erase(isv)-1;

               }

               recoVertices.insert(recoVertices.end(), vertices.begin(), vertices.end());
               //vertexMerge(recoVertices, 0.7, 2.0);
               std::vector<TransientVertex> newVTXs = TrackVertexRefit(t_tks_SV, recoVertices);
               vertexMerge(newVTXs, 0.2, 3.0);
               std::vector<size_t> orderedSV_idx = OrderSVs(newVTXs, pv);
               std::vector<TransientVertex> newVTXs_ordered;
               for(auto idx: orderedSV_idx){
                   newVTXs_ordered.push_back(newVTXs[idx]);
               } 
                
               std::vector<std::vector<float> > ip2d_SV_assign;
               std::vector<std::vector<float> > ip2dsig_SV_assign;
               std::vector<std::vector<float> > ip3d_SV_assign;
               std::vector<std::vector<float> > ip3dsig_SV_assign;
               std::vector<std::vector<float> > trkEnergy_SV;
               //std::vector<std::vector<float> > ip2d_wrt_SV;
               //std::vector<std::vector<float> > ip3d_wrt_SV;
               //std::vector<std::vector<float> > ip2dsig_wrt_SV;
               //std::vector<std::vector<float> > ip3dsig_wrt_SV;
            
               std::vector<std::vector<int> >   jetidx_SV;
               std::vector<std::vector<float>>  charges_SV;
               std::vector<float>     vtx_x;
               std::vector<float>     vtx_y;
               std::vector<float>     vtx_z;
               std::vector<float>     vtx_lxy;
               std::vector<float>     vtx_lxysig;
               std::vector<float>     vtx_lxyz;
               std::vector<float>     vtx_lxyzsig;
               std::vector<float>     vtx_chi2;
               std::vector<float>     vtx_dRdijet;
               std::vector<float>     vtx_costhetadijet;
               std::vector<float>     vtx_costhetaPLxyz;
               std::vector<float>     vtx_meancosthetatrks;
 
               std::vector<float>     vtx_distgenSV1;
               std::vector<float>     vtx_distgenSV2;
               std::vector<float>     vtx_distsiggenSV1;
               std::vector<float>     vtx_distsiggenSV2;
  
               std::vector<float>     vtx_dRgenmom1;
               std::vector<float>     vtx_dRgenmom2;

               std::vector<float>     kappa_SV;
               float                  kappa_total =0;
               std::vector<int>       ntrack_SV;
               std::vector<int>       ntrackjet1_SV;
               std::vector<int>       ntrackjet2_SV;
               std::vector<float>     EFracJet1_SV;
               std::vector<float>     EFracJet2_SV;

               std::vector<float>     svsvdist;
               std::vector<float>     svsvdistsig;
               std::vector<float>     svsvdisttanh;
               std::vector<float>     svsvdistsigtanh; 
               std::vector<float>     svsvjet1dR;
               std::vector<float>     svsvjet2dR;
               std::vector<float>     svsvjet1costheta;
               std::vector<float>     svsvjet2costheta;
              
               std::vector<float>       trksEnergyfrac_SV;
               std::vector<float>       jetEnergyfrac_SV;
               float trksEnergyfrac_total = 0;
               float jetEnergyfrac_total = 0;
               float SV_ESum = 0; 
               //std::vector<float>     trkEnergy_SV;
               std::vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > vtxP4_SV; 
               //std::vector<TransientVertex> goodvtxs;
               int nvtx=0;
               for(size_t ivtx=0; ivtx<newVTXs_ordered.size(); ivtx++){
                   // bool goodVtx=false;
                    TransientVertex jvtx = newVTXs_ordered[ivtx];
                    reco::Vertex tmpvtx(newVTXs_ordered[ivtx]);
                    //if(vertices[ivtx].isValid() &&
                    //   !tmpvtx.isFake() &&
                    //   (tmpvtx.nTracks(vtxweight_)>1) &&
                    //   (tmpvtx.normalizedChi2()>0) &&
                    //   (tmpvtx.normalizedChi2()<5)) goodVtx = true;
                    //if(!goodVtx) continue;
                    //goodvtxs.push_back(vertices[ivtx]);
                    nvtx++;
                    //Chi2_SV.push_back(tmpvtx.normalizedChi2());
                    vtx_x.push_back(tmpvtx.position().x());
                    vtx_y.push_back(tmpvtx.position().y());
                    vtx_z.push_back(tmpvtx.position().z());
                    vtx_chi2.push_back(tmpvtx.normalizedChi2());

                    ROOT::Math::SVector<double, 3> vector(tmpvtx.position().x()-pv.x(), tmpvtx.position().y()-pv.y(), 0);
                    ROOT::Math::SVector<double, 3> vector3D(tmpvtx.position().x()-pv.x(), tmpvtx.position().y()-pv.y(), tmpvtx.position().z()-pv.z());
               


                    math::XYZVector vec3d(tmpvtx.position().x()-pv.x(), tmpvtx.position().y()-pv.y(), tmpvtx.position().z()-pv.z());
                    TVector3 vtxvec = TVector3(tmpvtx.position().x()-pv.x(), tmpvtx.position().y()-pv.y(), tmpvtx.position().z()-pv.z());

                    ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > jet1_physp4 = (ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > )jet1_ref->physicsP4(tmpvtx.position());
                    ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > jet2_physp4 = (ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > )jet2_ref->physicsP4(tmpvtx.position());

                    ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > DJ_physp4 = jet1_physp4+jet2_physp4;

                    TVector3 DJvec = TVector3(DJ_physp4.px(), DJ_physp4.py(), DJ_physp4.pz());
 
                    vtx_dRdijet.push_back(reco::deltaR(DJ_physp4, vec3d));
                    vtx_costhetadijet.push_back(vtxvec.Unit().Dot(DJvec.Unit()));

                    float lxy = (float)ROOT::Math::Mag(vector);
                    float lxyz = (float)ROOT::Math::Mag(vector3D);

                    if(genSVx.size()==4){
                        ROOT::Math::SVector<double, 3> vec_genSV1(tmpvtx.position().x()-genSVx.at(0), tmpvtx.position().y()-genSVy.at(0), tmpvtx.position().z()-genSVz.at(0)); 
                        ROOT::Math::SVector<double, 3> vec_genSV2(tmpvtx.position().x()-genSVx.at(2), tmpvtx.position().y()-genSVy.at(2), tmpvtx.position().z()-genSVz.at(2));
                        
                        float dist_genSV1 = float(ROOT::Math::Mag(vec_genSV1));
                        float dist_genSV2 = float(ROOT::Math::Mag(vec_genSV2));
                        float disterr_genSV1 = sqrt(ROOT::Math::Similarity(tmpvtx.covariance(), vec_genSV1))/dist_genSV1;
                        float disterr_genSV2 = sqrt(ROOT::Math::Similarity(tmpvtx.covariance(), vec_genSV2))/dist_genSV2;

                        float dRmom1 = deltaR(DJ_physp4.Eta(), DJ_physp4.Phi(), genmometa.at(0), genmomphi.at(0));
                        float dRmom2 = deltaR(DJ_physp4.Eta(), DJ_physp4.Phi(), genmometa.at(2), genmomphi.at(2));

                        vtx_dRgenmom1.push_back(dRmom1);
                        vtx_dRgenmom2.push_back(dRmom2);

                        vtx_distgenSV1.push_back(dist_genSV1);
                        vtx_distgenSV2.push_back(dist_genSV2);
 
                        vtx_distsiggenSV1.push_back(dist_genSV1/disterr_genSV1);
                        vtx_distsiggenSV2.push_back(dist_genSV2/disterr_genSV2); 
                         
                            
                         
                    }

  

                    vtx_lxy.push_back(lxy);
                    vtx_lxyz.push_back(lxyz);

                    reco::Candidate::CovarianceMatrix matrix = tmpvtx.covariance()+pv.covariance();

                    float lxyerr = sqrt(ROOT::Math::Similarity(matrix, vector))/lxy;
                    float lxyzerr = sqrt(ROOT::Math::Similarity(matrix, vector3D))/lxyz;

                    float lxysig = lxy/lxyerr;
                    float lxyzsig = lxyz/lxyzerr;

                    vtx_lxysig.push_back(lxysig);
                    vtx_lxyzsig.push_back(lxyzsig);


                    if(ivtx<max_sv){
                        for(size_t jvtx=0; jvtx<max_sv;jvtx++){
                            if(jvtx==ivtx) continue;
                            if(jvtx<newVTXs_ordered.size()){
                            VertexDistance3D dist;
                            reco::Vertex tmpvtx_j(newVTXs_ordered[jvtx]);
                            Measurement1D itoj_dist = dist.distance(tmpvtx, tmpvtx_j);
                            svsvdist.push_back(itoj_dist.value()+1);
                            svsvdistsig.push_back(itoj_dist.significance()+1);       
                            svsvdisttanh.push_back(std::tanh(itoj_dist.value())-1.2);
                            svsvdistsigtanh.push_back(std::tanh(itoj_dist.significance()/50)-1.2); 

                            math::XYZVector vec_itoj(tmpvtx_j.position().x()-tmpvtx.position().x(), tmpvtx_j.position().y()-tmpvtx.position().y(), tmpvtx_j.position().z()-tmpvtx.position().z());
                            TVector3 vec3_itoj(tmpvtx_j.position().x()-tmpvtx.position().x(), tmpvtx_j.position().y()-tmpvtx.position().y(), tmpvtx_j.position().z()-tmpvtx.position().z()); 
                            TVector3 jet1vec = TVector3(jet1_physp4.px(), jet1_physp4.py(), jet1_physp4.pz());
                            TVector3 jet2vec = TVector3(jet2_physp4.px(), jet2_physp4.py(), jet2_physp4.pz());
                            
                            svsvjet1dR.push_back(reco::deltaR(vec_itoj, jet1_physp4)-8);
                            svsvjet2dR.push_back(reco::deltaR(vec_itoj, jet2_physp4)-8);  
                            svsvjet1costheta.push_back(vec3_itoj.Unit().Dot(jet1vec.Unit()));
                            svsvjet2costheta.push_back(vec3_itoj.Unit().Dot(jet2vec.Unit()));
                       
                          }
                           else{
                            svsvdist.push_back(0); 
                            svsvdistsig.push_back(0);
                            svsvdisttanh.push_back(0);
                            svsvdistsigtanh.push_back(0);
                            svsvjet1dR.push_back(0);
                            svsvjet2dR.push_back(0);
                            svsvjet1costheta.push_back(0);
                            svsvjet2costheta.push_back(0);
   


                           }
                        }
              
                    }
  
                    int vtx_nTrack = 0;
                    int vtx_ntrkjet1 = 0; 
                    int vtx_ntrkjet2 = 0;
                    

                    ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > vtxP4; 
                  
                    std::vector<float> ip2d_assign;
                    std::vector<float> ip2dsig_assign;
                    std::vector<float> ip3d_assign;   
                    std::vector<float> ip3dsig_assign;
                    std::vector<float> trkenergy_assign;
                    std::vector<float> charges;
                    std::vector<int>   trkjetidx; 
                    float svtrkenergy_jet1=0;
                    float svtrkenergy_jet2=0;                   
                    float kappa = 0;
                    float meantheta = 0;
                    float ptsum = 0;
                     

                    for(size_t i = 0; i<t_tks_SV.size(); i++){
                        if(jvtx.trackWeight(t_tks_SV[i])<vtxweight_) continue;
                        ip2d_assign.push_back(ip2d_SV[i]); 
                        ip2dsig_assign.push_back(ip2d_sig_SV[i]);
                        ip3d_assign.push_back(ip3d_SV[i]);
                        ip3dsig_assign.push_back(ip3d_sig_SV[i]);
                        kappa+=ip3d_sig_SV[i]; 

                        GlobalVector p3 = t_tks_SV[i].trajectoryStateClosestToPoint(jvtx.position()).momentum();
                        TVector3 trkp(p3.x(), p3.y(), p3.z());
                        meantheta+=trkp.Pt()*(trkp.Unit().Dot(vtxvec.Unit()));
                        ptsum+=trkp.Pt();
                        float trkenergy = sqrt(p3.mag2()+0.13957018*0.13957018);
                        trkenergy_assign.push_back(trkenergy);
                        charges.push_back(t_tks_SV[i].track().charge());
                        vtxP4 += ROOT::Math::LorentzVector<ROOT::Math::PxPyPzM4D<float> >(p3.x(), p3.y(), p3.z(), 0.13957018);
                        vtx_nTrack+=1;
                        if(indices_SV[i]==1){
			    vtx_ntrkjet1+=1;
   			    trkjetidx.push_back(1);
                            svtrkenergy_jet1+=trkenergy;
                        }
                        if(indices_SV[i]==2) {
                            vtx_ntrkjet2+=1;
                            trkjetidx.push_back(2);
                            svtrkenergy_jet2+=trkenergy;

                        }
                    }
                   
                    kappa_SV.push_back(kappa);
                    vtx_meancosthetatrks.push_back(meantheta/ptsum);
                    kappa_total+=kappa; 
                    vtxP4_SV.push_back(vtxP4);
                    SV_ESum += vtxP4.energy();


                    TVector3 vtxPvec(vtxP4.px(), vtxP4.py(), vtxP4.pz());

                    vtx_costhetaPLxyz.push_back(vtxPvec.Unit().Dot(vtxvec.Unit())); 
                    ntrack_SV.push_back(vtx_nTrack);
                    ntrackjet1_SV.push_back(vtx_ntrkjet1);
                    ntrackjet2_SV.push_back(vtx_ntrkjet2);
                    EFracJet1_SV.push_back(svtrkenergy_jet1/vtxP4.energy());
                    EFracJet2_SV.push_back(svtrkenergy_jet2/vtxP4.energy());
                  
                    ip2d_SV_assign.push_back(ip2d_assign);
                    ip2dsig_SV_assign.push_back(ip2dsig_assign);
                    ip3d_SV_assign.push_back(ip3d_assign);
                    ip3dsig_SV_assign.push_back(ip3dsig_assign);
                    jetidx_SV.push_back(trkjetidx);
                    charges_SV.push_back(charges);
                    trkEnergy_SV.push_back(trkenergy_assign);
                    trksEnergyfrac_SV.push_back(vtxP4.energy()/trksEnergy);
                    trksEnergyfrac_total+=vtxP4.energy()/trksEnergy;
                    jetEnergyfrac_SV.push_back(vtxP4.energy()/(jet1_ref->energy()*jetcorrfac.at(i)+jet2_ref->energy()*jetcorrfac.at(k)));
                    jetEnergyfrac_total+=vtxP4.energy()/(jet1_ref->energy()*jetcorrfac.at(i)+jet2_ref->energy()*jetcorrfac.at(k));
             
                    

              }

              //recoVertices.insert(recoVertices.end(), goodvtxs.begin(), goodvtxs.end());
              //if(TrueDijet.back()){
              //std::cout<<"Number of AVR vertices:"<<goodvtxs.size()<<std::endl; 
              //}
              //vertexMerge(recoVertices, 0.7, 2.0);
             
              //if(TrueDijet.back()){
              //std::cout<<"Number of the totoal merged vertices:"<<recoVertices.size()<<std::endl;
              //}
    
              //std::vector<TransientVertex> newVTXs = TrackVertexRefit(t_tks_SV, recoVertices);
              //if(TrueDijet.back()){
              //std::cout<<"Number of the refitted vertices:"<<newVTXs.size()<<std::endl;
              //}
              //
              //vertexMerge(newVTXs, 0.2, 3.0); 
              //if(TrueDijet.back()){
              //stjetIVFMiniMLDisp_tensor.ccd
              //}
 
              std::vector<std::vector<int> > trk_SVassign;
       
              std::vector<std::vector<float> > ip3d_wrt_SV;
              std::vector<std::vector<float> > ip3dsig_wrt_SV;
              std::vector<std::vector<float> > ip3dtanh_wrt_SV;
              std::vector<std::vector<float> > ip3dsigtanh_wrt_SV;
              std::vector<std::vector<float> > costheta_wrt_SV;
     

              std::vector<bool> trk_hasSV;
              size_t n_trk =  t_tks_dijet.size();
              for(size_t itrk=0; itrk<n_trk; itrk++){
                  std::vector<float> ip3dSV;
                  std::vector<float> ip3dsigSV;
                  std::vector<float> ip3dtanhSV;
                  std::vector<float> ip3dsigtanhSV;
                  std::vector<int> trkToSV; 
                  std::vector<float> costhetaSV;
                  bool hasSV = false; 
                  for(size_t ivtx =0; ivtx<newVTXs_ordered.size(); ivtx++){
                      reco::Vertex tmpvtx(newVTXs_ordered[ivtx]);
                      GlobalPoint vtxPos = newVTXs_ordered[ivtx].position();
                      Measurement1D IP3D = IPTools::signedImpactParameter3D(t_tks_dijet[itrk], direction, tmpvtx).second;
                      GlobalVector p3 = t_tks_dijet[itrk].trajectoryStateClosestToPoint(vtxPos).momentum();
                      TVector3 trkp(p3.x(), p3.y(), p3.z());
                      TVector3 vtx_vec(vtxPos.x()-pv.x(), vtxPos.y()-pv.y(), vtxPos.z()-pv.z());
                      costhetaSV.push_back(trkp.Unit().Dot(vtx_vec.Unit()));
                      ip3dSV.push_back(IP3D.value());
                      ip3dsigSV.push_back(IP3D.significance());
                      ip3dtanhSV.push_back(std::tanh(IP3D.value())-1.2);
                      ip3dsigtanhSV.push_back(std::tanh(IP3D.significance()/50)-1.2);

                      if(newVTXs_ordered[ivtx].trackWeight(t_tks_dijet[itrk])>vtxweight_){
                          trkToSV.push_back(1);
                          hasSV = true;
                          //trk_SV=ivtx; 
                          //break;
                      }
                      else{
                          trkToSV.push_back(0);
                      } 
  
                  }
  
                  trk_hasSV.push_back(hasSV);
          
                  trk_SVassign.push_back(trkToSV);
                  ip3d_wrt_SV.push_back(ip3dSV);
                  ip3dsig_wrt_SV.push_back(ip3dsigSV);
                  ip3dtanh_wrt_SV.push_back(ip3dtanhSV);   
                  ip3dsigtanh_wrt_SV.push_back(ip3dsigtanhSV);
                  costheta_wrt_SV.push_back(costhetaSV); 

              }

              
              
              
              
              
               //bool goodVtx = false;
               //std::vector<TransientVertex> vertices = vtxmaker_.vertices(t_tks_SV);
               //reco::Vertex vtx(jvtx);
               //if(jvtx.isValid() &&
               //   !vtx.isFake() &&
               //   (vtx.nTracks(vtxweight_)>1) &&
               //   (vtx.normalizedChi2()>0) &&
               //   (vtx.normalizedChi2()<10)) goodVtx = true;
               //if(!goodVtx) continue;

               //ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > jet1_physp4 = (ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > )jet1_ref->physicsP4(vtx.position());
               //ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > jet2_physp4 = (ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > )jet2_ref->physicsP4(vtx.position());
               //ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > DJ_physp4 = jet1_physp4+jet2_physp4;

               //ROOT::Math::SVector<double, 3> vector(vtx.position().x()-pv.x(), vtx.position().y()-pv.y(), 0);
               //float lxy = (float)ROOT::Math::Mag(vector);
               //GlobalVector lxyvec(vtx.position().x()-pv.x(), vtx.position().y()-pv.y(), vtx.position().z()-pv.z());
               //float lxyphi = (float)lxyvec.phi();
               //reco::Candidate::CovarianceMatrix matrix = vtx.covariance()+pv.covariance();

               //float err = sqrt(ROOT::Math::Similarity(matrix, vector))/lxy;
               //float sig = lxy/err;

               //ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > vtxP4;
               //float charge = 0;
               //int n_tks_jet1 = 0;
               //int n_tks_jet2 = 0;
               //int vtx_nTrack = 0;
               //int pos_nTrack = 0;
               ////float hitsInFrontOfVert = 0;
               ////float missHitsAfterVert = 0;
               //float SVtksEnergy = 0;
               //float SVtksPt = 0;


               //for(size_t i = 0; i< t_tks_SV.size(); i++){
               //   if(jvtx.trackWeight(t_tks_SV[i])<vtxweight_) continue;
               //   vtx_nTrack+=1;

               //   ip2d_SV_assign.push_back(ip2d_SV[i]);
               //   ip2d_sig_SV_assign.push_back(ip2d_sig_SV[i]);
               //   ip3d_SV_assign.push_back(ip3d_SV[i]);
               //   ip3d_sig_SV_assign.push_back(ip3d_sig_SV[i]);
               //   ip3d_minsig_SV_assign.push_back(ip3d_minsig_SV[i]);

               //   if(ip2d_SV[i]>0) pos_nTrack+=1;
               //   if(indices_SV[i]==1) n_tks_jet1 +=1;
               //   if(indices_SV[i]==2) n_tks_jet2 +=1;
               //   GlobalVector p3 = t_tks_SV[i].trajectoryStateClosestToPoint(jvtx.position()).momentum();
               //   SVtksEnergy+=sqrt(p3.mag2()+0.13957018*0.13957018);
               //   SVtksPt+=t_tks_SV[i].trajectoryStateClosestToPoint(jvtx.position()).pt();

               //   vtxP4 += ROOT::Math::LorentzVector<ROOT::Math::PxPyPzM4D<float> >(p3.x(), p3.y(), p3.z(), 0.13957018);
               //   charge+=t_tks_SV[i].track().charge();

               //}

              //// if( n_tks_jet1 >=1 && n_tks_jet2 >=1 ) dijet_tag = true;

               //cluster Cluster;
               //std::vector<std::vector<float> > dijetclusters = Cluster.clusters(guess_Lxy_SV, 0.15*lxy);
               //std::vector<float> dijetbestcluster = Cluster.bestcluster(dijetclusters, lxy);

               //int ClrN1=0;
               //int ClrN2=0;

               //for(size_t l=0; l<dijetbestcluster.size(); l++){
               //    float glxy = dijetbestcluster[l];
               //    for(size_t z=0; z<guess_Lxy_SV.size(); z++){
               //        if(fabs(glxy-guess_Lxy_SV[z])<1e-5){
               //            if(indices_SV[z]==1) ClrN1++;
               //            if(indices_SV[z]==2) ClrN2++;
               //            break;
               //        }
               //    }
               //} 
            
               //Fill jet 1 & jet 2 prompt track tensors 
               std::vector<int> tmp_indices = indices_prompt;
               std::vector<float> tmp_ip2d  = ip2d_prompt;
               std::vector<float> tmp_ip2dsig = ip2dsig_prompt;
               std::vector<float> tmp_ip3d  = ip3d_prompt;
               std::vector<float> tmp_ip3dsig = ip3dsig_prompt;
               std::vector<float> tmp_ip3dminisig = ip3d_minsig_prompt;
               std::vector<float> tmp_energys = energys_prompt; 
               std::vector<float> tmp_dRjet1 = dRjet1_prompt; 
               std::vector<float> tmp_dRjet2 = dRjet2_prompt;

               std::reverse(tmp_indices.begin(), tmp_indices.end()); 
               std::reverse(tmp_ip2d.begin(), tmp_ip2d.end()); 
               std::reverse(tmp_ip2dsig.begin(), tmp_ip2dsig.end()); 
               std::reverse(tmp_ip3d.begin(), tmp_ip3d.end()); 
               std::reverse(tmp_ip3dsig.begin(), tmp_ip3dsig.end()); 
               std::reverse(tmp_ip3dminisig.begin(), tmp_ip3dminisig.end());
               std::reverse(tmp_energys.begin(), tmp_energys.end());
               std::reverse(tmp_dRjet1.begin(), tmp_dRjet1.end());
               std::reverse(tmp_dRjet2.begin(), tmp_dRjet2.end());
               
               size_t nptrk = tmp_indices.size();
               size_t iptrk1 = 0;
               size_t iptrk2 = 0; 
 
               for(size_t iptrk = 0; iptrk<nptrk; iptrk++){
                   if(tmp_indices.at(iptrk)==1 && iptrk1<7){
                       float* ptr1 = &(_input_prompt_tensors.at(0).second).tensor<float, 3>()(0, iptrk1, 0);
                       *ptr1 = nanTozero(float(std::tanh(tmp_ip2d.at(iptrk)*10)-1));
                       *(++ptr1) = nanTozero(float(std::tanh(tmp_ip2dsig.at(iptrk)/10)-1));
                       *(++ptr1) = nanTozero(float(std::tanh(tmp_ip3d.at(iptrk)*10)-1));
                       *(++ptr1) = nanTozero(float(std::tanh(tmp_ip3dsig.at(iptrk)/10)-1));
                       *(++ptr1) = nanTozero(float(std::tanh(tmp_ip3dminisig.at(iptrk)/10)-1));
                       *(++ptr1) = nanTozero(float(std::tanh(tmp_energys.at(iptrk)/(jet1_ref->pt()*jetcorrfac.at(i)))));
                       //*(++ptr1) = nanTozero(float(tmp_dRjet1.at(iptrk) - 0.6));
                       iptrk1++;
                   }

                   if(tmp_indices.at(iptrk)==2 && iptrk2<7){
                       float* ptr2 = &(_input_prompt_tensors.at(1).second).tensor<float, 3>()(0, iptrk2, 0);
                       *ptr2 = nanTozero(float(std::tanh(tmp_ip2d.at(iptrk)*10)-1));
                       *(++ptr2) = nanTozero(float(std::tanh(tmp_ip2dsig.at(iptrk)/10)-1));
                       *(++ptr2) = nanTozero(float(std::tanh(tmp_ip3d.at(iptrk)*10)-1));
                       *(++ptr2) = nanTozero(float(std::tanh(tmp_ip3dsig.at(iptrk)/10)-1));
                       *(++ptr2) = nanTozero(float(std::tanh(tmp_ip3dminisig.at(iptrk)/10)-1));
                       *(++ptr2) = nanTozero(float(std::tanh(tmp_energys.at(iptrk)/(jet2_ref->pt()*jetcorrfac.at(i)))));
                       //*(++ptr2) = nanTozero(float(tmp_dRjet2.at(iptrk) - 0.6));
                       iptrk2++;
                   }
               } 

               //Fill Dijet tensor
               float *ptr = &(_input_tensors.at(0).second).tensor<float, 2>()(0, 0);
               //*ptr = nanTozero(float(jet1_ref->pt()*jetcorrfac.at(i)));
               //*(++ptr) = nanTozero(float(jet2_ref->pt()*jetcorrfac.at(k)));
               *(ptr) = nanTozero(float(kappa_total));
               *(++ptr) = nanTozero(float(nvtx));
               
               //Fill Secondary Vertex tensor
               size_t nsv  = std::min(vtx_lxy.size(), (size_t)6);
               for(size_t isv = 0; isv<nsv; isv++){
                  float* ptr =&(_input_tensors.at(1).second).tensor<float, 3>()(0, isv, 0);
                  *ptr =     nanTozero(float(tanh(vtxP4_SV.at(isv).M()/10)));
                  *(++ptr) = nanTozero(float(tanh(vtxP4_SV.at(isv).Pt()/20)));
                  *(++ptr) = nanTozero(float(ntrack_SV.at(isv)));
                  //*(++ptr) = nanTozero(float(tanh(vtx_lxy.at(isv)/100)));
                  *(++ptr) = nanTozero(float(tanh(vtx_lxysig.at(isv)/1000)));
                  *(++ptr) = nanTozero(float(tanh(kappa_SV.at(isv)/700)));
                  *(++ptr) = nanTozero(float(vtx_chi2.at(isv)));
                  *(++ptr) = nanTozero(float(vtx_costhetadijet.at(isv)));
                  *(++ptr) = nanTozero(float(ntrackjet1_SV.at(isv)));
                  *(++ptr) = nanTozero(float(ntrackjet2_SV.at(isv)));
                  *(++ptr) = nanTozero(float(vtx_costhetaPLxyz.at(isv)));
                  *(++ptr) = nanTozero(float(vtx_meancosthetatrks.at(isv)));
 
                  //*ptr = nanTozero(float(vtxP4_SV.at(isv).M()));
                  //*(++ptr) = nanTozero(float(vtxP4_SV.at(isv).Pt()));
                  //*(++ptr) = nanTozero(float(ntrack_SV.at(isv)));
                  //*(++ptr) = nanTozero(float(vtx_lxy.at(isv)));
                  //*(++ptr) = nanTozero(float(vtx_lxysig.at(isv)));
                  //*(++ptr) = nanTozero(float(kappa_SV.at(isv)));
                  //*(++ptr) = nanTozero(float(vtx_chi2.at(isv)));
                  //*(++ptr) = nanTozero(float(vtx_costhetadijet.at(isv)));
                  //*(++ptr) = nanTozero(float(ntrackjet1_SV.at(isv)));
                  //*(++ptr) = nanTozero(float(ntrackjet2_SV.at(isv)));
                  //*(++ptr) = nanTozero(float(vtx_costhetaPLxyz.at(isv)));
                  //*(++ptr) = nanTozero(float(vtx_meancosthetatrks.at(isv)));
 
                  //_input_tensors[3].second.matrix<float>()(0, isv) = ntrack_SV.at(isv); 
               }


               
               //Fill Track tensor
               size_t ntrk = std::min(ip2d_dijet.size(), (size_t)30);
               for(size_t itrk = 0; itrk<ntrk; itrk++){
                   float* ptr = &(_input_tensors.at(2).second).tensor<float,3>()(0, itrk, 0);
                   //*ptr = nanTozero(float(tanh(ip2d_dijet.at(itrk)/50)));
                   *(ptr) = nanTozero(float(tanh(ip2d_sig_dijet.at(itrk)/1000)));
                   //*(++ptr) = nanTozero(float(tanh(ip3d_dijet.at(itrk)/50)));
                   *(++ptr) = nanTozero(float(tanh(ip3d_sig_dijet.at(itrk)/2000)));
                   *(++ptr) = nanTozero(float(tanh(Lxyexp_dijet.at(itrk)/100)));
                   if(indices_dijet.at(itrk)==1){
                       *(++ptr) = float(1.0); 
                       *(++ptr) = float(0.0);
                   }
                   else{
                       *(++ptr) = float(0.0);
                       *(++ptr) = float(1.0);
                   }

                   *(++ptr) = nanTozero(float(tanh(ip3d_minsig_dijet.at(itrk)/200))); 
                   *(++ptr) = nanTozero(float(dRjet1_dijet.at(itrk)-0.6));
                   *(++ptr) = nanTozero(float(dRjet2_dijet.at(itrk)-0.6));
                   *(++ptr) = nanTozero(float(tanh(energys_dijet.at(itrk)/(trksEnergy_1+trksEnergy_2))));

                   //*ptr = nanTozero(float(ip2d_dijet.at(itrk)));
                   //*(++ptr) = nanTozero(float(ip2d_sig_dijet.at(itrk)));
                   //*(++ptr) = nanTozero(float(ip3d_dijet.at(itrk)));
                   //*(++ptr) = nanTozero(float(ip3d_sig_dijet.at(itrk)));
                   //*(++ptr) = nanTozero(float(Lxyexp_dijet.at(itrk)));
                   //if(indices_dijet.at(itrk)==1){
                   //    *(++ptr) = float(1.0); 
                   //    *(++ptr) = float(0.0);
                   //}
                   //else{
                   //    *(++ptr) = float(0.0);
                   //    *(++ptr) = float(1.0);
                   //}

                   //*(++ptr) = nanTozero(float(ip3d_minsig_dijet.at(itrk))); 
                   //*(++ptr) = nanTozero(float(dRjet1_dijet.at(itrk)-0.6));
                   //*(++ptr) = nanTozero(float(dRjet2_dijet.at(itrk)-0.6));
                   //*(++ptr) = nanTozero(float(energys_dijet.at(itrk)/(trksEnergy_1+trksEnergy_2)));


               }

               // Fill SV to track tensor
               for(size_t itrk = 0; itrk<30; itrk++){
                  for(size_t isv = 0; isv<6; isv++){
                      if(itrk<ip2d_dijet.size() && isv<vtx_lxy.size()){
                          float* ptr = &(_input_tensors.at(3).second).tensor<float, 3>()(0, isv*30+itrk, 0); 
                          
                          *ptr = nanTozero(float(trk_SVassign.at(itrk).at(isv)));
                          *(++ptr) = nanTozero(float(ip3dtanh_wrt_SV.at(itrk).at(isv)));
                          *(++ptr) = nanTozero(float(ip3dsigtanh_wrt_SV.at(itrk).at(isv)));
                          *(++ptr) = nanTozero(float(costheta_wrt_SV.at(itrk).at(isv)));

                        
                      }


                  }

               }
              
 
               std::vector<tensorflow::Tensor> outputs;
               std::vector<tensorflow::Tensor> promptoutputs;
               tensorflow::run(_Dispsession, _input_tensors, {"Identity:0"}, &outputs);
               tensorflow::run(_Promptsession, _input_prompt_tensors, {"Identity:0"}, &promptoutputs);
               SVDNNd.push_back(outputs[0].matrix<float>()(0,0));
               SVDNNp.push_back(promptoutputs[0].matrix<float>()(0,0));
               //std::cout<<promptoutputs[0].matrix<float>()(0,0)<<std::endl;
               //SVDNNd.push_back(outputs[0].matrix<float>()(0,1));
               //std::cout<<outputs[0].matrix<float>()(0,1)<<std::endl;
               

               fullIndices.push_back(indices_full);
               fullenergys.push_back(energys_full);
               fullpts.push_back(pts_full);
               fullIP2D.push_back(ip2d_full);
               fullIP2Dsig.push_back(ip2dsig_full);
               fullIP3D.push_back(ip3d_full);
               fullIP3Dsig.push_back(ip3dsig_full);
               fullIP3Dminsig.push_back(ip3dminsig_full);
               fullPVindex.push_back(pvindex_full);


               dijetIndices.push_back(indices_dijet);
               dijetIP2D.push_back(ip2d_dijet);
               dijetIP2D_sig.push_back(ip2d_sig_dijet);
               dijetLxyexp.push_back(Lxyexp_dijet);

               dijetpts.push_back(pts_dijet);
               dijetetas.push_back(etas_dijet);
               dijetphis.push_back(phis_dijet);
               dijetenergys.push_back(energys_dijet);
               dijetIP3D.push_back(ip3d_dijet);
               dijetIP3D_sig.push_back(ip3d_sig_dijet);
               dijethasSV.push_back(trk_hasSV);
               dijetIP3D_minsig.push_back(ip3d_minsig_dijet);
               dijetPVindex.push_back(pvidx_dijet);
               dijetdRjet1.push_back(dRjet1_dijet);
               dijetdRjet2.push_back(dRjet2_dijet);

               promptIndices.push_back(indices_prompt);
               promptIP2D.push_back(ip2d_prompt);
               promptIP2D_sig.push_back(ip2dsig_prompt);
               promptIP3D.push_back(ip3d_prompt);
               promptIP3D_sig.push_back(ip3dsig_prompt);
               promptpts.push_back(pts_prompt);
               promptenergys.push_back(energys_prompt);
               promptIP3Dminsig.push_back(ip3d_minsig_prompt);
               promptPVidx.push_back(pvidx_prompt);
               promptdRjet1.push_back(dRjet1_prompt);
               promptdRjet2.push_back(dRjet2_prompt);

               dijet_assSV.push_back(trk_SVassign);
               dijet_ip3dwrtSV.push_back(ip3d_wrt_SV);
               dijet_ip3dsigwrtSV.push_back(ip3dsig_wrt_SV);
               dijet_ip3dwrtSVtanh.push_back(ip3dtanh_wrt_SV);
               dijet_ip3dsigwrtSVtanh.push_back(ip3dsigtanh_wrt_SV);
               dijet_costhetawrtSV.push_back(costheta_wrt_SV);



               SVvtxP4.push_back(vtxP4_SV);
               SVvtxnTrack.push_back(ntrack_SV);
               SVvtxntrk_jet1.push_back(ntrackjet1_SV);
               SVvtxntrk_jet2.push_back(ntrackjet2_SV);
               SVenergyfrac_jet1.push_back(EFracJet1_SV);
               SVenergyfrac_jet2.push_back(EFracJet2_SV);
               SVvtxChi2.push_back(vtx_chi2);
               SVvtxlxy.push_back(vtx_lxy);
               SVvtxlxysig.push_back(vtx_lxysig);
               SVvtxlxyz.push_back(vtx_lxyz);
               SVvtxlxyzsig.push_back(vtx_lxyzsig);
               SVcosthetaPLxyz.push_back(vtx_costhetaPLxyz);
               SVmeancosthetatrks.push_back(vtx_meancosthetatrks);

               SVdistwrtgenSV1.push_back(vtx_distgenSV1);
               SVdistwrtgenSV2.push_back(vtx_distgenSV2);
               SVdistsigwrtgenSV1.push_back(vtx_distsiggenSV1);
               SVdistsigwrtgenSV2.push_back(vtx_distsiggenSV2);
               SVdijetdRgenmom1.push_back(vtx_dRgenmom1);
               SVdijetdRgenmom2.push_back(vtx_dRgenmom2);
               SVnSV.push_back(float(nvtx));

               SVIP2D.push_back(ip2d_SV_assign);
               SVIP2D_sig.push_back(ip2dsig_SV_assign);
               SVIP3D.push_back(ip3d_SV_assign);
               SVIP3D_sig.push_back(ip3dsig_SV_assign);
               SVjetidx.push_back(jetidx_SV);
               SVcharges.push_back(charges_SV);
               SVtrkenergy.push_back(trkEnergy_SV);

               SVkappa.push_back(kappa_SV);
               SVkappa_total.push_back(kappa_total);
               SVdijetdR.push_back(vtx_dRdijet);
               SVdijetcostheta.push_back(vtx_costhetadijet);

               SVtoSVdist.push_back(svsvdist);
               SVtoSVdistsig.push_back(svsvdistsig);
               SVtoSVdisttanh.push_back(svsvdisttanh);
               SVtoSVdistsigtanh.push_back(svsvdistsigtanh);
               SVtoSVjet1dR.push_back(svsvjet1dR);
               SVtoSVjet2dR.push_back(svsvjet2dR);
               SVtoSVjet1costheta.push_back(svsvjet1costheta);
               SVtoSVjet2costheta.push_back(svsvjet2costheta);
               
               ////dijetDeltaR.push_back(dR_dijet);

               //SVdijetbestglxyRMS.push_back(Cluster.RMS(dijetbestcluster, lxy));
               //SVdijetbestglxyAvg.push_back(Cluster.Avg(dijetbestcluster)/lxy);
               //SVndijetcluster.push_back(dijetclusters.size());
               //SVdijetbestN.push_back(ClrN1+ClrN2);
               //SVdijetbestN1.push_back(ClrN1);
               //SVdijetbestN2.push_back(ClrN2);
               //promptEnergy_frac   = promptEnergy/(jet1_ref->energy()*jetcorrfac.at(i)+jet2_ref->energy()*jetcorrfac.at(k));

               //promptEnergy_frac_1 = promptEnergy_1/(jet1_ref->energy()*jetcorrfac.at(i));
               //promptEnergy_frac_2 = promptEnergy_2/(jet2_ref->energy()*jetcorrfac.at(k));
               SVjetEnergyFrac.push_back(jetEnergyfrac_SV);//SVtksEnergy/(jet1_ref->energy()*jetcorrfac.at(i)+jet2_ref->energy()*jetcorrfac.at(k));
               
               SVtrksEnergyFrac.push_back(trksEnergyfrac_SV);
      
               SVjetEnergyFrac_total.push_back(jetEnergyfrac_total);
               SVtrksEnergyFrac_total.push_back(trksEnergyfrac_total);
               //svtrkspt_frac = SVtksPt/trksPt;
               //sigpromptEnergy_frac = sigpromptEnergy/(jet1_ref->energy()*jetcorrfac.at(i)+jet2_ref->energy()*jetcorrfac.at(k));
               //sig30promptEnergy_frac = sig30promptEnergy/(jet1_ref->energy()*jetcorrfac.at(i)+jet2_ref->energy()*jetcorrfac.at(k));

               //float PtFrac = vtxP4.Pt()/DJ_physp4.Pt();
               //float dphiDJVX = float(deltaPhi(vtxP4.phi(),DJ_physp4.phi()));
               //float dphiLxyVX = float(deltaPhi(vtxP4.phi(),lxyphi));

               //SVdijetPhyP4.push_back(DJ_physp4);
               //SVdijetPhyPt.push_back(DJ_physp4.Pt());
               //SVPtFrac.push_back(PtFrac);
               //SVdphiDJVX.push_back(dphiDJVX);
               //SVdphiLxyVX.push_back(dphiLxyVX);

                SVjet1Idx.push_back(int(i));
                SVjet2Idx.push_back(int(k));
                SVjet1Pt.push_back(jet1_ref->pt()*jetcorrfac.at(i));
                SVjet1Eta.push_back(jet1_ref->eta());
                SVjet1Phi.push_back(jet1_ref->phi());
                SVjet1PtUp.push_back(jetPtUp.at(i));
                SVjet1PtDown.push_back(jetPtDown.at(i));
                SVjet2Pt.push_back(jet2_ref->pt()*jetcorrfac.at(k));
                SVjet2Eta.push_back(jet2_ref->eta());
                SVjet2Phi.push_back(jet2_ref->phi());
                SVjet2PtUp.push_back(jetPtUp.at(k));
                SVjet2PtDown.push_back(jetPtDown.at(k));

               //SVdisptrksEnergyFrac.push_back(SVtksEnergy/disptrksEnergy);
               //SVtrksPtFrac.push_back(svtrkspt_frac);
               //SVdisptrksPtFrac.push_back(SVtksPt/disptrksPt);

               //SVIP2D.push_back(ip2d_SV_assign);
               //SVIP2D_sig.push_back(ip2d_sig_SV_assign);
               //SVIP3D.push_back(ip3d_SV_assign);
               //SVIP3D_sig.push_back(ip3d_sig_SV_assign);
               //SVIP3D_minsig.push_back(ip3d_minsig_SV_assign);

               SVtrkenergysum.push_back(SV_ESum);
               SVnPrompttk1.push_back(nPrompt_tk1);
               SVnPrompttk2.push_back(nPrompt_tk2);
               SVnPromptTracks.push_back(nPromptTracks);

               //SVpromptEnergy1.push_back(promptEnergy_1);
               //SVpromptEnergy2.push_back(promptEnergy_2);
               //SVpromptEnergy.push_back(promptEnergy);

               jet1trackEnergy.push_back(trksEnergy_1);
               jet1trackPt.push_back(trksPt_1);
               jet2trackEnergy.push_back(trksEnergy_2);
               jet2trackPt.push_back(trksPt_2);
               //dijettrackEnergy.push_back(trksEnergy_1+trksEnergy_2);
               //jet1trackPrompt_EFrac.push_back(promptEnergy_1/trksEnergy_1);
               //jet2trackPrompt_EFrac.push_back(promptEnergy_2/trksEnergy_2);
               //dijettrackPrompt_EFrac.push_back(promptEnergy/(trksEnergy_1+trksEnergy_2));

               //SVpromptEnergyfrac.push_back(promptEnergy_frac);
               //SVpromptEnergyfrac1.push_back(promptEnergy_frac_1);
               //SVpromptEnergyfrac2.push_back(promptEnergy_frac_2);
               //SVsigpromptEnergyfrac.push_back(sigpromptEnergy_frac);
               //SVsig30promptEnergyfrac.push_back(sig30promptEnergy_frac);

               ////SVDijetTag.push_back(dijet_tag);


               SVvtxx.push_back(vtx_x);
               SVvtxy.push_back(vtx_y);
               SVvtxz.push_back(vtx_z);
               //SVvtxx.push_back(jvtx.position().x());
               //SVvtxy.push_back(jvtx.position().y());
               //SVvtxz.push_back(jvtx.position().z());


               //SVvtxlxy.push_back(lxy);
               //SVvtxlxysig.push_back(sig);

               //SVvtxP4.push_back(vtxP4);
               //SVvtxnTrack.push_back(vtx_nTrack);
               //SVposnTrack.push_back(pos_nTrack);

               //SVvtxChi2.push_back(vtx.normalizedChi2());
               ////SVhitsInFrontOfVert.push_back(hitsInFrontOfVert);
               //SVmissHitsAfterVert.push_back(missHitsAfterVert);

      }
   } 
   
   tree->Fill();
   delete(jetUnc);
   
#ifdef THIS_IS_AN_EVENT_EXAMPLE
   Handle<ExampleData> pIn;
   iEvent.getByLabel("example",pIn);
#endif
   
#ifdef THIS_IS_AN_EVENTSETUP_EXAMPLE
   ESHandle<SetupData> pSetup;
   iSetup.get<SetupRecord>().get(pSetup);
#endif
}


// ------------ method called once each job just before starting event loop  ------------
void 
DijetIVFMiniMLDisp_dispprompttensor::beginJob()
{
   tree->Branch("run", &run_, "run/i");
   tree->Branch("lumi", &lumi_, "lumi/i");
   tree->Branch("evt", &evt_, "evt/l");


   tree->Branch("gen_mass", &gen_mass);
   tree->Branch("gen_life", &gen_life);
   tree->Branch("genpdgID", &genpdgID);
   tree->Branch("genpt", &genpt);
   tree->Branch("geneta", &geneta);
   tree->Branch("genphi", &genphi);
   tree->Branch("genenergy", &genenergy);
   tree->Branch("genmompdgID", &genmompdgID);
   tree->Branch("genmompt", &genmompt);
   tree->Branch("genmometa", &genmometa);
   tree->Branch("genmomphi", &genmomphi);
   tree->Branch("genmomenergy", &genmomenergy);
   tree->Branch("genSVx", &genSVx);
   tree->Branch("genSVy", &genSVy);
   tree->Branch("genSVz", &genSVz);
   tree->Branch("genSVlxy", &genSVlxy);
   tree->Branch("genSVlxyz", &genSVlxyz);
   tree->Branch("genSVctau0", &genSVctau0);

   tree->Branch("nPV", &nPV);
   tree->Branch("CaloHT", &CaloHT);
   tree->Branch("jetpt", &jetpt);
   tree->Branch("jetenergy", &jetenergy);
   tree->Branch("jeteta", &jeteta);
   tree->Branch("jetphi", &jetphi);
   tree->Branch("jetPtUp", &jetPtUp);
   tree->Branch("jetPtDown", &jetPtDown);

   tree->Branch("jetassociatedntrks_CALO", &jetassociatedntrks_CALO);
   tree->Branch("jetassociatedntrks_VTX",  &jetassociatedntrks_VTX);
   tree->Branch("jetassociatedntrks_combine", &jetassociatedntrks_combine);

   tree->Branch("jet1trackEnergy", &jet1trackEnergy);
   tree->Branch("jet2trackEnergy", &jet2trackEnergy);
   tree->Branch("dijettrackEnergy", &dijettrackEnergy);
   tree->Branch("jet1trackPrompt_EFrac", &jet1trackPrompt_EFrac);
   tree->Branch("jet2trackPrompt_EFrac", &jet2trackPrompt_EFrac);
   tree->Branch("dijettrackPrompt_EFrac", &dijettrackPrompt_EFrac);

   tree->Branch("fullIndices", &fullIndices);
   tree->Branch("fullenergys", &fullenergys);
   tree->Branch("fullpts", &fullpts);
   tree->Branch("fullIP2D", &fullIP2D);
   tree->Branch("fullIP2Dsig", &fullIP2Dsig);
   tree->Branch("fullIP3D", &fullIP3D);
   tree->Branch("fullIP3Dsig", &fullIP3Dsig);
   tree->Branch("fullIP3Dminsig", &fullIP3Dminsig);
   tree->Branch("fullPVindex", &fullPVindex);

   tree->Branch("dijetIndices", &dijetIndices);
   tree->Branch("dijetIP2D", &dijetIP2D);
   tree->Branch("dijetIP2D_sig", &dijetIP2D_sig);
   tree->Branch("dijetLxyexp", &dijetLxyexp);
   tree->Branch("dijetPreIndices", &dijetPreIndices);
   tree->Branch("dijetPreIP2D", &dijetPreIP2D);
   tree->Branch("dijetPreIP2D_sig", &dijetPreIP2D_sig);

   tree->Branch("dijetpts", &dijetpts);
   tree->Branch("dijetenergys", &dijetenergys);
   tree->Branch("dijetetas", &dijetetas);
   tree->Branch("dijetphis", &dijetphis);
   tree->Branch("dijetIP3D", &dijetIP3D);
   tree->Branch("dijetIP3D_sig", &dijetIP3D_sig);
   tree->Branch("dijetIP3D_minsig", &dijetIP3D_minsig);
   tree->Branch("dijethasSV", &dijethasSV);
   tree->Branch("dijetPVindex", &dijetPVindex);

   tree->Branch("promptIndices", &promptIndices);
   tree->Branch("promptIP2D", &promptIP2D);
   tree->Branch("promptIP2D_sig", &promptIP2D_sig);
   tree->Branch("promptIP3D", &promptIP3D);
   tree->Branch("promptIP3D_sig", &promptIP3D_sig);
   tree->Branch("promptpts", &promptpts);
   tree->Branch("promptenergys", &promptenergys);
   tree->Branch("promptIP3Dminsig", &promptIP3Dminsig);
   tree->Branch("promptPVidx", &promptPVidx);
   tree->Branch("promptdRjet1", &promptdRjet1);
   tree->Branch("promptdRjet2", &promptdRjet2);


   tree->Branch("dijet_assSV", &dijet_assSV);
   tree->Branch("dijet_ip3dwrtSV", &dijet_ip3dwrtSV);
   tree->Branch("dijet_ip3dsigwrtSV", &dijet_ip3dsigwrtSV);
   tree->Branch("dijet_ip3dwrtSVtanh", &dijet_ip3dwrtSVtanh);
   tree->Branch("dijet_ip3dsigwrtSVtanh", &dijet_ip3dsigwrtSVtanh);
   tree->Branch("dijet_costhetawrtSV", &dijet_costhetawrtSV);
   tree->Branch("dijetdRjet1", &dijetdRjet1);
   tree->Branch("dijetdRjet2", &dijetdRjet2);
   //tree->Branch("dijetDeltaR", &dijetDeltaR);

   tree->Branch("SVdijetPhyP4", &SVdijetPhyP4);
   tree->Branch("SVdijetPhyPt", &SVdijetPhyPt);
   tree->Branch("SVPtFrac", &SVPtFrac);
   tree->Branch("SVdphiDJVX", &SVdphiDJVX);
   tree->Branch("SVdphiLxyVX", &SVdphiLxyVX);

   tree->Branch("SVjet1Idx", &SVjet1Idx);
   tree->Branch("SVjet2Idx", &SVjet2Idx);
   tree->Branch("SVPrejet1Pt", &SVPrejet1Pt);
   tree->Branch("SVjet1Pt", &SVjet1Pt);
   tree->Branch("SVjet1PtUp", &SVjet1PtUp);
   tree->Branch("SVjet1PtDown", &SVjet1PtDown);
   tree->Branch("SVjet1Eta", &SVjet1Eta);
   tree->Branch("SVjet1phi", &SVjet1Phi);
   tree->Branch("SVPrejet2Pt", &SVPrejet2Pt);
   tree->Branch("SVjet2Pt", &SVjet2Pt);
   tree->Branch("SVjet2Eta", &SVjet2Eta);
   tree->Branch("SVjet2Phi", &SVjet2Phi);
   tree->Branch("SVjet2PtUp", &SVjet2PtUp);
   tree->Branch("SVjet2PtDown", &SVjet2PtDown);
   tree->Branch("SVnSV", &SVnSV);
   tree->Branch("SVIP2D", &SVIP2D);
   tree->Branch("SVIP2D_sig", &SVIP2D_sig);

   tree->Branch("SVIP3D", &SVIP3D);
   tree->Branch("SVIP3D_sig", &SVIP3D_sig);
   tree->Branch("SVIP3D_minsig", &SVIP3D_minsig);
   tree->Branch("SVjetidx", &SVjetidx);
   tree->Branch("SVcharges", &SVcharges);
   tree->Branch("SVtrkenergy", &SVtrkenergy);

   tree->Branch("SVtrkenergysum", &SVtrkenergysum);
   tree->Branch("SVnPrompttk1", &SVnPrompttk1);
   tree->Branch("SVnPrompttk2", &SVnPrompttk2);
   tree->Branch("SVnPromptTracks", &SVnPromptTracks);

   tree->Branch("SVpromptEnergy1", &SVpromptEnergy1);
   tree->Branch("SVpromptEnergy2", &SVpromptEnergy2);
   tree->Branch("SVpromptEnergy", &SVpromptEnergy);

   tree->Branch("SVjetEnergyFrac", &SVjetEnergyFrac);
   tree->Branch("SVtrksEnergyFrac", &SVtrksEnergyFrac);
   tree->Branch("SVjetEnergyFrac_total", &SVjetEnergyFrac_total);
   tree->Branch("SVtrksEnergyFrac_total", &SVtrksEnergyFrac_total);
   tree->Branch("SVdisptrksEnergyFrac", &SVdisptrksEnergyFrac);
   tree->Branch("SVtrksPtFrac", &SVtrksPtFrac);
   tree->Branch("SVdisptrksPtFrac", &SVtrksPtFrac);

   tree->Branch("SVpromptEnergyfrac", &SVpromptEnergyfrac);
   tree->Branch("SVpromptEnergyfrac1", &SVpromptEnergyfrac1);
   tree->Branch("SVpromptEnergyfrac2", &SVpromptEnergyfrac2);
   tree->Branch("SVsigpromptEnergyfrac", &SVsigpromptEnergyfrac);
   tree->Branch("SVsig30promptEnergyfrac", &SVsig30promptEnergyfrac);


   tree->Branch("SVvtxx", &SVvtxx);
   tree->Branch("SVvtxy", &SVvtxy);
   tree->Branch("SVvtxz", &SVvtxz);

   tree->Branch("SVvtxlxy", &SVvtxlxy);
   tree->Branch("SVvtxlxysig", &SVvtxlxysig);
   tree->Branch("SVcosthetaPLxyz", &SVcosthetaPLxyz);
   tree->Branch("SVmeancosthetatrks", &SVmeancosthetatrks);
   tree->Branch("SVdistwrtgenSV1", &SVdistwrtgenSV1);
   tree->Branch("SVdistwrtgenSV2", &SVdistwrtgenSV2);
   tree->Branch("SVdistsigwrtgenSV1", &SVdistsigwrtgenSV1);
   tree->Branch("SVdistsigwrtgenSV2", &SVdistsigwrtgenSV2);

   tree->Branch("SVdijetdRgenmom1", &SVdijetdRgenmom1);
   tree->Branch("SVdijetdRgenmom2", &SVdijetdRgenmom2);
   
   tree->Branch("SVvtxP4", &SVvtxP4);

   tree->Branch("SVvtxnTrack", &SVvtxnTrack);
   tree->Branch("SVvtxntrk_jet1", &SVvtxntrk_jet1);
   tree->Branch("SVvtxntrk_jet2", &SVvtxntrk_jet2);
   tree->Branch("SVenergyfrac_jet1", &SVenergyfrac_jet1);
   tree->Branch("SVenergyfrac_jet2", &SVenergyfrac_jet2);

   tree->Branch("SVposnTrack", &SVposnTrack);

   tree->Branch("SVvtxChi2", &SVvtxChi2);

   tree->Branch("SVkappa", &SVkappa);
   tree->Branch("SVkappa_total", &SVkappa_total);
   tree->Branch("SVdijetdR", &SVdijetdR);
   tree->Branch("SVdijetcostheta", &SVdijetcostheta);

   tree->Branch("SVDNNp", &SVDNNp);
   tree->Branch("SVDNNd", &SVDNNd);


   tree->Branch("SVtoSVdist", &SVtoSVdist);
   tree->Branch("SVtoSVdistsig", &SVtoSVdistsig);
   tree->Branch("SVtoSVdisttanh", &SVtoSVdisttanh);
   tree->Branch("SVtoSVdistsigtanh", &SVtoSVdistsigtanh);
   tree->Branch("SVtoSVjet1dR", &SVtoSVjet1dR);
   tree->Branch("SVtoSVjet2dR", &SVtoSVjet2dR);
   tree->Branch("SVtoSVjet1costheta", &SVtoSVjet1costheta);
   tree->Branch("SVtoSVjet2costheta", &SVtoSVjet2costheta);


   tree->Branch("SVdijetbestglxyRMS", &SVdijetbestglxyRMS);
   tree->Branch("SVdijetbestglxyAvg", &SVdijetbestglxyAvg);
   tree->Branch("SVndijetcluster", &SVndijetcluster);

   tree->Branch("SVdijetbestN", &SVdijetbestN);
   tree->Branch("SVdijetbestN1", &SVdijetbestN1);
   tree->Branch("SVdijetbestN2", &SVdijetbestN2);

   tree->Branch("TrueDijet", &TrueDijet);
   tree->Branch("jet1pdgID", &jet1pdgID);
   tree->Branch("jet2pdgID", &jet2pdgID);
   tree->Branch("jet1mompdgID", &jet1mompdgID);
   tree->Branch("jet2mompdgID", &jet2mompdgID);


   tree->Branch("jet1genpt",           &jet1genpt);
   tree->Branch("jet1geneta",          &jet1geneta); 
   tree->Branch("jet1genphi",          &jet1genphi);
   tree->Branch("jet1genenergy",       &jet1genenergy);
   tree->Branch("jet2genpt",           &jet2genpt);
   tree->Branch("jet2geneta",          &jet2geneta);
   tree->Branch("jet2genphi",          &jet2genphi);
   tree->Branch("jet2genenergy",       &jet2genenergy);
   tree->Branch("dijetgenSVx1",        &dijetgenSVx1);
   tree->Branch("dijetgenSVy1",        &dijetgenSVy1);
   tree->Branch("dijetgenSVz1",        &dijetgenSVz1);
   tree->Branch("dijetgenSVlxy1",      &dijetgenSVlxy1);
   tree->Branch("dijetgenSVlxyz1",     &dijetgenSVlxyz1);
   tree->Branch("dijetgenSVctau01",    &dijetgenSVctau01);
   tree->Branch("dijetgenSVx2",        &dijetgenSVx2);
   tree->Branch("dijetgenSVy2",        &dijetgenSVy2);
   tree->Branch("dijetgenSVz2",        &dijetgenSVz2);
   tree->Branch("dijetgenSVlxy2",      &dijetgenSVlxy2);
   tree->Branch("dijetgenSVlxyz2",     &dijetgenSVlxyz2);
   tree->Branch("dijetgenSVctau02",    &dijetgenSVctau02);



   tree->Branch("HLT_IsoMu24_v",                                         &pass_HLT_IsoMu24_);
   tree->Branch("HLT_IsoTkMu24_v",                                       &pass_HLT_IsoTkMu24_);
   tree->Branch("HLT_HT200_v",                                           &pass_HLT_HT200_);
   tree->Branch("HLT_HT275_v",                                           &pass_HLT_HT275_);
   tree->Branch("HLT_HT325_v",                                           &pass_HLT_HT325_);
   tree->Branch("HLT_HT425_v",                                           &pass_HLT_HT425_);
   tree->Branch("HLT_HT575_v",                                           &pass_HLT_HT575_);
   tree->Branch("HLT_HT650_v",                                           &pass_HLT_HT650_);
   tree->Branch("HLT_L1Mu6HT240_v",                                      &pass_HLT_L1Mu6HT240_);

   tree->Branch("HLT_HT430_DisplacedDijet40_DisplacedTrack_v",           &pass_HLT_HT430_DisplacedDijet40_DisplacedTrack_);
   tree->Branch("HLT_HT430_DisplacedDijet60_DisplacedTrack_v",           &pass_HLT_HT430_DisplacedDijet60_DisplacedTrack_);

   tree->Branch("HLT_HT400_DisplacedDijet40_Inclusive_v",                &pass_HLT_HT400_DisplacedDijet40_Inclusive_);
   tree->Branch("HLT_HT500_DisplacedDijet40_Inclusive_v",                &pass_HLT_HT500_DisplacedDijet40_Inclusive_);
   tree->Branch("HLT_HT550_DisplacedDijet40_Inclusive_v",                &pass_HLT_HT550_DisplacedDijet40_Inclusive_);
   tree->Branch("HLT_HT650_DisplacedDijet60_Inclusive_v",                &pass_HLT_HT650_DisplacedDijet60_Inclusive_);
   tree->Branch("HLT_HT650_DisplacedDijet80_Inclusive_v",                &pass_HLT_HT650_DisplacedDijet80_Inclusive_);
   tree->Branch("HLT_HT750_DisplacedDijet80_Inclusive_v",                &pass_HLT_HT750_DisplacedDijet80_Inclusive_);

   tree->Branch("HLT_HT430_DisplacedDijet30_Inclusive1PtrkShortSig5_v",                        &pass_HLT_HT430_DisplacedDijet30_Inclusive1PtrkShortSig5_);
   tree->Branch("HLT_HT430_DisplacedDijet35_Inclusive1PtrkShortSig5_v",                        &pass_HLT_HT430_DisplacedDijet35_Inclusive1PtrkShortSig5_);
   tree->Branch("HLT_HT430_DisplacedDijet40_Inclusive1PtrkShortSig5_v",                        &pass_HLT_HT430_DisplacedDijet40_Inclusive1PtrkShortSig5_);
   tree->Branch("HLT_Mu6HT240_DisplacedDijet30_Inclusive0PtrkShortSig5_v",                     &pass_HLT_Mu6HT240_DisplacedDijet30_Inclusive0PtrkShortSig5_);
   tree->Branch("HLT_Mu6HT240_DisplacedDijet30_Inclusive1PtrkShortSig5_DisplacedLoose_v",      &pass_HLT_Mu6HT240_DisplacedDijet30_Inclusive1PtrkShortSig5_DisplacedLoose_);
   tree->Branch("HLT_Mu6HT240_DisplacedDijet35_Inlcusive0PtrkShortSig5_v",                     &pass_HLT_Mu6HT240_DisplacedDijet35_Inlcusive0PtrkShortSig5_);
   tree->Branch("HLT_Mu6HT240_DisplacedDijet35_Inclusive1PtrkShortSig5_DisplacedLoose_v",      &pass_HLT_Mu6HT240_DisplacedDijet35_Inclusive1PtrkShortSig5_DisplacedLoose_);
   tree->Branch("HLT_Mu6HT240_DisplacedDijet40_Inclusive0PtrkShortSig5_v",                     &pass_HLT_Mu6HT240_DisplacedDijet40_Inclusive0PtrkShortSig5_);
   tree->Branch("HLT_Mu6HT240_DisplacedDijet40_Inclusive1PtrkShortSig5_DisplacedLoose_v",      &pass_HLT_Mu6HT240_DisplacedDijet40_Inclusive1PtrkShortSig5_DisplacedLoose_);
   tree->Branch("HLT_HT430_DelayedJet40_DoubleDelay0p5nsTrackless_v",                          &pass_HLT_HT430_DelayedJet40_DoubleDelay0p5nsTrackless_);
   tree->Branch("HLT_HT430_DelayedJet40_DoubleDelay1nsInclusive_v",                            &pass_HLT_HT430_DelayedJet40_DoubleDelay1nsInclusive_);
   tree->Branch("HLT_HT430_DelayedJet40_SingleDelay1nsTrackless_v",                            &pass_HLT_HT430_DelayedJet40_SingleDelay1nsTrackless_);
   tree->Branch("HLT_HT430_DelayedJet40_SingleDelay2nsInclusive_v",                            &pass_HLT_HT430_DelayedJet40_SingleDelay2nsInclusive_);                          





   

}

// ------------ method called once each job just after ending the event loop  ------------
void 
DijetIVFMiniMLDisp_dispprompttensor::endJob() 
{
}

// ------------ method called when starting to processes a luminosity block  ------------
// 
void
DijetIVFMiniMLDisp_dispprompttensor::beginLuminosityBlock(edm::LuminosityBlock const& iLumi, edm::EventSetup const& iSetup)
{  

   if(getgeninfo_){
       edm::Handle<GenLumiInfoHeader> gen_header;
       iLumi.getByToken(genLumiHeaderToken_, gen_header);
       std::string comments = gen_header->configDescription();
       std::cout<<comments<<std::endl;
       std::vector<std::string> fields;
       process(comments, '_', fields);
       if(fields.size()>4){ 
           std::string massstr = fields.at(3);
           std::string lifestr = fields.at(4);
           std::vector<std::string> finmass;
           std::vector<std::string> finlife;
           process(massstr, '-', finmass);
           process(lifestr, '-', finlife);
           gen_mass = std::stod(finmass[1]);
           gen_life = std::stod(finlife[1]);
           std::cout<<gen_mass<<","<<gen_life<<std::endl;
       }
  }

 
}

void 
DijetIVFMiniMLDisp_dispprompttensor::endLuminosityBlock(edm::LuminosityBlock const& iLumi, edm::EventSetup const& iSetup)
{}





// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
DijetIVFMiniMLDisp_dispprompttensor::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();

  edm::ParameterSetDescription clusterizer;
        clusterizer.add<double>("seedMax3DIPSignificance", 9999.0);
        clusterizer.add<double>("seedMax3DIPValue", 9999.0);
        clusterizer.add<double>("seedMin3DIPSignificance", 1.2);
        clusterizer.add<double>("seedMin3DIPValue", 0.005);
        clusterizer.add<double>("clusterMaxDistance", 0.1);
        clusterizer.add<double>("clusterMaxSignificance", 4.5);
        clusterizer.add<double>("distanceRatio", 20.0);
        clusterizer.add<double>("clusterMinAngleCosine", 0.0);
        clusterizer.add<double>("maxTimeSignificance", 3.5);
      desc.add<edm::ParameterSetDescription>("clusterizer", clusterizer);

  descriptions.addDefault( desc);
}

void  
DijetIVFMiniMLDisp_dispprompttensor::jettracks (JetTrks* fAssociation, const edm::Handle<edm::View<reco::Jet> >&  jetcoll, const std::vector<reco::Track>& tracks, float cone){

 
    for (unsigned ijet=0; ijet<jetcoll->size(); ijet++){
        edm::RefToBase<reco::Jet> ijet_ref = jetcoll->refAt(ijet);
        reco::TrackRefVector  associated;
        for (unsigned itrk = 0; itrk < tracks.size(); itrk++){
            if (float(deltaR(ijet_ref->eta(), ijet_ref->phi(), tracks[itrk].eta(), tracks[itrk].phi()))<cone){
                //reco::TrackRef tmptrkref = edm::RefToBase<reco::Track>(itrk);
                associated.push_back(reco::TrackRef(&tracks, itrk));
            }

        }

        reco::JetTracksAssociation::setValue(fAssociation, ijet_ref, associated);

    }
    
}

void 
DijetIVFMiniMLDisp_dispprompttensor::vertexMerge(std::vector<TransientVertex> &VTXs, double maxFraction, double minSignificance){
    VertexDistance3D dist;
    for(std::vector<TransientVertex>::iterator sv = VTXs.begin(); sv != VTXs.end(); ++sv){
        bool shared = false;
        VertexState s1 = sv->vertexState();//(RecoVertex::convertPos(sv->pos()), RecoVertex::convertError(sv->posError()));
        for(std::vector<TransientVertex>::iterator sv2 = VTXs.begin(); sv2 != VTXs.end(); ++sv2){
        VertexState s2 = sv2->vertexState();
        double fr = vertexTools::computeSharedTracks(reco::Vertex(*sv2), reco::Vertex(*sv));
        //std::cout<<"shared fraction: "<<fr<<std::endl;
        if (fr > maxFraction && dist.distance(s1, s2).significance()<minSignificance && sv-sv2!=0 && fr >= vertexTools::computeSharedTracks(reco::Vertex(*sv), reco::Vertex(*sv2))){
            shared = true;
        } 
    
      //  std::cout<<"shared fraction: "<<fr<<";distance: "<<dist.distance(s1, s2).value()<< 
      //  "; distance sig: "<<dist.distance(s1, s2).significance()<<"; inverse fr: "<<vertexTools::computeSharedTracks(reco::Vertex(*sv), reco::Vertex(*sv2))<<"; shared: "<<shared<<std::endl;
    } 
   
    if (shared){
        sv = VTXs.erase(sv) - 1;
    }
}

}


std::vector<TransientVertex> 
DijetIVFMiniMLDisp_dispprompttensor::TrackVertexRefit(std::vector<reco::TransientTrack> &Tracks, std::vector<TransientVertex> &VTXs){
    AdaptiveVertexFitter theAVF(GeometricAnnealing(3, 256, 0.25),
				DefaultLinearizationPointFinder(),
                                         KalmanVertexUpdator<5>(),
                                         KalmanVertexTrackCompatibilityEstimator<5>(),
                                         KalmanVertexSmoother());
 
  std::vector<TransientVertex> newVTXs;

  for(std::vector<TransientVertex>::const_iterator sv = VTXs.begin(); sv != VTXs.end(); ++sv){
      GlobalPoint ssv = sv->position();
      reco::Vertex tmpvtx = reco::Vertex(*sv);
      std::vector<reco::TransientTrack> selTrks; 
      for(std::vector<reco::TransientTrack>::const_iterator trk = Tracks.begin(); trk!=Tracks.end(); ++trk){
          Measurement1D ip3d = IPTools::absoluteImpactParameter3D(*trk, tmpvtx).second;
          if(ip3d.significance()<5.0 || sv->trackWeight(*trk)>0.5){
              selTrks.push_back(*trk);
          }
      }
      
      if(selTrks.size()>=2){
          TransientVertex newsv = theAVF.vertex(selTrks, ssv);
          if(isGoodVtx(newsv)) newVTXs.push_back(newsv);
      }
  
  }


  return newVTXs;
}

bool 
DijetIVFMiniMLDisp_dispprompttensor::isGoodVtx(TransientVertex& tVTX){

   reco::Vertex tmpvtx(tVTX);
   return (tVTX.isValid() &&
    !tmpvtx.isFake() &&
    (tmpvtx.nTracks(vtxweight_)>1) &&
    (tmpvtx.normalizedChi2()>0) &&
    (tmpvtx.normalizedChi2()<5));
}

std::vector<size_t> 
DijetIVFMiniMLDisp_dispprompttensor::OrderTracks(const reco::TrackRefVector&  inputTracks, const reco::Vertex& pv, const TransientTrackBuilder& theB){
  //std::vector<size_t> ordered_idx;
  std::vector<float> fabs_ip2dsig;
  for(auto const &itrk: inputTracks){
      reco::TransientTrack t_trk = theB.build(itrk);
      Measurement1D absip2d = IPTools::absoluteTransverseImpactParameter(t_trk, pv).second;
      fabs_ip2dsig.push_back(absip2d.significance());       
   }
  
  return inversesort_indexes(fabs_ip2dsig);

}


std::vector<size_t>
DijetIVFMiniMLDisp_dispprompttensor::OrderSVs(const std::vector<TransientVertex> & inputvtx, const reco::Vertex& pv){
    std::vector<float> lxysig;
    for(auto const itvtx: inputvtx){
        reco::Vertex tmpvtx(itvtx);
        ROOT::Math::SVector<double, 3> vector(tmpvtx.position().x()-pv.x(), tmpvtx.position().y()-pv.y(), 0);
        
        float lxy = float(ROOT::Math::Mag(vector));
      
        reco::Candidate::CovarianceMatrix matrix = tmpvtx.covariance()+pv.covariance();
        
        float lxyerr = sqrt(ROOT::Math::Similarity(matrix, vector))/lxy;
        lxysig.push_back(lxy/lxyerr);
        

    }

    return inversesort_indexes(lxysig);

}

void
DijetIVFMiniMLDisp_dispprompttensor::process(std::string line, char delim, std::vector<std::string>& fields){

    std::stringstream ss(line);
    std::string field;
    while(getline(ss,field,delim)){
        fields.push_back(field);
    }
}


float 
DijetIVFMiniMLDisp_dispprompttensor::nanTozero(float input){
    if(std::isnan(input)) return 0;
    else return input;

}

//define this as a plug-in
DEFINE_FWK_MODULE(DijetIVFMiniMLDisp_dispprompttensor);
