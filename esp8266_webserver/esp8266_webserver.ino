#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "DHT.h"
#define DHTTYPE DHT11

const int ledPin1 = 16;
const int ledPin2 = 2;
const int DHTPin = 5;
int time_now;
//const char* ssid = "TP-LINK_AA04";
//const char* password = "48061582";
const char* ssid = "Lhm";
const char* password = "lhm12345";

DHT dht(DHTPin, DHTTYPE);
ESP8266WebServer server(80);
void setup() {
pinMode(ledPin1, OUTPUT);
pinMode(ledPin2, OUTPUT);
pinMode(DHTPin, OUTPUT);

Serial.begin(115200);
WiFi.begin(ssid, password); //Connect to the WiFi network

while (WiFi.status() != WL_CONNECTED) { //Wait for connection

delay(500);
Serial.println("Waiting to connect…");
}

Serial.print("IP address: ");
Serial.println(WiFi.localIP()); //Print the local IP

server.on("/on/led1", turnOn1);         //Associate the handler function to the path
server.on("/off/led1", turnOff1);        //Associate the handler function to the path
server.on("/toggle/led1", toggle1);   //Associate the handler function to the path
server.on("/on/led2", turnOn2);         //Associate the handler function to the path
server.on("/off/led2", turnOff2);        //Associate the handler function to the path
server.on("/toggle/led2", toggle2);   //Associate the handler function to the path

server.begin(); //Start the server
Serial.println("Server listening");
dht.begin();
time_now = millis();
}
void turnOn1(){
  digitalWrite(ledPin1, LOW);
  server.send(200, "text/plain", "LED on");  
}
void turnOff1(){
  digitalWrite(ledPin1, 1);
  server.send(200, "text/plain", "LED off");  
}
void toggle1(){
  digitalWrite(ledPin1, !digitalRead(ledPin1));
  server.send(200, "text/plain", "LED toggle");  
}
void turnOn2(){
  digitalWrite(ledPin2, LOW);
  server.send(200, "text/plain", "LED on");  
}
void turnOff2(){
  digitalWrite(ledPin2, 1);
  server.send(200, "text/plain", "LED off");  
}
void toggle2(){
  digitalWrite(ledPin2, !digitalRead(ledPin2));
  server.send(200, "text/plain", "LED toggle");  
}
void read_and_print_sensor_value(){
 float hum = dht.readHumidity();
 float temp = dht.readTemperature();
  if(isnan(temp) || isnan(hum)){
    temp = 25;
    hum = 76;
    Serial.println("faile to read DTH11, hardcode");
  }
  int light = analogRead(A0);
  Serial.print("temp = ");Serial.print(temp);Serial.println("*C"); 
  Serial.print("hum = ");Serial.print(hum);Serial.println("%");
  Serial.print("light_level = ");Serial.print(light);Serial.println("analog");
  Serial.println("");
}
void loop() {
    server.handleClient();
    if(millis() - time_now > 2000){
    time_now = millis();
    read_and_print_sensor_value();
  }
  }
