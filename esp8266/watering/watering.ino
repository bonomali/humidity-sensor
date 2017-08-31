/*
 Humidity Sensor - Copyright (c) 2017 Adamo Morone
 Wait for a server message saying how many minutes
 the water pump should pump water.
 Created 30 Aug 2017
 by Adamo Morone
*/

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

ESP8266WebServer server;
uint8_t relay = 13;

char* ssid = "xxxxxxxx";
char* password = "xxxxxxxx";

// Time definitions
const long oneSecond    = 1000;  //A second is a thousand milliseconds
const long oneMinute    = oneSecond * 60;
const long fiveMinutes  = oneMinute * 5;
const long tenMinutes   = oneMinute * 10;
const long oneHour      = oneMinute * 60;
const long oneDay       = oneHour * 24;

void setup()
{
  pinMode(relay, OUTPUT);
  digitalWrite(relay, HIGH);


  IPAddress ip(192, 168, 1, 111); // Desired IP Address
  IPAddress gateway(192, 168, 1, 1); // Gateway
  IPAddress subnet(255, 255, 255, 0); // Subnet Mask
  
  WiFi.config(ip, gateway, subnet);

  WiFi.begin(ssid, password);

  Serial.begin(115200);
  while(WiFi.status()!=WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.print("IP Address: ");
  Serial.print(WiFi.localIP());

  server.on("/",[](){server.send(200, "text/plain", "Watering Service Online!");});
  server.on("/water", sendWater);

  server.begin();
}

void loop()
{
  server.handleClient();
}

void sendWater()
{
  // Usage example: http://192.168.1.111/water?wateringTime=1
  // Receives the number of minutes of watering.

  long totalTime = server.arg("wateringTime").toInt() * oneMinute;

  digitalWrite(relay, LOW);
  String message = "Watering for " + server.arg("wateringTime") + " minutes.";
  server.send(200, "text/plain", message);
  delay(totalTime);
  digitalWrite(relay, HIGH);
}

