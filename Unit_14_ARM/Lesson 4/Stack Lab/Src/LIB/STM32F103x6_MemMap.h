#ifndef INC_STM32F103X6_MEM_MAP_H_
#define INC_STM32F103X6_MEM_MAP_H_

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
#define NVIC_BASE_ADDERESS					(0xE000E100UL)
#define NVIC_ISER0							*(vuint32_t*)(NVIC_BASE_ADDERESS+0x000)
#define NVIC_ISER1							*(vuint32_t*)(NVIC_BASE_ADDERESS+0x004)
#define NVIC_ISER2							*(vuint32_t*)(NVIC_BASE_ADDERESS+0x008)
#define NVIC_ICER0							*(vuint32_t*)(NVIC_BASE_ADDERESS+0x080)
#define NVIC_ICER1							*(vuint32_t*)(NVIC_BASE_ADDERESS+0x084)
#define NVIC_ICER2							*(vuint32_t*)(NVIC_BASE_ADDERESS+0x088)

/************************************** Peripherals Base Addresses *************************************/
/*-------------------------------------------------------*/
/*---------- Base addresses of AHB Peripherals ----------*/
/*-------------------------------------------------------*/
/*********************** RCC ****************************/
#define RCC_BASE_ADDERESS					0x40021000UL



/*-------------------------------------------------------*/
/*---------- Base addresses of APB1 Peripherals ---------*/
/*-------------------------------------------------------*/
/*********************** USART2 ****************************/
#define USART2_BASE_ADDERESS				0x40014400UL

/*********************** USART3 ****************************/
#define USART3_BASE_ADDERESS				0x40014800UL


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

/*********************** USART1 ****************************/
#define USART1_BASE_ADDERESS				0x40013800UL


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

/*---------------------- USART ---------------------------*/
typedef struct
{
	vuint32_t SR;
	vuint32_t DR;
	vuint32_t BRR;
	vuint32_t CR1;
	vuint32_t CR2;
	vuint32_t CR3;
	vuint32_t GTPR;
}USART_t;

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
typedef struct
{
	uint8_t			EXTI_LINE		;
	GPIO_t*			EXTI_GPIO		;
	uint8_t 		GPIO_PIN		;
}EXTI_Setup_t;


/*---------------------- USART ---------------------------*/
#define USART1								((USART_t*)USART1_BASE_ADDERESS)
#define USART2								((USART_t*)USART2_BASE_ADDERESS)
#define USART3								((USART_t*)USART3_BASE_ADDERESS)

/************************************ Macros Configuration References *********************************/
/*---------------------- GPIO --------------------------*/
// @ref GPIO_PIN_define
#define GPIO_PIN_0						((uint8_t)0)		/* Pin 0 is selected */
#define GPIO_PIN_1						((uint8_t)1)		/* Pin 1 is selected */
#define GPIO_PIN_2						((uint8_t)2)		/* Pin 2 is selected */
#define GPIO_PIN_3						((uint8_t)3)		/* Pin 3 is selected */
#define GPIO_PIN_4						((uint8_t)4)		/* Pin 4 is selected */
#define GPIO_PIN_5						((uint8_t)5)		/* Pin 5 is selected */
#define GPIO_PIN_6						((uint8_t)6)		/* Pin 6 is selected */
#define GPIO_PIN_7						((uint8_t)7)		/* Pin 7 is selected */
#define GPIO_PIN_8						((uint8_t)8)		/* Pin 8 is selected */
#define GPIO_PIN_9						((uint8_t)9)		/* Pin 9 is selected */
#define GPIO_PIN_10						((uint8_t)10)		/* Pin 10 is selected */
#define GPIO_PIN_11						((uint8_t)11)		/* Pin 11 is selected */
#define GPIO_PIN_12						((uint8_t)12)		/* Pin 12 is selected */
#define GPIO_PIN_13						((uint8_t)13)		/* Pin 13 is selected */
#define GPIO_PIN_14						((uint8_t)14)		/* Pin 14 is selected */
#define GPIO_PIN_15						((uint8_t)15)		/* Pin 15 is selected */

