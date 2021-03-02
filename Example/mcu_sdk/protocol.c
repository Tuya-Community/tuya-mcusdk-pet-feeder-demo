/**********************************Copyright (c)**********************************
**                     All rights reserved (C), 2015-2020, Tuya
**
**                             http://www.tuya.com
**
*********************************************************************************/
/**
 * @file    protocol.c
 * @author  Tuya Team
 * @version v2.5.4
 * @date    2020.4.15
 * @brief                *******Very important, be sure to watch!!!********
 *          1. The user implements the data delivery/reporting function in this file.
 *          2. DP ID / TYPE and data processing functions require the user to implement according to the actual definition
 *          3. There are #err hints inside the function that needs the user to implement the code after starting some macro definitions. 
 *             Please delete the #err after completing the function.
 */

/******************************************************************************
                                Transplant instructions:
1:The MCU must directly call the wifi_uart_service() function in mcu_api.c in the while.
2:After the normal initialization of the program is completed, 
  it is recommended not to turn off the serial port interrupt. 
  If the interrupt must be turned off, the off interrupt time must be short, 
  and the interrupt will cause the serial port packet to be lost.
3:Do not call the escalation function in the interrupt/timer interrupt
******************************************************************************/

#include "wifi.h"

#include "HX711.h"
extern unsigned long Weight;

#ifdef WEATHER_ENABLE
/**
 * @var    weather_choose
 * @brief  Weather data parameter selection array
 * @note   Users can customize the required parameters, comments or uncomment,
 *         pay attention to the changes
 */
const char *weather_choose[WEATHER_CHOOSE_CNT] = {
    "temp",
    "humidity",
    "condition",
    "pm25",
    /*"pressure",
    "realFeel",
    "uvi",
    "tips",
    "windDir",
    "windLevel",
    "windSpeed",
    "sunRise",
    "sunSet",
    "aqi",
    "so2 ",
    "rank",
    "pm10",
    "o3",
    "no2",
    "co",*/
 };
#endif


/******************************************************************************
                              The first step: initialization
1:Include "wifi.h" in files that need to use wifi related files
2:Call the wifi_protocol_init() function in the mcu_api.c file in the MCU initialization
3:Fill the MCU serial single-byte send function into the uart_transmit_output 
   function in the protocol.c file, and delete #error
4:Call the uart_receive_input function in the mcu_api.c file in the MCU serial receive 
   function and pass the received byte as a parameter.
5:The wifi_uart_service() function in the mcu_api.c file is called after the MCU enters the while loop.
******************************************************************************/

/******************************************************************************
                        1:dp data point sequence type comparison table
          **This is the automatic generation of code, such as the relevant changes in
              the development platform, please re-download MCU_SDK**
******************************************************************************/
const DOWNLOAD_CMD_S download_cmd[] =
{
  {DPID_MEAL_PLAN, DP_TYPE_RAW},
  {DPID_QUICK_FEED, DP_TYPE_BOOL},
  {DPID_MANUAL_FEED, DP_TYPE_VALUE},
  {DPID_FEED_STATE, DP_TYPE_ENUM},
  {DPID_UNIT, DP_TYPE_ENUM},
  {DPID_SLOW_FEED, DP_TYPE_BOOL},
  {DPID_EXPORT_CALIBRATE, DP_TYPE_BOOL},
  {DPID_WEIGHT_CALIBRATE, DP_TYPE_BOOL},
  {DPID_FACTORY_RESET, DP_TYPE_BOOL},
  {DPID_EXPORT_STATE, DP_TYPE_ENUM},
  {DPID_BATTERY_PERCENTAGE, DP_TYPE_VALUE},
  {DPID_CHARGE_STATE, DP_TYPE_BOOL},
  {DPID_COVER_STATE, DP_TYPE_ENUM},
  {DPID_FAULT, DP_TYPE_BITMAP},
  {DPID_FEED_REPORT, DP_TYPE_VALUE},
  {DPID_WEIGHT, DP_TYPE_VALUE},
  {DPID_VOICE_TIMES, DP_TYPE_VALUE},
  {DPID_LIGHT, DP_TYPE_BOOL},
  {DPID_SWITCH, DP_TYPE_BOOL},
  {DPID_VOICE_VOL, DP_TYPE_VALUE},
  {DPID_VOICE_MIC, DP_TYPE_BOOL},
  {DPID_VOICE_PLAY, DP_TYPE_BOOL},
  {DPID_VOICE_BT_PLAY, DP_TYPE_BOOL},
  {DPID_VOICE_ALARM_CLOCK, DP_TYPE_STRING},
  {DPID_VOICE_CTRL_GROUP, DP_TYPE_STRING},
};



/******************************************************************************
                        2:Serial single-byte send function
Please fill in the MCU serial port send function into the function,
and pass the received data as a parameter to the serial port send function.
******************************************************************************/


/**
 * @brief  Send data processing
 * @param[in] {value} Serial port receives byte data
 * @return Null
 */
void uart_transmit_output(unsigned char value)
{
	UART3_SendByte(value);
//  #error "Please fill in the MCU serial port send function and delete the line"

/*
  //Example:
  extern void Uart_PutChar(unsigned char value);
  Uart_PutChar(value);	                                //Serial port send function
*/
}
/******************************************************************************
                           Step 2: Implement a specific user function
1:APP send data processing
2:Data upload processing
******************************************************************************/

/******************************************************************************
                            1:All data upload processing
The current function handles all data upload (including deliverable/reportable and report only)

  Users need to implement according to the actual situation:
  1:Need to implement the reportable/reportable data point report
  2:Need to report only reported data points
This function must be called internally by the MCU.
Users can also call this function to achieve all data upload.
******************************************************************************/

//Automated generation of data reporting functions

/**
 * @brief  All dp point information of the system is uploaded to realize APP and muc data synchronization
 * @param  Null
 * @return Null
 * @note   This function SDK needs to be called internally;
 *         The MCU must implement the data upload function in the function;
 *         including only reporting and reportable hair style data.
 */
