/*
 * File:   MultipleSwitches_pic12f675.c
 * Author: Andre
 *
 * Created on 10 de Julho de 2023, 19:30
 */


// CONFIG
#pragma config FOSC = INTRCIO   // Oscillator Selection bits (INTOSC oscillator: I/O function on GP4/OSC2/CLKOUT pin, I/O function on GP5/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-Up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // GP3/MCLR pin function select (GP3/MCLR pin function is digital I/O, MCLR internally tied to VDD)
#pragma config BOREN = OFF      // Brown-out Detect Enable bit (BOD disabled)
#pragma config CP = OFF         // Code Protection bit (Program Memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#define SW1 GPIObits.GP1
#define SW2 GPIObits.GP2
#define SW3 GPIObits.GP4
#define SW4 GPIObits.GP5

#include <xc.h>

#define _XTAL_FREQ 4000000

void ADC_Init(void){
    //Configuracion del ADC
    ADCON0bits.ADFM = 1;
    ADCON0bits.VCFG = 0;//Voltage Reference VDD
    ADCON0bits.CHS  = 0b00; //Select chanel AN0
    ANSELbits.ADCS  = 0b100; //  FOSC/4
    ANSELbits.ANS   = 0b0001;
    ADCON0bits.ADON = 1;//Turn ADC on
    
}

void MCU_Init(void){
    ADC_Init(); //Configura e inicializa o ADC
    TRISIO = 0b00000001; // GP0/AN0 como entrada e o restante como saída
    GPIO   = 0b00000000; // inicia todas as saídas em low
}

unsigned int ADC_Read(void){
    int RESULT_ADC = 0;  // variável de armazenamento da saída do adc
    ADCON0bits.GO = 1;//Start ADC
    while(ADCON0bits.GO); // aguardando a conversão
        RESULT_ADC = (ADRESH << 8);
        RESULT_ADC = RESULT_ADC + ADRESL;
    return (RESULT_ADC);//Return ADC value
}

unsigned int leitura = 0;

void main(void) {
    
    
    MCU_Init();
    
    
    do {
        
   leitura = ADC_Read();
   
   if(leitura > 700) { // SW4
     SW4 = ~SW4;
     __delay_ms(250);
   }
   if(leitura > 500 && leitura < 700) { // SW3
     SW3 = ~SW3;
     __delay_ms(250);
   }
   if(leitura > 300 && leitura < 500) { // SW2
     SW2 = ~SW2;
     __delay_ms(250);
   }
   if(leitura > 100 && leitura < 300) { // SW1
     SW1 = ~SW1;
     __delay_ms(250);
   }
  } while(1);
          
}