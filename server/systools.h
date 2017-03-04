/* ----------------------------------------------------------------------------
  HUMIDITY-SENSOR HEADER FILE FOR SYSTOOLS - Copyright (c) 2017 Adamo Morone

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

void hs_print(const char* logtype, const char* function, const char* file, int line, const char* format, ...);

/* Function macros */
#define LOG(logtype,format,...)		hs_print(logtype, __func__, __FILE__, __LINE__, format, ##__VA_ARGS__)
#define LOG_DEBUG(format,...)		LOG("DEBUG", format, ##__VA_ARGS__)
#define LOG_INFO(format,...)		LOG("INFO",  format, ##__VA_ARGS__)
#define LOG_ERROR(format,...)		LOG("ERROR", format, ##__VA_ARGS__)

void write_to_file(char *message);
void outputLog(char *logType, char *message);
