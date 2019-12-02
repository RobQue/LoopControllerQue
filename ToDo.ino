/*

Jumping valur between 2 steps, noise reduction

[Done] Led phase mapping start end led

figure out that 0.5 thing shift is it float to integer? should round it or wtf 0 must be center

august2019

Glitch low fps fixed with midi flush

Still there is some delay perhabs because of computation either noise reduction or just transfer lag? 

[done] delay might be because of midi buffer overflow, so try to implement limited FPS for midi 





Structure: 

1. ADC denoising and parameters : HowManyBits configuration 10/ 12/ 16 and output value should be something common like 16 bit value or 0 - 1 float.
2. Rotary position math : two input values per pot, and output of absolute position and relative motion vector. Output of 16 bit either 0 - 1 float. 
3. USB communication functions:
    MIDI output - PitchBend, CC absolute, Encoder CC with vector;
    MIDI input -  PitchBend, CC absolute, Note in 
    MIDI modes - in out related, and separate

   Serial protocols for debugging and for communication.
   HID - Mouse Absolue/Relative, Keyboard, Media controll (volume), Joystick X, Y Abs/Rel,

4. Display module incl the display functions for : absolute position in display, relative position display, display rotation(offset), display animation, fades
    Librery independant so it could work with both, Adafruit library, Fastled or any other.
    Display modes:
      Marker led digital shift, or led blend digital vs analog smooth fading test ! for precision view
      Absolute single color ring, another color marker.
      Limited pot style color range, another color marker.
      Limited pot style color gradient range, and constant color marker.
      Limited pot style start marker, end marker and range indicator light up anmount of leds equivalent. can have inverse mode or center mode (for pan for example)

     `Predefined rotating array indicators which can be uploaded and stored in custom banks. 
     Settings and arrays could be defined by serial or midi comands from processing or other software 
      

 */
