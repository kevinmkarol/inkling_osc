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

#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>

#include "../libraries/hidapi/hidapi/hidapi.h"
#include "../osc_broadcaster/osc_broadcaster.h"
#include "../datatypes/inklingOSC.h"

/**
* Function that checks to see if Inkling is connected, and returns a
* handler to interact with it, or NULL if something goes wrong
**/
hid_device* get_inkling_device();

/**
* Function that intercepts all incoming data from the handler and forwards
* it as OSC to the ipAddress and port passed in
**/
void mac_inkling_listener(hid_device *handle, char* ipAddress, int port);

