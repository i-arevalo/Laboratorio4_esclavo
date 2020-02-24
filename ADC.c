#include <xc.h> // include processor files - each processor file is guarded. 
#include "ADC.h"

//Función para configurar el ADC
void adc_conf(uint8_t con1, uint8_t con0){
    ADCON0 = con0;
    ADCON1 = con1;
}

//Función para iniciar la conversión ADC
void iniciar_adc(void){
    ADCON0bits.GO = 1;
}