//@ref GPIO_PINSTATE_define
#define GPIO_PINSTATE_HIGH							1
#define GPIO_PINSTATE_LOW							0

//@ref GPIO_PORTSTATE_define
#define GPIO_PORTSTATE_HIGH							0xffff
#define GPIO_PORTSTATE_LOW							0x0000

//@ref GPIO_LOCKSTATE_define
#define GPIO_LOCKSTATE_ERROR						1
#define GPIO_LOCKSTATE_NOERROR						0

// @ref GPIO_PIN_MODE_define
// 0: Analog mode
// 1: Floating input (reset state)
// 2: Input with pull-up
// 3: Input with pull-down
// 4: General purpose output push-pull
// 5: General purpose output Open-drain
// 6: Alternate function output Push-pull
// 7: Alternate function output Open-drain
// 8: Alternate function input
#define GPIO_PIN_MODE_ANALOG							0b0000		/* Analog mode */
#define GPIO_PIN_MODE_INPUT_FLOATING					0b0100		/* Floating input (reset state) */
#define GPIO_PIN_MODE_INPUT_PULL_UP						0b1000		/* Input with pull-up */
#define GPIO_PIN_MODE_INPUT_PULL_DOWN					0b1000		/* Input with pull-down */
#define GPIO_PIN_MODE_OUTPUT_PUSH_PULL_10_MHZ			0b0001		/* General purpose output Push-pull with speed 10 MHZ */
#define GPIO_PIN_MODE_OUTPUT_OPEN_DRAIN_10_MHZ			0b0101		/* General purpose output Open-drain with speed 10 MHZ */
#define GPIO_PIN_MODE_ALTERNATE_PUSH_PULL_10_MHZ		0b1001		/* Alternate function output Push-pull with speed 10 MHZ */
#define GPIO_PIN_MODE_ALTERNATE_OPEN_DRAIN_10_MHZ		0b1101		/* Alternate function output Open-drain with speed 10 MHZ */
#define GPIO_PIN_MODE_OUTPUT_PUSH_PULL_2_MHZ			0b0010		/* General purpose output Push-pull with speed 2 MHZ */
#define GPIO_PIN_MODE_OUTPUT_OPEN_DRAIN_2_MHZ			0b0110		/* General purpose output Open-drain with speed 2 MHZ */
#define GPIO_PIN_MODE_ALTERNATE_PUSH_PULL_2_MHZ			0b1010		/* Alternate function output Push-pull with speed 2 MHZ */
#define GPIO_PIN_MODE_ALTERNATE_OPEN_DRAIN_2_MHZ		0b1110		/* Alternate function output Open-drain with speed 2 MHZ */
#define GPIO_PIN_MODE_OUTPUT_PUSH_PULL_50_MHZ			0b0011		/* General purpose output Push-pull with speed 50 MHZ */
#define GPIO_PIN_MODE_OUTPUT_OPEN_DRAIN_50_MHZ			0b0111		/* General purpose output Open-drain with speed 50 MHZ */
#define GPIO_PIN_MODE_ALTERNATE_PUSH_PULL_50_MHZ		0b1011		/* Alternate function output Push-pull with speed 50 MHZ */
#define GPIO_PIN_MODE_ALTERNATE_OPEN_DRAIN_50_MHZ		0b1111		/* Alternate function output Open-drain with speed 50 MHZ */
#define GPIO_PIN_MODE_ALTERNATE_INPUT					0b0100		/* Alternate function input */
// for Whole Port @ref GPIO_PORT_MODE_define
#define GPIO_PORT_MODE_INPUT_FLOATING				    0x44444444	/* All port configured as Floating input (reset state) */
#define GPIO_PORT_MODE_INPUT_PULL_UP				    0x88888888	/* All port configured as Input with pull-up */
#define GPIO_PORT_MODE_INPUT_PULL_DOWN				    0x88888888	/* All port configured as Input with pull-down */
#define GPIO_PORT_MODE_OUTPUT_PUSH_PULL_10_MHZ		    0x11111111	/* All port configured as output Push-pull with speed 10 MHZ */
#define GPIO_PORT_MODE_OUTPUT_OPEN_DRAIN_10_MHZ		    0x55555555	/* All port configured as output Open-drain with speed 10 MHZ */
#define GPIO_PORT_MODE_ALTERNATE_PUSH_PULL_10_MHZ	    0x99999999	/* All port configured as Alternate output Push-pull with speed 10 MHZ */
#define GPIO_PORT_MODE_ALTERNATE_OPEN_DRAIN_10_MHZ	    0xDDDDDDDD	/* All port configured as Alternate output Open-drain with speed 10 MHZ */
#define GPIO_PORT_MODE_OUTPUT_PUSH_PULL_2_MHZ		    0x22222222	/* All port configured as output Push-pull with speed 2 MHZ */
#define GPIO_PORT_MODE_OUTPUT_OPEN_DRAIN_2_MHZ		    0x66666666	/* All port configured as output Open-drain with speed 2 MHZ */
#define GPIO_PORT_MODE_ALTERNATE_PUSH_PULL_2_MHZ	    0xAAAAAAAA	/* All port configured as Alternate output Push-pull with speed 2 MHZ */
#define GPIO_PORT_MODE_ALTERNATE_OPEN_DRAIN_2_MHZ	    0xEEEEEEEE	/* All port configured as Alternate output Open-drain with speed 2 MHZ */
#define GPIO_PORT_MODE_OUTPUT_PUSH_PULL_50_MHZ		    0x33333333	/* All port configured as output Push-pull with speed 50 MHZ */
#define GPIO_PORT_MODE_OUTPUT_OPEN_DRAIN_50_MHZ		    0x77777777	/* All port configured as output Open-drain with speed 50 MHZ */
#define GPIO_PORT_MODE_ALTERNATE_PUSH_PULL_50_MHZ	    0xBBBBBBBB	/* All port configured as Alternate output Push-pull with speed 50 MHZ */
#define GPIO_PORT_MODE_ALTERNATE_OPEN_DRAIN_50_MHZ	    0xFFFFFFFF	/* All port configured as Alternate output Open-drain with speed 50 MHZ */
#define GPIO_PORT_MODE_ALTERNATE_INPUT				    0x44444444	/* All port configured as Alternate input */

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


