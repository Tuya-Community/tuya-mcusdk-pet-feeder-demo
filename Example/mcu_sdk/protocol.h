/**********************************Copyright (c)**********************************
**                     All rights reserved (C), 2015-2020, Tuya
**
**                             http://www.tuya.com
**
*********************************************************************************/
/**
 * @file    protocol.h
 * @author  Tuya Team
 * @version v2.5.4
 * @date    2020.4.15
 * @brief                *******Very important, be sure to watch!!!********
 *          1. The user implements the data delivery/reporting function in this file.
 *          2. DP ID / TYPE and data processing functions require the user to implement according to the actual definition
 *          3. There are #err hints inside the function that needs the user to implement the code after starting some macro definitions. 
 *             Please delete the #err after completing the function.
 */


#ifndef __PROTOCOL_H_
#define __PROTOCOL_H_


/******************************************************************************
                 User related information configuration
******************************************************************************/
/******************************************************************************
                       1:Modify product information
******************************************************************************/
#define PRODUCT_KEY "cipl6jnvmul44klx"    //开发平台创建产品后生成的16位字符产品唯一标识

#define MCU_VER "1.0.0"         //User's software version for MCU firmware upgrade, MCU upgrade version needs to be modified



/*  Distribution mode selection, only three choices, Anti-touch mode is recommended  */
//#define CONFIG_MODE     CONFIG_MODE_DEFAULT             //Default working mode
//#define CONFIG_MODE     CONFIG_MODE_LOWPOWER            //Safe mode (low power working mode)
#define CONFIG_MODE     CONFIG_MODE_SPECIAL             // Anti-touch mode (special working mode)

/*  Set the opening time of network activity in low power working mode and special working mode,
    The define in the comment state will be processed for 3 minutes,Set data ranges that can be supported: 3~10 minutes  */
//#define CONFIG_MODE_DELAY_TIME    10         //Network activity time.   unit: minutes

/*  Special configuration for smart mode and AP mode.
    If you do not use this define, you switch between smart mode and AP mode    */
//#define CONFIG_MODE_CHOOSE        0         //Open both AP and smart distribution networks without user switching, and the corresponding distribution network state 0x06
//#define CONFIG_MODE_CHOOSE        1         //Use only AP network configuration mode

/******************************************************************************
                          2:Does the MCU require a firmware upgrade?                  
If you need to support MCU firmware upgrade, please open this macro
The MCU can call the mcu_firm_update_query() function in the mcu_api.c file to get the current MCU firmware update.

                        ********WARNING!!!**********
The current receive buffer is the size to turn off the firmware update function. 
The firmware upgrade package is 256 bytes.
If you need to enable this function, the serial receive buffer will become larger.
******************************************************************************/
//#define         SUPPORT_MCU_FIRM_UPDATE                 //Enable MCU firmware upgrade function (off by default)
/*  Firmware package size selection  */
#ifdef SUPPORT_MCU_FIRM_UPDATE
#define PACKAGE_SIZE                   0        //The package size is 256 bytes
//#define PACKAGE_SIZE                   1        //The package size is 512 bytes
//#define PACKAGE_SIZE                   2        //The package size is 1024 bytes
#endif
/******************************************************************************
                         3:Define the send and receive buffer:
          If the current RAM of the MCU is not enough, it can be modified to 24
******************************************************************************/
#ifndef SUPPORT_MCU_FIRM_UPDATE
#define WIFI_UART_RECV_BUF_LMT          16              //UART data receiving buffer size, can be reduced if the MCU has insufficient RAM
#define WIFI_DATA_PROCESS_LMT           24              //UART data processing buffer size, according to the user DP data size, must be greater than 24
#else
#define WIFI_UART_RECV_BUF_LMT          128             //UART data receiving buffer size, can be reduced if the MCU has insufficient RAM

/*  Select the appropriate UART data processing buffer size here 
    (select the buffer size based on the size selected by the above MCU firmware upgrade package and whether to turn on the weather service)  */
