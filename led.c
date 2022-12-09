/********************************************************************************
* led.c: Inneh�ller funktioner relaterade till lamporna.
********************************************************************************/
#include "led.h"

/********************************************************************************
* led.init: Initierar angiven pin till utport och registrerar vilket pin-nummer
*           och I/O-port som lysdioden �r ansluten till.
*
*           - self: Pekare till lysdioden.
*           - pin : Pin-nummer p� Arduino Uno som lysdioden �r ansluten till.
********************************************************************************/
void led_init(struct led* self, const uint8_t pin)
{	
	if (pin >= 0 && pin <= 7)
	{
		self->io_port = IO_PORTD;
		self->pin = pin;
		DDRD |= (1 << self->pin);
	}
	else if (pin >= 8 && pin <= 13)
	{
		self->io_port = IO_PORTB;
		self->pin = pin - 8;
		DDRB |= (1 << self->pin);
	}
	
	self->enabled = false; // Lysdioden �r sl�ckt.
	
	return;
}

/********************************************************************************
* led_clear: Resetar pin, IO-port och s�tter togglen till false
*
*            - self: Pekare till lysdioden.
********************************************************************************/
void led_clear(struct led* self)
{
	led_off(self);
	
	if (self->io_port == PORTB)
	{
		DDRB &= ~(1 << self->io_port);
	}
	else if (self->io_port == PORTD)
	{
		DDRD &= ~(1 << self->io_port);
	}
	
	self->pin = 0;
	self->io_port = IO_PORT_NONE;
	self->enabled = false;
	
	return;
}

/********************************************************************************
* led_on: T�nder angiven lysdiod.
*
*         - self: Pekare till lysdioden.
********************************************************************************/
void led_on(struct led* self)
{
	if (self->io_port == IO_PORTB)
	{
		PORTB |= (1 << self->pin);
	}
	else if (self->io_port == IO_PORTD)
	{
		PORTD |= (1 << self->pin);
	}
	
	self->enabled = true; // Betyder att lysdioden �r t�nd.
	return;
}

/********************************************************************************
* led_off: T�nder angiven lysdiod.
*
*         - self: Pekare till lysdioden.
********************************************************************************/
void led_off(struct led* self)
{
	if (self->io_port == IO_PORTB)
	{
		PORTB &= ~(1 << self->pin);
	}
	else if (self->io_port == IO_PORTD)
	{
		PORTD &= ~(1 << self->pin);
	}
	
	self->enabled = false; // Lysdioden �r sl�ckt.
	return;
}

/********************************************************************************
* led_toggle: Togglar mellan av och p� f�r lysdioden.
*
*             - self: Pekare till lysdioden.
********************************************************************************/
void led_toggle(struct led* self)
{
	if (self->enabled)
	{
		led_off(self);
	}
	else
	{
		led_on(self);
	}
	
	return;
}
/********************************************************************************
* led_blink: G�r att lampan blinkar genom toggling.
*
*            - self: Pekare till lysdioden.
********************************************************************************/
void led_blink(struct led* self, const uint16_t* blink_speed_us)
{
	if (self->enabled)
	{
		led_toggle(self);
		delay_us(blink_speed_us);
	}
}