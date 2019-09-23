/**
 * @file HSLAPixel.cpp
 */

#include <cmath>
#include <iostream>
#include "HSLAPixel.h"
using namespace std;

namespace Image {

  int HSLAPixel::cdistance(double x, double y){

    int rvalue = (int(x) - int(y) + 180) % 360 - 180;

    return rvalue;
  }
}
