// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/GetterOfProducts.h"
#include "FWCore/Framework/interface/ProcessMatch.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "SimDataFormats/GeneratorProducts/interface/LHEEventProduct.h"

#include "SimDataFormats/GeneratorProducts/interface/GenLumiInfoHeader.h"

// STL include files
#include <memory>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>

//
// class declaration
//

class SusyScanProducer : public edm::EDProducer {
    public:
        explicit SusyScanProducer(const edm::ParameterSet&);
        ~SusyScanProducer();
        static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

    private:
        virtual void beginJob();
        virtual void produce(edm::Event&, const edm::EventSetup&);
        virtual void endJob();
        
        virtual void beginRun(edm::Run&, edm::EventSetup const&);
        virtual void endRun(edm::Run&, edm::EventSetup const&);
        virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
        virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
        
        void process(std::string line, char delim, std::vector<std::string>& fields);
        
        // ----------member data ---------------------------
        edm::GetterOfProducts<LHEEventProduct> getterOfProducts_;
        bool shouldScan_, debug_;
                float motherMass, lspMass;
                const std::string versionStr_;
   
                edm::EDGetTokenT<GenLumiInfoHeader> genLumiHeaderToken;
};

SusyScanProducer::SusyScanProducer(const edm::ParameterSet& iConfig) : 
    getterOfProducts_(edm::ProcessMatch("*"), this), shouldScan_(iConfig.getParameter<bool>("shouldScan")), debug_(iConfig.getParameter<bool>("debug")), versionStr_(iConfig.getUntrackedParameter<std::string>("versionStr", "80X"))
{
    callWhenNewProductsRegistered(getterOfProducts_);
        genLumiHeaderToken = consumes<GenLumiInfoHeader,edm::InLumi>(edm::InputTag("generator"));
    produces<float>("SusyMotherMass");
    produces<float>("SusyLSPMass");
}

SusyScanProducer::~SusyScanProducer()
{
    
    // do anything here that needs to be done at desctruction time
    // (e.g. close files, deallocate resources etc.)
    
}

void SusyScanProducer::produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
    //  std::cout<<"Running SusyScanProducer"<<std::endl;
 
   using namespace edm;


   std::auto_ptr<float > motherMass_(new float(motherMass));
   iEvent.put(motherMass_, "SusyMotherMass");
    
   std::auto_ptr<float > lspMass_(new float(lspMass));
   iEvent.put(lspMass_, "SusyLSPMass");

}

// ------------ method called once each job just before starting event loop  ------------
void
SusyScanProducer::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
SusyScanProducer::endJob() {
}

// ------------ method called when starting to processes a run  ------------
void 
SusyScanProducer::beginRun(edm::Run&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a run  ------------
void 
SusyScanProducer::endRun(edm::Run&, edm::EventSetup const&)
{
}

// ------------ method called when starting to processes a luminosity block  ------------
void 
SusyScanProducer::beginLuminosityBlock(edm::LuminosityBlock const& iLumi, edm::EventSetup const& iEventSetup)
{
   motherMass =0; lspMass =0;
   edm::Handle<GenLumiInfoHeader> gen_header;
   iLumi.getByToken(genLumiHeaderToken, gen_header);
   std::string model = gen_header->configDescription(); 

   std::vector<std::string> fields;
   //underscore-delimited data
   process(model,'_',fields);

   //convert fields 1:n to doubles
   std::vector<float> dfields;
   dfields.reserve(fields.size()-1);
   for(unsigned f = 1; f < fields.size(); ++f){
      std::stringstream sfield(fields[f]);
      float tmp = 0;
      sfield >> tmp;
      dfields.push_back(tmp);
   }

   //two options:
   //model name_mMother_mLSP (1+2 fields)
   //model name_xChi_mMother_mLSP (1+3 fields)
          if(dfields.size()>=2){
               motherMass = dfields[dfields.size()-2];
               lspMass = dfields[dfields.size()-1];
            }
   if(debug_) std::cout <<"\nSusyScanProducer -->  model : "<<model.c_str()<<"  motherMass : "<<motherMass<<"  lspMass : "<<lspMass<<std::endl<<std::endl; // prints, e.g. T1tttt_1500_100

}

// ------------ method called when ending the processing of a luminosity block  ------------
void 
SusyScanProducer::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
SusyScanProducer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
    //The following says we do not know what parameters are allowed so do no validation
    // Please change this to state exactly what you do use, even if it is no parameters
    edm::ParameterSetDescription desc;
    desc.setUnknown();
    descriptions.addDefault(desc);
}

//generalization for processing a line
void
SusyScanProducer::process(std::string line, char delim, std::vector<std::string>& fields){
    std::stringstream ss(line);
    std::string field;
    while(std::getline(ss,field,delim)){
        fields.push_back(field);
    }
}

//define this as a plug-in
DEFINE_FWK_MODULE(SusyScanProducer);

