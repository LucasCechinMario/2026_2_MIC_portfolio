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

void GPIO_config(){
    DDRB |= (1<<DDB5);//Pino PB5 (13) como saída
}

void main(void){
    GPIO_config();
    while(1){
        PORTB ^= (1<<PORTB5);//Alterna o estado do LED
        _delay_ms(500);
    }
}