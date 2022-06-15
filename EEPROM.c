/*
 * File:   EEPROM.c
 * Author: talon
 *
 * Created on June 15, 2022, 5:17 PM
 */


#include <xc.h>
#include<stdint.h>
#include "EEPROM.h"

char EEPROM_Read(uint8_t Address){
    // Step 1
    EEADR = Address;
    // Step 2
    EEPGD = 0;
    // Step 3
    EECON1bits.RD = 1;
    // Step 4
    return EEDATA;
}

void EEPROM_Write(uint8_t Address, char Data){
    // Step 1
    while(WR);
    // Step 2
    EEADR = Address;
    // Step 3
    EEDATA = Data;
    // Step 4
    EEPGD = 0;
    // ------------ Step 5
    EECON1bits.WREN = 1;
    // Step 6
    GIE = 0;
    // Step 7
    EECON2 = 0x55;
    EECON2 = 0xAA;
    EECON1bits.WR = 1;
    // Step 8
    GIE = 1;
    // Step 9
    EECON1bits.WREN = 0;
    // Step 10
    EECON1bits.WR = 0;
}
uint8_t EEPROM_Check(char uid)
{
  
    for(int i = 0 ; i < EEPROM_Size ; i ++)
    {
        if(uid == EEPROM_Read(i))
        {
            return 1;
        }
    }
    return 0;
}

