void genDistri(Int_t xmax=10){
	// method=0:transfer;else:selcte
	TH1F* h1= new TH1F("h1", "tranfer method xm^2*y",100, 0, xmax);
	TH1F* h2 = new TH1F("h2", "select method", 100, 0, xmax);
	//transfer,f^-1=xm^2*y
	for(Int_t i =0;i<10000;i++){
		h1->Fill(xmax*sqrt(gRandom->Uniform(0, 1)));
	}
	//select method
	Float_t tempx,tempy;
	for(Int_t i=0;i<10000;i++){
		tempx = gRandom->Uniform(0, xmax);
		tempy = gRandom->Uniform(0, 1);
		if(tempy<2*tempx/xmax/xmax)
			h2->Fill(tempx);
	}
	TCanvas *c1= new TCanvas("c1", "generate distirbution", 1000, 500);
	c1->Divide(2,1);
	c1->cd(1);
	h1->Draw();
	h1->GetXaxis()->SetTitle("x,num:10000");
	c1->cd(2);
	h2->Draw();
	h2->GetXaxis()->SetTitle("x,num:10000");
	c1->SaveAs("genDistribution.pdf");
}
