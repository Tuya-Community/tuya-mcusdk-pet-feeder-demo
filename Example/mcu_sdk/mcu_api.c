/**********************************Copyright (c)**********************************
**                     All rights reserved (C), 2015-2020, Tuya
**
**                             http://www.tuya.com
**
*********************************************************************************/
/**
 * @file    mcu_api.c
 * @author  Tuya Team
 * @version v2.5.4
 * @date    2020.4.15
 * @brief   The function under this file does not need to be modified by the user. 
            The files that the user needs to call are in the file.
 */


#define MCU_API_GLOBAL

#include "wifi.h"

/**
 * @brief  hex to bcd
 * @param[in] {Value_H} High Byte
 * @param[in] {Value_L} Low Byte
 * @return Converted data
 */
unsigned char hex_to_bcd(unsigned char Value_H,unsigned char Value_L)
{
  unsigned char bcd_value;
  
  if((Value_H >= '0') && (Value_H <= '9'))
    Value_H -= '0';
  else if((Value_H >= 'A') && (Value_H <= 'F'))
    Value_H = Value_H - 'A' + 10;
  else if((Value_H >= 'a') && (Value_H <= 'f'))
    Value_H = Value_H - 'a' + 10;
   
  bcd_value = Value_H & 0x0f;
  
  bcd_value <<= 4;
  if((Value_L >= '0') && (Value_L <= '9'))
    Value_L -= '0';
  else if((Value_L >= 'A') && (Value_L <= 'F'))
    Value_L = Value_L - 'a' + 10;
  else if((Value_L >= 'a') && (Value_L <= 'f'))
    Value_L = Value_L - 'a' + 10;
  
  bcd_value |= Value_L & 0x0f;

  return bcd_value;
}

/**
 * @brief  Calculate string length
 * @param[in] {str} String address
 * @return data length
 */
unsigned long my_strlen(unsigned char *str)  
{
  unsigned long len = 0;
  if(str == NULL)
  { 
    return 0;
  }
  
  for(len = 0; *str ++ != '\0'; )
  {
    len ++;
  }
  
  return len;
}

/**
 * @brief  Set the first count bytes of the memory area pointed to by src to the character c
 * @param[out] {src} source address
 * @param[in] {ch} Set character
 * @param[in] {count} Set the data length
 * @return Source address after data processing
 */
void *my_memset(void *src,unsigned char ch,unsigned short count)
{
  unsigned char *tmp = (unsigned char *)src;
  
  if(src == NULL)
  {
    return NULL;
  }
  
  while(count --)
  {
    *tmp ++ = ch;
  }
  
  return src;
}

/**
 * @brief  Memory copy
 * @param[out] {dest} target address
 * @param[in] {src} source address
 * @param[in] {count} number of data copies
 * @return Source address after data processing
 */
void *my_memcpy(void *dest, const void *src, unsigned short count)  
{  
  unsigned char *pdest = (unsigned char *)dest;  
  const unsigned char *psrc  = (const unsigned char *)src;  
  unsigned short i;
  
  if(dest == NULL || src == NULL)
  { 
    return NULL;
  }
  
  if((pdest <= psrc) || (pdest > psrc + count))
  {  
    for(i = 0; i < count; i ++)
    {  
      pdest[i] = psrc[i];  
    }  
  }
  else
  {
    for(i = count; i > 0; i --)
    {  
      pdest[i - 1] = psrc[i - 1];  
    }  
  }  
  
  return dest;  
}

/**
 * @brief  String copy
 * @param[in] {dest} target address
 * @param[in] {src} source address
 * @return Source address after data processing
 */
char *my_strcpy(char *dest, const char *src)  
{
  char *p = dest;
  while(*src!='\0')
  {
    *dest++ = *src++;
  }
  *dest = '\0';
  return p;
}

/**
 * @brief  String compare
 * @param[in] {s1} String 1
 * @param[in] {s2} String 2
 * @return Size comparison value
 * -             0:s1=s2
 * -             <0:s1<s2
 * -             >0:s1>s2
 */
int my_strcmp(char *s1 , char *s2)
{
  while( *s1 && *s2 && *s1 == *s2 )
  {
    s1++;
    s2++;
  }
  return *s1 - *s2;
}

/**
 * @brief  Split the int type into four bytes
 * @param[in] {number} 4 bytes of original data
 * @param[out] {value} 4 bytes of data after processing is completed
 * @return Null
 */
void int_to_byte(unsigned long number,unsigned char value[4])
{
  value[0] = number >> 24;
  value[1] = number >> 16;
  value[2] = number >> 8;
  value[3] = number & 0xff;
}

