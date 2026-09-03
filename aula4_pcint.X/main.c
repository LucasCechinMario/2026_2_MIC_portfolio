/*
 * File:   main.c
 * Author: lucascechinmario
 *
 * Created on September 3, 2026, 8:59 AM
 */

#define F_CPU 16000000
#include <xc.h>
#include <avr/interrupt.h>
#include <util/delay.h>

void GPIO_config(){
    DDRB &= ~((1<<DDB0)|(1<<DDB1)|(1<<DDB2)|(1<<DDB3)); //Portas PB0, PB1, PB2, PB3 como entrada
    PORTB |= (1<<DDB0)|(1<<DDB1)|(1<<DDB2)|(1<<DDB3);// habilita pull up
    DDRD = 0xff; //Seta todos como saída
    DDRC |= (1<<DDC0);//Pino PC0 como saída;
}

void PCINT_config(){
    PCICR |= (1<<PCIE0); //habilita grupo PCINT0-PCINT7
    PCMSK0 |= (1<<PCINT0)|(1<<PCINT1)|(1<<PCINT2)|(1<<PCINT3); //habilita interrupção nesses PCINT
}

void GPIO_incBar(){
    PORTD = PORTD >> 1;
    PORTD |= 0b10000000; //aciona bit mais significativo
}


ISR(PCINT0_vect){
    PORTC |= (1<<PORTC0);//seta pino PC0
    _delay_ms(100);
    PORTC &= ~(1<<PORTC0);//limpa pino PC0
    GPIO_incBar();
}

void main(void) {
    GPIO_config();
    PCINT_config();
    sei();
    while(1){
    }
}
