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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

#include "inkling/inkling_listener.h"
#include "libraries/hidapi/hidapi/hidapi.h"

int main(int argc, char** argv)
{
	if(argc > 1)
	{
	    static struct option options[] =
		{
		  { "broadcast",        required_argument, 0, 'b' },
		};
	    
	    int arg = 0;
        int index = 0;
	    while ( arg != -1 )
		{
		  /* Make sure to list all short options in the string below. */
		  arg = getopt_long (argc, argv, "b", options, &index);
          char* address;
          
		  switch(arg)
		  {
		  	case 'b':
              address = argv[2];
		  	  if(address != NULL){
	            char* ipAddress;
	            int port;
	            char* delim = ":";
	            char* token;

	            ipAddress = strtok(address, delim);
	            port = atoi(strtok(NULL, delim));
	            
	            if(port != 0){
	              hid_device * inkling = get_inkling_device();
                  if(inkling != NULL){
	                mac_inkling_listener(inkling, ipAddress, port);
                  }else{
                    goto incorrectArguments;
                  }
	            }else{
                  goto incorrectArguments;
                }
		  	  }else{
                goto incorrectArguments;
              }
		  	  break;
            default:
              goto incorrectArguments;
		  }
		}
	}else{
      goto incorrectArguments;
    }
    
    incorrectArguments:
          puts("Incorrect invocation.  Please specify an ipAddress and port number in the form -b ipAddress:port");
}