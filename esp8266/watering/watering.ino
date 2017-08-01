#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

ESP8266WebServer server;
uint8_t relay = 13;

char* ssid = "";
char* password = "";

void setup()
{
  pinMode(relay, OUTPUT);
  digitalWrite(relay, HIGH);
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

  server.on("/",[](){server.send(200, "text/plain", "Hello World");});
  server.on("/water", sendWater); 
  server.begin();
}

void loop()
{
  server.handleClient();
}

void sendWater()
{
  digitalWrite(relay, LOW);
  server.send(204, "");
  delay(5000);
  digitalWrite(relay, HIGH);
}

