// include the ResponsiveAnalogRead library
#include <ResponsiveAnalogRead.h>

// make a ResponsiveAnalogRead objects, pass in the pins, and either true or false depending on if you want sleep enabled
// enabling sleep will cause values to take less time to stop changing and potentially stop changing more abruptly,
//   where as disabling sleep will cause values to ease into their correct position smoothly and more accurately

ResponsiveAnalogRead analogOne(A0, true);
ResponsiveAnalogRead analogTwo(A1, true);

// the next optional argument is snapMultiplier, which is set to 0.01 by default
// you can pass it a value from 0 to 1 that controls the amount of easing
// increase this to lessen the amount of easing (such as 0.1) and make the responsive values more responsive
// but doing so may cause more noise to seep through if sleep is not enabled

int analogResolution = 1024;

analogOne.setAnalogResolution(analogResolution);




void analog360setup()
{
  analogOne.setAnalogResolution(analogResolution); 
}






























//Analog functions
// analog.update(); // on each loop update analog and denoise
//if(analog.hasChanged()) { // if analog has changed execute update 
//    Serial.print(analog.getValue()); //the filtered analog value
//    Serial.print(analog.getRawValue()); //the raw analog read value
//  }
 
