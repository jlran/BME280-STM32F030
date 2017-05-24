#include "BME280.h"

signed long int t_fine;
bme280_calib_data bme280_calib; 

/*
void SPI_Write_OneByte(uint8 u8_writedata);
uint8 SPI_Read_OneByte();
uint32_t SPI_Read_32();
uint16_t SPI_Read_16();
int16_t SPI_Read_S16();

uint16_t  read16_LE(); // little endian
int16_t   readS16_LE(); // little endian
*/

/*
========bme280_calib.dig_H1=======75
========bme280_calib.dig_H2=======366
========bme280_calib.dig_H3=======19
========bme280_calib.dig_H4=======49
========bme280_calib.dig_H5=======4095
========bme280_calib.dig_H6=======-1
*/

int16_t newreadCoefficients(){
	  uint8_t data[32],i=0;
	
//	
//		if(bme280_calib.dig_H1 == 75){
//			if(bme280_calib.dig_H2 == 366){
//				 if(bme280_calib.dig_H3 == 19){
//							return 0;
//				 }
//			}
//		}
	
	  BME_CSL;
    SPI_Write_OneByte(BME280_REGISTER_DIG_T1 | 0x80);
		for(i = 0; i < 24; i++){
			   data[i] = SPI_Read_OneByte();
		}
		bme280_calib.dig_H1 = read8(BME280_REGISTER_DIG_H1);
		
		 BME_CSH;
		
		 BME_CSL;
		
		SPI_Write_OneByte(BME280_REGISTER_DIG_H2);
    bme280_calib.dig_H2 = readS16_LE();
    bme280_calib.dig_H3 = read8(BME280_REGISTER_DIG_H3);
    bme280_calib.dig_H4 = (read8(BME280_REGISTER_DIG_H4) << 4) | (read8(BME280_REGISTER_DIG_H4+1) & 0x0F); 
    bme280_calib.dig_H5 = (read8(BME280_REGISTER_DIG_H5+1) << 4) | ((read8(BME280_REGISTER_DIG_H5) >> 4 & 0x0F)); 
    bme280_calib.dig_H6 = (int8_t)read8(BME280_REGISTER_DIG_H6);

	  BME_CSH;
		
		bme280_calib.dig_T1 = (data[1] << 8) | data[0];
    bme280_calib.dig_T2 = (data[3] << 8) | data[2];
    bme280_calib.dig_T3 = (data[5] << 8) | data[4];
		
    bme280_calib.dig_P1 = (data[7] << 8) | data[6];
    bme280_calib.dig_P2 = (data[9] << 8) | data[8];
    bme280_calib.dig_P3 = (data[11]<< 8) | data[10];
    bme280_calib.dig_P4 = (data[13]<< 8) | data[12];
    bme280_calib.dig_P5 = (data[15]<< 8) | data[14];
    bme280_calib.dig_P6 = (data[17]<< 8) | data[16];
    bme280_calib.dig_P7 = (data[19]<< 8) | data[18];
    bme280_calib.dig_P8 = (data[21]<< 8) | data[20];
    bme280_calib.dig_P9 = (data[23]<< 8) | data[22];
		
		
		printf("==bme280_calib.dig_H1=======%d\n",bme280_calib.dig_H1);
		printf("==bme280_calib.dig_H2=======%d\n",bme280_calib.dig_H2);
		printf("==bme280_calib.dig_H3=======%d\n",bme280_calib.dig_H3);
//		printf("==bme280_calib.dig_H4=======%d\n",bme280_calib.dig_H4);
//		printf("==bme280_calib.dig_H5=======%d\n",bme280_calib.dig_H5);
//		printf("==bme280_calib.dig_H6=======%d\n",bme280_calib.dig_H6);
		return 0;
}

uint16_t BME280Begininit(){

	uint8_t osrs_t = 1;             //Temperature oversampling x 1
	uint8_t osrs_p = 1;             //Pressure oversampling x 1
	uint8_t osrs_h = 1;             //Humidity oversampling x 1
	uint8_t mode = 3;               //Normal mode
	uint8_t t_sb = 5;               //Tstandby 1000ms
	uint8_t filter = 0;             //Filter off 
	uint8_t spi3w_en = 0;           //3-wire SPI Disable
	uint8_t ctrl_meas_reg = (osrs_t << 5) | (osrs_p << 2) | mode;
	uint8_t config_reg    = (t_sb << 5) | (filter << 2) | spi3w_en;
	uint8_t ctrl_hum_reg  = osrs_h;
	//读取数据
	if(BmeReadReg() != 0x01){
		//失败
		 return 2;
	}
	
	BME_CSL;
	
	SPI_Write_OneByte(0xF2& ~0x80);
	SPI_Write_OneByte(ctrl_hum_reg);
	
	SPI_Write_OneByte(0xF4& ~0x80);
	SPI_Write_OneByte(ctrl_meas_reg);
	
	SPI_Write_OneByte(0xF5& ~0x80);
	SPI_Write_OneByte(config_reg);
	
	BME_CSH;
	
	newreadCoefficients();
	

	return 0;
}



