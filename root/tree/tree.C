//to write a simple tree
//to run: root -l ex41.C
//by yangzw, 2008.03.20
//
struct Evt_t{
	Float_t px;
	Float_t py;
	Float_t pz;
	Double_t random;
	Int_t i;

};
	
void tree() {
   TFile *f = new TFile("tree.root","recreate");
   TTree *t1 = new TTree("t1","test tree");
   gRandom->SetSeed(0);
   Evt_t evt;
   Float_t px,py,pz;
   Double_t random;
   Int_t i;
   //Set the Branches of tree
   /*
   t1->Branch("px",&px,"px/F");
   t1->Branch("py",&py,"py/F");
   t1->Branch("pz",&pz,"pz/F");
   t1->Branch("random",&random,"random/D");
   t1->Branch("i",&i,"i/I");
   */
   t1->Branch("evt",&evt.px,"px/F:py/F:pz/F:random/D:i/I");
   for (i=0;i<5000;i++) {
	gRandom->Rannor(evt.px,evt.py);
	evt.pz = evt.px*evt.px + evt.py*evt.py;
	evt.random = gRandom->Rndm();
	evt.i = i;
	t1->Fill();//Fill tree
   }
   t1->Write();
}
void readTree(){
	TFile* fin=new TFile("tree.root");
	Int_t N = 100;
	Evt_t evt;
	TTree * t1 = (TTree*)fin->Get("t1");
	t1->SetBranchAddress("evt",&evt);
	for(int i=0;i<N;i++){
		t1->GetEntry(i);
		printf("%2f,%2f,%2f,%2f,%d\n",evt.px,evt.py,evt.pz,evt.random,evt.i);
	}
}	
