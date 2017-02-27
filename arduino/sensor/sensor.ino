#include <SoftwareSerial.h>

/*
  Connect BT module TX to D10
  Connect BT module RX to D11
  Connect BT Vcc to 5V, GND to GND
*/

SoftwareSerial BT(11, 10);
int sensor1;
long previousTime = 0;
long interval = 600000; //10 minutes
String buf;
String sensorName= "1|";

void setup() {
   BT.begin(9600);
}

void loop() {

  unsigned long currentTime = millis();

  if(currentTime - previousTime > interval){

    previousTime = currentTime;
   
    sensor1 = analogRead(0);
    BT.println(sensorName + analogRead(0));
  }
  
}
