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
#include "spi.h"

int main(void) {
    SPI_master_config();
    while(1){
        SPI_transceive(0x45);
        _delay_ms(1);
    }
}

