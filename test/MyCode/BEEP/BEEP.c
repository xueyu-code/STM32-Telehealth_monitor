#include "BEEP.h"
#include "delay.h"

void BEEP_Init(void)
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;				 //
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 GPIO_Init(GPIOB, &GPIO_InitStructure);					 //根据设定参数初始化GPIOB.0
 GPIO_SetBits(GPIOB,GPIO_Pin_1);	
}
 
void BEEP_ON(){                        //蜂鸣器响一声
	GPIO_ResetBits(GPIOB,GPIO_Pin_1);	
	delay_ms(1000);
	GPIO_SetBits(GPIOB,GPIO_Pin_1);
	
}

