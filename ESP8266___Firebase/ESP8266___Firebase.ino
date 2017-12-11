#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <SoftwareSerial.h>
#include <time.h>
#define WIFI_SSID       "MyASUS"
#define WIFI_PASSWORD   "1ccccf2a7cd1"  
#define FIREBASE_HOST "smarthomev01-626ae.firebaseio.com"
#define FIREBASE_AUTH "Db0D7jIrZEutBdE8qhj03t92QPcasT8xw3CKUlv8"
// Config time
int timezone = 7;

char ntp_server1[20] = "ntp.ku.ac.th";
char ntp_server2[20] = "fw.eng.ku.ac.th";
char ntp_server3[20] = "time.uni.net.th";

int dst = 0;

SoftwareSerial esp(D5,D6);
String a;
String e;
char b;
int c;
float d;
String NowString();
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
  configTime(timezone * 3600, dst, ntp_server1, ntp_server2, ntp_server3);
  while (!time(nullptr)) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.println("Now: " + NowString());
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
    String RFID_log = NowString() + ':' + a.substring(2);
    Firebase.setString(text,RFID_log);
  }
  a = "";
  delay(1);
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

String NowString() {
  time_t now = time(nullptr);
  struct tm* newtime = localtime(&now);

  String tmpNow = "";
  tmpNow += String(newtime->tm_hour);
  tmpNow += ":";
  tmpNow += String(newtime->tm_min);
  tmpNow += ":";
  tmpNow += String(newtime->tm_sec);
  return tmpNow;
}


void loop() {
  get_nucleo();
  delay(1);
  check_get_nucleo();
  delay(1);
  //get_firebase();
}


