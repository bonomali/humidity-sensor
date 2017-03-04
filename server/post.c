/* ----------------------------------------------------------------------------
  HUMIDITY-SENSOR POST LIB - Copyright (c) 2017 Adamo Morone

  This file was set to post data to a URL.

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


#include <stdio.h>
#include <curl/curl.h>
#include "systools.h"

/*
 * Function: noop_cb
 * ----------------------------./
 *   Writes the curl_easy_perform default output to nothing.
 *
 */
size_t noop_cb(void *ptr, size_t size, size_t nmemb, void *data) {
  return size * nmemb;
}
 

/*
 * Function: postToURL
 * ----------------------------
 *   Posts a json string msg to URL.
 *
 *   message: The message that will be posted 
 *
 */
int postToURL(char *url, char *header, char *data)
{
  CURL *curl;
  CURLcode res;
  struct curl_slist *list = NULL;
 
  /* In windows, this will init the winsock stuff */ 
  curl_global_init(CURL_GLOBAL_ALL);
 
  /* get a curl handle */ 
  curl = curl_easy_init();

  if(curl) {
    curl_easy_setopt(curl, CURLOPT_URL, url);
    
    list = curl_slist_append(list, header);
     
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, list);

    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data);

    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &noop_cb);
 
    /* Perform the request, res will get the return code */ 
    res = curl_easy_perform(curl);

    /* Check for errors */ 
    if(res != CURLE_OK)
      LOG_ERROR("curl_easy_perform() failed: %s", curl_easy_strerror(res));
 
    /* Always cleanup */ 
    curl_easy_cleanup(curl);
    curl_slist_free_all(list); 
  }
  curl_global_cleanup();

  return 0;
}

void postToIFTTT(char *sensor, char *percentage, int sensor_val){
    /*
    *
    * This is posting to IFTTT Maker applet.
    * Replace xxxxxxxxx in the URL bellow by
    * your access token.
    *
    * Check http://ifttt.com/maker for more information
    */

  LOG_INFO("Sending data do IFTTT [%s, %s, %d]", sensor, percentage, sensor_val);
  char jsonToPost[1024];

  if(sensor_val < 300)
    snprintf(jsonToPost, sizeof(jsonToPost), "{\"value1\": \"Estou morrendo de sede! Me regue por favor! (Sensor: %s | Umidade: %s%c)\"}", sensor, percentage, 37);
  else if(sensor_val > 700)
    snprintf(jsonToPost, sizeof(jsonToPost), "{\"value1\": \"Que me matar afogada! Estou cheia de água! (Sensor: %s | Umidade: %s%c)\"}", sensor, percentage, 37);
  else if((sensor_val >= 300) && (sensor_val <= 700))
    snprintf(jsonToPost, sizeof(jsonToPost), "{\"value1\": \"Estou bem por enquanto! (Sensor: %s | Umidade: %s%c)\"}", sensor, percentage, 37);
  
  postToURL("https://maker.ifttt.com/trigger/humidity_sensor/with/key/XXXXXXXXXXX", "Content-Type: application/json", jsonToPost);
}

void postToThingSpeak(char *percentage){
  char urlGET[100];
  LOG_INFO("Sending data do Thing Speak [%s]", percentage);
  snprintf(urlGET, sizeof(urlGET), "https://api.thingspeak.com/update?key=XXXXXXXXXX&field1=%s", percentage);
  postToURL(urlGET, "Content-Type: text/plain", "");
}

void postToLoggly(char *data){
  postToURL("http://logs-01.loggly.com/bulk/XXXXXXXXXXX/tag/http/", "Content-Type: text/plain", data);
}



