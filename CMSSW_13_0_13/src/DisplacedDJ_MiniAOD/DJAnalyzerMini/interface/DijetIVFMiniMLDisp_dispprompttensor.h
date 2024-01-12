#ifndef DisplacedDJ_MiniAOD_DJAnalyzerMini_DijetMVMini_hh
#define DisplacedDJ_MiniAOD_DJAnalyzerMini_DijetMVMini_hh


#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/one/EDAnalyzer.h"
#include "FWCore/Framework/interface/LuminosityBlock.h"


#include "FWCore/Utilities/interface/InputTag.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"

#include "DataFormats/JetReco/interface/CaloJet.h"
#include "DataFormats/JetReco/interface/CaloJetCollection.h"
#include "DataFormats/JetReco/interface/PFJet.h"
#include "DataFormats/JetReco/interface/PFJetCollection.h"

#include "DataFormats/JetReco/interface/GenJet.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "DataFormats/JetReco/interface/PFJetCollection.h"
#include "DataFormats/BTauReco/interface/JetTag.h"
#include "DataFormats/PatCandidates/interface/PATObject.h"
#include "DataFormats/PatCandidates/interface/PackedCandidate.h"
#include "DataFormats/PatCandidates/interface/PackedGenParticle.h"

//class declaration

//TFile Service

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"


//Pat Jet
//#include "DataFormats/PatCandidates/interface/Jet.h"

//Track Associate
//#include "SimTracker/TrackAssociation/interface/TrackAssociatorBase.h"
#include "DataFormats/Common/interface/AssociationVector.h"
#include "DataFormats/JetReco/interface/JetTracksAssociation.h"
//#include "SimTracker/Records/interface/TrackAssociatorRecord.h"
//#include "SimTracker/TrackAssociation/interface/TrackAssociatorByChi2.h"
//#include "SimTracker/TrackAssociation/interface/TrackAssociatorByHits.h"

//Transient Track
#include "TrackingTools/TransientTrack/interface/TransientTrackBuilder.h"
#include "TrackingTools/Records/interface/TransientTrackRecord.h"
#include "MagneticField/Engine/interface/MagneticField.h"


//Transient Vertex
#include "RecoVertex/VertexPrimitives/interface/TransientVertex.h"


//IPTOOLS
#include "TrackingTools/IPTools/interface/IPTools.h"


//Vertex Fitter
#include "RecoVertex/ConfigurableVertexReco/interface/ConfigurableVertexFitter.h"
#include "RecoVertex/ConfigurableVertexReco/interface/ConfigurableVertexReconstructor.h"

//Hit Pattern
#include "PhysicsTools/RecoUtils/interface/CheckHitPattern.h"
//#include "RecoTracker/DebugTools/interface/FixTrackHitPattern.h"
//#include "RecoTracker/DebugTools/interface/GetTrackTrajInfo.h"

//ROOT
#include "TTree.h"

#include "math.h"

//Measurement1D
#include "DataFormats/GeometryCommonDetAlgo/interface/Measurement1D.h"


//Trigger
#include "DataFormats/Common/interface/TriggerResults.h"
#include "FWCore/Common/interface/TriggerNames.h"
#include "DataFormats/HLTReco/interface/TriggerObject.h"
#include "DataFormats/HLTReco/interface/TriggerEvent.h"
#include "DataFormats/HLTReco/interface/TriggerEventWithRefs.h"
#include "HLTrigger/HLTcore/interface/HLTConfigProvider.h"

//GenParticle
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"

//Navigation School
#include "TrackingTools/DetLayers/interface/NavigationSchool.h"
#include "RecoTracker/Record/interface/NavigationSchoolRecord.h"

//Jet Tracks Association
#include "DataFormats/JetReco/interface/JetTracksAssociation.h"

//DeltaR Calculation
#include "DataFormats/Math/interface/deltaR.h"
#include "DataFormats/Math/interface/deltaPhi.h"

//Cluster Algorithm
//#include "DisplacedDJ/AnlDisplacedJet/interface/cluster.h"
#include "DisplacedDJ_MiniAOD/DJAnalyzerMini/interface/cluster.h"

//Pileup and PDF Information
#include "SimDataFormats/PileupSummaryInfo/interface/PileupSummaryInfo.h"
#include "SimDataFormats/GeneratorProducts/interface/PdfInfo.h"
#include "SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h"

