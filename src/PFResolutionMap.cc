#include "DataFormats/ParticleFlowReco/interface/PFResolutionMap.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <functional>

using namespace std;
using namespace reco;


const unsigned PFResolutionMap::lineSize_ = 10000;


PFResolutionMap::PFResolutionMap(const char* name, unsigned nbinseta,  
				 double mineta, double maxeta,
				 unsigned nbinse, 
				 double mine, double maxe, double value) 
  : TH2D(name, name, nbinseta, mineta, maxeta, nbinse, mine, maxe) {
  // fNbinsEta(nbinseta), fMinEta(mineta), fMaxEta(maxeta),
  //    fNbinsE(nbinse), fMinE(mine), fMaxE(maxe) {

  GetXaxis()->SetTitle("#eta");
  GetYaxis()->SetTitle("E");

  if(value>0) {
    for(int ie=1; ie<=GetNbinsY(); ie++) {
      for(int ieta=1; ieta<=GetNbinsX(); ieta++) {
	SetBinContent(ieta,ie, value);
      }
    }  
  }
  // cout<<"creating resolution map "<<endl;
  // Print("all");
  
}

// void PFResolutionMap::Init(unsigned nbinseta,  
// 			   double mineta, double maxeta,
// 			   unsigned nbinse, 
// 			   double mine, double maxe) {
//   assert(mineta<maxeta);
//   assert(mine<maxe);
  
//   unsigned nbins =  nbinseta*nbinse;
//   fData.reserve( nbins );
//   for(unsigned i=0; i<nbins; i++) {
//     fData.push_back(-1);
//   } 
  
//   // calculate lower bound of eta and e bins
//   double binsize =  (fMaxEta - fMinEta)/fNbinsEta;
//   double lb = fMinEta;
//   // cout<<"eta bins lower bounds : "<<endl;
//   for(unsigned i=0; i<nbinseta; i++) {
//     fEtaBinsLowerBounds[lb] = i; 
//     // cout<<i<<" "<<lb<<endl;
//     lb += binsize;
//   }
  
//   binsize =  (fMaxE - fMinE)/fNbinsE;
//   lb = fMinE;
//   // cout<<"E bins lower bounds : "<<endl;
//   for(unsigned i=0; i<nbinse; i++) {
//     fEBinsLowerBounds[lb] = i; 
//     // cout<<i<<" "<<lb<<endl;
//     lb += binsize;
//   } 
// }

PFResolutionMap::PFResolutionMap(const char* name, const char* mapfile) 
throw (string) 
try {
  
  SetTitle(mapfile);
  GetXaxis()->SetTitle("#eta");
  GetYaxis()->SetTitle("E");
  if( ! ReadMapFile(mapfile) ) {
    string err = "PFResolutionMap::PFResolutionMap : cannot read file ";
    err += mapfile;
    throw err;
  }
}
catch(string) {
}
  

bool PFResolutionMap::WriteMapFile(const char* mapfile) const {

  //  assert(fData.size() == fNbinsEta*fNbinsE);


  // open the file

  ofstream outf(mapfile);
  if( !outf.good() ) {
    cout<<"PFResolutionMap::Write : cannot open file "<<mapfile<<endl;
    return false;
  }
  
  outf<<(*this)<<endl;
  if(!outf.good() ) {
    cerr<<"PFResolutionMap::Write : corrupted file "<<mapfile<<endl;
    return false;
  }
  else return true;
}



