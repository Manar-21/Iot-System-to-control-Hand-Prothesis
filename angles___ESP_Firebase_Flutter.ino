#include <Arduino.h>
#include <ESP32Servo.h>
#include <WiFi.h>
#include <Firebase_ESP_Client.h>
#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"
#include <ESPAsyncWebServer.h>
//#include <Servo.h>

#define WIFI_SSID "Menna"
#define WIFI_PASSWORD "Menna010"
//
//const char* WIFI_SSID = "3eengallery";
//const char* WIFI_PASSWORD = "G44445555#";

#define API_KEY "AIzaSyCfWy5kWleSqEUNFe8Lo57PeDZVK0Fq9pQ"
#define DATABASE_URL "https://project-6eda1-default-rtdb.firebaseio.com"

#define USER_EMAIL "manarabdo@gmail.com"
#define USER_PASSWORD "1234manar"


const int servoCount = 5;// how many servo 
static const int servosPins[servoCount] = {26, 12, 25, 27, 14}; // define pins here

Servo servos[servoCount];//do not change


//Servo servos[servoCount];

AsyncWebServer server(80);

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
        delay(10); 
    }
  }
  
}

void servoMotorClose(){
  Serial.println("Close Hand");

  for (int pos=0; pos<=180; pos++){
    for (int servo=0; servo<=5; servo++){
        servos[servo].write(pos);
        delay(10); 
    }
  }
  
}

void thumbOpen(){
  Serial.println("thumb Open");
  servos[4].write(0);
}
void thumbClose(){
  Serial.println("thumb Close");
  servos[4].write(180);
}
void indexOpen(){
  Serial.println("index Open");
  servos[3].write(0);
}
void indexClose(){
  Serial.println("index Close");
  servos[3].write(180);
}
void middleOpen(){
  Serial.println("Middle Open");
  servos[2].write(0);
}
void middleClose(){
  Serial.println("Middle Close");
  servos[2].write(180);
}
void ringOpen(){
  Serial.println("Ring Open");
  servos[1].write(0);
}
void ringClose(){
  Serial.println("Ring Close");
  servos[1].write(180);
  delay(20);
}
void littleOpen(){
  Serial.println("Little Open");
  servos[0].write(0);
}
void littleClose(){
  Serial.println("Little Close");
  servos[0].write(180);
}
void pin(){
  Serial.println("pin");
  servos[0].write(180);
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
  Serial.println("Thumb");
  servos[4].write(90);
  
  Serial.println("Index Finger");
  servos[3].write(90);
  
  Serial.println("Middle Finger");
  servos[2].write(90);

  Serial.println("Ring Close");
  servos[1].write(90);
  
  Serial.println("Little Close");
  servos[0].write(90);
}

void done(){
  Serial.println("Thumb");
  servos[4].write(180);
  
  Serial.println("Index Finger");
  servos[3].write(180);
  
  Serial.println("Middle Finger");
  servos[2].write(0);

  Serial.println("Ring Close");
  servos[1].write(180);
  
  Serial.println("Little Close");
  servos[0].write(180);
}

void ok(){
  Serial.println("OK");

  Serial.println("Little Finger");
  servos[0].write(180);
  delay(20);  
  
  Serial.println("Ring Finger");
  servos[1].write(180);
  delay(20);  
  
  Serial.println("Middle Finger");
  servos[2].write(180);
  delay(20);  
 
  Serial.println("Index Finger");
  servos[3].write(180);
  delay(20);

  Serial.println("thumb Open");
  servos[4].write(0);
  delay(20);
}

