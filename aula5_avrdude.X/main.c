/* 
 * File:   main.c
 * Author: lucascechinmario
 *
 * Created on September 10, 2026, 8:05 AM
 */

#define F_CPU 16000000

#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include "util/delay.h"

/*
 * 
 */

void GPIO_incBar(){
    PORTD = PORTD >> 1;
    PORTD |= 0b10000000;
}

void GPIO_decBar(){
    PORTD = PORTD << 1;
}

void GPIO_config(){
    DDRD |= 0xFF;//Pinos usados pelos LEDs como saída
    PORTD = 0x00;//Parte com a barra apagada
}

void main(void){
    GPIO_config();
    while(1){
        for (uint8_t i = 0; i < 8; i++) {
            GPIO_incBar();
            _delay_ms(500);
        }
        for (uint8_t i = 0; i < 8; i++) {
            GPIO_decBar();
            _delay_ms(200);
        }
    }
}