/********************************************************************************
* ISR.c: Togglar led n�r respektive knapp �r nedtryckt.
********************************************************************************/
#include "header.h"

// S�tter interrrupts p� portarna i register D.
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

// S�tter interrrupts p� portarna i register B.
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