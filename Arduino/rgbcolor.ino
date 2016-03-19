#include "Arduino.h"
#include "rgbcolor.h"

RGBColor::RGBColor (int red, int green, int blue)
{
  my_r = red;
  my_g = green;
  my_b = blue;
};
int RGBColor::r() const {return my_r;}
int RGBColor::g() const {return my_g;}
int RGBColor::b() const {return my_b;}

