#include <SoftwareSerial.h>
#include"MP3Trigger.h"

SoftwareSerial trigSerial = SoftwareSerial(2, 3);
MP3Trigger trigger;

void setup() {
  // Start serial communication with the trigger (over SoftwareSerial)
  trigger.setup(&trigSerial);
  trigSerial.begin( MP3Trigger::serialRate() );

}

void loop() {
  trigger.update();
  trigger.play(1);
  Serial.println("play track 1");
  delay(5000);
  trigger.play(2);
  Serial.println("play track 2");
  delay(2000);
  trigger.play(3);
  Serial.println("play track 3");
  delay(3000);
}