#define WIFI_DATA_PROCESS_LMT           1000             //UART data processing buffer size. If the MCU firmware upgrade is required, the single-packet size is 256, the buffer must be greater than 260, or larger if the weather service is enabled
//#define WIFI_DATA_PROCESS_LMT           600             //UART data processing buffer size. If the MCU firmware upgrade is required, the single-packet size is 512, the buffer must be greater than 520, or larger if the weather service is enabled
//#define WIFI_DATA_PROCESS_LMT           1200            //UART data processing buffer size. If the MCU firmware upgrade is required, the single-packet size is 1024, the buffer must be greater than 1030, or larger if the weather service is enabled

#endif

#define WIFIR_UART_SEND_BUF_LMT         48              //According to the user's DP data size, it must be greater than 48
/******************************************************************************
                        4:Define how the module works
Module self-processing:
          The wifi indicator and wifi reset button are connected to the wifi module (turn on the WIFI_CONTROL_SELF_MODE macro)
          And correctly define WF_STATE_KEY and WF_RESET_KEY
MCU self-processing:
          The wifi indicator and wifi reset button are connected to the MCU (turn off the WIFI_CONTROL_SELF_MODE macro)
          The MCU calls the mcu_reset_wifi() function in the mcu_api.c file where it needs to handle the reset wifi, and can call the mcu_get_reset_wifi_flag() function to return the reset wifi result
          or call the mcu_set_wifi_mode(WIFI_CONFIG_E mode) function in the mcu_api.c file in the wifi mode, and call mcu_get_wifi_work_state() to return the setting wifi result.
******************************************************************************/
//#define         WIFI_CONTROL_SELF_MODE                       //Wifi self-processing button and LED indicator; if the MCU external button / LED indicator please turn off the macro
#ifdef          WIFI_CONTROL_SELF_MODE                      //Module self-processing
  #define     WF_STATE_KEY            14                    //Wifi module status indication button, please set according to the actual GPIO pin
  #define     WF_RESERT_KEY           0                     //Wifi module reset button, please set according to the actual GPIO pin
#endif

/******************************************************************************
                      5: Does the MCU need to support the time function?
Open this macro if needed and implement the code in mcu_write_rtctime in the Protocol.c file.
Mcu_write_rtctime has #err hint inside, please delete the #err after completing the function
Mcu can call the mcu_get_system_time() function to initiate the calibration function after the wifi module is properly networked.
******************************************************************************/
//#define         SUPPORT_MCU_RTC_CHECK                //Turn on time calibration

/******************************************************************************
                      6:Does the MCU need to support the wifi function test?                    
Please enable this macro if necessary, and mcu calls mcu_start_wifitest in mcu_api.c file when wifi function test is required.
And view the test results in the protocol_c file wifi_test_result function.
There is a #err hint inside wifi_test_result. Please delete the #err after completing the function.
******************************************************************************/
#define         WIFI_TEST_ENABLE                //Open WIFI production test function (scan designated route)

/******************************************************************************
                      7:Whether to turn on the weather function                   
Open this macro if needed, and in the protocol.c file weather_open_return_handle and weather_data_u\
Ser_handle two user handlers to achieve display and other code
#err hint in these two functions, delete the #err after completing the function

******************************************************************************/
//#define         WEATHER_ENABLE                  //Turn on weather function
#ifdef          WEATHER_ENABLE
/*  Tunable in the weather_choose array in the protocol.c file, and then write the number of open service types to this macro definition  */
#define         WEATHER_CHOOSE_CNT              4   //The number of required weather service types selected
/*  When the weather service is turned on, you can set this macro definition to select the number of days for the weather forecast, 
    with 1 representing the weather for the day (the forecast is not required to be set to 1), up to 7 days (cannot be set to 0 or greater than 7).  */
#define         WEATHER_FORECAST_DAYS_NUM       1   //Set the number of days for the weather forecast
#endif

/******************************************************************************
                      8:Whether to enable the WIFI module heartbeat off function
If you need to open this macro, call the wifi_heart_stop function in the mcu_api.c file to stop the heartbeat.
******************************************************************************/
//#define         WIFI_HEARTSTOP_ENABLE           //Turn on weather function

