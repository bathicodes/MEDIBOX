#include <ESP8266WiFi.h>

#include <FirebaseArduino.h>
#include <SoftwareSerial.h>
SoftwareSerial s(D6, D5);
#include <ArduinoJson.h>


#define WIFI_SSID "add your wifi name here"
#define WIFI_PASSWORD "add your wifi password here"
#define FIREBASE_HOST "add firebase host here"
#define FIREBASE_AUTH "add firebase Auth here"



void setup()
{

  Serial.begin(9600);
  s.begin(9600);
  while (!Serial) continue;


  delay(2000);
  Serial.println('\n');

  wifiConnect();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

  delay(10);
}

void loop()
{

  StaticJsonBuffer<1000> jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(s);
  if (root == JsonObject::invalid())
    return;

  int data1 = root["data1"];
  String stringOne =  String(data1);
  Serial.println(data1);

  int data2 = root["data2"];
  String stringTwo = String(data2);
  Serial.println(data2);

  
  Firebase.setString("MEDIBOX/orientaion", stringOne);
  Firebase.setString("MEDIBOX/temperature", stringTwo);


  if (WiFi.status() != WL_CONNECTED)
  {
    wifiConnect();
  }
  delay(10);

}

void wifiConnect()
{
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);             // Connect to the network
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID); Serial.println(" ...");

  int teller = 0;
  while (WiFi.status() != WL_CONNECTED)
  { // Wait for the Wi-Fi to connect
    delay(1000);
    Serial.print(++teller); Serial.print(' ');
  }

  Serial.println('\n');
  Serial.println("Connection established!");
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());         // Send the IP address of the ESP8266 to the computer
}
