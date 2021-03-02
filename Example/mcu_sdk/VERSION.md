**-----------------------------------Revised Version---------------------------------------

** Version : v2.5.4
** Date    : 2020.4.15.
** Description: 1: add support for multiple map data stream data transmission
			2: add file package download function
			3: the default choice of distribution network mode is changed to special distribution network (anti-mis-touch working mode)
			4: fix the problem with the definition of the result variable in the data_handle function
			5: fixed some inconsistent function definitions and declarations
			6: fixed an uninitialized length variable in the OTA data handler
			7: modify the wifi_uart_write_frame function to add the passed frame version number parameter
			8: modify the weather service field to support the weather forecast function
			9: add voice module related protocol
			10: add module extension service
			11: add bluetooth function
			12: add product information mt and n fields
			13: add network status 7
			14:modify code comment format



** Version : v2.5.3
** Date    : 2019.11.26.
** Description: 1:Added infrared status notification
                2:Add infrared into transceiver production test
		        3:Fixed a BUG in the serial port data receiving function uart_receive_input (unable to tell if one of the caches is full)
                4:Modify the array name of the serial port data cache and the name of the length macro definition
		   
** Version : v2.5.2
** Date    : 2019.7.5.
** Description: 1:Add WiFi functionality test (connection specified route)
                2:To simplify the flow service process, users only need to invoke the flow service transport interface to consume the flow service
		        3:Increased synchronous escalation instruction
                4:Added command to get current wifi network status
                5:Added fetch green time command
                6:Optimize the ota upgrade process so that users can choose the transmission packet size when starting the ota upgrade
                7:Added command to get module MAC address
		   
** Version : v2.5.1
** Date    : 2018.10.27.
** Description: 1:Turn off streaming service by default
                2:Increase 03 protocol wifi status macro definition
		        3:Update and modify some function comments
		   

** Version: v2.5.0
** Date     : 2018.4.18

# Version: v2.5.0
# Date     : 2018.4.18
# Description: 
## 1:The protocol version is changed to 0x03
## 2:Increase WIFI module heartbeat off function
## 3:Increase weather function

# Version: v2.3.8
# Date      : 2018.1.17
# Description: 
## 1:Variables added volatile to prevent compiler optimization
## 2:Add #error hint

# Version: v2.3.7
# Date     : 2017.4.18
# Description 1:Optimize serial queue reception processing

# Version: v2.3.6
# Date     : 2016.7.21
# Description: Upload background file to compressed package format,Fixed file name isMCU_SDK_V2.zip
##1:Fix getting local time error
##2:Add hex_to_bcd conversion function

# Version: v2.3.5
# Date     : 2016.6.3
# Description: Upload background file to compressed package format
##1:Modify the return protocol version to 0x01
##2:Firmware upgrade data offset is modified to 4 bytes

# Version: v2.3.4
# Date     : 2016 .5.26
# Description: Upload background file to compressed package format
##1:Optimize serial port parsing function
##2:Optimize compiler compatibility, cancel enum type definitions

# Version: v2.3.3
# Date     : 2016.5.24

# Description: Upload background file to compressed package format

##1:Modify mcu to get local time function
##2:Add wifi function test

# Version: v2.3.2
# Date     : 2016.4.23
# Description : 

##1:Optimize serial port data analysis
##2:Optimize the MCU firmware upgrade process
##3:Optimize the reporting process

# Version: v2.3.1
# Date     : 2016.4.15
# Description: 
##1:Optimize serial port data analysis
