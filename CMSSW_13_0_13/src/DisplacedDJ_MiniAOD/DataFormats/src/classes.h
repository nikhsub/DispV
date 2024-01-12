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
