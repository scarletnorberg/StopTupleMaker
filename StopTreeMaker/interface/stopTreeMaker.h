#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
// additional headers
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "FWCore/Utilities/interface/EDMException.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "DataFormats/Provenance/interface/EventAuxiliary.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "TString.h"
#include "TTree.h"
#include <TFile.h>
#include <vector>
#include "TLorentzVector.h"
#include "Math/GenVector/LorentzVector.h"
#include <DataFormats/Math/interface/deltaR.h>
#include "DataFormats/PatCandidates/interface/PackedGenParticle.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"

#include "DataFormats/PatCandidates/interface/PackedCandidate.h"
//
// class declaration
//

class stopTreeMaker : public edm::EDProducer {
public:
  explicit stopTreeMaker(const edm::ParameterSet&);
  ~stopTreeMaker();
  static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);
private:
  virtual void beginJob() override;
  virtual void produce(edm::Event&, const edm::EventSetup&) override;
  virtual void endJob() override;
  // ----------member data ---------------------------
  const unsigned int nMaxCandidates_;
  void setBranchVariablesToDefault();
  TString treeName_;
  TTree* tree_;	
  bool debug_;
  // generell event information
  UInt_t runNum_;      
  UInt_t lumiBlockNum_;
  ULong64_t evtNum_;
  
  // any float precision varialbes
  std::vector<edm::InputTag> varsDoubleTags_;
  std::vector<std::string> varsDoubleNames_;
  std::vector<double> varsDouble_;
  std::vector<TString> varsDoubleNamesCached_;

  std::vector<edm::InputTag> varsFloatTags_;
  std::vector<std::string> varsFloatNames_;
  std::vector<float> varsFloat_;
  std::vector<TString> varsFloatNamesCached_;

  std::vector<edm::EDGetTokenT<float>>VarsFloatTok_; 
  std::vector<edm::EDGetTokenT<double>>VarsDoubleTok_;
  std::vector<edm::EDGetTokenT<int>>VarsIntTok_;
  // any int precision varialbes
  std::vector<edm::InputTag> varsIntTags_;
  std::vector<std::string> varsIntNames_;
  std::vector<int> varsInt_;
  std::vector<TString> varsIntNamesCached_;
  // any bool precision varialbes
  std::vector<edm::InputTag> varsBoolTags_;
  std::vector<std::string> varsBoolNames_;
  std::vector<unsigned int> varsBool_;
  std::vector<TString> varsBoolNamesCached_;
  
  std::vector<edm::EDGetTokenT<bool>>VarsBoolTok_;
  // any string precision varialbes
  std::vector<edm::InputTag> varsStringTags_;
  std::vector<std::string> varsStringNames_;
  std::vector<std::string> varsString_;
  std::vector<TString> varsStringNamesCached_;
  
  std::vector<edm::EDGetTokenT<std::string>>VarsStringTok_;  

  // any TLorentzVector precision varialbes
  std::vector<edm::InputTag> varsTLorentzVectorTags_;
  std::vector<std::string> varsTLorentzVectorNames_;
  std::vector<TLorentzVector> varsTLorentzVector_;
  std::vector<TString> varsTLorentzVectorNamesCached_;
  
  std::vector<edm::EDGetTokenT<TLorentzVector>> VarsTLorentzVectorTok_;
  
  // any float precision varialbes
  std::vector<edm::InputTag> vectorDoubleTags_;
  std::vector<std::string> vectorDoubleNames_;
  std::vector<std::vector<double> > vectorDoubleVector_;
  std::vector<TString> vectorDoubleNamesCached_;

  std::vector<edm::InputTag> vectorFloatTags_;
  std::vector<std::string> vectorFloatNames_;
  std::vector<std::vector<float> > vectorFloatVector_;
  std::vector<TString> vectorFloatNamesCached_;

  std::vector<edm::EDGetTokenT<std::vector<float> >>VectorFloatTok_;

  std::vector<edm::EDGetTokenT<std::vector<double> >>VectorDoubleTok_;

  // any int precision varialbes
  std::vector<edm::InputTag> vectorIntTags_;
  std::vector<std::string> vectorIntNames_;
  std::vector<std::vector<int> > vectorIntVector_;
  std::vector<TString> vectorIntNamesCached_;
 
  std::vector<edm::EDGetTokenT<std::vector<int> >>VectorIntTok_; 
 
 // any bool precision varialbes
  std::vector<edm::InputTag> vectorBoolTags_;
  std::vector<std::string> vectorBoolNames_;
  std::vector<std::vector<unsigned int> > vectorBoolVector_;
  std::vector<TString> vectorBoolNamesCached_;

  std::vector<edm::EDGetTokenT<std::vector<bool> >>VectorBoolTok_;  

  // any string precision varialbes
  std::vector<edm::InputTag> vectorStringTags_;
  std::vector<std::string> vectorStringNames_;
  std::vector<std::vector<std::string> > vectorStringVector_;
  std::vector<TString> vectorStringNamesCached_;
  
  std::vector<edm::EDGetTokenT<std::vector<std::string> >>VectorStringTok_;
  
  // any TLorentzVector precision varialbes
  std::vector<edm::InputTag> vectorTLorentzVectorTags_;
  std::vector<std::string> vectorTLorentzVectorNames_;
  std::vector<std::vector<TLorentzVector> > vectorTLorentzVector_;
  std::vector<TString> vectorTLorentzVectorNamesCached_;

  std::vector<edm::EDGetTokenT<std::vector<TLorentzVector> >>VectorTLorentzVectorTags_;

  // any vector<TLorentzVector> precision varialbes
  std::vector<edm::InputTag> vectorVectorTLorentzVectorTags_;
  std::vector<std::string> vectorVectorTLorentzVectorNames_;
  std::vector<std::vector<std::vector<TLorentzVector> > > vectorVectorTLorentzVector_;
  std::vector<TString> vectorVectorTLorentzVectorNamesCached_;

  std::vector<edm::EDGetTokenT<std::vector<std::vector<TLorentzVector>> >>VectorVectorTLorentzVectorTags_;

  // any vector<double> precision variables
  std::vector<edm::InputTag> vectorVectorDoubleTags_;
  std::vector<std::string> vectorVectorDoubleNames_;
  std::vector<std::vector<std::vector<double> > > vectorVectorDouble_;
  std::vector<TString> vectorVectorDoubleNamesCached_;

  std::vector<edm::EDGetTokenT<std::vector<std::vector<double>> >>VectorVectorDoubleTags_;
  
  // any vector<float> precision variables
  
  std::vector<edm::InputTag> vectorVectorFloatTags_;
  std::vector<std::string> vectorVectorFloatNames_;
  std::vector<std::vector<std::vector<float> > > vectorVectorFloat_;
  std::vector<TString> vectorVectorFloatNamesCached_;

  std::vector<edm::EDGetTokenT<std::vector<std::vector<float>> >>VectorVectorFloatTags_;

  TString formBranchName(const edm::InputTag & varTag, const std::vector<std::string> & vectorNames);

  std::vector<TString> cachedNames_;

};
