void hist2(TString str) {
	gROOT->Reset();
	const Int_t N = 100000;
	TFile *fopt = new TFile("Gauss2.root", "RECREATE");
	TH2F *h1 = new TH2F("gauss2", "Gauss 2D", 100, -5, 5, 100, -5, 5);
	Double_t x,y;
	for(int i=0;i<N;i++){
		x = gRandom->Gaus(2, 2);
		y = gRandom->Gaus(0, 2);
		//gRandom->Rannor(x, y);
		h1->Fill(x, y);
	}
	h1->GetXaxis()->SetTitle("x, Gauss(#mu=0,#sigma=2)");
	h1->GetXaxis()->CenterTitle();
	h1->GetYaxis()->SetTitle("y, Gauss(#mu=1,#sigma=5)");
	h1->GetYaxis()->CenterTitle();
	TCanvas *c1 = new TCanvas("c1", "");
	h1->Draw(str);
	fopt->Write();
	c1->SaveAs("Gauss"+str+".pdf");
}
void viewHist2() {
	TFile *fin = new TFile("Gauss2.root", "READ");
	TH2F *h1= (TH2F*) fin->Get("gauss2");
	TCanvas *c1 = new TCanvas("c2", "view each Dimension", 800, 1000);
	c1->Divide(1,2);
	c1->cd(1);
	h1->ProjectionX()->Draw();
	c1->cd(2);
	h1->ProjectionY()->Draw();
	c1->cd();
	c1->SaveAs("GaussEach.pdf");
}

