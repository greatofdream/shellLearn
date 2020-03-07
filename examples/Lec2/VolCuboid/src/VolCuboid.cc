
#include "VolCuboid.h"
#include "math.h"
#define PI 3.141592
VolCuboid::VolCuboid(float x, float y, float z) {
   length = x ;
   width  = y ;
   height = z ;
}

VolCuboid::~VolCuboid() {
   //new pointers should be deleted here.
   //if not, do nothing.
}

float VolCuboid::Vol() {
   return length*width*height;
}

float VolCuboid::Area() {
   float area;
   area = 2*length*width + 2*length*height + 2* width*height ;
   return area;
}
float VolCuboid::maxSphereVolume(){
    float maxR = length>width?width:length;
    maxR = maxR>height?height:maxR;
    return 3*PI*pow(maxR,3)/4;
}
