#include <iostream>
#include "TCanvas.h"
#include "TRandom.h"
#include "TMinuit.h"
using namespace std;
const Int_t nentries = 100;
const Int_t N =1000;
Double_t x[N];
Double_t y[N];
Double_t h1[nentries];
Double_t mu_fix = 0;
TString filename("gminuit.root");
void fcn1(Int_t &npar, Double_t *gin, Double_t &chi2, Double_t *par, Int_t iflag){
	Double_t log_l = 0;
	Double_t sigma;
	sigma = par[0];
	Double_t logf;
	for (Int_t i=0;i<nentries;i++){
		logf = (h1[i]-mu_fix)/sigma;
		log_l += logf*logf*(-0.5)-log(sigma)-0.5*log(2*3.14159);
	}
	chi2 = -2.0*log_l;
}
void fcn(Int_t &npar, Double_t *gin, Double_t &chi2, Double_t *par, Int_t iflag){
	Double_t log_l = 0;
	Double_t mu, sigma;
	mu = par[0];
	sigma = par[1];
	Double_t logf;
	for (Int_t i=0;i<nentries;i++){
		logf = (h1[i]-mu)/sigma;
		log_l += logf*logf*(-0.5)-log(sigma)-0.5*log(2*3.14159);
	}
	chi2 = -2.0*log_l;
}
void fitGaus(){
	TFile *f = new TFile(filename);
	TTree *tr = (TTree*)f->Get("gminuit");
	tr->SetBranchAddress("gauss",h1);
	//TH1F* h1 = new TH1F("h1","gauss distribution",100,-5,5);
	TH1F* hfitlikelihood = new TH1F("hfitlikelihood","liklihood",100, -200, -100);
	TH1F* hfitmu = new TH1F("hfitmu","mu",100, -2, 2);
	TH1F* hfitsigma = new TH1F("hfitsigma", "sigma", 100,-1,3);
	
	TH1F* hfitfixlikelihood = new TH1F("hfitlikelihood","liklihood:mu=1",100, -200, -100);
	TH1F* hfitfixsigma = new TH1F("hfitsigma", "sigma:mu=1", 100,-1,3);

	TH1F* hfitfix2likelihood = new TH1F("hfitlikelihood","liklihood:mu=0.2",100, -200, -100);
	TH1F* hfitfix2sigma = new TH1F("hfitsigma", "sigma:mu=0.2", 100,-1,3);

	TH1F* hfitfix5likelihood = new TH1F("hfitlikelihood","liklihood:mu=0.5",100, -200, -100);
	TH1F* hfitfix5sigma = new TH1F("hfitsigma", "sigma:mu=0.5", 100,-1,3);

	Double_t par[3];
	Double_t arglist[10];
	Int_t ierflg = 0;
	arglist[0]=500;
	arglist[1]=1;
	Double_t fmin, fedm, errdef;
	Double_t mu, mu_err, sigma, sigma_err;
	Int_t nvpar, nparx, icstat;
	const Int_t npar = 2;
	TMinuit g2Minuit(1);
	for(Int_t i=0;i<N;i++){
		tr->GetEntry(i);
		// fit
		TMinuit gMinuit(2);
		gMinuit.SetFCN(fcn);
		arglist[0] = 1;
		gMinuit.mnexcm("SET ERR", arglist, 1, ierflg);
		Double_t vstart[npar] = {0, 1};
		Double_t step[npar] = {0.001,  0.001};
		gMinuit.mnparm(0, "mu", vstart[0], step[0], 0, 0, ierflg);
		gMinuit.mnparm(1, "sigma", vstart[1], step[1], 0, 0, ierflg);
		gMinuit.mnexcm("MIGRAD", arglist, 0, ierflg);
		gMinuit.mnstat(fmin,fedm,errdef,nvpar,nparx,icstat);
		gMinuit.GetParameter(0, mu, mu_err );
		gMinuit.GetParameter(1, sigma, sigma_err );	
		hfitlikelihood->Fill(-0.5*fmin);
		hfitmu->Fill(mu);
		hfitsigma->Fill(sigma);
		
		mu_fix=1;
		g2Minuit.SetFCN(fcn1);
		arglist[0] = 1;
		g2Minuit.mnexcm("SET ERR", arglist, 1, ierflg);
		g2Minuit.mnparm(0, "sigma", vstart[1], step[1], 0, 0, ierflg);
		g2Minuit.mnexcm("MIGRAD", arglist, 0, ierflg);
		g2Minuit.mnstat(fmin,fedm,errdef,nvpar,nparx,icstat);
		g2Minuit.GetParameter(0, sigma, sigma_err );	
		hfitfixlikelihood->Fill(-0.5*fmin);
		hfitfixsigma->Fill(sigma);

		mu_fix = 0.2;
		g2Minuit.mnexcm("SET ERR", arglist, 1, ierflg);
		g2Minuit.mnparm(0, "sigma", vstart[1], step[1], 0, 0, ierflg);
		g2Minuit.mnexcm("MIGRAD", arglist, 0, ierflg);
		g2Minuit.mnstat(fmin,fedm,errdef,nvpar,nparx,icstat);
		g2Minuit.GetParameter(0, sigma, sigma_err );	
		hfitfix2likelihood->Fill(-0.5*fmin);
		hfitfix2sigma->Fill(sigma);

		mu_fix = 0.5;
		g2Minuit.mnexcm("SET ERR", arglist, 1, ierflg);
		g2Minuit.mnparm(0, "sigma", vstart[1], step[1], 0, 0, ierflg);
		g2Minuit.mnexcm("MIGRAD", arglist, 0, ierflg);
		g2Minuit.mnstat(fmin,fedm,errdef,nvpar,nparx,icstat);
		g2Minuit.GetParameter(0, sigma, sigma_err );	
		hfitfix5likelihood->Fill(-0.5*fmin);
		hfitfix5sigma->Fill(sigma);

	}
	
	TCanvas* c1= new TCanvas("c1","",1000,600);
	c1->Divide(4,3);
	c1->cd(1);
	hfitlikelihood->Draw();
	c1->cd(9);
	hfitmu->Draw();
	c1->cd(5);
	hfitsigma->Draw();
	c1->cd(4);
	hfitfixlikelihood->Draw();
	c1->cd(8);
	hfitfixsigma->Draw();
	c1->cd(2);
	hfitfix2likelihood->Draw();
	c1->cd(6);
	hfitfix2sigma->Draw();
	c1->cd(3);
	hfitfix5likelihood->Draw();
	c1->cd(7);
	hfitfix5sigma->Draw();


	c1->SaveAs("paraDistri1000.png");
}

void generateData(){
	TFile f(filename, "recreate");
	TTree *tr = new TTree("gminuit", "simulate gauss events");
	
	tr->Branch("gauss", h1,"h1[100]/D");

	for(Int_t i=0;i<N;i++){
		for(Int_t j=0;j<nentries;j++){
			h1[j] = gRandom->Gaus(0,1);
		}
		tr->Fill();
	}
	f.cd();
	tr->Write();
}
