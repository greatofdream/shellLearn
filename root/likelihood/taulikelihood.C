#include <iostream>
#include <TMath.h>
using namespace std;
void taulikelihood(Int_t nentries=1000,Int_t n = 10) {
        gROOT->Reset();
	Double_t tau = 1;
	Double_t tau_hat = 0, t_sum = 0;
        TH1F *h1 = new TH1F("h1", "possion chisquare", 100, 0, 5);
        for(int i=0;i<nentries;i++){
		t_sum = 0;
		for(Int_t j=0;j<n;j++){
			t_sum += gRandom->Exp(tau);
		}
		tau_hat = t_sum/n;
		h1->Fill(tau_hat);
	}
	cout<<"average"<<h1->GetMean()<<";truth"<<1<<endl;
	cout<<"std"<<h1->GetRMS()<<";truth"<<tau/sqrt(n)<<endl;
	TCanvas* c1= new TCanvas("c1","");
	h1->Draw();
	h1->SetTitle(TString::Format("nentries=%d,nOberve=%d",nentries,n));
	c1->SaveAs("taulikelihood.png");
}
void lambdalikelihood(Int_t nentries=1000,Int_t n = 10) {
        gROOT->Reset();
	Double_t tau = 1;
	Double_t lambda_hat = 0, t_sum = 0;
        TH1F *h1 = new TH1F("h1", "possion chisquare", 100, 0, 5);
        for(int i=0;i<nentries;i++){
		t_sum = 0;
		for(Int_t j=0;j<n;j++){
			t_sum += gRandom->Exp(tau);
		}
		lambda_hat = n/t_sum;
		h1->Fill(lambda_hat);
	}
	cout<<"average"<<h1->GetMean()<<";truth"<<1/tau<<";expect"<<n/tau/(n-1)<<endl;
	cout<<"std"<<h1->GetRMS()<<";expect"<<1/sqrt(tau*n)<<endl;
	cout<<"n="<<n<<",b="<<h1->GetMean()-1/tau<<endl;
	TCanvas* c1= new TCanvas("c1","");
	h1->Draw();
	h1->SetTitle(TString::Format("nentries=%d,nOberve=%d",nentries,n));
	c1->SaveAs(TString::Format("lambdalikelihood_n%d.png",n));
}

