#ifndef INC_STM32F103X6_H_
#define INC_STM32F103X6_H_

/*********************************************** Includes **********************************************/
#include "Utils.h"
#include "Platform_Types.h"

/**************************************** Memory Base Addresses ****************************************/
#define FLASH_MEMORY_BASE_ADD				0x08000000UL
#define SYSTEM_MEMORY_BASE_ADD				0x1FFFF800UL
#define SRAM_BASE_ADD						0x20000000UL
#define PERIPHERALS_BASE_ADD				0x40000000UL

/************************************** Core Peripherals  *************************************/
/*********************** NVIC ****************************/
#define NVIC_BASE_ADDERESS					0xE000E100UL
#define NVIC_ISER0							*((vuint32_t*)NVIC_BASE_ADDERESS+0x000)
#define NVIC_ISER1							*((vuint32_t*)NVIC_BASE_ADDERESS+0x004)
#define NVIC_ISER2							*((vuint32_t*)NVIC_BASE_ADDERESS+0x008)
#define NVIC_ICER0							*((vuint32_t*)NVIC_BASE_ADDERESS+0x080)
#define NVIC_ICER1							*((vuint32_t*)NVIC_BASE_ADDERESS+0x084)
#define NVIC_ICER2							*((vuint32_t*)NVIC_BASE_ADDERESS+0x088)

/************************************** Peripherals Base Addresses *************************************/
/*-------------------------------------------------------*/
/*---------- Base addresses of AHB Peripherals ----------*/
/*-------------------------------------------------------*/
/*********************** RCC ****************************/
#define RCC_BASE_ADDERESS					0x40021000UL



/*-------------------------------------------------------*/
/*---------- Base addresses of APB1 Peripherals ---------*/
/*-------------------------------------------------------*/



/*-------------------------------------------------------*/
/*---------- Base addresses of APB2 Peripherals ---------*/
/*-------------------------------------------------------*/
/*********************** GPIO ****************************/
#define GPIOA_BASE_ADDERESS					0x40010800UL
#define GPIOB_BASE_ADDERESS					0x40010C00UL
#define GPIOC_BASE_ADDERESS					0x40011000UL
#define GPIOD_BASE_ADDERESS					0x40011400UL
#define GPIOE_BASE_ADDERESS					0x40011800UL

/*********************** AFIO ****************************/
#define AFIO_BASE_ADDERESS					0x40010000UL

/*********************** EXTI ****************************/
#define EXTI_BASE_ADDERESS					0x40010400UL




/************************************** Peripherals Registers *************************************/
/*---------------------- RCC ---------------------------*/
typedef struct
{
	vuint32_t CR;
	vuint32_t CFGR;
	vuint32_t CIR;
	vuint32_t APB2RSTR;
	vuint32_t APB1RSTR;
	vuint32_t AHBENR;
	vuint32_t APB2ENR;
	vuint32_t APB1ENR;
	vuint32_t BDCR;
	vuint32_t CSR;
}RCC_t;

/*---------------------- GPIO --------------------------*/
typedef struct
{
	vuint32_t CRL;
	vuint32_t CRH;
	vuint32_t IDR;
	vuint32_t ODR;
	vuint32_t BSRR;
	vuint32_t BRR;
	vuint32_t LCKR;
}GPIO_t;

/*---------------------- AFIO --------------------------*/
typedef struct
{
	vuint32_t EVCR;
	vuint32_t MAPR;
	vuint32_t EXTICR[4];			// Merged the four EXTICR in array to ease the writing of the driver
	vuint32_t RESERVED0;
	vuint32_t MAPR2;
}AFIO_t;

/*---------------------- EXTI --------------------------*/
typedef struct
{
	vuint32_t IMR;
	vuint32_t EMR;
	vuint32_t RTSR;
	vuint32_t FTSR;
	vuint32_t SWIER;
	vuint32_t PR;
}EXTI_t;

/************************************** Peripherals Instants *************************************/
/*---------------------- RCC ---------------------------*/
#define RCC									((RCC_t*)RCC_BASE_ADDERESS)