void all_data_update(void)
{
//  #error "Please process the reportable data and report only the data. After the processing is completed, delete the line"
	   mcu_dp_value_update(DPID_BATTERY_PERCENTAGE,100); //VALUE型数据上报;
  /* 
  //This code is automatically generated by the platform. 
  //Please modify each reportable and reportable function according to the actual data.
    mcu_dp_raw_update(DPID_MEAL_PLAN,当前喂食计划指针,当前喂食计划数据长度); //RAW型数据上报;
    mcu_dp_bool_update(DPID_QUICK_FEED,当前快速喂食); //BOOL型数据上报;
    mcu_dp_value_update(DPID_MANUAL_FEED,当前手动喂食); //VALUE型数据上报;
    mcu_dp_enum_update(DPID_FEED_STATE,当前喂食状态); //枚举型数据上报;
    mcu_dp_enum_update(DPID_UNIT,当前单位转换); //枚举型数据上报;
    mcu_dp_bool_update(DPID_SLOW_FEED,当前慢放喂食); //BOOL型数据上报;
    mcu_dp_bool_update(DPID_EXPORT_CALIBRATE,当前出粮校准); //BOOL型数据上报;
    mcu_dp_bool_update(DPID_WEIGHT_CALIBRATE,当前余粮校准); //BOOL型数据上报;
    mcu_dp_bool_update(DPID_FACTORY_RESET,当前恢复出厂); //BOOL型数据上报;
    mcu_dp_enum_update(DPID_EXPORT_STATE,当前出粮校准状态); //枚举型数据上报;
    mcu_dp_value_update(DPID_BATTERY_PERCENTAGE,100); //VALUE型数据上报;
    mcu_dp_bool_update(DPID_CHARGE_STATE,当前充电状态); //BOOL型数据上报;
    mcu_dp_enum_update(DPID_COVER_STATE,当前喂食盖状态); //枚举型数据上报;
    mcu_dp_fault_update(DPID_FAULT,当前故障告警); //故障型数据上报;
    mcu_dp_value_update(DPID_FEED_REPORT,当前喂食结果上报); //VALUE型数据上报;
    mcu_dp_value_update(DPID_WEIGHT,当前余粮重量); //VALUE型数据上报;
    mcu_dp_value_update(DPID_VOICE_TIMES,当前语音播放次数); //VALUE型数据上报;
    mcu_dp_bool_update(DPID_LIGHT,当前小夜灯); //BOOL型数据上报;
    mcu_dp_bool_update(DPID_SWITCH,当前开关); //BOOL型数据上报;
    mcu_dp_value_update(DPID_VOICE_VOL,当前音量控制); //VALUE型数据上报;
    mcu_dp_bool_update(DPID_VOICE_MIC,当前麦克风开关); //BOOL型数据上报;
    mcu_dp_bool_update(DPID_VOICE_PLAY,当前暂停/播放); //BOOL型数据上报;
    mcu_dp_bool_update(DPID_VOICE_BT_PLAY,当前蓝牙开/关); //BOOL型数据上报;
    mcu_dp_string_update(DPID_VOICE_ALARM_CLOCK,当前本地闹钟指针,当前本地闹钟数据长度); //STRING型数据上报;
    mcu_dp_string_update(DPID_VOICE_CTRL_GROUP,当前语音控制组合指针,当前语音控制组合数据长度); //STRING型数据上报;

 */
}