//Jet Corrections and Uncertainty
#include "CondFormats/JetMETObjects/interface/JetCorrectionUncertainty.h"
#include "CondFormats/JetMETObjects/interface/JetCorrectorParameters.h"
#include "JetMETCorrections/Objects/interface/JetCorrectionsRecord.h"
#include "JetMETCorrections/JetCorrector/interface/JetCorrector.h"

#include "RecoVertex/AdaptiveVertexFinder/interface/TracksClusteringFromDisplacedSeed.h"
#include "RecoVertex/AdaptiveVertexFinder/interface/VertexMerging.h"



#include "DataFormats/Math/interface/deltaR.h"
#include "DataFormats/Math/interface/deltaPhi.h"

#include "RecoVertex/VertexTools/interface/SharedTracks.h"
#include "RecoVertex/VertexPrimitives/interface/VertexState.h"
#include "RecoVertex/VertexPrimitives/interface/ConvertToFromReco.h"

#include "RecoVertex/AdaptiveVertexFit/interface/AdaptiveVertexFitter.h"
#include "RecoVertex/KalmanVertexFit/interface/KalmanVertexUpdator.h"
#include "RecoVertex/KalmanVertexFit/interface/KalmanVertexTrackCompatibilityEstimator.h"
#include "RecoVertex/KalmanVertexFit/interface/KalmanVertexSmoother.h"

#include "PhysicsTools/TensorFlow/interface/TensorFlow.h"

#include "SimDataFormats/GeneratorProducts/interface/GenLumiInfoHeader.h"

#include <TVector3.h>


 typedef reco::JetTracksAssociation::Container JetTrks; 

