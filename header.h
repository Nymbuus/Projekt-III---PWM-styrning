/********************************************************************************
* header.h: inkluderar alla header filer i en fil.
********************************************************************************/
#ifndef HEADER_H_
#define HEADER_H_

#include "misc.h"
#include "led.h"
#include "button.h"
#include "led_vector.h"
#include "ADC.h"

#define POT1 PORTC0 // Potentiometer 1 på analog pin A0 (PORTC).

// Kollar om leds är aktiverade.
extern volatile bool led1_enabled,
                     led2_enabled,
                     led3_enabled,
                     led4_enabled,
                     led5_enabled;

extern struct led l1, l2, l3, l4, l5; // Deklarerar 5 led objekt.
extern struct button b1, b2, b3, b4, b5; // Deklarerar 5 button objekt.

// Typisk setup funktion.
void setup(void);

#endif /* HEADER_H_ */