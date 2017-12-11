#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <SoftwareSerial.h>
#define WIFI_SSID       "pengpond"
#define WIFI_PASSWORD   "0865679871"
#define FIREBASE_HOST "smarthomev01-626ae.firebaseio.com"
#define FIREBASE_AUTH "Db0D7jIrZEutBdE8qhj03t92QPcasT8xw3CKUlv8"
SoftwareSerial esp(D5,D6);
String a;
String e;
char b;
int c;
float d;
void setup() {
  Serial.begin(9600);
  esp.begin(9600);
  Serial.println(WiFi.localIP());
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
  //Firebase.setInt("/Sensor/Sensor_val", 0);
}

void get_nucleo(){
   while(esp.available()){
    b = esp.read();
    if (b == '\n'){
      break;
    }
    else{
      a = a + b;
      //Serial.println(a);
    }
  }
  Serial.println(a);
}

void check_get_nucleo(){
  if (a.charAt(0) == 'r'){
    e = a.charAt(2);
    c = e.toInt();
    Serial.println(c);
    Firebase.setInt("/Sensor/Rain",c);
  }
  else if(a.charAt(0) == 't'){
    e = a.substring(2);
    d = e.toFloat();
    Firebase.setFloat("/Sensor/Temp",d);    
  }
  a = "";
  delay(50);
}

void get_firebase(){
  
}

void loop() {
  get_nucleo();
  delay(50);
  check_get_nucleo();
  delay(50);
}


