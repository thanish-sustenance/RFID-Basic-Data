#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "AndroidAP2B58";
const char* password =  "thanish13";
const char* mqtt_server = "test.mosquitto.org"; /// MQTT Broker
int mqtt_port = 1883;
 
WiFiClient espClient;
PubSubClient client(espClient);

 
void setup_wifi() {
 
 delay(10);
 // We start by connecting to a WiFi network
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

 
}

 
void reconnect() {
 // Loop until we're reconnected
 while (!client.connected()) {
 Serial.print("Attempting MQTT connection...");
 if (client.connect("ESP32Client")) {
 
 Serial.println("connected");
 client.publish("outTopic", "hello world");
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
 
 delay(10000);
 
}
