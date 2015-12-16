/************************ CEDT, NSIT - 2015 ****************************\
* 																		*
*																		*
* 	Hello LED (Blink) - Blinks the LED at a predefined rate				*
* 																		*
*																		*
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
	SysCtlClockSet(SYSCTL_SYSDIV_1|SYSCTL_USE_OSC|SYSCTL_OSC_MAIN|SYSCTL_XTAL_16MHZ);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
	GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE,GPIO_PIN_2);
	GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_2,0);

	while(1)
	{
		GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_2,GPIO_PIN_2);
		SysCtlDelay(SysCtlClockGet()/3);
		GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_2,0);
		SysCtlDelay(SysCtlClockGet()/3);
	}

	return 0;
}
