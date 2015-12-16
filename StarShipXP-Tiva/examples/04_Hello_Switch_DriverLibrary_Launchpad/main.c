/************************ CEDT, NSIT - 2015 ****************************\
* 																		*
*																		*
* 			Hello Switch - Read user switch and show on LED				*
* 																		*
* 																		*
************************************************************************/

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"


#include "inc/hw_sysctl.h"
#include "driverlib/sysctl.h"
#include "inc/hw_gpio.h"
#include "driverlib/gpio.h"


int main(void)
{
	SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);

	/* Peripheral Initialization Statement
	 * Set the clock for the GPIO Port F */
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

	/* Peripheral Configuration Statement
	 * Set the type of the GPIO Pin, PF4 as input and PF1 as output */
	GPIOPinTypeGPIOInput(GPIO_PORTF_BASE,GPIO_PIN_4);
	GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_STRENGTH_2MA,
	GPIO_PIN_TYPE_STD_WPU);
	GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE,GPIO_PIN_1);

	/* GPIO Pin 1 on PORT F initialized to 0, RED LED is off */
	GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1,0);

	/* Application Loop */
	while(1)
	     {
	     /* Reading the state of input pin PF4
	      * If read state is logic low implies switch is pressed
	      * Turn on the LED at PF1 */
	     if(GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_4)==0)
	       {
	       GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, GPIO_PIN_1);
	       }
	   	 /* If read state is logic high implies switch is not pressed
	   	  * Turn off the LED at PF1 */
	   	 else
	   	   {
	   	   GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0);
	   	   }
	   	 }
	}
