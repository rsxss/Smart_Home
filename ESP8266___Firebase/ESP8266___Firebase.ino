#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <SoftwareSerial.h>
#define WIFI_SSID       "MyASUS"
#define WIFI_PASSWORD   "1ccccf2a7cd1"
#define FIREBASE_HOST "smarthomev01-626ae.firebaseio.com"
#define FIREBASE_AUTH "Db0D7jIrZEutBdE8qhj03t92QPcasT8xw3CKUlv8"
SoftwareSerial esp(D5,D6);
String a;
char b;
void setup() {
  Serial.begin(9600);
  esp.begin(9600);
  /*Serial.println(WiFi.localIP());
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.setInt("/Sensor/Sensor_val", 0);*/
}

void loop() {
  while(esp.available()){
    b = esp.read();
    delay(50);
    Serial.print("b:");
    delay(50);
    Serial.println(b);
    delay(50);
    if (b == '\n'){
      Serial.println("BREAK");
      break;
    }
    else{
      a = a + b;
      delay(50);
      Serial.println(a);
      delay(50);
    }
  }
  Serial.println(a);
  delay(50);
  a = "";
  delay(3000);
  //Serial.println("end");
  /*esp.p1rintln(Firebase.getInt("Sensor/Sensor_val"));
  delay(2000);
  digitalWrite(ledPin, Firebase.getInt("LED"));
  delay(500);
  if (esp.available()){
    //Serial.println("esp readable");
    esp.write("B");
    Firebase.setInt("/Sensor/Sensor_val", esp.read());
    Serial.print("nucleo_data: ");
    Serial.println(char(esp.read()));
  }*/
}
