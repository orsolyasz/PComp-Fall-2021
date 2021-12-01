
int humanSwitchPin = A3;
int humanSwitchVal = 0;
int switchResponsePin = 9;
int humanSwitchState = 0;

int humanSwitchPin2 = A2;
int humanSwitchVal2 = 0;
int switchResponsePin2 = 9;
int humanSwitchState2 = 0;

int pressurePin = A1;
int pressureVal = 0;

int vibration1 = 0;
int vibration2 = 0;

int lightSensVal = 0;
int lightSensPin = A0;
int brightness = 64;

int red1 = 50;
int green1 = 5;
int blue1 = 0;
int white1 = 20;

int red2 = 20;
int green2 = 50;
int blue2 = 0;
int white2 = 10;

int red3 = 30;
int green3 = 20;
int blue3 = 10;
int white3 = 10;

int r = 0;
int g = 0;
int b = 0;
int w = 0;

int rPrev = 0;
int gPrev = 0;
int bPrev = 0;
int wPrev = 0;

int rTarget = 0;
int gTarget = 0;
int bTarget = 0;
int wTarget = 0;

int sensMax = 60;
int brightMin = 30;
int brightMax = 200;

char inData[100];
int dataLength = 0;
String pressureReadings = "0000,0000,0000,";


//for rgbLED control:

#include <FastLED.h>
//blspecial addition to the FastLED library to work with
//an RGBW strip from https://www.partsnotincluded.com/fastled-rgbw-neopixels-sk6812/
#include "FastLED_RGBW.h";

#define LED_PIN     5
#define NUM_LEDS    30
#define BRIGHTNESS  64
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB
#define UPDATES_PER_SECOND 100

CRGBW leds[NUM_LEDS];
CRGB *ledsRGB = (CRGB *) &leds[0];


//CAP1188 sensor setup
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_CAP1188.h>

// Reset Pin is used for I2C or SPI
// For I2C, connect SDA to your Arduino's SDA pin, SCL to SCL pin
#define CAP1188_RESET
// CS pin is used for software or hardware SPI
#define CAP1188_CS  10
// These are defined for software SPI
#define CAP1188_MOSI  11
#define CAP1188_MISO  12
#define CAP1188_CLK  13

//var for the cap sensor itself:
Adafruit_CAP1188 cap1 = Adafruit_CAP1188();

//var[]s for capacitive sensor channels:
uint8_t channels[8];
int sensorAValues[8] = {0, 0, 0, 0, 0, 0, 0, 0};



//Communication Setup

//Using SoftwareSerial to communicate with the XBee.
// I have an XBee shield on my Arduino but otherwise for Atmega328P's (like Arduino Uno)
// XBee's DOUT (TX) is connected to pin 2 (Arduino's Software RX)
// XBee's DIN (RX) is connected to pin 3 (Arduino's Software TX)

//Also using SoftwareSerial to communicate with the second Arduino,
//which was added to have more analoge pins.
//Pin 7 on this board is connected to pin 6 on the other board
//Pin 6 on this board is connected to pin 7 on the other board
//BUT the other board also runs a sketch where the pins are listed in the same order, so
//"SoftwareSerial mainBoard(7,6) is the line on that board.

#include <SoftwareSerial.h>
SoftwareSerial XBee(2, 3); // RX, TX
SoftwareSerial secondBoard(7, 6);


void setup() {
  delay( 3000 ); // power-up safety delay

  //begin communication
  Serial.begin(9600);
  XBee.begin(9600);
  establishContact();
  secondBoard.begin(9600);

  // Initialize the cap sensor - using i2c we pass in the i2c addres
  if (!cap1.begin(0x29)) {
    while (1);
  }

  for (uint8_t i = 0; i < 8; i++) {
    int chaN = i + 1;
    int address = 0xF + (0x10 * chaN);
    channels[i] = cap1.readRegister( address ) & 0x0f;
    cap1.writeRegister(address, channels[i] | 0xBF);
  }

  cap1.writeRegister(0x3f, channels[2] | 0xAF);
  cap1.writeRegister(0x7f, channels[6] | 0x2F);


  //Initialize the LED strip
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
  rPrev = red1;
  bPrev = blue1;
  gPrev = green1;
  wPrev = white1;

}




