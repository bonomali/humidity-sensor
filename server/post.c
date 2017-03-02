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

/*
 * Function: noop_cb
 * ----------------------------
 *   Writes the curl_easy_perform default output to nothing.
 *
 *   message: The message that will be printed 
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
int postToURL(char *message)
{
  CURL *curl;
  CURLcode res;
  struct curl_slist *list = NULL;
 
  /* In windows, this will init the winsock stuff */ 
  curl_global_init(CURL_GLOBAL_ALL);
 
  /* get a curl handle */ 
  curl = curl_easy_init();

  if(curl) {

    /*
    *
    * This is posting to IFTTT Maker applet.
    * Replace xxxxxxxxx in the URL bellow by
    * your access token.
    *
    * Check http://ifttt.com/maker for more information
    */
    curl_easy_setopt(curl, CURLOPT_URL, "https://maker.ifttt.com/trigger/humidity_sensor/with/key/xxxxxxxxxxxx");
    
    list = curl_slist_append(list, "Content-Type: application/json");
     
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, list);

    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, message);

    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, noop_cb);
 
    /* Perform the request, res will get the return code */ 
    res = curl_easy_perform(curl);
    /* Check for errors */ 
    if(res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
 
    /* Always cleanup */ 
    curl_easy_cleanup(curl);
    curl_slist_free_all(list); 
  }
  curl_global_cleanup();

  return 0;
}