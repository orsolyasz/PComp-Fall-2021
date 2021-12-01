//Transmitter Code
#include <SoftwareSerial.h>
SoftwareSerial mainBoard(7, 6);

byte pressurePin1 = A0;
byte pressurePin2 = A1;
byte pressurePin3 = A2;
int pressureVal1 = 0;
int pressureVal2 = 0;
int pressureVal3 = 0;
String pressureValStr1 = "0000";
String pressureValStr2 = "0000";
String pressureValStr3 = "0000";

int strength1 = 0;
int targetStrength1 = 0;
int minPressure1 = 10;
int maxPressure1 = 300;
int threshold1 = 240;

int strength2 = 0;
int targetStrength2 = 0;
int minPressure2 = 10;
int maxPressure2 = 840;
int threshold2 = 750;

int strength3 = 0;
int targetStrength3 = 0;
int minPressure3 = 10;
int maxPressure3 = 990;
int threshold3 = 920;



void setup()
{
  Serial.begin(9600);
  mainBoard.begin(9600);
}


void loop()
{
  pressureVal1 = analogRead(pressurePin1);
  pressureValStr1 = fourDigitString(pressureVal1);
  pressureVal2 = analogRead(pressurePin2);
  pressureValStr2 = fourDigitString(pressureVal2);
  pressureVal3 = analogRead(pressurePin3);
  pressureValStr3 = fourDigitString(pressureVal3);

  targetStrength1 = map(pressureVal1, maxPressure1, minPressure1,
                        0, 200);
  if (pressureVal1 > threshold1) {
    targetStrength1 = 0;
  }

  targetStrength2 = map(pressureVal2, maxPressure2, minPressure2,
                        0, 200);
  if (pressureVal2 > threshold2) {
    targetStrength2 = 0;
  }

  targetStrength3 = map(pressureVal3, maxPressure3, minPressure3,
                        0, 200);
  if (pressureVal3 > threshold3) {
    targetStrength3 = 0;
  }

  strength1 = strength1 - (strength1 - targetStrength1) * 0.08;
  strength2 = strength2 - (strength2 - targetStrength2) * 0.08;
  strength3 = strength3 - (strength3 - targetStrength3) * 0.08;


  Serial.print(pressureVal1);
  Serial.print(',');
  Serial.print(pressureVal2);
  Serial.print(',');
  Serial.println(pressureVal3);

  analogWrite(9, strength1);
  analogWrite(10, strength2);
  analogWrite(11, strength3);


  //  Serial.print(pressureValStr1); //print to local screen for debug
  //  Serial.print(',');
  //  Serial.println(pressureValStr2);
  mainBoard.print('$');
  mainBoard.print(pressureValStr1);
  mainBoard.print(',');
  mainBoard.print(pressureValStr2);
  mainBoard.print(',');
  mainBoard.print(pressureValStr3);
  mainBoard.println('#');

  delay(200);
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
