#include <SoftwareSerial.h>

SoftwareSerial BT(11, 10); 
// creates a "virtual" serial port/UART
// connect BT module TX to D10
// connect BT module RX to D11
// connect BT Vcc to 5V, GND to GND

void setup() {
   BT.begin(9600);

   pinMode(13, OUTPUT);
   pinMode(0,INPUT);

}

int sensor1; //First humidity sensor

void loop() {
  sensor1 = analogRead(0);
  BT.println(sensor1, DEC);
  /*
    TODO: Set this timer to get
    data each 15 minutes.

    The value above is for test only.
  */
  delay(1000);
}
