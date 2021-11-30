# Week 2

## Lab 00 - Leds in Serial and Parallel

### How many LEDs can you hook up with a 220Ω resistor in serial?


In a serial connection, resistance of connected elements adds up:

R(total) = R1 + R2 + R3 + ... + Rn


Since all our resistors are the same: 

R1=R2=R3=...=Rn

**R(total) = n×R**

Assuming that we are using a 5V power source, the current in our overall circuit is:

I = V/nR

**I= 5/(220×n)**


This current is the same across all parts of the circuit, since it is serial.
That is, 5/(220×n) is the current through any LED&resistor unit.
The LEDs stop working when this current becomes too low. When does that happen?

At 1 LED with 1 220Ω resistor: I=5/(220)=0.02273A = 22.73mA

At 2 LEDs with 2 220Ω resistors: I=5/(2×220)=0.01136A= 11.36mA

At 3 LEDs with 3 220Ω resistors: I=5/(3×220)=0.007575A= 7.58mA

At 4 LEDs with 4 220Ω resistors: I=5/(4×220)=0.005682A= 5.68mA

From what I gather, the normal operating range for common LEDs is 10-30mA. ([Source](https://www.allaboutcircuits.com/tools/led-resistor-calculator/))
This makes it safe to assume that the LEDs would already start to get dimmer already at 3 serially connected, and would likely not work at 4.

From testing this setup in a physical circuit and a Tinkercad setup as well, this seems to be the case.
At three LEDs connected, the LEDs begin to dim, at 4, they don't light up at all.

![Tinkercad image showing 3 dim LEDs connected in serial](https://github.com/orsolyasz/PComp-Fall-2021/blob/main/Week%2002/Serial%20LED%20Test.png)
![Photo of 3 LEDs serially connected in a breadboard, they are on but two of them extremely dim](https://github.com/orsolyasz/PComp-Fall-2021/blob/main/Week%2002/3LED-Serial.jpg)
![Photo of 4 LEDs serially connected in a breadboard, they are not on at all](https://github.com/orsolyasz/PComp-Fall-2021/blob/main/Week%2002/4LED-Serial.jpg)


### How many LEDs can you hook up with a 220Ω resistor in parallel?

In a parallel circuit, the resistance of different components does not simply add up. Rather, we have to use the formula below:

1/R(total) = 1/R1 + 1/R2 + 1/R3 + ... + 1/Rn

Again, as all our resistors are the same, this becomes:

1/R(total) = n×(1/R)
R/R(total) = n
R=n×R(total)
R(total) = R/n
R(total) = 220/n

Assuming that we are using 5V, since we are in a parallel circuit, we know that the the voltage is 5V everywhere.

V = R×I
5 = 220/n × I

Meaning our current is:
I = 5/(220/n)

Rearranging to solve for n

I×(220/n)=5
220/n=5/I
220=(5/I)×n
**n=220/(5/I)**

So how many LEDs can we connect before we require more current than our power source could provide?

If our LEDS are powered by an Arduino powered through a computer, it is likely we would get about 500mA current at most.
This would mean we can have:

n=220/(5/0.5)=22 LEDs hooked up in parallel.

Obviously, if our LEDs are powered through a source that provides higher current, we could have more LEDs.

*(Disclaimer: Confusingly, in testing this in [Tinkercad](https://www.tinkercad.com/things/10RUG4jhJwq-led-voltage-drop-test/editel?sharecode=tCFQxqizOxRyy1MuqHPETv5tSEmU-f7ZWBSBlc1BSho) I am able to line up about 35-36 LEDs to a 5V 500mA power supply without an issue. I am not sure why that is or where my calculations above would be off, but maybe it is only the simulation that is off as the power supply element is a bit finicky to use. I did not have 20+ LEDs to test this with physically, but I will try at some point.)*

![Tinkercad image showing 35 LEDs connected in parallel](https://github.com/orsolyasz/PComp-Fall-2021/blob/main/Week%2002/Parallel%20LED%20Test.png)


## Lab 01 - Serial Data Story


For this lab, I created a mini (un)helpful machine. Code and [Tinkercad](https://www.tinkercad.com/things/k7yTJEfIG5u-serial-story/editel?sharecode=UmDBjt008TeCs5V7xzIVgiV9OaORmBbtavxoB2J3KDo) screenshots of the mini story's two branches are below.

```
bool startUp = true;
bool restart = false;

String response = "";

void setup() {
  // put your setup code here, to run once:
   Serial.begin(9600); 
}

void loop() {

  if(startUp)
  {
    delay(200);
    Serial.println("Hello there! Do you need any help today?"); 
    startUp = false;
  }
  
  if(restart)
  {
    delay(200);
    Serial.println("Do you need any help today?"); 
    restart = false;
  }
  
  
 if(Serial.available()) 
 {
   response = Serial.readString();
   Serial.println(response);
   if(response=="no")
   {
    think();
    Serial.println("Well good for you then.");
    delay(1000);
    think();
    delay(2500);
    Serial.println("Goodbye.");
   }
   else if(response=="yes")
   {
    think();
    Serial.println("Oh honey");
    delay(1200);
    Serial.println("Don't we all?");
    delay(1200);
    Serial.println("You should go get some help then.");
    delay(2500);
    Serial.println("Goodbye.");
   } 
   else
   {
    think();
    Serial.println("I'm a simple machine, please respond by typing 'yes' or 'no'.");
    restart=true;
    delay(1200);
   }
 }
}

void think() 
{ 
  delay(500);
  Serial.print(".");
  delay(500);
  Serial.print(".");
  delay(500);
  Serial.println(".");
  delay(500);
}
```

![Screenshot of bot chat responses if the responder needs help](https://github.com/orsolyasz/PComp-Fall-2021/blob/main/Week%2002/UnhelpfulMachine-Yes.png)
![Screenshot of bot chat responses if the responder does not need help](https://github.com/orsolyasz/PComp-Fall-2021/blob/main/Week%2002/UnhelpfulMachine-No.png)



## Lab 02 - Potentiometers (Knobs)

Here is my code for a Potentiometer to control the brightness of an LED. I was also curious to see how much a smoothing equation would affect the knob's impact on the light, so I experimented a bit with that, but just ended up keeping it commented out below as I did not see a significant difference (which seems to make sense with a knob).

```
byte ledPin =11;
byte potPin = A0;

int potValue=0;
int ledValue=0;
int ledTarget=0;

void setup()
{
  delay(400);
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
}

void loop()
{
  potValue= analogRead(potPin);
  ledValue= map(potValue, 0, 1023, 0, 255);
  //ledTarget=potValue;
  
  //ledValue=ledValue-(ledValue-ledTarget)*0.05;
  
  //Serial.print(potValue);
  //Serial.print(",");
  //Serial.println(ledValue);

  analogWrite(ledPin, ledValue);
}
```

Here is my wiring diagram from [Tinkercad](https://www.tinkercad.com/things/gIJUbbWlhq4-pot-ldr-tilt-led-control/editel?sharecode=GUPORPcPk-2q8_CoKlePIML9vyNZAyp_25dJrqXx6iQ) and my physical setup: 

![Tinkercad screenshot of a potentiometer and an LED connected to an Arduino Uno via a breadboard](https://github.com/orsolyasz/PComp-Fall-2021/blob/main/Week%2002/Potentiometer-with-LED.png)
![Image of an LED and a potentiometer connected to an Arduino Uno via a breadboard](https://github.com/orsolyasz/PComp-Fall-2021/blob/main/Week%2002/LED-Potentiometer.jpg)

## Lab 03 - Light Dependent Resistors

Here is my code for an LDR to control the brightness of an LED. It is basically the same as above, except the numbers for the mapping range are different, as the range of values coming from the LDR is much smaller and with lower values. Given the smaller range and different mechanism, the incoming data is also not as smooth on its own as it was for the pot, so here I am using smoothing to make the LED change without jumpiness.

```
byte ledPin =11;
byte ldrPin = A0;

int ldrValue=0;
int ledValue=0;
int ledTarget=0;

void setup()
{
  delay(400);
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
}

void loop()
{
  ldrValue= analogRead(ldrPin);
  ledTarget=map(ldrValue, 1, 39, 0, 255);
  
  ledValue=ledValue-(ledValue-ledTarget)*0.05;
  
  Serial.println(ldrValue);
  //Serial.print(",");
  //Serial.println(ledValue);

  analogWrite(ledPin, ledValue);
}
```

Here is my [Tinkercad](https://www.tinkercad.com/things/gIJUbbWlhq4-pot-ldr-tilt-led-control/editel?sharecode=GUPORPcPk-2q8_CoKlePIML9vyNZAyp_25dJrqXx6iQ) wiring diagram and my physical setup:

![Tinkercad screenshot of an LDR and an LED connected to an Arduino Uno via a breadboard](https://github.com/orsolyasz/PComp-Fall-2021/blob/main/Week%2002/LDR-LED-Tinker.png)
![Image of an LED and an LDR connected to an Arduino Uno via a breadboard the LDR is not covered, the LED is on](https://github.com/orsolyasz/PComp-Fall-2021/blob/main/Week%2002/LDR-LED-on.jpg)
![Image of an LED and an LDR connected to an Arduino Uno via a breadboard the LDR is covered, the LED is not on](https://github.com/orsolyasz/PComp-Fall-2021/blob/main/Week%2002/LDR-LED-off.jpg)


## Lab 04 - Playing with Common Sensors

For this part of the lab, I decided to look at a [tilt switch](https://learn.adafruit.com/tilt-sensor/using-a-tilt-sensor). I tried both the simple battery and the Arduino setup in tinkercad. I also tried the same in a physical setup but my tilt switch fell apart when I first plugged it in :( The code I used was taken directly from the link above.

Here is my wiring diagram from [Tinkercad](https://www.tinkercad.com/things/gIJUbbWlhq4-pot-ldr-tilt-led-control/editel?sharecode=GUPORPcPk-2q8_CoKlePIML9vyNZAyp_25dJrqXx6iQ):

![Tinkercad screenshot of a tilt switch connected directly to an LED and 2 AA batteries, and another one connected to an Arduino to control a LED on the same circuit](https://github.com/orsolyasz/PComp-Fall-2021/blob/main/Week%2002/Tilt-Switch-Tinker.png)


## Lab 05 

I have a confession to make. I have killed.

I have killed so many house plants I can't even remember! I am usually pretty good at being caring and attentive, and I even (mostly) remember to water them regularly-- and yet, many of them, sadly, are not with us anymore.

That's why I'm happy to introduce you to the Happy Plant monitoring pot! 

![Handdrawn sketch of a potted plant. The pot has a smiley face of LEDs and a temp and a light sensor built in](https://github.com/orsolyasz/PComp-Fall-2021/blob/main/Week%2002/HappyPlant.jpg)

This plant pot helps you easily monitor the light and temperature conditions of your plant, to make sure you are taking care of all of your plant's needs. If you've ever been confused about why your dear plant baby that you have been watering so diligently just died, this pot is for you! with a built in temp sensor with adjustable settings, the pot will make sure your plant is never too cold or hot. The light sensor in the pot helps warn you if the plant has not been receiving enough light for too long (for over 8 hours/a night's time by default). Whenever your plants conditions are unideal, the pot will warn you with a nice big red sad face. Fix the conditions, and the lights will change back to a green smiley once you've got a Happy Plant!

[Tinkercad](https://www.tinkercad.com/things/gAJiEAUBMpD-plant-monitor/editel?sharecode=OUMlEQ0rGYFAuaYqaRqen2gKbaj-nj88KC7kkXIeI88) image of my wiring diagram and the code to run it are below:

![Arduino with three breadboards. One board with light and a temp meter, one with a smiley of LEDS, one with a sad face of LEDs.](https://github.com/orsolyasz/PComp-Fall-2021/blob/main/Week%2002/HappyPlant-Tinker.png)

```
byte redLEDs = 9;
byte greenLEDs = 3;
byte tempSens = A5;
byte lightSens = A0;

int temp = 0;
int light = 0;

int minTemp = 141; //about 18 degrees C
int maxTemp = 155; //about 25 degrees C

int minLight = 15;
int lightCycle = 28800000; //8 hours in msec
//int lightCycle = 5000; // 5 sec, for testing

long darkStart = 0;
long currentTime = 0;
bool dark = false;

bool happy = true;


void setup()
{
  delay(300);
  Serial.begin(9600);
  pinMode(redLEDs, OUTPUT);
  pinMode(greenLEDs, OUTPUT);
  
}

void loop()
{
  temp = analogRead(tempSens);
  light = analogRead(lightSens);
  
  Serial.print(temp);
  Serial.print(",");
  Serial.println(lightSens);
  
  if(temp<minTemp || temp>maxTemp){
    happy=false;
  } else {
    happy=true;
  }
  
  currentTime = millis();
  
  if (light<minLight){
    if(dark==false){
     dark = true;
     darkStart = currentTime;
    } else if (dark==true){
      if (currentTime-darkStart>lightCycle){
      happy= false;
      }
    }
  }
  
  Serial.println(happy);
  
  
  
  if(happy){
  	digitalWrite(greenLEDs, HIGH);
  	digitalWrite(redLEDs, LOW);
  } else {
    digitalWrite(greenLEDs, LOW);
  	digitalWrite(redLEDs, HIGH);
  }
  
}
```

## Lab 06 - DIY Pressure Sensor for an Embodied Computing  

Following the provided guide, I assembled my first pressure sensor:

![Photo of a hand next to a small piece of foam, the DIY sensor](https://github.com/orsolyasz/PComp-Fall-2021/blob/main/Week%2002/PressureSensor.jpeg)

Using four sensors like the above, I created an interactive glove (prototype) that controls a basic Processing drawing sketch. I left the thumb empty to allow the glove's wearer to use their thumb to press on the other four fingers, for added control. The four fingers with sensors control the horizontal position, vertical position, size, and warmth (red channel) of the color of the circles being drawn in Processing.

For this experiment, I just went with using masking tape to lightly fix the sensors on the glove -- which was a rubber glove as I did not have anything more proper available. Once I assembled my prototype, this is what I had:

![Two photos in different angles of an interactive rubber glove with foam DIY pressure sensors affixed to the fingers.](https://github.com/orsolyasz/PComp-Fall-2021/blob/main/Week%2002/DrawingGlove.png)

Here is a brief [video](https://drive.google.com/file/d/1mohareurr6Dfzqi_ISjWGye6XnWnpkbV/view?usp=sharing) documentation of the project in action! Using the glove, these are some of the fun images I created:

![Three images with different sized greenish and yellowish circles forming patterns and lines](https://github.com/orsolyasz/PComp-Fall-2021/blob/main/Week%2002/GloveDrawings.png)

On the technical side, the below [Tinkercad](https://www.tinkercad.com/things/aNsRA67E2WX-sizzling-sango/editel?sharecode=jnV3aBeOTYbAliIEe9FE8Nu7chbpnw1LdyP62m9wsnU) diagram shows my wiring - except I was using the "DIY" sensors.

![Tinkercad diagram of four pressure sensors connected to an Arduino.](https://github.com/orsolyasz/PComp-Fall-2021/blob/main/Week%2002/Tinker%20Pressure%20Gloves.png)

My code for the Arduino to read the sensors and forward them to Processing:
```
int pressure1 = 0;
int pressure2 = 0;
int pressure3 = 0;
int pressure4 = 0;

byte finger1 = A0;
byte finger2 = A1;
byte finger3 = A3;
byte finger4 = A5;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

}

void loop() {
  delay(100);
  // put your main code here, to run repeatedly:
  pressure1 = analogRead(finger1);
  pressure2 = analogRead(finger2);
  pressure3 = analogRead(finger3);
  pressure4 = analogRead(finger4);
  
  Serial.print(pressure1);
  Serial.print(',');
  Serial.print(pressure2);
  Serial.print(',');
  Serial.print(pressure3);
  Serial.print(',');
  Serial.print(pressure4);
  Serial.print(',');
  Serial.println();

}
```

My Processing sketch is below. Note that in all the `map()` functions I am using values based on the readings I got from the particular sensors with the particular wiring that I had in my setup. *(Also note that the sketch could maybe use an addition to wait until a serial port is ready, but I really only thought about this once I was completely done as the lack of a wait did not cause too much of a problem - I only had to restart my sketch a few times.)*

```
import processing.serial.*;

Serial myPort;  // Create object from Serial class
String val;     // Data received from the serial port

int[] pressures = {0, 0, 0, 0, 0}; // array to store my incoming sensor values


float xPos=0;
float xTarget=0;
float xPrev=0;

float yPos=0;
float yTarget=0;
float yPrev = 0;

int r=200;
int g=200;
int b=0;
int rTarget=200;
int rPrev=0;

float size=50;
float sizeTarget=0;
float sizePrev=0;

void setup()
{
     size(1280, 720);
     background(0);
  
  //printArray(Serial.list()); // printing all serial ports to see what port we neeed to use
  String portName = Serial.list()[9]; //here the 9 changes based on what port we need
  myPort = new Serial(this, portName, 9600);
}

void draw()
{
  
  if ( myPort.available() > 0) 
  {  // If data is available,
  val = myPort.readStringUntil('\n');         // read it and store it in val
  } 
 //println(val); //print it out in the console
 
 if(val!=null){ 
 pressures= int(split(val, ','));
 }
 

 xTarget=map(pressures[0], 0,265, 0, width); //map incoming data from finger1 to correspond to an x position accross the full width of the screen
 yTarget=map(pressures[1], 0,80, 0, height); //map incoming data from finger2 to correspond to a y position accross the full height of the screen
 sizeTarget=map(pressures[2], 0, 100, 20, 100); //map incoming data from finger3 to correspond to an size between 20 and 100 pixels
 rTarget=int(map(pressures[3]*random(0.7,1.2), 0, 270, 255, 0)); //map incoming data from finger4 to correspond to a red value on the full available scale

 
 xPos=xPos-(xPos-xTarget)*0.1; //smoothly change the x position of our circle
 yPos=yPos-(yPos-yTarget)*0.01; //smoothly change the y position of our circle
 r=int(r-(r-rTarget)*0.01); //smoothly change the redness of the color of our circle
 size=size-(size-sizeTarget)*0.01; //smoothly change the size of our circle

 
 //println(pressures);
 
 fill(color(r,g,b)); //use new color
 circle(xPos, yPos, size); //draw the next circle at the new location with the new size
}
```
 
 ## Reflections
 
#### Reflect on creating interfaces for your body. Consider how we engage with tools – how does this impact how your body extends into the tools around you? What possibilities do you see?

This week's most exciting part fot me was definitely the creation of the glove and using that to control my drawing sketch. I find that we often expect tools to immediately reveal their exact affordances to us, we rely on designers to give us immedate access to the intended functions of any tool (we could think of something as complex as phones, somethig as simple as a microwave, or something as recent as zoom/video education, a lot of us are frustrated if there is too much of a learning curve when starting to use something). While I obviously see how easy to use and easy to understand tools are often practically necessary, what I liked about the glove - and what I have enojoyed in interactive art in the past- is exactly need to figure out how something works and what we can do with it.

I find that when I am facing a tool whose purpose is not immediately clear to me, I become much more exploratory about it. If I am not told how to use something but something makes it clear to me that it has a use, it really activates my creativity to see what I could possible use the tool for -whether that use is an intended use or not. Similarly, as a designer, I am alwasy excited to see how I can create tools/objects/art pieces that show an affordance of "useability" (that is, which invite interction), but without giving away what the expected or required use would be. I find this approach often puts me in my body and engages me in a joyful way, and that is what I strive to be able to offer other people.

#### Consider what it means to have the skills to make this device. How does it impact, collide with, and alter your relationship with consumer interfaces?

While this is not my first time using some of these skills or my first time creating an interactive device, I am always reminded of the joy and amazement I felt the first time I saw interactive art. Until then, it had simply never even occured to me that I could aslo literally just take some sensors and build something. While of course I can only speak to my personal experience, I think we do live in a society that makes us so used to getting ready made devices, beutifully pacakged technology, and tools with prescribed uses, that we often do not even know to think of an alternative. In addition, in an almost counterintuitive way, the more prevalent computers and smart phones and internet use are becoming, the more removed we are becoming from a concept of them as just objects that someone once came up with -- objects that we could use, alter, and repair (!!!) ourselves with really not a lot of prior knowledge at all.

In this context, having the skills to make this device -or rather, having the experience of having built basic interactive technology- has for me often meant that I am able to approach even consumer interfaces as tools that I can shape to my liking, and it has demystified computers and electricty a lot in my eyes. At the same time, it is also making me more aware of the actual people that are behind the creation of common consumer interfaces -- the designer/manufacturers whose intentions I try to remain  cautiously critical of, but also the actual people whose labor goes into building parts and devices that we as a society often think of as short-term-use (almost disposable) tools.