void loop() {

  //get pressure readings from the second board
  delay(2);
  secondBoard.listen();
  delay(2);

  if (secondBoard.available()) {
    //Serial.println("data incoming");
    if (secondBoard.read() == '$') {
      for (dataLength = 0; dataLength < 100; dataLength++) {
        delay(2);
        inData[dataLength] = secondBoard.read();
        if (inData[dataLength] == '#') {
          inData[dataLength] = ',';
          break;
        }
      }
    }
  }

  pressureReadings = "";
  for (int i = 0; i < 15; i++) {
    pressureReadings = pressureReadings + inData[i];
  }

  delay(1);


  //take capacitive sensor readings and store which
  //channels are touch/not touched

  uint8_t touched1 = cap1.touched();

  // if the sensor is not touched
  //  if (touched1 == 0) {
  //    for (uint8_t i = 0; i < 8; i++) {
  //      sensorAValues[i] = 0;
  //      XBee.print(sensorAValues[i]);
  //      XBee.print(",");
  //    }
  //    XBee.print("0");  //one digit ID - 0 for small box, 1 for big box
  //    XBee.println();
  //    delay(10);
  //    return;
  //  }


  for (uint8_t i = 0; i < 8; i++) {
    if (touched1 & (1 << i)) {
      sensorAValues[i] = 1;
      if (i == 0) {
        vibration1 = 200;
      }
      else if (i == 3) {
        vibration2 = 200;
      }
    } else {
      sensorAValues[i] = 0;
      if (i == 0) {
        vibration1 = 0;
      }
      else if (i == 3) {
        vibration2 = 0;
      }
    }
  }

  analogWrite(11, vibration1);
  analogWrite(10, vibration2);



  //read all other sensor values
  pressureVal = analogRead(pressurePin);
  //Serial.println(pressureVal);

  humanSwitchVal = analogRead(humanSwitchPin);
  //Serial.print(" SW 1: ");
  //Serial.println(humanSwitchVal);

  humanSwitchVal2 = analogRead(humanSwitchPin2);
  //  Serial.print(" SW 2: ");
  //  Serial.println(humanSwitchVal2);

  lightSensVal = analogRead(lightSensPin);



  // set LED strip colors based on which plant/"mode" we are in

  // if (humanSwitchVal2 < 940) {
  if (humanSwitchVal2 - humanSwitchVal > 800 || humanSwitchVal - humanSwitchVal2 > 800) {
    humanSwitchState = humanSwitchState + (255 - humanSwitchState) * 0.05;
    rTarget = red2;
    gTarget = green2;
    bTarget = blue2;
    wTarget = white2;
  }
  //else if (humanSwitchVal < 940) {
  else if (humanSwitchVal < 850) {
    humanSwitchState = humanSwitchState + (255 - humanSwitchState) * 0.05;
    rTarget = red1;
    gTarget = green1;
    bTarget = blue1;
    wTarget = white1;
  }
  else {
    humanSwitchState = humanSwitchState - (humanSwitchState - 0) * 0.05;
    rTarget = red3;
    gTarget = green3;
    bTarget = blue3;
    wTarget = white3;
  }


  //animate colors if there is a change of state
  updateLEDs();


  //send on/off signal to control LED so we can see if the plant switches are working
  analogWrite(switchResponsePin, humanSwitchState);
  //Serial.println(humanSwitchState);



  Serial.println(pressureReadings);

  //send XBee all sensor readings
  sendInfo();
  delay(1);
  secondBoard.listen();

  //  XBee.print('$');  //one digit ID - to mark incoming SENSOR data and distinguish it from the "noise" that might be sent because of values being written through FastLED
  //  XBee.print(',');
  //  //send cap sensor values as digits 2-9
  //  for (uint8_t i = 0; i < 8; i++) {
  //    XBee.print(sensorAValues[i]);
  //    XBee.print(",");
  //    //    Serial.print(sensorAValues[i]);
  //    //    Serial.print(",");
  //
  //  }
  //
  //  XBee.print(fourDigitString(lightSensVal));
  //  XBee.print(",");
  //  XBee.print(fourDigitString(humanSwitchVal));
  //  XBee.print(",");
  //  XBee.print(fourDigitString(humanSwitchVal2));
  //  XBee.print(",");
  //  XBee.print(pressureVal);
  //  XBee.println();
  //  //  Serial.print("1");
  //  //  Serial.println();
  delay(4);
}



