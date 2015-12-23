#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "inc/hw_timer.h"
#include "driverlib/timer.h"
#include "driverlib/adc.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/pin_map.h"

uint32_t adcValue[1];
int32_t pwmDuty;

int main(void)
{

    SysCtlClockSet(SYSCTL_SYSDIV_10 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
    GPIOPinTypeADC(GPIO_PORTE_BASE, GPIO_PIN_2);

    ADCSequenceConfigure(ADC0_BASE, 3, ADC_TRIGGER_PROCESSOR, 0);
    ADCSequenceStepConfigure(ADC0_BASE, 3, 0, ADC_CTL_CH1 | ADC_CTL_IE | ADC_CTL_END);
    ADCSequenceEnable(ADC0_BASE, 3);
    ADCIntClear(ADC0_BASE, 3);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER1);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    GPIOPinTypeTimer(GPIO_PORTF_BASE,GPIO_PIN_2|GPIO_PIN_3);
    GPIOPinConfigure(GPIO_PF2_T1CCP0);
    GPIOPinConfigure(GPIO_PF3_T1CCP1);
    TimerClockSourceSet(TIMER1_BASE, TIMER_CLOCK_SYSTEM);
    TimerConfigure(TIMER1_BASE, TIMER_CFG_SPLIT_PAIR | TIMER_CFG_B_PWM|TIMER_CFG_A_PWM);
    TimerLoadSet(TIMER1_BASE, TIMER_A, 255);
    TimerLoadSet(TIMER1_BASE, TIMER_B, 255);
    TimerEnable(TIMER1_BASE, TIMER_A);
    TimerEnable(TIMER1_BASE, TIMER_B);

    while(1)
    {
        ADCProcessorTrigger(ADC0_BASE, 3);
        while(!ADCIntStatus(ADC0_BASE, 3, false));
        ADCIntClear(ADC0_BASE, 3);
        ADCSequenceDataGet(ADC0_BASE, 3, adcValue);
        pwmDuty = (adcValue[0] - 2048);
        pwmDuty = pwmDuty/2;
        pwmDuty = 127 + pwmDuty;
		TimerMatchSet(TIMER1_BASE, TIMER_A, pwmDuty);
		TimerMatchSet(TIMER1_BASE, TIMER_B, pwmDuty);
        SysCtlDelay(SysCtlClockGet() / 1000000);
    }
}