//@ref EXTI_TRIGGER_define
#define EXTI_TRIGGER_RISING						0
#define EXTI_TRIGGER_FALLING					1
#define EXTI_TRIGGER_RISING_AND_FALLING			2

//@ref EXTI_STATE_define
#define EXTI_STATE_ENABLE						1
#define EXTI_STATE_DISABLE						0


//@ref EXTI_PIN_define
#define EXTI_PIN_LINE0PA0          	 (EXTI_Setup_t){EXTI0,GPIOA,GPIO_PIN_0}
#define EXTI_PIN_LINE0PB0          	 (EXTI_Setup_t){EXTI0,GPIOB,GPIO_PIN_0}
#define EXTI_PIN_LINE0PC0          	 (EXTI_Setup_t){EXTI0,GPIOC,GPIO_PIN_0}
#define EXTI_PIN_LINE0PD0          	 (EXTI_Setup_t){EXTI0,GPIOD,GPIO_PIN_0}

#define EXTI_PIN_LINE1PA1          	 (EXTI_Setup_t){EXTI1,GPIOA,GPIO_PIN_1}
#define EXTI_PIN_LINE1PB1          	 (EXTI_Setup_t){EXTI1,GPIOB,GPIO_PIN_1}
#define EXTI_PIN_LINE1PC1          	 (EXTI_Setup_t){EXTI1,GPIOC,GPIO_PIN_1}
#define EXTI_PIN_LINE1PD1          	 (EXTI_Setup_t){EXTI1,GPIOD,GPIO_PIN_1}

