#include <WiFi.h>
#include <PubSubClient.h>
#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN  5 
#define RST_PIN 27

MFRC522 rfid(SS_PIN, RST_PIN);

const char* ssid = "AndroidAP2B58";
const char* password =  "thanish13";
const char* mqtt_server = "test.mosquitto.org"; 
int mqtt_port = 1883;

 
WiFiClient espClient;
PubSubClient client(espClient);

 
void setup_wifi() {
 
 delay(10);
 Serial.println();
 Serial.print("Connecting to ");
 Serial.println(ssid);
 
 WiFi.begin(ssid, password);
 
 while (WiFi.status() != WL_CONNECTED) {
 delay(500);
 Serial.print(".");
 }
 
 Serial.println("");
 Serial.println("WiFi connected");
 Serial.println("IP address: ");
 Serial.println(WiFi.localIP());
}
 
void setup() { 
 Serial.begin(115200);
 setup_wifi();
 client.setServer(mqtt_server, mqtt_port);
 Serial.println("Connected ");
 Serial.print("MQTT Server ");
 Serial.print(mqtt_server);
 Serial.print(":");
 Serial.println(String(mqtt_port)); 
 Serial.print("ESP32 IP ");
 Serial.println(WiFi.localIP());
 SPI.begin();
 rfid.PCD_Init();  
}

void reconnect() {
 // Loop until we're reconnected
 while (!client.connected()) {
 Serial.print("Attempting MQTT connection...");
 if (client.connect("ESP32Client")) {
 
 Serial.println("connected");
 } 
 else {
 Serial.print("failed, rc=");
 Serial.print(client.state());
 Serial.println(" try again in 5 seconds");
 delay(5000);
 }
 }
}
void loop() {
 if (!client.connected()) {
 reconnect();
 }
 client.loop();
 rfidloop();
}

void rfidloop() {
  if (rfid.PICC_IsNewCardPresent()) { 
    if (rfid.PICC_ReadCardSerial()) {
      String rfid_uid = "";
      for (int i = 0; i < rfid.uid.size; i++) {
        String uid_part = String(rfid.uid.uidByte[i], HEX); 
        rfid_uid += uid_part;
    }
    Serial.println(rfid_uid);
    String comsg;
    comsg=rfid_uid;
    client.publish("test", (char*) comsg.c_str());
    rfid.PICC_HaltA(); 
    rfid.PCD_StopCrypto1(); 
    }
  }
}