/**
 * @brief  Combine 4 bytes into 1 32bit variable
 * @param[in] {value} 4 bytes of data after processing is completed
 * @return 32bit variable after the merge is completed
 */
unsigned long byte_to_int(const unsigned char value[4])
{
  unsigned long nubmer = 0;

  nubmer = (unsigned long)value[0];
  nubmer <<= 8;
  nubmer |= (unsigned long)value[1];
  nubmer <<= 8;
  nubmer |= (unsigned long)value[2];
  nubmer <<= 8;
  nubmer |= (unsigned long)value[3];
  
  return nubmer;
}

#ifndef WIFI_CONTROL_SELF_MODE
/**
 * @brief  MCU gets reset wifi success flag
 * @param  Null
 * @return Reset flag
 * -           0(RESET_WIFI_ERROR):failure
 * -           1(RESET_WIFI_SUCCESS):success
 * @note   1:The MCU actively calls mcu_reset_wifi() and calls this function to get the reset state.
 *         2:If the module is in self-processing mode, the MCU does not need to call this function.
 */
unsigned char mcu_get_reset_wifi_flag(void)
{
  return reset_wifi_flag;
}

/**
 * @brief  MCU actively resets wifi working mode
 * @param  Null
 * @return Null
 * @note   1:The MCU actively calls to obtain whether the reset wifi is successful through the mcu_get_reset_wifi_flag() function.
 *         2:If the module is in self-processing mode, the MCU does not need to call this function.
 */
void mcu_reset_wifi(void)
{
  reset_wifi_flag = RESET_WIFI_ERROR;
  
  wifi_uart_write_frame(WIFI_RESET_CMD, MCU_SEND_VER, 0);
}

/**
 * @brief  Get set wifi status success flag
 * @param  Null
 * @return wifimode flag
 * -           0(SET_WIFICONFIG_ERROR):failure
 * -           1(SET_WIFICONFIG_SUCCESS):success
 * @note   1:The MCU actively calls to obtain whether the reset wifi is successful through the mcu_get_reset_wifi_flag() function.
 *         2:If the module is in self-processing mode, the MCU does not need to call this function.
 */
unsigned char mcu_get_wifimode_flag(void)
{
  return set_wifimode_flag;
}

/**
 * @brief  MCU set wifi working mode
 * @param[in] {mode} enter mode
 * @ref        0(SMART_CONFIG):enter smartconfig mode
 * @ref        1(AP_CONFIG):enter AP mode
 * @return Null
 * @note   1:MCU active call
 *         2:After success, it can be judged whether set_wifi_config_state is TRUE; TRUE means successful setting of wifi working mode
 *         3:If the module is in self-processing mode, the MCU does not need to call this function.
 */
void mcu_set_wifi_mode(unsigned char mode)
{
  unsigned char length = 0;
  
  set_wifimode_flag = SET_WIFICONFIG_ERROR;
  
  length = set_wifi_uart_byte(length, mode);
  
  wifi_uart_write_frame(WIFI_MODE_CMD, MCU_SEND_VER, length);
}

/**
 * @brief  The MCU actively obtains the current wifi working status.
 * @param  Null
 * @return wifi work state
 * -          SMART_CONFIG_STATE:smartconfig config status
 * -          AP_STATE:AP config status
 * -          WIFI_NOT_CONNECTED:WIFI configuration succeeded but not connected to the router
 * -          WIFI_CONNECTED:WIFI configuration is successful and connected to the router
 * -          WIFI_CONN_CLOUD:WIFI is connected to the cloud server
 * -          WIFI_LOW_POWER:WIFI is in low power mode
 * @note   1:If the module is in self-processing mode, the MCU does not need to call this function.
 */
unsigned char mcu_get_wifi_work_state(void)
{
  return wifi_work_state;
}
#endif

#ifdef SUPPORT_GREEN_TIME
/**
 * @brief  MCU gets green time
 * @param  Null
 * @return Null
 * @note   The MCU needs to call this function by itself.
 */
void mcu_get_green_time(void)
{
  wifi_uart_write_frame(GET_ONLINE_TIME_CMD,MCU_SEND_VER,0);
}
#endif

#ifdef SUPPORT_MCU_RTC_CHECK
/**
 * @brief  MCU gets system time for proofreading local clock
 * @param  Null
 * @return Null
 * @note   The rtc clock is checked in the mcu_write_rtctime function after the MCU is actively called.
 */