class DijetIVFMiniMLDisp_dispprompttensor : public edm::one::EDAnalyzer<edm::one::WatchLuminosityBlocks,
                                                                 edm::one::SharedResources>  { 
   public:
  
      explicit DijetIVFMiniMLDisp_dispprompttensor(const edm::ParameterSet&);
      ~DijetIVFMiniMLDisp_dispprompttensor();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);
     // typedef std::pair<edm::RefToBase<reco::CaloJet>,  std::vector<reco::Track> > JetTrkPair;

   private:
      void beginJob() override;
      void analyze(const edm::Event&, const edm::EventSetup&) override;
      void endJob() override;
      void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;
      void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;
      float dR(float, float, float, float);
      reco::TrackRefVector MergeTracks(reco::TrackRefVector, reco::TrackRefVector);
      void jettracks (JetTrks*, const edm::Handle<edm::View<reco::Jet> > &, const std::vector<reco::Track> &, float); 
      void vertexMerge(std::vector<TransientVertex> &, double, double );
      std::vector<TransientVertex> TrackVertexRefit(std::vector<reco::TransientTrack> &, std::vector<TransientVertex> &);
      std::vector<size_t> OrderTracks(const reco::TrackRefVector &, const reco::Vertex&, const TransientTrackBuilder& );
      std::vector<size_t> OrderSVs(const std::vector<TransientVertex> &, const reco::Vertex&);
      void process(std::string, char, std::vector<std::string>& );
      float nanTozero(float );      

      bool isGoodVtx(TransientVertex &);
      

      const edm::ESGetToken<TransientTrackBuilder, TransientTrackRecord> theTTBToken;
      edm::EDGetTokenT<GenLumiInfoHeader> genLumiHeaderToken_;
      edm::EDGetTokenT<pat::PackedCandidateCollection> TrackCollT_;
      edm::EDGetTokenT<pat::PackedCandidateCollection> LostTrackCollT_;
      edm::EDGetTokenT<edm::View<reco::Jet> > jet_collT_;
      edm::EDGetTokenT<edm::View<reco::CaloJet> > calojet_collT_;
      edm::EDGetTokenT<reco::VertexCollection> PVCollT_;
      edm::EDGetTokenT<GenEventInfoProduct> genEvtInfoT_;
      edm::EDGetTokenT<edm::View<reco::GenParticle>> genCollT_;
      edm::EDGetTokenT<std::vector<PileupSummaryInfo>> PupInfoT_;
      edm::EDGetTokenT<reco::JetCorrector> jetCorrT_;

      edm::ParameterSet vtxconfig_;
      //ConfigurableVertexFitter vtxmaker_;
      ConfigurableVertexReconstructor vtxmaker_;
      //VertexMerging first_merging;
   

      double JetPtCut_;
      double TrackPtCut_;
      double vtxweight_;
      bool dataMC_;
      bool firstEvent_;

      edm::EDGetTokenT<edm::TriggerResults>    trigresultsToken_;
      //edm::EDGetTokenT<reco::JetTracksAssociationCollection> assocCALOToken_;
      //edm::EDGetTokenT<reco::JetTracksAssociationCollection> assocVTXToken_;

      //bool JTACALO_;
      //bool JTAVTX_;
      //bool JTACombine_;
      bool runtrigger_;
      bool isMC_;
      bool getgeninfo_;
      bool checkHitOpt_;
      bool pdfReweight_;

      std::string JECTag_;
      const edm::ESGetToken<JetCorrectorParametersCollection, JetCorrectionsRecord> theJECToken;

      std::unique_ptr<TracksClusteringFromDisplacedSeed> clusterizer;
      //std::unique_ptr<VertexMerging> first_merging;
      unsigned int run_;
      unsigned int lumi_;
      unsigned int evt_;

      double gen_mass;
      double gen_life;
      
      TTree *tree;

      //edm::ESHandle<TransientTrackBuilder> theB;
      tensorflow::GraphDef* _DispgraphDef;
      tensorflow::GraphDef* _PromptgraphDef;
      tensorflow::Session* _Dispsession;
      tensorflow::Session* _Promptsession;

      //Gen Particle Information

      float nPU;
      float CT14Weight0;
      float MMHT2014Weight0;
      float NNPDF30Weight0;

      std::vector<float> CT14Weight;
      std::vector<float> MMHT2014Weight;
      std::vector<float> NNPDF30Weight;

      std::vector<float> genSVx;
      std::vector<float> genSVy;
      std::vector<float> genSVz;
      std::vector<float> genSVlxy; 
      std::vector<float> genSVlxyz;
      std::vector<float> genSVctau0;
      std::vector<int>   genpdgID;
      std::vector<float> genpt;
      std::vector<float> geneta;
      std::vector<float> genphi;
      std::vector<float> genenergy;
      std::vector<int>   genmompdgID;
      std::vector<float> genmompt;
      std::vector<float> genmometa;
      std::vector<float> genmomphi;
      std::vector<float> genmomenergy;
    
      
      //std::vector<float> momvx;
      //std::vector<float> momvy;
      //std::vector<float> momvz;
      //std::vector<float> momEta;
      //std::vector<float> momPhi;
      //std::vector<float> momPt;
      //std::vector<float> momBeta;
      //std::vector<float> momGamma;
      //std::vector<float> momEnergy;
      //std::vector<int>   mompdgID;
      //std::vector<float> momCtau0; 
    
      //std::vector<float> genLxy;
      //std::vector<float> genLxyz;
      //
      //std::vector<float> genParticlePt;
     
    
      float CaloHT;
      float CaloHTup;
      float CaloHTdown;
      int nPV;

      static constexpr size_t max_sv = 6;
      size_t max_NSV = max_sv;
     
      std::vector<double> jetcorrfac; 
      std::vector<float> jetpt;
      std::vector<float> jetenergy;
      std::vector<float> jeteta;
      std::vector<float> jetphi;
      std::vector<float> jetPtUp;
      std::vector<float> jetPtDown;

      std::vector<int> jetassociatedntrks_CALO;
      std::vector<int> jetassociatedntrks_VTX;
      std::vector<int> jetassociatedntrks_combine;

      std::vector<std::vector<int> > dijetPreIndices;
      std::vector<std::vector<float> > dijetPreIP2D;
      std::vector<std::vector<float> > dijetPreIP2D_sig;

      std::vector<std::vector<int> > fullIndices;
      std::vector<std::vector<float> > fullenergys;
      std::vector<std::vector<float> > fullpts; 
      std::vector<std::vector<float> > fullIP2D;
      std::vector<std::vector<float> > fullIP2Dsig;
      std::vector<std::vector<float> > fullIP3D;
      std::vector<std::vector<float> > fullIP3Dsig;
      std::vector<std::vector<float> > fullIP3Dminsig;
      std::vector<std::vector<int> > fullPVindex;

      std::vector<std::vector<int> > dijetIndices;      
      std::vector<std::vector<float> > dijetIP2D;
      std::vector<std::vector<float> > dijetIP2D_sig;
   
      std::vector<std::vector<float> > dijetLxyexp; 

      std::vector<std::vector<float> > dijetpts;
      std::vector<std::vector<float> > dijetenergys;
      std::vector<std::vector<float> > dijetetas;
      std::vector<std::vector<float> > dijetphis;

      std::vector<std::vector<float> > dijetIP3D;
      std::vector<std::vector<float> > dijetIP3D_sig;
      std::vector<std::vector<bool> >  dijethasSV;
     
      std::vector<std::vector<float> > dijetIP3D_minsig;
      std::vector<std::vector<int> > dijetPVindex;
      std::vector<std::vector<float> > dijetdRjet1;
      std::vector<std::vector<float> > dijetdRjet2;

      std::vector<std::vector<int> >   promptIndices;
      std::vector<std::vector<float> > promptIP2D;
      std::vector<std::vector<float> > promptIP2D_sig;
      std::vector<std::vector<float> > promptIP3D;
      std::vector<std::vector<float> > promptIP3D_sig;
      std::vector<std::vector<float> > promptpts;
      std::vector<std::vector<float> > promptenergys;
      std::vector<std::vector<float> > promptIP3Dminsig;
      std::vector<std::vector<int> >   promptPVidx;
      std::vector<std::vector<float> > promptdRjet1;
      std::vector<std::vector<float> > promptdRjet2;
   
      

      std::vector<std::vector<std::vector<int> > > dijet_assSV;
      std::vector<std::vector<std::vector<float> > > dijet_ip3dwrtSV;
      std::vector<std::vector<std::vector<float> > > dijet_ip3dsigwrtSV;
      std::vector<std::vector<std::vector<float> > > dijet_ip3dwrtSVtanh;
      std::vector<std::vector<std::vector<float> > > dijet_ip3dsigwrtSVtanh;
      std::vector<std::vector<std::vector<float> > > dijet_costhetawrtSV;
  

      std::vector<std::vector<std::vector<float> > > SVIP2D;
      std::vector<std::vector<std::vector<float> > > SVIP2D_sig;
      
      std::vector<std::vector<std::vector<float> > > SVIP3D;
      std::vector<std::vector<std::vector<float> > > SVIP3D_sig;

      std::vector<std::vector<std::vector<int> > > SVjetidx;
      std::vector<std::vector<std::vector<float> > > SVcharges;
      std::vector<std::vector<std::vector<float> > > SVtrkenergy;
      std::vector<std::vector<float> > SVIP3D_minsig;

     
      //Dijet-level genmatch informatins
      std::vector<bool> TrueDijet;
      std::vector<int> jet1pdgID;
      std::vector<int> jet2pdgID;
      std::vector<float> jet1mompdgID;
      std::vector<float> jet2mompdgID;
      std::vector<float> jet1genpt;
      std::vector<float> jet1geneta; 
      std::vector<float> jet1genphi;
      std::vector<float> jet1genenergy;
      std::vector<float> jet2genpt;
      std::vector<float> jet2geneta;
      std::vector<float> jet2genphi;
      std::vector<float> jet2genenergy;
      std::vector<float> dijetgenSVx1;
      std::vector<float> dijetgenSVy1;
      std::vector<float> dijetgenSVz1;
      std::vector<float> dijetgenSVlxy1;
      std::vector<float> dijetgenSVlxyz1;
      std::vector<float> dijetgenSVctau01;
   
      std::vector<float> dijetgenSVx2;
      std::vector<float> dijetgenSVy2;
      std::vector<float> dijetgenSVz2;
      std::vector<float> dijetgenSVlxy2;
      std::vector<float> dijetgenSVlxyz2;
      std::vector<float> dijetgenSVctau02;
      


      // test with new variables
  
      std::vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > SVdijetPhyP4; 
      std::vector<float> SVdijetPhyPt;   //Physics Pt of Dijet
      std::vector<float> SVPtFrac;       //Pt Fraction of Vertex within Dijet
      std::vector<float> SVdphiDJVX;     //delta Phi between Dijet and Vertex Momentum
      std::vector<float> SVdphiLxyVX;    //delta Phi between Lxy and Vertex Momentum
  
      std::vector<int>   SVjet1Idx;
      std::vector<int>   SVjet2Idx;
      std::vector<float> SVPrejet1Pt;
      std::vector<float> SVjet1Pt;
      std::vector<float> SVjet1PtUp;
      std::vector<float> SVjet1PtDown;
      std::vector<float> SVjet1Eta;
      std::vector<float> SVjet1Phi;
      std::vector<float> SVPrejet2Pt;
      std::vector<float> SVjet2Pt;
      std::vector<float> SVjet2Eta;
      std::vector<float> SVjet2Phi;
      std::vector<float> SVjet2PtUp;
      std::vector<float> SVjet2PtDown;
      std::vector<float> jet1trackEnergy;
      std::vector<float> jet1trackPt;
      std::vector<float> jet2trackEnergy;
      std::vector<float> jet2trackPt;
      std::vector<float> SVnSV;
     
      std::vector<float> SVDNNp;
      std::vector<float> SVDNNd;
  
      std::vector<float> SVtrkenergysum; 
      
      std::vector<float> dijettrackEnergy;
      std::vector<float> jet1trackPrompt_EFrac;
      std::vector<float> jet2trackPrompt_EFrac;
      std::vector<float> dijettrackPrompt_EFrac;
 
      std::vector<std::vector<float> >  SVjetEnergyFrac; //The ratio of the energy carried by tracks at the vertex with respect to the jet energy
      std::vector<std::vector<float> >  SVtrksEnergyFrac; //The ratio of the energy carried by tracks at the vertex with respect to all tracks in the jet

      std::vector<float> SVjetEnergyFrac_total;
      std::vector<float> SVtrksEnergyFrac_total;
      std::vector<float> SVdisptrksEnergyFrac;
      std::vector<float> SVtrksPtFrac;    
      std::vector<float> SVdisptrksPtFrac; 
 
      std::vector<int> SVnPrompttk1;
      std::vector<int> SVnPrompttk2;
      std::vector<int> SVnPromptTracks;

      std::vector<float> SVpromptEnergy1;
      std::vector<float> SVpromptEnergy2;
      std::vector<float> SVpromptEnergy;

      std::vector<float> SVpromptEnergyfrac;
      std::vector<float> SVpromptEnergyfrac1;
      std::vector<float> SVpromptEnergyfrac2;
    
      //Redefine Prompt Track as IP2D_sig<50
      std::vector<float> SVsigpromptEnergyfrac;

      //Prompt Track as IP2D_sig<30
      std::vector<float> SVsig30promptEnergyfrac;
 
      //Selection Tag/    
      std::vector<std::vector<bool>>  SVDijetTag;
      
      std::vector<std::vector<float>> SVvtxx;
      std::vector<std::vector<float>> SVvtxy;
      std::vector<std::vector<float>> SVvtxz;

      std::vector<std::vector<float>> SVvtxlxy;
      std::vector<std::vector<float>> SVvtxlxysig;
      std::vector<std::vector<float>> SVvtxlxyz;
      std::vector<std::vector<float>> SVvtxlxyzsig;

      std::vector<std::vector<float>> SVcosthetaPLxyz;

      std::vector<std::vector<float>> SVmeancosthetatrks; //pt weighted mean opening cos theta of tracks w.r.t the vertex

      std::vector<std::vector<float>> SVdistwrtgenSV1;  //the distance w.r.t the gen-level LLP decay vertex 1 
      std::vector<std::vector<float>> SVdistwrtgenSV2;  //the distance w.r.t the gen-level LLP decay vertex 2
     
      std::vector<std::vector<float>> SVdistsigwrtgenSV1;
      std::vector<std::vector<float>> SVdistsigwrtgenSV2;

      std::vector<std::vector<float>> SVdijetdRgenmom1;
      std::vector<std::vector<float>> SVdijetdRgenmom2;
    
      std::vector<std::vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > > SVvtxP4;
      std::vector<std::vector<int>> SVvtxnTrack;
      std::vector<std::vector<int>> SVposnTrack;
      std::vector<std::vector<int>> SVvtxntrk_jet1;
      std::vector<std::vector<int>> SVvtxntrk_jet2;    
      std::vector<std::vector<float>> SVenergyfrac_jet1;
      std::vector<std::vector<float>> SVenergyfrac_jet2;
       
 
      std::vector<std::vector<float>> SVvtxChi2;
      std::vector<std::vector<float>> SVkappa;
      std::vector<float> SVkappa_total;
      std::vector<std::vector<float>> SVdijetdR;
      std::vector<std::vector<float>> SVdijetcostheta;
      std::vector<std::vector<float>> SV2ndip2dsig;  
      std::vector<std::vector<float>> SVhitsInFrontOfVert;
      std::vector<std::vector<float>> SVmissHitsAfterVert;

      //SV to SV edge information
      std::vector<std::vector<float>> SVtoSVdist;
      std::vector<std::vector<float>> SVtoSVdistsig;
      std::vector<std::vector<float>> SVtoSVdisttanh;
      std::vector<std::vector<float>> SVtoSVdistsigtanh;
      std::vector<std::vector<float>> SVtoSVjet1dR;
      std::vector<std::vector<float>> SVtoSVjet2dR;
      std::vector<std::vector<float>> SVtoSVjet1costheta;
      std::vector<std::vector<float>> SVtoSVjet2costheta;
    


      //Cluster Information
      std::vector<float> SVdijetbestglxyRMS;
      std::vector<float> SVdijetbestglxyAvg;
      std::vector<int>   SVndijetcluster;
    
      std::vector<int> SVdijetbestN;
      std::vector<int> SVdijetbestN1;
      std::vector<int> SVdijetbestN2;

   
      //Offline Information
      unsigned int nhltjets_;
      std::vector<float> hltjetpt_, hltjeteta_, hltjetphi_, hltjetmass_;
      
      //Trigger Information
      bool pass_HLT_IsoMu24_;
      bool pass_HLT_IsoTkMu24_;
      bool pass_HLT_HT200_;
      bool pass_HLT_HT275_;
      bool pass_HLT_HT325_;
      bool pass_HLT_HT425_;
      bool pass_HLT_HT575_;
      bool pass_HLT_HT650_;
      bool pass_HLT_L1Mu6HT240_;
  
      bool pass_HLT_HT430_DisplacedDijet40_DisplacedTrack_;
      bool pass_HLT_HT430_DisplacedDijet60_DisplacedTrack_;

      bool pass_HLT_HT400_DisplacedDijet40_Inclusive_;
      bool pass_HLT_HT500_DisplacedDijet40_Inclusive_;
      bool pass_HLT_HT550_DisplacedDijet40_Inclusive_;
      bool pass_HLT_HT650_DisplacedDijet60_Inclusive_;
      bool pass_HLT_HT650_DisplacedDijet80_Inclusive_;
      bool pass_HLT_HT750_DisplacedDijet80_Inclusive_;

      //Run-3 triggers
      bool pass_HLT_HT430_DisplacedDijet30_Inclusive1PtrkShortSig5_;
      bool pass_HLT_HT430_DisplacedDijet35_Inclusive1PtrkShortSig5_;
      bool pass_HLT_HT430_DisplacedDijet40_Inclusive1PtrkShortSig5_;
      
      bool pass_HLT_Mu6HT240_DisplacedDijet30_Inclusive0PtrkShortSig5_;
      bool pass_HLT_Mu6HT240_DisplacedDijet30_Inclusive1PtrkShortSig5_DisplacedLoose_;
      bool pass_HLT_Mu6HT240_DisplacedDijet35_Inlcusive0PtrkShortSig5_;
      bool pass_HLT_Mu6HT240_DisplacedDijet35_Inclusive1PtrkShortSig5_DisplacedLoose_;
      bool pass_HLT_Mu6HT240_DisplacedDijet40_Inclusive0PtrkShortSig5_;
      bool pass_HLT_Mu6HT240_DisplacedDijet40_Inclusive1PtrkShortSig5_DisplacedLoose_;
   
      bool pass_HLT_HT430_DelayedJet40_DoubleDelay0p5nsTrackless_;
      bool pass_HLT_HT430_DelayedJet40_DoubleDelay1nsInclusive_;
      bool pass_HLT_HT430_DelayedJet40_SingleDelay1nsTrackless_;
      bool pass_HLT_HT430_DelayedJet40_SingleDelay2nsInclusive_;



      // ----------member data ---------------------------
};
#endif