#define EXTI_PIN_LINE2PA2          	 (EXTI_Setup_t){EXTI2,GPIOA,GPIO_PIN_2}
#define EXTI_PIN_LINE2PB2        	 (EXTI_Setup_t){EXTI2,GPIOB,GPIO_PIN_2}
#define EXTI_PIN_LINE2PC2          	 (EXTI_Setup_t){EXTI2,GPIOC,GPIO_PIN_2}
#define EXTI_PIN_LINE2PD2          	 (EXTI_Setup_t){EXTI2,GPIOD,GPIO_PIN_2}

#define EXTI_PIN_LINE3PA3          	 (EXTI_Setup_t){EXTI3,GPIOA,GPIO_PIN_3}
#define EXTI_PIN_LINE3PB3          	 (EXTI_Setup_t){EXTI3,GPIOB,GPIO_PIN_3}
#define EXTI_PIN_LINE3PC3          	 (EXTI_Setup_t){EXTI3,GPIOC,GPIO_PIN_3}
#define EXTI_PIN_LINE3PD3          	 (EXTI_Setup_t){EXTI3,GPIOD,GPIO_PIN_3}

#define EXTI_PIN_LINE4PA4          	 (EXTI_Setup_t){EXTI4,GPIOA,GPIO_PIN_4}
#define EXTI_PIN_LINE4PB4          	 (EXTI_Setup_t){EXTI4,GPIOB,GPIO_PIN_4}
#define EXTI_PIN_LINE4PC4          	 (EXTI_Setup_t){EXTI4,GPIOC,GPIO_PIN_4}
#define EXTI_PIN_LINE4PD4          	 (EXTI_Setup_t){EXTI4,GPIOD,GPIO_PIN_4}

#define EXTI_PIN_LINE5PA5          	 (EXTI_Setup_t){EXTI5,GPIOA,GPIO_PIN_5}
#define EXTI_PIN_LINE5PB5          	 (EXTI_Setup_t){EXTI5,GPIOB,GPIO_PIN_5}
#define EXTI_PIN_LINE5PC5          	 (EXTI_Setup_t){EXTI5,GPIOC,GPIO_PIN_5}
#define EXTI_PIN_LINE5PD5          	 (EXTI_Setup_t){EXTI5,GPIOD,GPIO_PIN_5}

#define EXTI_PIN_LINE6PA6          	 (EXTI_Setup_t){EXTI6,GPIOA,GPIO_PIN_6}
#define EXTI_PIN_LINE6PB6          	 (EXTI_Setup_t){EXTI6,GPIOB,GPIO_PIN_6}
#define EXTI_PIN_LINE6PC6          	 (EXTI_Setup_t){EXTI6,GPIOC,GPIO_PIN_6}
#define EXTI_PIN_LINE6PD6          	 (EXTI_Setup_t){EXTI6,GPIOD,GPIO_PIN_6}

#define EXTI_PIN_LINE7PA7          	 (EXTI_Setup_t){EXTI7,GPIOA,GPIO_PIN_7}
#define EXTI_PIN_LINE7PB7          	 (EXTI_Setup_t){EXTI7,GPIOB,GPIO_PIN_7}
#define EXTI_PIN_LINE7PC7          	 (EXTI_Setup_t){EXTI7,GPIOC,GPIO_PIN_7}
#define EXTI_PIN_LINE7PD7          	 (EXTI_Setup_t){EXTI7,GPIOD,GPIO_PIN_7}

#define EXTI_PIN_LINE8PA8          	 (EXTI_Setup_t){EXTI8,GPIOA,GPIO_PIN_8}
#define EXTI_PIN_LINE8PB8          	 (EXTI_Setup_t){EXTI8,GPIOB,GPIO_PIN_8}
#define EXTI_PIN_LINE8PC8          	 (EXTI_Setup_t){EXTI8,GPIOC,GPIO_PIN_8}
#define EXTI_PIN_LINE8PD8          	 (EXTI_Setup_t){EXTI8,GPIOD,GPIO_PIN_8}

