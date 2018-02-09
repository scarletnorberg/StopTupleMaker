#include <memory>
#include <algorithm>
#include <vector>
#include <map>

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDFilter.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/Framework/interface/Event.h"
#include "DataFormats/Common/interface/Handle.h"
#include "DataFormats/Common/interface/View.h"
#include "DataFormats/VertexReco/interface/Vertex.h"

#include "DataFormats/PatCandidates/interface/Jet.h"
#include "JetMETCorrections/Objects/interface/JetCorrector.h"

#include "DataFormats/JetReco/interface/BasicJet.h"
#include "DataFormats/JetReco/interface/BasicJetCollection.h"

#include "DataFormats/METReco/interface/MET.h"

#include "DataFormats/ParticleFlowCandidate/interface/PFCandidateFwd.h"
#include "DataFormats/ParticleFlowCandidate/interface/PFCandidate.h"

#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "CommonTools/Utils/interface/PtComparator.h"
#include "JetMETCorrections/Objects/interface/JetCorrectionsRecord.h"
#include "CondFormats/JetMETObjects/interface/JetCorrectionUncertainty.h"
#include "CondFormats/JetMETObjects/interface/JetCorrectorParameters.h"

#include "TLorentzVector.h"

#include "DataFormats/BTauReco/interface/TaggingVariable.h"
#include "DataFormats/BTauReco/interface/ShallowTagInfo.h"
//#include "DeepNTuples/JetAnalysis/interface/JetHelper.h"
#include "DataFormats/BTauReco/interface/TaggingVariable.h"
//#include "DeepNTuples/DeepNtuplizer/interface/ntuple_bTagVars.h"
#include "DataFormats/BTauReco/interface/CandIPTagInfo.h"
#include "DataFormats/BTauReco/interface/CandSoftLeptonTagInfo.h"
#include "DataFormats/BTauReco/interface/BoostedDoubleSVTagInfo.h"
#include "DataFormats/BTauReco/interface/TrackIPTagInfo.h"
#include "DataFormats/BTauReco/interface/IPTagInfo.h"
#include "DataFormats/BTauReco/interface/SecondaryVertexTagInfo.h"
#include "DataFormats/PatCandidates/interface/PackedCandidate.h"
//#include "DeepNTuples/DeepNtuplizer/interface/ntuple_bTagVars.h"

//#include "DeepNTuples/DeepNtuplizer/interface/ntuple_content.h"
//#include "DeepNTuples/DeepNtuplizer/interface/ntuple_SV.h"
//#include "DeepNTuples/DeepNtuplizer/interface/ntuple_JetInfo.h"
//#include "DeepNTuples/DeepNtuplizer/interface/ntuple_pfCands.h"
//#include "DeepNTuples/DeepNtuplizer/interface/ntuple_bTagVars.h"

#include "RecoBTau/JetTagComputer/interface/GenericMVAJetTagComputer.h"
#include "RecoBTau/JetTagComputer/interface/GenericMVAJetTagComputerWrapper.h"
#include "RecoBTau/JetTagComputer/interface/JetTagComputer.h"
#include "RecoBTau/JetTagComputer/interface/JetTagComputerRecord.h"
#include "RecoBTag/SecondaryVertex/interface/CombinedSVComputer.h"
#include "RecoBTag/SecondaryVertex/interface/TrackKinematics.h"
#include "RecoBTag/SecondaryVertex/interface/V0Filter.h"
#include "RecoBTag/ImpactParameter/plugins/IPProducer.h"
#include "RecoVertex/VertexPrimitives/interface/ConvertToFromReco.h"

class prodJets : public edm::EDFilter 
{
public:

    explicit prodJets(const edm::ParameterSet & iConfig);
    ~prodJets();


private:

    virtual bool filter(edm::Event & iEvent, const edm::EventSetup & iSetup);

    void compute(const reco::Jet * jet, bool isReco, double& totalMult_, double& ptD_, double& axis1_, double& axis2_);
    
    edm::EDGetTokenT<std::vector<pat::Jet> >JetTok_;
    edm::EDGetTokenT<std::vector<pat::Jet> >OtherJetsTok_;
    edm::EDGetTokenT<std::vector<int> > W_EmuVec_Tok_;
    edm::EDGetTokenT<std::vector<int> >W_TauVec_Tok_;
    edm::EDGetTokenT<std::vector<int> >W_Tau_EmuVec_Tok_;
    edm::EDGetTokenT<std::vector<int> >W_Tau_ProngsVec_Tok_;
    edm::EDGetTokenT<std::vector<int> >W_Tau_NuVec_Tok_;
    edm::EDGetTokenT<std::vector<TLorentzVector> >GenDecayLVec_Tok_;
    edm::EDGetTokenT<std::vector<int> >GenDecayMomRefVec_Tok_;
    edm::EDGetTokenT<std::vector<TLorentzVector> >EleLVec_Tok_;
    edm::EDGetTokenT<std::vector<TLorentzVector> >MuLVec_Tok_;
    edm::EDGetTokenT<std::vector<TLorentzVector> >TrksForIsoVetolVec_Tok_;
    edm::EDGetTokenT<std::vector<TLorentzVector> >LooseIsoTrksVec_Tok_;
    edm::EDGetTokenT< std::vector<reco::Vertex> >VtxTok_;
    edm::EDGetTokenT<std::vector<pat::Jet>> PuppiJetsSrc_Tok_;
    edm::EDGetTokenT<std::vector<pat::Jet>> PuppiSubJetsSrc_Tok_;
    edm::EDGetTokenT<std::vector<pat::Jet> > AK8JetTok_;

    edm::InputTag W_emuVec_Src_, W_tauVec_Src_, W_tau_emuVec_Src_, W_tau_prongsVec_Src_, W_tau_nuVec_Src_;
    edm::Handle<std::vector<int> > W_emuVec_, W_tauVec_, W_tau_emuVec_, W_tau_prongsVec_, W_tau_nuVec_;

    edm::InputTag genDecayLVec_Src_;
    edm::Handle<std::vector<TLorentzVector> > genDecayLVec_;

    edm::InputTag genDecayMomRefVec_Src_;
    edm::Handle<std::vector<int> > genDecayMomRefVec_;

    edm::InputTag eleLVec_Src_, muLVec_Src_;
    edm::Handle<std::vector<TLorentzVector> > eleLVec_, muLVec_;

    edm::InputTag trksForIsoVetoLVec_Src_, looseisoTrksLVec_Src_;
    edm::Handle<std::vector<TLorentzVector> > trksForIsoVetoLVec_, looseisoTrksLVec_;
    double deltaRcon_;
    double ak4ptCut_;

    //PUPPI sources
    edm::InputTag puppiJetsSrc_, puppiSubJetsSrc_;
    edm::Handle<std::vector<pat::Jet> > puppiJets;
    edm::Handle<std::vector<pat::Jet> > puppiSubJets; 
 
    //AK8 Jets
    edm::InputTag AK8JetSrc_;
    //edm::InputTag ak8JetsSrc_, ak8SubJetsSrc_;
    //edm::Handle<std::vector<pat::Jet> > ak8Jets;
    //edm::Handle<std::vector<pat::Jet> > ak8SubJets;
    double ak8ptCut_;

    std::string qgTaggerKey_;

    std::string jetType_;

  edm::InputTag jetSrc_, jetOtherSrc_;
  // All have to be pat::Jet, otherwise cannot get b-tagging information!
  edm::Handle<std::vector<pat::Jet> > jets, otherjets; 

    std::string NjettinessAK8Puppi_label_, ak8PFJetsPuppi_label_;

  std::string bTagKeyString_;

  std::string jetPBJetTags_;
  std::string jetPNegBJetTags_;
  std::string jetPPosBJetTags_;

  std::string jetBPBJetTags_;
  std::string jetBPNegBJetTags_;
  std::string jetBPPosBJetTags_;

  std::string deepCSVBJetTags_;
  std::string deepCSVNegBJetTags_;
  std::string deepCSVPosBJetTags_;

  std::string deepFlavorBJetTags_;

  std::string combinedSVBJetTags_;
  std::string combinedSVNegBJetTags_;
  std::string combinedSVPosBJetTags_;

  std::string combinedIVFSVBJetTags_;
  std::string combinedIVFSVPosBJetTags_;
  std::string combinedIVFSVNegBJetTags_;

  std::string simpleSVHighEffBJetTags_;
  std::string simpleSVNegHighEffBJetTags_;
  std::string simpleSVHighPurBJetTags_;
  std::string simpleSVNegHighPurBJetTags_;

  std::string softPFMuonBJetTags_;
  std::string softPFMuonNegBJetTags_;
  std::string softPFMuonPosBJetTags_;

  std::string softPFElectronBJetTags_;
  std::string softPFElectronNegBJetTags_;
  std::string softPFElectronPosBJetTags_;

  std::string doubleSVBJetTags_;

  std::string cMVABJetTags_;
  std::string cMVAv2BJetTags_;
  std::string cMVAv2NegBJetTags_;
  std::string cMVAv2PosBJetTags_;

  std::string   CvsBCJetTags_;
  std::string   CvsBNegCJetTags_;
  std::string   CvsBPosCJetTags_;
  std::string   CvsLCJetTags_;
  std::string   CvsLNegCJetTags_;
  std::string   CvsLPosCJetTags_;

  std::string SVComputer_, SLComputer_;
  const GenericMVAJetTagComputer *computer_, *slcomputer_;

  edm::InputTag vtxSrc_;
  edm::InputTag metSrc_;
  bool isPatJet;
  bool debug_;

  bool isData_;

  double jetPtCut_miniAOD_, genMatch_dR_;
  double relPt_for_xCheck_, dR_for_xCheck_;

  std::string tagInfoName_;
  std::string ipTagInfos_;
  std::string svTagInfos_;

  std::string ipTagInfosCTag_;
  std::string svTagInfosCTag_;
  std::string softPFMuonTagInfosCTag_;
  std::string softPFElectronTagInfosCTag_;

  float jetNTracks_;              // tracks associated to jet
  float trackJetPt_;
};

