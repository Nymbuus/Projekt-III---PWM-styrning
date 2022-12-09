#include "button.h"

/*************************************************************************************
* button_init: Initierar angiven tryckknapp och aktiverar den interna pullup-
*              resistotoen på angiven pin.
*
*              1. Vi sparar vilken I/O-port vi är på (pin 0-7 = D, pin 8 - 13 = B).
*
*              2. Vi sparar vilket pin-nummer på aktuell I/O-port som knappen
*                 är ansluten till (så att vi kan läsa av rätt bit).
*
*              3. Vi aktiverar den interna pullup-resistorn på aktuell pin
*                 så att insignaöen alltid blir 0 eller 1 (låg eller hög),
*                 inget flytande där emellan.
*
*              - self: Pekare till kanppen som ska initieras.
*              - pin: Pin-numret på Arduino Uno, exempelvis 13.
**************************************************************************************/
void button_init(struct button* self, const uint8_t pin)
{
	if (pin >= 0 && pin <= 7)
	{
		self->io_port = IO_PORTD;
		self->pin = pin;
		PORTD |= (1 << self->pin);
	}
	else if (pin >= 8 && pin <= 13)
	{
		self->io_port = IO_PORTB;
		self->pin = pin - 8;
		PORTB |= (1 << self->pin);
	}
	
	self->interrupt_enabled = false;
	return;
}

/*************************************************************************************
* button_is_pressed: Indikerar ifall angiven tryckknapp är nedtryckt genom
*                    att returnera true eller false.
*
*                    1. Vi undersöker vilken I/O-port knappen är ansluten till
*                       för att veta vilket PIN-register som ska läsas av
*                       (PINB, PINC eller PIND). Vi kollar därmed vår medlem
*                       io_port.
*
*                    2. när vi fått reda på vilken I/O_port knappen är ansluten
*                       till så läser vi av den pin som tryckknappen är
*                       ansluten till (medlemmen pin) och returnerar detta värde.
*                       Det värde som reutneraras blir true om knappen är
*                       nedtryckt, annars false.
*
*                    - self: Pekare till tryckknappen som ska läsas av.
**************************************************************************************/
bool button_is_pressed(const struct button* self)
{
	if (self->io_port == IO_PORTB)
	{
		return (PINB & (1 << self->pin));
	}
	else if (self->io_port == IO_PORTC)
	{
		return (PINC & (1 << self->pin));
	}
	else if (self->io_port == IO_PORTD)
	{
		return (PIND & (1 << self->pin));
	}
	else
	{
		return false;
	}
}

/********************************************************************************
* button_enable_interrupt: Aktiverar PCI-avbrott på angiven tryckknapp så att
*                          event på tryckknappens pin medför avbrott, både på
*                          stigande och fallande flank. Kontroll av flank måste
*                          skötas av användaren, förslagsvis via avläsning i
*                          motsvarande avbrottsrutin.
*
*                          Nedan visas sambandet mellan använd I/O-port samt
*                          avbrottsvektorn för motsvarande avbrottsrutin:
*
*                          I/O-port     pin (Arduino Uno)     Avbrottsvektor
*                             B              8 - 13             PCINT0_vect
*                             C             A0 - A5             PCINT1_vect
*                             D              0 - 7              PCINT2_vect
*
*                          - self: Pekare till tryckknappen som PCI-avbrott
*                                  ska aktiveras på.
********************************************************************************/
void button_enable_interrupt(struct button* self)
{
	asm("SEI");

	if (self->io_port == IO_PORTB)
	{
		PCICR |= (1 << PCIE0);
		PCMSK0 |= (1 << self->pin);
	}
	else if (self->io_port == IO_PORTC)
	{
		PCICR |= (1 << PCIE1);
		PCMSK1 |= (1 << self->pin);
	}
	else if (self->io_port == IO_PORTD)
	{
		PCICR |= (1 << PCIE2);
		PCMSK2 |= (1 << self->pin);
	}

	self->interrupt_enabled = true;
	return;
}

/********************************************************************************
* button_disable_interrupt: Inaktiverar PCI-avbrott på angiven tryckknapp.
*
*                           - self: Pekare till tryckknappen som PCI-avbrott
*                                  ska inaktiveras på.
********************************************************************************/
void button_disable_interrupt(struct button* self)
{
	if (self->io_port == IO_PORTB)
	{
		PCMSK0 &= ~(1 << self->pin);
	}
	else if (self->io_port == IO_PORTC)
	{
		PCMSK1 &= ~(1 << self->pin);
	}
	else if (self->io_port == IO_PORTD)
	{
		PCMSK2 &= ~(1 << self->pin);
	}

	self->interrupt_enabled = false;
	return;
}

/********************************************************************************
* button_togglar_interrupt: Togglar aktivering av PCI-avbrott på angiven
*                           tryckknapp. Om avbrott är aktiverat vid anrop
*                           så sker inaktivering. På samma sätt gäller att om
*                           avbrott är inaktiverat vid anrop så sker aktivering.
*
*                           - self: Pekare till tryckknappen som aktivering av
*                                   PCI-avbrott ska inaktiveras på.
********************************************************************************/
void button_toggle_interrupt(struct button* self)
{
	if (self->interrupt_enabled)
	{
		button_disable_interrupt(self);
	}
	else
	{
		button_enable_interrupt(self);
	}

	return;
}