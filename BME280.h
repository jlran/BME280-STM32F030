#ifndef _BME280_H_
#define _BME280_H_

#include "stm32f0xx_rcc.h"
#include "mySPI.h"
#include "USART1.h"
//初始化
/*
	sck pa5  scl
	miso pa6	sdo
	mosi pa7	sda
	cs  pa4
*/

#define 		 u8 unsigned char 
#define 	 	 BME280_ADDRESS                      0x76
/*
#define      BME280_REGISTER_DIG_T1              0x88
#define      BME280_REGISTER_DIG_T2              0x8A
#define      BME280_REGISTER_DIG_T3              0x8C

#define      BME280_REGISTER_DIG_P1              0x8E
#define      BME280_REGISTER_DIG_P2              0x90
#define      BME280_REGISTER_DIG_P3              0x92
#define      BME280_REGISTER_DIG_P4              0x94
#define      BME280_REGISTER_DIG_P5              0x96
#define      BME280_REGISTER_DIG_P6              0x98
#define      BME280_REGISTER_DIG_P7              0x9A
#define      BME280_REGISTER_DIG_P8              0x9C
#define      BME280_REGISTER_DIG_P9              0x9E

#define      BME280_REGISTER_DIG_H1              0xA1
#define      BME280_REGISTER_DIG_H2              0xE1
#define      BME280_REGISTER_DIG_H3              0xE3
#define      BME280_REGISTER_DIG_H4              0xE4
#define      BME280_REGISTER_DIG_H5              0xE5
#define      BME280_REGISTER_DIG_H6              0xE7

#define      BME280_REGISTER_CHIPID              0xD0
#define      BME280_REGISTER_VERSION             0xD1
#define      BME280_REGISTER_SOFTRESET           0xE0

#define      BME280_REGISTER_CAL26               0xE1 // R calibration stored in 0xE1-0xF0

#define      BME280_REGISTER_CONTROLHUMID        0xF2
#define      BME280_REGISTER_CONTROL             0xF4
#define      BME280_REGISTER_CONFIG              0xF5
#define      BME280_REGISTER_PRESSUREDATA        0xF7
#define      BME280_REGISTER_TEMPDATA            0xFA
#define      BME280_REGISTER_HUMIDDATA           0xFD
*/

//#define 		 BME280_TEMPERATURE_MSB_REG					 0xFA
//#define 		 BME280_TEMPERATURE_LSB_REG					 0xFB
//#define 		 BME280_TEMPERATURE_XLSB_REG				 0xFC


enum
	{
		BME280_REGISTER_DIG_T1              = 0x88,
		BME280_REGISTER_DIG_T2              = 0x8A,
		BME280_REGISTER_DIG_T3              = 0x8C,

		BME280_REGISTER_DIG_P1              = 0x8E,
		BME280_REGISTER_DIG_P2              = 0x90,
		BME280_REGISTER_DIG_P3              = 0x92,
		BME280_REGISTER_DIG_P4              = 0x94,
		BME280_REGISTER_DIG_P5              = 0x96,
		BME280_REGISTER_DIG_P6              = 0x98,
		BME280_REGISTER_DIG_P7              = 0x9A,
		BME280_REGISTER_DIG_P8              = 0x9C,
		BME280_REGISTER_DIG_P9              = 0x9E,

		BME280_REGISTER_DIG_H1              = 0xA1,
		BME280_REGISTER_DIG_H2              = 0xE1,
		BME280_REGISTER_DIG_H3              = 0xE3,
		BME280_REGISTER_DIG_H4              = 0xE4,
		BME280_REGISTER_DIG_H5              = 0xE5,
		BME280_REGISTER_DIG_H6              = 0xE7,

		BME280_REGISTER_CHIPID             = 0xD0,
		BME280_REGISTER_VERSION            = 0xD1,
		BME280_REGISTER_SOFTRESET          = 0xE0,

		BME280_REGISTER_CAL26              = 0xE1,  // R calibration stored in 0xE1-0xF0

		BME280_REGISTER_CONTROLHUMID       = 0xF2,
		BME280_REGISTER_CONTROL            = 0xF4,
		BME280_REGISTER_CONFIG             = 0xF5,
		BME280_REGISTER_PRESSUREDATA       = 0xF7,
		BME280_REGISTER_TEMPDATA           = 0xFA,
		BME280_REGISTER_HUMIDDATA          = 0xFD,
	};

typedef struct
	{
		uint16_t dig_T1;
		int16_t  dig_T2;
		int16_t  dig_T3;

		uint16_t dig_P1;
		int16_t  dig_P2;
		int16_t  dig_P3;
		int16_t  dig_P4;
		int16_t  dig_P5;
		int16_t  dig_P6;
		int16_t  dig_P7;
		int16_t  dig_P8;
		int16_t  dig_P9;

		uint8_t  dig_H1;
		int16_t  dig_H2;
		uint8_t  dig_H3;
		int16_t  dig_H4;
		int16_t  dig_H5;
		int8_t   dig_H6;
	} bme280_calib_data;

uint16_t BME280Begininit(); //初始化数据
	
double readTemperature();
double readHumidity();
double readPressure();
	
	
int16_t newreadCoefficients();
	
signed long int calibration_T(signed long int adc_T);
unsigned long int calibration_P(signed long int adc_P);
unsigned long int calibration_H(signed long int adc_H);
	

#endif