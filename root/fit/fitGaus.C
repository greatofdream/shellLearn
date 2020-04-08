#include <iostream>
#include "TCanvas.h"
#include "TRandom.h"
using namespace std;
void fitGaus(){
	Int_t N = 1000;
	Int_t nentries = 1000;
	TH1F* h1 = new TH1F("h1","gauss distribution",100,-5,5);
	TH3F* hfit1 = new TH3F("hfit1","fit use 3 para",100, -5, 5, 100, -10, 10, 100, 0, 200);
	// TH1F* hsig1 = new TH1F("hsig1","fit mu use 3 para",100, -5, 5);
	// TH1F* hchi1 = new TH1F("hchi1","fit mu use 3 para",100, -5, 5);
	TH2F* hfit2 = new TH2F("hfit2","fit use 2 para",100, -10, 10, 100, 0, 200);
	// TH1F* hsig2 = new TH1F("hmu1","fit mu use 3 para",100, -5, 5);
	// TH1F* hchi2 = new TH1F("hmu1","fit mu use 3 para",100, -5, 5);
	Double_t par[3];
	TF1 *fit1 = new TF1("f1","[0]*exp(-0.5*((x-[2])/[1])^2)",-5, 5);
	TF1 *fit2 = new TF1("f2","[0]*exp(-0.5*((x-0.5)/[1])^2)",-5, 5);
	for(Int_t i=0;i<N;i++){
		for(Int_t j=0;j<nentries;j++){
			//h1->FillRandom("gaus",nentries);
			h1->Fill(gRandom->Gaus(0,1));
		}
		h1->Draw();
		fit1->SetParameters(10,1,0);
		fit2->SetParameters(10,1);
		h1->Fit("f1");
		fit1->GetParameters(par);
		hfit1->Fill(abs(par[1]),par[2],fit1->GetChisquare());
		h1->Fit("f2");
		fit2->GetParameters(par);
		hfit2->Fill(abs(par[1]),fit2->GetChisquare());
		h1->Reset();
	}
	
	TCanvas* c1= new TCanvas("c1","");
	c1->Divide(3,2);
	c1->cd(1);
	hfit1->ProjectionY()->Draw();
	c1->cd(2);
	hfit1->ProjectionX()->Draw();
	c1->cd(3);
	hfit1->ProjectionZ()->Draw();
	c1->cd(5);
	hfit2->ProjectionX()->Draw();
	c1->cd(6);
	hfit2->ProjectionY()->Draw();
	c1->SaveAs("paraDistri1000.png");
}