void please(){
  Serial.println("Please");

  Serial.println("Little Finger");
  servos[0].write(180);
  delay(20);  
  
  Serial.println("Ring Finger");
  servos[1].write(180);
  delay(20);  
  
  Serial.println("Middle Finger");
  servos[2].write(180);
  delay(20);  
 
  Serial.println("Index Finger");
  servos[3].write(0);
  delay(20);

  Serial.println("thumb Open");
  servos[4].write(180);
  delay(20);
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

  for(int i = 0; i < servoCount; ++i) {
        if(!servos[i].attach(servosPins[i])) {
            Serial.print("Servo ");
            Serial.print(i);
            Serial.println("attach error");
        }
    }
    
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

    // Route for root ("/")
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    String html = "<html><body style=\"display: flex; flex-direction: column; \">";
    //html += "<h1 style=\"color: #ff378F9F;\">Hand Angle Control</h1>";

    html += "<div style=\"text-align: center;\">"; // Center align the content

    // Add image
    //html += "<img src=\"/logo2.png\" alt=\"Image\" style=\"width: 200px;\"><br>";

    // Create sliders for each servo motor
    html += "<h1 style=\"color: #1C95AB; \">Thumb</h1>";
    html += "<input type=\"range\" min=\"0\" max=\"180\" step=\"1\" value=\"90\" "
            "oninput=\"updateServo(this.value, " + String(0) + ")\"><br>";
    html += "<span id=\"servoValue" + String(0) + "\">90</span><br><br>";

    html += "<h1 style=\"color: #1C95AB; \">Index Finger</h1>";
    html += "<input type=\"range\" min=\"0\" max=\"180\" step=\"1\" value=\"90\" "
            "oninput=\"updateServo(this.value, " + String(1) + ")\"><br>";
    html += "<span id=\"servoValue" + String(1) + "\">90</span><br><br>";

    html += "<h1 style=\"color: #1C95AB; \">Middle Finger</h1>";
    html += "<input type=\"range\" min=\"0\" max=\"180\" step=\"1\" value=\"90\" "
            "oninput=\"updateServo(this.value, " + String(2) + ")\"><br>";
    html += "<span id=\"servoValue" + String(2) + "\">90</span><br><br>";

    html += "<h1 style=\"color: #1C95AB; \">Ring Finger</h1>";
    html += "<input type=\"range\" min=\"0\" max=\"180\" step=\"1\" value=\"90\" "
            "oninput=\"updateServo(this.value, " + String(3) + ")\"><br>";
    html += "<span id=\"servoValue" + String(3) + "\">90</span><br><br>";

    html += "<h1 style=\"color: #1C95AB; \">Little Finger</h1>";
    html += "<input type=\"range\" min=\"0\" max=\"180\" step=\"1\" value=\"90\" "
            "oninput=\"updateServo(this.value, " + String(4) + ")\"><br>";
    html += "<span id=\"servoValue" + String(4) + "\">90</span><br><br>";

    html += "<h1 style=\"color: #1C95AB; \">All Fingers</h1>";
    html += "<input type=\"range\" min=\"0\" max=\"180\" step=\"1\" value=\"90\" "
            "oninput=\"updateServo(this.value, " + String(6) + ")\"><br>";
    html += "<span id=\"servoValue" + String(6) + "\">90</span><br><br>";

    html += "</div>";

    html += "<script>";
    html += "function updateServo(value, index) {";
    html += "var xhr = new XMLHttpRequest();";
    html += "xhr.open('GET', '/servo?index=' + index + '&value=' + value, true);";
    html += "xhr.send();";
    html += "document.getElementById('servoValue' + index).innerHTML = value;";
    html += "}";
    html += "</script>";
    html += "</body></html>";
    request->send(200, "text/html", html);
  });

  // Route to handle servo control
  server.on("/servo", HTTP_GET, [](AsyncWebServerRequest *request){
    int servoIndex = request->getParam("index")->value().toInt();
    int servoValue = request->getParam("value")->value().toInt();

    if (servoIndex == 6) {
      Serial.println("servoIndex angles");
      Serial.println(servoIndex);
      Serial.println("servoValue");
      Serial.println(servoValue);
      for (int i = 0; i < servoCount; i++){
        servos[i].write(servoValue);
        request->send(200, "text/plain", "Servo " + String(servoIndex) + " set to " + String(servoValue));
      }
    }
    else if (servoIndex >= 0 && servoIndex < servoCount) {
      Serial.println("servoIndex angles");
      Serial.println(servoIndex);
      Serial.println("servoValue");
      Serial.println(servoValue);
      servos[servoIndex].write(servoValue);
      request->send(200, "text/plain", "Servo " + String(servoIndex) + " set to " + String(servoValue));
    }
    else {
      request->send(400, "text/plain", "Invalid servo index");
    }
  });

  // Start server
  server.begin();
}

void loop(){

    if (Firebase.ready() && (millis() - sendDataPrevMillis > 1000 || sendDataPrevMillis == 0)) {
         sendDataPrevMillis = millis();
        
        if (Firebase.RTDB.getInt(&fbdo, "/handStatus")) {
          hand = fbdo.intData();
          if (hand == 100) {
            Serial.println("No Action");
          }
          else if (hand == 18) {
            Serial.println(hand);
            servoMotorClose();
          }
          else if (hand == 17) {
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
          else if (hand == 16) {
            Serial.println(hand);
            please();
          }
        }
        else {
          Serial.println(fbdo.errorReason());
        }
    }
    
}
