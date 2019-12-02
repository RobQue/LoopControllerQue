// include the ResponsiveAnalogRead library
#include <ResponsiveAnalogRead.h>

// make a ResponsiveAnalogRead objects, pass in the pins, and either true or false depending on if you want sleep enabled
// enabling sleep will cause values to take less time to stop changing and potentially stop changing more abruptly,
//   where as disabling sleep will cause values to ease into their correct position smoothly and more accurately

bool analogSleep = true;
ResponsiveAnalogRead analog[] = {
  ResponsiveAnalogRead(A0, analogSleep),
  ResponsiveAnalogRead(A1, analogSleep),
  ResponsiveAnalogRead(A2, analogSleep),
  ResponsiveAnalogRead(A3, analogSleep),
  ResponsiveAnalogRead(A4, analogSleep),
  ResponsiveAnalogRead(A5, analogSleep),
  };

//ResponsiveAnalogRead analogOne(A0, true);
//ResponsiveAnalogRead analogTwo(A1, true);

#define analogObjectsQuantity  sizeof(analog) / sizeof(analog[0])

float rad[analogObjectsQuantity/2]; // because 2 analogs per pot
float lastrad[analogObjectsQuantity/2];
float radstep[analogObjectsQuantity/2];

// the next optional argument is snapMultiplier, which is set to 0.01 by default
// you can pass it a value from 0 to 1 that controls the amount of easing
// increase this to lessen the amount of easing (such as 0.1) and make the responsive values more responsive
// but doing so may cause more noise to seep through if sleep is not enabled

int analogResolution = 1024;  // how many bits ADC

int precision = 180; // Presision for degrees/

//----------------------------------------------------------------------------------------------------------- ANALOG360 Variables


// A basic everyday NeoPixel strip test program.


// NEOPIXEL BEST PRACTICES for most reliable operation:
// - Add 1000 uF CAPACITOR between NeoPixel strip's + and - connections.
// - MINIMIZE WIRING LENGTH between microcontroller board and first pixel.
// - NeoPixel strip's DATA-IN should pass through a 300-500 OHM RESISTOR.
// - AVOID connecting NeoPixels on a LIVE CIRCUIT. If you must, ALWAYS
//   connect GROUND (-) first, then +, then data.
// - When using a 3.3V microcontroller with a 5V-powered NeoPixel strip,
//   a LOGIC-LEVEL CONVERTER on the data line is STRONGLY RECOMMENDED.
// (Skipping these may work OK on your workbench but can fail in the field)

#include "MIDIUSB.h"
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1:
#define LED_PIN    6

// How many NeoPixels are attached to the Arduino?
#define LED_COUNT 108

// Declare our NeoPixel strip object:
int wait = 30;
//float rad[3];
//float lastrad[3];
//float radstep[3];
float relative[3] = {0.6, 0.6, 0.6};

float lastval;
int receivedPitchBend;
bool pitchBendReceived;

unsigned long previousMillis = 0;        //FPS
const long interval = 10;

//ResponsiveAnalogRead analogOne(A0, true);
//ResponsiveAnalogRead analogTwo(A1, true);

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
// Argument 1 = Number of pixels in NeoPixel strip
// Argument 2 = Arduino pin number (most are valid)
// Argument 3 = Pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)


// setup() function -- runs once at startup --------------------------------

void setup() {
  // These lines are specifically to support the Adafruit Trinket 5V 16 MHz.
  // Any other board, you can remove this part (but no harm leaving it):
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  // END of Trinket-specific code.
  //potFromPotSetup();
  
  analog360initialize();


  Serial.begin(115200);

  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(255); // Set BRIGHTNESS to about 1/5 (max = 255)
}


// loop() function -- runs repeatedly as long as board is on ---------------

  void loop() {

  //receiveMIDI();
  receivedPitchBend = receivePitchBend(0);
  
calculateRads();
calculateRadsteps();

  // get midi from usb and set it to current bufffer (override the relative) if it changed
  if(pitchBendReceived)
  {
    float pbr = float(receivedPitchBend);
    relative[0] = map (pbr, 0, 16383, -129, 139);
    pitchBendReceived = LOW;
  }
   //pitchBendReceived = LOW;
  
  relative[0] = relative[0] + radstep[0];
  relative[0] = constrain(relative[0], -129, 139);
  //Serial.print( relative[0] );
  //if ( relative[0] > 180.6 ) relative[0] = 180.6; //because of round
  //if ( relative[0] < -179.4 ) relative[0] = -179.4; //because of round to int
  float ralfine = relative[0]*1000;
  float pitchb = map(ralfine/10, -12900, 13900, 0, 16383);

  
  unsigned long currentMillis = millis();  //fps limit
  
  if (currentMillis - previousMillis >= interval) 
  {
      // save the last time you blinked the LED
    previousMillis = currentMillis;
    
     if (pitchb != lastval) // avoid sending repetative midi data
     {
        pitchBend(0, (int) pitchb );
        //Serial.println( relative[0] );
        //Serial.println ((int)pitchb);
        lastval = pitchb;
     }
}

  
  
  //relative[0] = relative[0] * -1;

//  Serial.print( rad[0] );
//  Serial.print( "\t");
//  Serial.print( radstep[0] );
//  Serial.print( "\t");
//  Serial.print( relative[0] );
//  Serial.print( "\t");
//  Serial.print( "\t");
//    
//  Serial.print( rad[1] );
//  Serial.print( "\t");
//  Serial.print( rad[2] );
//  Serial.println( "\t");

  //Serial.println( readVcc(), DEC );

  int x = 0;
  int constrL = 4;
  int constrR = 30;

  for (int i = 0 ; i < 36; i++) //display scanner; value input must range in 36 leds
  {
    //x = 35- (rad[0]/10 + 17); //absolute radian display; absolute ranges from -180 to 180
    x = relative[0] / 10 + 17; //relative ranges from 0 to 360
    if (i >= constrL && i <= constrR)
    {
      if (x == i) //if display scan position matches value, light up marker
      {
        strip.setPixelColor(shiftPhase( i, 36, -10), strip.Color(36,12,24));//6, 2, 4));       //  Set pixel's color (in RAM)
      }
      else
      {
        strip.setPixelColor(shiftPhase( i, 36, -10), strip.Color(1, 0, 0));       //  Set pixel's color (in RAM)
      }
    }
  }
  strip.show();
  //delay(wait);                           //  Pause for a moment
  lastrad[0] = rad[0];
  lastrad[1] = rad[1];
  lastrad[2] = rad[2]; 
}

long readVcc() {
  long result;
  // Read 1.1V reference against AVcc
  ADMUX = _BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
  delay(2); // Wait for Vref to settle
  ADCSRA |= _BV(ADSC); // Convert
  while (bit_is_set(ADCSRA, ADSC));
  result = ADCL;
  result |= ADCH << 8;
  result = 1125300L / result; // Back-calculate AVcc in mV
  return result;
}

int shiftPhase( int val, int maxVal, int shift) // shift cant be more then maxVal
{
  int shiftedVal = val + shift;

  if (shiftedVal >= maxVal) shiftedVal = shiftedVal - maxVal;
  if (shiftedVal < 0) shiftedVal = shiftedVal + maxVal;

  return shiftedVal;

}