#define EXTI_PIN_LINE9PA9          	 (EXTI_Setup_t){EXTI9,GPIOA,GPIO_PIN_9}
#define EXTI_PIN_LINE9PB9          	 (EXTI_Setup_t){EXTI9,GPIOB,GPIO_PIN_9}
#define EXTI_PIN_LINE9PC9          	 (EXTI_Setup_t){EXTI9,GPIOC,GPIO_PIN_9}
#define EXTI_PIN_LINE9PD9          	 (EXTI_Setup_t){EXTI9,GPIOD,GPIO_PIN_9}

#define EXTI_PIN_LINE10PA10          (EXTI_Setup_t){EXTI10,GPIOA,GPIO_PIN_10}
#define EXTI_PIN_LINE10PB10          (EXTI_Setup_t){EXTI10,GPIOB,GPIO_PIN_10}
#define EXTI_PIN_LINE10PC10          (EXTI_Setup_t){EXTI10,GPIOC,GPIO_PIN_10}
#define EXTI_PIN_LINE10PD10          (EXTI_Setup_t){EXTI10,GPIOD,GPIO_PIN_10}

#define EXTI_PIN_LINE11PA11          (EXTI_Setup_t){EXTI11,GPIOA,GPIO_PIN_11}
#define EXTI_PIN_LINE11PB11          (EXTI_Setup_t){EXTI11,GPIOB,GPIO_PIN_11}
#define EXTI_PIN_LINE11PC11          (EXTI_Setup_t){EXTI11,GPIOC,GPIO_PIN_11}
#define EXTI_PIN_LINE11PD11          (EXTI_Setup_t){EXTI11,GPIOD,GPIO_PIN_11}

#define EXTI_PIN_LINE12PA12          (EXTI_Setup_t){EXTI12,GPIOA,GPIO_PIN_12}
#define EXTI_PIN_LINE12PB12          (EXTI_Setup_t){EXTI12,GPIOB,GPIO_PIN_12}
#define EXTI_PIN_LINE12PC12          (EXTI_Setup_t){EXTI12,GPIOC,GPIO_PIN_12}
#define EXTI_PIN_LINE12PD12          (EXTI_Setup_t){EXTI12,GPIOD,GPIO_PIN_12}

#define EXTI_PIN_LINE13PA13          (EXTI_Setup_t){EXTI13,GPIOA,GPIO_PIN_13}
#define EXTI_PIN_LINE13PB13          (EXTI_Setup_t){EXTI13,GPIOB,GPIO_PIN_13}
#define EXTI_PIN_LINE13PC13          (EXTI_Setup_t){EXTI13,GPIOC,GPIO_PIN_13}
#define EXTI_PIN_LINE13PD13          (EXTI_Setup_t){EXTI13,GPIOD,GPIO_PIN_13}

#define EXTI_PIN_LINE14PA14          (EXTI_Setup_t){EXTI14,GPIOA,GPIO_PIN_14}
#define EXTI_PIN_LINE14PB14          (EXTI_Setup_t){EXTI14,GPIOB,GPIO_PIN_14}
#define EXTI_PIN_LINE14PC14          (EXTI_Setup_t){EXTI14,GPIOC,GPIO_PIN_14}
#define EXTI_PIN_LINE14PD14          (EXTI_Setup_t){EXTI14,GPIOD,GPIO_PIN_14}

#define EXTI_PIN_LINE15PA15          (EXTI_Setup_t){EXTI15,GPIOA,GPIO_PIN_15}
#define EXTI_PIN_LINE15PB15          (EXTI_Setup_t){EXTI15,GPIOB,GPIO_PIN_15}
#define EXTI_PIN_LINE15PC15          (EXTI_Setup_t){EXTI15,GPIOC,GPIO_PIN_15}
#define EXTI_PIN_LINE15PD15          (EXTI_Setup_t){EXTI15,GPIOD,GPIO_PIN_15}


