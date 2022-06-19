
void fitoptshow(){
	gStyle->SetOptFit(1001);
	TH1F *h1 = new TH1F("h1", "h1", 200, -5,5);
TF1 *f1 = new TF1("f1", "[2]*TMath::Gaus(x,[0],[1])");
f1->SetParameters(1,1,1);
h1->FillRandom("f1");
h1->Draw();
h1->Fit("gaus");
}
