#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WiFiUdp.h>

const char *ssid     = "DWIT-Hotspot";
const char *password = "@DWZone-hotspot1";

ESP8266WebServer server(80);

void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid,password);
    while(WiFi.status() != WL_CONNECTED){
      Serial.println("Connecting");
    delay(1000);
    }
    Serial.println("Connected to");
    Serial.println(WiFi.localIP());

    //server.on("/test",HTTP_GET,sendData);

    server.on("/test",HTTP_POST,receiveData);

    server.begin();

}

void loop() {
    server.handleClient();
}

// to send data to api

void sendData(){
    StaticJsonDocument<300> JSONData;
    // Use the object just like a javascript object or a python dictionary
    JSONData["key"] = "Value";
    // You can add more fields
    char data[300];
    // Converts the JSON object to String and stores it in data variable
    serializeJson(JSONData,data);
    // Set status code as 200, content type as application/json and send the data
  server.send(200,"application/json",data);
}