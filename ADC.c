/**************************************************************************************
* ADC.c: Inneh�ller funktionalitet f�r AD-omvandling och PWM.
**************************************************************************************/
#include "header.h"
#include "led_vector.h"
#include "ADC.h"

/**************************************************************************************
* adc_read: L�ser av analog insignal fr�n angiven pin och returnerar motsvarande
*           digitala v�rde mellan 0-1023.
*
*           1. V�ljer intern matningssp�nning via ettst�llning av biten REFS0
*              i registret ADMUX (ADC Multiplexer Select Register). Vi v�ljer
*              ocks� analog kanal genom att skriva in-numret till MUX-bitar
*              MUX[3:0] i samma register.
*
*           2. Aktiverar och startar AD-omvandlaren genom att ettst�lla bitar
*              ADEN (ADC Enable) samt ADSC
*
*           3. Vi v�ntar p att AD-omvandlingen slutf�rs, vilket indikeras d�
*              interrupt-flaggan ADIF (AD
*
*           -pin: Analog pin som ska l�sas av.
**************************************************************************************/
uint16_t adc_read(const uint8_t pin)
{
	ADMUX = (1 << REFS0) | pin; // Vilken pin som det analoga v�rdet komer in p�.
	ADCSRA = (1 << ADEN) | (1 << ADSC) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // S�tter pre-scale till 128.
	while ((ADCSRA & (1 << ADIF)) == 0); // S�l�nge flaggan �r lika med noll s� v�ntar vi p� AD-omvandlaren.
	ADCSRA = (1 << ADIF); // N�r flaggan �r lika med 1 s� resetas den.
	return ADC; // returnerar AD-omvandlingens v�rde.
}

/**************************************************************************************
* adc_get_pwm_values: L�ser av insignalen fr�n angiven analog pin och ber�knar
*                     PWM-v�rden (on- off tid) i mikrosekunder utefter
*                     angiven periodtid. Ber�knade v�rden lagras p� angivna
*					  adresser.
*
*                     - pin        : Analog pin A0 - A5 som ska l�sas av.
*                     - period_us  : Periodtid i mikrosekunder.
*                     - on_time_us : Adress d�r on-tiden ska lagras.
*                     - off_time_us: Adress d�r off-tiden ska lagras.
**************************************************************************************/
void adc_get_pwm_values(const uint8_t pot, const uint16_t period_us, uint16_t* on_time_us, uint16_t* off_time_us)
{
	const double duty_cycle = adc_read(pot) / 1023.0;
	*on_time_us = (uint16_t)(period_us * duty_cycle + 0.5);
	*off_time_us = period_us - *on_time_us;
	
	return;
}

/**************************************************************************************
* pwm_run: skickar hur l�ng tid en period �r och f�r tillbaka pwm v�rdena f�r
*          p� och av-tid.
*          Kollar d�refter vilka leds som �r aktiverade och t�nder dem enligt
*          pwm-v�rdena.
*
*          - on_time_us : Adress d�r on-tiden ska lagras.
*          - off_time_us: Adress d�r off-tiden ska lagras.
**************************************************************************************/
void pwm_run(const uint8_t pot, const uint16_t period_us)
{
	uint16_t pwn_on_us;   // Initierar av och p� tid f�r leds.
	uint16_t pwn_off_us;
	
	adc_get_pwm_values(pot, period_us, &pwn_on_us, &pwn_off_us);  // �ndrar av och p�-tiden med potentiometer.
	
	if (led1_enabled) led_on(&l1);  // T�nder lysdioderna om dem �r aktiverade.
	if (led2_enabled) led_on(&l2);
	if (led3_enabled) led_on(&l3);
	if (led4_enabled) led_on(&l4);
	if (led5_enabled) led_on(&l5);
	
	delay_us(&pwn_on_us);  // H�ller lysdioden t�nd under on-tiden.
	
	led_off(&l1);  // Sl�cker lysdioder.
	led_off(&l2);
	led_off(&l3);
	led_off(&l4);
	led_off(&l5);
	
	delay_us(&pwn_off_us); // H�ller lysdioden sl�ckt under off-tiden.
}