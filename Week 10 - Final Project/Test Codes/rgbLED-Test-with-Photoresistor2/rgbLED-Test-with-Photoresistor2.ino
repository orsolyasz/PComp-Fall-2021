int humanSwitchPin = A2;
int humanSwitchVal = 0;
int switchResponsePin = 9;
int humanSwitchState = 0;

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


//CRGBPalette16 currentPalette;
//TBlendType    currentBlending;
//extern CRGBPalette16 myColorPalette;
//extern const TProgmemPalette16 myColorPalette_p PROGMEM;


void setup() {
  delay( 3000 ); // power-up safety delay

  Serial.begin(9600);

  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(ledsRGB, NUM_LEDS);
  pinMode(switchResponsePin, OUTPUT);


  r = red1;
  b = blue1;
  g = green1;
  w = white1;


  //FastLED.setBrightness(  BRIGHTNESS );
  //  FastLED.setBrightness(  brightness );
  //  currentPalette = myColorPalette_p;
  //
  //  currentBlending = NOBLEND;
}


void loop()
{

  lightSensVal = analogRead(lightSensPin);
  //Serial.println(lightSensVal);
  humanSwitchVal = analogRead(humanSwitchPin);
//  Serial.println(humanSwitchVal);
  if (humanSwitchVal < 1003) {
    humanSwitchState = humanSwitchState + (255-humanSwitchState)*0.05;
    r=red2;
    g=green2;
    b=blue2;
    w=white2;
  }
  else {
    humanSwitchState = humanSwitchState - (humanSwitchState-0)*0.05;
  }
  analogWrite(switchResponsePin, humanSwitchState);
  Serial.println(humanSwitchState);

  //changing brightness value based on the sensor reading,
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