void establishContact() {
  //while (Serial.available() <= 0) {
  XBee.println("0,0,0,0,0,0,0,0,0");   // send an initial string
  delay(300);
  //}
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

void updateLEDs() {


  //if (r != rTarget || g != gTarget || b != bTarget || w != wTarget) {

  updateRed();
  updateBlue();
  updateGreen();
  updateWhite();

  //smoothing out the LED strip brightness value change by'
  //always only moving by 4% of the brightness difference
  brightness = brightness + (map(lightSensVal, 0, sensMax, brightMin, brightMax) - brightness) * 0.04;

  //send LED strip values

  FillColors();
  FastLED.setBrightness( brightness );
  FastLED.show();
  FastLED.delay(1000 / UPDATES_PER_SECOND);

  //}
}

void updateRed() {
  if ((r - rTarget < 1) && (r - rTarget > -1)) {
    r = rTarget;
  }
  else {
    r = round((r - (r - rTarget) * 0.05) + 0);
    if (r == rPrev) {
      if (r < rTarget) {
        r += 1;
      }
      else {
        r -= 1;
      }
    }
  }
  rPrev = r;
}


void updateGreen() {
  if ((g - gTarget > -1) && (g - gTarget < 1)) {
    g = gTarget;
  }
  else {
    g = round((g - (g - gTarget) * 0.05) + 0);
    if (g == gPrev) {
      if (g < gTarget) {
        g += 1;
      }
      else {
        g -= 1;
      }
    }
  }
  gPrev = g;
}

void updateBlue() {
  if ((b - bTarget > -1) && (b - bTarget < 1)) {
    b = bTarget;
  }
  else {
    b = round((b - (b - bTarget) * 0.05) + 0);
    if (b == bPrev) {
      if (b < bTarget) {
        b += 1;
      }
      else {
        b -= 1;
      }
    }

  }
  bPrev = b;
}

void updateWhite() {
  if ((w - wTarget > -1) && (w - wTarget < 1)) {
    w = wTarget;
  }
  else {
    w = round((w - (w - wTarget) * 0.05) + 0);
    if (w == wPrev) {
      if (w < wTarget) {
        w += 1;
      }
      else {
        w -= 1;
      }
    }
  }
  wPrev = w;

}

String fourDigitString(int val) {
  String stringValue = "0000";

  if (val < 10) {
    stringValue = "000" + String(val);
  }
  else if (val > 9 && val < 100) {
    stringValue = "00" + String(val);
  }
  else if (val > 99 && val < 1000) {
    stringValue = "0" + String(val);
  }
  else {
    stringValue = String(val);
  }

  return stringValue;
}

void sendInfo() {

  delay(3);
  XBee.listen();
  delay(1);

  XBee.print('$');  //one digit ID - to mark incoming SENSOR data and distinguish it from the "noise" that might be sent because of values being written through FastLED
  XBee.print(',');
  //send cap sensor values as digits 2-9
  for (uint8_t i = 0; i < 8; i++) {
    XBee.print(sensorAValues[i]);
    XBee.print(",");
    //    Serial.print(sensorAValues[i]);
    //    Serial.print(",");

  }

  //send all other values after, separated by commas
  XBee.print(fourDigitString(lightSensVal));
  XBee.print(",");
  XBee.print(fourDigitString(humanSwitchVal));
  XBee.print(",");
  XBee.print(fourDigitString(humanSwitchVal2));
  XBee.print(",");
  XBee.print(pressureReadings);
  XBee.println();
  delay(1);
}
