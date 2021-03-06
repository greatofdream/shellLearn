//#########ex22.cc##################

#include <iostream>
//#include <math>

#include "VolCuboid.h"
//#include "TH1F.h"

using namespace std;

int main ()
{
   std::cout << "This is exercise 22......" << endl;
   float length, width, height;
   
   length = 2.0 ; //cm
   width  = 3.0 ; //cm
   height = 4.0 ; //cm

   VolCuboid myVolCuboid( length, width, height );
   //VolCuboid *myVolCuboid = new VolCuboid( length, width, height );

   float volume = myVolCuboid.Vol() ;
   //float volume = myVolCuboid->Vol() ;
   cout << "Volume is " << volume << " cm^3" << endl;
   cout << "Area   is " << myVolCuboid.Area() << " cm^2" << endl;
   cout << "Max sphere volume is "<<myVolCuboid.maxSphereVolume()<<"cm^3"<<endl;
   //cout << "Area   is " << myVolCuboid->Area() << " cm^2" << endl;
   //TH1F *h1 = new TH1F("h1","",100,-3,3);
   //cout << h1->GetBinWidth(10) << endl;
}
