/* Lab 2 part 2*/
.globl _reset

/* (.sections) to save all the following words in section called .vectors in memory */
.section .vectors

/* (.word) to save the this symbol(address value) in the beginning of the memory */
.word 0x20001000  			/* Stack top address */
/* save in the next place in the ram all the vector table content (When the programs go to address of them it will go to Vector_handler section */
.word _reset				/* 1)Reset */
.word Vector_handler		/* 2)NMI */
.word Vector_handler		/* 3)Hard Fault */
.word Vector_handler		/* 4)MM Fault */
.word Vector_handler		/* 5)Bus Fault */
.word Vector_handler		/* 6)Usage Fault */
.word Vector_handler		/* 7)Reserved */
.word Vector_handler		/* 8)Reserved */
.word Vector_handler		/* 9)Reserved */
.word Vector_handler		/* 10)Reserved */
.word Vector_handler		/* 11)SV Call */
.word Vector_handler		/* 12)Debug Monitor */
.word Vector_handler		/* 13)Reserved */
.word Vector_handler		/* 14)PendSV */
.word Vector_handler		/* 15)Systick */
.word Vector_handler		/* 16)IRQ0 */
.word Vector_handler		/* 17)IRQ1 */
.word Vector_handler		/* 18)IRQ2 */


/* (.sections) to save all the following in section .text in memory to prevent taking them with the previous section (.vectors) */
.section .text

/* Reset handler */
_reset:
	bl main
	b .
	
/* Use thumb instruction to use 16 and 32 bits architectures in STM to help the compiler */	
.thumb_func

/* One Section for all Vector handlers instead of implementing sections for every vector handler */
Vector_handler:
	b _reset