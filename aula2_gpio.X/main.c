/* 
 * File:   main.c
 * Author: lucascechinmario
 *
 * Created on August 27, 2026, 8:27 AM
 */

#define F_CPU 16000000
#include <xc.h>
#include <stdint.h>
#include "util/delay.h"

/* 
 * Controle de vários  LEDs com operações de shift
 */
void GPIO_config(){
    DDRB = (1<<DDB6)|(1<<DDB4)|(1<<DDB2)|(1<<DDB0); //Bits pares são configurados com 
}

int main(void){
    GPIO_config();
    uint8_t tData = 0x03; //0b00000011
    while(1){
        PORTB = tData;
        _delay_ms(1000);
        tData = tData << 1; //0b00000110 e sempre irá se alterar deslocando para esquerda
    }
}

