/*****************************************************************/
/*****************************************************************/
/*****************		Author: Mohamed Magdy	******************/
/*****************		Layer:  MCAL			******************/
/*****************		SWC:    RCC				******************/
/*****************************************************************/
/*****************************************************************/
#include "RCC_interface.h"

/* An array to store the number of shifts we will do to the HCLK according to the configured PCLK input */
/* We shift right the HCLK to divide it by (2 power the numbers of shifts) */
// 0xx: HCLK not divided
// 100: HCLK divided by 2
// 101: HCLK divided by 4
// 110: HCLK divided by 8
// 111: HCLK divided by 16
const uint8_t APB_PrescTable[8U] = {0,0,0,0,1,2,3,4};
/* The same to divide the SYSCLK */
// 0xxx: SYSCLK not divided
// 1000: SYSCLK divided by 2
// 1001: SYSCLK divided by 4
// 1010: SYSCLK divided by 8
// 1011: SYSCLK divided by 16
// 1100: SYSCLK divided by 64
// 1101: SYSCLK divided by 128
// 1110: SYSCLK divided by 256
// 1111: SYSCLK divided by 512
const uint16_t AHB_PrescTable[16U] = {0,0,0,0,0,0,0,0,1,2,3,4,6,7,8,9};

uint32_t MCAL_RCC_GetSYSCLK(void)
{
	/* Check the system clock status */
	switch( (RCC->CFGR >> 2) & 0b11 )
	{
	/* Return the Internal clock */
	case 0: return HSI_CLK; break;
	/* Return the External clock specified by the user */
	case 1: return HSE_CLK; break;
	/* Return the PLL clock ( To-Do ) */
	case 2: return 16000000; break;
	}
}

uint32_t MCAL_RCC_GetHCLK(void)
{
	return (MCAL_RCC_GetSYSCLK() >> (AHB_PrescTable[ (RCC->CFGR >> 4) & (0xF) ]) );
}

uint32_t MCAL_RCC_GetPCLK1(void)
{
	return (MCAL_RCC_GetHCLK() >> (APB_PrescTable[ (RCC->CFGR >> 8) & (0b111) ]) );
}

uint32_t MCAL_RCC_GetPCLK2(void)
{
	return (MCAL_RCC_GetHCLK() >> (APB_PrescTable[ (RCC->CFGR >> 11) & (0b111) ]) );
}
