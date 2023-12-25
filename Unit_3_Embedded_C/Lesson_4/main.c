/*Base Addresses of the peripherals*/
#define SYSCTL_BASE				0x400FE000
#define GPIO_PORTF_BASE			0x40025000

/*Registers of the peripherals*/
#define SYSCTL_RCGC2_R			(*((volatile unsigned long*)(SYSCTL_BASE+0x108)))			/* For enabling the clock of the peripherals */
#define GPIO_PORTF_DIR_R		(*((volatile unsigned long*)(GPIO_PORTF_BASE+0x400)))		/* Direction Register of GPIOF pins */
#define GPIO_PORTF_DEN_R		(*((volatile unsigned long*)(GPIO_PORTF_BASE+0x51c)))		/* Enable Register of GPIOF pins */
#define GPIO_PORTF_DATA_R		(*((volatile unsigned long*)(GPIO_PORTF_BASE+0x3FC)))		/* Data Register of GPIOF pins */

int x;		/* Wrote it to see the addresses of the .bss section and understand more the way of initializing stack pointer in startup code */

int main(void)
{
	volatile unsigned long delay_count;		/* To make sure the for loop will not be optimized */
	
	/* Enable the GPIO Port */
	SYSCTL_RCGC2_R = 0x20;
	
	/* Delay to make sure that GPIO is up and running */
	for(delay_count=0 ; delay_count < 200 ; delay_count++);
	
	/* Set the direction of GPIOF pin 3 to be output */
	GPIO_PORTF_DIR_R |= (1<<3);

	/* Enable the GPIOF pin 3  */
	GPIO_PORTF_DEN_R |= (1<<3);	

	while(1)
	{
		/* Toggle pin 3 in GPIOF */
		GPIO_PORTF_DATA_R ^= (1<<3);	
		/* Wait to see the toggling of the led */
		for(delay_count=0 ; delay_count < 200000 ; delay_count++);
	}
	return 0;
}
