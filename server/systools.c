/* ----------------------------------------------------------------------------
  HUMIDITY-SENSOR LOG LIB - Copyright (c) 2017 Adamo Morone

  This file was set to provide easy log texts to terminal and also to
  server.log file.

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
#include <time.h>
#include <string.h>
#include "post.h"


/*
 * Function: write_to_file
 * ----------------------------
 *   Writes the log to a file
 *
 *   message: The message that will be printed 
 *
 */
void write_to_file(char *message){
	FILE *f = fopen("server.log", "ab+");
	if (f == NULL)
	{
	    exit(1);
	}

	fprintf(f, "%s", message);
	fclose(f);
}

/*
 * Function: outputLog
 * ----------------------------
 *   Prints the log message to console and send it
 *	 to be written to a log file.
 *
 *   logType: Type of the log, according to funcion.
 *   message: The message that will be printed
 *
 */
void outputLog(char *logType, char *message){


	/* Timestamp vars */
	time_t timer;
	struct tm* timeInfo;
	time(&timer);
	char currentTime[26];
	

	/* Message log container */
	char msgLog[1024];
	
	

	/* Set up timestamp to use on log*/
	timeInfo = localtime(&timer);
	strftime(currentTime, sizeof(currentTime), "%Y-%m-%d %H:%M:%S", timeInfo);

	/* Set up log message format and content*/
	snprintf(msgLog, sizeof(msgLog), "<%s> [%s] - %s \n", logType, currentTime, message);

	/**************************************
	*
	*
	* Send log message to LOGGLY service.
	*
	*
	***************************************/
	postToLoggly(msgLog);


	/**************************************
	*
	*
	* Write log message to server.log file.
	*
	*
	***************************************/
	write_to_file(msgLog);

	/**************************************
	*
	*
	* Print log message on terminal.
	*
	*
	***************************************/
	printf("%s", msgLog);

}


/*
 * Function: SYS_LOG_INFO
 * ----------------------------
 *   Set the type of log that will be written to <INFO>
 *
 *   message: The message that will be printed 
 *
 */
void SYS_LOG_INFO(char *message){
	outputLog("INFO", message);
}


/*
 * Function: SYS_LOG_DEBUG
 * ----------------------------
 *   Set the type of log that will be written to <DEBUG>
 *
 *   message: The message that will be printed 
 *
 */
void SYS_LOG_DEBUG(char *message){
	outputLog("DEBUG", message);
}


/*
 * Function: SYS_LOG_ERROR
 * ----------------------------
 *   Set the type of log that will be written to <ERROR>
 *
 *   message: The message that will be printed 
 *
 */
void SYS_LOG_ERROR(char *message){
	outputLog("ERROR", message);
}


