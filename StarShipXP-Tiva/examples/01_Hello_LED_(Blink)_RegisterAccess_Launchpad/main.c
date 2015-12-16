/************************ CEDT, NSIT - 2015 ****************************\
* 																		*
*																		*
* 	Hello LED (Blink) - Blinks the LED at a predefined rate				*
* 						using Register Access							*
* 																		*
*																		*
************************************************************************/

#include <stdbool.h>
#include <stdint.h>

#include "inc/tm4c123gh6pm.h"

#define delay_value 125000

int main(void)
{
/* Delay Loop variable */
volatile unsigned long ulLoop;

/* Enable the GPIO port that is used for the on-board LED */
SYSCTL_RCGC2_R = SYSCTL_RCGC2_GPIOF;

/* Do a dummy read to insert a few cycles after peripheral enable */
ulLoop = SYSCTL_RCGC2_R;

/* Enable the GPIO pin for the LED (PF1)
 * Set the direction as output, and enable the GPIO pin for
 * digital function. Care is taken to not disrupt the
 * operation of the JTAG pins on PC0-PC3 */
GPIO_PORTF_DIR_R |= 0x02;
GPIO_PORTF_DEN_R |= 0x02;
GPIO_PORTF_AFSEL_R = 0x00;

/* Loop forever */
while(1)
   {
   /* Turn on the LED */

	 GPIO_PORTF_DATA_R |= 0x02;

	   /* Delay for a 100ms */
	   for(ulLoop = 0; ulLoop < delay_value; ulLoop++)
	      {
	      }
	    /* Turn off the LED */
	    GPIO_PORTF_DATA_R &= ~(0x02);

	    /* Delay for a 100ms */
	    for(ulLoop = 0; ulLoop < delay_value; ulLoop++)
	       {
	       }

   }
}
