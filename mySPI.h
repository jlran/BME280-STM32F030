#ifndef _MYSPI_H_
#define _MYSPI_H_

#include "stm32f0xx_spi.h"
#include "stm32f0xx_rcc.h"
#include "delay.h"

#define uint8 uint8_t


#define BME_CS 			0x0010    //pa4   cs
#define BME_SCK 		0x0020		//pa5		scl
#define BME_MISO 		0x0040		//pa6		sdo
#define BME_MOSI 		0x0080 		//pa7		sda

#define MISOR 			GPIO_ReadInputDataBit(GPIOA, 0x0040)
#define BME_SCKH 		GPIOA->BSRR = 0x0020
#define BME_SCKL 		GPIOA->BRR = 0x0020

#define BME_MOSIH 		GPIOA->BSRR = 0x0080
#define BME_MOSIL 		GPIOA->BRR = 0x0080

#define BME_CSH 		GPIOA->BSRR = 0x0010
#define BME_CSL 		GPIOA->BRR = 0x0010

uint16_t BmeReadReg();
void BME280init();
void SPI_Write_OneByte(uint8 u8_writedata);
uint8 SPI_Read_OneByte();

uint16_t SPI_Read_16();
int16_t SPI_Read_S16();

uint16_t read_16();

uint16_t  read16_LE(); // little endian
int16_t   readS16_LE(); // little endian

uint8 read8(uint8 addr);

#endif