 #include <xc.h>
#include<stdio.h>
#include <stdint.h>
#include <string.h>
#include<pic16f877a.h>

#include "EEPROM.h"
#include "UART.h"



#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT enabled)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program M

#define _XTAL_FREQ 20000000      // PIC frequency (Hz))
#define PWM_max 500


char data_r, data_s;


void Rotation0()   // 0 degree
{
unsigned int i;
for(i=0;i<50;i++)
{
    RD0 = 1;      //connected to RB0, Motor OFF
    __delay_us(1500);     //delay of 800us
    RD0 = 0;      //connected to RB0, Motor ON
    __delay_us(18500);   //delay of 19200us
}
}

void Rotation90() //180 Degree
{
unsigned int i;
for(i=0;i<50;i++)
{
    RD0 = 1;
__delay_us(4000); // delay of 2000us
    RD0 = 0;
__delay_us(16000); //delay of 18000us
}
}
void Rotation180() //180 Degree
{
unsigned int i;
for(i=0;i<50;i++)
{
    RD0 = 1;
__delay_us(1000); // delay of 2000us
    RD0 = 0;
__delay_us(19000); //delay of 18000us
}
}

//void __interrupt() ISR(void){
//    if(INTF == 1){               // Check the flag bit 
//        RA3 = RB0;
//        INTF = 0;
//    }               
//} 
void __interrupt() ISR(void){

    if(RCIF == 1){
        
        data_r = RCREG;
        RCIF = 0;
    }
}

void main(void) {
    TRISA = 0x00;
    TRISD = 0x00;
    TRISB = 0xFF;
    PORTA = 0x00;
    
    INTEDG = 1;                 // Interrupt edge config bit (HIGH value means interrupt occurs every rising edge)
    RCIE = 1;
    PEIE = 1;
    GIE = 1;
    EEPROM_Write(1, UID1);
   
    
    UART_Init(9600);
    
    
    while(1){
        RA3 = RB0;
        if (RB0 == 1){
            RA4 = ~RA4;
            Rotation90(); //90 Degree            
            Rotation0();     
        }
        if(EEPROM_Check(data_r))  
            {   
                TXREG = data_r;                
                 Rotation90(); //90 Degree            
                 Rotation0();    
                 data_r = 0;
            }     
    } 
    
    return;
}


