#include <WiFiManager.h> 

void setup() {
    WiFi.mode(WIFI_STA); // explicitly set mode, esp defaults to STA+AP

    Serial.begin(115200);

    WiFiManager wm;

    bool res;
   
    res = wm.autoConnect("AutoConnectAP","password"); 

    if(!res) {
        Serial.println("Failed to connect");

    } 
    else {
      
        Serial.println("connected.)");
    }

}

void loop() {
    // put your main code here, to run repeatedly:   
}