/*---------------------- USART Baudrate Calculations --------------------------*/
#define USARTDIV(_PCLK,_BAUDRATE)           	(uint32_t)(_PCLK/(_BAUDRATE*16))
#define USARTDIV_MUL100(_PCLK,_BAUDRATE)    	(uint32_t)((_PCLK*25)/(_BAUDRATE*4))
#define MANTISSA_MUL100(_PCLK,_BAUDRATE)   	 	(uint32_t)(USARTDIV(_PCLK,_BAUDRATE)*100)
#define MANTISSA(_PCLK,_BAUDRATE)          		(uint32_t)(USARTDIV(_PCLK,_BAUDRATE))
#define FRACTION_DIV(_PCLK,_BAUDRATE)       	(uint32_t)(((USARTDIV_MUL100(_PCLK,_BAUDRATE) - MANTISSA_MUL100(_PCLK,_BAUDRATE))*16)/100)
#define USART_BRR_REGISTER(_PCLK,_BAUDRATE)     (uint32_t)((USARTDIV(_PCLK,_BAUDRATE)<<4) | (FRACTION_DIV(_PCLK,_BAUDRATE) & 0xF))

/************************************** Clock Management (RCC) *****************************************/
#define HSI_CLK							(uint32_t)8000000
/* APB2 Peripherals */
#define RCC_AFIO_EN()					RCC->APB2ENR |= (1<<0)
#define RCC_GPIOA_EN()					RCC->APB2ENR |= (1<<2)
#define RCC_GPIOB_EN()					RCC->APB2ENR |= (1<<3)
#define RCC_GPIOC_EN()					RCC->APB2ENR |= (1<<4)
#define RCC_GPIOD_EN()					RCC->APB2ENR |= (1<<5)
#define RCC_GPIOE_EN()					RCC->APB2ENR |= (1<<6)
#define RCC_ADC1_EN()                   RCC->APB2ENR |= (1<<9)
#define RCC_ADC2_EN()                   RCC->APB2ENR |= (1<<10)
#define RCC_TIM1_EN()                   RCC->APB2ENR |= (1<<11)
#define RCC_SPI1_EN()                   RCC->APB2ENR |= (1<<12)
#define RCC_TIM8_EN()                   RCC->APB2ENR |= (1<<13)
#define RCC_USART1_EN()                 RCC->APB2ENR |= (1<<14)
#define RCC_ADC3_EN()                   RCC->APB2ENR |= (1<<15)
#define RCC_TIM9_EN()                   RCC->APB2ENR |= (1<<19)
#define RCC_TIM10_EN()                  RCC->APB2ENR |= (1<<20)
#define RCC_TIM11_EN()                  RCC->APB2ENR |= (1<<21)
/* AHB Peripherals */
#define RCC_DMA1_EN()                   RCC->AHBENR |= (1<<0)
#define RCC_DMA2_EN()                   RCC->AHBENR |= (1<<1)
#define RCC_SRAM_EN()                   RCC->AHBENR |= (1<<2)
#define RCC_FLITF_EN()                  RCC->AHBENR |= (1<<4)
#define RCC_CRC_EN()                    RCC->AHBENR |= (1<<6)
#define RCC_FSMC_EN()                   RCC->AHBENR |= (1<<8)
#define RCC_SDIO_EN()                   RCC->AHBENR |= (1<<10)
/* APB1 Peripherals */
#define RCC_TIM2_EN()					RCC->APB1ENR |= (1<<0)
#define RCC_TIM3_EN()					RCC->APB1ENR |= (1<<1)
#define RCC_TIM4_EN()					RCC->APB1ENR |= (1<<2)
#define RCC_TIM5_EN()					RCC->APB1ENR |= (1<<3)
#define RCC_TIM6_EN()					RCC->APB1ENR |= (1<<4)
#define RCC_TIM7_EN()					RCC->APB1ENR |= (1<<5)
#define RCC_TIM12_EN()                  RCC->APB1ENR |= (1<<6)
#define RCC_TIM13_EN()                  RCC->APB1ENR |= (1<<7)
#define RCC_TIM14_EN()                  RCC->APB1ENR |= (1<<8)
#define RCC_WWD_EN()                    RCC->APB1ENR |= (1<<11)
#define RCC_SPI2_EN()					RCC->APB1ENR |= (1<<14)
#define RCC_SPI3_EN()                  	RCC->APB1ENR |= (1<<15)
#define RCC_USART2_EN()                 RCC->APB1ENR |= (1<<17)
#define RCC_USART3_EN()                 RCC->APB1ENR |= (1<<18)
#define RCC_UART4_EN()                  RCC->APB1ENR |= (1<<19)
#define RCC_UART5_EN()                  RCC->APB1ENR |= (1<<20)
#define RCC_I2C1_EN()                   RCC->APB1ENR |= (1<<21)
#define RCC_I2C2_EN()                   RCC->APB1ENR |= (1<<22)
#define RCC_USB_EN()					RCC->APB1ENR |= (1<<23)
#define RCC_CAN_EN()                  	RCC->APB1ENR |= (1<<25)
#define RCC_BKP_EN()                	RCC->APB1ENR |= (1<<27)
#define RCC_PWR_EN()                   	RCC->APB1ENR |= (1<<28)
#define RCC_DAC_EN()               	    RCC->APB1ENR |= (1<<29)

