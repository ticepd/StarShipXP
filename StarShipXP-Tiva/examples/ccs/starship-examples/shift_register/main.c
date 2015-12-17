/************************ CEDT, NSIT - 2015 ****************************\
* 																		*
*																		*
* 	Shift register using SPI														*
* 																		*
*																		*
************************************************************************/
#include "stdint.h"
#include "stdbool.h"
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/ssi.h"
#include "driverlib/pin_map.h"

void latch()
{
	GPIOPinWrite(GPIO_PORTB_BASE,GPIO_PIN_6,GPIO_PIN_6);
	SysCtlDelay(SysCtlClockGet()/1000000);
	GPIOPinWrite(GPIO_PORTB_BASE,GPIO_PIN_6,0);
}

int main()
{
	SysCtlClockSet(SYSCTL_SYSDIV_2_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);

	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_SSI2);
	GPIOPinConfigure(GPIO_PB4_SSI2CLK);
	GPIOPinConfigure(GPIO_PB7_SSI2TX);
	GPIOPinTypeSSI(GPIO_PORTB_BASE,GPIO_PIN_4|GPIO_PIN_7);
	SSIConfigSetExpClk(SSI2_BASE,SysCtlClockGet(),SSI_FRF_MOTO_MODE_0,SSI_MODE_MASTER,2000000,8);
	SSIEnable(SSI2_BASE);

	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
	GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, GPIO_PIN_2|GPIO_PIN_3);
	GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_2,0);
	GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_3,0);

	GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, GPIO_PIN_6);
	GPIOPinWrite(GPIO_PORTB_BASE,GPIO_PIN_6,0);

	while(1)
	{
		SSIDataPut(SSI2_BASE,0xAA);
		latch();
		SysCtlDelay(SysCtlClockGet()/10);

		SSIDataPut(SSI2_BASE,0x55);
		latch();
		SysCtlDelay(SysCtlClockGet()/10);
	}
}
