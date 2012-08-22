/*
 * Play example using Time3 library.
 *
 * The sample must be raw 8bits 8KHz, please read README.md.
 *
 * References:
 *
 *  - http://arduino.cc/en/Tutorial/SecretsOfArduinoPWM
 *  - http://www.arduino.cc/playground/Main/TimerPWMCheatsheet
 *  - http://arduino.cc/playground/Code/Timer1
 *  - http://www.pjrc.com/teensy/td_libs_TimerOne.html
 *
 *  Juan J. Martinez <jjm@usebox.net>
 *  https://github.com/reidrac/play-pcm-example
 */

#include <avr/pgmspace.h>
#include <TimerThree.h>

/* sample to play */
#include "coin8.h"

volatile unsigned char *play_sample;
volatile unsigned short play_sample_length;
volatile unsigned short play_sample_ptr;
volatile int play_pin;

/* for Teensy 2.0: pin 9 */
void init_play(unsigned char pin)
{
  play_sample_length = 0;
  play_pin = pin;

  pinMode(play_pin, OUTPUT);

  // 8KHz are 125 microsencodns
  Timer3.initialize(125);
  Timer3.attachInterrupt(play_cb);
  Timer3.pwm(pin, HIGH);
}

void play_cb(void)
{
  if(play_sample_length)
  {
    Timer3.setPwmDuty(play_pin, pgm_read_byte(&play_sample[play_sample_ptr]));
    play_sample_ptr++;

    if(play_sample_ptr == play_sample_length)
    {
      play_sample_length = 0;
      Timer3.setPwmDuty(play_pin, 0);
    }
  }
}

void play(const unsigned char *sample, const unsigned short length)
{
  noInterrupts();
  play_sample = (unsigned char *)sample;
  play_sample_ptr = 0;
  play_sample_length = length;
  interrupts();
}

void setup()
{
  init_play(9);
  play(coin8, coin8_len);
}

void loop()
{
  /* nothing */
}

/* EOF */