void prodJets::compute(const reco::Jet * jet, bool isReco, double& totalMult_, double& ptD_, double& axis1_, double& axis2_)
{

    totalMult_ = 0;
    ptD_       = 0;
    axis1_     = 0;
    axis2_     = 0;
    
    if(jet->numberOfDaughters() == 0) return;

    float sum_weight    = 0.0;
    float sum_dEta      = 0.0;
    float sum_dPhi      = 0.0;
    float sum_dEta2     = 0.0;
    float sum_dPhi2     = 0.0;
    float sum_dEta_dPhi = 0.0;
    float sum_pt        = 0.0;
    bool useQC          = false; // useQualityCuts; hard-coded for now to mimic what jetMet does in 731

    // loop over the jet constituents
    // (packed candidate situation)
    for(auto part : jet->getJetConstituentsQuick()) {
        if(part->charge()){ // charged particles
            if(isReco) {
                auto p = dynamic_cast<const pat::PackedCandidate*>(part);
                if(!p){
                    try { throw; }
                    catch(...) {
                        std::cout << "ERROR: QGTagging variables cannot be computed for these jets!" << std::endl
                                  << "       See QuauarGluonTaggingVaiables::compute()"              << std::endl;
                    } // catch(...)
                } // !p
                if(!( p->fromPV() > 1 && p->trackHighPurity() )) continue;
                if(useQC) {
                    // currently hard-coded to false above
                    // this isn't stored for packedCandidates, so will need fix if useQC is changed to true
                    if( p->dzError()==0 || p->dxyError()==0 ) continue;
                    if( (p->dz()*p->dz() )  / (p->dzError()*p->dzError() ) > 25. ) continue;
                    if( (p->dxy()*p->dxy()) / (p->dxyError()*p->dxyError()) < 25. ) ++totalMult_; // this cut only applies to multiplicity
                } else ++totalMult_;
            } else ++totalMult_;
        } else { // neutral particles
            if(part->pt() < 1.0) continue;
            ++totalMult_;
        } // charged, neutral particles

        float dEta   = part->eta() - jet->eta();
        float dPhi   = reco::deltaPhi(part->phi(), jet->phi());
        float partPt = part->pt();
        float weight = partPt*partPt;

        sum_weight    += weight;
        sum_pt        += partPt;
        sum_dEta      += dEta      * weight;
        sum_dPhi      += dPhi      * weight;
        sum_dEta2     += dEta*dEta * weight;
        sum_dEta_dPhi += dEta*dPhi * weight;
        sum_dPhi2     += dPhi*dPhi * weight;
    } // jet->getJetConstituentsQuick()

    // calculate axis2 and ptD
    float a = 0.0;
    float b = 0.0;
    float c = 0.0;
    float ave_dEta  = 0.0;
    float ave_dPhi  = 0.0;
    float ave_dEta2 = 0.0;
    float ave_dPhi2 = 0.0;

    if(sum_weight > 0){
        ptD_ = sqrt(sum_weight)/sum_pt;
        ave_dEta  = sum_dEta  / sum_weight;
        ave_dPhi  = sum_dPhi  / sum_weight;
        ave_dEta2 = sum_dEta2 / sum_weight;
        ave_dPhi2 = sum_dPhi2 / sum_weight;
        a = ave_dEta2 - ave_dEta*ave_dEta;
        b = ave_dPhi2 - ave_dPhi*ave_dPhi;
        c = -(sum_dEta_dPhi/sum_weight - ave_dEta*ave_dPhi);
    } else ptD_ = 0;

    float delta = sqrt(fabs( (a-b)*(a-b) + 4*c*c ));
    if(a+b-delta > 0) axis2_ = sqrt(0.5*(a+b-delta));
    else              axis2_ = 0.0;
    if(a+b+delta > 0) axis1_ = sqrt(0.5*(a+b+delta));
    else              axis1_ = 0.0;
}

prodJets::prodJets(const edm::ParameterSet & iConfig) 
{
  isData_ = true;

  jetSrc_      = iConfig.getParameter<edm::InputTag>("jetSrc");
  jetOtherSrc_ = iConfig.getParameter<edm::InputTag>("jetOtherSrc");
  vtxSrc_      = iConfig.getParameter<edm::InputTag>("vtxSrc");
  //metSrc_      = iConfig.getParameter<edm::InputTag>("metSrc");
  bTagKeyString_ = iConfig.getParameter<std::string>("bTagKeyString");

  jetPBJetTags_        = iConfig.getParameter<std::string>("jetPBJetTags");
  jetPNegBJetTags_     = iConfig.getParameter<std::string>("jetPNegBJetTags");
  jetPPosBJetTags_     = iConfig.getParameter<std::string>("jetPPosBJetTags");

  jetBPBJetTags_        = iConfig.getParameter<std::string>("jetBPBJetTags");
  jetBPNegBJetTags_     = iConfig.getParameter<std::string>("jetBPNegBJetTags");
  jetBPPosBJetTags_     = iConfig.getParameter<std::string>("jetBPPosBJetTags");

  deepCSVBJetTags_    = iConfig.getParameter<std::string>("deepCSVBJetTags");
  deepCSVNegBJetTags_ = iConfig.getParameter<std::string>("deepCSVNegBJetTags");
  deepCSVPosBJetTags_ = iConfig.getParameter<std::string>("deepCSVPosBJetTags");

  deepFlavorBJetTags_    = iConfig.getParameter<std::string>("deepFlavorBJetTags");

  combinedSVBJetTags_     = iConfig.getParameter<std::string>("combinedSVBJetTags");
  combinedSVNegBJetTags_  = iConfig.getParameter<std::string>("combinedSVNegBJetTags");
  combinedSVPosBJetTags_  = iConfig.getParameter<std::string>("combinedSVPosBJetTags");

  combinedIVFSVBJetTags_      = iConfig.getParameter<std::string>("combinedIVFSVBJetTags");
  combinedIVFSVPosBJetTags_   = iConfig.getParameter<std::string>("combinedIVFSVPosBJetTags");
  combinedIVFSVNegBJetTags_   = iConfig.getParameter<std::string>("combinedIVFSVNegBJetTags");

  simpleSVHighEffBJetTags_      = iConfig.getParameter<std::string>("simpleSVHighEffBJetTags");
  simpleSVNegHighEffBJetTags_   = iConfig.getParameter<std::string>("simpleSVNegHighEffBJetTags");
  simpleSVHighPurBJetTags_      = iConfig.getParameter<std::string>("simpleSVHighPurBJetTags");
  simpleSVNegHighPurBJetTags_   = iConfig.getParameter<std::string>("simpleSVNegHighPurBJetTags");

  combinedIVFSVBJetTags_      = iConfig.getParameter<std::string>("combinedIVFSVBJetTags");
  combinedIVFSVPosBJetTags_   = iConfig.getParameter<std::string>("combinedIVFSVPosBJetTags");
  combinedIVFSVNegBJetTags_   = iConfig.getParameter<std::string>("combinedIVFSVNegBJetTags");

  softPFMuonBJetTags_       = iConfig.getParameter<std::string>("softPFMuonBJetTags");
  softPFMuonNegBJetTags_    = iConfig.getParameter<std::string>("softPFMuonNegBJetTags");
  softPFMuonPosBJetTags_    = iConfig.getParameter<std::string>("softPFMuonPosBJetTags");

  softPFElectronBJetTags_       = iConfig.getParameter<std::string>("softPFElectronBJetTags");
  softPFElectronNegBJetTags_    = iConfig.getParameter<std::string>("softPFElectronNegBJetTags");
  softPFElectronPosBJetTags_    = iConfig.getParameter<std::string>("softPFElectronPosBJetTags");

  doubleSVBJetTags_ = iConfig.getParameter<std::string>("doubleSVBJetTags");

  cMVABJetTags_ = iConfig.getParameter<std::string>("cMVABJetTags");
  cMVAv2BJetTags_ = iConfig.getParameter<std::string>("cMVAv2BJetTags");
  cMVAv2NegBJetTags_ = iConfig.getParameter<std::string>("cMVAv2NegBJetTags");
  cMVAv2PosBJetTags_ = iConfig.getParameter<std::string>("cMVAv2PosBJetTags");

  CvsBCJetTags_             = iConfig.getParameter<std::string>("CvsBCJetTags");
  CvsBNegCJetTags_             = iConfig.getParameter<std::string>("CvsBNegCJetTags");
  CvsBPosCJetTags_             = iConfig.getParameter<std::string>("CvsBPosCJetTags");
  CvsLCJetTags_             = iConfig.getParameter<std::string>("CvsLCJetTags");
  CvsLNegCJetTags_             = iConfig.getParameter<std::string>("CvsLNegCJetTags");
  CvsLPosCJetTags_             = iConfig.getParameter<std::string>("CvsLPosCJetTags");

  debug_       = iConfig.getParameter<bool>("debug");

  jetPtCut_miniAOD_ = iConfig.getUntrackedParameter<double>("jetPtCut_miniAOD", 10);
  genMatch_dR_ = iConfig.getUntrackedParameter<double>("genMatch_dR", 1.0);
  dR_for_xCheck_ = iConfig.getUntrackedParameter<double>("dR_for_xCheck", 0.2);
  relPt_for_xCheck_ = iConfig.getUntrackedParameter<double>("relPt_for_xCheck", 1e-2);

  qgTaggerKey_ = iConfig.getParameter<std::string>("qgTaggerKey");
  

  ipTagInfos_              = iConfig.getParameter<std::string>("ipTagInfos");
  svTagInfos_              = iConfig.getParameter<std::string>("svTagInfos");

  ipTagInfosCTag_              = iConfig.getParameter<std::string>("ipTagInfosCTag");
  svTagInfosCTag_              = iConfig.getParameter<std::string>("svTagInfosCTag");
  softPFMuonTagInfosCTag_      = iConfig.getParameter<std::string>("softPFMuonTagInfosCTag");
  softPFElectronTagInfosCTag_  = iConfig.getParameter<std::string>("softPFElectronTagInfosCTag");

  ak4ptCut_ = iConfig.getParameter<double>("ak4ptCut");

  JetTok_ = consumes<std::vector<pat::Jet> >(jetSrc_);
  VtxTok_=consumes< std::vector<reco::Vertex> >(vtxSrc_);

  SVComputer_               = iConfig.getParameter<std::string>("svComputer");
  SLComputer_               = iConfig.getParameter<std::string>("slComputer");

  computer_ = nullptr;
  slcomputer_ = nullptr;
  
  AK8JetSrc_ = iConfig.getParameter<edm::InputTag>("ak8JetSrc");
  ak8ptCut_ = iConfig.getParameter<double>("ak8ptCut");
  AK8JetTok_ = consumes<std::vector<pat::Jet> >(AK8JetSrc_);

  NjettinessAK8Puppi_label_ = iConfig.getParameter<std::string>("NjettinessAK8Puppi_label");
  ak8PFJetsPuppi_label_ = iConfig.getParameter<std::string>("ak8PFJetsPuppi_label");

  //produces<std::vector<pat::Jet> >("");
  produces<std::vector<TLorentzVector> >("jetsLVec");
  produces<std::vector<int> >("recoJetsFlavor");
  produces<std::vector<double> >("recoJetsBtag");

  produces<std::vector<double> >("JetProba");
  produces<std::vector<double> >("JetProbaN");
  produces<std::vector<double> >("JetProbaP");
  produces<std::vector<double> >("JetBprob");
  produces<std::vector<double> >("JetBprobP");
  produces<std::vector<double> >("JetBprobN");

  produces<std::vector<double> >("CombinedSvtx");
  produces<std::vector<double> >("CombinedSvtxN");
  produces<std::vector<double> >("CombinedSvtxP");

  produces<std::vector<double> >("recoJetsCharge");
  produces<std::vector<double> >("recoJetsJecUnc");
  produces<std::vector<double> >("recoJetsJecScaleRawToFull");
  produces<std::vector<double> >("qgLikelihood");
  produces<std::vector<double> >("qgPtD");
  produces<std::vector<double> >("qgAxis1");
  produces<std::vector<double> >("qgAxis2");
  produces<std::vector<int> >("qgMult");
/*
  produces<std::vector<double> >("qgPtDrLog");
  produces<std::vector<int> >("qgcMult");
  produces<std::vector<int> >("qgnMult");
*/
  produces<std::vector<double> >("DeepCSVb");
  produces<std::vector<double> >("DeepCSVc");
  produces<std::vector<double> >("DeepCSVl");
  produces<std::vector<double> >("DeepCSVbb");
  produces<std::vector<double> >("DeepCSVcc");

  produces<std::vector<double> >("DeepCSVbN");
  produces<std::vector<double> >("DeepCSVcN");
  produces<std::vector<double> >("DeepCSVlN");
  produces<std::vector<double> >("DeepCSVbbN");
  produces<std::vector<double> >("DeepCSVccN");

  produces<std::vector<double> >("DeepCSVbP");
  produces<std::vector<double> >("DeepCSVcP");
  produces<std::vector<double> >("DeepCSVlP");
  produces<std::vector<double> >("DeepCSVbbP");
  produces<std::vector<double> >("DeepCSVccP");

  produces<std::vector<double> >("DeepFlavorb");
  produces<std::vector<double> >("DeepFlavorbb");
  produces<std::vector<double> >("DeepFlavorlepb");
  produces<std::vector<double> >("DeepFlavorc");
  produces<std::vector<double> >("DeepFlavoruds");
  produces<std::vector<double> >("DeepFlavorg");

  produces<std::vector<float> >("CombinedIVF");
  produces<std::vector<float> >("CombinedIVFP");
  produces<std::vector<float> >("CombinedIVFN");

  produces<std::vector<double> >("Svtx");
  produces<std::vector<double> >("SvtxN");
  produces<std::vector<double> >("SvtxHP");
  produces<std::vector<double> >("SvtxNHP");

  produces<std::vector<double> >("SoftM");
  produces<std::vector<double> >("SoftMN");
  produces<std::vector<double> >("SoftMP");

  produces<std::vector<double> >("SoftE");
  produces<std::vector<double> >("SoftEN");
  produces<std::vector<double> >("SoftEP");

  produces<std::vector<double> >("DoubleSV");

  produces<std::vector<double> >("cMVA");
  produces<std::vector<double> >("cMVAv2");
  produces<std::vector<double> >("cMVAv2Neg");
  produces<std::vector<double> >("cMVAv2Pos");

  produces<std::vector<double> >("CvsB");
  produces<std::vector<double> >("CvsBNeg");
  produces<std::vector<double> >("CvsBPos");
  produces<std::vector<double> >("CvsL");
  produces<std::vector<double> >("CvsLNeg");
  produces<std::vector<double> >("CvsLPos");

  //produces<std::vector<int>>("nTracks");
  //produces<std::vector<int>>("nSVs");

  //produce variables needed for Lost Lepton study, added by hua.wei@cern.ch
  produces<std::vector<double> >("recoJetschargedHadronEnergyFraction");
  produces<std::vector<double> >("recoJetsneutralEnergyFraction");
  produces<std::vector<double> >("recoJetschargedEmEnergyFraction");
  produces<std::vector<double> >("recoJetsneutralEmEnergyFraction");
  produces<std::vector<double> >("recoJetsHFHadronEnergyFraction");
  produces<std::vector<double> >("recoJetsHFEMEnergyFraction");
  produces<std::vector<double> >("PhotonEnergyFraction");
  produces<std::vector<double> >("ElectronEnergyFraction");

  produces<std::vector<double> >("recoJetsmuonEnergyFraction");

  produces<std::vector<double> >("ChargedHadronMultiplicity");
  produces<std::vector<double> >("NeutralHadronMultiplicity");
  produces<std::vector<double> >("PhotonMultiplicity");
  produces<std::vector<double> >("ElectronMultiplicity");
  produces<std::vector<double> >("MuonMultiplicity");

  produces<std::vector<double> >("TagVarCSVtrackSumJetEtRatio");

  //produces<std::vector<double> >("CSVTrackJetPt");
  //produces<std::vector<double> >("CSVVertexCategory");
  //produces<std::vector<int> >   ("CSVJetNSecondaryVertices");
  //produces<std::vector<double> >("CSVTrackSumJetEtRatio");
  //produces<std::vector<double> >("CSVTrackSumJetDeltaR");
  //produces<std::vector<double> >("CSVTrackSip2dValAboveCharm");
  //produces<std::vector<double> >("CSVTrackSip2dSigAboveCharm");
  //produces<std::vector<double> >("CSVTrackSip3dValAboveCharm");
  //produces<std::vector<double> >("CSVTrackSip3dSigAboveCharm");
  //produces<std::vector<double> >("CSVVertexMass");
  //produces<std::vector<int> >   ("CSVVertexNTracks");
  //produces<std::vector<double> >("CSVVertexEnergyRatio");
  //produces<std::vector<double> >("CSVVertexJetDeltaR");
  //produces<std::vector<double> >("CSVFlightDistance2dVal");
  //produces<std::vector<double> >("CSVFlightDistance2dSig");
  //produces<std::vector<double> >("CSVFlightDistance3dVal");
  //produces<std::vector<double> >("CSVFlightDistance3dSig");
  //
  //produces<std::vector<double> >("CTagVertexCategory");
  //produces<std::vector<int> >   ("CTagJetNSecondaryVertices");
  //produces<std::vector<double> >("CTagTrackSumJetEtRatio");
  //produces<std::vector<double> >("CTagTrackSumJetDeltaR");
  //produces<std::vector<double> >("CTagTrackSip2dSigAboveCharm");
  //produces<std::vector<double> >("CTagTrackSip3dSigAboveCharm");
  //produces<std::vector<double> >("CTagVertexMass");
  //produces<std::vector<int> >   ("CTagVertexNTracks");
  //produces<std::vector<double> >("CTagVertexEnergyRatio");
  //produces<std::vector<double> >("CTagVertexJetDeltaR");
  //produces<std::vector<double> >("CTagFlightDistance2dSig");
  //produces<std::vector<double> >("CTagFlightDistance3dSig");
  //produces<std::vector<double> >("CTagMassVertexEnergyFraction");
  //produces<std::vector<double> >("CTagVertexBoostOverSqrtJetPt");
  //produces<std::vector<double> >("CTagVertexLeptonCategory");

  produces<std::vector<std::vector<TLorentzVector> > >("chargedPFCandLV");
  produces<std::vector<std::vector<TLorentzVector> > >("neutralPFCandLV");

  produces<std::vector<std::vector<double> > > ("chargedPFDxy");
  produces<std::vector<std::vector<double> > > ("chargedPFDz");
  produces<std::vector<std::vector<double> > > ("chargedPFFromPV");
  produces<std::vector<std::vector<double> > > ("chargedPFVertexChi2");
  produces<std::vector<std::vector<double> > > ("chargedPFVertexNdof");
  produces<std::vector<std::vector<double> > > ("chargedPFVertexMass");
  produces<std::vector<std::vector<double> > > ("neutralPFHCALFrac");

  ////produces<std::vector<TLorentzVector> > ("puppiAK8LVec");
  ////produces<std::vector<double> > ("puppiAK8Tau1");
  ////produces<std::vector<double> > ("puppiAK8Tau2");
  ////produces<std::vector<double> > ("puppiAK8Tau3");
  ////produces<std::vector<double> > ("puppiAK8SoftDropMass");
  ////
  ////produces<std::vector<std::vector<TLorentzVector> > > ("puppiAK8SubjetLVec");
  ////produces<std::vector<std::vector<double> > > ("puppiAK8SubjetMult");
  ////produces<std::vector<std::vector<double> > > ("puppiAK8SubjetPtD");
  ////produces<std::vector<std::vector<double> > > ("puppiAK8SubjetAxis1");
  ////produces<std::vector<std::vector<double> > > ("puppiAK8SubjetAxis2");
  ////produces<std::vector<std::vector<double> > > ("puppiAK8SubjetBDisc");
  
}


