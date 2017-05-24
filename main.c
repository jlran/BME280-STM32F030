#include "stm32f0xx.h"
#include "delay.h"
#include "USART1.h"
#include "mySPI.h"
#include "BME280.h"

//#include "BME280.h"

int main(void)
{
  delay_init();
  USART1_Init(115200);	
  BME280init();
	while(1){
		if(BME280Begininit() == 2){
			  printf("init....\n");
		  	delay_ms(500);
		}else{
			  printf("success!\n");
			break;
		}
	}
  while (1)
  {	 
		newreadCoefficients();
		delay_ms(1000);		
		delay_ms(1000);		
		delay_ms(1000);		
	  printf("\n-T-%f *C",readTemperature());
	  printf("\n-P-%f P",readPressure());
		delay_ms(1000);		
	  printf("\n-H-%f %%",readHumidity());
		delay_ms(1000);		
		delay_ms(1000);		
		delay_ms(1000);		
	} 
}

#ifdef  USE_FULL_ASSERT

void assert_failed(uint8_t* file, uint32_t line)
{

  while (1)
  {
  }
}
#endif

           