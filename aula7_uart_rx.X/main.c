/* 
 * File:   main.c
 * Author: lucascechinmario
 *
 * Created on September 24, 2026, 10:22 AM
 */

#define F_CPU 16000000

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include <util/delay.h>
#include "avr/interrupt.h"

char gMessage[16] = "Mensagem"; //"Null terminated strings" (8 bytes + 1 terminação nula)

/*
 * Configuração do módulo USART0 para modo assíncrono, frame de 8 bits, paridade par
 */
void UART_config_rx(uint16_t pBAUD){
    UCSR0A = (0<<U2X0);
    UCSR0B = (1<<RXEN0)|(0<<TXEN0)|(0<<UCSZ02)//Habilita o receptor UART0, frame de 8 bits
            | (1<<RXCIE0);//Habilita interrupção
    UCSR0C = (0<<UMSEL01)|(0<<UMSEL00)//Modo assíncrono
            |(1<<UPM01)|(0<<UPM00)//Habilita paridade par
            |(1<<USBS0)//1 bit de stop
            |(1<<UCSZ01)|(1<<UCSZ00)//frame de 8bits
            |(0<<UCPOL0);//Polaridade do clock: ignorada
    UBRR0 = (1000000 / pBAUD) - 1;//BAUD de 9600, erro de 0,16%
}

void GPIO_config(){
    DDRC = (1<<DDC0)|(1<<DDC1); //PC0 e PC1 como saída
}

ISR(USART_RX_vect){
    uint8_t tReceivedByte = UDR0;
    //Tratamento de mensagem recebida
    if(tReceivedByte == 'M'){
        PORTC |= (1<<PORTC0); //LED VERDE
    }
    else{
        PORTC |= (1<<PORTC1); //LED VERMELHO
    }
    _delay_ms(1);
    PORTC = 0; //Apaga todos os leds
}

int main(void) {
    GPIO_config();
    UART_config_rx(9600);
    sei();//Habilita interrupções globalmente
    while(1){
        //
    }
}

