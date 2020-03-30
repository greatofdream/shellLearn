void cauchy(){
	TH1F* h1 = new TH1F("h1","cauchy distribution",100, -10, 10);
	for(Int_t i=0;i<10000;i++){
		h1->Fill(tan(3.1415926*(gRandom->Uniform(0,1)-0.5)));
	}
	TCanvas *c1=new TCanvas("c1","");
	h1->Draw();
	c1->SaveAs("cauchyDistribution.png");
}
void cauchyMean(Int_t n=10){
	TH1F* h1 = new TH1F("h1","cauchy distribution",100, -10, 10);
	for(Int_t i=0;i<10000;i++){
		Float_t sum = 0;
		for(Int_t j=0;j<n;j++)
			sum += tan(3.1415926*(gRandom->Uniform(0,1)-0.5));
		h1->Fill(sum/n);
	}
	TCanvas *c1=new TCanvas("c1","");
	h1->Draw();
	c1->SaveAs(TString::Format("cauchyMean%d.png",n));
}
