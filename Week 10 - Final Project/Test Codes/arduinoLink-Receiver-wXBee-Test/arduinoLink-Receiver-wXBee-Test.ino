#include <SoftwareSerial.h>
SoftwareSerial secondBoard(7, 6);
SoftwareSerial XBee(2, 3); // RX, TX

char inData[100];
int dataLength = 0;
String pressureReadings = "0000,0000,0000,";

void setup() {
  // put your setup code here, to run once:
  delay(300);

  Serial.begin(9600);
  XBee.begin(9600);
  establishContact();
  secondBoard.begin(9600);

}

void loop() {
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


  Serial.println(pressureReadings);
  sendInfo();
  delay(1);
  secondBoard.listen();


}

void establishContact() {
  //while (Serial.available() <= 0) {
  XBee.println("0000,0000,0000,");   // send an initial string
  delay(300);
  //}
}

void sendInfo() {

  delay(3);
  XBee.listen();
  delay(1);
  XBee.println(pressureReadings);
  delay(1);
}
