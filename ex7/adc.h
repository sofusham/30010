/*
 * adc.h
 *
 *  Created on: 11. jun. 2023
 *      Author: sofus
 */

#ifndef ADC_H_
#define ADC_H_

void configureADC();
int16_t measurePA0();
int16_t measurePA1();
void setPinPA0();
void setPinPA1();
void initPins();


#endif /* ADC_H_ */
