#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <SoftwareSerial.h>
#define WIFI_SSID       "MyASUS"
#define WIFI_PASSWORD   "1ccccf2a7cd1"  
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
  //Serial.println(a);
}

void check_get_nucleo(){
  if (a.charAt(0) == 'r'){
    e = a.charAt(2);
    c = e.toInt();
    //Serial.println(c);
    Firebase.setInt("/Sensor/Rain",c);
  }
  else if(a.charAt(0) == 't'){
    e = a.substring(2);
    d = e.toFloat();
    Firebase.setFloat("/Sensor/Temp_O",d);    
  }
  else if(a.charAt(0) == 'I'){
    String text = "/RFID/" + a.substring(2);
    Firebase.setString(text,a.substring(2));
  }
  else if(a.charAt(0) == 'C'){
    String text = "/RFID/" + a.substring(2);
    String result = Firebase.getString(text);
    if (result){
      esp.print('1');
    }
    else esp.print('0');
  }
  else if(a.charAt(0) == 'D'){
    String text = "/RFID/" + a.substring(2);
    Firebase.remove(text);
  }
  else if(a.charAt(0) == 'L'){
    String text = "/Log/" + a.substring(2);
    
  }
  a = "";
  delay(50);
}

void get_firebase(){
    /*Firebase.stream("Setting/Rain_status");
    if (Firebase.available()){
      FirebaseObject event = Firebase.readEvent();
      String type = event.getString("type");
      String path = event.getString("path");
      String data = event.getString("data"); 

    }*/
}



void loop() {
  get_nucleo();
  delay(50);
  check_get_nucleo();
  delay(50);
  //get_firebase();
}


