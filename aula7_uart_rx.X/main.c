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
#include <string.h>

#define RX_BUFFER_SIZE 16

uint8_t gMessage[RX_BUFFER_SIZE]; //Buffer global da UART
uint16_t gRxCounter = 0; //Contagem de bytes recebidos
uint8_t gMessageReady = 0;

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
    UBRR0 = (F_CPU / (16UL * pBAUD)) - 1;
}

void GPIO_config(){
    DDRC = (1<<DDC0)|(1<<DDC1); //PC0 e PC1 como saída
}

ISR(USART_RX_vect){
    uint8_t tReceivedByte = UDR0;//Leitura do buffer 
    gMessage[gRxCounter] = tReceivedByte;
    gRxCounter++;
    if(gRxCounter < RX_BUFFER_SIZE - 1){
        gMessage[gRxCounter] = tReceivedByte;
        gRxCounter++;
    }
    if(tReceivedByte == '\n'){
        gMessageReady = 1;//Flag de mensagem completa
    }
}

int main(void) {
    GPIO_config();
    UART_config_rx(9600);
    sei();//Habilita interrupções globalmente
    while(1){
        if(gMessageReady){
            gMessageReady = 0;
        }
        //Tratamento de mensagem recebida
        if(strcmp((char*)gMessage, "Mensagem\n") == 0){
            PORTC |= (1<<PORTC0); //LED VERDE
        }
        else{
            PORTC |= (1<<PORTC1); //LED VERMELHO
        }
        _delay_ms(10);
        PORTC = 0; //Apaga todos os leds
    }
}

