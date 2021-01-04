#include <FirebaseESP32.h>
#include <FB_HTTPClient32.h>
#include <FirebaseJson.h>
#include <WiFi.h>
#include "FirebaseESP32.h"

#define FIREBASE_HOST "https:REALTIME_DATABASE_URL"
#define FIREBASE_AUTH "AUTH_KEY"
#define WIFI_SSID "WIFI_NAME"
#define WIFI_PASSWORD "WIFI_PASSWORD"
// define firebase data object
FirebaseData firebaseData;
FirebaseJson json;
int Data;
int SendingDB;


void setup () {
  Serial.begin(115200);
  disableCore0WDT();
  disableCore1WDT();
  
  
  
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
  //Set database read timeout to 1 minute (max 15 minutes)
  Firebase.setReadTimeout(firebaseData, 1000 * 60);
  //tiny, small, medium, large and unlimited.
  //Size and its write timeout e.g. tiny (1s), small (10s), medium (30s) and large (60s).
  Firebase.setwriteSizeLimit(firebaseData, "tiny");
  Serial.println("------------------------------------");
  Serial.println("Connected...");
  xTaskCreatePinnedToCore(Task1, "TSK1", 8192, NULL, 1, NULL, 0);
  xTaskCreatePinnedToCore(Task2, "TSK2", 8192, NULL, 1, NULL, 0);
  xTaskCreatePinnedToCore(Task3, "TSK3", 8192, NULL, 1, NULL, 0);
}

void loop()
{
  
}
void Task1(void *pvParameters)  {
   (void) pvParameters;
   
  
    while (1){
      int APIR;
      int DPIR=0;
      DPIR = digitalRead(33);
      APIR = analogRead(33);
      Data=APIR;
      Serial.printf("digital = %d, analog= %d\n", DPIR,APIR); 
      vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
    
}

void Task2(void *pvParameters)  { 
  (void) pvParameters;
  int underData;  
  
  while(1){
    underData = Data;
    if (underData >= 3000 ){
      SendingDB =1;
      Serial.println("Should be one");
    } else { 
      SendingDB = 0;
      Serial.println("Should be Zero");
    }
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
  
}



void Task3(void *pvParameters)  {
 
  (void) pvParameters;
    while(1) {
      Firebase.setInt(firebaseData, "/DATA",SendingDB);
      Serial.println("Data sent");
     vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}
