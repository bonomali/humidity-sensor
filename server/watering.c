/* ----------------------------------------------------------------------------
  HUMIDITY-SENSOR WATERING SERVICE LIB - Copyright (c) 2017 Adamo Morone

  This file was set to check if the plant needs water.

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
  
  Author: Adamo Morone - Aug/30/2017
   ----------------------------------------------------------------------------
*/

#include <stdio.h>
#include <curl/curl.h>

#include "systools.h"
#include "post.h"
#include "config.h"

/*
 * Function: waterPlant
 * ----------------------------
 *   Check if the humidity is low and
 *   sends the command to the watering 
 *   service start.
 *
 *   message: The message that will be posted 
 *
 */
void waterPlant(int sensor_val, char *percentage)
{
    if(sensor_val < 420){
        char urlGET[100];
        char *totalTime = "5";
        LOG_INFO("Watering plant! [%s]", percentage);
        snprintf(urlGET, sizeof(urlGET), "http://%s/water?wateringTime=%s", WATERINGurl, totalTime);
        postToURL(urlGET, "Content-Type: text/plain", "");
    }
}