/******************************************************************************
                      9:Whether to support streaming service function
STREM_PACK_LEN is the size of a packet transferred by the stream service. Currently, the maximum part of the data that can be cached in the module serial port can reach 1024 bytes.
The data portion of a packet of map packet cannot exceed 1024 bytes, and 512 bytes per packet is recommended for each packet of map data.
******************************************************************************/
//#define         WIFI_STREAM_ENABLE              //Support for streaming service related functions
#ifdef WIFI_STREAM_ENABLE
#define         STREM_PACK_LEN                 256
#endif

/******************************************************************************
                      10:Whether the MCU needs to support wifi function test (connection designated route)
Turn on the macro if necessary, and the MCU calls mcu_start_connect_wifitest in the mcu_api.c file where wifi function test is needed, 
and views the test results in the wifi_connect_test_result function in protocol.c file,
There is a #err hint inside wifi_connect_test_result. Please delete the #err after completing the function.
******************************************************************************/
//#define         WIFI_CONNECT_TEST_ENABLE                //Open wifi function test (connection designated route)

/******************************************************************************
                      11:Whether the MCU needs to turn on the function of obtaining the current WIFI network status
Turn on the macro if desired, and the MCU calls mcu_get_wifi_connect_status in the mcu_api.c file where it is necessary to obtain the current WIFI networking status
And view the result in the wifi_test_result function in the protocol.c file,
Wifi_test_result has an internal #err prompt that is removed when the function is complete
******************************************************************************/
//#define         GET_WIFI_STATUS_ENABLE                  //Enable access to current WIFI network status

/******************************************************************************
                      12:Whether the MCU need to open the access module MAC address function
Turn on the macro if needed, and the MCU calls mcu_get_module_mac in the mcu_api.c file where it needs to get the module's MAC address
And in the protocol.c file mcu_get_mac function to view the results,
mcu_get_mac has a #err prompt inside, please delete the #err after the function is completed
******************************************************************************/
//#define         GET_MODULE_MAC_ENABLE                   //Enable access to module MAC address function

/******************************************************************************
                      13:Whether the MCU need to support the acquisition of green time function
Open the macro if necessary and implement the mcu_get_greentime code in protocol.c
There is a #err hint inside mcu_get_greentime. Please delete the #err after completing the function.
The MCU can call the mcu_get_green_time() function to initiate the calibration function after the wifi module is properly networked.
******************************************************************************/
//#define         SUPPORT_GREEN_TIME                //Turn on green time

/******************************************************************************
                      14:Whether the MCU need to turn on the synchronization status report function
1) This command is a synchronization instruction. After MCU data status is reported, we need to wait for the module to return the result.
2) Each sending module will have a response, and the WIFI module cannot be reported many times before it does not respond.
3) If the network is not good and the data cannot be reported in time, the module will return failure after 5 seconds, and the MCU needs to wait for more than 5 seconds.
******************************************************************************/
//#define         MCU_DP_UPLOAD_SYN                   //Enable the synchronization status report function

/******************************************************************************
                      15:Whether the MCU need to open the infrared status notification
Open the macro if necessary,
And in the protocol.c file get_ir_status function to view the results and reply,
get_ir_status is prompted with #err. Please remove the #err when the function is complete
******************************************************************************/
//#define         GET_IR_STATUS_ENABLE                   //Turn on the infrared status notification function

/******************************************************************************
                      16:Whether the MCU need to open the infrared into the transceiver production test function
Turn on the macro if necessary, and the MCU calls mcu_start_ir_test in the mcu_api.c file when it is necessary to turn on the infrared to enter the send, receive, production and test
And in the protocol.c file ir_tx_rx_test_result function to view the test results,
ir_tx_rx_test_result has a #err prompt inside, remove the #err when the function is complete
******************************************************************************/
//#define         IR_TX_RX_TEST_ENABLE                   //Turn on the infrared into the receiving and receiving production test function

/******************************************************************************
                      17:File package download function
Open the macro if desired and select the package size
And process the data in the file_download_handle function in the protocol.c file,
Inside the file_download_handle is the #err prompt, which is removed when the function is complete
******************************************************************************/
//#define         FILE_DOWNLOAD_ENABLE                   //Enable file package download function
/*  File download package size selection  */
#ifdef FILE_DOWNLOAD_ENABLE
#define FILE_DOWNLOAD_PACKAGE_SIZE                   0        //The package size is 256 bytes
//#define FILE_DOWNLOAD_PACKAGE_SIZE                   1        //The package size is 512 bytes
//#define FILE_DOWNLOAD_PACKAGE_SIZE                   2        //The package size is 1024 bytes
#endif

