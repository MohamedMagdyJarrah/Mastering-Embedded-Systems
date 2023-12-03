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
	vuint32_t EXTICR1;
	vuint32_t EXTICR2;
	vuint32_t EXTICR3;
	vuint32_t EXTICR4;
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


/************************************** Clock Management *************************************/
#define CLOCK_AFIO_EN()						RCC->APB2ENR |= (1<<0)
#define CLOCK_GPIOA_EN()					RCC->APB2ENR |= (1<<2)
#define CLOCK_GPIOB_EN()					RCC->APB2ENR |= (1<<3)
#define CLOCK_GPIOC_EN()					RCC->APB2ENR |= (1<<4)
#define CLOCK_GPIOD_EN()					RCC->APB2ENR |= (1<<5)
#define CLOCK_GPIOE_EN()					RCC->APB2ENR |= (1<<6)

#endif /* INC_STM32F103X6_H_ */
