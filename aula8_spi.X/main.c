/* 
 * File:   main.c
 * Author: lucascechinmario
 *
 * Created on October 8, 2026, 8:51 AM
 */

#define F_CPU 16000000
#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include <util/delay.h>

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
}

int main(void) {
    SPI_master_config();
    while(1){
        SPDR = 0xC7;
        _delay_ms(1);
    }
}

