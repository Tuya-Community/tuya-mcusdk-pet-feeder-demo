
This MCU_SDK is an automatically generated MCU code based on the product features defined on the graffiti development platform. 
Based on this modification and supplement, the MCU program can be completed quickly.


MCU_SDK use guide document links：
https://docs.tuya.com/en/iot/device-development/access-mode-mcu/mcu-sdk-application-wifi/sdk-transplant


Development steps:


1: You need to configure according to the actual situation of the product (reset wifi button and wifi status indicator processing, 
    whether to support MCU upgrade, etc.), please modify this configuration in protocol.h;

2: To migrate this MCU_SDK, please check the migration steps in the protocol.c file and complete the migration correctly. 
    After the migration, please complete the data processing and data reporting part of the code to complete all wifi functions.

File overview:
This MCU_SDK consists of 7 files:

(1) protocol.h and protocol.c are required for you to modify. Detailed instructions for modification in the protocol.h and protocol.c files, please read them carefully.

(2) The wifi.h file is the total .h file. If you need to call the wifi internal function, please #include "wifi.h".

(3) system.c and system.h are wifi function implementation code, users do not need to modify.

(4) All the users in mcu_api.c and mcu_api.h need to call the function, the user does not need to modify.