#ifndef __USART_2_H
#define __USART_2_H
#include "stdio.h"	
#include "sys.h" 

	  	
	
#define USART_2_REC_LEN  			76  	//�����������ֽ��� 76
#define EN_USART1_RX 			1		//ʹ�ܣ�1��/��ֹ��0������1����
	  	
extern u8  USART_2_RX_BUF[USART_2_REC_LEN]; //���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
extern u8 USART_2_RX_STA;         		//����״̬���	
extern u8 senor_Flag;
void Usart_SendByte( USART_TypeDef * pUSARTx, uint8_t ch);
void usart2_init(u32 bound);
#endif


