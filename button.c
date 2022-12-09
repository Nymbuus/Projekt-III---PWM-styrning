#include "button.h"

/*************************************************************************************
* button_init: Initierar angiven tryckknapp och aktiverar den interna pullup-
*              resistotoen p� angiven pin.
*
*              1. Vi sparar vilken I/O-port vi �r p� (pin 0-7 = D, pin 8 - 13 = B).
*
*              2. Vi sparar vilket pin-nummer p� aktuell I/O-port som knappen
*                 �r ansluten till (s� att vi kan l�sa av r�tt bit).
*
*              3. Vi aktiverar den interna pullup-resistorn p� aktuell pin
*                 s� att insigna�en alltid blir 0 eller 1 (l�g eller h�g),
*                 inget flytande d�r emellan.
*
*              - self: Pekare till kanppen som ska initieras.
*              - pin: Pin-numret p� Arduino Uno, exempelvis 13.
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
* button_is_pressed: Indikerar ifall angiven tryckknapp �r nedtryckt genom
*                    att returnera true eller false.
*
*                    1. Vi unders�ker vilken I/O-port knappen �r ansluten till
*                       f�r att veta vilket PIN-register som ska l�sas av
*                       (PINB, PINC eller PIND). Vi kollar d�rmed v�r medlem
*                       io_port.
*
*                    2. n�r vi f�tt reda p� vilken I/O_port knappen �r ansluten
*                       till s� l�ser vi av den pin som tryckknappen �r
*                       ansluten till (medlemmen pin) och returnerar detta v�rde.
*                       Det v�rde som reutneraras blir true om knappen �r
*                       nedtryckt, annars false.
*
*                    - self: Pekare till tryckknappen som ska l�sas av.
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
* button_enable_interrupt: Aktiverar PCI-avbrott p� angiven tryckknapp s� att
*                          event p� tryckknappens pin medf�r avbrott, b�de p�
*                          stigande och fallande flank. Kontroll av flank m�ste
*                          sk�tas av anv�ndaren, f�rslagsvis via avl�sning i
*                          motsvarande avbrottsrutin.
*
*                          Nedan visas sambandet mellan anv�nd I/O-port samt
*                          avbrottsvektorn f�r motsvarande avbrottsrutin:
*
*                          I/O-port     pin (Arduino Uno)     Avbrottsvektor
*                             B              8 - 13             PCINT0_vect
*                             C             A0 - A5             PCINT1_vect
*                             D              0 - 7              PCINT2_vect
*
*                          - self: Pekare till tryckknappen som PCI-avbrott
*                                  ska aktiveras p�.
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
* button_disable_interrupt: Inaktiverar PCI-avbrott p� angiven tryckknapp.
*
*                           - self: Pekare till tryckknappen som PCI-avbrott
*                                  ska inaktiveras p�.
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
* button_togglar_interrupt: Togglar aktivering av PCI-avbrott p� angiven
*                           tryckknapp. Om avbrott �r aktiverat vid anrop
*                           s� sker inaktivering. P� samma s�tt g�ller att om
*                           avbrott �r inaktiverat vid anrop s� sker aktivering.
*
*                           - self: Pekare till tryckknappen som aktivering av
*                                   PCI-avbrott ska inaktiveras p�.
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