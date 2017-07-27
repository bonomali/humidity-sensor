/* ----------------------------------------------------------------------------
  HUMIDITY-SENSOR SERVER - Copyright (c) 2017 Adamo Morone

  This file was set to receive messages from bluetooth device connected 
  to Arduino.

  The data consists on the soil humidity that arduino is in.

  This code is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public License
  as published by the Free Software Foundation; either version 2.1 of
  the License, or (at your option) any later version.

  This code is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Library General Public
  License along with this code; if not, see
  <http://www.gnu.org/licenses/>.
  Author: Adamo Morone - Mar/01/2017
   ----------------------------------------------------------------------------
*/


/** Standard Libs **/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>     // string function definitions
#include <unistd.h>     // UNIX standard function definitions


/** Custom Libs **/
#include "post.h"
#include "systools.h"
#include "regex.h"
#include "bluetooth.h"
#include "config.h"


/*
 * Function: parseMessage
 * ----------------------------
 *   Parses the message comming from bluetooth
 *   to three different variables:
 *
 *   sensor     -> Sensor number that the data is
 *                 comming from.
 *   value      -> The raw data from humidity sensor
 *   percentage -> Humidity percentage according
 *                 to previous calibration.
 *
 *   message: The full message that is comming
 *            via BluetoothBluetooth.
 *
 */
void parseMessage(char *message)
{


  char        *sensor="";
  char        *value="";
  char        *delimiter = "|";
  int         sensor_val;
  char        percentage[10];

  sensor = strtok(message , delimiter);
  value = strtok(NULL, delimiter);
  sensor_val = atoi(value);

  snprintf(percentage, sizeof(percentage), "%2.2f", ((sensor_val/700.0)*100.0));
  
  /* Send humidity information to IFTTT. */
  if(IFTTTactive==1)
    postToIFTTT(sensor, percentage, sensor_val);
  
  /* Send humidity information to ThingSpeak. */
  if(THINGSPEAKactive==1)
    postToThingSpeak(percentage);

}

/*
 * Function: printInit
 * ----------------------------
 *   Prints initial ascii art from file.
 */
void printASCIIImage()
{
  int c;
  FILE *file;
  file = fopen("server/logo.ascii", "r");
  if (file) {
    while ((c = getc(file)) != EOF)
        putchar(c);
    fclose(file);
  }
  puts("");
}


/*
 * Function: main
 * ----------------------------
 *   Connects to bluetooth device via serial
 *   port and keeps waiting for messages.
 */
int main() 
{
  printASCIIImage();
  LOG_INFO("Initializing Humidity Sensor server.");

  /** Read configuration file and set vars */
  LOG_INFO("Reading configuration file.");
  ReadConfigCFG();

  /** Init bluetooth reading */
  BluetoothInit();

  LOG_INFO("Start reading Bluetooth data.");
  do {
    char *buf = BluetoothRead();
    if(buf != NULL){
      parseMessage(buf);
    }
    sleep(1);
    //usleep(500);
  }while(1);

  return 0;
}
