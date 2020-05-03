#include <iostream>
#include "TMinuit.h"
using namespace std;
const Int_t npoints=4, T=293, pi=3.1415926;
Double_t delta_rho = 0.063, g=980, r=0.52, kscale=16;
Double_t x[npoints]={0, 6, 12, 18};
Double_t y[npoints]={1880, 940, 530, 305};
void fcn(Int_t &npar, Double_t *gin, Double_t &chi2, Double_t 
*par, Int_t iflag)
{
   // Calculate log-likelihood
   Double_t log_l = 0;
   Double_t k,v0,f_nor,f;
   k = par[0];
   v0  = par[1];
   for (Int_t i=0;i<npoints; i++) {
     f=v0 * TMath::Exp(-4*pi*r*r*r*delta_rho*g*x[i]/3/k/T);
	 
	 log_l += y[i] * TMath::Log(f)-f;
   }
   // 2 gets errors right
   chi2=-2.*log_l;  
}
void fcn2(Int_t &npar, Double_t *gin, Double_t &chi2, Double_t 
*par, Int_t iflag)
{
   // Calculate log-likelihood
   Double_t sum = 0;
   Double_t k,v0,f_nor,f;
   k = par[0];
   v0  = par[1];
   for (Int_t i=0;i<npoints; i++) {
     f = v0 * TMath::Exp(-4*pi*r*r*r*delta_rho*g*x[i]/3/k/T);
	sum += y[i] * TMath::Log(y[i]/f)+ f - y[i];
   }
   // 2 gets errors right
   chi2=2.*sum;  
}
void na(){
	
	TMinuit *gMinuit = new TMinuit(2);
	// gMinuit->SetFCN(fcn);
	gMinuit->SetFCN(fcn2);
	const int npar=2;
	Double_t arglist[10];
	Int_t ierflg =0;
	arglist[0]=1;
	gMinuit->mnexcm("SET ERR", arglist, 1, ierflg);

	Double_t vstart[npar] = {1, 1000};
	Double_t step[npar] = {0.001, 0.1};
	gMinuit->mnparm(0, "k", vstart[0], step[0], 0, 0, ierflg);
	gMinuit->mnparm(1, "v0", vstart[1], step[1], 0, 0, ierflg);

	arglist[0] =500;
	arglist[1] = 1.;
	gMinuit->mnexcm("MIGRAD", arglist, 0, ierflg);
	gMinuit->mnexcm("HESSE", arglist ,0,ierflg);
	gMinuit->mnexcm("MINOS", arglist ,0,ierflg);   
	// Print results
	// alpha = k;beta = v0
	Double_t fmin,fedm,errdef;
	Double_t alpha,alpha_err,beta,beta_err;
	Int_t nvpar,nparx,icstat;
	Double_t covmat[npar][npar];
	gMinuit->mnstat(fmin,fedm,errdef,nvpar,nparx,icstat);
	gMinuit->GetParameter(0, alpha, alpha_err );
	gMinuit->GetParameter(1, beta, beta_err );
	gMinuit->mnemat(&covmat[0][0],npar); 
	Double_t rho=covmat[0][1]/(alpha_err*beta_err);

	cout <<"alpha           = "<<alpha<<" +/- "<<alpha_err<<endl;
	cout <<"beta            = "<<beta <<" +/- "<<beta_err<<endl;
	cout <<"cov[alpha][beta]= "<<covmat[0][1]<<endl;
	cout <<"rho[alpha][beta]= "<<rho<<endl;
	cout <<"log_l           = "<<-0.5*fmin<<endl;
       cout << "chi=" <<fmin<<endl;	

}