/******************************************************************************
                                WARNING!!!    
                            2:All data upload processing
Automate code template functions, please implement data processing by yourself
******************************************************************************/
/*****************************************************************************
函数名称 : dp_download_meal_plan_handle
功能描述 : 针对DPID_MEAL_PLAN的处理函数
输入参数 : value:数据源数据
        : length:数据长度
返回参数 : 成功返回:SUCCESS/失败返回:ERROR
使用说明 : 可下发可上报类型,需要在处理完数据后上报处理结果至app
*****************************************************************************/
static unsigned char dp_download_meal_plan_handle(const unsigned char value[], unsigned short length)
{
    //示例:当前DP类型为RAW
    unsigned char ret;
    /*
    //RAW类型数据处理
    
    */
    
    //处理完DP数据后应有反馈
    ret = mcu_dp_raw_update(DPID_MEAL_PLAN,value,length);
    if(ret == SUCCESS)
        return SUCCESS;
    else
        return ERROR;
}
/*****************************************************************************
函数名称 : dp_download_quick_feed_handle
功能描述 : 针对DPID_QUICK_FEED的处理函数
输入参数 : value:数据源数据
        : length:数据长度
返回参数 : 成功返回:SUCCESS/失败返回:ERROR
使用说明 : 可下发可上报类型,需要在处理完数据后上报处理结果至app
*****************************************************************************/
static unsigned char dp_download_quick_feed_handle(const unsigned char value[], unsigned short length)
{
    //示例:当前DP类型为BOOL
    unsigned char ret;
    //0:关/1:开
    unsigned char quick_feed;
    
    quick_feed = mcu_get_dp_download_bool(value,length);
    if(quick_feed == 0) {
        //开关关
    }else {
        //开关开
    }
  
    //处理完DP数据后应有反馈
    ret = mcu_dp_bool_update(DPID_QUICK_FEED,quick_feed);
    if(ret == SUCCESS)
        return SUCCESS;
    else
        return ERROR;
}
/*****************************************************************************
函数名称 : dp_download_manual_feed_handle
功能描述 : 针对DPID_MANUAL_FEED的处理函数
输入参数 : value:数据源数据
        : length:数据长度
返回参数 : 成功返回:SUCCESS/失败返回:ERROR
使用说明 : 可下发可上报类型,需要在处理完数据后上报处理结果至app
*****************************************************************************/
static unsigned char dp_download_manual_feed_handle(const unsigned char value[], unsigned short length)
{
    //示例:当前DP类型为VALUE
    unsigned char ret;
    unsigned long manual_feed;
    
    manual_feed = mcu_get_dp_download_value(value,length);
    /*
    //VALUE类型数据处理
    
    */
    turn_on_motor();//开关开
	manual_feed=manual_feed*2000;
    HAL_Delay(manual_feed);
	
	  turn_off_motor();//开关开
    //处理完DP数据后应有反馈
    ret = mcu_dp_value_update(DPID_MANUAL_FEED,manual_feed);
	    mcu_dp_value_update(DPID_FEED_REPORT,manual_feed); //VALUE型数据上报;

    if(ret == SUCCESS)
        return SUCCESS;
    else
        return ERROR;
}
/*****************************************************************************
函数名称 : dp_download_unit_handle
功能描述 : 针对DPID_UNIT的处理函数
输入参数 : value:数据源数据
        : length:数据长度
返回参数 : 成功返回:SUCCESS/失败返回:ERROR
使用说明 : 可下发可上报类型,需要在处理完数据后上报处理结果至app
*****************************************************************************/
static unsigned char dp_download_unit_handle(const unsigned char value[], unsigned short length)
{
    //示例:当前DP类型为ENUM
    unsigned char ret;
    unsigned char unit;
    
    unit = mcu_get_dp_download_enum(value,length);
    switch(unit) {
        case 0:
        break;
        
        case 1:
        break;
        
        case 2:
        break;
        
        default:
    
        break;
    }
    
    //处理完DP数据后应有反馈
    ret = mcu_dp_enum_update(DPID_UNIT, unit);
    if(ret == SUCCESS)
        return SUCCESS;
    else
        return ERROR;
}
/*****************************************************************************
函数名称 : dp_download_slow_feed_handle
功能描述 : 针对DPID_SLOW_FEED的处理函数
输入参数 : value:数据源数据
        : length:数据长度
返回参数 : 成功返回:SUCCESS/失败返回:ERROR
使用说明 : 可下发可上报类型,需要在处理完数据后上报处理结果至app
*****************************************************************************/
static unsigned char dp_download_slow_feed_handle(const unsigned char value[], unsigned short length)
{
    //示例:当前DP类型为BOOL
    unsigned char ret;
    //0:关/1:开
    unsigned char slow_feed;
    
    slow_feed = mcu_get_dp_download_bool(value,length);
    if(slow_feed == 0) {
        //开关关
    }else {
        //开关开
    }
  
    //处理完DP数据后应有反馈
    ret = mcu_dp_bool_update(DPID_SLOW_FEED,slow_feed);
    if(ret == SUCCESS)
        return SUCCESS;
    else
        return ERROR;
}
/*****************************************************************************
函数名称 : dp_download_export_calibrate_handle
功能描述 : 针对DPID_EXPORT_CALIBRATE的处理函数
输入参数 : value:数据源数据
        : length:数据长度
返回参数 : 成功返回:SUCCESS/失败返回:ERROR
使用说明 : 可下发可上报类型,需要在处理完数据后上报处理结果至app
*****************************************************************************/
static unsigned char dp_download_export_calibrate_handle(const unsigned char value[], unsigned short length)
{
    //示例:当前DP类型为BOOL
    unsigned char ret;
    //0:关/1:开
    unsigned char export_calibrate;
    
    export_calibrate = mcu_get_dp_download_bool(value,length);
    if(export_calibrate == 0) {
        //开关关
    }else {
        //开关开
    }
  
    //处理完DP数据后应有反馈
    ret = mcu_dp_bool_update(DPID_EXPORT_CALIBRATE,export_calibrate);
    if(ret == SUCCESS)
        return SUCCESS;
    else
        return ERROR;
}
/*****************************************************************************
函数名称 : dp_download_weight_calibrate_handle
功能描述 : 针对DPID_WEIGHT_CALIBRATE的处理函数
输入参数 : value:数据源数据
        : length:数据长度
返回参数 : 成功返回:SUCCESS/失败返回:ERROR
使用说明 : 可下发可上报类型,需要在处理完数据后上报处理结果至app
*****************************************************************************/
static unsigned char dp_download_weight_calibrate_handle(const unsigned char value[], unsigned short length)
{
    //示例:当前DP类型为BOOL
    unsigned char ret;
    //0:关/1:开
    unsigned char weight_calibrate;
    
    weight_calibrate = mcu_get_dp_download_bool(value,length);
    if(weight_calibrate == 0) {
			HX711_uart_write_frame(Read_Weight);//读
		
		mcu_dp_value_update(DPID_WEIGHT,Weight); //VALUE型数据上报;
			
        //开关关
    }else {
			mcu_dp_value_update(DPID_WEIGHT,Weight); //VALUE型数据上报;
        //开关开
    }
  
    //处理完DP数据后应有反馈
    ret = mcu_dp_bool_update(DPID_WEIGHT_CALIBRATE,weight_calibrate);
    if(ret == SUCCESS)
        return SUCCESS;
    else
        return ERROR;
}
/*****************************************************************************
函数名称 : dp_download_factory_reset_handle
功能描述 : 针对DPID_FACTORY_RESET的处理函数
输入参数 : value:数据源数据
        : length:数据长度
返回参数 : 成功返回:SUCCESS/失败返回:ERROR
使用说明 : 可下发可上报类型,需要在处理完数据后上报处理结果至app
*****************************************************************************/
static unsigned char dp_download_factory_reset_handle(const unsigned char value[], unsigned short length)
{
    //示例:当前DP类型为BOOL
    unsigned char ret;
    //0:关/1:开
    unsigned char factory_reset;
    
    factory_reset = mcu_get_dp_download_bool(value,length);
    if(factory_reset == 0) {
        //开关关
    }else {
        //开关开
    }
  
    //处理完DP数据后应有反馈
    ret = mcu_dp_bool_update(DPID_FACTORY_RESET,factory_reset);
    if(ret == SUCCESS)
        return SUCCESS;
    else
        return ERROR;
}
/*****************************************************************************
函数名称 : dp_download_voice_times_handle
功能描述 : 针对DPID_VOICE_TIMES的处理函数
输入参数 : value:数据源数据
        : length:数据长度
返回参数 : 成功返回:SUCCESS/失败返回:ERROR
使用说明 : 可下发可上报类型,需要在处理完数据后上报处理结果至app
*****************************************************************************/
static unsigned char dp_download_voice_times_handle(const unsigned char value[], unsigned short length)
{
    //示例:当前DP类型为VALUE
    unsigned char ret;
    unsigned long voice_times;
    
    voice_times = mcu_get_dp_download_value(value,length);
    /*
    //VALUE类型数据处理
    
    */
    
    //处理完DP数据后应有反馈
    ret = mcu_dp_value_update(DPID_VOICE_TIMES,voice_times);
    if(ret == SUCCESS)
        return SUCCESS;
    else
        return ERROR;
}
/*****************************************************************************
函数名称 : dp_download_light_handle
功能描述 : 针对DPID_LIGHT的处理函数
输入参数 : value:数据源数据
        : length:数据长度
返回参数 : 成功返回:SUCCESS/失败返回:ERROR
使用说明 : 可下发可上报类型,需要在处理完数据后上报处理结果至app
*****************************************************************************/
static unsigned char dp_download_light_handle(const unsigned char value[], unsigned short length)
{
    //示例:当前DP类型为BOOL
    unsigned char ret;
    //0:关/1:开
    unsigned char light;
    
    light = mcu_get_dp_download_bool(value,length);
    if(light == 0) {
			turn_off_motor();
        //开关关
    }else {
        turn_on_change_motor();//开关开
    }
  
    //处理完DP数据后应有反馈
    ret = mcu_dp_bool_update(DPID_LIGHT,light);
    if(ret == SUCCESS)
        return SUCCESS;
    else
        return ERROR;
}
/*****************************************************************************
函数名称 : dp_download_switch_handle
功能描述 : 针对DPID_SWITCH的处理函数
输入参数 : value:数据源数据
        : length:数据长度
返回参数 : 成功返回:SUCCESS/失败返回:ERROR
使用说明 : 可下发可上报类型,需要在处理完数据后上报处理结果至app
*****************************************************************************/
static unsigned char dp_download_switch_handle(const unsigned char value[], unsigned short length)
{
    //示例:当前DP类型为BOOL
    unsigned char ret;
    //0:关/1:开
    unsigned char switch_1;
    
    switch_1 = mcu_get_dp_download_bool(value,length);
    if(switch_1 == 0) {
			turn_off_motor();
			
        //开关关
    }else {
			turn_on_motor();
        //开关开
    }
  
    //处理完DP数据后应有反馈
    ret = mcu_dp_bool_update(DPID_SWITCH,switch_1);
    if(ret == SUCCESS)
        return SUCCESS;
    else
        return ERROR;
}
/*****************************************************************************
函数名称 : dp_download_voice_vol_handle
功能描述 : 针对DPID_VOICE_VOL的处理函数
输入参数 : value:数据源数据
        : length:数据长度
返回参数 : 成功返回:SUCCESS/失败返回:ERROR
使用说明 : 可下发可上报类型,需要在处理完数据后上报处理结果至app
*****************************************************************************/
static unsigned char dp_download_voice_vol_handle(const unsigned char value[], unsigned short length)
{
    //示例:当前DP类型为VALUE
    unsigned char ret;
    unsigned long voice_vol;
    
    voice_vol = mcu_get_dp_download_value(value,length);
    /*
    //VALUE类型数据处理
    
    */
    
    //处理完DP数据后应有反馈
    ret = mcu_dp_value_update(DPID_VOICE_VOL,voice_vol);
    if(ret == SUCCESS)
        return SUCCESS;
    else
        return ERROR;
}
/*****************************************************************************
函数名称 : dp_download_voice_mic_handle
功能描述 : 针对DPID_VOICE_MIC的处理函数
输入参数 : value:数据源数据
        : length:数据长度
返回参数 : 成功返回:SUCCESS/失败返回:ERROR
使用说明 : 可下发可上报类型,需要在处理完数据后上报处理结果至app
*****************************************************************************/
static unsigned char dp_download_voice_mic_handle(const unsigned char value[], unsigned short length)
{
    //示例:当前DP类型为BOOL
    unsigned char ret;
    //0:关/1:开
    unsigned char voice_mic;
    
    voice_mic = mcu_get_dp_download_bool(value,length);
    if(voice_mic == 0) {
        //开关关
    }else {
        //开关开
    }
  
    //处理完DP数据后应有反馈
    ret = mcu_dp_bool_update(DPID_VOICE_MIC,voice_mic);
    if(ret == SUCCESS)
        return SUCCESS;
    else
        return ERROR;
}
/*****************************************************************************
函数名称 : dp_download_voice_play_handle
功能描述 : 针对DPID_VOICE_PLAY的处理函数
输入参数 : value:数据源数据
        : length:数据长度
返回参数 : 成功返回:SUCCESS/失败返回:ERROR
使用说明 : 可下发可上报类型,需要在处理完数据后上报处理结果至app
*****************************************************************************/
static unsigned char dp_download_voice_play_handle(const unsigned char value[], unsigned short length)
{
    //示例:当前DP类型为BOOL
    unsigned char ret;
    //0:关/1:开
    unsigned char voice_play;
    
    voice_play = mcu_get_dp_download_bool(value,length);
    if(voice_play == 0) {
        //开关关
    }else {
        //开关开
    }
  
    //处理完DP数据后应有反馈
    ret = mcu_dp_bool_update(DPID_VOICE_PLAY,voice_play);
    if(ret == SUCCESS)
        return SUCCESS;
    else
        return ERROR;
}
/*****************************************************************************
函数名称 : dp_download_voice_bt_play_handle
功能描述 : 针对DPID_VOICE_BT_PLAY的处理函数
输入参数 : value:数据源数据
        : length:数据长度
返回参数 : 成功返回:SUCCESS/失败返回:ERROR
使用说明 : 可下发可上报类型,需要在处理完数据后上报处理结果至app
*****************************************************************************/
static unsigned char dp_download_voice_bt_play_handle(const unsigned char value[], unsigned short length)
{
    //示例:当前DP类型为BOOL
    unsigned char ret;
    //0:关/1:开
    unsigned char voice_bt_play;
    
    voice_bt_play = mcu_get_dp_download_bool(value,length);
    if(voice_bt_play == 0) {
        //开关关
    }else {
        //开关开
    }
  
    //处理完DP数据后应有反馈
    ret = mcu_dp_bool_update(DPID_VOICE_BT_PLAY,voice_bt_play);
    if(ret == SUCCESS)
        return SUCCESS;
    else
        return ERROR;
}
/*****************************************************************************
函数名称 : dp_download_voice_alarm_clock_handle
功能描述 : 针对DPID_VOICE_ALARM_CLOCK的处理函数
输入参数 : value:数据源数据
        : length:数据长度
返回参数 : 成功返回:SUCCESS/失败返回:ERROR
使用说明 : 可下发可上报类型,需要在处理完数据后上报处理结果至app
*****************************************************************************/
static unsigned char dp_download_voice_alarm_clock_handle(const unsigned char value[], unsigned short length)
{
    //示例:当前DP类型为STRING
    unsigned char ret;
    /*
    //STRING类型数据处理
    unsigned char string_data[8];
    
    string_data[0] = value[0];
    string_data[1] = value[1];
    string_data[2] = value[2];
    string_data[3] = value[3];
    string_data[4] = value[4];
    string_data[5] = value[5];
    string_data[6] = value[6];
    string_data[7] = value[7];
    */
    
    //处理完DP数据后应有反馈
    ret = mcu_dp_string_update(DPID_VOICE_ALARM_CLOCK,value, length);
    if(ret == SUCCESS)
        return SUCCESS;
    else
        return ERROR;
}
/*****************************************************************************
函数名称 : dp_download_voice_ctrl_group_handle
功能描述 : 针对DPID_VOICE_CTRL_GROUP的处理函数
输入参数 : value:数据源数据
        : length:数据长度
返回参数 : 成功返回:SUCCESS/失败返回:ERROR
使用说明 : 可下发可上报类型,需要在处理完数据后上报处理结果至app
*****************************************************************************/
static unsigned char dp_download_voice_ctrl_group_handle(const unsigned char value[], unsigned short length)
{
    //示例:当前DP类型为STRING
    unsigned char ret;
    /*
    //STRING类型数据处理
    unsigned char string_data[8];
    
    string_data[0] = value[0];
    string_data[1] = value[1];
    string_data[2] = value[2];
    string_data[3] = value[3];
    string_data[4] = value[4];
    string_data[5] = value[5];
    string_data[6] = value[6];
    string_data[7] = value[7];
    */
    
    //处理完DP数据后应有反馈
    ret = mcu_dp_string_update(DPID_VOICE_CTRL_GROUP,value, length);
    if(ret == SUCCESS)
        return SUCCESS;
    else
        return ERROR;
}



