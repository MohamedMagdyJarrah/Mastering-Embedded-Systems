/* Startup.c code for lab2 made by Mohamed Magdy */
#include <stdint.h>

/* Let this program to know that we will use main from main.c */
extern int main(void);

/* Let this program to know that we will use these symbols from linkerscript */
// extern unsigned int _stack_top;
/* We will try to implement the stack pointer in different way */
/* We will reserve 1024 Byte (Size of the stack) in .bss section as the array is global un-initialized variable (We made an array with 256 elements of variable size 4 Byte, So the result 1024 Byte) */
static	unsigned long Stack_Top[256];	
extern unsigned int _S_Data;
extern unsigned int _E_Data;
extern unsigned int _E_text;
extern unsigned int _S_bss;
extern unsigned int _E_bss;

void Reset_Handler(void);

void Default_Handler(void)
{
	Reset_Handler();
}

/* we used {weak} in the attribute to let the user define its own ISR and override the symbol here in the startup (prevent symbol defined twice) */
/* we used {alias} in the attribute here to prevent reserve for every handler address in memory (even if I don't use them) and make their address alias for one handler(symbol) 
	and execute the default handler	 */
void NMI_Handler(void) __attribute__((weak,alias("Default_Handler")));
void Hard_fault_Handler(void) __attribute__((weak,alias("Default_Handler")));
void MM_Handler(void) __attribute__((weak,alias("Default_Handler")));
void Bus_Fault_Handler(void) __attribute__((weak,alias("Default_Handler")));
void Usage_Fault_Handler(void) __attribute__((weak,alias("Default_Handler")));


/* Define symbols in array to put it in the vectors section */
/* We casted every elemtent (which is the address of every function in Vector Table) in the array to be the same type of the array */
//uint32_t vectors[] __attribute__((section(".vectors")))	=		/* This attribute to save this array in section called vectors in memory */
//{
//	(uint32_t)&_stack_top,
//	(uint32_t)&Reset_Handler,
//	(uint32_t)&NMI_Handler,
//	(uint32_t)&Hard_fault_Handler,
//	(uint32_t)&MM_Handler,
//	(uint32_t)&Bus_Fault_Handler,
//	(uint32_t)&Usage_Fault_Handler
//};
	
/* Also we will try to implement the vector table in new way (Array of pointers to function) and store the address of every function */
/* Here we will not cast the elements to be uint32_t as we point to the same type which is function  */
void (*g_p_fn_VectorTable[])(void) __attribute__((section(".vectors")))	=	/* Also we put the attribute to save this array in section called vectors in memory */
{
	( void (*)(void) )	(&Stack_Top[0]+sizeof(Stack_Top)),		/* Here we will cast the stack pointer as it isn't the same type */
	Reset_Handler,
	NMI_Handler,
	Hard_fault_Handler,
	MM_Handler,
	Bus_Fault_Handler,
	Usage_Fault_Handler,
};

/* ===========================================================================================================================================================================
	With this way we discarded the initialization of the stack pointer in the linkerscript and initialized it here in the startup code by taking a part of the .bss section 
	by defining un-initialized global variable here
	===========================================================================================================================================================================
*/



/* Note: All pointer types have the same size */

void Reset_Handler(void)
{
	int i = 0;
	/* Copy the .data from flash to sram */
	unsigned int Data_Size = (unsigned char*)&_E_Data - (unsigned char*)&_S_Data;		/* Get the size of .data section by info of its end and start address 
	(we put & before the _E_Data and _S_Data because they are symbols not variables and we want to take its addresses also cast them as pointers */
	unsigned char *P_src = (unsigned char*)&_E_text;
	unsigned char *P_dest = (unsigned char*)&_S_Data;
	
	for(i=0 ; i < Data_Size ; i++)
	{
		*((unsigned char*)P_dest++) = *((unsigned char*)P_src++);
	}
	
	
	/* Reserve .bss in sram and init them by zeroes*/
	unsigned int Bss_Size = (unsigned char)_E_bss - (unsigned char)_S_bss;	
	P_dest = (unsigned char*)&_S_bss;
	for(i=0 ; i < Bss_Size ; i++)
	{
		*((unsigned char*)P_dest++) = (unsigned char)0;
	}
	
	/* Jump to the main */
	main();
}