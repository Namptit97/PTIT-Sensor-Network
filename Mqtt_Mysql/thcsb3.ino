#include "DHT.h"  
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#define DHTPIN 5
#define DHTTYPE DHT11
int sensor = A0;
int value = 0;
DHT dht(DHTPIN, DHTTYPE);
const char* ssid = "AndroidAP";
const char* password = "11011996";
const char* mqtt_server = "192.168.43.209";

WiFiClient espClient;
PubSubClient client(espClient);  

void setup() {
  
 Serial.begin(115200);
 Serial.println("DHT11 test!");
 Wifi();
 client.setServer(mqtt_server, 1883);
 pinMode(sensor,INPUT);
 dht.begin();
 
}

void Wifi() {
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

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect mqtt
    if (client.connect("ESP8266Client","huynam","huynam")) {
      Serial.println("connected");
      // Subscribe
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void loop() 
{
  
 int value=analogRead(sensor);
 int humidity = dht.readHumidity();
 int temperature = dht.readTemperature();

// Serial.print("Sensor: "); 
// Serial.print(value);
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  char Temp[8];
  sprintf(Temp, "%d",temperature);
  Serial.print("  Nhiet Do: ");
  Serial.print(Temp);
  client.publish("temperature", Temp);
  
  char Hum[8];
  sprintf(Hum, "%d", humidity);
  Serial.print("  Do Am: ");
  Serial.println(Hum);
  client.publish("humidity", Hum);
  
  delay(3000);
}
