/*
  MIDI Driven Drumbot
  ©2024 Crunchysteve
  ----------------------
  This code will be the MIDI driven heart of SoléBot, the solenoid driven drumbot. 

  Dynamics are provided by using analogWrite() on channels that need them, or digitalWrite() for 
  the channels that don't, with a timed pulse to kick 12v solenoids with 24v for just long enough 
  to never exceed 24W RMS applied to each solenoid, even at maximum tempo. The MIDI note number 
  corresponding to each drum will determine which solenoid operates, while MIDI velocity + 127 
  applied to analogWrite() on the PWM outputs will generate soft to loud hits.

  This code will run on almost any micro, but the pins are setup for an Arduino Uno or Nano. 
  Use a dual AOD4184 MOSFET module, such as this one, 
    https://core-electronics.com.au/mosfet-power-switch-module.html, to drive each solenoid.

  I'm using JF-0826B 12v/2A 20N solenoids and, because of the light duty cycle, I run them from
  24V via the MOSFET boards. I haven't tried higher than 30v yet, but neither Solenoids nor the 
  MOSFETS run hot at 30v, even when run for extended periods. Non-blocking timing will be used to 
  pulse PWM drive just long enough to get the beater within a millimetre of the drum skin.
  
  All code, including C code and the OpenSCAD bracket 3D files, are hosted on
    https://github.com/crunchysteve/Solebot while,
  the OpenSCAD models are also hosted here 
    https://www.thingiverse.com/thing:6771931 without without C code.
  
  This code is copyright ©2024 Crunchysteve and is available for use or modification under an MIT 
  licence, except for commercial use, whereupon the author would appreciate a percentage of device 
  sales in exchange for any licence for manufacturing this project commercially.

  This preamble must always remain at the head of all 3d models and source code.
*/

#ifndef PINS_H
    #define PINS_H
      //  Define output pins for each percussion
        #define CLCK 2    /* Click or count with sticks */
        #define KICK 3    /* Kick drum */
        #define CRSH 4    /* Crash cymbal */
        #define SNRE 5    /* Snare drum */
        #define HHAT 6    /* Hi hat stick drive */
        #define HOPN 7    /* Hi hat top lift (open hat) */
        #define HCLS 8    /* Hi hat bottom lift (closed hat) */
        #define RTOM 9    /* Rack tom */
        #define FTOM 10   /* Floor tom */
        #define RIDE 11   /* Ride cymbal */
        #define CBEL 12   /* Cow bell or woodblock */
      //  The fields in each drum represent...
      //  MIDI note number, output pin, whether analog or digital out, 
      //                                whether out has been played and at what time.
        byte DRUMS[][5] = {
          {STICK_CLICK,CLCK,0,0,0},   /* Stick Click, pin 2, digital, triggered, ms */
          {KICK_DRUM,KICK,1,0,0},     /* Kick Drum, pin 3, analog, triggered, ms */
          {CRASH_CYMBAL,CRSH,0,0,0},  /* Crash Cymbal, pin 4, digital, triggered, ms */
          {SNARE_DRUM,SNRE,1,0,0},    /* Snare Drum, pin 5, analog, triggered, ms */
          {HI_HAT_HALF,HHAT,1,0,0},   /* HiHat hit (half open), pin 6, analog, 
                                                                          triggered, millis() */
          {HI_HAT_OPEN,HOPN,0,0,0},   /* HiHat hit (top lift open), pin 7, digital, 
                                                                          triggered, millis() */
          {HI_HAT_CLOSED,HCLS,0,0,0}, /* HiHat hit (bottom lift close), pin 8, digital, 
                                                                          triggered, millis() */
          {HIGH_MID_TOM,RTOM,1,0,0},  /* Rack Tom, pin 9, analog, triggered, ms */
          {FLOOR_TOM_1,FTOM,1,0,0},   /* Floor Tom, pin 10, analog, triggered, ms */
          {RIDE_CYMBAL,RIDE,1,0,0},   /* Ride Cymbal, pin 11, analog, triggered, ms */
          {COWBELL,CBEL,0,0,0}        /* Cowbell, pin 12, digital, triggered, ms */
        };
        byte LED = 13;             //  Will (eventually) flash the LED every quaternote from MIDI clock
#endif