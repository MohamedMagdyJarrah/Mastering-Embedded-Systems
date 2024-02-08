#ifndef INC_STM32F103X6_EXTI_H_
#define INC_STM32F103X6_EXTI_H_


/*********************************************** Includes **********************************************/
#include "../../LIB/STM32F103x6_MemMap.h"
#include "../GPIO Driver/GPIO_interface.h"

/*******************************************  Type definitions *****************************************/
typedef struct
{
	/* Specifies the GPIO pin that is configured as external interrupt */
	/* This parameter must be based on @ref EXTI_PIN_define */
	EXTI_Setup_t		EXTI_PIN	;

	/* Specifies the type of the trigger for the external interrupt */
	/* This parameter must be based on @ref EXTI_TRIGGER_define */
	uint8_t				Trigger_Case;

	/* Specifies the State of the pin by enabling or disabling it considering the NVIC Controller too */
	/* This parameter must be based on @ref EXTI_STATE_define */
	uint8_t				IRQ_EN;

	/* Specifies the callback function received from the user (application layer) */
	void				(*P_IRQ_CallBack)(void);

}EXTI_PinConfig_t;

/*============================= @ref EXTI_PIN_define =============================
 * When you choose the EXTI_PIN you should configure according to these configurations:
 *  EXTI_PIN_LINE(x)P(y)(z)		where x is the number of the EXTI line and y is the port while z is the pin used
 * Examples:
 *	1- EXTI_PIN_LINE0PA0
	2- EXTI_PIN_LINE5PB5
	3- EXTI_PIN_LINE7PC7
	4- EXTI_PIN_LINE10PD10

	Note:		The number of the line will be the same of the pin
 * */

/*============================= @ref EXTI_TRIGGER_define =============================
 * You can choose the trigger case from these configurations:
 * 	1- EXTI_TRIGGER_RISING
	2- EXTI_TRIGGER_FALLING
	3- EXTI_TRIGGER_RISING_AND_FALLING
 * */

/*============================= @ref EXTI_STATE_define =============================
 * You can choose the state of EXTI will be enabled or disabled with these configurations:
 * 	1- EXTI_STATE_ENABLE
	2- EXTI_STATE_DISABLE
 * */


/*===============================================================================================
 * 								APIs supported by "MCAL EXTI Driver"
 *===============================================================================================*/
void MCAL_EXTI_GPIO_Init(EXTI_PinConfig_t* EXTI_Config);
void MCAL_EXTI_GPIO_DeInit(void);

void MCAL_EXTI_GPIO_Update(EXTI_PinConfig_t* EXTI_Config);


#endif /* INC_MCAL_EXTI_DRIVER_STM32F103X6_EXTI_H_ */