/*********************** Reset Mechanism ****************************/
#define RCC_USART1_RESET()              RCC->APB2RSTR |= (1<<14)
#define RCC_USART2_RESET()              RCC->APB1RSTR |= (1<<17)
#define RCC_USART3_RESET()              RCC->APB1RSTR |= (1<<18)

/************************************** Core Peripherals Macros *************************************/
/*********************** NVIC ****************************/
#define NVIC_IRQ6_EXTI0_ENABLE				NVIC_ISER0 |= (1<<6);
#define NVIC_IRQ7_EXTI1_ENABLE				NVIC_ISER0 |= (1<<7);
#define NVIC_IRQ8_EXTI2_ENABLE				NVIC_ISER0 |= (1<<8);
#define NVIC_IRQ9_EXTI3_ENABLE				NVIC_ISER0 |= (1<<9);
#define NVIC_IRQ10_EXTI4_ENABLE				NVIC_ISER0 |= (1<<10);
#define NVIC_IRQ23_EXTI9_5_ENABLE			NVIC_ISER0 |= (1<<23);
#define NVIC_IRQ40_EXTI15_10_ENABLE			NVIC_ISER1 |= (1<<8);	//40(Vector table number) - 32(number of bits) = 8 (the index of interrupt in reg.)
#define NVIC_IRQ37_USART1_ENABLE			NVIC_ISER1 |= (1<<5);	//37(Vector table number) - 32(number of bits) = 5
#define NVIC_IRQ38_USART2_ENABLE			NVIC_ISER1 |= (1<<6);	//38(Vector table number) - 32(number of bits) = 6
#define NVIC_IRQ39_USART3_ENABLE			NVIC_ISER1 |= (1<<7);	//39(Vector table number) - 32(number of bits) = 7

#define NVIC_IRQ6_EXTI0_DISABLE				NVIC_ICER0 |= (1<<6);
#define NVIC_IRQ7_EXTI1_DISABLE				NVIC_ICER0 |= (1<<7);
#define NVIC_IRQ8_EXTI2_DISABLE				NVIC_ICER0 |= (1<<8);
#define NVIC_IRQ9_EXTI3_DISABLE				NVIC_ICER0 |= (1<<9);
#define NVIC_IRQ10_EXTI4_DISABLE			NVIC_ICER0 |= (1<<10);
#define NVIC_IRQ23_EXTI9_5_DISABLE			NVIC_ICER0 |= (1<<23);
#define NVIC_IRQ40_EXTI15_10_DISABLE		NVIC_ICER1 |= (1<<8);	//40(Vector table number) - 32(number of bits) = 8 (the index of interrupt in reg.)
#define NVIC_IRQ37_USART1_DISABLE			NVIC_ICER1 |= (1<<5);	//37(Vector table number) - 32(number of bits) = 5
#define NVIC_IRQ38_USART2_DISABLE			NVIC_ICER1 |= (1<<6);	//38(Vector table number) - 32(number of bits) = 6
#define NVIC_IRQ39_USART3_DISABLE			NVIC_ICER1 |= (1<<7);	//39(Vector table number) - 32(number of bits) = 7


#endif /* INC_STM32F103X6_MEM_MAP_H_ */
