#include <Arduino.h>
#include <ESP32Servo.h>
#include <WiFi.h>
#include <Firebase_ESP_Client.h>
#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"

#define WIFI_SSID "M"
#define WIFI_PASSWORD "mostafa151**#"

#define API_KEY "AIzaSyCfWy5kWleSqEUNFe8Lo57PeDZVK0Fq9pQ"
#define DATABASE_URL "https://project-6eda1-default-rtdb.firebaseio.com"

#define USER_EMAIL "manarabdo@gmail.com"
#define USER_PASSWORD "1234manar"


const int servoCount = 5;// how many servo 
static const int servosPins[servoCount] = {14, 12, 25, 26, 27}; // define pins here

Servo servos[servoCount];//do not change

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

unsigned long sendDataPrevMillis = 0;
int hand;

void servoMotorOpen(){
  Serial.println("Open Hand");

  for (int pos=180; pos>=0; pos--){
    for (int servo=0; servo<=5; servo++){
        servos[servo].write(pos);
          Serial.println("Open");
        delay(20); 
    }
  }
  
}

void servoMotorClose(){
  Serial.println("Close Hand");

  for (int pos=0; pos<=180; pos++){
    for (int servo=0; servo<=5; servo++){
        servos[servo].write(pos);
        delay(20); 
    }
  }
  
}

void thumbOpen(){
  Serial.println("thumb Open");
  servos[4].write(0);
  delay(500);
}
void thumbClose(){
  Serial.println("thumb Close");
  servos[4].write(180);
  delay(500);  
}
void indexOpen(){
  Serial.println("index Open");
  servos[3].write(0);
  delay(500); 
}
void indexClose(){
  Serial.println("index Close");
  servos[3].write(180);
  delay(500); 
}
void middleOpen(){
  Serial.println("Middle Open");
  servos[2].write(0);
  delay(500);
}
void middleClose(){
  Serial.println("Middle Close");
  servos[2].write(180);
  delay(500); 
}
void ringOpen(){
  Serial.println("Ring Open");
  servos[1].write(0);
  delay(500);  
}
void ringClose(){
  Serial.println("Ring Close");
  servos[1].write(180);
  delay(500);
}
void littleOpen(){
  Serial.println("Little Open");
  servos[0].write(0);
  delay(500);
}
void littleClose(){
  Serial.println("Little Close");
  servos[0].write(180);
  delay(500);
}
void pin(){
  Serial.println("pin");
  servos[0].write(180);
  delay(500);
}

void three(){
  Serial.println("Three");
  
  Serial.println("Thumb");
  servos[4].write(0);
  delay(20);
  
  Serial.println("Index Finger");
  servos[3].write(0);
  delay(20);  
  
  Serial.println("Middle Finger");
  servos[2].write(0);
  delay(20);  

  Serial.println("Ring Close");
  servos[1].write(180);
  delay(20);
  
  Serial.println("Little Close");
  servos[0].write(180);
  delay(20);
}

void heart(){
  Serial.println("Ring Open");
  servos[1].write(0);
  delay(500);  
}

void done(){
  Serial.println("Ring Close");
  servos[1].write(180);
  delay(500);
}

void ok(){
  Serial.println("OK");

  Serial.println("Little Finger");
  servos[0].write(180);
  delay(500);  
  
  Serial.println("Ring Finger");
  servos[1].write(180);
  delay(500);  
  
  Serial.println("Middle Finger");
  servos[2].write(180);
  delay(500);  
 
  Serial.println("Index Finger");
  servos[3].write(180);
  delay(500);

  Serial.println("thumb Open");
  servos[4].write(0);
  delay(500);
}

void please(){
  Serial.println("Please");

  Serial.println("Little Finger");
  servos[0].write(180);
  delay(500);  
  
  Serial.println("Ring Finger");
  servos[1].write(180);
  delay(500);  
  
  Serial.println("Middle Finger");
  servos[2].write(180);
  delay(500);  
 
  Serial.println("Index Finger");
  servos[3].write(0);
  delay(500);

  Serial.println("thumb Open");
  servos[4].write(180);
  delay(500);
}
// Initialize WiFi
void initWiFi() {
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  Serial.println(WiFi.localIP());
  Serial.println();
}

void setup(){
  Serial.begin(115200);
  
  // Initialize WiFi
  initWiFi();

  Firebase.reconnectWiFi(true);

  config.api_key = API_KEY;

  /* Assign the user sign in credentials */
  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;

  /* Assign the RTDB URL (required) */
  config.database_url = DATABASE_URL;

  /* Assign the callback function for the long running token generation task */
  config.token_status_callback = tokenStatusCallback; // see addons/TokenHelper.h

  Firebase.begin(&config, &auth);

  
}

void loop(){

    if (Firebase.ready() && (millis() - sendDataPrevMillis > 1000 || sendDataPrevMillis == 0)) {
         sendDataPrevMillis = millis();
        
        if (Firebase.RTDB.getInt(&fbdo, "/handStatus")) {
          hand = fbdo.intData();
          if (hand == 0) {
            Serial.println(hand);
            servoMotorClose();
          }
          else if (hand == 01) {
            Serial.println(hand);
            servoMotorOpen();
          }
          else if (hand == 1) {
            Serial.println(hand);
            thumbOpen();
          }
          else if (hand == 10) {
            Serial.println(hand);
            thumbClose();
          }
          else if (hand == 2) {
            Serial.println(hand);
            indexOpen();
          }
          else if (hand == 20) {
            Serial.println(hand);
            indexClose();
          }
          else if (hand == 3) {
            Serial.println(hand);
            middleOpen();
          }
          else if (hand == 30) {
            Serial.println(hand);
            middleClose();
          }
          else if (hand == 4) {
            Serial.println(hand);
            ringOpen();
          }
          else if (hand == 40) {
            Serial.println(hand);
            ringClose();
          }
          else if (hand == 5) {
            Serial.println(hand);
            littleOpen();
          }
          else if (hand == 50) {
            Serial.println(hand);
            littleClose();
          }
          else if (hand == 11) {
            Serial.println(hand);
            pin();
          }
          else if (hand == 12) {
            Serial.println(hand);
            three();
          }
          else if (hand == 13) {
            Serial.println(hand);
            heart();
          }
          else if (hand == 14) {
            Serial.println(hand);
            done();
          }
          else if (hand == 15) {
            Serial.println(hand);
            ok();
          }
          else if (hand == 15) {
            Serial.println(hand);
            please();
          }
        }
        else {
          Serial.println(fbdo.errorReason());
        }
    }
    
}