void mcu_get_system_time(void)
{
  wifi_uart_write_frame(GET_LOCAL_TIME_CMD,MCU_SEND_VER,0);
}
#endif

#ifdef WIFI_TEST_ENABLE
/**
 * @brief  Mcu initiated wifi function test
 * @param  Null
 * @return Null
 * @note   The MCU needs to call this function by itself.
 */
void mcu_start_wifitest(void)
{
  wifi_uart_write_frame(WIFI_TEST_CMD,MCU_SEND_VER,0);
}
#endif

#ifdef WIFI_HEARTSTOP_ENABLE
/**
 * @brief  Notify the WIFI module to turn off the heartbeat
 * @param  Null
 * @return Null
 * @note   The MCU needs to call this function by itself.
 */
void wifi_heart_stop(void)
{
  wifi_uart_write_frame(HEAT_BEAT_STOP,MCU_SEND_VER,0);
}
#endif

#ifdef GET_WIFI_STATUS_ENABLE
/**
 * @brief  Get the current wifi connection status
 * @param  Null
 * @return Null
 * @note   The MCU needs to call this function by itself.
 */
void mcu_get_wifi_connect_status(void)
{
  wifi_uart_write_frame(GET_WIFI_STATUS_CMD,MCU_SEND_VER,0);
}
#endif

#ifdef WIFI_STREAM_ENABLE
/**
 * @brief  Stream data transmission
 * @param[in] {id} Stream service identifier
 * @param[in] {offset} Offset
 * @param[in] {buffer} Data address
 * @param[in] {buf_len} Data length
 * @return Null
 * @note   Null
 */
unsigned char stream_trans(unsigned short id, unsigned int offset, unsigned char *buffer, unsigned short buf_len)
{
  unsigned short length = 0;

  stream_status = 0xff;

  if(stop_update_flag == ENABLE)
    return SUCCESS;

  //ID
  length = set_wifi_uart_byte(length,id / 0x100);
  length = set_wifi_uart_byte(length,id % 0x100);
  //Offset
  length = set_wifi_uart_byte(length,offset >> 24);
  length = set_wifi_uart_byte(length,offset >> 16);
  length = set_wifi_uart_byte(length,offset >> 8);
  length = set_wifi_uart_byte(length,offset % 256);
  //data
  length = set_wifi_uart_buffer(length, buffer, buf_len);
  wifi_uart_write_frame(STREAM_TRANS_CMD,MCU_SEND_VER,length);
  return SUCCESS;
}

/**
 * @brief  Stream data transmission
 * @param[in] {pro_ver} Map service agreement version
 * @param[in] {id} Map stream service session id
 * @param[in] {sub_id} submap id
 * @param[in] {sub_id_pro_mode} Sub-map ID data processing method
 * @ref           0x00:Continue to accumulate
 * @ref           0x00:Clear uploaded data
 * @param[in] {offset} Offset
 * @param[in] {buffer} Data address
 * @param[in] {buf_len} Data length
 * @return Null
 * @note   Null
 */
unsigned char maps_stream_trans(unsigned char pro_ver, unsigned short id, unsigned char sub_id, unsigned char sub_id_pro_mode, 
                                unsigned int offset, unsigned char *buffer, unsigned short buf_len)
{
  unsigned short length = 0;

  maps_stream_status = 0xff;

  if(stop_update_flag == ENABLE)
    return SUCCESS;

  //Map service agreement version
  length = set_wifi_uart_byte(length, pro_ver);
  
  //Map stream service session id
  length = set_wifi_uart_byte(length,id / 0x100);
  length = set_wifi_uart_byte(length,id % 0x100);
  
  //submap id
  length = set_wifi_uart_byte(length, sub_id);
  
  //Sub-map ID data processing method
  length = set_wifi_uart_byte(length, sub_id_pro_mode);
  
  //Offset
  length = set_wifi_uart_byte(length,offset >> 24);
  length = set_wifi_uart_byte(length,offset >> 16);
  length = set_wifi_uart_byte(length,offset >> 8);
  length = set_wifi_uart_byte(length,offset % 256);
  //Data
  length = set_wifi_uart_buffer(length, buffer, buf_len);
  wifi_uart_write_frame(MAPS_STREAM_TRANS_CMD,MCU_SEND_VER,length);
  return SUCCESS;
}
#endif

#ifdef WIFI_CONNECT_TEST_ENABLE
/**
 * @brief  mcu initiate wifi function test (connection specified route)
 * @param[in] {ssid_buf} Address to hold the router name string data (ssid length up to 32 bytes)
 * @param[in] {passwd_buffer} The address where the router name string data is stored (passwd is up to 64 bytes long)
 * @return Null
 * @note   The MCU needs to call this function by itself.
 */
