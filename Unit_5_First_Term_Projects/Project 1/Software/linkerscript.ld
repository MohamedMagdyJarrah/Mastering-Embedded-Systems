/* Just information for the debugger to know the entry point of the processor */
ENTRY(Reset_Handler)

/* Configure Memories we use from the specs */
MEMORY
{
	FLASH (rx) : ORIGIN = 0x08000000, LENGTH = 128k
	SRAM (rwx) : ORIGIN = 0x20000000, LENGTH = 20k
}

SECTIONS
{
	.text :
	{
		*(.vectors*)		/* The * after the vectors because if the user named it vectors.. and something else like vectors_section */
		*(.text*)
		*(.rodata)			/* Merge all the .text and .rodata and .vectors (input sections) to .text section (output section) */
		_E_text = .;		/* Save the end address of .text section */
	}> FLASH

	.data :
	{
		_S_Data = .;		/* Save the start address of .data section */
		*(.data)
		_E_Data = .;		/* Save the end address of .data section */
		. = ALIGN(4);		/* Align the last address we reach (4) bytes according to the architecture */
	}> SRAM AT> FLASH  		/* As we put the virtual ram (sram) the address will saved in _S_Data and _E_Data we be in sram */
	
	.bss :
	{
		_S_bss = .;			/* Save the start address of .bss section */
		*(.bss) *(COMMON)	/* (COMMON) mean put anything doesn't have section in .bss */
		_E_bss = .;			/* Save the end address of .bss section */
		
		. = ALIGN(4);		/* Align the last address we reach */
		. = . + 0x1000;		/* Add some space between data in sram to put the stack */
		_stack_top = .;		/* store the start of stack pointer */
	}> SRAM
}