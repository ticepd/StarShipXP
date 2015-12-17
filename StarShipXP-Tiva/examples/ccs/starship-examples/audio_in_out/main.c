/************************ CEDT, NSIT - 2015 ****************************\
* 																		*
*																		*
* 	Audio IN to OUT Chaining											*
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
#include "inc/hw_adc.h"
#include "driverlib/adc.h"

uint32_t adcValue[2];



int main(void)
{
	/*Using Default 16MHz clock from external crystal*/
	SysCtlClockSet(SYSCTL_SYSDIV_10 | SYSCTL_USE_PLL| SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);


    SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_ADC0));
    ADCClockConfigSet(ADC0_BASE,ADC_CLOCK_SRC_PIOSC|ADC_CLOCK_RATE_HALF,1);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
    GPIOPinTypeADC(GPIO_PORTD_BASE, GPIO_PIN_2);
    GPIOPinTypeADC(GPIO_PORTD_BASE,GPIO_PIN_3);

    ADCSequenceDisable(ADC0_BASE, 2);
    ADCSequenceConfigure(ADC0_BASE, 2, ADC_TRIGGER_PROCESSOR, 0);
    ADCSequenceStepConfigure(ADC0_BASE, 2, 0, ADC_CTL_CH5);
    ADCSequenceStepConfigure(ADC0_BASE, 2, 1, ADC_CTL_CH4 | ADC_CTL_IE| ADC_CTL_END);

    ADCSequenceEnable(ADC0_BASE, 2);
    ADCIntClear(ADC0_BASE, 2);
    IntMasterEnable();

    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER1);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    GPIOPinTypeTimer(GPIO_PORTF_BASE,GPIO_PIN_2|GPIO_PIN_3);
    GPIOPinConfigure(GPIO_PF2_T1CCP0);
    GPIOPinConfigure(GPIO_PF3_T1CCP1);

    TimerClockSourceSet(TIMER1_BASE,TIMER_CLOCK_SYSTEM);
    TimerConfigure(TIMER1_BASE, TIMER_CFG_SPLIT_PAIR | TIMER_CFG_B_PWM|TIMER_CFG_A_PWM);
    TimerLoadSet(TIMER1_BASE, TIMER_A, 255);
    TimerLoadSet(TIMER1_BASE, TIMER_B, 255);
    TimerEnable(TIMER1_BASE, TIMER_A);
    TimerEnable(TIMER1_BASE, TIMER_B);

    while(1)
    {
    	 ADCProcessorTrigger(ADC0_BASE, 2);
    	 while(!ADCIntStatus(ADC0_BASE, 2, false));
    	 ADCIntClear(ADC0_BASE, 2);
    	 ADCSequenceDataGet(ADC0_BASE, 2, adcValue);
    	 TimerMatchSet(TIMER1_BASE, TIMER_A, 127+ (adcValue[0])/40);
    	 TimerMatchSet(TIMER1_BASE, TIMER_B, 127+(adcValue[1])/40);

    }

}