/******************************************************************************
                      18:Whether the MCU needs to support voice module-related protocol functions
This protocol is only applicable to the common docking of voice module VWXR2. The common firmware of other non-voice modules does not have the relevant protocol functions in this directory
Turn on the macro if necessary, and the MCU calls the mcu_api.c file where the voice module-related protocol functions are required
get_voice_state /set_voice_MIC_silence/set_speaker_voice/voice_test/voice_awaken_test
And check the results in the related result handling function of protocol.c file.
The result processing function is prompted with #err. Please delete the #err after completing the function
******************************************************************************/
//#define         VOICE_MODULE_PROTOCOL_ENABLE           //Enable voice mode-related protocol functions

/******************************************************************************
                      19:Whether the MCU needs to support the module to extend the service function
Open the macro if necessary, and the MCU calls open_module_time_serve in the mcu_api.c file where the module extension service is needed
And view the result in the open_module_time_serve_result function in the protocol.c file,
Inside the open_module_time_serve_result is the #err prompt, which is removed when the function is complete
******************************************************************************/
//#define         MODULE_EXPANDING_SERVICE_ENABLE        //Open the module to expand the service function

/******************************************************************************
                      20:Whether the MCU needs to support bluetooth-related functions
Turn on the macro if necessary, and the MCU calls mcu_start_BLE_test in the mcu_api.c file where it is needed for bluetooth-related functionality
And view the test results in the BLE_test_result function in the protocol.c file,
BLE_test_result has an internal #err prompt that is removed when the function is complete
******************************************************************************/
//#define         BLE_RELATED_FUNCTION_ENABLE            //Enable bluetooth-related functions




/******************************************************************************
                        1:dp data point serial number redefinition
          **This is the automatic generation of code, 
            such as the relevant changes in the development platform, 
            please re-download MCU_SDK**         
******************************************************************************/
//喂食计划(可下发可上报)
//备注:同步到设备端本地，即使设备离线，扔能正常喂食出粮，喂食计划最多支持10个
//raw格式约定：按照周期+时间+喂食份数来实现本地定时，具体如下
//1，前7个比特位代表周一到周日，二进制转十六进制，占用一个字节，0代表未设置，1代表设置，如0000001，表示周日生效，转换为16进制就是01
//2，时间按照小时分钟格式，占用2个字节，分钟和小时，十进制转16进制，如18：50，转为16进制为1232
//3，喂食份数，占用1个字节，十进制转16进制，如12，转为16进制为0c
//4，开关，占用1个字节，00表示关闭，01表示开启
//上述举例，对于APP端时间下发的结果为0112320c01，表示周日，18：50，喂食12份，开启。
#define DPID_MEAL_PLAN 1
//快速喂食(可下发可上报)
//备注:
#define DPID_QUICK_FEED 2
//手动喂食(可下发可上报)
//备注:
#define DPID_MANUAL_FEED 3
//喂食状态(只上报)
//备注:
#define DPID_FEED_STATE 4
//单位转换(可下发可上报)
//备注:
#define DPID_UNIT 5
//慢放喂食(可下发可上报)
//备注:
#define DPID_SLOW_FEED 6
//出粮校准(可下发可上报)
//备注:
#define DPID_EXPORT_CALIBRATE 7
//余粮校准(可下发可上报)
//备注:
#define DPID_WEIGHT_CALIBRATE 8
//恢复出厂(可下发可上报)
//备注:
#define DPID_FACTORY_RESET 9
//出粮校准状态(只上报)
//备注:
#define DPID_EXPORT_STATE 10
//电池电量(只上报)
//备注:
#define DPID_BATTERY_PERCENTAGE 11
//充电状态(只上报)
//备注:
#define DPID_CHARGE_STATE 12
//喂食盖状态(只上报)
//备注:
#define DPID_COVER_STATE 13
//故障告警(只上报)
//备注:
#define DPID_FAULT 14
//喂食结果上报(只上报)
//备注:
#define DPID_FEED_REPORT 15
//余粮重量(只上报)
//备注:
#define DPID_WEIGHT 17
//语音播放次数(可下发可上报)
//备注:
#define DPID_VOICE_TIMES 18
//小夜灯(可下发可上报)
//备注:
#define DPID_LIGHT 19
//开关(可下发可上报)
//备注:旋转食盒类宠物喂食器专用
#define DPID_SWITCH 20
//音量控制(可下发可上报)
//备注:
#define DPID_VOICE_VOL 203
//麦克风开关(可下发可上报)
//备注:
#define DPID_VOICE_MIC 204
//暂停/播放(可下发可上报)
//备注:
#define DPID_VOICE_PLAY 205
//蓝牙开/关(可下发可上报)
//备注:
#define DPID_VOICE_BT_PLAY 206
//本地闹钟(可下发可上报)
//备注:
#define DPID_VOICE_ALARM_CLOCK 207
//语音控制组合(可下发可上报)
//备注:
#define DPID_VOICE_CTRL_GROUP 208



