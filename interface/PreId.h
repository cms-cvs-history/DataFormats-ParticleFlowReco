#ifndef PreId_H
#define PreId_H

#include "DataFormats/Math/interface/Point3D.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"
#include "DataFormats/ParticleFlowReco/interface/PFRecTrackFwd.h"
#include "DataFormats/ParticleFlowReco/interface/PFClusterFwd.h"

namespace reco
{
  class PreId{
  public:
    PreId(){}
    void setTrack(reco::TrackRef trackref, float eta, float pt,float chi2red, int nhit)     {
      trackRef_ = trackref;
      kfEta_ = eta;
      kfPt_ = pt;
      chikfred_ = chi2red;
      nhit_ = nhit;
    }
    void setCaloMatching(PFClusterRef clusterRef, const math::XYZPoint & ecalpos, const math::XYZPoint &meanShower, float deta,float dphi,float chieta,float chiphi, float chi2, float eop,bool ecalmatch,bool psmatch){
      clusterRef_ = clusterRef;
      EcalPos_ = ecalpos;
      meanShower_ = meanShower;
      matchingDeltaEta_ = deta;
      matchingDeltaPhi_ = dphi;
      matchingChiEta_ = chieta;
      matchingChiPhi_ = chiphi;
      matchingChi2_ = chi2;
      matchingEop_= eop;      
      EcalMatching_ = ecalmatch;
      PSMatching_ = psmatch;
    }
    
    void setTrackId(bool tkfilt, float newchi2, float chi2ratio,float dpt, float mva){
      trackFilt_ = tkfilt;
      newchikfred_=newchi2;
      chiRatio_ = chi2ratio;
      dpt_ = dpt;
      mva_ = mva;
    }

    void setFinalDecision(bool accepted)
    {
      goodpreid_ = accepted;
    }

  private:
    reco::TrackRef trackRef_;
      //    PFRecTrackRef trackRefPF_;
    PFClusterRef clusterRef_;
    
    float matchingDeltaEta_;
    float matchingDeltaPhi_;
    float matchingChiEta_;
    float matchingChiPhi_;
    float matchingChi2_;
    float matchingEop_;
    float kfPt_;
    float kfEta_;
    float kfChi2_;
    math::XYZPoint EcalPos_;
    math::XYZPoint meanShower_;
    bool TkId_;
    bool EcalMatching_;
    bool PSMatching_;
    float chikfred_;
    bool trackFilt_;
    int nhit_;
    float newchikfred_;
    float dpt_;
    float chiRatio_;
    float mva_;
    bool goodpreid_;
  };
}
#endif
