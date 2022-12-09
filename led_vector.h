/********************************************************************************
* led_vector.h: Innehåller struct som samlar ihop alla leds och funktionalitet
                för att hantera den.
********************************************************************************/
#ifndef LED_VECTOR_H_
#define LED_VECTOR_H_

#include "misc.h"
#include "led.h"

// Innehåller alla leds och storlek på structen.
struct led_vector {
	struct led* leds;
	size_t size;
	};
	
// Deklarerar funktioner.
void led_vector_init(struct led_vector* self);
void led_vector_clear(struct led_vector* self);
int led_vector_push(struct led_vector* self, struct led* new_led);
int led_vector_pop(struct led_vector* self);
void led_vector_leds_on(struct led_vector* self);
void led_vector_leds_off(struct led_vector* self);
void led_vector_blink_sequentially(struct led_vector* self, uint16_t* delay);
void led_vector_blink_collectively(struct led_vector* self, uint16_t* delay);

#endif /* LED_VECTOR_H_ */