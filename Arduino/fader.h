#ifndef FADER_H
#define FADER_H

#include "Arduino.h"

class Fader {

  private:
    int r_pin;
    int g_pin;
    int b_pin;
  public:
    Fader(int red_pin, int green_pin, int blue_pin);
    void fade( const RGBColor& in,
               const RGBColor& out,
               unsigned n_steps = 256,
               unsigned delay_time = 10);
};
#endif
