Playing PCM audio using Timer3
==============================

This is an example on how to play a raw 8bits 8KHz PCM audio sample
using one of the ATmega32u4 PWM pins and the Timer3 library:

  http://arduino.cc/playground/Code/Timer1

There are other examples/ways of doing this, most notably:

  https://github.com/damellis/PCM/

But I couldn't make it work in Arduino Leonardo or Teensy 2.0, both
based on ATmega32u4.

After reading the docs pointed in the 'refrences' section of this
document, I found out that the same can be achieved using the Timer3
library.

The sample can be genereated with raw2c.c tool:

 1. sox -V coin.wav -b 8 -t raw -r 8000 coin8.raw
 2. raw2c coin8.raw coin8.h

The code has been tested with Teensy 2.0 only.

Demo: https://plus.google.com/104932008385650668491/posts/BE91htfJ1R9

References
----------

 - http://arduino.cc/en/Tutorial/SecretsOfArduinoPWM
 - http://arduino.cc/playground/Main/TimerPWMCheatsheet
 - http://arduino.cc/playground/Code/Timer1
 - http://www.pjrc.com/teensy/td_libs_TimerOne.html

Juan J. Martínez <jjm@usebox.net>