//温度
double readTemperature()
{
  int32_t var1, var2;
  int32_t adc_T;
	double T;
	
	BME_CSL;
	
	SPI_Write_OneByte((BME280_REGISTER_TEMPDATA) | 0x80);
	adc_T = read_16();
  adc_T <<= 8;
	SPI_Write_OneByte((BME280_REGISTER_TEMPDATA + 2) | 0x80);
  adc_T |= SPI_Read_OneByte();
  adc_T >>= 4;
	
	BME_CSH;

  return (double)calibration_T(adc_T)/100;
}

//压强
double readPressure() {
  int64_t var1, var2, p;
	int32_t adc_P;
  
	BME_CSL;
	
	SPI_Write_OneByte((BME280_REGISTER_PRESSUREDATA) | 0x80);
  adc_P = SPI_Read_16();
  adc_P <<= 8;
	SPI_Write_OneByte((BME280_REGISTER_PRESSUREDATA + 2) | 0x80);
  adc_P |= SPI_Read_OneByte();
  adc_P >>= 4;
	
  BME_CSH;
	
  return (double)calibration_P(adc_P)/256;
}

//湿度
double readHumidity() {
	
	int32_t v_x1_u32r;
	int32_t adc_H;
	double h;
	
	BME_CSL;
	
	SPI_Write_OneByte((BME280_REGISTER_HUMIDDATA) | 0x80);
  adc_H = SPI_Read_16();
	
	BME_CSH;

  return  (double)calibration_H(adc_H) / 1024.0;
}




//计算
signed long int calibration_T(signed long int adc_T)
{
    
    signed long int var1, var2, T;
    var1 = ((((adc_T >> 3) - ((signed long int)bme280_calib.dig_T1<<1))) * ((signed long int)bme280_calib.dig_T2)) >> 11;
    var2 = (((((adc_T >> 4) - ((signed long int)bme280_calib.dig_T1)) * ((adc_T>>4) - ((signed long int)bme280_calib.dig_T1))) >> 12) * ((signed long int)bme280_calib.dig_T3)) >> 14;
    
    t_fine = var1 + var2;
    T = (t_fine * 5 + 128) >> 8;
    return T; 
}

unsigned long int calibration_P(signed long int adc_P)
{
    signed long int var1, var2;
    unsigned long int P;
    var1 = (((signed long int)t_fine)>>1) - (signed long int)64000;
    var2 = (((var1>>2) * (var1>>2)) >> 11) * ((signed long int)bme280_calib.dig_P6);
    var2 = var2 + ((var1*((signed long int)bme280_calib.dig_P5))<<1);
    var2 = (var2>>2)+(((signed long int)bme280_calib.dig_P4)<<16);
    var1 = (((bme280_calib.dig_P3 * (((var1>>2)*(var1>>2)) >> 13)) >>3) + ((((signed long int)bme280_calib.dig_P2) * var1)>>1))>>18;
    var1 = ((((32768+var1))*((signed long int)bme280_calib.dig_P1))>>15);
    if (var1 == 0)
    {
        return 0;
    }    
    P = (((unsigned long int)(((signed long int)1048576)-adc_P)-(var2>>12)))*3125;
    if(P<0x80000000)
    {
       P = (P << 1) / ((unsigned long int) var1);   
    }
    else
    {
        P = (P / (unsigned long int)var1) * 2;    
    }
    var1 = (((signed long int)bme280_calib.dig_P9) * ((signed long int)(((P>>3) * (P>>3))>>13)))>>12;
    var2 = (((signed long int)(P>>2)) * ((signed long int)bme280_calib.dig_P8))>>13;
    P = (unsigned long int)((signed long int)P + ((var1 + var2 + bme280_calib.dig_P7) >> 4));
    return P;
}

unsigned long int calibration_H(signed long int adc_H)
{
    signed long int v_x1;
    
    v_x1 = (t_fine - ((signed long int)76800));
    v_x1 = (((((adc_H << 14) -(((signed long int)bme280_calib.dig_H4) << 20) - (((signed long int)bme280_calib.dig_H5) * v_x1)) + 
              ((signed long int)16384)) >> 15) * (((((((v_x1 * ((signed long int)bme280_calib.dig_H6)) >> 10) * 
              (((v_x1 * ((signed long int)bme280_calib.dig_H3)) >> 11) + ((signed long int) 32768))) >> 10) + (( signed long int)2097152)) * 
              ((signed long int) bme280_calib.dig_H2) + 8192) >> 14));
   v_x1 = (v_x1 - (((((v_x1 >> 15) * (v_x1 >> 15)) >> 7) * ((signed long int)bme280_calib.dig_H1)) >> 4));
   v_x1 = (v_x1 < 0 ? 0 : v_x1);
   v_x1 = (v_x1 > 419430400 ? 419430400 : v_x1);
   return (unsigned long int)(v_x1 >> 12);   
}

