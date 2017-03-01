#include <stdio.h>
#include <stdlib.h>
#include <string.h>     // string function definitions
#include <errno.h>      // Error number definitions
#include <unistd.h>     // UNIX standard function definitions
#include <fcntl.h>      // File control definitions
#include <termios.h>    // POSIX terminal control definitions
#include "post.h"
#include "systools.h"


void parseMessage(char *message){

  char sensor[32], value[32], percentage[32];

  strcpy(sensor, strtok(message , "|"));
  strcpy(value, strtok(NULL, "|"));
  strcpy(percentage, strtok(NULL, "|"));
  
  char jsonToPost[500];

  if(atoi(value) < 300)
    snprintf(jsonToPost, sizeof(jsonToPost), "{\"value1\": \"Estou morrendo de sede! Me regue por favor! (Sensor: %s | Umidade: %s%c)\"}", sensor, percentage, 37);
  else if(atoi(value) > 700)
    snprintf(jsonToPost, sizeof(jsonToPost), "{\"value1\": \"Que me matar afogada! Estou cheia de água! (Sensor: %s | Umidade: %s%c)\"}", sensor, percentage, 37);
  else if((atoi(value) >= 300) && (atoi(value) <= 700))
    snprintf(jsonToPost, sizeof(jsonToPost), "{\"value1\": \"Estou bem por enquanto! (Sensor: %s | Umidade: %s%c)\"}", sensor, percentage, 37);

  SYS_LOG_INFO(jsonToPost);

  postToTwitter(jsonToPost);
}


int main() {
  /**
  * TODO: Clean BT memory buffer on start to prevent crash.
  **/
  SYS_LOG_INFO("Opening device... ");
  int BLUETOOTH = open("/dev/tty.HC-05-DevB", O_RDONLY | O_NOCTTY | O_NONBLOCK);
  SYS_LOG_INFO("Opened!");

  struct termios tty;
  struct termios tty_old;
  memset (&tty, 0, sizeof tty);

  /* Error Handling */
  if (tcgetattr(BLUETOOTH, &tty) != 0) {
    SYS_LOG_INFO("Error on read Bluetooth.");
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
    SYS_LOG_INFO("Error on flush port.");
  }

  int n = 0;
  char buf[255];

  SYS_LOG_INFO("Starting to read data...");
  do {
    n = read( BLUETOOTH, &buf, sizeof buf);

    if (n > 0) {
      char destination[100];
      strcpy(destination, buf);
      parseMessage(destination);
      memset(&buf, '\0', sizeof buf);
    }

    usleep(500000);  /* sleep for 100 milliSeconds */
  } while(1);
}
