//Transmitter Code
#include <SoftwareSerial.h>
SoftwareSerial mainBoard(7, 6);
byte pressurePin2 = A0;
int pressureVal2 = 0;
String pressureValStr2 = "0000";

void setup()
{
 Serial.begin(9600);
  mainBoard.begin(9600);
}

void loop()
{
  pressureVal2 = analogRead(pressurePin2);
  pressureValStr2= fourDigitString(pressureVal2);
  
  Serial.println(pressureValStr2); //print to local screen for debug
  mainBoard.print('$');
  mainBoard.print(pressureValStr2);
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
