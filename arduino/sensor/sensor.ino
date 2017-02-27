#include <SoftwareSerial.h>

/*
  Connect BT module TX to D10
  Connect BT module RX to D11
  Connect BT Vcc to 5V, GND to GND
*/

SoftwareSerial BT(11, 10);
int sensor1;
String hash;

int MINUTE = 60000;

void setup() {
   BT.begin(9600);
}

void loop() {
  sensor1 = analogRead(0);

  String message="";

  if(sensor1 < 300){
    message = "Socorro! Estou com sede, me dê água por favor";
  }else if((sensor1 >=300) && (sensor1<=700)){
    message = "Estou bem alimentada, não precisa se preocupar!";
  }else if(sensor1>700){
    message = "Quer me afogar?! Estou cheia de água!";
  }

  if(message!=""){
    hash = "{\"value1\" : \"" + message + "\"}";
    BT.println(hash);
  }
  
  delay(600000);
}
