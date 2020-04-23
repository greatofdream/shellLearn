#include <iostream>
#include "TCanvas.h"
#include "TRandom.h"
using namespace std;
void simScatterN(Int_t nentries=100){
	Double_t l_s = 0.1;
	Double_t angle_s = 30;
	Double_t l_A = 5;
	Double_t l_B = 0.3;
	// hitogram
	Double_t pi = 3.14159;
	TH1D* h1 = new TH1D("h1", "lambda A", 10, 0, 10);
	TH1D* h2 = new TH1D("h2", "lambda B", 10, 0, 2);
	TGraph** gr = new TGraph*[nentries];
	TMultiGraph* mg = new TMultiGraph();
	for(Int_t i=0; i<nentries; i++){
		//do sim
		Bool_t annihilate = false;
		Double_t x=0, y=0;
		Double_t theta = 0;
		Double_t p_s,p_a,p_b;
		Double_t ls, la, lb;
		Double_t totallength = 0;
		Int_t step = 0;
		std::vector<Double_t> posx, posy;
		posx.push_back(x);
		posy.push_back(y);
		step++;	
		while(!annihilate){
			step++;
			p_s = gRandom->Uniform(0,1);
			p_a = gRandom->Uniform(0,1);
			p_b = gRandom->Uniform(0,1);
			ls = -log(p_s)*l_s;
			la = -log(p_a)*l_A;
			lb = -log(p_b)*l_B;
			theta += gRandom->Uniform(-angle_s,angle_s);
				
			if(ls>la || ls>lb){
				if(lb>la){
					x = x + la * cos(theta/180*pi);
					y = y + la * sin(theta/180*pi);
					posx.push_back(x);
					posy.push_back(y);
			

					totallength += la;
					h2->Fill(totallength);
					annihilate = true;
				}
				else{
					x = x + lb * cos(theta/180*pi);
					y = y + lb * sin(theta/180*pi);
					posx.push_back(x);
					posy.push_back(y);
				
					totallength += lb;
					h2->Fill(totallength);
					annihilate = true;
				}
			}
			x = x + ls * cos(theta/180*pi);
			y = y + ls * sin(theta/180*pi);
			posx.push_back(x);
			posy.push_back(y);
			totallength += ls;
		}
		gr[i] = new TGraph(step, &posx[0], &posy[0]);
		mg->Add(gr[i]);
	}
	// plot track
	TCanvas* c2 = new TCanvas("c2", "track");
	mg->Draw("AC*");
	/*for(Int_t i=0;i<nentries;i++){
		gr[i]->Draw("C*");
	}*/
	c2->SaveAs(TString::Format("trackN%d.eps",nentries));
	// plot distribution
	TCanvas* c1 = new TCanvas("c1", "lambda A and B");
	/*c1->Divide(2,1);
	c1->cd(1);
	h1->Draw();
	c1->cd(2);*/
	/*Float_t rightmax = 1.1*h2->GetMaximum();
	cout<<rightmax<<endl;
	Float_t scale = gPad->GetUymax()/rightmax;
	h2->SetLineColor(kRed);
	h2->Scale(scale);
	h2->Draw("same");
	TGaxis* axis = new TGaxis(gPad->GetUxmax(),gPad->GetUymin(),gPad->GetUxmax(),gPad->GetUymax(),0,rightmax,510,"+L");
	axis->SetLineColor(kRed);
	axis->SetLabelColor(kRed);
	axis->Draw();
	*/
	h2->Draw();
	c1->SaveAs(TString::Format("distributionN%d.eps",nentries));
}
