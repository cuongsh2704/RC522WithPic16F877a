 #include <xc.h>
#include<stdio.h>
#include <stdint.h>
#include <string.h>
#include<pic16f877a.h>

#include "EEPROM.h"
#include "UART.h"



#pragma config FOSC = HS        // Oscillator Selection bits (XT oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT enabled)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program M

#define _XTAL_FREQ 20000000      // PIC frequency (Hz))



char data_r, data_s;




void main(void) {
    TRISA = 0x00;
    TRISD = 0x00;
    PORTA = 0x00;
    
    EEPROM_Write(1, UID1);
   
    
    UART_Init(9600);
    
    
    while(1){
        data_r = UART_Read();
        if(EEPROM_Check(data_r))  
            {
                TXREG = data_r;
//             TRMT = 1;
                   RA3 = 1;
                   __delay_ms(1000);
                   RA3 = 0;
                  
                
            }
       
        
       
    } 
    
    return;
}


