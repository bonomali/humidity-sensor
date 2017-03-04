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


#include <stdio.h>
#include <stdlib.h>
#include <string.h>     // string function definitions
#include <errno.h>      // Error number definitions
#include <unistd.h>     // UNIX standard function definitions
#include <fcntl.h>      // File control definitions
#include <termios.h>    // POSIX terminal control definitions
#include <regex.h>
#include "post.h"
#include "systools.h"

/* The following is the size of a buffer to contain any error messages
   encountered when the regular expression is compiled. */

#define MAX_ERROR_MSG 0x1000

/* Compile the regular expression described by "regex_text" into
   "r". */

static int compile_regex (regex_t * r, const char * regex_text)
{
    int status = regcomp (r, regex_text, REG_EXTENDED|REG_NEWLINE);
    if (status != 0) {
  char error_message[MAX_ERROR_MSG];
  regerror (status, r, error_message, MAX_ERROR_MSG);
        printf ("Regex error compiling '%s': %s\n",
                 regex_text, error_message);
        return 1;
    }
    return 0;
}

/*
  Match the string in "to_match" against the compiled regular
  expression in "r".
 */

static int match_regex (regex_t * r, const char * to_match)
{
    /* "P" is a pointer into the string which points to the end of the
       previous match. */
    const char * p = to_match;
    /* "N_matches" is the maximum number of matches allowed. */
    const int n_matches = 10;
    /* "M" contains the matches found. */
    regmatch_t m[n_matches];

    while (1) {
        int i = 0;
        int nomatch = regexec (r, p, n_matches, m, 0);
        if (nomatch) {
            return 0;
        }
        for (i = 0; i < n_matches; i++) {
            int start;
            int finish;
            if (m[i].rm_so == -1) {
                break;
            }
            start = m[i].rm_so + (p - to_match);
            finish = m[i].rm_eo + (p - to_match);
            if (i == 0) {
                return 1;
            }
        }
        p += m[0].rm_eo;
    }
    return 0;
}


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
 *            via Bluetooth.
 *
 */
void parseMessage(char *message){


  char *sensor="";
  char *value="";
  char *delimiter = "|";
  int sensor_val;
  char percentage[10];

  sensor = strtok(message , delimiter);
  value = strtok(NULL, delimiter);
  sensor_val = atoi(value);

  snprintf(percentage, sizeof(percentage), "%2.2f", ((sensor_val/700.0)*100.0));

  SYS_LOG_DEBUG(value);
  
  /**************************************
  *
  *
  * Send humidity information to IFTTT.
  *
  *
  ***************************************/
  // postToIFTTT(sensor, percentage, sensor_val);
  

  /**************************************
  *
  *
  * Send humidity information to ThingSpeak.
  *
  *
  ***************************************/
  postToThingSpeak(percentage);

}



/*
 * Function: main
 * ----------------------------
 *   Connects to bluetooth device via serial
 *   port and keeps waiting for messages.
 */
int main() {

  SYS_LOG_INFO("Opening device... ");
  int BLUETOOTH = open("/dev/tty.HC-05-DevB", O_RDONLY | O_NOCTTY | O_NONBLOCK);
  SYS_LOG_INFO("Opened!");

  struct termios tty;
  struct termios tty_old;
  memset (&tty, 0, sizeof tty);

  /* Error Handling */
  if (tcgetattr(BLUETOOTH, &tty) != 0) {
    SYS_LOG_ERROR("Error on read Bluetooth.");
    return 1;
  }

  /* Save old tty parameters */
  tty_old = tty;

  /* Set Baud Rate */
  cfsetospeed (&tty, (speed_t)B9600);
  cfsetispeed (&tty, (speed_t)B9600);

  /* Setting other Port Stuff */
  tty.c_cflag     &=  ~PARENB;        // Make 8n1
  tty.c_cflag     &=  ~CSTOPB;
  tty.c_cflag     &=  ~CSIZE;
  tty.c_cflag     |=  CS8;

  tty.c_cflag     &=  ~CRTSCTS;       // no flow control
  tty.c_cc[VMIN]  =   1;
  tty.c_cc[VTIME] =   5;
  tty.c_cflag     |=  CREAD | CLOCAL; // turn on READ & ignore ctrl lines

  /* Make raw */
  cfmakeraw(&tty);

  /* Flush Port, then applies attributes */
  tcflush(BLUETOOTH, TCIFLUSH);
  if ( tcsetattr ( BLUETOOTH, TCSANOW, &tty ) != 0) {
    SYS_LOG_ERROR("Error on flush port.");
    return 1;
  }

  int n = 0;
  char buf[255];

  SYS_LOG_INFO("Starting to read data...");
  do {
    n = read(BLUETOOTH, &buf, sizeof buf);

    if ((n >= 4) && (n <= 7)) {

      /* 
          Check if information comming from Arduino is valid
          using regex. 
      */
      int regexResult = 0;
      regex_t r;
      compile_regex(&r, "^([0-5]).([1-9][0-9]{0,2}|1000).$");
      regexResult = match_regex(&r, buf);
      regfree(&r);

      if(regexResult==1)
        parseMessage(buf);

      memset(buf, '\0', sizeof buf);

    }

    usleep(999000);  /* sleep for 1 second */

  } while(1);

  return 0;
}
