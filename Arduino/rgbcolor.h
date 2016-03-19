#ifndef RGBCOLOR_H
#define RGBCOLOR_H

#include "Arduino.h"

class RGBColor
{
  private:
    int my_r;
    int my_g;
    int my_b;
  public:
    RGBColor (int red, int green, int blue);
    int r() const;
    int b() const;
    int g() const;
};

#endif
