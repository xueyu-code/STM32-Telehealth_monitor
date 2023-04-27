#ifndef __DS18B20_H
#define	__DS18B20_H

#include "stm32f10x.h"

#define DS18B20_DQ_OUT(a)	if (a)	\
							GPIO_SetBits(GPIOB,GPIO_Pin_8);\
							else		\
							GPIO_ResetBits(GPIOB,GPIO_Pin_8)

#define DS18B20_DQ_IN      GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_8)


void DS18B20_IO_OUT(void);
void DS18B20_IO_IN(void);
void DS18B20_Rst(void);
u8 DS18B20_Check(void);
u8 DS18B20_Read_Bit(void); 			 // read one bit
u8 DS18B20_Read_Byte(void);    // read one byte
void DS18B20_Write_Byte(u8 dat);
void DS18B20_Start(void);// ds1820 start convert 	 
u8 DS18B20_Init(void);
short DS18B20_Get_Temp(void);


#endif 
