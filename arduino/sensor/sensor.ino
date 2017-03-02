/*
 Humidity Sensor

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

//Sets the blutooth shield.
SoftwareSerial BT(11, 10);

//Value captured by sensor will be here
int sensor1;

//Both variables used to set interval between
//each reding.
long previousTime = 0;
long interval = 3600000; //1 hour
// long interval = 600000; //10 minutes

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
}

void loop() {

  // Gets the current time in millisecond
  unsigned long currentTime = millis();

  // Checks if the current time - time from last
  // iteration is higher to defined interval.
  if(currentTime - previousTime > interval){

    //Saves the last iteration time.
    previousTime = currentTime;
   
    //Reads the sensor data.
    sensor1 = analogRead(0);

    //Gets the percentage of humidity based
    //on calibration that was defined by me,
    //where 700 is the 100% wet and 0% is 
    //completely dry.
    double percentage = (sensor1/700.0)*100.0;


    // Sends the data over Bluetooth to server,
    BT.println(sensorName + "|" + analogRead(0) + "|" + percentage + '|');
  }
  
}
