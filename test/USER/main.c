#include "stm32f10x.h"
#include "delay.h"
#include "usart.h"
#include "oled.h"
#include "usart2.h"
#include "timer.h"
#include "gizwits_product.h"
#include "math.h"
#include "bmp.h"
#include "usart_2.h"
#include "DS18B20.h"

//声明
void errorLog(int num);
void parseGpsBuffer(void);
void printGpsBuffer(void);
int string_num(char* num);
void get_gps_data(void);
void get_health_data(void);

char a[10];
int weidu=0;
int jingdu=0;
int time;
float weidu_1=3.51;
float jingdu_1=73.33;
float time_1;
float temper =0.0;
int hearts,Systolic,Diastole,spo2;//Systolic是收缩压 Diastole是舒张压
int low_hearts_flag,high_hearts_flag,low_blood_pressure_flag,high_blood_pressure_flag;
	//默认经纬度

int main(void)
{	

	
	
	delay_init();	    	 //延时函数初始化	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_3); //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
//	BEEP_Init();
	DS18B20_Init();
	uart_init(9600);	 //串口1 与定位模组通信
	usart2_init(38400);//串口2 与心率模组通信
	OLED_Init();
	 
	TIM3_Int_Init(71,999);				//一毫秒定时
    
	memset((uint8_t*)&currentDataPoint, 0, sizeof(dataPoint_t));//设备状态结构体初始化
	usart3_init((u32)9600);//WIFI初始化 串口3与WIFI模组通信
	gizwitsInit();//缓冲区初始化
//	gizwitsSetMode(WIFI_RESET_MODE);
	delay_ms(500);
//	gizwitsSetMode(WIFI_AIRLINK_MODE);
	gizwitsSetMode(WIFI_SOFTAP_MODE);
	 delay_ms(1000);

	clrStruct();

	//发送心率模组需要的指令
	Usart_SendByte(USART2, 0x8a);


	//显示相关字符信息
	OLED_ShowString(0,0,"Temper:",16,1);
	OLED_ShowString(0,16,"Hearts:",16,1);
	OLED_ShowString(0,32,"Systolic:",16,1);
	OLED_ShowString(0,48,"Diastole:",16,1);
	OLED_Refresh();
	while(1)
	{
		get_gps_data();
		get_health_data();
		temper= DS18B20_Get_Temp();
		OLED_ShowNum(100,0,temper,3,16,1);
		OLED_Refresh();
		
		//判断是否是高血压
		if((Diastole>=90)||(Systolic>=140))
		{
			high_blood_pressure_flag=1;
			low_blood_pressure_flag=0;
		}
		//判断是否是低血压
		if(Systolic<90)
		{
			low_blood_pressure_flag=1;
			high_blood_pressure_flag=0;
		}
		//判断是否心率过低
		if(hearts<60)
		{
			low_hearts_flag=1;
			high_hearts_flag=0;
		}
		//判断心率过高
		if(hearts>100)
		{
			high_hearts_flag=1;
			low_hearts_flag=0;
		}
		
		userHandle();
    gizwitsHandle((dataPoint_t *)&currentDataPoint);

	}
		

}




//显示心率等各项数据
void get_health_data(void)
{
		if(senor_Flag)
		{
			senor_Flag=0;
			hearts=USART_2_RX_BUF[65];
			Systolic=USART_2_RX_BUF[71];
			Diastole=USART_2_RX_BUF[72];
			spo2=USART_2_RX_BUF[66];
			OLED_ShowNum(100,16,hearts,3,16,1);
			OLED_ShowNum(100,32,Systolic,3,16,1);
			OLED_ShowNum(100,48,Diastole,3,16,1);
			OLED_Refresh();
		}

}
//以下是定位模组相关的函数
	
//获取经纬度数据
void get_gps_data(void)
{
		weidu=string_num(Save_Data.latitude);
		jingdu=string_num(Save_Data.longitude);
		time=string_num(Save_Data.UTCTime);
		time+=80000;
		weidu_1=(float)weidu/100.0;
		jingdu_1=(float)jingdu/100.0;
		
		time_1=(float)time/10000.0;
		
		parseGpsBuffer();
//		printGpsBuffer();
}

int string_num(char* num)			//该函数将接收到的字符串转成int型
{
	int i;
	int j;
	int temp;
	i=0;
	while(num[i]!=NULL)
	{
		if(num[i]=='.')
		{
			break;
		}
		i++;
	}
	for(j=i-1;j>=0;j--)
	{
		temp+=(int)(num[j]-'0')*pow(10,i-j-1);
	}
	return temp;
}






/***********GPS模块的函数**************************/
/***********编写：2022年3月25日23:33:15************/
/*************************************************/
void errorLog(int num)
{
	
	while (1)
	{
	  	printf("ERROR%d\r\n",num);
	}
}
void parseGpsBuffer()
{
	char *subString;
	char *subStringNext;
	char i = 0;
	if (Save_Data.isGetData)
	{
		Save_Data.isGetData = false;
//		printf("**************\r\n");
//		printf(Save_Data.GPS_Buffer);
		for (i = 0 ; i <= 6 ; i++)
		{
			if (i == 0)
			{
				if ((subString = strstr(Save_Data.GPS_Buffer, ",")) == NULL)
					errorLog(1);	//解析错误
			}
			else
			{
				subString++;
				if ((subStringNext = strstr(subString, ",")) != NULL)
				{
					char usefullBuffer[2]; 
					switch(i)
					{
						case 1:memcpy(Save_Data.UTCTime, subString, subStringNext - subString);break;	//获取UTC时间
						case 2:memcpy(usefullBuffer, subString, subStringNext - subString);break;	//获取UTC时间
						case 3:memcpy(Save_Data.latitude, subString, subStringNext - subString);break;	//获取纬度信息
						case 4:memcpy(Save_Data.N_S, subString, subStringNext - subString);break;	//获取N/S
						case 5:memcpy(Save_Data.longitude, subString, subStringNext - subString);break;	//获取经度信息
						case 6:memcpy(Save_Data.E_W, subString, subStringNext - subString);break;	//获取E/W

						default:break;
					}
					subString = subStringNext;
					Save_Data.isParseData = true;
					if(usefullBuffer[0] == 'A')
						Save_Data.isUsefull = true;
					else if(usefullBuffer[0] == 'V')
						Save_Data.isUsefull = false;
				}
				else
				{
					errorLog(2);	//解析错误
				}
			}
		}
	}
}

void printGpsBuffer()				//通过串口调试助手显示数据
{
	if (Save_Data.isParseData)
	{
		Save_Data.isParseData = false;
		
//	printf("Save_Data.UTCTime = ");
//	printf(Save_Data.UTCTime);
//	printf("\r\n");

		if(Save_Data.isUsefull)
		{
			Save_Data.isUsefull = false;
//			printf("Save_Data.latitude = ");
//			printf(Save_Data.latitude);
//			printf("\r\n");


//			printf("Save_Data.N_S = ");
//			printf(Save_Data.N_S);
//			printf("\r\n");

//			printf("Save_Data.longitude = ");
//			printf(Save_Data.longitude);
//			printf("\r\n");

//			printf("Save_Data.E_W = ");
//			printf(Save_Data.E_W);
//			printf("\r\n");
		}
		else
		{
//			printf("GPS DATA is not usefull!\r\n");
		}
		
	}
}
/**********************************/
/**********************************/
/***********GPS模块的函数***********/