/**
 * @brief  Send data processing
 * @param[in] {value} Serial port receives byte data
 * @return Null
 */
void uart_transmit_output(unsigned char value);

/**
 * @brief  All dp point information of the system is uploaded to realize APP and muc data synchronization
 * @param  Null
 * @return Null
 * @note   This function SDK needs to be called internally;
 *         The MCU must implement the data upload function in the function;
 *         including only reporting and reportable hair style data.
 */
void all_data_update(void);



#ifdef SUPPORT_MCU_FIRM_UPDATE
/**
 * @brief  Upgrade package size selection
 * @param[in] {package_sz} Upgrade package size
 * @ref           0x00: 256byte (default)
 * @ref           0x01: 512byte
 * @ref           0x02: 1024byte
 * @return Null
 * @note   MCU needs to implement this function by itself
 */
void upgrade_package_choose(unsigned char package_sz);

/**
 * @brief  MCU enters firmware upgrade mode
 * @param[in] {value} Firmware buffer
 * @param[in] {position} The current data packet is in the firmware location
 * @param[in] {length} Current firmware package length (when the firmware package length is 0, it indicates that the firmware package is sent)
 * @return Null
 * @note   MCU needs to implement this function by itself
 */
unsigned char mcu_firm_update_handle(const unsigned char value[],unsigned long position,unsigned short length);
#endif

#ifdef SUPPORT_GREEN_TIME
/**
 * @brief  Gets the green time
 * @param[in] {time} Get the time data
 * @return Null
 * @note   MCU needs to implement this function by itself
 */
void mcu_get_greentime(unsigned char time[]);
#endif

#ifdef SUPPORT_MCU_RTC_CHECK
/**
 * @brief  MCU proofreads local RTC clock
 * @param[in] {time} Get the time data
 * @return Null
 * @note   MCU needs to implement this function by itself
 */
void mcu_write_rtctime(unsigned char time[]);
#endif

#ifdef WIFI_TEST_ENABLE
/**
 * @brief  Wifi function test feedback
 * @param[in] {result} Wifi function test
 * @ref       0: failure
 * @ref       1: success
 * @param[in] {rssi} Test success indicates wifi signal strength / test failure indicates error type
 * @return Null
 * @note   MCU needs to implement this function by itself
 */
void wifi_test_result(unsigned char result,unsigned char rssi);
#endif

#ifdef WEATHER_ENABLE
/**
 * @brief  Turn on the weather function
 * @param[in] {res} Turn on the weather function to return the result
 * @ref       0: failure
 * @ref       1: success
 * @param[in] {err} Error code
 * @return Null
 * @note   MCU needs to implement this function by itself
 */
void weather_open_return_handle(unsigned char res, unsigned char err);

/**
 * @brief  Weather data user self-processing function
 * @param[in] {name} parameter name
 * @param[in] {type} parameter type
 * @ref       0: int
 * @ref       1: string
 * @param[in] {data} the address of the parameter value
 * @param[in] {day} What day's weather. range of value: 0~6
 * @ref       0: today
 * @ref       1: tomorrow
 * @return Null
 * @note   MCU needs to implement this function by itself
 */
