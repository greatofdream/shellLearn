#include "TObject.h"
//to write a simple tree
//to run: root -l ex41.C
//by yangzw, 2008.03.20
//
class Evt_t: public TObject{
public:
	Float_t px;
	Float_t py;
	Float_t pz;
	Double_t random;
	Int_t i;

	ClassDef(Evt_t,1);
};
	
void ex41() {
   TFile *f = new TFile("tree1.root","recreate");
   TTree *t1 = new TTree("t1","test tree");
   gRandom->SetSeed(0);
   Evt_t* evt = new Evt_t();
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
   t1->Branch("evt", "Evt_t",&evt,3200,99);
   for (i=0;i<5000;i++) {
	gRandom->Rannor(evt->px,evt->py);
	evt->pz = evt->px*evt->px + evt->py*evt->py;
	evt->random = gRandom->Rndm();
	evt->i = i;
	t1->Fill();//Fill tree
   }
   t1->Write();
}
