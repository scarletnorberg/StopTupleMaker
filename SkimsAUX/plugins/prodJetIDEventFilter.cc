
#include <memory>
#include "FWCore/Framework/interface/EDFilter.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DataFormats/Common/interface/View.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/MET.h"


class prodJetIDEventFilter : public edm::EDFilter
{
 public:
  explicit prodJetIDEventFilter(const edm::ParameterSet & iConfig);
  ~prodJetIDEventFilter();
 private:
  virtual bool filter(edm::Event & iEvent, const edm::EventSetup & iSetup) override;
  edm::EDGetTokenT<edm::View<pat::Jet> > theJetToken_;
  //Default are for Jet ID, loose and tight (https://twiki.cern.ch/twiki/bin/viewauth/CMS/JetID#Recommendations_for_13_TeV_data)
  const double minJetPt_, maxJetEta_;
  //Eta smaller than 2.7
  const double maxNeutHadF_Loose_EtaLe27_, maxNeutEmF_Loose_EtaLe27_; 
  const int minNumCon_Loose_EtaLe27_; 
  const double maxNeutHadF_Tight_EtaLe27_, maxNeutEmF_Tight_EtaLe27_;
  const int minNumCon_Tight_EtaLe27_;
  const double maxNeutHadF_TightLepVeto_EtaLe27_, maxNeutEmF_TightLepVeto_EtaLe27_;
  const int minNumCon_TightLepVeto_EtaLe27_;
  const double maxMuF_TightLepVeto_EtaLe27_;
  //Additional Eta smaller than 2.4
  const double minChargHadF_Loose_EtaLe24_;  
  const int minChargMulti_Loose_EtaLe24_;
  const double maxChargEmF_Loose_EtaLe24_;
  const double minChargHadF_Tight_EtaLe24_;
  const int minChargMulti_Tight_EtaLe24_;
  const double maxChargEmF_Tight_EtaLe24_;
  const double minChargHadF_TightLepVeto_EtaLe24_;
  const int minChargMulti_TightLepVeto_EtaLe24_;
  const double maxChargEmF_TightLepVeto_EtaLe24_;
  //Eta 2.7 to 3.0
  const double minNeutEmF_Loose_Eta27to30_, maxNeutHadF_Loose_Eta27to30_; 
  const int minNumNeutPart_Loose_Eta27to30_;
  const double minNeutEmF_Tight_Eta27to30_, maxNeutHadF_Tight_Eta27to30_;
  const int minNumNeutPart_Tight_Eta27to30_;
  //Eta greater than 3.0
  const double maxNeutEmF_Loose_EtaGe30_; 
  const int minNumNeutPart_Loose_EtaGe30_;
  const double maxNeutEmF_Tight_EtaGe30_;   
  const int minNumNeutPart_Tight_EtaGe30_;

  const bool debug_;
  const bool taggingMode_;
};



