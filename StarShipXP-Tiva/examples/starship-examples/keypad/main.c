#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_gpio.h"
#include "inc/hw_ints.h"
#include "inc/hw_sysctl.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"

uint8_t col=0, row=0, key=0;

void keypad_isr(void);

int main()
 {
	SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);

	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);

	HWREG(GPIO_PORTD_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;
	HWREG(GPIO_PORTD_BASE + GPIO_O_CR) |= GPIO_PIN_7;

	GPIOPinTypeGPIOOutput(GPIO_PORTE_BASE,GPIO_PIN_4);
	GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE,GPIO_PIN_5);
	GPIOPinTypeGPIOOutput(GPIO_PORTE_BASE,GPIO_PIN_3);
	GPIOPinTypeGPIOOutput(GPIO_PORTC_BASE,GPIO_PIN_6);

	GPIOPinWrite(GPIO_PORTE_BASE,GPIO_PIN_4,GPIO_PIN_4);
	GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_5,GPIO_PIN_5);
	GPIOPinWrite(GPIO_PORTE_BASE,GPIO_PIN_3,GPIO_PIN_3);
	GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_6,GPIO_PIN_6);

	GPIOPinTypeGPIOInput(GPIO_PORTC_BASE,GPIO_PIN_7);
	GPIOPinTypeGPIOInput(GPIO_PORTD_BASE,GPIO_PIN_6);
	GPIOPinTypeGPIOInput(GPIO_PORTD_BASE,GPIO_PIN_7);
	GPIOPinTypeGPIOInput(GPIO_PORTF_BASE,GPIO_PIN_4);

	GPIOIntRegister(GPIO_PORTF_BASE, keypad_isr);
	GPIOIntRegister(GPIO_PORTD_BASE, keypad_isr);
	GPIOIntRegister(GPIO_PORTC_BASE, keypad_isr);

	GPIOIntClear(GPIO_PORTC_BASE, GPIO_PIN_7);
	GPIOIntClear(GPIO_PORTD_BASE, GPIO_PIN_6 | GPIO_PIN_7);
	GPIOIntClear(GPIO_PORTF_BASE, GPIO_PIN_4);

	GPIOIntTypeSet(GPIO_PORTC_BASE, GPIO_PIN_7, GPIO_RISING_EDGE);
	GPIOIntTypeSet(GPIO_PORTD_BASE, GPIO_PIN_6 | GPIO_PIN_7, GPIO_RISING_EDGE);
	GPIOIntTypeSet(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_RISING_EDGE);

	GPIOIntEnable(GPIO_PORTC_BASE, GPIO_PIN_7);
	GPIOIntEnable(GPIO_PORTD_BASE, GPIO_PIN_6 | GPIO_PIN_7);
	GPIOIntEnable(GPIO_PORTF_BASE, GPIO_PIN_4);

	IntEnable(INT_GPIOF);
	IntEnable(INT_GPIOD);
	IntEnable(INT_GPIOC);

	IntMasterEnable();

	while(1)
    {
    }
}

uint32_t checkRow(uint8_t row)
{
	switch(row)
	{
		case 1:
			return GPIOPinRead(GPIO_PORTC_BASE, GPIO_PIN_7);
		case 2:
			return GPIOPinRead(GPIO_PORTD_BASE, GPIO_PIN_6);
		case 3:
			return GPIOPinRead(GPIO_PORTD_BASE, GPIO_PIN_7);
		case 4:
			return GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_4);
	}
	return 1;
}

void poll(uint8_t row)
{
	GPIOPinWrite(GPIO_PORTE_BASE,GPIO_PIN_4,0);
	if(!checkRow(row))
		col = 1;
	GPIOPinWrite(GPIO_PORTE_BASE,GPIO_PIN_4,GPIO_PIN_4);

	GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_5,0);
	if(!checkRow(row))
		col = 2;
	GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_5,GPIO_PIN_5);

	GPIOPinWrite(GPIO_PORTE_BASE,GPIO_PIN_3,0);
	if(!checkRow(row))
		col = 3;
	GPIOPinWrite(GPIO_PORTE_BASE,GPIO_PIN_3,GPIO_PIN_3);

	GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_6,0);
	if(!checkRow(row))
		col = 4;
	GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_6,GPIO_PIN_6);
}

void keypad_isr(void)
{
	row=0;

	if(GPIOIntStatus(GPIO_PORTC_BASE,true) & GPIO_INT_PIN_7)
	{
		GPIOIntClear(GPIO_PORTC_BASE, GPIO_PIN_7);
		row=1;
	}

	if(GPIOIntStatus(GPIO_PORTD_BASE,true) & GPIO_INT_PIN_6)
	{
		GPIOIntClear(GPIO_PORTD_BASE, GPIO_PIN_6);
		row=2;
	}

	if(GPIOIntStatus(GPIO_PORTD_BASE,true) & GPIO_INT_PIN_7)
	{
		GPIOIntClear(GPIO_PORTD_BASE, GPIO_PIN_7);
		row=3;
	}

	if(GPIOIntStatus(GPIO_PORTF_BASE,true) & GPIO_INT_PIN_4)
	{
		GPIOIntClear(GPIO_PORTF_BASE, GPIO_PIN_4);
		row=4;
	}

	if(row)
	{
		col=0;
		poll(row);
		if(col)
			key = ((4*(row-1))+(5-col));
	}
}