void mcu_start_connect_wifitest(unsigned char *ssid_buf,unsigned char *passwd_buffer)
{
  unsigned short length = 0;

  if( my_strlen(ssid_buf) > 32 || my_strlen(passwd_buffer) > 64) {
    //printf("ssid_buf or passwd_buffer is too long!");
    return;
  }
  
  length = set_wifi_uart_buffer(length, "{\"ssid\":\"", my_strlen("{\"ssid\":\""));
  length = set_wifi_uart_buffer(length,ssid_buf,my_strlen(ssid_buf));
  length = set_wifi_uart_buffer(length, "\",\"password\":\"", my_strlen("\",\"password\":\""));
  length = set_wifi_uart_buffer(length,passwd_buffer,my_strlen(passwd_buffer));
  length = set_wifi_uart_buffer(length, "\"}", my_strlen("\"}"));

  wifi_uart_write_frame(WIFI_CONNECT_TEST_CMD,MCU_SEND_VER,length);
}
#endif

#ifdef GET_MODULE_MAC_ENABLE
/**
 * @brief  Get module MAC
 * @param  Null
 * @return Null
 * @note   The MCU needs to call this function by itself.
 */
void mcu_get_module_mac(void)
{
  wifi_uart_write_frame(GET_MAC_CMD,MCU_SEND_VER,0);
}
#endif

#ifdef IR_TX_RX_TEST_ENABLE
/**
 * @brief  MCU initiated infrared into the transceiver production test
 * @param  Null
 * @return Null
 * @note   The MCU needs to call this function by itself.
 */
void mcu_start_ir_test(void)
{
  wifi_uart_write_frame(IR_TX_RX_TEST_CMD,MCU_SEND_VER,0);
}
#endif

#ifdef MODULE_EXPANDING_SERVICE_ENABLE
/**
 * @brief  Open the module time service notification
 * @param[in] {time_type} Type of time
 * @ref       0x00: Green time
 * @ref       0x01: Local time
 * @return Null
 * @note   The MCU needs to call this function by itself.
 */
void open_module_time_serve(unsigned char time_type)
{
    unsigned short length = 0;
    length = set_wifi_uart_byte(length, 0x01);
    length = set_wifi_uart_byte(length, time_type);
    wifi_uart_write_frame(OPEN_MODULE_TIME_SERVE_CMD, MCU_SEND_VER, length);
}
#endif

#ifdef BLE_RELATED_FUNCTION_ENABLE
/**
 * @brief  mcu initiates Bluetooth functional test (scanning specified Bluetooth beacons)
 * @param  Null
 * @return Null
 * @note   The MCU needs to call this function by itself.
 */
void mcu_start_BLE_test(void)
{
    unsigned short length = 0;
    length = set_wifi_uart_byte(length, 0x01);
    wifi_uart_write_frame(BLE_TEST_CMD, MCU_SEND_VER, length);
}
#endif

#ifdef VOICE_MODULE_PROTOCOL_ENABLE

/**
 * @brief  Gets the voice status code
 * @param  Null
 * @return Null
 * @note   The MCU needs to call this function by itself.
 */
void get_voice_state(void)
{
    wifi_uart_write_frame(GET_VOICE_STATE_CMD, MCU_SEND_VER, 0);
}

/**
 * @brief  MIC mute setting
 * @param[in] {set_val} Mute setting value
 * @ref       0x00: mic on
 * @ref       0x01: mic mute
 * @ref       0xA0: Query the mute status
 * @return Null
 * @note   The MCU needs to call this function by itself.
 */
void set_voice_MIC_silence(unsigned char set_val)
{
    unsigned short length = 0;
    length = set_wifi_uart_byte(length, set_val);
    wifi_uart_write_frame(MIC_SILENCE_CMD, MCU_SEND_VER, length);
}

/**
 * @brief  Speaker volume setting
 * @param[in] {set_val} Volume set value
 * @ref       0~10: Volume range
 * @ref       0xA0: Query volume value
 * @return Null
 * @note   The MCU needs to call this function by itself.
 */
void set_speaker_voice(unsigned char set_val)
{
    unsigned short length = 0;
    length = set_wifi_uart_byte(length, set_val);
    wifi_uart_write_frame(SET_SPEAKER_VOLUME_CMD, MCU_SEND_VER, length);
}