void weather_data_user_handle(char *name, unsigned char type, const unsigned char *data, char day);
#endif

#ifdef MCU_DP_UPLOAD_SYN
/**
 * @brief  Status reports results synchronously
 * @param[in] {result} Result
 * @ref       0: failure
 * @ref       1: success
 * @return Null
 * @note   MCU needs to implement this function by itself
 */
void get_upload_syn_result(unsigned char result);
#endif

#ifdef GET_WIFI_STATUS_ENABLE
/**
 * @brief  Get the WIFI status result
 * @param[in] {result} Wifi working state
 * @ref       0x00: wifi status 1  smartconfig configuration status
 * @ref       0x01: wifi status 2  AP configuration status
 * @ref       0x02: wifi status 3  WIFI configured but not connected to the router
 * @ref       0x03: wifi status 4  WIFI Configured and connected to the router
 * @ref       0x04: wifi status 5  The router is connected and connected to the cloud
 * @ref       0x05: wifi status 6  The wifi device is in low power mode
 * @ref       0x06: wifi status 7  The wifi device is in smartconfig&AP mode
 * @return Null
 * @note   MCU needs to implement this function by itself
 */
void get_wifi_status(unsigned char result);
#endif

#ifdef WIFI_STREAM_ENABLE
/**
 * @brief  Stream service delivery
 * @param[in] {id} ID number
 * @param[in] {buffer} The address at which the packet is sent
 * @param[in] {buf_len} Length of packet sent
 * @return Stream_trans result
 * -           0(ERROR): failure
 * -           1(SUCCESS): success
 * @note   MCU needs to implement this function by itself
 */
unsigned char stream_trans_send(unsigned int id, unsigned char *buffer, unsigned long buf_len);

/**
 * @brief  Multi-map stream service delivery
 * @param[in] {id} Map ID number
 * @param[in] {sub_id} Submap ID number
 * @param[in] {sub_id_pro_mode} Map ID data processing method
 * @ref       0x00: Continue to accumulate
 * @ref       0x01: Clear the data uploaded by the submap ID number
 * @param[in] {buffer} The address at which the packet is sent
 * @param[in] {buf_len} Length of packet sent
 * @return Stream_trans result
 * -           0(ERROR): failure
 * -           1(SUCCESS): success
 * @note   MCU needs to implement this function by itself
 */
unsigned char maps_stream_trans_send(unsigned int id, unsigned char sub_id, unsigned char sub_id_pro_mode, unsigned char *buffer, unsigned long buf_len);
#endif

#ifdef WIFI_CONNECT_TEST_ENABLE
/**
 * @brief  Routing information receives notification of results
 * @param[in] {result} Whether the module has successfully received the correct routing information
 * @ref       0x00: failure
 * @ref       0x01: success
 * @return Null
 * @note   MCU needs to implement this function by itself
 */
void wifi_connect_test_result(unsigned char result);
#endif
  
#ifdef GET_MODULE_MAC_ENABLE
/**
 * @brief  Gets the module MAC result
 * @param[in] {mac} Module MAC data
 * @ref       mac[0]: is whether to get the MAC success flag,  0x00 success, 0x01 failure
 * @ref       mac[1]~mac[6]: When obtaining the MAC address flag bit MAC [0] is successful, it represents the valid MAC address of the module
 * @return Null
 * @note   MCU needs to implement this function by itself
 */
void mcu_get_mac(unsigned char mac[]);
#endif

#ifdef GET_IR_STATUS_ENABLE
/**
 * @brief  Obtain the infrared state results
 * @param[in] {result} Indicating infrared state
 * @ref       0x00: Infrared state 1 Sending infrared code
 * @ref       0x01: Infrared state 2 Send infrared code to end
 * @ref       0x02: Infrared state 3 Infrared learning begins
 * @ref       0x03: Infrared state 4 End of infrared learning
 * @return Null
 * @note   MCU needs to implement this function by itself
 */
void get_ir_status(unsigned char result);
#endif

