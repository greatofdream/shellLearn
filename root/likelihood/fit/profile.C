#include "RooRealVar.h"
#include "RooConstVar.h"
#include "RooGaussian.h"
#include "RooArgusBG.h"
#include "RooAddPdf.h"
#include "RooDataSet.h"
#include "RooPlot.h"

using namespace RooFit;

void profile() {
	RooWorkspace w("w");
	// Here, cast into appropriate type directly. Since return type overloading is impossible in C++, this has to be done manually
   	auto g1 = (RooAbsPdf*) w.factory("Gaussian::g1(x[-20,20],mean[-10,10],sigma_g1[3])");
        auto g2 = (RooAbsPdf*) w.factory("Gaussian::g2(x,mean,sigma_g2[4,3,6])");
        auto model = (RooAbsPdf*) w.factory("SUM::model(frac[0.5,0,1]*g1,g2)");
        auto x = w.var("x");
        auto frac = w.var("frac");
        // Generate 1000 events 
        RooDataSet* data = model->generate(*x, 1000);
        // Create likelihood function
        RooAbsReal* nll = model->createNLL(*data, NumCPU(2));
	// Minimize likelihood
	RooMinuit(*nll).migrad();
	// Plot likelihood scan in parameter frac
	RooPlot* frame1 = frac->frame(Bins(10), Range(0.01,0.95));
	nll->plotOn(frame1,ShiftToZero());
	// Plot the profile likelihood in frac
	RooAbsReal* pll_frac = nll->createProfile(*frac);
	pll_frac->plotOn(frame1, LineColor(kRed));
	frame1->Draw();
}