/**
 * @brief  Audio production test
 * @param[in] {set_val} Audio production value
 * @ref       0x00: Turn off audio production test
 * @ref       0x01: mic1 audio loop test
 * @ref       0x02: mic2 audio loop test
 * @ref       0xA0: Query the current audio production test status
 * @return Null
 * @note   The MCU needs to call this function by itself.
 */
void voice_test(unsigned char test_val)
{
    unsigned short length = 0;
    length = set_wifi_uart_byte(length, test_val);
    wifi_uart_write_frame(VOICE_TEST_CMD, MCU_SEND_VER, length);
}

/**
 * @brief  Wake up test
 * @param  Null
 * @return Null
 * @note   The MCU needs to call this function by itself.
 */
void voice_awaken_test(void)
{
    wifi_uart_write_frame(VOICE_AWAKEN_TEST_CMD, MCU_SEND_VER, 0);
}
#endif



/**
 * @brief  raw type dp data upload
 * @param[in] {dpid} id number
 * @param[in] {value} Current dp value pointer
 * @param[in] {len} data length
 * @return Null
 * @note   Null
 */
unsigned char mcu_dp_raw_update(unsigned char dpid,const unsigned char value[],unsigned short len)
{
  unsigned short length = 0;
  
  if(stop_update_flag == ENABLE)
    return SUCCESS;
  //
  length = set_wifi_uart_byte(length,dpid);
  length = set_wifi_uart_byte(length,DP_TYPE_RAW);
  //
  length = set_wifi_uart_byte(length,len / 0x100);
  length = set_wifi_uart_byte(length,len % 0x100);
  //
  length = set_wifi_uart_buffer(length,(unsigned char *)value,len);
  
  wifi_uart_write_frame(STATE_UPLOAD_CMD,MCU_SEND_VER,length);
  
  return SUCCESS;
}

/**
 * @brief  bool type dp data upload
 * @param[in] {dpid} id number
 * @param[in] {value} Current dp value pointer
 * @return Null
 * @note   Null
 */
unsigned char mcu_dp_bool_update(unsigned char dpid,unsigned char value)
{
  unsigned short length = 0;
  
  if(stop_update_flag == ENABLE)
    return SUCCESS;
  
  length = set_wifi_uart_byte(length,dpid);
  length = set_wifi_uart_byte(length,DP_TYPE_BOOL);
  //
  length = set_wifi_uart_byte(length,0);
  length = set_wifi_uart_byte(length,1);
  //
  if(value == FALSE)
  {
    length = set_wifi_uart_byte(length,FALSE);
  }
  else
  {
    length = set_wifi_uart_byte(length,1);
  }
  
  wifi_uart_write_frame(STATE_UPLOAD_CMD,MCU_SEND_VER,length);
  
  return SUCCESS;
}

/**
 * @brief  value type dp data upload
 * @param[in] {dpid} id number
 * @param[in] {value} Current dp value pointer
 * @return Null
 * @note   Null
 */
unsigned char mcu_dp_value_update(unsigned char dpid,unsigned long value)
{
  unsigned short length = 0;
  
  if(stop_update_flag == ENABLE)
    return SUCCESS;
  
  length = set_wifi_uart_byte(length,dpid);
  length = set_wifi_uart_byte(length,DP_TYPE_VALUE);
  //
  length = set_wifi_uart_byte(length,0);
  length = set_wifi_uart_byte(length,4);
  //
  length = set_wifi_uart_byte(length,value >> 24);
  length = set_wifi_uart_byte(length,value >> 16);
  length = set_wifi_uart_byte(length,value >> 8);
  length = set_wifi_uart_byte(length,value & 0xff);
  
  wifi_uart_write_frame(STATE_UPLOAD_CMD,MCU_SEND_VER,length);
  
  return SUCCESS;
}

/**
 * @brief  string type dp data upload
 * @param[in] {dpid} id number
 * @param[in] {value} Current dp value pointer
 * @param[in] {len} data length
 * @return Null
 * @note   Null
 */
unsigned char mcu_dp_string_update(unsigned char dpid,const unsigned char value[],unsigned short len)
{
  unsigned short length = 0;
  
  if(stop_update_flag == ENABLE)
    return SUCCESS;
  //
  length = set_wifi_uart_byte(length,dpid);
  length = set_wifi_uart_byte(length,DP_TYPE_STRING);
  //
  length = set_wifi_uart_byte(length,len / 0x100);
  length = set_wifi_uart_byte(length,len % 0x100);
  //
  length = set_wifi_uart_buffer(length,(unsigned char *)value,len);
  
  wifi_uart_write_frame(STATE_UPLOAD_CMD,MCU_SEND_VER,length);
  
  return SUCCESS;
}

