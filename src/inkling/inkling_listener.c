/*
 * Copyright (C) 2016 Kevin M. Karol <kevinmkarol@gmail.com>
 * Some code adapted from:
 * Copyright (C) 2013  Roel Janssen <roel@moefel.org>
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

#include "inkling_listener.h"

hid_device* get_inkling_device()
{
	const int wacomVendorID = 0x056a;
	const int wacomInclingID = 0x0221;

	//Find device using hidapi
	#define MAX_STR 255
	hid_device *found = NULL;

	// Enumerate and print the HID devices on the system
	struct hid_device_info *devs, *cur_dev;

	devs = hid_enumerate(0x0, 0x0);
	cur_dev = devs;
	while (cur_dev) {
	  if(cur_dev->vendor_id == wacomVendorID && cur_dev->product_id == wacomInclingID){
	    found = hid_open(cur_dev->vendor_id, cur_dev->product_id, NULL);
	    if(found == NULL)
	      puts("Failed to open hid to Inkling");
	    break;
	  }
	  cur_dev = cur_dev->next;
	}
	hid_free_enumeration(devs);

    if(found == NULL){
	  puts("Inkling device not found");
    }
	return found;
}


void mac_inkling_listener(hid_device *handle, char* ipAddress, int port)
{
    // Some kind of handshaking.
    // Values obtained by sniffing the USB connection between SketchManager and the device.
    unsigned char usb_data[33];
    memset (&usb_data, '\0', 33);
    memcpy (&usb_data, "\x80\x01\x03\x01\x02\x00\x00\x00", 8);

    int bytes = 0;
    bytes += hid_send_feature_report(handle, usb_data, 33);

    memcpy (&usb_data, "\x80\x01\x0a\x01\x01\x0b\x01\x00", 8);
    bytes += hid_send_feature_report(handle, usb_data, 33);

    memset (&usb_data, '\0', 33);
    bytes += hid_send_feature_report(handle, usb_data, 33);

    memcpy (&usb_data, "\x80\x01\x0b\x01\x00\x00\x00\x00", 8);
    bytes += hid_send_feature_report(handle, usb_data, 33);

    memcpy (&usb_data, "\x80\x01\x02\x01\x01\x00\x00\x00", 8);
    bytes += hid_send_feature_report(handle, usb_data, 33);

    memcpy (&usb_data, "\x80\x01\x0a\x01\x01\x02\x01\x00", 8);
    bytes += hid_send_feature_report(handle, usb_data, 33);

    memset (&usb_data, '\0', 33);
    bytes += hid_send_feature_report(handle, usb_data, 33);

    // Assume that the incorrect amount of bytes returned indicates a
    // handshake failure.
    if (bytes != 163)
    {
      puts ("Device handshake failed.");
      printf("bytes:%i\n", bytes);
      goto device_release;
    }
    
    //SET UP THE SOCKET TO BROADCAST DATA

    int sockfd = 0;

    struct sockaddr_in remoteAddr;
    sockfd = sizeof(remoteAddr);
    if((sockfd=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
    {
    	puts("Socket failed to open");
    	return;
    }
    
    memset((char *) &remoteAddr, 0, sizeof(remoteAddr));
    remoteAddr.sin_family = AF_INET;
    remoteAddr.sin_addr.s_addr = inet_addr(ipAddress);
    remoteAddr.sin_port = htons(port);

    if(inet_aton(ipAddress, &remoteAddr.sin_addr) == 0)
    {
      fprintf(stderr, "inet_aton() failed\n");
      exit(1);
    }
    //THIS CAST MIGHT NOT BE VALID - If something goes wrong check here
    connect(sockfd, (struct sockaddr *)&remoteAddr, sizeof(remoteAddr));

    int error = 0;
    socklen_t len = sizeof(error);
    int retval = getsockopt (sockfd, SOL_SOCKET, SO_ERROR, &error, &len);

    if(retval != 0){
      printf("%s","error getting socket code");
    }

    if(error != 0){
      printf("%s", "socket error");
    }
   
   
    //Listen for data
    while (1)
    {
      // Allocate some space for receiving data.
      unsigned char data[10];
      memset (&data, '\0', 10);


      // Request coordinate and pressure data.
      //puts("reading bytes");
      int bytesRead = hid_read_timeout(handle, data, 10, 1000);
      //printf("read:%i\n", bytesRead);
      
      if (bytesRead == -1)
        {
          puts ("Device disconnected.");
          goto device_release;
        }
        
      
      // Only process complete packets.
      if (bytesRead != 10) continue;
      // Only process "Pen" packets.
      if (data[0] != 0x02) continue;

      // The coordinate are segmented in 7 pieces of 1 byte.
      // An extra byte indicates which in which segment the pen is.
      // Thus, the right value can be obtained by this formula:
      // segment * 2^8 + x
      int x = data[2] * 256 + data[1];
      int y = (data[4] * 256 + data[3]) * -1;

      int tilt_x = data[8];
      int tilt_y = data[9];

      // Same formula applies to pressure data.
      // segment * 2^8 + pressure
      // "segment" can vary between 0 and 3, giving us values
      // between 0 and 1024.
      int pressure = data[6];
      pressure = pressure + 256 * data[7];

      //Send the data over OSC
      dt_inkling_osc oscData;
      oscData.coordinate.x = x;
      oscData.coordinate.y = y;
      oscData.coordinate.pressure = pressure;
      oscData.tilt.x = tilt_x;
      oscData.tilt.y = tilt_y;
      sendInklingOSC(sockfd, oscData);
    }
    
    device_release:
      hid_close(handle);
}
