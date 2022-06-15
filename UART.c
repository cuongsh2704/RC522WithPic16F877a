/*
 * File:   UART.c
 * Author: talon
 *
 * Created on June 15, 2022, 5:15 PM
 */


#include <xc.h>
#include <stdint.h>
#include "UART.h"
#define _XTAL_FREQ 20000000      // PIC frequency (Hz))


uint8_t UART_Init(const long int baudrate)
{
	uint8_t x;
	x = (_XTAL_FREQ - baudrate*64)/(baudrate*64);
	if(x>255)
	{
		x = (_XTAL_FREQ - baudrate*16)/(baudrate*16);
		BRGH = 1;
	}
	if(x<256)
	{
	  SPBRG = x;
	  SYNC = 0;
	  SPEN = 1;
          TRISC7 = 1;
          TRISC6 = 0;
          CREN = 1;
          TXEN = 1;
	  return 1;
	}
	return 0;
}

char UART_TX_Empty()
{
  return TRMT;
}

uint8_t UART_Data_Ready()
{
   return RCIF;
}
char UART_Read()
{
 
  while(!RCIF);
  RCIF =0;
  return RCREG;
}

void UART_Read_Text(char *Output, unsigned int length)
{
	unsigned int i;
	for(int i=0;i<length;i++)
		Output[i] = UART_Read();
}

void UART_Write(char data)
{
  while(!TRMT);
  TXREG = data;
  TRMT = 0;
}

void UART_Write_Text(uint8_t *text)
{
  int i;
  for(i=0;text[i]!='\0';i++)
	  UART_Write(text[i]);
}
