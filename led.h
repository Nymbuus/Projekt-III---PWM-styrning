/********************************************************************************
* led.h: Inneh�ller funktionaltet f�r enkel implementering av lysdioder och
andra digitala utportar via strukten led samt associerade funktioner.
********************************************************************************/
#ifndef LED_H_
#define LED_H_

#include "misc.h"

// Inneh�ller datatyper f�r structen led.
struct led {
	uint8_t pin; // Lysdiodens pin-nummer
	enum io_port io_port; // Lysdiodens I/O-port.
	bool enabled; // Om lampan �r t�nd eller sl�ckt.
};

// Deklarerar funktioner.
void led_init(struct led* self, const uint8_t pin);
void led_clear(struct led* self);
void led_on(struct led* self);
void led_off(struct led* self);
void led_toggle(struct led* self);
void led_blink(struct led* self, const uint16_t* blink_speed_us);

#endif /* LED_H_ */