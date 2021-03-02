/**
  ******************************************************************************
  * @file           : HX711.c
  * @brief          : Weight sensor
  ******************************************************************************
  * @attention
  *
  *Copyright(C),2018-2020, TUYA_House www.tuya.comm
  ******************************************************************************
  */


#include "HX711.h"
#include "stm32g0xx_hal.h"
#include "main.h"

volatile unsigned char HX711_uart_tx_buf[5];
volatile unsigned char HX711_uart_rx_buf[10];
unsigned long Weight=0;
uint8_t count=0 ;
void HX711_uart_write_frame(unsigned char cmd)  //发送串口指令
{
	switch(cmd)
	{
		case  Read_Weight:                                //读取质量
		{
			HX711_uart_tx_buf[0]=cmd;
			HX711_uart_tx_buf[1]=0x00;
			HX711_uart_tx_buf[2]=0xA2;
			HX711_uart_tx_buf[3]=0xA4;
			HX711_uart_tx_buf[4]=0xA5;
		}
		break;
		case  Zero_Cal:                                   //清零（掉电保存）
		{
			HX711_uart_tx_buf[0]=cmd;
			HX711_uart_tx_buf[1]=0x00;
			HX711_uart_tx_buf[2]=0xA9;
			HX711_uart_tx_buf[3]=0xAB;
			HX711_uart_tx_buf[4]=0xA8;
		}
		break;	
		case  Peel:                                   		//去皮
		{
			HX711_uart_tx_buf[0]=cmd;
			HX711_uart_tx_buf[1]=0x00;
			HX711_uart_tx_buf[2]=0xAA;
			HX711_uart_tx_buf[3]=0xAC;
			HX711_uart_tx_buf[4]=0xAD;
		}
		break;
		case  Cancel_Peel:                                //取消去皮
		{
			HX711_uart_tx_buf[0]=cmd;
			HX711_uart_tx_buf[1]=0x00;
			HX711_uart_tx_buf[2]=0xAB;
			HX711_uart_tx_buf[3]=0xAD;
			HX711_uart_tx_buf[4]=0xAA;
		}
		break;
		default:break;
		
	}
	HX711_uart_write_data((unsigned char *)HX711_uart_tx_buf, 5);
	
  
}
void HX711_uart_write_data(unsigned char *in, unsigned short len) //串口数据发送
{
  if((NULL == in) || (0 == len))
  {
    return;
  }
  
  while(len --)
  {
    UART1_SendByte(*in);
    in ++;
  }
}


void HX711_uart_receive_input(unsigned char value) //串口数据接收
{
	if(count<10)
	{
		HX711_uart_rx_buf[count]=value;
		count++;
	}


}
void HX711_data_handle(void)    //接收数据处理
{
	unsigned char i=0;
		
	if(HX711_uart_rx_buf[0]==0xAA)
	{
		switch(HX711_uart_rx_buf[1])
		{
			case  Read_Weight:                                //读取质量
				Weight=HX711_uart_rx_buf[4]*65536+HX711_uart_rx_buf[5]*256+HX711_uart_rx_buf[6];
				break;
			case  Zero_Cal:
				break;
			default:break;
		}
//		for(i=0;i<10;i++)
//		{
//			HX711_uart_rx_buf[i]=0;  //buffer清零
//		}
		
	}

		
}

void turn_on_motor(void) 
{
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7,GPIO_PIN_SET );
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0,GPIO_PIN_RESET );
}

void turn_on_change_motor(void) 
{
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7,GPIO_PIN_RESET );
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0,GPIO_PIN_SET );
}
 
void turn_off_motor(void) 
{
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7,GPIO_PIN_RESET );
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0,GPIO_PIN_RESET );
}