/******************************************************************************
                                WARNING!!!                     
This code is called internally by the SDK. 
Please implement the internal data of the function according to the actual dp data.
******************************************************************************/
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
void upgrade_package_choose(unsigned char package_sz)
{
  #error "Please implement the upgrade package size selection processing code by yourself. Please delete this line after completion"
  unsigned short length = 0;
  length = set_wifi_uart_byte(length,package_sz);
  wifi_uart_write_frame(UPDATE_START_CMD,MCU_SEND_VER,length);
}

/**
 * @brief  MCU enters firmware upgrade mode
 * @param[in] {value} Firmware buffer
 * @param[in] {position} The current data packet is in the firmware location
 * @param[in] {length} Current firmware package length (when the firmware package length is 0, it indicates that the firmware package is sent)
 * @return Null
 * @note   MCU needs to implement this function by itself
 */
unsigned char mcu_firm_update_handle(const unsigned char value[],unsigned long position,unsigned short length)
{
  #error "Please complete the MCU firmware upgrade processing code yourself. Please delete the line after completion"
  if(length == 0)
  {
    //Firmware data transmission completed
    
  }
  else
  {
    //Firmware data processing
  }
  
  return SUCCESS;
}
#endif

#ifdef SUPPORT_GREEN_TIME
/**
 * @brief  Gets the green time
 * @param[in] {time} Get the time data
 * @return Null
 * @note   MCU needs to implement this function by itself
 */
