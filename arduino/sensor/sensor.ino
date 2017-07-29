/*
 Humidity Sensor - Copyright (c) 2017 Adamo Morone

 Sends a message to server using bluetooth device.
 The message is a reading from soil humidity sensor.

 Created 25 Feb 2017
 by Adamo Morone
 */

/*****
* TODO: Make it works with 1+ sensor at same time.
*****/

#include <SoftwareSerial.h>

/*
  Connect BT module TX to D10
  Connect BT module RX to D11
  Connect BT Vcc to 5V, GND to GND
*/

// Time definitions
const long oneSecond = 1000;  // a second is a thousand milliseconds
const long oneMinute = oneSecond * 60;
const long oneHour   = oneMinute * 60;
const long oneDay    = oneHour * 24;

//Sets the blutooth shield.
SoftwareSerial BT(2, 3);

//Value captured by sensor will be here
int sensor1;

//Name of the sensors that will be used.
String sensorName= "1";

/*
 * Function: setup
 * ----------------------------
 *   Initial set-up of circuit.
 */
void setup() {
   //Starts reading bluetooth device.
   BT.begin(9600);
   Serial.begin(9600);
}


void loop() {

    //Reads the sensor data.
    sensor1 = analogRead(0);

    // Sends the data over Bluetooth to server,
    BT.print(sensorName + "|" + sensor1 + "|");
    Serial.print(sensorName + "|" + sensor1 + "|\n");

    // Wait for the next read.
    delay(oneHour);
  
}
