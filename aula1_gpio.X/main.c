/*
 * File:   main.c
 * Author: lucascechinmario
 *
 * Created on August 20, 2026, 9:06 AM
 */

#define F_CPU 16000000
#include <xc.h>
#include "util/delay.h"

void main(void) {
    DDRB |= 0b00100000; //define pino PB5 como saída
    while (1){
        PORTB |= 0b00100000; //atribui nível lógico alto ao pino PB5
        _delay_ms(100);
        PORTB &= 0b11011111;
        _delay_ms(900);
    }
}
