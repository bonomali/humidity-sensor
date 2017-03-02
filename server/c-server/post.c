/***************************************
* HUMIDITY-SENSOR POST LIB
*
* This file was set to post data to a
* URL.
* 
* Author: Adamo Morone - Mar/01/2017
***************************************/

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

    /*********
    *
    * This is posting to IFTTT Maker applet.
    * Replace xxxxxxxxx in the URL bellow by
    * your access token.
    *
    * Check http://ifttt.com/maker for more information
    *********/
    curl_easy_setopt(curl, CURLOPT_URL, "https://maker.ifttt.com/trigger/humidity_sensor/with/key/lygrt0QwDHQw6b4kiSCCi");
    
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