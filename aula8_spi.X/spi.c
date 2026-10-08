/* 
 * File:   spi.c
 * Author: lucascechinmario
 *
 * Created on 8 de Outubro de 2026, 10:34
 */

#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>
#include <stdint.h>

/*
 * 
 */

void SPI_master_config(){
    SPCR = (1 << SPE)|(1 << DORD) //Habilita SPI, Ordem MSB primeiro(padrão)
        |(1 << MSTR) //Modo Mestre
        |(0 << CPOL)|(0 << CPHA) //SPI modo 0
        |(0 << SPR1)|(0 << SPR0); //Divisor fosc/2, CLK->8Mhz
    SPSR = (1 << SPI2X); //Velocidade dobrada
    DDRB = (1 << DDB3)|(1 << DDB5); //Config dos pinos MOSI e SCK como saída
    DDRC = (1 << DDC0); //Usando PC0 como Slave Select (Saída)
    PORTC |= (1 << PORTC0); //Slave select em nível alto
}

uint8_t SPI_transceive(uint8_t pTxByte){
    uint8_t tReceivedByte;
    PORTC &= ~(1 << PORTC0); //Slave select em nível baixo
    SPDR = pTxByte; //Escrita no SPDR dispara a transação
    while((SPSR & (1 << SPIF)) == 0); //Espera a flag SPIF subir
    tReceivedByte = SPDR; //Leitura do registrador
    PORTC |= (1 << PORTC0); //Slave select em nível alto
    return tReceivedByte;
}
