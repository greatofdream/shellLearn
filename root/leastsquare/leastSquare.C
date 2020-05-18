#include <iostream>
#include "TCanvas.h"
#include "TRandom.h"
#include "TMinuit.h"
using namespace std;
const Int_t nentries = 100;
const Int_t N =5;
Double_t x[N]={1000, 828, 800, 600, 300};
Double_t y[N]={1500, 1340, 1328, 1172, 800};
Double_t sigma=15;
Double_t h1[nentries];
Double_t mu_fix = 0;

void fcn(Int_t &npar, Double_t *gin, Double_t &chi2, Double_t *par, Int_t iflag){
	Double_t log_l = 0;
	Double_t alpha, beta;
	alpha = par[0];
	beta = par[1];
	Double_t logf;
	for (Int_t i=0;i<N;i++){
		logf = TMath::Power((y[i]-TMath::Power(x[i],beta)*alpha),2)/sigma/sigma;
		log_l += logf;
	}
	chi2 = log_l;
}
void leastSquare(){

	Double_t par[2];
	Double_t arglist[10];
	Int_t ierflg = 0;
	arglist[0]=500;
	arglist[1]=1;
	Double_t fmin, fedm, errdef;
	Double_t mu, mu_err, beta, sigma_err;
	Int_t nvpar, nparx, icstat;
	const Int_t npar = 2;
		// fit
		TMinuit gMinuit(2);
		gMinuit.SetFCN(fcn);
		arglist[0] = 1;
		gMinuit.mnexcm("SET ERR", arglist, 1, ierflg);
		Double_t vstart[npar] = {1, 1};
		Double_t step[npar] = {0.001,  0.001};
		gMinuit.mnparm(0, "alpha", vstart[0], step[0], 0, 0, ierflg);
		gMinuit.mnparm(1, "beta", vstart[1], step[1], 0, 0, ierflg);
		gMinuit.mnexcm("MIGRAD", arglist, 0, ierflg);
		gMinuit.mnstat(fmin,fedm,errdef,nvpar,nparx,icstat);
		gMinuit.GetParameter(0, mu, mu_err );
		gMinuit.GetParameter(1, beta, sigma_err );	
	cout<<"alpha:"<<mu<<endl;
	cout<<"beta"<<beta<<endl;	
	cout<<"chi"<<fmin<<endl;
}


