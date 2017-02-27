#include <SoftwareSerial.h>
SoftwareSerial BT(11, 10); 
// creates a "virtual" serial port/UART
// connect BT module TX to D10
// connect BT module RX to D11
// connect BT Vcc to 5V, GND to GND

void setup() {
  // put your setup code here, to run once:
   // Serial.begin(9600); //Set serial baud rate to 9600 bps
   // set the data rate for the SoftwareSerial port
   BT.begin(9600);
   Serial.begin(9600);

   pinMode(13, OUTPUT);
   pinMode(0,INPUT);

}

int sensor1; //First humidity sensor

void loop() {
  // put your main code here, to run repeatedly:
  sensor1 = analogRead(0);
  Serial.println(sensor1);
  BT.println(sensor1, DEC);
  delay(1000);
}
