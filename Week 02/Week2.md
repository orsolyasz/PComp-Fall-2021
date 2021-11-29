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

*(Disclaimer: Confusingly, in testing this in Tinkercad I am able to line up about 35-36 LEDs to a 5V 500mA power supply without an issue. I am not sure why that is or where my calculations above would be off, but maybe it is only the simulation that is off as the power supply element is a bit finicky to use. I did not have 20+ LEDs to test this with physically, but I will try at some point.)*

![Tinkercad image showing 35 LEDs connected in parallel](https://github.com/orsolyasz/PComp-Fall-2021/blob/main/Week%2002/Parallel%20LED%20Test.png)


## Lab 01 - Serial Data Story


For this lab, I created a mini (un)helpful machine. Code and screenshots of the mini story's two branches are below.

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
![Screenshot of bot chat responses if the responder does not need help(https://github.com/orsolyasz/PComp-Fall-2021/blob/main/Week%2002/UnhelpfulMachine-No.png)



