/************************ CEDT, NSIT - 2015 ****************************\
* 																		*
*																		*
* 	Hello Switch - Reads the status of a switch 						*
* 						using Register Access							*
* 																		*
*																		*
************************************************************************/

#include <stdbool.h>
#include <stdint.h>

#include "inc/tm4c123gh6pm.h"

int main(void)
{
	//
	//Dummy variable
	//
    volatile unsigned long ulLoop;

    //
    // Enable the GPIO port that is used for the on-board LED.
    //
    SYSCTL_RCGC2_R = SYSCTL_RCGC2_GPIOF;

    //
    // Do a dummy read to insert a few cycles after enabling the peripheral.
    //
    ulLoop = SYSCTL_RCGC2_R;

    //
    // Enable the GPIO pin for the LED (PF1).  Set the direction as output, and
    // enable the GPIO pin for digital function.  Care is taken to not disrupt
    // the operation of the JTAG pins on PC0-PC3.
    //
    GPIO_PORTF_DIR_R |= 0x02;
    GPIO_PORTF_DEN_R |= 0x02;

    //
    // Enable the GPIO pin for the Switch1(PF4).  Set the direction as input, and
    // enable the GPIO pin for digital function.  Care is taken to not disrupt
    // the operation of the JTAG pins on PC0-PC3.
    //
    GPIO_PORTF_DIR_R &= ~(0x10);
    GPIO_PORTF_DEN_R |= 0x10;

    GPIO_PORTF_AFSEL_R = 0x00;

    //
    //Pulling up PF4 Pin
    //
    GPIO_PORTF_PUR_R |= 0x10;

    //
    // Loop forever.
    //
    while(1)
    {
        //
        // If the button is pressed
        //
    	if(((GPIO_PORTF_DATA_R) & (0x10)) != (0X10))
    	{
        //
        // LED is on
        //
    	GPIO_PORTF_DATA_R |= 0x02;

    	}

    	else
    	{
        //
        //Turn off the LED
        //
        GPIO_PORTF_DATA_R &= ~(0x02);
    	}

    }
}

