void expPlusGauss(Float_t tau=1, Float_t sigma =0.5){
	TH1F* h1= new TH1F("h1", TString::Format("tau=%.2f,sigma=%.2f",tau, sigma), 100, -5, 30);
	for(Int_t i =0;i<10000;i++){
		h1->Fill(gRandom->Exp(tau)+gRandom->Gaus(0,sigma));
	}
	TCanvas*c1=new TCanvas("c1","");
	h1->Draw();
	c1->SaveAs(TString::Format("tau=%.2fsigma=%.2f.png",tau,sigma));
}

