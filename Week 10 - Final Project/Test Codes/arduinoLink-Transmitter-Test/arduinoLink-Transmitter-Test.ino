//Transmitter Code
#include <SoftwareSerial.h>
SoftwareSerial mainBoard(7, 6);
byte pressurePin2 = A0;
int pressureVal2 = 0;

void setup()
{
 Serial.begin(9600);
  mainBoard.begin(9600);
}

void loop()
{
  pressureVal2 = analogRead(pressurePin2);
  Serial.print(0);
  Serial.println(pressureVal2); //print to local screen for debug
  mainBoard.print(0);
  mainBoard.println(pressureVal2);

  delay(200);
}