void mcu_get_greentime(unsigned char time[])
{
  #error "Complete the code yourself and delete the line"
  /*
  time[0] is the flag of success for obtaining the time,0: failure / 1: success
  time[1] is year, 0x00 :2000 year
  time[2] is month, It starts at 1 and ends at 12
  time[3] is date, It starts at 1 and ends at 31
  time[4] is hour, It starts at 0 and ends at 23
  time[5] is minute, It starts at 0 and ends at 59
  time[6] is second, It starts at 0 and ends at 59
*/
  if(time[0] == 1)
  {
    //Receive the green data returned by wifi module correctly
  }
  else
  {
  	//There is an error in obtaining the green time. It may be that the current wifi module is not connected to the Internet
  }
}
#endif

#ifdef SUPPORT_MCU_RTC_CHECK
/**
 * @brief  MCU proofreads local RTC clock
 * @param[in] {time} Get the time data
 * @return Null
 * @note   MCU needs to implement this function by itself
 */
void mcu_write_rtctime(unsigned char time[])
{
  #error "Please complete the RTC clock write code yourself and delete the line"
  /*
  Time[0] is the time success flag, 0 is a failure, and 1 is a success.
  Time[1] is the year and 0x00 is the year 2000.
  Time[2] is the month, starting from 1 to ending at 12
  Time[3] is the date, starting from 1 to 31
  Time[4] is the clock, starting from 0 to ending at 23
  Time[5] is minutes, starting from 0 to ending at 59
  Time[6] is seconds, starting from 0 to ending at 59
  Time[7] is the week, starting from 1 to 7 and 1 is Monday.
 */
  if(time[0] == 1)
  {
    //Correctly receive the local clock data returned by the wifi module
	 
  }
  else
  {
  	//Error getting local clock data, it may be that the current wifi module is not connected
  }
}
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
void wifi_test_result(unsigned char result,unsigned char rssi)
{
//  #error "Please implement the wifi function test success/failure code by yourself. Please delete the line after completion"
  if(result == 0)
  {
    //Test failed
    if(rssi == 0x00)
    {
      //Can't scan to the router named tuya_mdev_test, please check
    }
    else if(rssi == 0x01)
    {
      //Module not authorized
    }
  }
  else
  {
    //Test success
    //rssiis the signal strength (0-100, 0 signal is the worst, 100 signal is the strongest)
  }
  
}
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
void weather_open_return_handle(unsigned char res, unsigned char err)
{
  #error "Please complete the M open weather function to return the data processing code. Please delete the line after completion"
  unsigned char err_num = 0;
  
  if(res == 1)
  {
    //Open the weather and return successfully
  }
  else if(res == 0)
  {
    //Open weather return failed
    //Get the error code
    err_num = err; 
  }
}

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
void weather_data_user_handle(char *name, unsigned char type, const unsigned char *data, char day)
{
  #error "Here is just an example. Please correct the weather data processing code yourself. Please delete the line after you finish."
  int value_int;
  char value_string[50];//Since there are many parameters, the default is 50. You can reduce this value appropriately based on the defined parameters.
  
  my_memset(value_string, '\0', 50);
  
  //First get the data type
  if(type == 0) //The parameter is INT type
  {
    value_int = data[0] << 24 | data[1] << 16 | data[2] << 8 | data[3];
  }
  else if(type == 1)
  {
    my_strcpy(value_string, data);
  }
  
  //Note that the parameter value is obtained according to the selected parameter type! ! !
  if(my_strcmp(name, "temp") == 0)
  {
    printf("day:%d temp value is:%d\r\n", day, value_int);            //int type
  }
  else if(my_strcmp(name, "humidity") == 0)
  {
    printf("day:%d humidity value is:%d\r\n", day, value_int);        //int type
  }
  else if(my_strcmp(name, "pm25") == 0)
  {
    printf("day:%d pm25 value is:%d\r\n", day, value_int);            //int type
  }
  else if(my_strcmp(name, "condition") == 0)
  {
    printf("day:%d condition value is:%s\r\n", day, value_string);    //string type
  }
}
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
void get_upload_syn_result(unsigned char result)
{
  #error "Please complete the status report result processing code by yourself and delete the line"
    
  if(result == 0)
  {
  	//Synchronous report error
  }
  else
  {
    //Report synchronously successfully
  }
}
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
void get_wifi_status(unsigned char result)
{
  #error "Complete the get the WIFI status result processing code yourself and delete the line"
 
  switch(result) {
    case 0:
      //wifi working state 1
      break;
  
    case 1:
      //wifi working state 2
      break;
      
    case 2:
      //wifi working state 3
      break;
      
    case 3:
      //wifi working state 4
      break;
      
    case 4:
      //wifi working state 5
      break;
      
    case 5:
      //wifi working state 6
      break;
    
    case 6:
      //wifi working state 7
      break;
      
    default:
    break;
  }
}
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
unsigned char stream_trans_send(unsigned int id, unsigned char *buffer, unsigned long buf_len)
{
  #error "Here is just an example. Please correct the stream service delivery processing code yourself. Please delete the line after you finish."
  unsigned long map_offset = 0;
  unsigned int pack_num = 0;
  unsigned int rest_length = 0;

  if(stop_update_flag == ENABLE)
    return SUCCESS;

  pack_num = buf_len / STREM_PACK_LEN;
  rest_length = buf_len - pack_num * STREM_PACK_LEN;
  if (rest_length > 0)
  {
    pack_num++;
  }

  int this_len = STREM_PACK_LEN;
  for (int cnt = 0; cnt < pack_num; cnt++)
  {
    if (cnt == pack_num - 1 && rest_length > 0)
    {
      this_len = rest_length;
    }
    else
    {
      this_len = STREM_PACK_LEN;
    }

    if(SUCCESS == stream_trans(id, map_offset, buffer + map_offset, this_len))
    {
      //The MCU is being upgraded and cannot be streamed
      //printf("is upgrade\n");
      return SUCCESS;
    }

    //while(stream_status == 0xff); //Received back
    
    if(stream_status != 0)
    {
      return ERROR;
    }
  }
  
  return SUCCESS;
}

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
unsigned char maps_stream_trans_send(unsigned int id, unsigned char sub_id, unsigned char sub_id_pro_mode, unsigned char *buffer, unsigned long buf_len)
{
  #error "Here is just an example. Please correct the multi-map stream service delivery processing code yourself. Please delete the line after you finish."
  unsigned long map_offset = 0;
  unsigned int pack_num = 0;
  unsigned int rest_length = 0;
  unsigned char pro_ver = 0; //Map service protocol version, default is 0

  if(stop_update_flag == ENABLE)
    return SUCCESS;

  pack_num = buf_len / STREM_PACK_LEN;
  rest_length = buf_len - pack_num * STREM_PACK_LEN;
  if (rest_length > 0)
  {
    pack_num++;
  }

  int this_len = STREM_PACK_LEN;
  for (int cnt = 0; cnt < pack_num; cnt++)
  {
    if (cnt == pack_num - 1 && rest_length > 0)
    {
      this_len = rest_length;
    }
    else
    {
      this_len = STREM_PACK_LEN;
    }

    if(SUCCESS == maps_stream_trans(pro_ver, id, sub_id, sub_id_pro_mode, map_offset, buffer + map_offset, this_len))
    {
      //The MCU is being upgraded and cannot be streamed
      //printf("is upgrade\n");
      return SUCCESS;
    }

    //while(stream_status == 0xff); //Received back
    
    if(stream_status != 0)
    {
      return ERROR;
    }
  }
  
  return SUCCESS;
}
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
void wifi_connect_test_result(unsigned char result)
{
  #error "Please implement the successful/failed wifi function test processing code by yourself, and delete the line after completion"
  if(result == 0)
  {
    //The routing message failed to receive. Please check whether the routing packet sent is a complete JSON packet
  }
  else
  {
    //The routing information was received successfully. Please pay attention to the wifi working state of WIFI_STATE_CMD command
  }
}
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
void mcu_get_mac(unsigned char mac[])
{
  #error "Complete the MAC fetch processing code yourself and delete the line"
  /*
  mac[0] is whether to get the MAC success flag,  0x00 success, 0x01 failure
  mac[1]~mac[6]:When obtaining the MAC address flag bit MAC [0] is successful, it represents the valid MAC address of the module
 */
 
  if(mac[0] == 1)
  {
  	//Error getting MAC
  }
  else
  {
    //Receive the MAC address returned by wifi module correctly
  }
}
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
void get_ir_status(unsigned char result)
{
  #error "Please complete the infrared status processing code by yourself and delete the line"
  unsigned short length = 0;
    
  switch(result) {
    case 0:
      //Infrared state 1
      break;
  
    case 1:
      //Infrared state 2
      break;
      
    case 2:
      //Infrared state 3
      break;
      
    case 3:
      //Infrared state 4
      break;
      
    default:
    break;
  }
  
  wifi_uart_write_frame(GET_IR_STATUS_CMD,MCU_SEND_VER,length);
}
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
void ir_tx_rx_test_result(unsigned char result)
{
  #error "Please implement the infrared entry, send, receive, and test functions by yourself. Please delete this line after completion"
  if(result == 0)
  {
    //Infrared into the transceiver production test successful
  }
  else
  {
    //Infrared incoming transceiver production test failed, please check the sent packet
  }
}
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
void file_download_package_choose(unsigned char package_sz)
{
  #error "Please complete the file download package size selection processing code by yourself and delete the line"
  unsigned short length = 0;
  length = set_wifi_uart_byte(length,package_sz);
  wifi_uart_write_frame(FILE_DOWNLOAD_START_CMD,MCU_SEND_VER,length);
}

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
unsigned char file_download_handle(const unsigned char value[],unsigned long position,unsigned short length)
{
  #error "Please complete the file download selection processing code by yourself and delete the line"
  if(length == 0)
  {
    //File package data sending completed
    
  }
  else
  {
    //File package data processing
  }
  
  return SUCCESS;
}
#endif

