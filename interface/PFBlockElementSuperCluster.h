#ifndef __PFBlockElementSuperCluster__
#define __PFBlockElementSuperCluster__

#include <iostream>

#include "DataFormats/ParticleFlowReco/interface/PFBlockElement.h"
#include "DataFormats/EgammaReco/interface/SuperClusterFwd.h"

namespace reco {
  
  /// \brief Cluster Element.
  /// 
  /// this class contains a reference to a PFCluster 
  class PFBlockElementSuperCluster : public PFBlockElement {
  public:
    PFBlockElementSuperCluster() {} 
    
    /// \brief constructor.
    /// type must be equal to PS1, PS2, ECAL, HCAL. 
    /// \todo add a protection against the other types...
  PFBlockElementSuperCluster(const SuperClusterRef& ref, 
			     PFBlockElement::Type type) 
      : 
      PFBlockElement(type),
      superClusterRef_( ref ) {}
    
    PFBlockElement* clone() const { return new PFBlockElementSuperCluster(*this); }
    
    /// \return reference to the corresponding cluster
    SuperClusterRef  superClusterRef() const {return superClusterRef_;}

    void Dump(std::ostream& out = std::cout, 
              const char* tab = " " ) const;
  
  private:
    /// reference to the corresponding cluster
    SuperClusterRef  superClusterRef_;
  };
}

#endif

