#include "LIB/STM32F103x6_MemMap.h"
#include "MCAL/GPIO Driver/GPIO_interface.h"
#include "MCAL/EXTI Driver/EXTI_interface.h"
#include "MCAL/USART Driver/USART_interface.h"
#include "HAL/LCD Driver/LCD_interface.h"
#include "HAL/Keypad Driver/Keypad_interface.h"
#define F_CPU				8000000UL

/* Data types of Modes we can switch between them */
typedef enum accessMode
{
	privileged,
	unprivileged
}accessMode;
/* Macro to switch between the privileged and the unprivileged modes */
#define SWITCH_CPU_ACCESS(Mode)		switch(Mode){\
case privileged:__asm volatile("MRS R3,CONTROL \n\t LSR R3,R3,#0x1 \n\t LSL R3,R3,#0x1 \n\t MSR CONTROL,R3");break;\
case unprivileged:__asm volatile("MRS R3,CONTROL \n\t ORR R3,R3,#0x1 \n\t MSR CONTROL,R3");break;}


/* Operation on the CPU Registers */
#define OS_SWITCH_SP_TO_PSP		__asm volatile("MRS r1,CONTROL \n\t  MOV r2,#0x02 \n\t  ORR r1,r1,r2 \n\t MSR CONTROL,r1")
#define OS_SWITCH_SP_TO_MSP     __asm volatile("MRS r1,CONTROL \n\t  MOV r2,#0x05 \n\t  AND r1,r1,r2 \n\t MSR CONTROL,r1")
#define OS_SET_PSP(address)		__asm volatile("MOV r1,%0 \n\t MSR PSP,r1" : : "r"(address))
#define OS_GENERATE_EXCEPTION	__asm volatile("SVC #0x3")

void SVC_Handler(void)
{
	SWITCH_CPU_ACCESS(privileged);
}

/* Define the stack pointer from the linker script */
extern int _estack;
/* Define the start and the end of the stack of main stack */
unsigned int _S_MSP = &_estack;
unsigned int _E_MSP;
/* Define the start of the stack of task A and its size */
unsigned int _S_PSP_TA;
unsigned int _E_PSP_TA;
/* Define the start of the stack of task B and its size */
unsigned int _S_PSP_TB;
unsigned int _E_PSP_TB;
/* Task Stack sizes */
#define TASKA_SIZE			100
#define TASKB_SIZE			100


/* Flags to switch between tasks in the ISR */
uint8_t TaskA_Flag = 0;
uint8_t TaskB_Flag = 0;
uint8_t IRQ_Flag   = 0;



/* Task A */
int TaskA_Handler(int a,int b)
{
	return a+b;
}

/* Task B */
int TaskB_Handler(int a,int b ,int c)
{
	return a+b+c;
}

/* The OS (Scheduler) */
void MainOs(void)
{
	/* First initialize stack pointers of the OS and the tasks */
	/* Main Stack */
	_E_MSP = (_S_MSP - 512);				// we subtract because our stack is descending stack and the size we chose is 512 bytes

	/* Task A */
	_S_PSP_TA = (_E_MSP - 8);				// We made a guard 8 bytes and start the stack of the task A
	_E_PSP_TA = (_S_PSP_TA - TASKA_SIZE );

	/* Task B */
	_S_PSP_TB = (_E_PSP_TA - 8);				// We made a guard 8 bytes and start the stack of the task B
	_E_PSP_TB = (_S_PSP_TB - TASKB_SIZE );


	while(1)
	{
		__asm("NOP");
		if(TaskA_Flag == 1)
		{
			/* First update the SP with the address of the Task A stack */
			OS_SET_PSP(_S_PSP_TA);
			/* Second switch from the MSP to PSP */
			OS_SWITCH_SP_TO_PSP;
			/* Switch to the unprivileged level */
			SWITCH_CPU_ACCESS(unprivileged);
			/* Call the Task */
			TaskA_Flag = TaskA_Handler(1, 2);
			/* Switch to the privileged level */		// By generating software exception to SVC Handler
			OS_GENERATE_EXCEPTION;
			/* Second switch from the PSP to MSP */
			OS_SWITCH_SP_TO_MSP;
		}
		else if(TaskB_Flag == 1)
		{
			/* First update the SP with the address of the Task B stack */
			OS_SET_PSP(_S_PSP_TB);
			/* Second switch from the MSP to PSP */
			OS_SWITCH_SP_TO_PSP;
			/* Switch to the unprivileged level */
			SWITCH_CPU_ACCESS(unprivileged);
			/* Call the Task */
			TaskB_Flag = TaskB_Handler(1, 2, 3);
			/* Switch to the privileged level */		// By generating software exception to SVC Handler
			OS_GENERATE_EXCEPTION;
			/* Second switch from the PSP to MSP */
			OS_SWITCH_SP_TO_MSP;
		}

	}
}




void clock_init()
{
	// Enable clock GPIOA
	RCC_GPIOA_EN();
	// Enable clock GPIOB
	RCC_GPIOB_EN();
	// Enable clock AFIO
	RCC_AFIO_EN();
}

void EXTIB9_CallBack(void)
{
	/* Check for the IRQ Flag to decide which task will start */
	if(IRQ_Flag == 0)
	{
		TaskA_Flag = 1;
		IRQ_Flag = 1;
	}
	else if(IRQ_Flag == 1)
	{
		TaskB_Flag = 1;
		IRQ_Flag = 0;
	}
}

int main(void) {
	/* Enable the clocks of used ports and AFIO */
	clock_init();


	/* Configure the EXTI */
	EXTI_PinConfig_t PinCfg;
	PinCfg.EXTI_PIN = EXTI_PIN_LINE9PB9;
	PinCfg.Trigger_Case = EXTI_TRIGGER_RISING;
	PinCfg.P_IRQ_CallBack = EXTIB9_CallBack;
	PinCfg.IRQ_EN = EXTI_STATE_ENABLE;
	MCAL_EXTI_GPIO_Init(&PinCfg);

	/* Start the OS */
	MainOs();

	while (1)
	{

	}
}