#ifdef MODULE_EXPANDING_SERVICE_ENABLE
/**
 * @brief  Module time service notification results
 * @param[in] {value} Data buffer
 * @param[in] {length} Data buffer length
 * @return Null
 * @note   MCU needs to implement this function by itself
 */
void open_module_time_serve_result(const unsigned char value[], unsigned short length)
{
  #error "Please complete the Module time service notification results processing code by yourself and delete the line"
  unsigned char sub_cmd = value[0];
  
  switch(sub_cmd)
  {
    case 0x01: { //
      if(0x02 != length)
      {
        //Data length error
        return;
      }
      
      if(value[1] == 0)
      {
        //Service started successfully
      }
      else
      {
        //Service startup failure
      }
    }
    break;
    case 0x02: {
      if(0x09 != length)
      {
        //Data length error
        return;
      }
      
      unsigned char time_type = value[1]; //0x00:Green time    0x01:Local time
      unsigned char time_data[7];
      
      my_memcpy(time_data, value + 2, length - 2);
      /*
      Data[0] is the year and 0x00 is the year 2000.
      Data[1] is the month, starting from 1 to ending at 12
      Data[2] is the date, starting from 1 to 31
      Data[3] is the clock, starting from 0 to ending at 23
      Data[4] is minutes, starting from 0 to ending at 59
      Data[5] is seconds, starting from 0 to ending at 59
      Data[6] is the week, starting from 1 to 7 and 1 is Monday.
      */
      
      //Add the time data handling code here, with time_type as the time type
      
      unsigned short length = 0;
      length = set_wifi_uart_byte(length,sub_cmd);
      wifi_uart_write_frame(OPEN_MODULE_TIME_SERVE_CMD,MCU_SEND_VER,length);
    }
    break;
    default:break;
  }
}
#endif

