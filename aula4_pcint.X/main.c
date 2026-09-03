/*
 * File:   main.c
 * Author: lucascechinmario
 *
 * Created on September 3, 2026, 8:59 AM
 */


#include <xc.h>
#include <avr/interrupt.h>


ISR(PCINT0_vect){
}

void GPIO_config(){
    DDRB &= ~((1<<DDB0)|(1<<DDB1)|(1<<DDB2)|(1<<DDB3));
}

void PCINT_config(){
}

void main(void) {
    return;
}