/*---------------------- GPIO --------------------------*/
#define GPIOA								((GPIO_t*)GPIOA_BASE_ADDERESS)
#define GPIOB								((GPIO_t*)GPIOB_BASE_ADDERESS)
#define GPIOC								((GPIO_t*)GPIOC_BASE_ADDERESS)
#define GPIOD								((GPIO_t*)GPIOD_BASE_ADDERESS)
#define GPIOE								((GPIO_t*)GPIOE_BASE_ADDERESS)

/*---------------------- AFIO --------------------------*/
#define AFIO								((AFIO_t*)AFIO_BASE_ADDERESS)

/*---------------------- EXTI --------------------------*/
#define EXTI								((EXTI_t*)EXTI_BASE_ADDERESS)


/************************************** Peripherals Macros *************************************/
/*---------------------- EXTI --------------------------*/
// EXTI Lines
#define EXTI0          	0
#define EXTI1          	1
#define EXTI2          	2
#define EXTI3          	3
#define EXTI4          	4
#define EXTI5          	5
#define EXTI6          	6
#define EXTI7          	7
#define EXTI8          	8
#define EXTI9          	9
#define EXTI10          10
#define EXTI11          11
#define EXTI12          12
#define EXTI13          13
#define EXTI14          14
#define EXTI15          15

// EXTI IRQ Handlers
#define EXTI0_IRQ		6
#define EXTI1_IRQ		7
#define EXTI2_IRQ		8
#define EXTI3_IRQ		9
#define EXTI4_IRQ		10
#define EXTI5_IRQ		23
#define EXTI6_IRQ		23
#define EXTI7_IRQ		23
#define EXTI8_IRQ		23
#define EXTI9_IRQ		23
#define EXTI10_IRQ		40
#define EXTI11_IRQ		40
#define EXTI12_IRQ		40
#define EXTI13_IRQ		40
#define EXTI14_IRQ		40
#define EXTI15_IRQ		40


/************************************** Clock Management *************************************/
#define CLOCK_AFIO_EN()						RCC->APB2ENR |= (1<<0)
#define CLOCK_GPIOA_EN()					RCC->APB2ENR |= (1<<2)
#define CLOCK_GPIOB_EN()					RCC->APB2ENR |= (1<<3)
#define CLOCK_GPIOC_EN()					RCC->APB2ENR |= (1<<4)
#define CLOCK_GPIOD_EN()					RCC->APB2ENR |= (1<<5)
#define CLOCK_GPIOE_EN()					RCC->APB2ENR |= (1<<6)

/************************************** Core Peripherals Macros *************************************/
/*********************** NVIC ****************************/
#define NVIC_IRQ6_EXTI0_ENABLE				NVIC_ISER0 |= (1<<6);
#define NVIC_IRQ7_EXTI1_ENABLE				NVIC_ISER0 |= (1<<7);
#define NVIC_IRQ8_EXTI2_ENABLE				NVIC_ISER0 |= (1<<8);
#define NVIC_IRQ9_EXTI3_ENABLE				NVIC_ISER0 |= (1<<9);
#define NVIC_IRQ10_EXTI4_ENABLE				NVIC_ISER0 |= (1<<10);
#define NVIC_IRQ23_EXTI9_5_ENABLE			NVIC_ISER0 |= (1<<23);
#define NVIC_IRQ40_EXTI15_10_ENABLE			NVIC_ISER1 |= (1<<8);	//40(Vector table number) - 32(number of bits) = 8 (the index of interrupt in reg.)

#define NVIC_IRQ6_EXTI0_DISABLE				NVIC_ICER0 |= (1<<6);
#define NVIC_IRQ7_EXTI1_DISABLE				NVIC_ICER0 |= (1<<7);
#define NVIC_IRQ8_EXTI2_DISABLE				NVIC_ICER0 |= (1<<8);
#define NVIC_IRQ9_EXTI3_DISABLE				NVIC_ICER0 |= (1<<9);
#define NVIC_IRQ10_EXTI4_DISABLE			NVIC_ICER0 |= (1<<10);
#define NVIC_IRQ23_EXTI9_5_DISABLE			NVIC_ICER0 |= (1<<23);
#define NVIC_IRQ40_EXTI15_10_DISABLE		NVIC_ICER1 |= (1<<8);	//40(Vector table number) - 32(number of bits) = 8 (the index of interrupt in reg.)


#endif /* INC_STM32F103X6_H_ */