#ifdef BLE_RELATED_FUNCTION_ENABLE
/**
 * @brief  Bluetooth functional test results
 * @param[in] {value} Data buffer
 * @param[in] {length} Data buffer length
 * @return Null
 * @note   MCU needs to implement this function by itself
 */
void BLE_test_result(const unsigned char value[], unsigned short length)
{
  #error "Please complete the Bluetooth functional test results processing code by yourself and delete the line"
  unsigned char sub_cmd = value[0];
  
  if(0x03 != length)
  {
    //Data length error
    return;
  }
  
  if(0x01 != sub_cmd)
  {
    //Subcommand error
    return;
  }
  
  unsigned char result = value[1];
  unsigned char rssi = value[2];
      
  if(result == 0)
  {
    //test failure 
    if(rssi == 0x00)
    {
      //Bluetooth beacon named ty_mdev is not scanned, please check
    }
    else if(rssi == 0x01)
    {
      //Module is not authorized
    }
  }
  else if(result == 0x01)
  {
    //Test success
    //rssiis the signal strength (0-100, 0 signal is the worst, 100 signal is the strongest)
  }
}
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
void get_voice_state_result(unsigned char result)
{
  #error "Please complete the get voice status code result processing code by yourself and delete the line"
  switch(result) {
    case 0:
      //idle
      break;
  
    case 1:
      //mic mute state
      break;
      
    case 2:
      //wake
      break;
      
    case 3:
      //recording
      break;
      
    case 4:
      //Recognizing
      break;
  
    case 5:
      //Identified successfully
      break;
      
    case 6:
      //Recognition failed
      break;
      
    default:
    break;
  }
}

