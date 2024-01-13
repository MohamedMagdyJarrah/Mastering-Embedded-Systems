/*****************************************************************/
/*****************************************************************/
/*****************		Author: Mohamed Magdy	******************/
/*****************		Layer:  MCAL			******************/
/*****************		SWC:    WATCHDOG		******************/
/*****************************************************************/
/*****************************************************************/
#include "Watchdog_interface.h"

/*========================================================================================================
 * @Fun			:	MCAL_WATCHDOG_Enable
 * @Brief		:	Enable the watchdog timer with the time configured in the pre-configuration
 * @RetVal		:	None
 *========================================================================================================*/
void MCAL_WATCHDOG_Enable(void)
{
	WDTCR |= (1<<WDTCR_WDE) | WDT_TIMEOUT_RESET;
}

/*========================================================================================================
 * @Fun			:	MCAL_WATCHDOG_Disable
 * @Brief		:	Disable the watchdog timer
 * @RetVal		:	None
 *========================================================================================================*/
void MCAL_WATCHDOG_Disable(void)
{
	/*Writing Logical one to WDE and WDTOE at the same Operation*/
	WDTCR |= 0b00011000;

	/*Then turn off watchdog timer by writing logic 0 on WDE*/
	WDTCR = 0;
}
