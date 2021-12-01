import processing.serial.*;
import processing.sound.*;
import de.looksgood.ani.*;
import de.looksgood.ani.easing.*;

Serial xBee;

float[] capSensors = new float[15];
String[] inArray = new String[15];
int[] intInArray= new int[15];
String inString;

SoundFile[] sounds = new SoundFile[15];
float timings1 = 0.;
float timings2 = 0.;
float timings3 = 0.;
float timings4 = 0.;
float timings5 = 0.;
float timings6 = 0.;
float timings7 = 0.;
float timings8 = 0.;
float timings9 = 0.;
float timings10 = 0.;
float timings11 = 0.;
float timings12 = 0.;
float timings13 = 0.;
float timings14 = 0.;
float timings15 = 0.;
float timings0 = 0.;
float maxAmp=.55;

void setup() {
  size(300, 300);
  printArray(Serial.list());
  xBee = new Serial(this, Serial.list()[9], 9600);
  xBee.bufferUntil('\n');

  for (int i=0; i<15; i++) {
    capSensors[i] = 0;
    inArray[i]="0";
    intInArray[i]=0;
    sounds[i] = new SoundFile(this, i+1 + ".aif");
  }

  inString = "$,0,0,0,0,0,0,0,0,0000,0000,0000,0000,0000,0000,";

  for (int i=0; i<15; i++) {
    sounds[i].amp(0);
    sounds[i].loop();
  }

  //initiating Ani to be used for fading sound
  Ani.init(this);
}


void draw()
{
  background (0);
  inArray = split(inString, ',');

  if(inArray.length>=15&&intInArray.length>=15) {
  for (int i=1; i<15; i++) {
    intInArray[i]=int(inArray[i]);
  }

  for (int i=1; i<15; i++) {
    float newValue = capSensors[i]+(intInArray[i]-capSensors[i])*.4;
    if (intInArray[i]==0) {
      capSensors[i-1]=0;
    } else {
      capSensors[i-1]=newValue;
    }
  }

  println(intInArray);

  soundTest();
  }
}

void soundTest() {
  for (int i =0; i<8; i++) {
    if (capSensors[i] >0) {
      Ani.to(this, 3, "timings" +i, maxAmp);
      //sounds[i].amp(0.5);
      //sounds[i].play();
      //println(timings[15]);
    } else {
      Ani.to(this, 1.5, "timings" +i, 0.);
      //sounds[i].amp(;
    }
  }


  if (intInArray[14]<40) {
    Ani.to(this, 3, "timings14", map(intInArray[14],5, 20, 0.8, 0.4));
    //sounds[i].amp(0.5);
    //sounds[i].play();
    //println(timings[15]);
  } else {
    Ani.to(this, 4, "timings14", 0.);
    //sounds[i].amp(;
  }

  if (intInArray[12]<70){
    Ani.to(this, 3, "timings12", map(intInArray[12],5, 20, 0.8, 0.4));
    //sounds[i].amp(0.5);
    //sounds[i].play();
    //println(timings[15]);
  } else {
    Ani.to(this, 4, "timings12", 0.);
    //sounds[i].amp(;
  }




  sounds[0].amp(timings0);
  sounds[1].amp(timings1);
  sounds[2].amp(timings2);
  sounds[3].amp(timings3);
  sounds[4].amp(timings4);
  sounds[5].amp(timings5);
  sounds[6].amp(timings6);
  sounds[7].amp(timings7);
  sounds[8].amp(timings8);
  sounds[9].amp(timings9);
  sounds[10].amp(timings10);
  sounds[11].amp(timings11);
  sounds[12].amp(timings12);
  sounds[13].amp(timings13);
  sounds[14].amp(timings14);
  //sounds[15].amp(timings15);
}


void serialEvent (Serial xBee) {
  inString =xBee.readStringUntil('\n');
  println(inString);
}
