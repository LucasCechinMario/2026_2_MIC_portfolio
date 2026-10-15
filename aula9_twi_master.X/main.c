/* 
 * File:   main.c
 * Author: lucascechinmario
 *
 * Created on October 15, 2026, 9:02 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>

/*
 * 
 */

void  TWI_master_config(){
    TWBR = 64; //Divisor 64, fscl=100KHz
    TWSR |= (0 << TWPS1)|(0 << TWPS0); //Prescaler de 1
    TWCR |= (1 << TWEN); //Habilita o periférico
}

int main(void) {
    while(1){
        //Inicia uma transmissão como mestre
        TWCR |= (1 << TWSTA); //Inicia condição de start
        while((TWCR & (1 << TWINT)) == 0); //Aguarda flag de interrupção subir
        //Condição de start ok ??
        TWCR |= (1 << TWINT); //Limpar flag de interrupção subir
        uint8_t tStatusCode = (TWSR & 0b1111100);
        //Condição de start ok??
        if(tStatusCode == 0x08){
            //Condição de start
        }
        else{
            //Algum erro
        }
        TWCR |= (1 << TWINT);
    }
}

