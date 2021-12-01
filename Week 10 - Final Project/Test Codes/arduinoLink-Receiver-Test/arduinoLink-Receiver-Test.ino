#include <SoftwareSerial.h>
SoftwareSerial secondBoard(7,6);
SoftwareSerial XBee(2, 3); // RX, TX

int inData = 0;


void setup() {
  // put your setup code here, to run once:
  delay(300);

  Serial.begin(9600);
  XBee.begin(9600);
  establishContact();
  secondBoard.begin(9600);

}

void loop() {
  
  secondBoard.listen();

 while (secondBoard.available()>0) {
   inData = secondBoard.read();
   Serial.write(inData);
  }

   //XBee.write(inData);



}

void establishContact() {
  //while (Serial.available() <= 0) {
  XBee.println("0,0,0,0,0,0,0,0,0");   // send an initial string
  delay(300);
  //}
}
