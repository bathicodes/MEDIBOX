#include <SoftwareSerial.h>
#include <ArduinoJson.h>
SoftwareSerial s(5, 6);

int tilt = 12;     //define tilt sensor
int tiltVal = 0;  // varieable for tilt value caught

int lm35 = A0;    //define LM35
int lm35Val = 0;  //varieable for LM35 value caught
int temperature = 0;  //temperature variable

int buzzer = 2;    //define buzzer

void setup() {
  pinMode(tilt, INPUT_PULLUP); //tilt pinMode

  pinMode(lm35,INPUT); //LM35 pinMode

  pinMode(buzzer,OUTPUT);  //buzzer pinMode

  analogReference(INTERNAL); // sensing range 0～100℃，output voltage 0～1V

  s.begin(9600);
  Serial.begin(9600);

  
}

void loop() {

  tiltVal = digitalRead(tilt);    // read the tilt value
  Serial.println(tiltVal);

  lm35Val = analogRead(lm35);     // read the LM35 value
  temperature = (float)lm35Val/1023*110.00; //converting to celciues

  //checking the orientation
  if(tiltVal == HIGH){
    orientationWarningUP();
  }

  //checking the temperature
  if(temperature > 34){
    coolentWarning();
  }



  StaticJsonBuffer<1000> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
  root["data1"] = tiltVal;
  root["data2"] = temperature;
  
  if (s.available() > 0)
  {
    root.printTo(s);
  }
}


//warning alarm for oreintation sensor
void orientationWarningUP(){
  digitalWrite(buzzer,HIGH);
  delay(250);
  digitalWrite(buzzer,LOW);
  delay(250);
}

//warning alarm for temperature sensor
void coolentWarning(){
  digitalWrite(buzzer,HIGH);
  delay(100);
  digitalWrite(buzzer,LOW);
  delay(100);
}
