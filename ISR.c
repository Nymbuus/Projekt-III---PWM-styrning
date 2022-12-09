/********************************************************************************
* ISR.c: Togglar led när respektive knapp är nedtryckt.
********************************************************************************/
#include "header.h"

// Sätter interrrupts på portarna i register D.
ISR (PCINT2_vect)
{
	if (button_is_pressed(&b1))
	{
		led1_enabled = !led1_enabled;
	}
	
	if (button_is_pressed(&b2))
	{
		led2_enabled = !led2_enabled;
	}
}

// Sätter interrrupts på portarna i register B.
ISR (PCINT0_vect)
{
	if (button_is_pressed(&b3))
	{
		led3_enabled = !led3_enabled;
	}
	if (button_is_pressed(&b4))
	{
		led4_enabled = !led4_enabled;
	}
	if (button_is_pressed(&b5))
	{
		led5_enabled = !led5_enabled;
	}
}