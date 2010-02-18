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
  PreId():trackRef_(reco::TrackRef()),clusterRef_(reco::PFClusterRef()),
      matchingDeltaEta_(0.),matchingDeltaPhi_(0.),matchingChiEta_(0.),matchingChiPhi_(0.),
      matchingChi2_(0.),matchingEop_(0.),kfPt_(0.),kfEta_(0.),EcalPos_(math::XYZPoint()),
      meanShower_(math::XYZPoint()),TkId_(false),EcalMatching_(false),PSMatching_(false),
      chikfred_(0.),trackFilt_(false),newchikfred_(0.),dpt_(0.),mva_(0.),goodpreid_(false){}
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

    /// Access methods
    inline float deltaEtaMatch() const {return matchingDeltaEta_;}
    inline float deltaPhiMatch() const {return matchingDeltaPhi_;}
    inline float chiEtaMatch() const {return matchingChiEta_;}
    inline float chiPhiMatch() const {return matchingChiPhi_;}
    inline float chi2Match() const {return matchingChi2_;}
    inline float eopMatch() const {return matchingEop_;}
    inline float pt() const {return kfPt_;}
    inline float eta() const {return kfEta_;}
    inline float kfChi2() const {return chikfred_;}
    inline float kfNHits() const {return nhit_;}

    inline bool ecalMatching() const {return EcalMatching_;}
    const math::XYZPoint & ecalPos() const {return EcalPos_;}
    const math::XYZPoint & meanShower() const {return meanShower_;}
    inline bool psMatching() const {return PSMatching_;}
    
    inline float gsfChi2Ratio() const {return chiRatio_;}
    inline float kfNewChi2() const {return newchikfred_;}
    inline bool trackFiltered() const {return trackFilt_;}
    inline float mva() const {return mva_;}
    inline bool preided() const {return goodpreid_;}
    inline float dpt() const {return dpt_;}
    reco::TrackRef trackRef() const {return trackRef_;}
    PFClusterRef clusterRef() const {return clusterRef_;}

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
