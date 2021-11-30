# Week 8

## Lab 1-2 Synths

For this lab, I experimented with hooking up an oscillator to different capacitors and resistors (including using a lightmeter and a potentiometer as resistors).

There was one thing I noticed that was really unexpected behavior. Once I tried using only two pins by connecting them as instructed, I wanted to try setting up two pin pairs and using the output from one to affect the output from the other. But when I connected the second pair of pins, they seemed to have an effect on my sound output even without me adding a wire from them to the first pin pair's output (which is where I was connecting my speakers). That said, after nudging some cables around, this effect was sometimes gone, and adding a cable also change the effect, so I think it's most likely that my problems all just came from the state/age of the breadboard I had available.

Here are some photos of different (fairly basic) setups I tried:

![Oscillator with capacitor and resistor setup](https://github.com/orsolyasz/PComp-Fall-2021/blob/main/Week%2008/Single-Osc-Res1.png)
![Oscillator with different capacitor and resistor setup](https://github.com/orsolyasz/PComp-Fall-2021/blob/main/Week%2008/Single-Osc-Res2.png)
![Oscillator with two outputs connected](https://github.com/orsolyasz/PComp-Fall-2021/blob/main/Week%2008/Double-Osc.png)
![Oscillator with temp sensor](https://github.com/orsolyasz/PComp-Fall-2021/blob/main/Week%2008/Temp-Osc.png)
![Oscillator with potentiometer](https://github.com/orsolyasz/PComp-Fall-2021/blob/main/Week%2008/Pot-Osc.png)
![Oscillator with potentiometer and temp sensor](https://github.com/orsolyasz/PComp-Fall-2021/blob/main/Week%2008/Pot-Temp-Osc.png)

I have also taken some [video documentation](https://drive.google.com/drive/folders/1GgM2qw1O5DZX3IEIMgCq0cUCMTZlmqhk?usp=sharing) of different setups' effects.

*(Note I only had access to one osccilator chip in my own kit and I was still not on campus for this lab)*


## Lab 3: Making your first soft robot 

For this lab, I first followed Matt's guide of using a watersnake toy to create a bead-shooting mechanism. See my setup in the images below, and see the snake in action in my [video](https://drive.google.com/drive/folders/10xeN3Ey0OuHELfAasA_rMa8N8ZWy6hKx?usp=sharing) documentation.

![Watersnake toy set up to shoot out beads](https://github.com/orsolyasz/PComp-Fall-2021/blob/main/Week%2008/Watersnake1.png)

As the second exercise, I created a string of spaced out beads to be able to make the snake move. My setup ended up looking like the image below, and you can see the toy move in my [documentation](https://drive.google.com/drive/folders/10xeN3Ey0OuHELfAasA_rMa8N8ZWy6hKx?usp=sharing).

![Watersnke toy with a string of beads inside to let it move](https://github.com/orsolyasz/PComp-Fall-2021/blob/main/Week%2008/Watersnake2.png)

As I was really excited about the movement the toy could produce, I started thinking about how I could automate the movement of the string -- so that the toy could wihtout me physically moving it. I came up with a very simple idea: to have the two ends of the string attached to two servo motors placed on either end and always pointing in the same direction (kind of like a windshield wiper, just different in being in synch and not so curved). A sketch of this idea is shown below.

![Handdrawn sketch of watersnake toy with a string of beads inside and two servos on the sides](https://github.com/orsolyasz/PComp-Fall-2021/blob/main/Week%2008/Automated-WaterSnake.jpg)

I tried actually building this setup but I only had two tiny micro servos, which proved just way too weak to actually be able to move the snake. That said, I have the code as I was using it to see if I could make my small servos work, so see that below.

 ``` 
 #include <Servo.h> 

int servoPos=90; 
int servoPos2=90;
byte servoPin= 9;
byte servoPin2=11;
Servo rightServo;
Servo leftServo;


void setup()
{
  Serial.begin(9600);
  rightServo.attach(servoPin);
  leftServo.attach(servoPin2);
  delay(2000);

}

void loop()
{
  servoPos=180;
  servoPos2=0;
  rightServo.write(servoPos);
  leftServo.write(servoPos2);
  delay(5000);

  servoPos2=180;
  servoPos=0;
  rightServo.write(servoPos);
  leftServo.write(servoPos2);
  delay(5000);  
 
}
 ``` 
 
This simple code has a servo connected to pin 9 an another at pin 11, and is switching them between 0 and 180 every few seconds. This version has the motors always at opposite angles to each other, so that if their bodies are oriented in the same direction, the would always point in the same direction (so they are maintaining the distance, the length of string, between their tips) 

## Lab 4 Reflections from Building the Hand

When I was first building the [DIY pressure sensors](https://github.com/orsolyasz/PComp-Fall-2021/blob/main/Week%2002/00%20Week2.md#lab-06---diy-pressure-sensor-for-an-embodied-computing), I already took the opportunity to build a pressure sensitive glove, which was really thin and had sensors right at my fingertips. 

Having played with that setup using my drawing sketch, I was excited to see what the difference would be when the sensors are removed from my body -- as one of the things I enjoyed so much about my original glove was that it was making me feel very aware of my body and movements. Having to use pressure directly on my fingertips really made me feel the touch I was receiving (both the touch I received back from the table as I pressed down on it and also the pressure I received from my thumb or my other hand pressing down on each particular finger). In a way, I felt like that design was interesting exactly because it encouraged me to be attentive to how strongly I am touchign/pressing on something, which made me start to pay attention to the relationship of how things felt on my body/on my hand versus what they looked like on the screen.

After this experience, I found that placing the sensors away from my body, on the ends of the hand puppet, actually almost had the opposite effect in regards to touch, but maybe instead made me focus more on movement. While in my first version of this setup (sensors on fingers), I was constantly aware of both the sensor against my skin and also the pressure of the touch I was using (partly because I set my pressure range wuite high so sometimes I would have to press reallllly hard to achieve something), in this setup I was more focused on how differnt movements of my hand translated to different movements of the puppet. In a way, I actually became less aware of my sense of touch - as the cardboard is also fairly lightweight, and while I never felt like the hand "became a part of my hand," I was definitely more focused on learning to move the hand "naturally" using my own movements. I left the pressure sensors almost just react to movement, almost ignoring them completely as means of touch.

I think the difference in my experience came from how the pressure sensors in this setup would never provide the same feedback I used to feel while using them directly on my hand (and on the inside of my hand rather than the outise of it) - so they were not really able to direct my attention. Instead, the size of the hand and its direct relationship to my own movements became a huge source of visual feedback, which is why I think I was incentivized to focus on that more. As an effect, though, not only was I focused more on my movements, but also interestingly (maybe surprisingly) I would say I was less aware of my body -- touch and pressure seem to have more of an impact in bringin my awareness to my body than abstract movement does.


