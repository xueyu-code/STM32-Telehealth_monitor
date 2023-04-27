#include "BEEP.h"
#include "delay.h"

void BEEP_Init(void)
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;				 //
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
 GPIO_Init(GPIOB, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOB.0
 GPIO_SetBits(GPIOB,GPIO_Pin_1);	
}
 
void BEEP_ON(){                        //��������һ��
	GPIO_ResetBits(GPIOB,GPIO_Pin_1);	
	delay_ms(1000);
	GPIO_SetBits(GPIOB,GPIO_Pin_1);
	
}

