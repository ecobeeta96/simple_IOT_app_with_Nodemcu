
#include <FirebaseArduino.h>
#include "ESP8266WiFi.h"

#define FIREBASE_HOST "<hostName>.firebaseio.com"
#define FIREBASE_AUTH "DatabaseSecret"
#define LED D4

// WiFi parameters to be configured
const char* ssid = "WiFiSSID";
const char* password = "WiFiPassword";
const char* Ledstatus = "LEDStatus";

void setup(void)
{ 
  pinMode(LED,OUTPUT);

  
  Serial.begin(9600);
  // Connect to WiFi
  WiFi.begin(ssid, password);

  // while wifi not connected yet, print '.'
  // then after it connected, get out of the loop
  while (WiFi.status() != WL_CONNECTED) {
     delay(500);
     Serial.print(".");
  }
  //print a new line, then print WiFi connected and the IP address
  Serial.println("");
  Serial.println("WiFi connected");
  // Print the IP address
  Serial.println(WiFi.localIP());

  Firebase.begin(FIREBASE_HOST,FIREBASE_AUTH);
  Firebase.setInt(Ledstatus,1);
}
void loop() {
  // Nothing
  int ledst = Firebase.getInt(Ledstatus);
  //Serial.println(ledst);
  if(Firebase.getInt(Ledstatus)==1){
    digitalWrite(LED,HIGH);
  }
  else{
    digitalWrite(LED,LOW);
  }
  
  if (Firebase.failed()){ // Check for errors {
    Serial.print("setting /number failed:");
    Serial.println(Firebase.error());
    return;
  }
  

  delay(1000);
}
