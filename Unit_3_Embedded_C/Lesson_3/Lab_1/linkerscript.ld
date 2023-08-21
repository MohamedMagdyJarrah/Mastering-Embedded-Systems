/* Just information for the debugger to know the entry point of the processor */
ENTRY(reset)

MEMORY
{
	MEM (rwx) : ORIGIN = 0x00000000, LENGTH = 64M 
}

SECTIONS
{
	/* We put the location counter at the entry point of the cpu (according to specs) */
	. = 0x10000;

	/* Define the output sections */
	.startup . :					/* (.) here after startup is to put the reset section at this address */
	{
		startup.o(.text)			/* Generate all .text section of startup in new section called .startup */
	}> MEM							/* Specifiy that this section have VMA = LMA (in load and run time) */
		
	.text :
	{
		*(.text) *(.rodata)			/* Merge all the .text and .rodata (input sections) to .text section (output section) */
	}> MEM

	.data :
	{
		*(.data)
	}> MEM
	
	.bss :
	{
		*(.bss) *(COMMON)			/* (COMMON) mean put anything doesn't have section in .bss */
	}> MEM

	. = . + 0x1000;					/* Added 0x1000 to create stack after this memory sections equal to 4KB */
	stack_top = .;					/* Let the stack pointer point to the address of the location counter which is the top of the stack */
}