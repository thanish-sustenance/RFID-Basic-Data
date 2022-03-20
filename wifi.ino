#include "WiFi.h"
 
const char* ssid = "AndroidAP2B58";
const char* password =  "thanish13";
 
void setup() {
 
  Serial.begin(115200);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
 
  Serial.println("Connected to the WiFi network");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
 
}
 
void loop() {}
