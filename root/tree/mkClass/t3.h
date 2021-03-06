//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Apr  7 02:19:14 2020 by ROOT version 6.16/00
// from TTree t3/Reconst events
// found on file: ex42.root
//////////////////////////////////////////////////////////

#ifndef t3_h
#define t3_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

class t3 {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Int_t           ntrack;
   Float_t         px[48];   //[ntrack]
   Float_t         py[48];   //[ntrack]
   Float_t         zv[48];   //[ntrack]
   Double_t        pv[3];

   // List of branches
   TBranch        *b_ntrack;   //!
   TBranch        *b_px;   //!
   TBranch        *b_py;   //!
   TBranch        *b_zv;   //!
   TBranch        *b_pv;   //!

   t3(TTree *tree=0);
   virtual ~t3();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
   void sortVector();
};

#endif

#ifdef t3_cxx
t3::t3(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("ex42.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("ex42.root");
      }
      f->GetObject("t3",tree);

   }
   Init(tree);
}

t3::~t3()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t t3::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t t3::LoadTree(Long64_t entry)
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

void t3::Init(TTree *tree)
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

   fChain->SetBranchAddress("ntrack", &ntrack, &b_ntrack);
   fChain->SetBranchAddress("px", px, &b_px);
   fChain->SetBranchAddress("py", py, &b_py);
   fChain->SetBranchAddress("zv", zv, &b_zv);
   fChain->SetBranchAddress("pv", pv, &b_pv);
   Notify();
}

Bool_t t3::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void t3::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t t3::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef t3_cxx
