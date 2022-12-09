#include "led_vector.h"

/********************************************************************************
* led_vector_init: Initierar vektorn och sätter startvärden.
********************************************************************************/
void led_vector_init(struct led_vector* self)
{
	self->leds = 0;
	self->size = 0;
	
	return;
}

/********************************************************************************
* led_vector_clear: Rensar hela  vektorn och startar om på nytt.
********************************************************************************/
void led_vector_clear(struct led_vector* self)
{
	free(self->leds);
	self->leds = 0;
	self->size = 0;
}

/********************************************************************************
* led_vector_push: Kollar först om det finns plats på heapen. Finns det plats,
*                  ökar vektorn med en lampa.
********************************************************************************/
int led_vector_push(struct led_vector* self, struct led* new_led)
{
	struct led* copy = (struct led*)realloc(self->leds, sizeof(struct led) * (self->size +1));
	if (!copy) return 1;
	copy[self->size++] = *new_led;
	self->leds = copy;
	return 0;
}

/********************************************************************************
* led_vector_pop: Tar bort sista lampan i vektorn.
********************************************************************************/
int led_vector_pop(struct led_vector* self)
{
	if(self->size <=1)
	{
		led_vector_clear(self);
		return 0;
	}
	else
	{
		struct led* copy = (struct led*)realloc(self->leds, sizeof(struct led) * (self->size - 1));
		if (!copy) return 1;
		self->leds = copy;
		self->size--;
		return 0;
	}
}

/********************************************************************************
* led_vector_leds_on: Tänder alla lamporna i vektorn.
********************************************************************************/
void led_vector_leds_on(struct led_vector* self)
{
	for (struct led* i = self->leds; i < self->leds + self->size; ++i)
	{
		led_on(i);
	}
}

/********************************************************************************
* led_vector_leds_off: Släcker alla lamporna i vektorn.
********************************************************************************/
void led_vector_leds_off(struct led_vector* self)
{
	for (struct led* i = self->leds; i < self->leds + self->size; ++i)
	{
		led_off(i);
	}
}

/********************************************************************************
* led_vector_blink_sequentially: Blinkar alla lamporna i vektorn i en sekvens.
********************************************************************************/
void led_vector_blink_sequentially(struct led_vector* self, uint16_t* delay)
{
	for (struct led* i = self->leds; i < self->leds + self->size; ++i)
	{
		led_on(i);
		delay_us(delay);
		led_off(i);
	}
}

/********************************************************************************
* led_vector_blink_collectively: Blinkar alla lamporna i vektorn kollektivt.
********************************************************************************/
void led_vector_blink_collectively(struct led_vector* self, uint16_t* delay)
{
	led_vector_leds_on(self);
	delay_us(delay);
	led_vector_leds_off(self);
	delay_us(delay);
}