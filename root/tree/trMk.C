#define trMk_cxx
#include "trMk.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <math.h>

void trMk::Loop()
{
//   In a ROOT session, you can do:
//      root> .L trMk.C
//      root> trMk t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();
    TH1F* totalP = new TH1F("tp","total P",100,-5,5);
    TH1F* partP = new TH1F("pp", "part P",100, -5,5);
   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      //nb = fChain->GetEntry(jentry);   nbytes += nb;
      fChain->GetEntry(jentry);
      
      totalP->Fill(sqrt(p_pz));
      if(i<20)
	      partP->Fill(sqrt(p_pz));
   }
   TCanvas* c1 = new TCanvas("c1","");

   totalP->Draw();
   partP->Draw("Same");
   c1->SaveAs("treeroot1.png");
	      // if (Cut(ientry) < 0) continue;
   
}
