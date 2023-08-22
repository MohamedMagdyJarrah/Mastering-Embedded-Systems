/* Just information for the debugger to know the entry point of the processor */
ENTRY(_reset)

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
	}> FLASH

	.data :
	{
		*(.data)
	}> FLASH
	
	.bss :
	{
		*(.bss) *(COMMON)			/* (COMMON) mean put anything doesn't have section in .bss */
	}> SRAM

}