#include <Wire.h>
#include <SPI.h>
#include <Adafruit_CAP1188.h>

// Reset Pin is used for I2C or SPI
#define CAP1188_RESET  9

// CS pin is used for software or hardware SPI
#define CAP1188_CS  10

// These are defined for software SPI, for hardware SPI, check your
// board's SPI pins in the Arduino documentation
#define CAP1188_MOSI  11
#define CAP1188_MISO  12
#define CAP1188_CLK  13

// For I2C, connect SDA to your Arduino's SDA pin, SCL to SCL pin
// On UNO/Duemilanove/etc, SDA == Analog 4, SCL == Analog 5
// On Leonardo/Micro, SDA == Digital 2, SCL == Digital 3
// On Mega/ADK/Due, SDA == Digital 20, SCL == Digital 21

// Use I2C, no reset pin!
Adafruit_CAP1188 cap1 = Adafruit_CAP1188();

//uint8_t channels[24];
uint8_t channels[8];


// Or...Use I2C, with reset pin
//Adafruit_CAP1188 cap = Adafruit_CAP1188(CAP1188_RESET);

// Or... Hardware SPI, CS pin & reset pin
// Adafruit_CAP1188 cap = Adafruit_CAP1188(CAP1188_CS, CAP1188_RESET);

// Or.. Software SPI: clock, miso, mosi, cs, reset
//Adafruit_CAP1188 cap = Adafruit_CAP1188(CAP1188_CLK, CAP1188_MISO, CAP1188_MOSI, CAP1188_CS, CAP1188_RESET);


//For Xbee
// We'll use SoftwareSerial to communicate with the XBee:
#include <SoftwareSerial.h>

//For Atmega328P's (like arduino uno)
// XBee's DOUT (TX) is connected to pin 2 (Arduino's Software RX)
// XBee's DIN (RX) is connected to pin 3 (Arduino's Software TX)
SoftwareSerial XBee(2, 3); // RX, TX

int sensorAValues[8] = {0, 0, 0, 0, 0, 0, 0, 0};

void setup() {
  Serial.begin(9600);
  XBee.begin(9600);
  //   while (!Serial) {
  //    ; // wait for serial port to connect. Needed for native USB port only
  //  }

  establishContact();
  //Serial.println("here");

  
  // Initialize the sensor, if using i2c you can pass in the i2c addres


  if (!cap1.begin(0x29)) {
    while (1);
  }



  //for sensor 1 at 0x29
  for (uint8_t i = 0; i < 8; i++) {
    int chaN = i + 1;
    int address = 0xF + (0x10 * chaN);
    channels[i] = cap1.readRegister( address ) & 0x0f;
    cap1.writeRegister(address, channels[i] | 0xBF);
  }
  cap1.writeRegister(0x3f, channels[2] | 0xAF);
  cap1.writeRegister(0x7f, channels[6] | 0x2F);

}




void loop() {
  //Serial.println("here");
  //XBee.print("hello");
  
  uint8_t touched1 = cap1.touched();


  if (touched1 == 0) {
    for (uint8_t i = 0; i < 8; i++) {
      sensorAValues[i] = 0;
      
      XBee.print(sensorAValues[i]);
      XBee.print(",");
    }
    XBee.print("0");  //one digit ID - 0 for small box, 1 for big box
    XBee.println();
    delay(10);
    return;
  }


  for (uint8_t i = 0; i < 8; i++) {
    if (touched1 & (1 << i)) {
      sensorAValues[i] = 1;
    } else {
      sensorAValues[i] = 0;
    }

  }


  for (uint8_t i = 0; i < 8; i++) {
    XBee.print(sensorAValues[i]);
    XBee.print(",");
   

    Serial.print(sensorAValues[i]);
    Serial.print(",");
   
  }

  XBee.print("0");  //one digit ID - 0 for small box, 1 for big box
  XBee.println();

  Serial.print("1");
  Serial.println();
  delay(10);
}

void establishContact() {
  //while (Serial.available() <= 0) {
  XBee.println("0,0,0,0,0,0,0,0,0");   // send an initial string
  delay(300);
  //}
}
