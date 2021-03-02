/**
  ******************************************************************************
  * @file           : HX711.h
  * @brief          : Weight sensor
  ******************************************************************************
  * @attention
  *
  *Copyright(C),2018-2020, TUYA_House www.tuya.comm
  ******************************************************************************
  */


#ifndef __HX711_H
#define __HX711_H

#ifdef __cplusplus
extern "C" {
#endif

	
	
	
#define Read_Weight 0xA3      //读取
#define Zero_Cal 		0xAA      //清零
#define Peel 			  0xAB      //去皮（临时清零）
#define Cancel_Peel 0xAC      //取消去皮（恢复）
 
	
void HX711_uart_write_frame(unsigned char cmd);
void HX711_uart_write_data(unsigned char *in, unsigned short len);
void HX711_uart_receive_input(unsigned char value);
void HX711_data_handle(void);
void turn_off_motor(void);
void turn_on_motor(void);	
	
	#ifdef __cplusplus
}
#endif

#endif