prodJets::~prodJets() 
{
}


bool prodJets::filter(edm::Event& iEvent, const edm::EventSetup& iSetup) 
{
  if( !iEvent.isRealData() ) isData_ = false;

  iEvent.getByToken(JetTok_, jets);

  //get the JEC uncertainties
  //edm::ESHandle<JetCorrectorParametersCollection> JetCorParColl;
  //iSetup.get<JetCorrectionsRecord>().get(jetType_, JetCorParColl);
  //JetCorrectorParameters const & JetCorPar = (*JetCorParColl)["Uncertainty"];
  //std::auto_ptr<JetCorrectionUncertainty> jecUnc( new JetCorrectionUncertainty(JetCorPar) );
  
  edm::Handle<std::vector<pat::Jet> > ak8Jets;
  iEvent.getByToken(AK8JetTok_, ak8Jets);

  //read in the objects
  edm::Handle< std::vector<reco::Vertex> > vertices;
  iEvent.getByToken(VtxTok_, vertices);

  edm::ESHandle<JetTagComputer> computerHandle;
  iSetup.get<JetTagComputerRecord>().get( SVComputer_.c_str(), computerHandle );

  computer_ = dynamic_cast<const GenericMVAJetTagComputer*>( computerHandle.product() );

  edm::ESHandle<JetTagComputer> slcomputerHandle;
  iSetup.get<JetTagComputerRecord>().get( SLComputer_.c_str(), slcomputerHandle );

  slcomputer_ = dynamic_cast<const GenericMVAJetTagComputer*>( slcomputerHandle.product() );


  std::vector<pat::Jet> extJets = (*jets);

  //check which ones to keep
  //std::auto_ptr<std::vector<pat::Jet> > prod(new std::vector<pat::Jet>());
  std::auto_ptr<std::vector<TLorentzVector> > jetsLVec(new std::vector<TLorentzVector>());
  std::auto_ptr<std::vector<int> > recoJetsFlavor(new std::vector<int>());
  std::auto_ptr<std::vector<double> > recoJetsBtag(new std::vector<double>());

  std::auto_ptr<std::vector<double> > JetProba(new std::vector<double>());
  std::auto_ptr<std::vector<double> > JetProbaN(new std::vector<double>());
  std::auto_ptr<std::vector<double> > JetProbaP(new std::vector<double>());
  std::auto_ptr<std::vector<double> > JetBprob(new std::vector<double>());
  std::auto_ptr<std::vector<double> > JetBprobP(new std::vector<double>());
  std::auto_ptr<std::vector<double> > JetBprobN(new std::vector<double>());

  std::auto_ptr<std::vector<double> >CombinedSvtx(new std::vector<double>());
  std::auto_ptr<std::vector<double> >CombinedSvtxN(new std::vector<double>());
  std::auto_ptr<std::vector<double> >CombinedSvtxP(new std::vector<double>());

  std::auto_ptr<std::vector<double> > recoJetsCharge(new std::vector<double>());
  std::auto_ptr<std::vector<double> > recoJetsJecUnc(new std::vector<double>());
  std::auto_ptr<std::vector<double> > recoJetsJecScaleRawToFull(new std::vector<double>());

  std::auto_ptr<std::vector<double> > qgLikelihood(new std::vector<double>());
  std::auto_ptr<std::vector<double> > qgPtD(new std::vector<double>());
  std::auto_ptr<std::vector<double> > qgAxis1(new std::vector<double>());
  std::auto_ptr<std::vector<double> > qgAxis2(new std::vector<double>());
  std::auto_ptr<std::vector<int> > qgMult(new std::vector<int>());
/*
  std::auto_ptr<std::vector<double> > qgPtDrLog(new std::vector<double>());
  std::auto_ptr<std::vector<double> > qgAxis1(new std::vector<double>());
  std::auto_ptr<std::vector<int> > qgnMult(new std::vector<int>());
  std::auto_ptr<std::vector<int> > qgcMult(new std::vector<int>());
*/
  std::auto_ptr<std::vector<double> > DeepCSVb(new std::vector<double>());
  std::auto_ptr<std::vector<double> > DeepCSVc(new std::vector<double>());
  std::auto_ptr<std::vector<double> > DeepCSVl(new std::vector<double>());
  std::auto_ptr<std::vector<double> > DeepCSVbb(new std::vector<double>());
  std::auto_ptr<std::vector<double> > DeepCSVcc(new std::vector<double>());

  std::auto_ptr<std::vector<double> > DeepCSVbN(new std::vector<double>());
  std::auto_ptr<std::vector<double> > DeepCSVcN(new std::vector<double>());
  std::auto_ptr<std::vector<double> > DeepCSVlN(new std::vector<double>());
  std::auto_ptr<std::vector<double> > DeepCSVbbN(new std::vector<double>());
  std::auto_ptr<std::vector<double> > DeepCSVccN(new std::vector<double>());

  std::auto_ptr<std::vector<double> > DeepCSVbP(new std::vector<double>());
  std::auto_ptr<std::vector<double> > DeepCSVcP(new std::vector<double>());
  std::auto_ptr<std::vector<double> > DeepCSVlP(new std::vector<double>());
  std::auto_ptr<std::vector<double> > DeepCSVbbP(new std::vector<double>());
  std::auto_ptr<std::vector<double> > DeepCSVccP(new std::vector<double>());

  std::auto_ptr<std::vector<double> > DeepFlavorb(new std::vector<double>());
  std::auto_ptr<std::vector<double> > DeepFlavorbb(new std::vector<double>());
  std::auto_ptr<std::vector<double> > DeepFlavorlepb(new std::vector<double>());
  std::auto_ptr<std::vector<double> > DeepFlavorc(new std::vector<double>());
  std::auto_ptr<std::vector<double> > DeepFlavoruds(new std::vector<double>());
  std::auto_ptr<std::vector<double> > DeepFlavorg(new std::vector<double>());

  std::auto_ptr<std::vector<float> >CombinedIVF(new std::vector<float>());
  std::auto_ptr<std::vector<float> >CombinedIVFN(new std::vector<float>());
  std::auto_ptr<std::vector<float> >CombinedIVFP(new std::vector<float>());

  std::auto_ptr<std::vector<double> >Svtx(new std::vector<double>());
  std::auto_ptr<std::vector<double> >SvtxN(new std::vector<double>());
  std::auto_ptr<std::vector<double> >SvtxHP(new std::vector<double>());
  std::auto_ptr<std::vector<double> >SvtxNHP(new std::vector<double>());

  std::auto_ptr<std::vector<double> >SoftM(new std::vector<double>());
  std::auto_ptr<std::vector<double> >SoftMN(new std::vector<double>());
  std::auto_ptr<std::vector<double> >SoftMP(new std::vector<double>());

  std::auto_ptr<std::vector<double> >SoftE(new std::vector<double>());
  std::auto_ptr<std::vector<double> >SoftEN(new std::vector<double>());
  std::auto_ptr<std::vector<double> >SoftEP(new std::vector<double>());

  std::auto_ptr<std::vector<double> >DoubleSV(new std::vector<double>());

  std::auto_ptr<std::vector<double> >cMVA(new std::vector<double>());
  std::auto_ptr<std::vector<double> >cMVAv2(new std::vector<double>());
  std::auto_ptr<std::vector<double> >cMVAv2Neg(new std::vector<double>());
  std::auto_ptr<std::vector<double> >cMVAv2Pos(new std::vector<double>());

  std::auto_ptr<std::vector<double> >CvsB(new std::vector<double>());
  std::auto_ptr<std::vector<double> >CvsBNeg(new std::vector<double>());
  std::auto_ptr<std::vector<double> >CvsBPos(new std::vector<double>());
  std::auto_ptr<std::vector<double> >CvsL(new std::vector<double>());
  std::auto_ptr<std::vector<double> >CvsLNeg(new std::vector<double>());
  std::auto_ptr<std::vector<double> >CvsLPos(new std::vector<double>());

  //std::auto_ptr<std::vector<int> > nTracks(new std::vector<int>());
  //std::auto_ptr<std::vector<int> > nSVs(new std::vector<int>());

  std::auto_ptr<std::vector<double> > recoJetschargedHadronEnergyFraction(new std::vector<double>());
  std::auto_ptr<std::vector<double> > recoJetsneutralEnergyFraction(new std::vector<double>());
  std::auto_ptr<std::vector<double> > recoJetschargedEmEnergyFraction(new std::vector<double>());
  std::auto_ptr<std::vector<double> > recoJetsneutralEmEnergyFraction(new std::vector<double>());
  std::auto_ptr<std::vector<double> > recoJetsmuonEnergyFraction(new std::vector<double>());
  std::auto_ptr<std::vector<double> > recoJetsHFHadronEnergyFraction(new std::vector<double>());
  std::auto_ptr<std::vector<double> > recoJetsHFEMEnergyFraction(new std::vector<double>());

  std::auto_ptr<std::vector<double> > PhotonEnergyFraction(new std::vector<double>());
  std::auto_ptr<std::vector<double> > ElectronEnergyFraction(new std::vector<double>());
  std::auto_ptr<std::vector<double> > ChargedHadronMultiplicity(new std::vector<double>());
  std::auto_ptr<std::vector<double> > NeutralHadronMultiplicity(new std::vector<double>());
  std::auto_ptr<std::vector<double> > PhotonMultiplicity(new std::vector<double>());
  std::auto_ptr<std::vector<double> > ElectronMultiplicity(new std::vector<double>());
  std::auto_ptr<std::vector<double> > MuonMultiplicity(new std::vector<double>());

  std::auto_ptr<std::vector<double> > TagVarCSVtrackSumJetEtRatio(new std::vector<double>());

  //std::auto_ptr<std::vector<double> > CSV_trackJetPt(new std::vector<double>());
  //std::auto_ptr<std::vector<double> > CSV_vertexCategory(new std::vector<double>());
  //std::auto_ptr<std::vector<int> >    CSV_jetNSecondaryVertices(new std::vector<int>());
  //std::auto_ptr<std::vector<double> > CSV_trackSumJetEtRatio(new std::vector<double>());
  //std::auto_ptr<std::vector<double> > CSV_trackSumJetDeltaR(new std::vector<double>());
  //std::auto_ptr<std::vector<double> > CSV_trackSip2dValAboveCharm(new std::vector<double>());
  //std::auto_ptr<std::vector<double> > CSV_trackSip2dSigAboveCharm(new std::vector<double>());
  //std::auto_ptr<std::vector<double> > CSV_trackSip3dValAboveCharm(new std::vector<double>());
  //std::auto_ptr<std::vector<double> > CSV_trackSip3dSigAboveCharm(new std::vector<double>());
  //std::auto_ptr<std::vector<double> > CSV_vertexMass(new std::vector<double>());
  //std::auto_ptr<std::vector<int> >    CSV_vertexNTracks(new std::vector<int>());
  //std::auto_ptr<std::vector<double> > CSV_vertexEnergyRatio(new std::vector<double>());
  //std::auto_ptr<std::vector<double> > CSV_vertexJetDeltaR(new std::vector<double>());
  //std::auto_ptr<std::vector<double> > CSV_flightDistance2dVal(new std::vector<double>());
  //std::auto_ptr<std::vector<double> > CSV_flightDistance2dSig(new std::vector<double>());
  //std::auto_ptr<std::vector<double> > CSV_flightDistance3dVal(new std::vector<double>());
  //std::auto_ptr<std::vector<double> > CSV_flightDistance3dSig(new std::vector<double>());
  //
  //std::auto_ptr<std::vector<double> > CTag_vertexCategory(new std::vector<double>());
  //std::auto_ptr<std::vector<int> >    CTag_jetNSecondaryVertices(new std::vector<int>());
  //std::auto_ptr<std::vector<double> > CTag_trackSumJetEtRatio(new std::vector<double>());
  //std::auto_ptr<std::vector<double> > CTag_trackSumJetDeltaR(new std::vector<double>());
  //std::auto_ptr<std::vector<double> > CTag_trackSip2dSigAboveCharm(new std::vector<double>());
  //std::auto_ptr<std::vector<double> > CTag_trackSip3dSigAboveCharm(new std::vector<double>());
  //std::auto_ptr<std::vector<double> > CTag_vertexMass(new std::vector<double>());
  //std::auto_ptr<std::vector<int> >    CTag_vertexNTracks(new std::vector<int>());
  //std::auto_ptr<std::vector<double> > CTag_vertexEnergyRatio(new std::vector<double>());
  //std::auto_ptr<std::vector<double> > CTag_vertexJetDeltaR(new std::vector<double>());
  //std::auto_ptr<std::vector<double> > CTag_flightDistance2dSig(new std::vector<double>());
  //std::auto_ptr<std::vector<double> > CTag_flightDistance3dSig(new std::vector<double>());
  //std::auto_ptr<std::vector<double> > CTag_massVertexEnergyFraction(new std::vector<double>());
  //std::auto_ptr<std::vector<double> > CTag_vertexBoostOverSqrtJetPt(new std::vector<double>());
  //std::auto_ptr<std::vector<double> > CTag_vertexLeptonCategory(new std::vector<double>());

  std::auto_ptr<std::vector<std::vector<TLorentzVector> > > chargedPFCandLV(new std::vector<std::vector<TLorentzVector> >());
  std::auto_ptr<std::vector<std::vector<TLorentzVector> > > neutralPFCandLV(new std::vector<std::vector<TLorentzVector> >());
  std::auto_ptr<std::vector<std::vector<double> > > chargedPFDxy(new std::vector<std::vector<double > >());
  std::auto_ptr<std::vector<std::vector<double> > > chargedPFDz(new std::vector<std::vector<double > >());
  std::auto_ptr<std::vector<std::vector<double> > > chargedPFFromPV(new std::vector<std::vector<double > >());
  std::auto_ptr<std::vector<std::vector<double> > > chargedPFVertexChi2(new std::vector<std::vector<double > >());
  std::auto_ptr<std::vector<std::vector<double> > > chargedPFVertexNdof(new std::vector<std::vector<double > >());
  std::auto_ptr<std::vector<std::vector<double> > > chargedPFVertexMass(new std::vector<std::vector<double > >());
  std::auto_ptr<std::vector<std::vector<double> > > neutralPFHCALFrac(new std::vector<std::vector<double > >());


  int cntJetLowPt = 0;
  for(unsigned int ij=0; ij < extJets.size(); ij++)
  {
    const pat::Jet& jet = extJets[ij];

    if(jet.pt() < ak4ptCut_) continue;

    //const reco::TrackIPTagInfo *ipTagInfo = jet.tagInfoCandIP(ipTagInfos_.c_str());
    //const auto *ipTagInfo = jet.tagInfoCandIP(ipTagInfos_.c_str());
    //const auto *svTagInfo = jet.tagInfoCandSecondaryVertex(svTagInfos_.c_str());
    //
    //const auto *ipTagInfoCTag = jet.tagInfoCandIP(ipTagInfosCTag_.c_str());
    //const auto *svTagInfoCTag = jet.tagInfoCandSecondaryVertex(svTagInfosCTag_.c_str());
    //const reco::CandSoftLeptonTagInfo *softPFMuTagInfoCTag = jet.tagInfoCandSoftLepton(softPFMuonTagInfosCTag_.c_str());
    //const reco::CandSoftLeptonTagInfo *softPFElTagInfoCTag = jet.tagInfoCandSoftLepton(softPFElectronTagInfosCTag_.c_str()); 

    TLorentzVector perJetLVec;
    perJetLVec.SetPtEtaPhiE( jet.pt(), jet.eta(), jet.phi(), jet.energy() );
    jetsLVec->push_back(perJetLVec);

    //Additional jec qualities
    std::vector<std::string> availableJECSets   = jet.availableJECSets();
    std::vector<std::string> availableJECLevels = jet.availableJECLevels(jet.currentJECSet());
    double scaleRawToFull = jet.jecFactor(jet.currentJECLevel(), "none", jet.currentJECSet())/jet.jecFactor("Uncorrected", "none", jet.currentJECSet());
    //double scaleRawToFull = jet.jecFactor(availableJECLevels.back())/jet.jecFactor("Uncorrected");
    recoJetsJecScaleRawToFull->push_back(scaleRawToFull);
    if( debug_ && ij==0 )
    {
      std::cout<<"\nAvailable JEC sets:"<<"   current : "<<jet.currentJECSet().c_str()<<std::endl;
      for(unsigned int ia=0; ia<availableJECSets.size(); ia++)
      {
         std::cout<<"ia : "<<ia<<"  --> "<<availableJECSets[ia].c_str()<<std::endl;
      }
      std::cout<<"\nAvailable JEC levels:"<<"   current : "<<jet.currentJECLevel().c_str()<<std::endl;
      for(unsigned int ia=0; ia<availableJECLevels.size(); ia++)
      {
        std::cout<<"ia : "<<ia<<"  --> "<<availableJECLevels[ia].c_str()<<std::endl;
      }
      std::cout<<"scaleRawToFull : "<<scaleRawToFull<<"  current : "<<jet.jecFactor(availableJECLevels.back())<<"  uncor : "<<jet.jecFactor("Uncorrected")<<std::endl;
    }

    //get JEC unc for this jet, using corrected pT
    //jecUnc->setJetEta(jet.eta());
    //jecUnc->setJetPt(jet.pt());
    //
    //double uncertainty = jecUnc->getUncertainty(true);
    ////safety check if uncertainty is not available for a jet
    //if( uncertainty==-999. ) uncertainty = 0;
    //recoJetsJecUnc->push_back(uncertainty);

    if( perJetLVec.Pt() < jetPtCut_miniAOD_ && ij < jets->size() ) cntJetLowPt ++;

    int flavor = jet.partonFlavour();
    recoJetsFlavor->push_back(flavor);

    std::string toGetName = qgTaggerKey_+":qgLikelihood";
    if( ij >= jets->size() && qgTaggerKey_ == "QGTagger" ) toGetName = qgTaggerKey_+"Other:qgLikelihood";
    double thisqgLikelihood = jet.userFloat(toGetName.c_str());
    qgLikelihood->push_back(thisqgLikelihood);
 
    toGetName = qgTaggerKey_+":ptD";
    if( ij >= jets->size() && qgTaggerKey_ == "QGTagger" ) toGetName = qgTaggerKey_+"Other:ptD";
    double thisqgPtD = jet.userFloat(toGetName.c_str());
    qgPtD->push_back(thisqgPtD);
   
    toGetName = qgTaggerKey_+":axis1"; 
    if( ij >= jets->size() && qgTaggerKey_ == "QGTagger" ) toGetName = qgTaggerKey_+"Other:axis1";
    double thisqgAxis1 = jet.userFloat(toGetName.c_str());
    qgAxis1->push_back(thisqgAxis1);

    toGetName = qgTaggerKey_+":axis2"; 
    if( ij >= jets->size() && qgTaggerKey_ == "QGTagger" ) toGetName = qgTaggerKey_+"Other:axis2";
    double thisqgAxis2 = jet.userFloat(toGetName.c_str());
    qgAxis2->push_back(thisqgAxis2);
   
    toGetName = qgTaggerKey_+":mult"; 
    if( ij >= jets->size() && qgTaggerKey_ == "QGTagger" ) toGetName = qgTaggerKey_+"Other:mult";
    int thisqgMult = jet.userInt(toGetName.c_str());
    qgMult->push_back(thisqgMult);
/*
    toGetName = qgTaggerKey_+":ptDrLog";
    if( ij >= jets->size() && qgTaggerKey_ == "QGTagger" ) toGetName = qgTaggerKey_+"Other:ptDrLog";
    double thisqgPtDrLog = jet.userFloat(toGetName.c_str());
    qgPtDrLog->push_back(thisqgPtDrLog);

    toGetName = qgTaggerKey_+":axis1";
    if( ij >= jets->size() && qgTaggerKey_ == "QGTagger" ) toGetName = qgTaggerKey_+"Other:axis1";
    double thisqgAxis1 = jet.userFloat(toGetName.c_str());
    qgAxis1->push_back(thisqgAxis1);

    toGetName = qgTaggerKey_+":cmult";
    if( ij >= jets->size() && qgTaggerKey_ == "QGTagger" ) toGetName = qgTaggerKey_+"Other:cmult";
    int thisqgcMult = jet.userInt(toGetName.c_str());
    qgcMult->push_back(thisqgcMult);

    toGetName = qgTaggerKey_+":nmult";
    if( ij >= jets->size() && qgTaggerKey_ == "QGTagger" ) toGetName = qgTaggerKey_+"Other:nmult";
    int thisqgnMult = jet.userInt(toGetName.c_str());
    qgnMult->push_back(thisqgnMult);
*/

//      'pfDeepCSVJetTags:probudsg', 
//      'pfDeepCSVJetTags:probb', 
//      'pfDeepCSVJetTags:probc', 
//      'pfDeepCSVJetTags:probbb', 
//      'pfDeepFlavourJetTags:probb',
//      'pfDeepFlavourJetTags:probbb',
//      'pfDeepFlavourJetTags:problepb',
//      'pfDeepFlavourJetTags:probc',
//      'pfDeepFlavourJetTags:probuds',
//      'pfDeepFlavourJetTags:probg',


    float trialDeepFlavorb = jet.bDiscriminator((deepFlavorBJetTags_+":probb").c_str());
    DeepFlavorb->push_back(trialDeepFlavorb);

    float trialDeepFlavorbb = jet.bDiscriminator((deepFlavorBJetTags_+":probbb").c_str());
    DeepFlavorbb->push_back(trialDeepFlavorbb);

    float trialDeepFlavorlepb = jet.bDiscriminator((deepFlavorBJetTags_+":problepb").c_str());
    DeepFlavorlepb->push_back(trialDeepFlavorlepb);

    float trialDeepFlavorc = jet.bDiscriminator((deepFlavorBJetTags_+":probc").c_str());
    DeepFlavorc->push_back(trialDeepFlavorc);

    float trialDeepFlavoruds = jet.bDiscriminator((deepFlavorBJetTags_+":probuds").c_str());
    DeepFlavoruds->push_back(trialDeepFlavoruds);

    float trialDeepFlavorg = jet.bDiscriminator((deepFlavorBJetTags_+":probg").c_str());
    DeepFlavorg->push_back(trialDeepFlavorg);

    float trialDeepCSVb = jet.bDiscriminator((deepCSVBJetTags_+":probb").c_str());
    DeepCSVb->push_back(trialDeepCSVb);

    float trialDeepCSVc = jet.bDiscriminator((deepCSVBJetTags_+":probc").c_str());
    DeepCSVc->push_back(trialDeepCSVc);

    float trialDeepCSVl = jet.bDiscriminator((deepCSVBJetTags_+":probudsg").c_str());
    DeepCSVl->push_back(trialDeepCSVl);

    float trialDeepCSVbb = jet.bDiscriminator((deepCSVBJetTags_+":probbb").c_str());
    DeepCSVbb->push_back(trialDeepCSVbb);

    float trialDeepCSVcc = jet.bDiscriminator((deepCSVBJetTags_+":probcc").c_str());
    DeepCSVcc->push_back(trialDeepCSVcc);

    float trialDeepCSVbN = jet.bDiscriminator((deepCSVNegBJetTags_+":probb").c_str());
    DeepCSVbN->push_back(trialDeepCSVbN);

    float trialDeepCSVcN = jet.bDiscriminator((deepCSVNegBJetTags_+":probc").c_str());
    DeepCSVcN->push_back(trialDeepCSVcN);

    float trialDeepCSVlN = jet.bDiscriminator((deepCSVNegBJetTags_+":probudsg").c_str());
    DeepCSVlN->push_back(trialDeepCSVlN);

    float trialDeepCSVbbN = jet.bDiscriminator((deepCSVNegBJetTags_+":probbb").c_str());
    DeepCSVbbN->push_back(trialDeepCSVbbN);

    double trialDeepCSVccN = jet.bDiscriminator((deepCSVNegBJetTags_+":probcc").c_str());
    DeepCSVccN->push_back(trialDeepCSVccN);

    double trialDeepCSVbP = jet.bDiscriminator((deepCSVPosBJetTags_+":probb").c_str());
    DeepCSVbP->push_back(trialDeepCSVbP);

    double trialDeepCSVcP = jet.bDiscriminator((deepCSVPosBJetTags_+":probc").c_str());
    DeepCSVcP->push_back(trialDeepCSVcP);

    double trialDeepCSVlP = jet.bDiscriminator((deepCSVPosBJetTags_+":probudsg").c_str());
    DeepCSVlP->push_back(trialDeepCSVlP);

    double trialDeepCSVbbP = jet.bDiscriminator((deepCSVPosBJetTags_+":probbb").c_str());
    DeepCSVbbP->push_back(trialDeepCSVbbP);

    double trialDeepCSVccP = jet.bDiscriminator((deepCSVPosBJetTags_+":probcc").c_str());
    DeepCSVccP->push_back(trialDeepCSVccP);

    float tri_CombinedIVF =jet.bDiscriminator(combinedIVFSVBJetTags_.c_str());
    CombinedIVF->push_back(tri_CombinedIVF);

    float tri_CombinedIVF_P =jet.bDiscriminator(combinedIVFSVPosBJetTags_.c_str());
    CombinedIVFP ->push_back(tri_CombinedIVF_P);

    float tri_CombinedIVF_N =jet.bDiscriminator(combinedIVFSVNegBJetTags_.c_str());
    CombinedIVFN ->push_back(tri_CombinedIVF_N);

    double btag = jet.bDiscriminator(bTagKeyString_.c_str());
    recoJetsBtag->push_back(btag);

    double Proba = jet.bDiscriminator(jetPBJetTags_.c_str());
    JetProba->push_back(Proba);

    double ProbaN = jet.bDiscriminator(jetPNegBJetTags_.c_str());
    JetProbaN->push_back(ProbaN);

    double ProbaP = jet.bDiscriminator(jetPPosBJetTags_.c_str());
    JetProbaP->push_back(ProbaP);

    double Bprob = jet.bDiscriminator(jetBPBJetTags_.c_str());
    JetBprob->push_back(Bprob);

    double BprobN = jet.bDiscriminator(jetBPNegBJetTags_.c_str());
    JetBprobN->push_back(BprobN);

    double BprobP = jet.bDiscriminator(jetBPPosBJetTags_.c_str());
    JetBprobP->push_back(BprobP);

    double Tri_CombinedSvtx = jet.bDiscriminator(combinedSVBJetTags_.c_str());
    CombinedSvtx->push_back(Tri_CombinedSvtx);

    double Tri_CombinedSvtxN = jet.bDiscriminator(combinedSVNegBJetTags_.c_str());
    CombinedSvtxN->push_back(Tri_CombinedSvtxN);
    
    double Tri_CombinedSvtxP = jet.bDiscriminator(combinedSVPosBJetTags_.c_str());
    CombinedSvtxP-> push_back(Tri_CombinedSvtxP);

    float tri_Svtx = jet.bDiscriminator(simpleSVHighEffBJetTags_.c_str());
    Svtx  ->push_back(tri_Svtx);
    float tri_SvtxN = jet.bDiscriminator(simpleSVNegHighEffBJetTags_.c_str());
    SvtxN ->push_back(tri_SvtxN);
    float tri_SvtxHP  = jet.bDiscriminator(simpleSVHighPurBJetTags_.c_str());
    SvtxHP->push_back(tri_SvtxHP);
    float tri_SvtxNHP = jet.bDiscriminator(simpleSVNegHighPurBJetTags_.c_str());
    SvtxNHP->push_back(tri_SvtxNHP);

    float tri_SoftM  = jet.bDiscriminator(softPFMuonBJetTags_.c_str());
    SoftM->push_back(tri_SoftM);
    float tri_SoftMN = jet.bDiscriminator(softPFMuonNegBJetTags_.c_str());
    SoftMN->push_back(tri_SoftMN);
    float tri_SoftMP = jet.bDiscriminator(softPFMuonPosBJetTags_.c_str());
    SoftMP->push_back(tri_SoftMP);

    float tri_SoftE  = jet.bDiscriminator(softPFElectronBJetTags_.c_str());
    SoftE->push_back(tri_SoftE);
    float tri_SoftEN = jet.bDiscriminator(softPFElectronNegBJetTags_.c_str());
    SoftEN->push_back(tri_SoftEN);
    float tri_SoftEP = jet.bDiscriminator(softPFElectronPosBJetTags_.c_str());
    SoftEP->push_back(tri_SoftEP);

    float tri_DoubleSV = jet.bDiscriminator(doubleSVBJetTags_.c_str());
    DoubleSV->push_back(tri_DoubleSV);

    float tri_cMVA = jet.bDiscriminator(cMVABJetTags_.c_str());
    cMVA->push_back(tri_cMVA);
    float tri_cMVAv2 = jet.bDiscriminator(cMVAv2BJetTags_.c_str());
    cMVAv2->push_back(tri_cMVAv2);
    float tri_cMVAv2Neg = jet.bDiscriminator(cMVAv2NegBJetTags_.c_str());
    cMVAv2Neg->push_back(tri_cMVAv2Neg);
    float tri_cMVAv2Pos = jet.bDiscriminator(cMVAv2PosBJetTags_.c_str());
    cMVAv2Pos->push_back(tri_cMVAv2Pos);

    float tri_CvsB = jet.bDiscriminator(CvsBCJetTags_.c_str());
    CvsB->push_back(tri_CvsB);
    float tri_CvsBNeg = jet.bDiscriminator(CvsBNegCJetTags_.c_str());
    CvsBNeg->push_back(tri_CvsBNeg);
    float tri_CvsBPos = jet.bDiscriminator(CvsBPosCJetTags_.c_str());
    CvsBPos->push_back(tri_CvsBPos);
    float tri_CvsL = jet.bDiscriminator(CvsLCJetTags_.c_str());
    CvsL->push_back(tri_CvsL);
    float tri_CvsLNeg = jet.bDiscriminator(CvsLNegCJetTags_.c_str());
    CvsLNeg->push_back(tri_CvsLNeg);
    float tri_CvsLPos = jet.bDiscriminator(CvsLPosCJetTags_.c_str());
    CvsLPos->push_back(tri_CvsLPos);

    //reco::TaggingVariableList ipVars = ipTagInfo->taggingVariables();
    //reco::TaggingVariableList svVars = svTagInfo->taggingVariables();

    //int nTracks_tri = ipTagInfo->selectedTracks().size();
    //int nSVs_tri = svTagInfo->nVertices();

    // per jet
    //nTracks->push_back(nTracks_tri);
    //nSVs->push_back(nSVs_tri);

    double charge = jet.jetCharge();
    recoJetsCharge->push_back(charge);

    double chargedHadronEnergyFraction = jet.chargedHadronEnergyFraction();
    recoJetschargedHadronEnergyFraction->push_back( chargedHadronEnergyFraction );

    double neutralHadronEnergyFraction = jet.neutralHadronEnergyFraction();
    recoJetsneutralEnergyFraction->push_back( neutralHadronEnergyFraction );

    double chargedEmEnergyFraction = jet.chargedEmEnergyFraction();
    recoJetschargedEmEnergyFraction->push_back( chargedEmEnergyFraction );

    double neutralEmEnergyFraction = jet.neutralEmEnergyFraction();
    recoJetsneutralEmEnergyFraction->push_back( neutralEmEnergyFraction );

    double muonEnergyFraction = jet.muonEnergyFraction();
    recoJetsmuonEnergyFraction->push_back( muonEnergyFraction );

    double photonEnergyFraction = jet.photonEnergyFraction();
    PhotonEnergyFraction->push_back( photonEnergyFraction );

    double electronEnergyFraction = jet.electronEnergyFraction();
    ElectronEnergyFraction->push_back( electronEnergyFraction );

    recoJetsHFHadronEnergyFraction->push_back(jet.HFHadronEnergyFraction());
    recoJetsHFEMEnergyFraction->push_back(jet.HFEMEnergyFraction());

    double chargedHadronMultiplicity = jet.chargedHadronMultiplicity();
    ChargedHadronMultiplicity->push_back( chargedHadronMultiplicity );

    double neutralHadronMultiplicity = jet.neutralHadronMultiplicity();
    NeutralHadronMultiplicity->push_back( neutralHadronMultiplicity );

    double photonMultiplicity = jet.photonMultiplicity();
    PhotonMultiplicity->push_back( photonMultiplicity );

    double electronMultiplicity = jet.electronMultiplicity();
    ElectronMultiplicity->push_back( electronMultiplicity );

    double muonMultiplicity1 = jet.muonMultiplicity();
    MuonMultiplicity->push_back( muonMultiplicity1 );

    //std::vector<const reco::BaseTagInfo*>  baseTagInfos;
    //JetTagComputer::TagInfoHelper helper(baseTagInfos);
    //baseTagInfos.push_back( ipTagInfo );
    //baseTagInfos.push_back( svTagInfo );
    //// TaggingVariables
    //reco::TaggingVariableList vars = computer_->taggingVariables(helper);
    //
    //// btag inputs per jet
    //double trackJetPt_loc              = ( vars.checkTag(reco::btau::trackJetPt)              ? vars.get(reco::btau::trackJetPt) : -9999 );
    //double vertexCategory_loc          = ( vars.checkTag(reco::btau::vertexCategory)          ? vars.get(reco::btau::vertexCategory) : -9999 );
    //int    jetNSecondaryVertices_loc   = ( vars.checkTag(reco::btau::jetNSecondaryVertices)   ? vars.get(reco::btau::jetNSecondaryVertices) : 0 );
    //double trackSumJetEtRatio_loc      = ( vars.checkTag(reco::btau::trackSumJetEtRatio)      ? vars.get(reco::btau::trackSumJetEtRatio) : -9999 );
    //double trackSumJetDeltaR_loc       = ( vars.checkTag(reco::btau::trackSumJetDeltaR)       ? vars.get(reco::btau::trackSumJetDeltaR) : -9999 );
    //double trackSip2dValAboveCharm_loc = ( vars.checkTag(reco::btau::trackSip2dValAboveCharm) ? vars.get(reco::btau::trackSip2dValAboveCharm) : -9999 );
    //double trackSip2dSigAboveCharm_loc = ( vars.checkTag(reco::btau::trackSip2dSigAboveCharm) ? vars.get(reco::btau::trackSip2dSigAboveCharm) : -9999 );
    //double trackSip3dValAboveCharm_loc = ( vars.checkTag(reco::btau::trackSip3dValAboveCharm) ? vars.get(reco::btau::trackSip3dValAboveCharm) : -9999 );
    //double trackSip3dSigAboveCharm_loc = ( vars.checkTag(reco::btau::trackSip3dSigAboveCharm) ? vars.get(reco::btau::trackSip3dSigAboveCharm) : -9999 );
    //double vertexMass_loc              = ( vars.checkTag(reco::btau::vertexMass)              ? vars.get(reco::btau::vertexMass) : -9999 );
    //int    vertexNTracks_loc           = ( vars.checkTag(reco::btau::vertexNTracks)           ? vars.get(reco::btau::vertexNTracks) : 0 );
    //double vertexEnergyRatio_loc       = ( vars.checkTag(reco::btau::vertexEnergyRatio)       ? vars.get(reco::btau::vertexEnergyRatio) : -9999 );
    //double vertexJetDeltaR_loc         = ( vars.checkTag(reco::btau::vertexJetDeltaR)         ? vars.get(reco::btau::vertexJetDeltaR) : -9999 );
    //double flightDistance2dVal_loc     = ( vars.checkTag(reco::btau::flightDistance2dVal)     ? vars.get(reco::btau::flightDistance2dVal) : -9999 );
    //double flightDistance2dSig_loc     = ( vars.checkTag(reco::btau::flightDistance2dSig)     ? vars.get(reco::btau::flightDistance2dSig) : -9999 );
    //double flightDistance3dVal_loc     = ( vars.checkTag(reco::btau::flightDistance3dVal)     ? vars.get(reco::btau::flightDistance3dVal) : -9999 );
    //double flightDistance3dSig_loc     = ( vars.checkTag(reco::btau::flightDistance3dSig)     ? vars.get(reco::btau::flightDistance3dSig) : -9999 );
    //
    //CSV_trackJetPt->push_back(trackJetPt_loc);
    //CSV_vertexCategory->push_back(vertexCategory_loc);
    //CSV_jetNSecondaryVertices->push_back(jetNSecondaryVertices_loc);
    //CSV_trackSumJetEtRatio->push_back(trackSumJetEtRatio_loc);
    //CSV_trackSumJetDeltaR->push_back(trackSumJetDeltaR_loc);
    //CSV_trackSip2dValAboveCharm->push_back(trackSip2dValAboveCharm_loc);
    //CSV_trackSip2dSigAboveCharm->push_back(trackSip2dSigAboveCharm_loc);
    //CSV_trackSip3dValAboveCharm->push_back(trackSip3dValAboveCharm_loc);
    //CSV_trackSip3dSigAboveCharm->push_back(trackSip3dSigAboveCharm_loc);
    //CSV_vertexMass->push_back(vertexMass_loc);
    //CSV_vertexNTracks->push_back(vertexNTracks_loc);
    //CSV_vertexEnergyRatio->push_back(vertexEnergyRatio_loc);
    //CSV_vertexJetDeltaR->push_back(vertexJetDeltaR_loc);
    //CSV_flightDistance2dVal->push_back(flightDistance2dVal_loc);
    //CSV_flightDistance2dSig->push_back(flightDistance2dSig_loc);
    //CSV_flightDistance3dVal->push_back(flightDistance3dVal_loc);
    //CSV_flightDistance3dSig->push_back(flightDistance3dSig_loc);
    //
    ////charm tagger info 
    //std::vector<const reco::BaseTagInfo*>  slbaseTagInfos;
    //slbaseTagInfos.push_back( ipTagInfoCTag );
    //slbaseTagInfos.push_back( svTagInfoCTag );
    //slbaseTagInfos.push_back( softPFMuTagInfoCTag );
    //slbaseTagInfos.push_back( softPFElTagInfoCTag ); 
    //JetTagComputer::TagInfoHelper slhelper(slbaseTagInfos);
    //// TaggingVariables
    //reco::TaggingVariableList slvars = slcomputer_->taggingVariables(slhelper);
    //
    //// per jet
    //CTag_vertexCategory->           push_back( slvars.checkTag(reco::btau::vertexCategory)           ? slvars.get(reco::btau::vertexCategory)            : -9999 );
    //CTag_jetNSecondaryVertices->    push_back( slvars.checkTag(reco::btau::jetNSecondaryVertices)    ? slvars.get(reco::btau::jetNSecondaryVertices)     : 0 );
    //CTag_trackSumJetEtRatio->       push_back( slvars.checkTag(reco::btau::trackSumJetEtRatio)       ? slvars.get(reco::btau::trackSumJetEtRatio)        : -9999 );
    //CTag_trackSumJetDeltaR->        push_back( slvars.checkTag(reco::btau::trackSumJetDeltaR)        ? slvars.get(reco::btau::trackSumJetDeltaR)         : -9999 );
    //CTag_trackSip2dSigAboveCharm->  push_back( slvars.checkTag(reco::btau::trackSip2dSigAboveCharm)  ? slvars.get(reco::btau::trackSip2dSigAboveCharm)   : -9999 );
    //CTag_trackSip3dSigAboveCharm->  push_back( slvars.checkTag(reco::btau::trackSip3dSigAboveCharm)  ? slvars.get(reco::btau::trackSip3dSigAboveCharm)   : -9999 );
    //CTag_vertexMass->               push_back( slvars.checkTag(reco::btau::vertexMass)               ? slvars.get(reco::btau::vertexMass)                : -9999 );
    //CTag_vertexNTracks->            push_back( slvars.checkTag(reco::btau::vertexNTracks)            ? slvars.get(reco::btau::vertexNTracks)             : 0 );
    //CTag_vertexEnergyRatio->        push_back( slvars.checkTag(reco::btau::vertexEnergyRatio)        ? slvars.get(reco::btau::vertexEnergyRatio)         : -9999 );
    //CTag_vertexJetDeltaR->          push_back( slvars.checkTag(reco::btau::vertexJetDeltaR)          ? slvars.get(reco::btau::vertexJetDeltaR)           : -9999 );
    //CTag_flightDistance2dSig->      push_back( slvars.checkTag(reco::btau::flightDistance2dSig)      ? slvars.get(reco::btau::flightDistance2dSig)       : -9999 );
    //CTag_flightDistance3dSig->      push_back( slvars.checkTag(reco::btau::flightDistance3dSig)      ? slvars.get(reco::btau::flightDistance3dSig)       : -9999 );
    //CTag_massVertexEnergyFraction-> push_back( slvars.checkTag(reco::btau::massVertexEnergyFraction) ? slvars.get(reco::btau::massVertexEnergyFraction)  : -0.1);
    //CTag_vertexBoostOverSqrtJetPt-> push_back( slvars.checkTag(reco::btau::vertexBoostOverSqrtJetPt) ? slvars.get(reco::btau::vertexBoostOverSqrtJetPt)  : -0.1);
    //CTag_vertexLeptonCategory->     push_back( slvars.checkTag(reco::btau::vertexLeptonCategory)     ? slvars.get(reco::btau::vertexLeptonCategory)      : -1);      

    std::vector<TLorentzVector> pfCandChargedLV;
    std::vector<TLorentzVector> pfCandNeutralLV;
    std::vector<double> pfCandChargedDxy;
    std::vector<double> pfCandChargedDz;
    std::vector<double> pfCandChargedFromPV;
    std::vector<double> pfCandChargedVertexChi2;
    std::vector<double> pfCandChargedVertexNdof;
    std::vector<double> pfCandChargedVertexMass;
    std::vector<double> pfCandNeutralHCALFrac;
    int chargedCand = 25;
    int neutralCand = 25;
    //create collection first, to be able to do some sorting
    for (unsigned int i = 0; i < jet.numberOfDaughters() && (chargedCand || neutralCand); i++)
    {
        const pat::PackedCandidate* packedCand = dynamic_cast<const pat::PackedCandidate*>(jet.daughter(i));
        if(packedCand)
        {
            /// Split to charged and neutral candidates
            if(packedCand->charge()!=0)
            {
                if(chargedCand == 0) continue;
                --chargedCand;
                TLorentzVector tmpVec;
                tmpVec.SetPtEtaPhiE(packedCand->pt(), packedCand->eta(), packedCand->phi(), packedCand->energy());
                pfCandChargedLV.push_back(tmpVec);
                pfCandChargedDxy.push_back(packedCand->dxy());
                packedCand->dxyError();
                pfCandChargedDz.push_back(packedCand->dz());
                packedCand->pvAssociationQuality();

                pfCandChargedFromPV.push_back(packedCand->fromPV());

                pfCandChargedVertexChi2.push_back(packedCand->vertexChi2());
                pfCandChargedVertexNdof.push_back(packedCand->vertexNdof());
                //divided
                packedCand->vertexNormalizedChi2();
                packedCand->vertex().rho();
                packedCand->vertex().phi();
                pfCandChargedVertexMass.push_back(packedCand->vertexRef()->p4().M());
                packedCand->puppiWeight();
                 
                packedCand->charge();
                packedCand->lostInnerHits();
                
            }
            else // neutral candidates
            {
                if(neutralCand == 0) continue;
                --neutralCand;
                TLorentzVector tmpVec;
                tmpVec.SetPtEtaPhiE(packedCand->pt(), packedCand->eta(), packedCand->phi(), packedCand->energy());
                pfCandNeutralLV.push_back(tmpVec);
                packedCand->puppiWeight();
                packedCand->pdgId();
                pfCandNeutralHCALFrac.push_back(packedCand->hcalFraction());
            }
        }
    }
    //DO NOT try to use the origional vectors after the move!
    chargedPFCandLV->emplace_back(std::move(pfCandChargedLV));
    neutralPFCandLV->emplace_back(std::move(pfCandNeutralLV));
    chargedPFDxy->emplace_back(std::move(pfCandChargedDxy));
    chargedPFDz->emplace_back(std::move(pfCandChargedDz));
    chargedPFFromPV->emplace_back(std::move(pfCandChargedFromPV));
    chargedPFVertexChi2->emplace_back(std::move(pfCandChargedVertexChi2));
    chargedPFVertexNdof->emplace_back(std::move(pfCandChargedVertexNdof));
    chargedPFVertexMass->emplace_back(std::move(pfCandChargedVertexMass));
    neutralPFHCALFrac->emplace_back(std::move(pfCandNeutralHCALFrac));

  }

  //AK8 jets
  ////std::auto_ptr<std::vector<TLorentzVector> > puppiAK8LVec(new std::vector<TLorentzVector>());
  ////std::auto_ptr<std::vector<double> > puppiAK8Tau1(new std::vector<double>());
  ////std::auto_ptr<std::vector<double> > puppiAK8Tau2(new std::vector<double>());
  ////std::auto_ptr<std::vector<double> > puppiAK8Tau3(new std::vector<double>());
  ////std::auto_ptr<std::vector<double> > puppiAK8SoftDropMass(new std::vector<double>());
  ////
  ////std::auto_ptr<std::vector<std::vector<TLorentzVector> > > puppiAK8SubjetLVec(new std::vector<std::vector<TLorentzVector> >());
  ////std::auto_ptr<std::vector<std::vector<double> > > puppiAK8SubjetMult(new std::vector<std::vector<double > >());
  ////std::auto_ptr<std::vector<std::vector<double> > > puppiAK8SubjetPtD(new std::vector<std::vector<double > >());
  ////std::auto_ptr<std::vector<std::vector<double> > > puppiAK8SubjetAxis1(new std::vector<std::vector<double > >());
  ////std::auto_ptr<std::vector<std::vector<double> > > puppiAK8SubjetAxis2(new std::vector<std::vector<double > >());
  ////std::auto_ptr<std::vector<std::vector<double> > > puppiAK8SubjetBDisc(new std::vector<std::vector<double > >());
  ////
  ////for(const pat::Jet& jet : *ak8Jets)
  ////{
  ////    if(jet.pt() < ak8ptCut_) continue;
  ////
  ////    TLorentzVector perJetLVec;
  ////    perJetLVec.SetPtEtaPhiE( jet.pt(), jet.eta(), jet.phi(), jet.energy() );
  ////
  ////    double puppi_tau1_uf         = jet.userFloat(NjettinessAK8Puppi_label_+":tau1");
  ////    double puppi_tau2_uf         = jet.userFloat(NjettinessAK8Puppi_label_+":tau2");
  ////    double puppi_tau3_uf         = jet.userFloat(NjettinessAK8Puppi_label_+":tau3");
  ////    double puppisoftDropMass_uf  = jet.userFloat(ak8PFJetsPuppi_label_+"SoftDropMass");
  ////
  ////    puppiAK8LVec->push_back(perJetLVec);
  ////    puppiAK8Tau1->push_back(puppi_tau1_uf);
  ////    puppiAK8Tau2->push_back(puppi_tau2_uf);
  ////    puppiAK8Tau3->push_back(puppi_tau3_uf);
  ////    puppiAK8Tau3->push_back(puppisoftDropMass_uf);
  ////
  ////
  ////    puppiAK8SubjetLVec->push_back(std::vector<TLorentzVector>());
  ////    puppiAK8SubjetMult->push_back(std::vector<double>());
  ////    puppiAK8SubjetPtD->push_back(std::vector<double>());
  ////    puppiAK8SubjetAxis1->push_back(std::vector<double>());
  ////    puppiAK8SubjetAxis2->push_back(std::vector<double>());
  ////    puppiAK8SubjetBDisc->push_back(std::vector<double>());
  ////
  ////    auto const & subjets = jet.subjets("SoftDrop");
  ////    for( auto const & it : subjets)
  ////    {
  ////        TLorentzVector perSubJetLVec;
  ////        perSubJetLVec.SetPtEtaPhiE( jet.pt(), jet.eta(), jet.phi(), jet.energy() );
  ////
  ////        // btag info
  ////        double subjetBDiscriminator = it->bDiscriminator(bTagKeyString_.c_str());
  ////
  ////        //compute the qg input variables for the subjet
  ////        double totalMult = 0;
  ////        double ptD       = 0;
  ////        double axis1     = 0;
  ////        double axis2     = 0;
  ////        compute(dynamic_cast<const pat::Jet *>(&(*it)), true, totalMult, ptD, axis1, axis2);
  ////
  ////        puppiAK8SubjetLVec->back().push_back(perSubJetLVec);
  ////        puppiAK8SubjetMult->back().push_back(totalMult);
  ////        puppiAK8SubjetPtD->back().push_back(ptD);
  ////        puppiAK8SubjetAxis1->back().push_back(axis1);
  ////        puppiAK8SubjetAxis2->back().push_back(axis2);
  ////        puppiAK8SubjetBDisc->back().push_back(subjetBDiscriminator);
  ////    }
  ////}

  ////iEvent.put(puppiAK8LVec, "puppiAK8LVec");
  ////iEvent.put(puppiAK8Tau1, "puppiAK8Tau1");
  ////iEvent.put(puppiAK8Tau2, "puppiAK8Tau2");
  ////iEvent.put(puppiAK8Tau3, "puppiAK8Tau3");
  ////iEvent.put(puppiAK8SoftDropMass, "puppiAK8SoftDropMass");
  ////
  ////iEvent.put(puppiAK8SubjetLVec, "puppiAK8SubjetLVec");
  ////iEvent.put(puppiAK8SubjetMult, "puppiAK8SubjetMult");
  ////iEvent.put(puppiAK8SubjetPtD, "puppiAK8SubjetPtD");
  ////iEvent.put(puppiAK8SubjetAxis1, "puppiAK8SubjetAxis1");
  ////iEvent.put(puppiAK8SubjetAxis2, "puppiAK8SubjetAxis2");
  ////iEvent.put(puppiAK8SubjetBDisc, "puppiAK8SubjetBDisc");

  //const->push_back(}

  //const_loc);
  
  // store in the event
  // iEvent.put(prod);
  iEvent.put(jetsLVec, "jetsLVec");
  iEvent.put(recoJetsFlavor, "recoJetsFlavor");
  iEvent.put(recoJetsBtag, "recoJetsBtag");

  iEvent.put(JetProba, "JetProba");
  iEvent.put(JetProbaN, "JetProbaN");
  iEvent.put(JetProbaP, "JetProbaP");
  iEvent.put(JetBprob, "JetBprob");
  iEvent.put(JetBprobP, "JetBprobP");
  iEvent.put(JetBprobN, "JetBprobN");

  iEvent.put(recoJetsCharge, "recoJetsCharge");
  iEvent.put(recoJetsJecUnc, "recoJetsJecUnc");
  iEvent.put(recoJetsJecScaleRawToFull, "recoJetsJecScaleRawToFull");
  //iEvent.put(nJets, "nJets");

  iEvent.put(qgLikelihood, "qgLikelihood");
  iEvent.put(qgPtD, "qgPtD");
  iEvent.put(qgAxis1, "qgAxis1");
  iEvent.put(qgAxis2, "qgAxis2");
  iEvent.put(qgMult, "qgMult");
/*
  iEvent.put(qgPtDrLog, "qgPtDrLog");
  iEvent.put(qgAxis1, "qgAxis1");
  iEvent.put(qgcMult, "qgcMult");
  iEvent.put(qgnMult, "qgnMult");
*/
  iEvent.put(DeepCSVb,"DeepCSVb");
  iEvent.put(DeepCSVc,"DeepCSVc");
  iEvent.put(DeepCSVl,"DeepCSVl");
  iEvent.put(DeepCSVbb,"DeepCSVbb");
  iEvent.put(DeepCSVcc,"DeepCSVcc");

  iEvent.put(DeepCSVbN,"DeepCSVbN");
  iEvent.put(DeepCSVcN,"DeepCSVcN");
  iEvent.put(DeepCSVlN,"DeepCSVlN");
  iEvent.put(DeepCSVbbN,"DeepCSVbbN");
  iEvent.put(DeepCSVccN,"DeepCSVccN");

  iEvent.put(DeepCSVbP,"DeepCSVbP");
  iEvent.put(DeepCSVcP,"DeepCSVcP");
  iEvent.put(DeepCSVlP,"DeepCSVlP");
  iEvent.put(DeepCSVbbP,"DeepCSVbbP");
  iEvent.put(DeepCSVccP,"DeepCSVccP");

  iEvent.put(DeepFlavorb, "DeepFlavorb");
  iEvent.put(DeepFlavorbb, "DeepFlavorbb");
  iEvent.put(DeepFlavorlepb, "DeepFlavorlepb");
  iEvent.put(DeepFlavorc, "DeepFlavorc");
  iEvent.put(DeepFlavoruds, "DeepFlavoruds");
  iEvent.put(DeepFlavorg, "DeepFlavorg");

  iEvent.put(CombinedSvtx,"CombinedSvtx");
  iEvent.put(CombinedSvtxN,"CombinedSvtxN");
  iEvent.put(CombinedSvtxP,"CombinedSvtxP");

  iEvent.put(CombinedIVF,"CombinedIVF");
  iEvent.put(CombinedIVFP,"CombinedIVFP");
  iEvent.put(CombinedIVFN,"CombinedIVFN");

  iEvent.put(Svtx,"Svtx");
  iEvent.put(SvtxN,"SvtxN");
  iEvent.put(SvtxHP,"SvtxHP");
  iEvent.put(SvtxNHP,"SvtxNHP");

  iEvent.put(SoftM,"SoftM");
  iEvent.put(SoftMN,"SoftMN");
  iEvent.put(SoftMP,"SoftMP");

  iEvent.put(SoftE,"SoftE");
  iEvent.put(SoftEN,"SoftEN");
  iEvent.put(SoftEP,"SoftEP");

  iEvent.put(DoubleSV,"DoubleSV");

  iEvent.put(cMVA,"cMVA");
  iEvent.put(cMVAv2,"cMVAv2");
  iEvent.put(cMVAv2Neg,"cMVAv2Neg");
  iEvent.put(cMVAv2Pos,"cMVAv2Pos");

  iEvent.put(CvsB,"CvsB");
  iEvent.put(CvsBNeg,"CvsBNeg");
  iEvent.put(CvsBPos,"CvsBPos");
  iEvent.put(CvsL,"CvsL");
  iEvent.put(CvsLNeg,"CvsLNeg");
  iEvent.put(CvsLPos,"CvsLPos");

  //iEvent.put(nTracks,"nTracks");
  //iEvent.put(nSVs,"nSVs");

  iEvent.put(recoJetschargedHadronEnergyFraction, "recoJetschargedHadronEnergyFraction");
  iEvent.put(recoJetsneutralEnergyFraction, "recoJetsneutralEnergyFraction");
  iEvent.put(recoJetschargedEmEnergyFraction, "recoJetschargedEmEnergyFraction");
  iEvent.put(recoJetsneutralEmEnergyFraction, "recoJetsneutralEmEnergyFraction");
  iEvent.put(recoJetsHFHadronEnergyFraction, "recoJetsHFHadronEnergyFraction");
  iEvent.put(recoJetsHFEMEnergyFraction, "recoJetsHFEMEnergyFraction");


  iEvent.put(recoJetsmuonEnergyFraction, "recoJetsmuonEnergyFraction");
  iEvent.put(PhotonEnergyFraction, "PhotonEnergyFraction");
  iEvent.put(ElectronEnergyFraction, "ElectronEnergyFraction");

  iEvent.put(ChargedHadronMultiplicity, "ChargedHadronMultiplicity");
  iEvent.put(NeutralHadronMultiplicity, "NeutralHadronMultiplicity");
  iEvent.put(PhotonMultiplicity, "PhotonMultiplicity");
  iEvent.put(ElectronMultiplicity, "ElectronMultiplicity");
  iEvent.put(MuonMultiplicity, "MuonMultiplicity");

  //iEvent.put(CSV_trackJetPt,                "CSVTrackJetPt");
  //iEvent.put(CSV_vertexCategory,            "CSVVertexCategory");
  //iEvent.put(CSV_jetNSecondaryVertices,     "CSVJetNSecondaryVertices");
  //iEvent.put(CSV_trackSumJetEtRatio,        "CSVTrackSumJetEtRatio");
  //iEvent.put(CSV_trackSumJetDeltaR,         "CSVTrackSumJetDeltaR");
  //iEvent.put(CSV_trackSip2dValAboveCharm,   "CSVTrackSip2dValAboveCharm");
  //iEvent.put(CSV_trackSip2dSigAboveCharm,   "CSVTrackSip2dSigAboveCharm");
  //iEvent.put(CSV_trackSip3dValAboveCharm,   "CSVTrackSip3dValAboveCharm");
  //iEvent.put(CSV_trackSip3dSigAboveCharm,   "CSVTrackSip3dSigAboveCharm");
  //iEvent.put(CSV_vertexMass,                "CSVVertexMass");
  //iEvent.put(CSV_vertexNTracks,             "CSVVertexNTracks");
  //iEvent.put(CSV_vertexEnergyRatio,         "CSVVertexEnergyRatio");
  //iEvent.put(CSV_vertexJetDeltaR,           "CSVVertexJetDeltaR");
  //iEvent.put(CSV_flightDistance2dVal,       "CSVFlightDistance2dVal");
  //iEvent.put(CSV_flightDistance2dSig,       "CSVFlightDistance2dSig");
  //iEvent.put(CSV_flightDistance3dVal,       "CSVFlightDistance3dVal");
  //iEvent.put(CSV_flightDistance3dSig,       "CSVFlightDistance3dSig");
  //
  //iEvent.put(CTag_vertexCategory,           "CTagVertexCategory");
  //iEvent.put(CTag_jetNSecondaryVertices,    "CTagJetNSecondaryVertices");
  //iEvent.put(CTag_trackSumJetEtRatio,       "CTagTrackSumJetEtRatio");
  //iEvent.put(CTag_trackSumJetDeltaR,        "CTagTrackSumJetDeltaR");
  //iEvent.put(CTag_trackSip2dSigAboveCharm,  "CTagTrackSip2dSigAboveCharm");
  //iEvent.put(CTag_trackSip3dSigAboveCharm,  "CTagTrackSip3dSigAboveCharm");
  //iEvent.put(CTag_vertexMass,               "CTagVertexMass");
  //iEvent.put(CTag_vertexNTracks,            "CTagVertexNTracks");
  //iEvent.put(CTag_vertexEnergyRatio,        "CTagVertexEnergyRatio");
  //iEvent.put(CTag_vertexJetDeltaR,          "CTagVertexJetDeltaR");
  //iEvent.put(CTag_flightDistance2dSig,      "CTagFlightDistance2dSig");
  //iEvent.put(CTag_flightDistance3dSig,      "CTagFlightDistance3dSig");
  //iEvent.put(CTag_massVertexEnergyFraction, "CTagMassVertexEnergyFraction");
  //iEvent.put(CTag_vertexBoostOverSqrtJetPt, "CTagVertexBoostOverSqrtJetPt");
  //iEvent.put(CTag_vertexLeptonCategory,     "CTagVertexLeptonCategory");

  iEvent.put(chargedPFCandLV, "chargedPFCandLV");
  iEvent.put(neutralPFCandLV, "neutralPFCandLV");

  iEvent.put(chargedPFDxy, "chargedPFDxy");
  iEvent.put(chargedPFDz, "chargedPFDz");
  iEvent.put(chargedPFFromPV, "chargedPFFromPV");
  iEvent.put(chargedPFVertexChi2, "chargedPFVertexChi2");
  iEvent.put(chargedPFVertexNdof, "chargedPFVertexNdof");
  iEvent.put(chargedPFVertexMass, "chargedPFVertexMass");
  iEvent.put(neutralPFHCALFrac, "neutralPFHCALFrac");

  return true;
}
  

#include "FWCore/Framework/interface/MakerMacros.h"

DEFINE_FWK_MODULE(prodJets);
