/*************************************************** 
IAS - Instituto Superior Técnico
MSc in Biomedical Engineering

Rita Silva 86805
Vicente Garção 86810

This code uses MLX90614 
IR non-contact temperature sensor and NodeMCU ESP32 
 ****************************************************/

#include <Wire.h>
#include <Adafruit_MLX90614.h>

#include <Wire.h>
#include "Adafruit_MCP9808.h"


#include <HTTPClient.h>
#include <HTTPUpdate.h>
#include <HTTPClientESP32Ex.h>
#include <WiFiClientSecureESP32.h>
#include <ssl_client32.h>
#include <FirebaseESP32.h>
#include <FirebaseESP32HTTPClient.h>
#include <FirebaseJson.h>
#include <WiFi.h>
String path = "/ESP32_Device";

//1. Change the following info for WiFi connection
#define FIREBASE_HOST "id-esp32-nodemcu.firebaseio.com" //Change to your Firebase RTDB project ID e.g. Your_Project_ID.firebaseio.com
#define FIREBASE_AUTH "baInxcVZJOTS0RuPWdajiVgRGR8n9e1gcO9u9y9X" //Change to your Firebase RTDB secret password

const char* ssid = "MEO-E7CDAF_EXT";
const char* password = "811F97E84B";

//2. Define FirebaseESP8266 data object for data sending and receiving
FirebaseData firebaseData;


//3. Define built in LED in NodeMCU ESP32 board
#define LED_BUILTIN 2

  
void setup() {
  WiFi.disconnect();
  Serial.begin(115200);
  
  WiFi.begin(ssid, password);
  WiFi.setSleep(false);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  //4. Set your Firebase info
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

  //5. Enable auto reconnect the WiFi when connection lost
  Firebase.reconnectWiFi(true);

  
  //6. initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  
}

  //7. Define initial LED status (OFF)
  char state = LOW;

void loop() {

        if (state==HIGH){
        state=LOW;
        }
        else{
        state=HIGH;
        }
        digitalWrite(LED_BUILTIN, state);
        delay(1000);

        // For Variable Update, will change the variable "ContinuousDataRT" each time the loop() runs
        Firebase.setDouble(firebaseData, path + "/LED",state); 
        // Saves data in a list
        Firebase.pushDouble(firebaseData, path + "/LED_History",state);
          
          
      
  delay(1000);
}
