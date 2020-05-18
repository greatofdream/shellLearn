#include <iostream>
#include "TMath.h"
#include "TMatrixD.h"
#include "TMatrixDLazy.h"
#include "TVectorD.h"

void linearSquare(){
	const Int_t msize=5;
	Double_t ax[msize] = {};
	TVectorD x;
	x.Use(msize, ax);
}
