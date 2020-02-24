#ifndef __ADC_H_
#define	__ADC_H_

#include <xc.h> // include processor files - each processor file is guarded. 
#include <stdint.h>

//Funciones prototipo de la librería ADC
void adc_conf(uint8_t con1, uint8_t con0);
void iniciar_adc(void);

#endif	/* XC_HEADER_TEMPLATE_H */
