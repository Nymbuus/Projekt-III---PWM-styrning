/**************************************************************************************
* ADC.h: Innehåller initieringar för funktionalitet i AD-omvandling och PWM.
**************************************************************************************/
#ifndef ADC_H_
#define ADC_H_

#include "misc.h"

/**************************************************************************************
* adc_read: Läser av analog insignal från angiven pin och returnerar motsvarande
*           digitala värde mellan 0-1023.
*
*           -pin: Analog pin som ska läsas av.
**************************************************************************************/
uint16_t adc_read(const uint8_t pin);

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
void adc_get_pwm_values(const uint8_t pin, const uint16_t period_us, uint16_t* on_time_us, uint16_t* off_time_us);

void pwm_run(const uint8_t pot,  const uint16_t period_us);

#endif /* ADC_H_ */