/**
 * @brief  enum type dp data upload
 * @param[in] {dpid} id number
 * @param[in] {value} Current dp value pointer
 * @return Null
 * @note   Null
 */
unsigned char mcu_dp_enum_update(unsigned char dpid,unsigned char value)
{
  unsigned short length = 0;
  
  if(stop_update_flag == ENABLE)
    return SUCCESS;
  
  length = set_wifi_uart_byte(length,dpid);
  length = set_wifi_uart_byte(length,DP_TYPE_ENUM);
  //
  length = set_wifi_uart_byte(length,0);
  length = set_wifi_uart_byte(length,1);
  //
  length = set_wifi_uart_byte(length,value);
  
  wifi_uart_write_frame(STATE_UPLOAD_CMD,MCU_SEND_VER,length);
  
  return SUCCESS;
}

/**
 * @brief  fault type dp data upload
 * @param[in] {dpid} id number
 * @param[in] {value} Current dp value pointer
 * @return Null
 * @note   Null
 */
unsigned char mcu_dp_fault_update(unsigned char dpid,unsigned long value)
{
  unsigned short length = 0;
   
  if(stop_update_flag == ENABLE)
    return SUCCESS;
  
  length = set_wifi_uart_byte(length,dpid);
  length = set_wifi_uart_byte(length,DP_TYPE_BITMAP);
  //
  length = set_wifi_uart_byte(length,0);
  
  if((value | 0xff) == 0xff)
  {
    length = set_wifi_uart_byte(length,1);
    length = set_wifi_uart_byte(length,value);
  }
  else if((value | 0xffff) == 0xffff)
  {
    length = set_wifi_uart_byte(length,2);
    length = set_wifi_uart_byte(length,value >> 8);
    length = set_wifi_uart_byte(length,value & 0xff);
  }
  else
  {
    length = set_wifi_uart_byte(length,4);
    length = set_wifi_uart_byte(length,value >> 24);
    length = set_wifi_uart_byte(length,value >> 16);
    length = set_wifi_uart_byte(length,value >> 8);
    length = set_wifi_uart_byte(length,value & 0xff);
  }    
  
  wifi_uart_write_frame(STATE_UPLOAD_CMD,MCU_SEND_VER,length);

  return SUCCESS;
}

#ifdef MCU_DP_UPLOAD_SYN
/**
 * @brief  raw type dp data upload syn
 * @param[in] {dpid} id number
 * @param[in] {value} Current dp value pointer
 * @param[in] {len} data length
 * @return Null
 * @note   Null
 */
unsigned char mcu_dp_raw_update_syn(unsigned char dpid,const unsigned char value[],unsigned short len)
{
  unsigned short length = 0;
  
  if(stop_update_flag == ENABLE)
    return SUCCESS;
  //
  length = set_wifi_uart_byte(length,dpid);
  length = set_wifi_uart_byte(length,DP_TYPE_RAW);
  //
  length = set_wifi_uart_byte(length,len / 0x100);
  length = set_wifi_uart_byte(length,len % 0x100);
  //
  length = set_wifi_uart_buffer(length,(unsigned char *)value,len);
  
  wifi_uart_write_frame(STATE_UPLOAD_SYN_CMD,MCU_SEND_VER,length);
  
  return SUCCESS;
}

/**
 * @brief  bool type dp data upload syn
 * @param[in] {dpid} id number
 * @param[in] {value} Current dp value pointer
 * @return Null
 * @note   Null
 */
unsigned char mcu_dp_bool_update_syn(unsigned char dpid,unsigned char value)
{
  unsigned short length = 0;
  
  if(stop_update_flag == ENABLE)
    return SUCCESS;
  
  length = set_wifi_uart_byte(length,dpid);
  length = set_wifi_uart_byte(length,DP_TYPE_BOOL);
  //
  length = set_wifi_uart_byte(length,0);
  length = set_wifi_uart_byte(length,1);
  //
  if(value == FALSE)
  {
    length = set_wifi_uart_byte(length,FALSE);
  }
  else
  {
    length = set_wifi_uart_byte(length,1);
  }
  
  wifi_uart_write_frame(STATE_UPLOAD_SYN_CMD,MCU_SEND_VER,length);
  
  return SUCCESS;
}

/**
 * @brief  value type dp data upload syn
 * @param[in] {dpid} id number
 * @param[in] {value} Current dp value pointer
 * @return Null
 * @note   Null
 */