#ifdef IR_TX_RX_TEST_ENABLE
/**
 * @brief  Notification of infrared incoming and outgoing test results
 * @param[in] {result} Whether the module successfully received the correct information
 * @ref       0x00: failure
 * @ref       0x01: success
 * @return Null
 * @note   MCU needs to implement this function by itself
 */
void ir_tx_rx_test_result(unsigned char result);
#endif

#ifdef FILE_DOWNLOAD_ENABLE
/**
 * @brief  File download package size selection
 * @param[in] {package_sz} File download package size
 * @ref       0x00: 256 byte
 * @ref       0x01: 512 byte
 * @ref       0x02: 1024 byte
 * @return Null
 * @note   MCU needs to implement this function by itself
 */
void file_download_package_choose(unsigned char package_sz);

/**
 * @brief  Package download
 * @param[in] {value} Data buffer
 * @param[in] {position} The current packet is at the file location
 * @param[in] {length} Current file package length (when the length is 0, the file package is sent)
 * @return Data processing results
 * -           0(ERROR): failure
 * -           1(SUCCESS): success
 * @note   MCU needs to implement this function by itself
 */
unsigned char file_download_handle(const unsigned char value[],unsigned long position,unsigned short length);
#endif

#ifdef MODULE_EXPANDING_SERVICE_ENABLE
/**
 * @brief  Module time service notification results
 * @param[in] {value} Data buffer
 * @param[in] {length} Data buffer length
 * @return Null
 * @note   MCU needs to implement this function by itself
 */
void open_module_time_serve_result(const unsigned char value[], unsigned short length);
#endif

#ifdef BLE_RELATED_FUNCTION_ENABLE
/**
 * @brief  Bluetooth functional test results
 * @param[in] {value} Data buffer
 * @param[in] {length} Data buffer length
 * @return Null
 * @note   MCU needs to implement this function by itself
 */
void BLE_test_result(const unsigned char value[], unsigned short length);
#endif

#ifdef VOICE_MODULE_PROTOCOL_ENABLE
/**
 * @brief  Get voice status code result
 * @param[in] {result} Voice status code
 * @ref       0x00: idle
 * @ref       0x01: mic mute state
 * @ref       0x02: wake
 * @ref       0x03: recording
 * @ref       0x04: Recognizing
 * @ref       0x05: Identified successfully
 * @ref       0x06: Recognition failed
 * @return Null
 * @note   MCU needs to implement this function by itself
 */
void get_voice_state_result(unsigned char result);

/**
 * @brief  MIC mute setting
 * @param[in] {result} Mute setting value
 * @ref       0x00: mic on
 * @ref       0x01: mic mute
 * @return Null
 * @note   MCU needs to implement this function by itself
 */
void set_voice_MIC_silence_result(unsigned char result);

/**
 * @brief  speaker volume setting result
 * @param[in] {result} Volume value
 * @ref       0~10: Volume range
 * @return Null
 * @note   MCU needs to implement this function by itself
 */
void set_speaker_voice_result(unsigned char result);

/**
 * @brief  Audio production test results
 * @param[in] {result} Audio production test status
 * @ref       0x00: Turn off audio production test
 * @ref       0x01: mic1 audio loop test
 * @ref       0x02: mic2 audio loop test
 * @return Null
 * @note   MCU needs to implement this function by itself
 */
void voice_test_result(unsigned char result);

/**
 * @brief  Get wake up test result
 * @param[in] {result} Wake-up return value
 * @ref       0x00: Wake up successfully
 * @ref       0x01: Wake up failure (10s timeout failure)
 * @return Null
 * @note   MCU needs to implement this function by itself
 */
void voice_awaken_test_result(unsigned char result);
#endif



/**
 * @brief  dp delivery processing function
 * @param[in] {dpid} DP number
 * @param[in] {value} dp data buffer address
 * @param[in] {length} dp data length
 * @return Dp processing results
 * -           0(ERROR): failure
 * -           1(SUCCESS): success
 * @note   The function user cannot modify
 */
unsigned char dp_download_handle(unsigned char dpid,const unsigned char value[], unsigned short length);

/**
 * @brief  Get the sum of all dp commands
 * @param[in] Null
 * @return Sent the sum of the commands
 * @note   The function user cannot modify
 */
unsigned char get_download_cmd_total(void);

#endif

