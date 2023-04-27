# STM32-Telehealth_monitor
该项目是为别人做的毕业设计，是远程医疗监测系统
## 功能简介
采集温度 血氧 舒张压 收缩压 心率数据和经纬度数据，把这些信息上传机智云平台，并能在手机弹窗报警
## 所需硬件
- 定位模块ATGM336H
- 健康检测模块(同时检测血氧 舒张压 收缩压 心率数据)
- STM32F103C8T6单片机
- OLED显示屏
- DS18B20
- ESP8266 01S
## 引脚连接
### OLED屏部分
- SCL--PA4
- SDA--PA5
- VCC-3.3V
### 健康检测模块
- VCC---3.3V
- RXD----PA2
- TXD----PA3
- GND----GND
### DS18B20
- VCC---3.3V
- D0----PB8
- GND----GND
### 定位模块
- VCC----3.3V
- RXD----PA9
- TXD----PA10
- GND----GND
- PPS----悬空
### ESP8266部分
- VCC---3.3V
- RXD----PB10
- TXD----PB11
- GND---GND
- 其余悬空
## 碎碎念
仅作备份记录，参考价值低
