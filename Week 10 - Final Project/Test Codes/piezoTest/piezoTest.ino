int ledPin = 13;
int piezoPin = A0;

int sensor = 0;
int ledStatus = LOW;
int range = 50;


void setup()
{
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  sensor = 0;
  sensor = analogRead(piezoPin);
  Serial.println(sensor);

  if (sensor >= range) {
    ledStatus = !ledStatus;
    digitalWrite(ledPin, ledStatus);
  } else {
    ledStatus = LOW;
    digitalWrite(ledPin, ledStatus);
    }

  //int thisPitch = map(sensor, 400, 250, 120, 1500);
  int thisPitch = sensor;
  Serial.println(thisPitch);


  // play the pitch:

  tone(9, thisPitch, 10);

  delay(1);
}
