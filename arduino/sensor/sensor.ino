#include <SoftwareSerial.h>

/*
	Connect BT module TX to D10
	Connect BT module RX to D11
	Connect BT Vcc to 5V, GND to GND
*/

SoftwareSerial BT(11, 10);
int sensor1;
String hash;
String sensorData;

void setup() {
   BT.begin(9600);
}

void loop() {
  sensor1 = analogRead(0);
  /*
	[
		{
			"name":"sensor_1",
			"data":"300"
		},
		{
			"name":"sensor_2",
			"data":"400"
		}
	]
	*/
  sensorData = String(sensor1);
  hash = "[{\"name\": \"sensor_1\", \"data\" :" + sensorData + " }]";

  BT.println(hash);
  /*
    TODO: Set this timer to get
    data each 15 minutes.

    The value above is for test only.
  */
  delay(1000);
}
