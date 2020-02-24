#include <xc.h>
#include <stdint.h>
//#include <pic16f887.h>
#include "SPI.h"


//#define _XTAL_FREQ 4000000

//función para configurar al PIC dependiendo de su función dentro de la comuniación SPI
void spi_conf(uint8_t op){
    switch (op){
        //maestro recibe
        case 1:
            TRISCbits.TRISC5 = 0;
            SSPSTATbits.SMP = 0;
            SSPSTATbits.CKE = 0;
            SSPCONbits.SSPEN = 1;
            SSPCONbits.CKP = 0;
            
            SSPCONbits.SSPM3 = 0;
            SSPCONbits.SSPM2 = 0;
            SSPCONbits.SSPM1 = 0;
            SSPCONbits.SSPM0 = 0;
            TRISCbits.TRISC3 = 0;
            break;
        //esclavo envia
        case 2:
            TRISCbits.TRISC5 = 0;
            SSPSTATbits.SMP = 0;
            SSPSTATbits.CKE = 0;
            SSPCONbits.SSPEN = 1;
            SSPCONbits.CKP = 0;
            
            SSPCONbits.SSPM3 = 0;
            SSPCONbits.SSPM2 = 1;
            SSPCONbits.SSPM1 = 0;
            SSPCONbits.SSPM0 = 1;
            TRISCbits.TRISC3 = 1;
            break;
    }
}

//Función para enviar dato por medio de SPI
void spi_escribir(char dato){
    SSPBUF = dato;
}

//función para saber si la transferencia de datos ya finalizo
uint8_t spi_puede_leer(void){
    if (SSPSTAT & 00000001)
        return 1;
    else
        return 0;
}

//función para leer el dato recivido
char spi_leer(void){
    return SSPBUF;
}
