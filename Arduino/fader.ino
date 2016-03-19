#include "Arduino.h"
#include "rgbcolor.h"
#include "fader.h"

Fader::Fader(int red_pin, int green_pin, int blue_pin)
{
  r_pin = red_pin;
  g_pin = green_pin;
  b_pin = blue_pin;
};

void Fader::fade( const RGBColor& in,
               const RGBColor& out,
               unsigned n_steps,  //default take 256 steps
               unsigned delay_time)   //wait 10 ms per step
{
  int red_diff   = out.r() - in.r();
  int green_diff = out.g() - in.g();
  int blue_diff  = out.b() - in.b();
  for ( unsigned i = 0; i < n_steps; ++i){
    /* output is the color that is actually written to the pins
     * and output nicely fades from in to out.
     */
    RGBColor output ( in.r() + i * red_diff / n_steps,
                       in.g() + i * green_diff / n_steps,
                       in.b() + i * blue_diff/ n_steps);
    //Serial.print(String(output.r()));
    //Serial.print(String(output.g()));
    //Serial.println(String(output.b()));
    /*put the analog pins to the proper output.*/
    analogWrite( r_pin, output.r() );
    analogWrite( g_pin, output.g() );
    analogWrite( b_pin, output.b() );
    delay(delay_time);
  }
};
