#ifndef __USART_2_H
#define __USART_2_H
#include "stdio.h"	
#include "sys.h" 

	  	
	
#define USART_2_REC_LEN  			76  	//定义最大接收字节数 76
#define EN_USART1_RX 			1		//使能（1）/禁止（0）串口1接收
	  	
extern u8  USART_2_RX_BUF[USART_2_REC_LEN]; //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符 
extern u8 USART_2_RX_STA;         		//接收状态标记	
extern u8 senor_Flag;
void Usart_SendByte( USART_TypeDef * pUSARTx, uint8_t ch);
void usart2_init(u32 bound);
#endif


