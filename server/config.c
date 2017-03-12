/* ----------------------------------------------------------------------------
  HUMIDITY-SENSOR Config Lib - Copyright (c) 2017 Adamo Morone

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
#include <stdlib.h>
#include <libconfig.h>
#include "systools.h"

config_t              cfg;
config_setting_t      *IFTTTsetting;
config_setting_t      *LOGGLYsetting; 
config_setting_t      *THINGSPEAKsetting;

const char            *IFTTTtoken;
const char            *IFTTTeventName;

const char            *LOGGLYtoken;
const char            *THINGSPEAKtoken;

int                   IFTTTactive;
int                   LOGGLYactive;
int                   THINGSPEAKactive;

void ReadConfigCFG() 
{

  config_init(&cfg);

  /* Read the file.*/
  if(!config_read_file(&cfg, "config.cfg"))
  {
    fprintf(stderr, "%s:%d - %s\n", config_error_file(&cfg), config_error_line(&cfg), config_error_text(&cfg));
    config_destroy(&cfg);
    LOG_ERROR("Config file not found!");
  }

  /* IFTTT Settings. */
  IFTTTsetting = config_lookup(&cfg, "ifttt");
  if(IFTTTsetting != NULL)
  {
    config_setting_lookup_string(IFTTTsetting, "token", &IFTTTtoken);
    config_setting_lookup_string(IFTTTsetting, "event_name", &IFTTTeventName);
    config_setting_lookup_int(IFTTTsetting, "active", &IFTTTactive);
    if(IFTTTactive==1)
      LOG_INFO("IFTTT service active [event_name: %s; token: %s;]", IFTTTeventName, IFTTTtoken);
  }

  /* LOGGLY Settings. */
  LOGGLYsetting = config_lookup(&cfg, "loggly");
  if(LOGGLYsetting != NULL)
  {
    config_setting_lookup_string(LOGGLYsetting, "token", &LOGGLYtoken);
    config_setting_lookup_int(LOGGLYsetting, "active", &LOGGLYactive);
    if(LOGGLYactive==1)
      LOG_INFO("LOGGLY service active [token: %s;]", LOGGLYtoken);
  }

  /* THINGSPEAK Settings. */
  THINGSPEAKsetting = config_lookup(&cfg, "thingspeak");
  if(THINGSPEAKsetting != NULL)
  {
    config_setting_lookup_string(THINGSPEAKsetting, "token", &THINGSPEAKtoken);
    config_setting_lookup_int(THINGSPEAKsetting, "active", &THINGSPEAKactive);
    if(THINGSPEAKactive==1)
      LOG_INFO("THING SPEAK service active [token: %s;]", THINGSPEAKtoken);
  }
}