prodJetIDEventFilter::prodJetIDEventFilter(const edm::ParameterSet & iConfig)
   : theJetToken_ (consumes<edm::View<pat::Jet> >(iConfig.getParameter<edm::InputTag>("JetSource") ))
   , minJetPt_ (iConfig.getParameter<double>("MinJetPt") )
   , maxJetEta_ (iConfig.getParameter<double>("MaxJetEta") )
   //JetID parameter for different Eta range and Loose/Tight
   //Eta smaller than 2.7
   , maxNeutHadF_Loose_EtaLe27_ (iConfig.getUntrackedParameter<double>("MaxNeutralHadFrac_Loose_EtaLe27", 0.99) )
   , maxNeutEmF_Loose_EtaLe27_  (iConfig.getUntrackedParameter<double>("MaxNeutralEMFrac_Loose_EtaLe27", 0.99) )
   , minNumCon_Loose_EtaLe27_ (iConfig.getUntrackedParameter<int>("MinNumberOfConstituents_Loose_EtaLe27", 1) )
   , maxNeutHadF_Tight_EtaLe27_ (iConfig.getUntrackedParameter<double>("MaxNeutralHadFrac_Tight_EtaLe27", 0.90) )
   , maxNeutEmF_Tight_EtaLe27_  (iConfig.getUntrackedParameter<double>("MaxNeutralEMFrac_Tight_EtaLe27", 0.90) )
   , minNumCon_Tight_EtaLe27_ (iConfig.getUntrackedParameter<int>("MinNumberOfConstituents_Tight_EtaLe27", 1) )
   , maxNeutHadF_TightLepVeto_EtaLe27_ (iConfig.getUntrackedParameter<double>("MaxNeutralHadFrac_TightLepVeto_EtaLe27", 0.90) )
   , maxNeutEmF_TightLepVeto_EtaLe27_  (iConfig.getUntrackedParameter<double>("MaxNeutralEMFrac_TightLepVeto_EtaLe27", 0.90) )
   , minNumCon_TightLepVeto_EtaLe27_ (iConfig.getUntrackedParameter<int>("MinNumberOfConstituents_TightLepVeto_EtaLe27", 1) )
   , maxMuF_TightLepVeto_EtaLe27_ (iConfig.getUntrackedParameter<double>("maxMuF_TightLepVeto_EtaLe27", 0.80) )
   //Additional cut for Eta smaller than 2.4, tracker ??
   , minChargHadF_Loose_EtaLe24_ (iConfig.getUntrackedParameter<double>("MinChargedHadFrac_Loose_EtaLe24", 0) )
   , minChargMulti_Loose_EtaLe24_ (iConfig.getUntrackedParameter<int>("MinChargedMultiplicity_Loose_EtaLe24", 0) )
   , maxChargEmF_Loose_EtaLe24_ (iConfig.getUntrackedParameter<double>("MaxChargedEMFrac_Loose_EtaLe24", 0.99) ) 
   , minChargHadF_Tight_EtaLe24_ (iConfig.getUntrackedParameter<double>("MinChargedHadFrac_Tight_EtaLe24", 0) )
   , minChargMulti_Tight_EtaLe24_ (iConfig.getUntrackedParameter<int>("MinChargedMultiplicity_Tight_EtaLe24", 0) )
   , maxChargEmF_Tight_EtaLe24_ (iConfig.getUntrackedParameter<double>("MaxChargedEMFrac_Tight_EtaLe24", 0.99) )
   , minChargHadF_TightLepVeto_EtaLe24_ (iConfig.getUntrackedParameter<double>("MinChargedHadFrac_TightLepVeto_EtaLe24", 0) )
   , minChargMulti_TightLepVeto_EtaLe24_ (iConfig.getUntrackedParameter<int>("MinChargedMultiplicity_TightLepVeto_EtaLe24", 0) )
   , maxChargEmF_TightLepVeto_EtaLe24_ (iConfig.getUntrackedParameter<double>("MaxChargedEMFrac_TightLepVeto_EtaLe24", 0.90) )
   //Eta 2.7 to 3.0
   , minNeutEmF_Loose_Eta27to30_ (iConfig.getUntrackedParameter<double>("MinNeutralEMFracHF_Loose_Eta27to30", 0.01) )
   , maxNeutHadF_Loose_Eta27to30_ (iConfig.getUntrackedParameter<double>("MaxNeutralHadFrac_Loose_Eta27to30", 0.98) )
   , minNumNeutPart_Loose_Eta27to30_ (iConfig.getUntrackedParameter<int>("MinNumberOfNeutralParticles_Loose_Eta27to30", 2) )
   , minNeutEmF_Tight_Eta27to30_ (iConfig.getUntrackedParameter<double>("MinNeutralEMFracHF_Tight_Eta27to30", 0.01) )
   , maxNeutHadF_Tight_Eta27to30_ (iConfig.getUntrackedParameter<double>("MaxNeutralHadFrac_Tight_Eta27to30", 0.98) )
   , minNumNeutPart_Tight_Eta27to30_ (iConfig.getUntrackedParameter<int>("MinNumberOfNeutralParticles_Tight_Eta27to30", 2) )
   //Eta greater than 3.0
   , maxNeutEmF_Loose_EtaGe30_ (iConfig.getUntrackedParameter<double>("MaxNeutralEMFracHF_Loose_EtaGe30", 0.90) )
   , minNumNeutPart_Loose_EtaGe30_ (iConfig.getUntrackedParameter<int>("MinNumberOfNeutralParticles_Loose_EtaGe30", 10) )
   , maxNeutEmF_Tight_EtaGe30_ (iConfig.getUntrackedParameter<double>("MaxNeutralEMFracHF_Tight_EtaGe30", 0.90) )
   , minNumNeutPart_Tight_EtaGe30_ (iConfig.getUntrackedParameter<int>("MinNumberOfNeutralParticles_Tight_EtaGe30", 10) )
   //End of JetId parameter
   , debug_ (iConfig.getParameter<bool>("debug") )
   , taggingMode_ (iConfig.getParameter<bool>("taggingMode") )
{
  produces<bool>("AK4looseJetID");
  produces<bool>("AK4tightJetID");
  produces<bool>("AK4tightlepvetoJetID");
}


prodJetIDEventFilter::~prodJetIDEventFilter()
{
}


