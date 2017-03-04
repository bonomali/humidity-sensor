/* ----------------------------------------------------------------------------
  HUMIDITY-SENSOR Bluetooth Lib - Copyright (c) 2017 Adamo Morone

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

#include <string.h>     // string function definitions
#include <unistd.h>     // UNIX standard function definitions
#include <fcntl.h>      // File control definitions
#include <termios.h>    // POSIX terminal control definitions
#include <errno.h>      // Error number definitions
#include "systools.h"
#include "regex.h"

int             BLUETOOTH;
int             n = 0;
char            buf[255];

void BluetoothInit()
{
  struct termios  tty;
  struct termios  tty_old;

  LOG_INFO("Opening device.");
  BLUETOOTH = open("/dev/tty.HC-05-DevB", O_RDONLY | O_NOCTTY | O_NONBLOCK);
  memset (&tty, 0, sizeof tty);

  /* Error Handling */
  if (tcgetattr(BLUETOOTH, &tty) != 0) {
    LOG_ERROR("Error %d from tcgetattr: %s!", errno, strerror(errno));;
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
  if (tcsetattr(BLUETOOTH, TCSANOW, &tty) != 0) {
    LOG_ERROR("Error %d from tcgetattr: %s!", errno, strerror(errno));;
  }

}

char * BluetoothRead()
{
  
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
      return buf;

    memset(buf, '\0', sizeof buf);
  }
  return NULL;
} 