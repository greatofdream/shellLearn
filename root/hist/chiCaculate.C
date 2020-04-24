#include <iostream>
using namespace std;
void chiCaculate() {
        gROOT->Reset();
        const Int_t N = 20;

        TH1F *h1 = new TH1F("h1", "possion chisquare", 20, 0, 10);
        TH1F *h2 = new TH1F("h2", "possion chisquare", 20, 0, 10);
        TH1F *h3 = new TH1F("h3", "possion chisquare", 20, 0, 10);
        Double_t x[N]={1,0,3,4,6,
		3,3,4,5,7,
		4,5,2,0,1,
		0,0,1,0,0
	};
	Double_t y1[N]={0.2,1.2,1.9,3.2,4,
		4.5,4.7,4.8,4.8,4.5,
		4.1,3.5,3,2.4,1.6,
		0.9,0.5,0.3,0.2,0.1
	};
	Double_t y2[N]={0.2,0.7,1.1,1.6,1.9,
	      2.2,2.7,3.3,3.6,3.9,
	      4,4,3.9,3.5,3.2,
	      2.8,2.2,1.5,1,0.5
	};
	Double_t chi1=0,chi2=0;
        for(int i=0;i<N;i++){
		h1->SetBinContent(i+1, x[i]);
		h2->SetBinContent(i+1, y1[i]);
		h3->SetBinContent(i+1, y2[i]);
		chi1 += (y1[i]-x[i])*(y1[i]-x[i])/y1[i];
		chi2 += (y2[i]-x[i])*(y2[i]-x[i])/y2[i];
	}
	TCanvas* c1= new TCanvas("c1","");
	h1->Draw();
	h1->SetTitle(TString::Format("chi1=%.2f,chi2=%.2f",chi1,chi2));
	h2->SetLineColor(kRed);
	h2->Draw("same");
	h3->SetLineColor(kRed);
	h3->Draw("same");
	c1->SaveAs("chisquareCaculate.png");
}
void simChi(Int_t nentries=1000){
	const Int_t N = 20;
        TH1F *h1 = new TH1F("h1", "sim possion chisquare distribution", 100, 0, 100);
        TH1F *h2 = new TH1F("h2", "possion chisquare", 100, 0, 100);
        Double_t y1[N]={0.2,1.2,1.9,3.2,4,
		4.5,4.7,4.8,4.8,4.5,
		4.1,3.5,3,2.4,1.6,
		0.9,0.5,0.3,0.2,0.1
	};
	Double_t y2[N]={0.2,0.7,1.1,1.6,1.9,
	      2.2,2.7,3.3,3.6,3.9,
	      4,4,3.9,3.5,3.2,
	      2.8,2.2,1.5,1,0.5
	};
	Double_t x1[N], x2[N];
	Double_t chi1=0,chi2=0;
	Double_t chiCal1=15.82, chiCal2=35.97;
        for(Int_t i=0;i<nentries;i++){
		for(Int_t j=0;j<N;j++){
			x1[j] = gRandom->Poisson(y1[j]);
			x2[j] = gRandom->Poisson(y2[j]);
			chi1 += (y1[j]-x1[j])*(y1[j]-x1[j])/y1[j];
			chi2 += (y2[j]-x2[j])*(y2[j]-x2[j])/y2[j];
		}
		h1->Fill(chi1);
		h2->Fill(chi2);
		chi1=0;
		chi2=0;
	}
	Int_t sum1=0, sum2=0;
	for(Int_t i=16;i<101;i++){
		sum1 += h1->GetBinContent(i);
	}
	for(Int_t i=36;i<101;i++){
		sum2 += h2->GetBinContent(i);
	}
	cout<<sum1/h1->GetEntries()<<endl;
	cout<<sum2/h2->GetEntries()<<endl;
	cout<<ROOT::Math::chisquared_cdf(chiCal1,N)<<endl;
	cout<<ROOT::Math::chisquared_cdf_c(chiCal2,N)<<endl;

	TCanvas* c1= new TCanvas("c1","");
	c1->Divide(2, 1);
	c1->cd(1);
	h1->Draw();
	c1->cd(2);
	h2->Draw();
	c1->SaveAs("simChi.png");
}
void alphadecay(Int_t nentries=1000){
	const Int_t N=15;
	Double_t decaytimes[N]={57,203,383,525,532,408,273,139,
	45,27,10,4,0,1,1};
	Double_t msum=0,nsum=0, s2=0;
	for(Int_t i=0;i<N;i++){
		msum += i * decaytimes[i];
		nsum += decaytimes[i];
		s2 += decaytimes[i]*i*i;
	}
	Double_t maverage = msum/nsum;
	s2 = (s2-maverage*maverage*nsum)/(nsum-1);
	Double_t t=s2/maverage;
	cout<<"maverage"<<maverage<<endl;
	cout<<"s2"<<s2<<endl;
	cout<<"t"<<t<<endl;
	cout<<"(n-1)t"<<(nsum-1)*t<<endl;
	cout<<"n"<<nsum<<endl;
	cout<<"p:"<<ROOT::Math::chisquared_cdf_c((nsum-1)*t,nsum-1)<<endl;
	TH1D* h1 = new TH1D("h1","chi distribution",100,0, 1.5);
	Double_t s2new=0, manew=0, temp=0;
	for(Int_t i=0;i<nentries;i++){
		for(Int_t j=0;j<nsum;j++){
			temp = gRandom->Poisson(maverage);
			s2new += temp*temp;
			manew += temp;
		}
		manew = manew/nsum;
		s2new = (s2new-manew*manew*nsum)/(nsum-1);
		h1->Fill(s2new/manew);
		s2new =0;
		manew =0;
	}
	Int_t num = 0;
	for(Int_t i=1;i<=100;i++){
		if(i*0.015>0.95)
			num += h1->GetBinContent(i);
	}
	cout<<num/h1->GetEntries()<<endl;
	TCanvas* c1 = new TCanvas("c1","");
	h1->Draw();
	c1->SaveAs("alphadecay.png");
}

