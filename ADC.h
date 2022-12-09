/**************************************************************************************
* ADC.h: Inneh�ller initieringar f�r funktionalitet i AD-omvandling och PWM.
**************************************************************************************/
#ifndef ADC_H_
#define ADC_H_

#include "misc.h"

/**************************************************************************************
* adc_read: L�ser av analog insignal fr�n angiven pin och returnerar motsvarande
*           digitala v�rde mellan 0-1023.
*
*           -pin: Analog pin som ska l�sas av.
**************************************************************************************/
uint16_t adc_read(const uint8_t pin);

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
void adc_get_pwm_values(const uint8_t pin, const uint16_t period_us, uint16_t* on_time_us, uint16_t* off_time_us);

void pwm_run(const uint8_t pot,  const uint16_t period_us);

#endif /* ADC_H_ */