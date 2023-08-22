#include <stdint.h>

typedef volatile unsigned int vuint32_t;

/*Base Addresses of the peripherals*/
#define RCC_BASE			0x40021000
#define GPIOA_BASE			0x40010800

/*Registers of the peripherals*/
#define RCC_APB2ENR			*(vuint32_t*)(RCC_BASE+0x18)
#define GPIOA_CRH			*(vuint32_t*)(GPIOA_BASE+0x04)
#define GPIOA_ODR			*(vuint32_t*)(GPIOA_BASE+0x0C)

typedef union{
	vuint32_t allfields;
	struct{
		vuint32_t reserved:13;
		vuint32_t P_13:1;
	}Pin;
}R_ODR_t;

volatile R_ODR_t* R_ODR = (volatile R_ODR_t*)(GPIOA_BASE+0x0C);

int main(void)
{
	uint32_t i=0;
	RCC_APB2ENR |= (1<<2);		/*Setting bit to enable clock for pin*/
	GPIOA_CRH &= 0xff0fffff;	/*Masking Register*/
	GPIOA_CRH |= 0x00200000;	/*Setting mode of the pin*/

	while(1)
	{
		/*Turning led on*/
		GPIOA_ODR |= (1<<13);
		for(i=0;i<5000;i++);
		/*Turning led off*/
		GPIOA_ODR &= ~(1<<13);
		for(i=0;i<5000;i++);

	//	/*Turning led on*/
	//	R_ODR->Pin.P_13 = 1;
	//	for(i=0;i<5000;i++);
	//	/*Turning led off*/
	//	R_ODR->Pin.P_13 = 0;
	//	for(i=0;i<5000;i++);

	}
	return 0;
}
