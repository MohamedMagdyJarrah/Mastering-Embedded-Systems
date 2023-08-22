/* Startup.c code for lab2 made by Mohamed Magdy */
#include <stdint.h>

/* Let this program to know that we will use main from main.c */
extern int main(void);

/* Let this program to know that we will use these symbols from linkerscript */
extern unsigned int _stack_top;
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
uint32_t vectors[] __attribute__((section(".vectors")))	=		/* This attribute to save this array in section called vectors in memory */
{
	(uint32_t)&_stack_top,
	(uint32_t)&Reset_Handler,
	(uint32_t)&NMI_Handler,
	(uint32_t)&Hard_fault_Handler,
	(uint32_t)&MM_Handler,
	(uint32_t)&Bus_Fault_Handler,
	(uint32_t)&Usage_Fault_Handler,
};
	
	
void Reset_Handler(void)
{
	/* Copy the .data from flash to sram */
	unsigned int Data_Size = (unsigned char*)&_E_Data - (unsigned char*)&_S_Data;		/* Get the size of .data section by info of its end and start address 
	(we put & before the _E_Data and _S_Data because they are symbols not variables and we want to take its addresses also cast them as ponters */
	unsigned char *P_src = (unsigned char*)&_E_text;
	unsigned char *P_dest = (unsigned char*)&_S_Data;
	
	for(int i=0 ; i < Data_Size ; i++)
	{
		*((unsigned char*)P_dest++) = *((unsigned char*)P_src++);
	}
	
	
	/* Reserve .bss in sram and init them by zeroes*/
	unsigned int Bss_Size = (unsigned char)_E_bss - (unsigned char)_S_bss;	
	P_dest = (unsigned char*)&_S_bss;
	for(int i=0 ; i < Bss_Size ; i++)
	{
		*((unsigned char*)P_dest++) = (unsigned char)0;
	}
	
	/* Jump to the main */
	main();
}