#include <FirebaseESP32.h>
#include <FB_HTTPClient32.h>
#include <FirebaseJson.h>
#include <WiFi.h>
#include "FirebaseESP32.h"

#define FIREBASE_HOST "https://logic-30aa3.firebaseio.com/"
#define FIREBASE_AUTH "gnnU1dVHVeqoW76JTcXPah5aYXZUeGOlrK1sUKCb"
#define WIFI_SSID "Ooredoo_2.4Ghz_A7F51F"
#define WIFI_PASSWORD "AAMPFABB"
// define firebase data object
FirebaseData firebaseData;
FirebaseJson json;
int SensorPlace = A0;
int Data;
int SendingDB;

void setup () {
  Serial.begin(19200);
  disableCore0WDT();
  disableCore1WDT();
  
  pinMode(SensorPlace, INPUT);
  
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting to WIFI");
    while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("Connected to ");
  Serial.println(WIFI_SSID);
  Serial.print("IP Address is : ");
  Serial.println(WiFi.localIP());                                            //print local IP address
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);                              // connect to firebase
  Firebase.reconnectWiFi(true);
  xTaskCreatePinnedToCore(Task1, "TSK1", 1024, NULL, 1, NULL, 0);
  xTaskCreatePinnedToCore(Task2, "TSK2", 1024, NULL, 1, NULL, 0);
  xTaskCreatePinnedToCore(Task3, "TSK3", 1024, NULL, 1, NULL, 0);
}

void loop()
{
  
}



void Task1(void *pvParameters)
{
  (void) pvParameters;
  int ADC_Value;

  while(1)
  {
//    ADC_Value= analogRead(36);
      Data = 2;
      
      vTaskDelay(250 / portTICK_PERIOD_MS);
  }
}

void Task2(void *pvParameters) 
{
  (void) pvParameters;
 int underData;
 underData = Data;
  while(1)
  {
    if (underData > 1) {
      SendingDB = 1;
    }
    else {
      SendingDB = 0;
    }
    vTaskDelay(250 / portTICK_PERIOD_MS);
  }
    
}

void Task3(void *pvParameters)  {
  (void) pvParameters;

    while(1) {
      json.set("/SensorUpdate", SendingDB);
      Firebase.updateNode(firebaseData, "/logic", json);
      vTaskDelay(250 / portTICK_PERIOD_MS);
    }
}
