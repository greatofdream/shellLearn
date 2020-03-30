#include "stdio.h"
void randomHist(){
	TH1F *h1 = new TH1F("h1", "uniform hist", 100, 0, 1);
	for(Int_t i =0;i<10000;i++){
		h1->Fill(gRandom->Uniform(0, 1));
	}
	h1->GetXaxis()->SetTitle("x, uniform");
	h1->GetYaxis()->SetTitle("y");
	h1->GetXaxis()->CenterTitle();
	h1->GetYaxis()->CenterTitle();
	TCanvas *c1 = new TCanvas("c1", "");
	h1->Draw();
	c1->SaveAs("Uniform.pdf");
}
void randomRepeatHist(Int_t n, Int_t index){
	TH1F *h1 = new TH1F("h1", "uniform hist", 100, 0, 50);
	TH1F *h2 = new TH1F("h2", "uniform hist",5, 0, 1);

	for(Int_t i =0;i<n;i++){
		for(Int_t j=0;j<100;j++){
			h2->Fill(gRandom->Uniform(0, 1));
		}
		h1->Fill(h2->GetBinContent(index));
		// printf("%f %f %d\n",h2->GetBinContent(index),h2->GetBin(index),index);
		h2->Reset();
	}
	h1->GetXaxis()->SetTitle("x,bin["+TString(index)+"]");
	h1->GetYaxis()->SetTitle("y");
	h1->GetXaxis()->CenterTitle();
	h1->GetYaxis()->CenterTitle();
	TCanvas *c1 = new TCanvas("c1", "");
	h1->Draw();
	c1->SaveAs("uniformRepeatBin"+TString(index)+".pdf");
}
void randomRepeatHist2(Int_t n, Int_t xindex, Int_t yindex){
	TH2F *h1 = new TH2F("h1", "uniform hist", 100, 0, 50, 100, 0, 50);
	TH1F *h2 = new TH1F("h2", "uniform hist",5, 0, 1);

	for(Int_t i =0;i<n;i++){
		for(Int_t j=0;j<100;j++){
			h2->Fill(gRandom->Uniform(0, 1));
		}
		h1->Fill(h2->GetBinContent(xindex),h2->GetBinContent(yindex));
		// printf("%f %f %d\n",h2->GetBinContent(index),h2->GetBin(index),index);
		h2->Reset();
	}
	h1->GetXaxis()->SetTitle(TString::Format("x,bin[%d],#rho=%2f,cov=%2f",xindex,h1->GetCorrelationFactor(),h1->GetCovariance()));
	h1->GetYaxis()->SetTitle(TString::Format("y,bin[%d]",yindex));
	h1->GetXaxis()->CenterTitle();
	h1->GetYaxis()->CenterTitle();
	TCanvas *c1 = new TCanvas("c1", "");
	h1->Draw();
	c1->SaveAs("uniformRepeatBin2.pdf");
}




