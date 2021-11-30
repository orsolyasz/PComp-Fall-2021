# Week 4

*Lab 1 was part of the final project so it is included in my final project documentation instead**

## Lab 2 - Hook up a servo

Here are screenshots of my [Tinkercad](https://www.tinkercad.com/things/lVTFG19bJag-super-elzing/editel?sharecode=qkUXhapHf6PbOWHWwMj3fkh_NIhcWmrRoL4stFDihtE) servo setup, as well as the two bits of code I tested. One Arduino is making the motor switch between 90 and 180 degrees every 3 seconds. The other Arduino is making a motor go slowly/gradually from 0 to 180 degrees (in steps of 5 degrees every 300milliseconds), going back to 0 to restart once it reaches 180.

![Tinkercad screenshot of two servos connected to two different Arduinos](https://github.com/orsolyasz/PComp-Fall-2021/blob/main/Week%2004/Servos.png)

Arduino 1 code, which makes the servo behave as documented in this [video](https://drive.google.com/file/d/1my3vBpCigYfZeLg-Id2Mng6RWSc3IxhI/view?usp=sharing).
```
#include <Servo.h> 


int servoPos=90;
byte servoPin = 3;
Servo myServo;

void setup()
{
  Serial.begin(9600);
  myServo.attach(servoPin);
}

void loop()
{
  myServo.write(servoPos);
  Serial.println(servoPos);
  delay(3000);
  
  servoPos=180;
  myServo.write(servoPos);
  Serial.println(servoPos);
  delay(3000);
  
  servoPos=90;
  
}
```

Arduino 2, which makes the servo move a lot like a water sprinkler, as seen [here](https://drive.google.com/file/d/1mzndaug5WSl7mq1uhtmJoZtS5Bkj_ykG/view?usp=sharing)
```
#include <Servo.h> 


int servoPos=0; 
byte servoPin= 9;
Servo myServo;

void setup()
{
  Serial.begin(9600);
  myServo.attach(servoPin);
}

void loop()
{
  myServo.write(servoPos);
  Serial.println(servoPos);
  delay(100);
  
  if(servoPos<180){
    servoPos+=5;
  } else {
    delay(500);
    servoPos=0;
    myServo.write(servoPos);
    delay(1000);
  } 
}
```


## Lab 3 - Hook up a motor

For this lab, to make a servo move a pinwheel, I followed the wiring diagram from the Arduino handbook (below) and came up with this setup:

![Photo of a servo and a push button connected to an Arduino, next to the wiring diagram of the same](https://github.com/orsolyasz/PComp-Fall-2021/blob/main/Week%2004/Motor%20Wiring.png)

I then created a small 3-color flower pinwheel, secured together in the middle with an LED (this isn't powered, but it was the closest thing to a pin I had and it looked cute). I actually happened to have the exact wood base pieces created for this exercise of the handbook (it had been passed on to me by a friend). This base was designed to neatly connect to the top of the motor, so I used this as the base of my flower. 

![Images of the flower pinwheel and the servo being assembled](https://github.com/orsolyasz/PComp-Fall-2021/blob/main/Week%2004/Pinwheel%20Build.png)

Then, using the below code, also from the handbook, I made the pinwheel move whenever my pushbutton is pressed. You can see this in my [video documentation](https://drive.google.com/file/d/1n1iNLTKGMXDoQCItReIWpcSTv_09epzK/view?usp=sharing).


```
const int switchPin = 2;
const int motorPin = 9;
int switchState = 0; 

void setup() {
 Serial.begin(9600);
 pinMode(motorPin, OUTPUT);
 pinMode(switchPin, INPUT);
}

void loop(){
 switchState = digitalRead(switchPin);
 Serial.println(switchState);
 if (switchState == HIGH) {
 digitalWrite(motorPin, HIGH);
 }
 else {
 digitalWrite(motorPin, LOW);
 }
}
```

## Lab 4 - Hook up an MPR121 

As I was not yet enrolled or on campus for this lab, I did not have an MPR121 to work with. However, I luckily had some CAP1188 sensors, which are Adafruit's 8 channel capacitive touch sensors, so I went with those instead. Other than having fewer channels, the CAP1188 sensors seem to just require a bit more wiring in that it does not have STEMMA QT connectors, but otherwise are definitely similar enough.

I connected my CAP1188 using the wiring guide on the [Adafruit website](https://learn.adafruit.com/adafruit-cap1188-breakout/wiring). Tnere also is a dedicated CAP1188 library for Arduino, which is what I am using to get sensor readings.

For my circuit, I decided to use an RGB LED diode to get some experience with it. I programmed my Arduino to use 3 touch channels as on/off switches for the 3 color channels (r,g,b) of the LED. I'm using an array to store the 8 channel states (touched/not touched), and then using the state of channel 1, 4, and 8 to determine my output to pins 9, 10 and 11.

Photos of my circuit and my code follow below. The working circuit is demonstrated in my [video](https://drive.google.com/file/d/1nR4eNGDj_6W24J2qIMxJPvow2JqSw4Ca/view?usp=sharing) documentation.

![Photo of a CAP1188 sensor and an RGB LED diode connected to an Arduino via a breadboard](https://github.com/orsolyasz/PComp-Fall-2021/blob/main/Week%2004/Cap1188-with-rgbLED.png)


```
byte rPin = 11;
byte gPin = 10;
byte bPin = 9;

int sensorAValues[8] = {0, 0, 0, 0, 0, 0, 0, 0};

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_CAP1188.h>

// Reset Pin is used for I2C or SPI
#define CAP1188_RESET  9

// CS pin is used for software or hardware SPI
#define CAP1188_CS  10

// These are defined for software SPI, for hardware SPI
#define CAP1188_MOSI  11
#define CAP1188_MISO  12
#define CAP1188_CLK  13

// For I2C, connect SDA to your Arduino's SDA pin, SCL to SCL pin
// Use I2C, no reset pin!
Adafruit_CAP1188 cap = Adafruit_CAP1188();


void setup() {
  Serial.begin(9600);
  Serial.println("CAP1188 test!");

  pinMode(rPin, OUTPUT);
  pinMode(gPin, OUTPUT);
  pinMode(bPin, OUTPUT);



  // Initialize the sensor, if using i2c you can pass in the i2c address
  // if (!cap.begin(0x28)) {
  if (!cap.begin()) {
    Serial.println("CAP1188 not found");
    while (1);
  }
  Serial.println("CAP1188 found!");
}

void loop() {

  analogWrite(rPin, sensorAValues[0]*255);
  Serial.println(sensorAValues[0]);
  analogWrite(gPin, sensorAValues[3]*255);
  analogWrite(bPin, sensorAValues[7]*255);


  uint8_t touched = cap.touched();

  if (touched == 0) {
    // No touch detected
    sensorAValues[0] = 0;
    sensorAValues[3] = 0;
    sensorAValues[7] = 0;
    return;
  }

  for (uint8_t i = 0; i < 8; i++) {
    if (touched & (1 << i)) {
      sensorAValues[i] = 1;
    } 
    else {
      sensorAValues[i] = 0;
    }
  }

  delay(50);
  
}
```

## Lab 5 - The Capsense library 

For this lab, I followed the linked CapSens [guide](https://playground.arduino.cc/Main/CapacitiveSensor/) to set up my own Arduino to be able to use two connected pins as a capacitive sensor. 

When I first read the description, I was very excited to see that the readings we would get from such a setup are actually much more detailed than an on/off switch -- hoping that maybe it could be used to detect different grips/levels of touch, or at least distinguish between no touch, touch, and just a person's presence nearby. I do think this 3-level detection is definitely possible -based on how my actual physical setup worked- yet I was largely disappointed to find that I could not really use the incoming data to create gradual/smooth changes and that full contact touch often made my system really, really slowed down. **(Although my disappointment is just due to my expectations being not super realistic really, if I think about it.)**

While I was creating my setup, I found it easier to actually create 3 separate pin-pairs (4-2, 6-8, 12-13, with the "sensors" being 2, 8, and 13), instead of connecting 3 sensor pins all to the same pin (pin4 in the original demo example). I just found that connecting 3 sensors all to pin four caused interference/noise - touching one sensor would also affect others quite a bit.

So in the end, this is the setup I came up with:

![Photo of arduino with resistors between some pin pairs and an RGB LED connected](https://github.com/orsolyasz/PComp-Fall-2021/blob/main/Week%2004/CapSense%20Setup.png)

The code I used for my test is below, and it produced similar results regardless of the materials I used as my "sensor" surface. I experimented with [kitchen tools](https://drive.google.com/file/d/1ntJDh8ZmxNDUJ8OsjprreBIGUgJGuOFS/view?usp=sharing) and then also just plain [copper tape](https://drive.google.com/file/d/1nvWGkCKLWdwO4fr_gQQf-cI_4jwVCcSf/view?usp=sharing). 

As you can see in the videos, touching the sensors always slowed the Arduino down so much that the LED color changes would be implemented in a jumpy way instead of with animating between values smoothly. I am sure though that this could be worked out by changing the resistors and attached materials, and maybe by experimenting with some capacitors or some foil to ground, as suggested in the library, to make the sensors more stable.

I will be excited to experiment with this library further later, as even just knowing if a person is touching, nearby, or far from the sensor could help create a lot of interesting interactions. It would be fascinating to see if I could use my knowledge that a person is *near* an installation element, for example, to try to invite them to touch it. Would, say, a glow or a soft sound brought about by somone's walking past a piece of wood give them a hint of the affordance of interactivty? Would they feel more invited to touch something that otherwise looks ordinary/"non-technological" (not a well known interface like a button or screen or knob) if the object reacted to their presence? 

I'm particularly interested in this as I have already had some issues with letting people know they are allowed to touch things in an open installation setup without explicitly telling them to do so (which really is a boring way to communicate an affordance in my opinion.

The code for this lab is below. To control the RGB LED with the sensor values, I merged my code from above with the library's demo to get this:

```
byte rPin = 11;
byte gPin = 10;
byte bPin = 9;

int r = 0;
int g = 0;
int b = 0;

int rTarg = 0;
int gTarg = 0;
int bTarg = 0;

int minIn = 2000;
int maxIn = 220000;

#include <CapacitiveSensor.h>

/*
   CapitiveSense Library Demo Sketch
   Paul Badger 2008
   Uses a high value resistor e.g. 10 megohm between send pin and receive pin
   Resistor effects sensitivity, experiment with values, 50 kilohm - 50 megohm. Larger resistor values yield larger sensor values.
   Receive pin is the sensor pin - try different amounts of foil/metal on this pin
   Best results are obtained if sensor foil and wire is covered with an insulator such as paper or plastic sheet
*/


CapacitiveSensor   cs_4_2 = CapacitiveSensor(4, 2);       // 10 megohm resistor between pins 4 & 2, pin 2 is sensor pin, add wire, foil
CapacitiveSensor   cs_4_5 = CapacitiveSensor(12, 13);       // 10 megohm resistor between pins 12 & 7, pin 7 is sensor pin, add wire, foil
CapacitiveSensor   cs_4_8 = CapacitiveSensor(6, 8);       // 10 megohm resistor between pins 9 & 8, pin 8 is sensor pin, add wire, foil

void setup()
{

  //   cs_4_2.set_CS_AutocaL_Millis(0xFFFFFFFF);     // turn off autocalibrate on channel 1 - just as an example
  Serial.begin(9600);
  pinMode(rPin, OUTPUT);
  pinMode(gPin, OUTPUT);
  pinMode(bPin, OUTPUT);
}

void loop()
{

  analogWrite(rPin, r);
  analogWrite(gPin, g);
  analogWrite(bPin, b);
  Serial.println(b);


  long start = millis();
  long total1 =  cs_4_2.capacitiveSensor(30);

  if (total1 > maxIn) {
    total1 = maxIn;
  } else if (total1 < minIn) {
    total1 = minIn;
  }
  rTarg = int(map(total1, minIn, maxIn, 0, 255));

  long total2 =  cs_4_5.capacitiveSensor(30);
  if (total2 > maxIn) {
    total2 = maxIn;
  } else if (total2 < minIn) {
    total2 = minIn;
  }
  gTarg = int(map(total2, minIn, maxIn, 0, 255));

  long total3 =  cs_4_8.capacitiveSensor(30);
  if (total3 > maxIn) {
    total1 = maxIn;
  } else if (total1 < minIn) {
    total3 = minIn;
  }
  bTarg = int(map(total3, minIn, maxIn, 0, 255));

  r = r - (r - rTarg) * 0.5;
  if (r > 255) {
    r = 255;
  } else if (r < 0) {
    r = 0;
  }
  g = g - (g - gTarg) * 0.5;
  if (g > 255) {
    g = 255;
  } else if (g < 0) {
    g = 0;
  }
  b = b - (b - bTarg) * 0.5;
  if (b > 255) {
    b = 255;
  } else if (b < 0) {
    b = 0;
  }

  Serial.print(millis() - start);        // check on performance in milliseconds
  Serial.print("\t");                    // tab character for debug window spacing

  Serial.print(total1);                  // print sensor output 1
  Serial.print("\t");
  Serial.print(total2);                  // print sensor output 2
  Serial.print("\t");
  Serial.println(total3);                // print sensor output 3

  delay(10);                             // arbitrary delay to limit data to serial port
}
```