bool prodJetIDEventFilter::filter(edm::Event & iEvent, const edm::EventSetup & iSetup) 
{
  // read in the objects
  edm::Handle<edm::View<pat::Jet>> jets;
  iEvent.getByToken(theJetToken_, jets);

  bool goodJetID = true, goodJetIDtight = true, goodJetIDtightlepveto = true;
  int jetIdx =-1;

  for (edm::View<pat::Jet>::const_iterator j = jets->begin(); j != jets->end(); ++j)
  {
    if (j->isCaloJet())
    {
      std::cout << "No JetId is applied to CaloJets for time being !!! " << std::endl;
    } 
    else if (j->isPFJet())
    {
      if (j->pt() > minJetPt_ && fabs(j->eta()) < maxJetEta_)
      {
        jetIdx++;
        double eta = j->eta();

        double NHF = j->neutralHadronEnergyFraction();
        double NEMF = j->neutralEmEnergyFraction();
        int NumConst = j->chargedMultiplicity() + j->neutralMultiplicity();
        double MUF = j->muonEnergyFraction();

        double CHF = j->chargedHadronEnergyFraction();
        int CHM = j->chargedMultiplicity();
        double CEMF = j->chargedEmEnergyFraction();

        int NumNeutralParticle = j->neutralMultiplicity();

        bool perlooseJetID = true, pertightJetID = true, pertightlepvetoJetID = true;
        if( std::abs(eta) <= 2.7 )
        {
          perlooseJetID = NHF<maxNeutHadF_Loose_EtaLe27_ && NEMF<maxNeutEmF_Loose_EtaLe27_ && NumConst>minNumCon_Loose_EtaLe27_;
          pertightJetID = NHF<maxNeutHadF_Tight_EtaLe27_ && NEMF<maxNeutEmF_Tight_EtaLe27_ && NumConst>minNumCon_Tight_EtaLe27_;
          pertightlepvetoJetID = NHF<maxNeutHadF_TightLepVeto_EtaLe27_ && NEMF<maxNeutEmF_TightLepVeto_EtaLe27_ && NumConst>minNumCon_TightLepVeto_EtaLe27_ && MUF<maxMuF_TightLepVeto_EtaLe27_;
          if( std::abs(eta) <= 2.4 )
          {
            perlooseJetID &= CHF>minChargHadF_Loose_EtaLe24_ && CHM>minChargMulti_Loose_EtaLe24_ && CEMF<maxChargEmF_Loose_EtaLe24_;
            pertightJetID &= CHF>minChargHadF_Tight_EtaLe24_ && CHM>minChargMulti_Tight_EtaLe24_ && CEMF<maxChargEmF_Tight_EtaLe24_;
            pertightlepvetoJetID &= CHF>minChargHadF_TightLepVeto_EtaLe24_ && CHM>minChargMulti_TightLepVeto_EtaLe24_ && CEMF<maxChargEmF_TightLepVeto_EtaLe24_;
          }
        }
        else if( std::abs(eta) > 2.7 && std::abs(eta) <= 3.0 )
        {
          perlooseJetID = NHF<maxNeutHadF_Loose_Eta27to30_ && NEMF>minNeutEmF_Loose_Eta27to30_ && NumNeutralParticle>minNumNeutPart_Loose_Eta27to30_;
          pertightJetID = NHF<maxNeutHadF_Tight_Eta27to30_ && NEMF>minNeutEmF_Tight_Eta27to30_ && NumNeutralParticle>minNumNeutPart_Tight_Eta27to30_;
          pertightlepvetoJetID = pertightJetID;
        }
        else
        {
          perlooseJetID = NEMF<maxNeutEmF_Loose_EtaGe30_ && NumNeutralParticle>minNumNeutPart_Loose_EtaGe30_;
          pertightJetID = NEMF<maxNeutEmF_Tight_EtaGe30_ && NumNeutralParticle>minNumNeutPart_Tight_EtaGe30_;
          pertightlepvetoJetID = pertightJetID;
        }

        goodJetID &= perlooseJetID;
        goodJetIDtight &= pertightJetID;
        goodJetIDtightlepveto &= pertightlepvetoJetID;
      }
    }
  }

  iEvent.put( std::unique_ptr<bool>(std::move(new bool(goodJetID))), "AK4looseJetID" );
  iEvent.put( std::unique_ptr<bool>(std::move(new bool(goodJetIDtight))), "AK4tightJetID" );
  iEvent.put( std::unique_ptr<bool>(std::move(new bool(goodJetIDtightlepveto))), "AK4tightlepvetoJetID" );
  //default is loose ID, but in general we use tagging mode
  return taggingMode_ || goodJetID;
}

#include "FWCore/Framework/interface/MakerMacros.h"

DEFINE_FWK_MODULE(prodJetIDEventFilter);
