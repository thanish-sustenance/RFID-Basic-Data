#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "AndroidAP2B58";
const char* password =  "thanish13";
const char* ID= "rfid";


IPAddress broker(192,168,55,69); 
WiFiClient wclient;

PubSubClient client(wclient); 
bool state=0;

void setup_wifi() {
  Serial.print("\nConnecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password); 

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect(ID)) {
      Serial.println("connected");
      Serial.println('\n');

    } else {
      Serial.println(" try again in 5 seconds");
  
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200); 
  delay(100);
  setup_wifi(); 
  client.setServer(broker, 1883);
}

void loop() {
  if (!client.connected())  
  {
    reconnect();
  }
  client.loop();
}
