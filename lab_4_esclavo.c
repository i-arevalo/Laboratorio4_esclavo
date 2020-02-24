/*
 * File:   main_lab4_esclavo.c
 * Author: Arevalo
 *
 * Created on 20 de febrero de 2020, 01:03 AM
 */

// PIC16F887 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1
#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#include <stdint.h>
#include <pic16f887.h>
#include "SPI.h"
#include "ADC.h"

#define _XTAL_FREQ 4000000

//uint8_t cont = 0;
char pot1 = 0;
char pot2 = 0;
uint8_t ban = 1;

void init(void);
void inter_init(void);

void __interrupt() inter (void){
    //interrupción comunicación USART
    if (PIR1bits.SSPIF == 1){
        if (spi_leer() == 0x01){
            spi_escribir(pot1);
        }
        else if (spi_leer() == 0x02){
            spi_escribir(pot2);
        }
        PIR1bits.SSPIF = 0;
    }
    if (PIR1bits.ADIF == 1){
        if (ban==1){
            pot2 = ADRESH;
            ban = 2;
            adc_conf(0b00000000, 0b01110001);
        }
        else if (ban==2){
            pot1 = ADRESH;
            ban = 1;
            adc_conf(0b00000000, 0b01100001);
        }
        PIR1bits.ADIF = 0;
        __delay_ms(5);
        iniciar_adc();
    }
}

void main(void) {
    init();
    inter_init();
    spi_conf(2);
    iniciar_adc();
    spi_escribir(0x00);
    while (1){
        
    }
    //return;
}

void inter_init (void)
{
    INTCONbits.GIE = 1;
    INTCONbits.RBIE = 1;
    INTCONbits.PEIE = 1;
    PIE1bits.ADIE = 1;
    adc_conf(0b00000000, 0b01110001);
    PIE1bits.SSPIE = 1;
}

void init (void)
{
    ANSEL = 0x00;
    ANSELH = 0xFF;
    TRISA = 0x00;
    TRISB = 0xFF;
    TRISC = 0x00;
    TRISD = 0x00;
    TRISE = 0x00;
}
