/* 
 * File:   main.c
 * Author: lucascechinmario
 *
 * Created on August 27, 2026, 10:27 AM
 */

#define F_CPU 16000000
#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include <avr/interrupt.h>
#include <util/delay.h>


/*
 *Configuração da Interrupção Externa (INT0/INT1) 
 */
ISR(INT0_vect){ //Função no vetor de interrupção INT0
    PORTB |= (1<<PORTB1); //Acende led em PB1
    _delay_ms(50);
    PORTB &= ~(1<<PORTB1); //Apaga led em PB1
}

ISR(INT1_vect){ //Função no vetor de interrupção INT0
    PORTB |= (1<<PORTB1); //Acende led em PB1
    _delay_ms(100);
    PORTB &= ~(1<<PORTB1); //Apaga led em PB1
}


void INT_config(){
    EICRA = (1<<ISC11)|(1<<ISC10)|(1<<ISC01)|(0<<ISC00); //configura INT1 borda de subida, INT0 borda de descida
    EIMSK = (1<<INT0)|(1<<INT1); //Habilita INT0
}

void GPIO_config(){
    DDRB |= (1<<DDB0);//saída
    DDRB |= (1<<DDB1);//saída
}

int main(void) {
    INT_config();
    GPIO_config();
    sei(); //Habilita Interrupções globalmente
    while(1){
        cli(); //Desabilita interrupções temporáriamente
        PORTB |= (1<<PORTB0);
        _delay_ms(100);
        sei(); //Habilita novamente
        PORTB &= ~(1<<PORTB0);
        _delay_ms(100);
    }
}

