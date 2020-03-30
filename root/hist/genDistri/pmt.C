void pmt(Int_t N=6, Float_t nu=3){
	TH1F* h1 = new TH1F("h1","pmt distribution",100, 0, 3000);
	for(Int_t i=0;i<1000;i++){
		Int_t sum = 1;
		Int_t esum;
		for(Int_t n=0;n<N;n++){
			esum = 0;
			for(Int_t j=0;j<sum;j++)
				esum += gRandom->Poisson(nu);
			sum = esum;
			if(sum ==0){
				printf("%d:stop at %d\n",i,n);
				break;
			}
		}
		// printf("%d\n",sum);
		h1->Fill(sum);
	}
	TCanvas *c1=new TCanvas("c1","");
	h1->Draw();
	Double_t std= h1->GetStdDev();
	h1->GetXaxis()->SetTitle(TString::Format("stddev:%.2f,mean:%.2f",std*std*1000/999,h1->GetMean()));
	c1->SaveAs(TString::Format("pmt%d.png",N));
}
void pmtdynode1(Float_t nu1=6,Int_t N=6, Float_t nu=3){
	TH1F* h1 = new TH1F("h1","pmt distribution",100, 0, 6000);
	for(Int_t i=0;i<1000;i++){
		Int_t sum = 1;
		Int_t esum = 0;
		esum += gRandom->Poisson(nu1);
		sum = esum;
		if(sum != 0)	
		for(Int_t n=1;n<N;n++){
			esum = 0;
			for(Int_t j=0;j<sum;j++)
				esum += gRandom->Poisson(nu);
			sum = esum;
			if(sum ==0){
				printf("%d:stop at %d\n",i,n);
				break;
			}
		}
		// printf("%d\n",sum);
		h1->Fill(sum);
	}
	TCanvas *c1=new TCanvas("c1","");
	h1->Draw();
	Double_t std= h1->GetStdDev();
	h1->GetXaxis()->SetTitle(TString::Format("stddev:%.2f,mean:%.2f",std*std*1000/999,h1->GetMean()));
	c1->SaveAs(TString::Format("pmt%dnu1%d.png",N,nu1));
}
void pmtdynode1N12(Float_t nu1=6,Int_t N=6, Float_t nu=3){
	TH1F* h1 = new TH1F("h1","pmt distribution",50, 0, 5000);
	for(Int_t i=0;i<10000;i++){
		Int_t sum = 1;
		Int_t esum = 0;
		esum += gRandom->Poisson(nu1);
		sum = esum;
		if(sum != 0)	
		for(Int_t n=1;n<N;n++){
			esum = 0;
			for(Int_t j=0;j<sum;j++)
				esum += gRandom->Poisson(nu);
			sum = esum;
			if(sum ==0){
				// printf("%d:stop at %d\n",i,n);
				break;
			}
		}
		// printf("%d\n",sum);
		h1->Fill(sum);
	}
	TH1F* h2 = new TH1F("h2","pmt distribution",100, 0, 3000000);
	TH1F* h3 = new TH1F("h3", "test sample h1", 50, 0, 5000);
	for(Int_t i=0;i<1000;i++){
		Int_t sum = h1->GetRandom();
		h3->Fill(sum);
		Int_t esum;
		for(Int_t n=0;n<N;n++){
			esum = 0;
			for(Int_t j=0;j<sum;j++)
				esum += gRandom->Poisson(nu);
			sum = esum;
			if(sum ==0){
				printf("%d:stop at %d\n",i,6+n);
				break;
			}
		}
		// printf("%d\n",sum);
		h2->Fill(sum);
	}

	TCanvas *c1=new TCanvas("c1","",1000,400);
	c1->Divide(2,1);
	c1->cd(1);
	h2->Draw();
	Double_t std= h2->GetStdDev();
	h2->GetXaxis()->SetTitle(TString::Format("stddev:%.2f,mean:%.2f",std*std*1000/999,h2->GetMean()));
	c1->cd(2);
	h3->Draw();
	std = h3->GetStdDev();
	h3->GetXaxis()->SetTitle(TString::Format("stddev:%.2f,mean:%.2f",std*std*1000/999,h3->GetMean()));
	c1->SaveAs(TString::Format("pmt%dnu%d.png",12,nu1));
}

