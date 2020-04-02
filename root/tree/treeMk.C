void treeMk() {
	TFile *f = new TFile("treeMk.root","recreate");
	TTree *t1 = new TTree("t1","test tree");
	gRandom->SetSeed(0);
	Float_t px,py,pz;
	float p[3];
	Double_t random;
	Int_t i;
	//Set the Branches of tree
	t1->Branch("p",p,"px:py:pz");
	t1->Branch("random",&random,"random/D");
	t1->Branch("i",&i,"i/I");
	for (i=0;i<5000;i++) {
		gRandom->Rannor(px,py);
		pz = px*px + py*py;
		random = gRandom->Rndm();
		p[0]=px;p[1]=py;p[2]=pz;
		t1->Fill();//Fill tree
	}
	t1->Write();
	//t1->MakeClass("trMk");
}
void sortVector() {
	TFile *t = new TFile("treeMk.root");
	TTree* t1= (TTree*)t->Get("t1");
	Float_t p[3];
	t1->GetBranch("p")->SetAddress(&p);
	std::vector<float> vpx;
	Int_t nentries = (Int_t)t1->GetEntries();
	for(Int_t i=0; i<nentries;i++){
		t1->GetEntry(i);
		vpx.push_back(p[0]);
	}
	std::sort(vpx.begin(), vpx.end());
	for(Int_t i=0;i<100;i++){
		printf("%.2f\n",vpx[i]);
	}
}
	
