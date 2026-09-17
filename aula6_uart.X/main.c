/* 
 * File:   main.c
 * Author: lucascechinmario
 *
 * Created on September 17, 2026, 10:16 AM
 */

#define F_CPU 16000000

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include <util/delay.h>
/*
 * Configuração do módulo USART0 para modo assíncrono, frame de 8 bits, paridade par, BAUD de 9600
 */
void UART_config(){
    UCSR0A = 0;
    UCSR0B = (1<<RXEN0)|(1<<TXEN0)|(0<<UCSZ02);//Habilita o transmissor UART0, frame de 8 bits
    UCSR0C = (0<<UMSEL01)|(0<<UMSEL00)//Modo assíncrono
            |(1<<UPM01)|(0<<UPM00)//Habilita paridade par
            |(0<<USBS0)//1 bit de stop
            |(1<<UCSZ01)|(1<<UCSZ00)//frame de 8bits
            |(0<<UCPOL0);//Polaridade do clock
    UBRR0 = 103;//BAUD de 9600, erro de 0,16%
}

//Envia um byte na USART0
void UART_send(){
    UDR0 = 0x53;//Envia um byte exemplo
    _delay_ms(2);
}

int main(void) {
    UART_config();
    while(1){
        UART_send();
    }
}

