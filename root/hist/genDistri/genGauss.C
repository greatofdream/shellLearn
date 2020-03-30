void genGauss(Int_t n =0){
	TH1F** h0 = new TH1F*[20];
	TCanvas *c1 = new TCanvas("c1", "different genGauss", 1000, 1000);
	c1->Divide(4,5);
	for(Int_t i=1;i<=20;i++){
		h0[i-1] = new TH1F(TString::Format("h%d",i),"",100,-5,5);
		Float_t sum;
		Float_t E = Float_t(i)/2;
		Float_t sigma = sqrt(E/6);
		for(Int_t j=0;j<10000;j++){
			sum = 0;
			for(Int_t k=0;k<i;k++){
				sum += gRandom->Uniform(0,1);
			}
			h0[i-1]->Fill((sum-E)/sigma);
		}
		c1->cd(i);
		h0[i-1]->Draw();
		h0[i-1]->GetXaxis()->SetTitle(TString::Format("num:%d",i));
		h0[i-1]->GetXaxis()->CenterTitle();
		//h1->Reset();
	}
	c1->SaveAs("Gauss.png");
}