unsigned char mcu_dp_value_update_syn(unsigned char dpid,unsigned long value)
{
  unsigned short length = 0;
  
  if(stop_update_flag == ENABLE)
    return SUCCESS;
  
  length = set_wifi_uart_byte(length,dpid);
  length = set_wifi_uart_byte(length,DP_TYPE_VALUE);
  //
  length = set_wifi_uart_byte(length,0);
  length = set_wifi_uart_byte(length,4);
  //
  length = set_wifi_uart_byte(length,value >> 24);
  length = set_wifi_uart_byte(length,value >> 16);
  length = set_wifi_uart_byte(length,value >> 8);
  length = set_wifi_uart_byte(length,value & 0xff);
  
  wifi_uart_write_frame(STATE_UPLOAD_SYN_CMD,MCU_SEND_VER,length);
  
  return SUCCESS;
}

/**
 * @brief  string type dp data upload syn
 * @param[in] {dpid} id number
 * @param[in] {value} Current dp value pointer
 * @param[in] {len} data length
 * @return Null
 * @note   Null
 */
unsigned char mcu_dp_string_update_syn(unsigned char dpid,const unsigned char value[],unsigned short len)
{
  unsigned short length = 0;
  
  if(stop_update_flag == ENABLE)
    return SUCCESS;
  //
  length = set_wifi_uart_byte(length,dpid);
  length = set_wifi_uart_byte(length,DP_TYPE_STRING);
  //
  length = set_wifi_uart_byte(length,len / 0x100);
  length = set_wifi_uart_byte(length,len % 0x100);
  //
  length = set_wifi_uart_buffer(length,(unsigned char *)value,len);
  
  wifi_uart_write_frame(STATE_UPLOAD_SYN_CMD,MCU_SEND_VER,length);
  
  return SUCCESS;
}

/**
 * @brief  enum type dp data upload syn
 * @param[in] {dpid} id number
 * @param[in] {value} Current dp value pointer
 * @return Null
 * @note   Null
 */
unsigned char mcu_dp_enum_update_syn(unsigned char dpid,unsigned char value)
{
  unsigned short length = 0;
  
  if(stop_update_flag == ENABLE)
    return SUCCESS;
  
  length = set_wifi_uart_byte(length,dpid);
  length = set_wifi_uart_byte(length,DP_TYPE_ENUM);
  //
  length = set_wifi_uart_byte(length,0);
  length = set_wifi_uart_byte(length,1);
  //
  length = set_wifi_uart_byte(length,value);
  
  wifi_uart_write_frame(STATE_UPLOAD_SYN_CMD,MCU_SEND_VER,length);
  
  return SUCCESS;
}

/**
 * @brief  fault type dp data upload syn
 * @param[in] {dpid} id number
 * @param[in] {value} Current dp value pointer
 * @return Null
 * @note   Null
 */
unsigned char mcu_dp_fault_update_syn(unsigned char dpid,unsigned long value)
{
  unsigned short length = 0;
   
  if(stop_update_flag == ENABLE)
    return SUCCESS;
  
  length = set_wifi_uart_byte(length,dpid);
  length = set_wifi_uart_byte(length,DP_TYPE_BITMAP);
  //
  length = set_wifi_uart_byte(length,0);
  
  if((value | 0xff) == 0xff)
  {
    length = set_wifi_uart_byte(length,1);
    length = set_wifi_uart_byte(length,value);
  }
  else if((value | 0xffff) == 0xffff)
  {
    length = set_wifi_uart_byte(length,2);
    length = set_wifi_uart_byte(length,value >> 8);
    length = set_wifi_uart_byte(length,value & 0xff);
  }
  else
  {
    length = set_wifi_uart_byte(length,4);
    length = set_wifi_uart_byte(length,value >> 24);
    length = set_wifi_uart_byte(length,value >> 16);
    length = set_wifi_uart_byte(length,value >> 8);
    length = set_wifi_uart_byte(length,value & 0xff);
  }    
  
  wifi_uart_write_frame(STATE_UPLOAD_SYN_CMD,MCU_SEND_VER,length);

  return SUCCESS;
}
#endif

/**
 * @brief  mcu gets bool type to send dp value
 * @param[in] {value} dp data buffer address
 * @param[in] {len} data length
 * @return current dp value
 * @note   Null
 */
unsigned char mcu_get_dp_download_bool(const unsigned char value[],unsigned short len)
{
  return(value[0]);
}

/**
 * @brief  mcu gets enum type to send dp value
 * @param[in] {value} dp data buffer address
 * @param[in] {len} data length
 * @return current dp value
 * @note   Null
 */
