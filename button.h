/*************************************************************************************
* button.h: Inneh�ller funktionalitet f�r implementering av tryckknappar och
* andra digitala inportar, d�r det finns behov av att l�sa av
* insignalen samt implementera PCI-avbrott.
**************************************************************************************/
#ifndef BUTTON_H_
#define BUTTON_H_

#include "misc.h"

// En struct som inneh�ller datatyper f�r knapparna.
struct button
{
	uint8_t pin;            /* Knappens pin-nummer p� aktuellt */
	enum io_port io_port;   /* I/O-porten som lysdioden �r ansluten till */
	bool interrupt_enabled; /* Indikerar ifall avbrott �r aktiverat. */
};

// void button_toggle(struct button* self);

/*************************************************************************************
* button_init: Initierar angiven tryckknapp och aktiverar den interna pullup-
*              resistorn p� angiven pin.
*
*              - self: Pekare till kanppen som ska initieras.
*              - pin: Pin-numret p� Arduino Uno, exempelvis 13.
**************************************************************************************/
void button_init(struct button* self, const uint8_t pin);


/*************************************************************************************
* button_is_pressed: Indikerar ifall angiven tryckknapp �r nedtryckt genom
*                    att returnera true eller false.
*
*                    - self: Pekare till tryckknappen som ska l�sas av.
**************************************************************************************/
bool button_is_pressed(const struct button* self);

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
void button_enable_interrupt(struct button* self);

/********************************************************************************
* button_disable_interrupt: Inaktiverar PCI-avbrott p� angiven tryckknapp.
*
*                           - self: Pekare till tryckknappen som PCI-avbrott
*                                  ska inaktiveras p�.
********************************************************************************/
void button_disable_interrupt(struct button* self);

/********************************************************************************
* button_toggle_interrupt: Togglar aktivering av PCI-avbrott p� angiven
*                          tryckknapp. Om avbrott �r aktiverat vid anrop
*                          s� sker inaktivering. P� samma s�tt g�ller att om
*                          avbrott �r inaktiverat vid anrop s� sker aktivering.
*
*                          - self: Pekare till tryckknappen som aktivering av
*                                  PCI-avbrott ska inaktiveras p�.
********************************************************************************/
void button_toggle_interrupt(struct button* self);


#endif /* BUTTON_H_ */