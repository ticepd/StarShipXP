/************************ CEDT, NSIT - 2015 ****************************\
* 																		*
*																		*
* 	Implementing PWM using TIMER										*
* 																		*
*																		*
************************************************************************/

#include <stdint.h>
#include <stdbool.h>

#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_timer.h"
#include "inc/hw_ints.h"
#include "inc/hw_gpio.h"
#include "driverlib/timer.h"
#include "driverlib/interrupt.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "utils/uartstdio.h"
#include "driverlib/pin_map.h"

unsigned long i;

void low_to_high(void)
{
	for(i=999;i>1;i--)
	{
		TimerMatchSet(WTIMER0_BASE, TIMER_A, i);
		TimerMatchSet(WTIMER0_BASE, TIMER_B, i);
		TimerMatchSet(TIMER3_BASE, TIMER_B, i);
        SysCtlDelay(SysCtlClockGet()/5000);
	}
}

void high_to_low(void)
{
	for(i=1;i<1000;i++)
	{
		TimerMatchSet(WTIMER0_BASE, TIMER_A, i);
		TimerMatchSet(WTIMER0_BASE, TIMER_B, i);
		TimerMatchSet(TIMER3_BASE, TIMER_B, i);
        SysCtlDelay(SysCtlClockGet()/5000);
	}
}

int main(void)
{
	/*Using Default 16MHz clock from external crystal*/
	SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);

	SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER3);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    GPIOPinTypeTimer(GPIO_PORTB_BASE, GPIO_PIN_3);
    GPIOPinConfigure(GPIO_PB3_T3CCP1);

    TimerConfigure(TIMER3_BASE, TIMER_CFG_SPLIT_PAIR | TIMER_CFG_B_PWM);
    TimerLoadSet(TIMER3_BASE, TIMER_B, 1000);
    TimerEnable(TIMER3_BASE, TIMER_B);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_WTIMER0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
    GPIOPinTypeTimer(GPIO_PORTC_BASE,GPIO_PIN_4|GPIO_PIN_5);
    GPIOPinConfigure(GPIO_PC4_WT0CCP0);
    GPIOPinConfigure(GPIO_PC5_WT0CCP1);

    TimerConfigure(WTIMER0_BASE, TIMER_CFG_SPLIT_PAIR | TIMER_CFG_B_PWM|TIMER_CFG_A_PWM);
    TimerLoadSet(WTIMER0_BASE, TIMER_A, 1000);
    TimerLoadSet(WTIMER0_BASE, TIMER_B, 1000);
    TimerEnable(WTIMER0_BASE, TIMER_A);
    TimerEnable(WTIMER0_BASE, TIMER_B);

    while(1)
    {
      low_to_high();
      high_to_low();
    }

}
