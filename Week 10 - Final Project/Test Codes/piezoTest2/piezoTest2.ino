int piezoIn =0;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
   piezoIn= analogRead(A0);
   //digitalWrite(9, piezoIn*100);
   Serial.println(piezoIn);
}