/**
 * @brief  MIC mute setting
 * @param[in] {result} Mute setting value
 * @ref       0x00: mic on
 * @ref       0x01: mic mute
 * @return Null
 * @note   MCU needs to implement this function by itself
 */
void set_voice_MIC_silence_result(unsigned char result)
{
  #error "Please complete the MIC mute setting processing code by yourself and delete the line"
  if(result == 0)
  {
    //mic on
  }
  else
  {
    //mic mute
  }
}

/**
 * @brief  speaker volume setting result
 * @param[in] {result} Volume value
 * @ref       0~10: Volume range
 * @return Null
 * @note   MCU needs to implement this function by itself
 */
void set_speaker_voice_result(unsigned char result)
{
  #error "Please complete the speaker volume setting result processing code by yourself and delete the line"
  
}

/**
 * @brief  Audio production test results
 * @param[in] {result} Audio production test status
 * @ref       0x00: Turn off audio production test
 * @ref       0x01: mic1 audio loop test
 * @ref       0x02: mic2 audio loop test
 * @return Null
 * @note   MCU needs to implement this function by itself
 */
void voice_test_result(unsigned char result)
{
  #error "Please complete the audio production test results processing code by yourself and delete the line"
  if(result == 0x00)
  {
    //Turn off audio production test
  }
  else if(result == 0x01)
  {
    //mic1 audio loop test
  }
  else if(result == 0x02)
  {
    //mic2 audio loop test
  }
}

/**
 * @brief  Get wake up test result
 * @param[in] {result} Wake-up return value
 * @ref       0x00: Wake up successfully
 * @ref       0x01: Wake up failure (10s timeout failure)
 * @return Null
 * @note   MCU needs to implement this function by itself
 */
void voice_awaken_test_result(unsigned char result)
{
  #error "Please complete the wake up the test results processing code by yourself and delete the line"
  if(result == 0x00)
  {
    //Wake up successfully
  }
  else if(result == 0x01)
  {
    //Wake up failure
  }
}
#endif



/******************************************************************************
                                WARNING!!!                     
The following function users do not modify!!
******************************************************************************/

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
unsigned char dp_download_handle(unsigned char dpid,const unsigned char value[], unsigned short length)
{
  /*********************************
  Current function processing can issue/report data calls                    
  Need to implement the data processing in the specific function
  The result of the processing needs to be fed back to the APP, otherwise the APP will consider the delivery failure.
  ***********************************/
  unsigned char ret;
  switch(dpid)
  {
        case DPID_MEAL_PLAN:
            //喂食计划处理函数
            ret = dp_download_meal_plan_handle(value,length);
        break;
        case DPID_QUICK_FEED:
            //快速喂食处理函数
            ret = dp_download_quick_feed_handle(value,length);
        break;
        case DPID_MANUAL_FEED:
            //手动喂食处理函数
            ret = dp_download_manual_feed_handle(value,length);
        break;
        case DPID_UNIT:
            //单位转换处理函数
            ret = dp_download_unit_handle(value,length);
        break;
        case DPID_SLOW_FEED:
            //慢放喂食处理函数
            ret = dp_download_slow_feed_handle(value,length);
        break;
        case DPID_EXPORT_CALIBRATE:
            //出粮校准处理函数
            ret = dp_download_export_calibrate_handle(value,length);
        break;
        case DPID_WEIGHT_CALIBRATE:
            //余粮校准处理函数
            ret = dp_download_weight_calibrate_handle(value,length);
        break;
        case DPID_FACTORY_RESET:
            //恢复出厂处理函数
            ret = dp_download_factory_reset_handle(value,length);
        break;
        case DPID_VOICE_TIMES:
            //语音播放次数处理函数
            ret = dp_download_voice_times_handle(value,length);
        break;
        case DPID_LIGHT:
            //小夜灯处理函数
            ret = dp_download_light_handle(value,length);
        break;
        case DPID_SWITCH:
            //开关处理函数
            ret = dp_download_switch_handle(value,length);
        break;
        case DPID_VOICE_VOL:
            //音量控制处理函数
            ret = dp_download_voice_vol_handle(value,length);
        break;
        case DPID_VOICE_MIC:
            //麦克风开关处理函数
            ret = dp_download_voice_mic_handle(value,length);
        break;
        case DPID_VOICE_PLAY:
            //暂停/播放处理函数
            ret = dp_download_voice_play_handle(value,length);
        break;
        case DPID_VOICE_BT_PLAY:
            //蓝牙开/关处理函数
            ret = dp_download_voice_bt_play_handle(value,length);
        break;
        case DPID_VOICE_ALARM_CLOCK:
            //本地闹钟处理函数
            ret = dp_download_voice_alarm_clock_handle(value,length);
        break;
        case DPID_VOICE_CTRL_GROUP:
            //语音控制组合处理函数
            ret = dp_download_voice_ctrl_group_handle(value,length);
        break;

  default:
    break;
  }
  return ret;
}

/**
 * @brief  Get the sum of all dp commands
 * @param[in] Null
 * @return Sent the sum of the commands
 * @note   The function user cannot modify
 */
unsigned char get_download_cmd_total(void)
{
  return(sizeof(download_cmd) / sizeof(download_cmd[0]));
}