bool PFResolutionMap::ReadMapFile(const char* mapfile) {
  
  // open the file

  ifstream inf(mapfile);
  if( !inf.good() ) {
    // cout<<"PFResolutionMap::Read : cannot open file "<<mapfile<<endl;
    return false;
  }
  
  // first data describes the map

  int nbinseta=0;
  double mineta=0;
  double maxeta=0;
  
  int nbinse=0;
  double mine=0;
  double maxe=0;
  
  inf>>nbinseta;
  inf>>mineta;
  inf>>maxeta;

  inf>>nbinse;
  inf>>mine;
  inf>>maxe;

  SetBins(nbinseta, mineta, maxeta, nbinse, mine, maxe);

  // Init(fNbinsEta,fMinEta,fMaxEta,fNbinsE,fMinE,fMaxE);

  // char data[lineSize_];
  char s[lineSize_];
  int pos=inf.tellg();

  // parse map data
  int i=1;
  do { 
    inf.seekg(pos);
    inf.getline(s,lineSize_);
    
    pos = inf.tellg();     
 
    if(string(s).empty()) {
      continue; // remove empty lines
    }

    istringstream lin(s);  

    double dataw;
    int j=1;
    do {
      lin>>dataw;
      SetBinContent(j, i, dataw);
      j++;
    } while (lin.good() );
    i++;
  } while(inf.good());
  
  if(inf.eof()) {
    return true;
  }
  else {
    // cout<<"error"<<endl;
    return false;
  }
  return true;
}



// int PFResolutionMap::FindBin(double eta, double e) const {
  
//   if(eta<fMinEta || eta>=fMaxEta) {
//     cout<<"PFResolutionMap::FindBin "<<eta<<" out of eta bounds "<<fMinEta<<" "<<fMaxEta<<endl;
//     return -1;
//   }
//   if(e<fMinE || e>=fMaxE) {
//     cout<<"PFResolutionMap::FindBin "<<e<<" out of e bounds "<<fMinE<<" "<<fMaxE<<endl;
//     return -1;
//   }
  
//   map<double,unsigned >::const_iterator iteta = 
//     fEtaBinsLowerBounds.upper_bound( eta );
//   iteta--;
		 
// //   if( iteta != fEtaBinsLowerBounds.end() ) {
// //     cout<<"eta lower bound "<<iteta->first<<" "<<iteta->second<<endl;
// //   }
// //   else return -1;

//   map<double,unsigned>::const_iterator ite = 
//     fEBinsLowerBounds.upper_bound( e );
//   ite--;
// //   if( ite != fEBinsLowerBounds.end() ) {
// //     cout<<"e lower bound "<<ite->first<<" "<<ite->second<<endl;
// //   }
// //   else return -1;

// //   cout<<"returning "<<ite->second * fNbinsEta + iteta->second<<endl;
// //   cout<<"returning "<<ite->second<<" "<<iteta->second<<endl;

//   return ite->second * fNbinsEta + iteta->second;
// }

// void PFResolutionMap::Fill(double eta, double e, double res) {

//   unsigned bin = FindBin(eta, e);
//   if( bin<0 || bin>fData.size() ) {
//     // cout<<"PFResolutionMap::Fill : out of range " <<bin<<endl;
//     return;
//   }
  
//   fData[bin] = res;
// }



// double PFResolutionMap::getRes(double eta, double e) const {

//   if( eta<fMinEta ) eta = fMinEta;
//   if( eta>fMaxEta ) eta = fMaxEta-0.001;
 
//   if( e<fMinE ) e = fMinE;
//   if( e>fMaxE ) e = fMaxE-0.001;
 

//   unsigned bin = FindBin(eta, e);
//   assert( ! (bin<0 || bin>fData.size()) );
//   return fData[bin];
// }

int PFResolutionMap::FindBin(double eta, double e) {
  if(e >= GetYaxis()->GetXmax() )
    e = GetYaxis()->GetXmax() - 0.001;
  
  return TH2D::FindBin(eta,e);
}



ostream& reco::operator<<(ostream& outf, const PFResolutionMap& rm) {

  if(!outf.good() ) return outf;

  // first data describes the map
  outf<<rm.GetNbinsX()<<endl;
  outf<<rm.GetXaxis()->GetXmin()<<endl;
  outf<<rm.GetXaxis()->GetXmax()<<endl;

  outf<<rm.GetNbinsY()<<endl;
  outf<<rm.GetYaxis()->GetXmin()<<endl;
  outf<<rm.GetYaxis()->GetXmax()<<endl;

  for(int ie=1; ie<=rm.GetNbinsY(); ie++) {
    for(int ieta=1; ieta<=rm.GetNbinsX(); ieta++) {
      outf<<rm.GetBinContent(ieta,ie)<<"\t";
    }
    outf<<endl;
  }
  
  return outf;
}