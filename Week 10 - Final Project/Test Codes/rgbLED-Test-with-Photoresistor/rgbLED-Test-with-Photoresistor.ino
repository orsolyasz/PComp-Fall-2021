int lightSensVal = 0;
int lightSensPin = A0;
int brightness = 64;

//for rgbLED control:

#include <FastLED.h>
#include "FastLED_RGBW.h";


#define LED_PIN     3
#define NUM_LEDS    100
#define BRIGHTNESS  64
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB
#define UPDATES_PER_SECOND 100

//CRGB leds[NUM_LEDS];
CRGBW leds[NUM_LEDS];
CRGB *ledsRGB = (CRGB *) &leds[0];


CRGBPalette16 currentPalette;
TBlendType    currentBlending;
extern CRGBPalette16 myColorPalette;
extern const TProgmemPalette16 myColorPalette_p PROGMEM;


void setup() {
  delay( 3000 ); // power-up safety delay

  Serial.begin(9600);

  //FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  //FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  //FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(ledsRGB, getRGBWsize(NUM_LEDS));
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(ledsRGB, NUM_LEDS);



  //FastLED.setBrightness(  BRIGHTNESS );
//  FastLED.setBrightness(  brightness );
//  currentPalette = myColorPalette_p;
//
//  currentBlending = NOBLEND;
}


void loop()
{

  lightSensVal = analogRead(lightSensPin);
  Serial.println(lightSensVal);


  //ChangePalettePeriodically();

  static uint8_t startIndex = 0;
  startIndex = startIndex + 1; /* motion speed */

  FillLEDsFromPaletteColors(startIndex);
  FastLED.setBrightness( brightness );
  FastLED.show();
  FastLED.delay(1000 / UPDATES_PER_SECOND);

  brightness = brightness + (map(lightSensVal, 0, 20, 5, 160)-brightness)*0.05;
}


void FillLEDsFromPaletteColors( uint8_t colorIndex)
{
  //uint8_t brightness = 255;

  //    for( int i = 0; i < NUM_LEDS; i++) {
  //        leds[i] = ColorFromPalette( currentPalette, colorIndex, brightness, currentBlending);
  //        //leds[i].setRGB( i, 100, 150);
  //        colorIndex += 3;
  //    }


  for ( int i = 0; i < NUM_LEDS; i++) {

   if (i % 3 == 2) { // these LEDs are B3 G3 R3 W3
      leds[i] = CRGBW(10, 0, 20, 20);
    }
    else if (i % 3 == 0) { // these LEDS are G1 R1 B1 G2 don't ask me why
      leds[i] = CRGBW(0, 20, 10, 0);
    }
    else if (i % 3 == 1) { // these LEDS are R2 W1 W2 B2 really don't ask
      leds[i] = CRGBW(20, 20, 20, 10);

    }




    //leds[i] = CRGBW(10, 10, 10,0);

    //      if (i%4==0){ // these LEDs are RGB(W) in CRGB
    //        leds[i] = CRGBW(10, 10, 10,10);
    //
    //      } else if (i%4==1){ // these LEDS are GWR(B)
    //        //leds[i] = CRGB(10, 0, 10);
    //
    //        }
    //        else if (i%4==3){ // these LEDS are BRW(G) (don't ask me why)
    //       // leds[i] = CRGB(10, 10, 0);
    //        }


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