unsigned char mcu_get_dp_download_enum(const unsigned char value[],unsigned short len)
{
  return(value[0]);
}

/**
 * @brief  mcu gets value type to send dp value
 * @param[in] {value} dp data buffer address
 * @param[in] {len} data length
 * @return current dp value
 * @note   Null
 */
unsigned long mcu_get_dp_download_value(const unsigned char value[],unsigned short len)
{
  return(byte_to_int(value));
}

/**
 * @brief  Receive data processing
 * @param[in] {value} UART receives byte data
 * @return Null
 * @note   Call this function in the MCU serial receive function and pass the received data as a parameter.
 */
void uart_receive_input(unsigned char value)
{
//  #error "Please call uart_receive_input(value) in the serial port receive interrupt. The serial port data is processed by MCU_SDK. The user should not process it separately. Delete the line after completion."
	
  if(1 == queue_out - queue_in)
  {
    //Data queue full
  }
  else if((queue_in > queue_out) && ((queue_in - queue_out) >= sizeof(wifi_uart_rx_buf)))
  {
    //Data queue full
  }
  else
  {
    //Queue is not full
    if(queue_in >= (unsigned char *)(wifi_uart_rx_buf + sizeof(wifi_uart_rx_buf)))
    {
      queue_in = (unsigned char *)(wifi_uart_rx_buf);
    }
    
    *queue_in ++ = value;
  }
}

/**
 * @brief  Wifi serial port processing service
 * @param  Null
 * @return Null
 * @note   Call this function in the MCU main function while loop
 */
void wifi_uart_service(void)
{
//  #error "Please add wifi_uart_service() directly in the while(1){} of the main function, call this function without adding any conditional judgment, delete the line after completion." 
  static unsigned short rx_in = 0;
  unsigned short offset = 0;
  unsigned short rx_value_len = 0;             //Data frame length
  
  while((rx_in < sizeof(wifi_data_process_buf)) && get_queue_total_data() > 0)
  {
    wifi_data_process_buf[rx_in ++] = Queue_Read_Byte();
  }
  
  if(rx_in < PROTOCOL_HEAD)
    return;
  
  while((rx_in - offset) >= PROTOCOL_HEAD)
  {
    if(wifi_data_process_buf[offset + HEAD_FIRST] != FRAME_FIRST)
    {
      offset ++;
      continue;
    }
    
    if(wifi_data_process_buf[offset + HEAD_SECOND] != FRAME_SECOND)
    {
      offset ++;
      continue;
    }  
    
    if(wifi_data_process_buf[offset + PROTOCOL_VERSION] != VERSION)
    {
      offset += 2;
      continue;
    }      
    
    rx_value_len = wifi_data_process_buf[offset + LENGTH_HIGH] * 0x100;
    rx_value_len += (wifi_data_process_buf[offset + LENGTH_LOW] + PROTOCOL_HEAD);
    if(rx_value_len > sizeof(wifi_data_process_buf) + PROTOCOL_HEAD)
    {
      offset += 3;
      continue;
    }
    
    if((rx_in - offset) < rx_value_len)
    {
      break;
    }
    
    //Data reception completed
    if(get_check_sum((unsigned char *)wifi_data_process_buf + offset,rx_value_len - 1) != wifi_data_process_buf[offset + rx_value_len - 1])
    {
      //Verification error
      //printf("crc error (crc:0x%X  but data:0x%X)\r\n",get_check_sum((unsigned char *)wifi_data_process_buf + offset,rx_value_len - 1),wifi_data_process_buf[offset + rx_value_len - 1]);
      offset += 3;
      continue;
    }
    
    data_handle(offset);
    offset += rx_value_len;
  }//end while

  rx_in -= offset;
  if(rx_in > 0)
  {
    my_memcpy((char *)wifi_data_process_buf,(const char *)wifi_data_process_buf + offset,rx_in);
  }
}

/**
 * @brief  Protocol serial port initialization function
 * @param  Null
 * @return Null
 * @note   This function must be called in the MCU initialization code
 */
void wifi_protocol_init(void)
{
//  #error " Please add wifi_protocol_init() in the main function to complete the wifi protocol initialization and delete the line."
  queue_in = (unsigned char *)wifi_uart_rx_buf;
  queue_out = (unsigned char *)wifi_uart_rx_buf;
  //
#ifndef WIFI_CONTROL_SELF_MODE
  wifi_work_state = WIFI_SATE_UNKNOW;
#endif
}


