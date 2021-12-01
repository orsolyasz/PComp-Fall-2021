void setup(){
    Serial.begin(115200);    // standard for mp3trigger
}
 
 
void loop()
{
    // play track 1. name on sd-card: 001.mp3
    Serial.print("t");
    Serial.write(1);
    delay(5000);

    // play track 5. name on sd-card: 005.mp3
    Serial.print("t");
    Serial.write(5);
    delay(5000);
}
