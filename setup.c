/********************************************************************************
* setup.c: Deklarerar och Initierar leds och knapparna även interupts på knapparna.
*          Sätter alla leds till false(Kan inte tändas). 
********************************************************************************/
#include "header.h"

struct led l1, l2, l3, l4, l5; // Deklarerar 5 led objekt.
struct button b1, b2, b3, b4, b5; // Deklarerar 5 button objekt.

// Sätter leds till false.
volatile bool led1_enabled = false,
              led2_enabled = false,
              led3_enabled = false,
			  led4_enabled = false,
			  led5_enabled = false;

void setup(void)
{
	led_init(&l1, 6); // Leds pin 6-10.
	led_init(&l2, 7);
	led_init(&l3, 8);
	led_init(&l4, 9);
	led_init(&l5, 10);
	
	button_init(&b1, 2); // Knappar pin 2, 3, 11-13.
	button_init(&b2, 3);
	button_init(&b3, 11);
	button_init(&b4, 12);
	button_init(&b5, 13); 
	
	button_enable_interrupt(&b1); // Sätter interrupts
	button_enable_interrupt(&b2);
	button_enable_interrupt(&b3);
	button_enable_interrupt(&b4);
	button_enable_interrupt(&b5);
}