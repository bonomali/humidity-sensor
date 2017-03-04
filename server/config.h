/* ----------------------------------------------------------------------------
  HUMIDITY-SENSOR Config Lib - Copyright (c) 2017 Adamo Morone

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
 #include <libconfig.h>

 void ReadConfigCFG();

 extern config_t              cfg;
 extern config_setting_t      *IFTTTsetting;
 extern config_setting_t      *LOGGLYsetting; 
 extern config_setting_t      *THINGSPEAKsetting;

 extern const char            *IFTTTtoken;
 extern const char            *IFTTTeventName;

 extern const char            *LOGGLYtoken;
 extern const char            *THINGSPEAKtoken;

 extern int                   IFTTTactive;
 extern int                   LOGGLYactive;
 extern int                   THINGSPEAKactive;