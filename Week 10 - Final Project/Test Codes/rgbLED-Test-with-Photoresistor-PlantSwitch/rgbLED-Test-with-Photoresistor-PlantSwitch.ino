int humanSwitchPin = A3;
int humanSwitchVal = 0;
int switchResponsePin = 9;
int humanSwitchState = 0;

int humanSwitchPin2 =A2;
int humanSwitchVal2 = 0;
int switchResponsePin2 = 9;
int humanSwitchState2 = 0;


int pressurePin = A4;
int pressureVal = 0;

int lightSensVal = 0;
int lightSensPin = A0;
int brightness = 64;

int red1 = 50;
int green1 = 5;
int blue1 = 0;
int white1 = 20;

int red2 =20;
int green2 = 50;
int blue2 = 0;
int white2 = 10;

int r = 0;
int g = 0;
int b = 0;
int w = 0;

int rTarget = 0;
int gTarget = 0;
int bTarget = 0;
int wTarget = 0;

int sensMax = 24;
int brightMin = 180;
int brightMax = 20;


//for rgbLED control:

#include <FastLED.h>
//blspecial addition to the FastLED library to work with
//an RGBW strip from https://www.partsnotincluded.com/fastled-rgbw-neopixels-sk6812/
#include "FastLED_RGBW.h";

#define LED_PIN     3
#define NUM_LEDS    100
#define BRIGHTNESS  64
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB
#define UPDATES_PER_SECOND 100

CRGBW leds[NUM_LEDS];
CRGB *ledsRGB = (CRGB *) &leds[0];


void setup() {
  delay( 3000 ); // power-up safety delay

  Serial.begin(9600);

  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(ledsRGB, NUM_LEDS);
  pinMode(switchResponsePin, OUTPUT);
  pinMode(switchResponsePin2, OUTPUT);


  r = red1;
  b = blue1;
  g = green1;
  w = white1;

  rTarget = red1;
  bTarget = blue1;
  gTarget = green1;
  wTarget = white1;

}


void loop()
{

  pressureVal = analogRead(pressurePin);
  //Serial.println(pressureVal);

  
  humanSwitchVal = analogRead(humanSwitchPin);
  //Serial.print(" SW 1: ");
  //Serial.println(humanSwitchVal);

  humanSwitchVal2 = analogRead(humanSwitchPin2);
//  Serial.print(" SW 2: ");
//  Serial.println(humanSwitchVal2);

  if (humanSwitchVal2 < 940) {
    humanSwitchState = humanSwitchState + (255-humanSwitchState)*0.05;
    rTarget=red2;
    gTarget=green2;
    bTarget=blue2;
    wTarget=white2;
  }
  else if (humanSwitchVal < 940) {
    humanSwitchState = humanSwitchState + (255-humanSwitchState)*0.05;
    rTarget=red1;
    gTarget=green1;
    bTarget=blue1;
    wTarget=white1;
  }
  else {
    humanSwitchState = humanSwitchState - (humanSwitchState-0)*0.05;
  }


 //animate colors if there is a change of state
  r=r-(r-rTarget)*0.05;
  g=g-(g-gTarget)*0.05;
  b=b-(b-bTarget)*0.05;
  w=w-(w-wTarget)*0.05;

  Serial.print(r);
  Serial.print(" ");
  Serial.print(g);
  Serial.print(" ");
  Serial.print(b);
  Serial.print(" ");
  Serial.println(w);
 
  analogWrite(switchResponsePin, humanSwitchState);
  //Serial.println(humanSwitchState);


 
  //getting the sensor reading to change brightness value
   lightSensVal = analogRead(lightSensPin);
  //Serial.println(lightSensVal);
  
  //smoothing out the value change by always only moving by 4% of the brightness difference
  brightness = brightness + (map(lightSensVal, 0, sensMax, brightMin, brightMax) - brightness) * 0.04;


  FillColors();

  FastLED.setBrightness( brightness );
  FastLED.show();
  FastLED.delay(1000 / UPDATES_PER_SECOND);

}


void FillColors ()
{

  for ( int i = 0; i < NUM_LEDS; i++) {

    if (i % 3 == 2) { // these LEDs are B3 G3 R3 W3
      leds[i] = CRGBW(b, g, r, w);
    }
    else if (i % 3 == 0) { // these LEDS are G1 R1 B1 G2 don't ask me why
      leds[i] = CRGBW(g, r, b, g);
    }
    else if (i % 3 == 1) { // these LEDS are R2 W1 W2 B2 really don't ask
      leds[i] = CRGBW(r, w, w, b);

    }

  }
}







// This example shows how to set up a static color palette
// which is stored in PROGMEM (flash), which is almost always more
// plentiful than RAM.  A static PROGMEM palette like this
// takes up 64 bytes of flash.
const TProgmemPalette16 myColorPalette_p PROGMEM =
{
  CRGB::Red,
  CRGB::Pink, // 'white' is too bright compared to red and blue
  CRGB::DeepPink,
  CRGB::Black,

  CRGB::Red,
  CRGB::Gray,
  CRGB::Pink,
  CRGB::DeepPink,

  CRGB::Red,
  CRGB::Red,
  CRGB::Gray,
  CRGB::Gray,
  CRGB::DeepPink,
  CRGB::Pink,
  CRGB::DeepPink,
  CRGB::Pink,
};
