#include "mySPI.h"

/*
#define BME_SCK 		0x0020
#define BME_MISO 		0x0040
#define BME_MOSI 		0x0080 
#define BME_CS 			0x0010
*/

void BME280init(){
	    GPIO_InitTypeDef GPIO_InitStructure; 
			RCC_APB2PeriphClockCmd(GPIO_Pin_5|GPIO_Pin_7|GPIO_Pin_6 , ENABLE);
	  	//RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; 
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
			GPIO_Init(GPIOA, &GPIO_InitStructure);
		
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6; 
			GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_IN;
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
			GPIO_Init(GPIOA, &GPIO_InitStructure);
		
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; 
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
			GPIO_Init(GPIOA, &GPIO_InitStructure);
		
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; 
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
			GPIO_Init(GPIOA, &GPIO_InitStructure);  

			BME_CSH; 
}

void delay(){
	 int i =0;
	 for(i =0; i < 5; i++);
}

uint8 read8(uint8 addr){
		SPI_Write_OneByte(addr);
		return SPI_Read_OneByte();
}


uint8 SPI_Read_OneByte()
{
  uint8 i;
  uint8 temp = 0;
	
	BME_SCKL; 
	//开始
	//BME_CSL;  
	//循环读取
  for(i=0;i<8;i++)
  {
		temp <<= 1;
		BME_SCKH;	
		delay();
    
    if(MISOR)   
      temp |= 0x01;
    else
      temp &= ~0x01;
		BME_SCKL; 
		delay();
  }
	//结束
	//BME_CSH;   
  return temp;
}


uint16_t read_16(){
	uint16_t value;
	value = (SPI_Read_OneByte() << 8) | SPI_Read_OneByte();
	return value;
}


uint16_t SPI_Read_16()
{
  uint16_t i;
  uint16_t temp = 0;
	
	BME_SCKL; 
  for(i=0;i<16;i++)
  {
		temp <<= 1;
		BME_SCKH;	
		delay();
    
    if(MISOR)   
      temp |= 0x01;
    else
      temp &= ~0x01;
		BME_SCKL; 
		delay();
  } 
  return temp;
}


int16_t SPI_Read_S16(){	
  return (int16_t)read_16();
}

uint16_t  read16_LE() // little endian
{
		uint16_t temp = read_16();
    return (temp >> 8) | (temp << 8);
}

int16_t   readS16_LE() // little endian
{
	 return (int16_t)read16_LE();
}


void SPI_Write_OneByte(uint8 u8_writedata)
{
  uint8 i;  
	uint8 temp = 0;
	
	BME_SCKL; 
	//开始
	//BME_CSL;   
	
  for(i=0;i<8;i++)
  {
		//写入数据
    if(u8_writedata&0x80)     
			BME_MOSIH;                  
    else
			BME_MOSIL;   
		//延时
		delay();
		//高电平
     BME_SCKH;  
	   delay();
		 u8_writedata <<= 1; 
		 BME_SCKL; 
		
  }
	//结束
	//BME_CSH;   
}




//测试通过
uint16_t BmeReadReg(){
	  
	  uint16_t value;         
	  BME_CSL;
	  SPI_Write_OneByte(0xD0); 
  	value = SPI_Read_OneByte();
	  BME_CSH;
	  if(value == 0x60){
			return 1;
		}else{
			 return value;
		}
}
