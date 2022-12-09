/**************************************************************************************
* ADC.c: Innehåller funktionalitet för AD-omvandling och PWM.
**************************************************************************************/
#include "header.h"
#include "led_vector.h"
#include "ADC.h"

/**************************************************************************************
* adc_read: Läser av analog insignal från angiven pin och returnerar motsvarande
*           digitala värde mellan 0-1023.
*
*           1. Väljer intern matningsspänning via ettställning av biten REFS0
*              i registret ADMUX (ADC Multiplexer Select Register). Vi väljer
*              också analog kanal genom att skriva in-numret till MUX-bitar
*              MUX[3:0] i samma register.
*
*           2. Aktiverar och startar AD-omvandlaren genom att ettställa bitar
*              ADEN (ADC Enable) samt ADSC
*
*           3. Vi väntar p att AD-omvandlingen slutförs, vilket indikeras då
*              interrupt-flaggan ADIF (AD
*
*           -pin: Analog pin som ska läsas av.
**************************************************************************************/
uint16_t adc_read(const uint8_t pin)
{
	ADMUX = (1 << REFS0) | pin; // Vilken pin som det analoga värdet komer in på.
	ADCSRA = (1 << ADEN) | (1 << ADSC) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // Sätter pre-scale till 128.
	while ((ADCSRA & (1 << ADIF)) == 0); // Sålänge flaggan är lika med noll så väntar vi på AD-omvandlaren.
	ADCSRA = (1 << ADIF); // När flaggan är lika med 1 så resetas den.
	return ADC; // returnerar AD-omvandlingens värde.
}

/**************************************************************************************
* adc_get_pwm_values: Läser av insignalen från angiven analog pin och beräknar
*                     PWM-värden (on- off tid) i mikrosekunder utefter
*                     angiven periodtid. Beräknade värden lagras på angivna
*					  adresser.
*
*                     - pin        : Analog pin A0 - A5 som ska läsas av.
*                     - period_us  : Periodtid i mikrosekunder.
*                     - on_time_us : Adress där on-tiden ska lagras.
*                     - off_time_us: Adress där off-tiden ska lagras.
**************************************************************************************/
void adc_get_pwm_values(const uint8_t pot, const uint16_t period_us, uint16_t* on_time_us, uint16_t* off_time_us)
{
	const double duty_cycle = adc_read(pot) / 1023.0;
	*on_time_us = (uint16_t)(period_us * duty_cycle + 0.5);
	*off_time_us = period_us - *on_time_us;
	
	return;
}

/**************************************************************************************
* pwm_run: skickar hur lång tid en period är och får tillbaka pwm värdena för
*          på och av-tid.
*          Kollar därefter vilka leds som är aktiverade och tänder dem enligt
*          pwm-värdena.
*
*          - on_time_us : Adress där on-tiden ska lagras.
*          - off_time_us: Adress där off-tiden ska lagras.
**************************************************************************************/
void pwm_run(const uint8_t pot, const uint16_t period_us)
{
	uint16_t pwn_on_us;   // Initierar av och på tid för leds.
	uint16_t pwn_off_us;
	
	adc_get_pwm_values(pot, period_us, &pwn_on_us, &pwn_off_us);  // Ändrar av och på-tiden med potentiometer.
	
	if (led1_enabled) led_on(&l1);  // Tänder lysdioderna om dem är aktiverade.
	if (led2_enabled) led_on(&l2);
	if (led3_enabled) led_on(&l3);
	if (led4_enabled) led_on(&l4);
	if (led5_enabled) led_on(&l5);
	
	delay_us(&pwn_on_us);  // Håller lysdioden tänd under on-tiden.
	
	led_off(&l1);  // Släcker lysdioder.
	led_off(&l2);
	led_off(&l3);
	led_off(&l4);
	led_off(&l5);
	
	delay_us(&pwn_off_us); // Håller lysdioden släckt under off-tiden.
}