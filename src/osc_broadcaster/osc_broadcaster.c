/*
 * Copyright (C) 2016  Kevin M. Karol <kevinmkarol@gmail.com>
 *
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "osc_broadcaster.h"
#include "../libraries/tinyosc/tinyosc.h"

//Client UDP
#include <stdio.h> //printf
#include <string.h> //memset
#include <stdlib.h> //exit(0);
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUFLEN 1024  //Max length of buffer

void sendInklingOSC(int sockfd, dt_inkling_osc oscData)
{ 
  char buffer[BUFLEN];

  tosc_bundle bundle;
  uint64_t timeTag = 0;
  tosc_writeBundle(&bundle, timeTag, buffer, sizeof(buffer));
  
  tosc_writeNextMessage(&bundle, "/cord_xyp", "fff", oscData.coordinate.x, oscData.coordinate.y, oscData.coordinate.pressure);
  tosc_writeNextMessage(&bundle, "/tilt_txy", "fff", oscData.tilt.type,  oscData.tilt.x, oscData.tilt.y);
  
  int flags = 0;
  send(sockfd, buffer, tosc_getBundleLength(&bundle), flags);

}
