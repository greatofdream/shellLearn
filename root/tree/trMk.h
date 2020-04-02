//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Apr  2 12:47:05 2020 by ROOT version 6.16/00
// from TTree t1/test tree
// found on file: treeMk.root
//////////////////////////////////////////////////////////

#ifndef trMk_h
#define trMk_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

class trMk {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Float_t         p_px;
   Float_t         p_py;
   Float_t         p_pz;
   Double_t        random;
   Int_t           i;

   // List of branches
   TBranch        *b_p;   //!
   TBranch        *b_random;   //!
   TBranch        *b_i;   //!

   trMk(TTree *tree=0);
   virtual ~trMk();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef trMk_cxx
trMk::trMk(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("treeMk.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("treeMk.root");
      }
      f->GetObject("t1",tree);

   }
   Init(tree);
}

trMk::~trMk()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t trMk::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t trMk::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void trMk::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("p", &p_px, &b_p);
   fChain->SetBranchAddress("random", &random, &b_random);
   fChain->SetBranchAddress("i", &i, &b_i);
   Notify();
}

Bool_t trMk::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void trMk::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t trMk::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef trMk_cxx
