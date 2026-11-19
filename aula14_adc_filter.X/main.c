/* 
 * File:   main.c
 * Author: lucascechinmario
 *
 * Created on November 12, 2026, 10:20 AM
 */

#include <xc.h>
#include "avr/interrupt.h"

//Termos da função transferência (Butterworth de ordem 2, corte em 0.114 * fs = 114Hz)
const int16_t b[3] = {1372, 2744, 1372};
const int16_t a[2] = {-16899, 6002};

int16_t x[3]; //Medidas do ADC
int16_t y[3]; //Saída do filtro

ISR(ADC_vect) { // Interrupção referente a conversão concluída
	PORTB |= (1<<PORTB1); //Debug: tempo de processamento
	
	uint16_t tADCData = ADC; // Acesso a ADCH e ADCL como um único registrador de 16 bits, faixa de inteiros de 0 a 1023 (ADLAR=0)
	
	//Linha de atraso dos sinais x e y (fila FIFO)
	x[2] = x[1];
	x[1] = x[0];
	x[0] = tADCData;
	y[2] = y[1];
	y[1] = y[0];
	y[0] = b[0] * x[0] + b[1] * x[1] + b[2] * x[2] - a[0] * y[1] - a[1] * y[2];
	
	if(y < 670) {
		PORTB ^= (1<<PORTB0); //Acender LED abaixo de 720mV
	} else {
		PORTB &= ~(1<<PORTB0); //Apagar LED caso contr�rio
	}
	
	PORTB &= ~(1<<PORTB1); //Debug: tempo de processamento
}

void ADC_config() {
	ADMUX	= (0<<MUX3)|(0<<MUX2)|(0<<MUX1)|(0<<MUX0)	// Canal de conversão: pino ADC0
			| (1<<REFS1)|(1<<REFS0);					// Referência de tens�o interna (1.1V)
	ADCSRA	= (1<<ADEN)|(1<<ADATE)						// Habilita o ADC em modo 'auto trigger'
			| (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0)			// Fator de prescale 128 (125kHz freq do adc)
			| (1<<ADIE);								// Habilita interrupção do AD
	DIDR0	= (1<<ADC0D);								// Desabilita porta PC0 (função digital do pino ADC0)
	ADCSRB	= (1<<ADTS2)|(0<<ADTS1)|(1<<ADTS0);			// Fonte do disparo: TMR1 Compare match B
}

//Configurar Timer 1 para disparo a cada 1 ms
void TMR1_config() {
	TCCR1A	= (0<<WGM11)|(0<<WGM10);
	TCCR1B	= (0<<WGM13)|(1<<WGM12) //Modo 4: CTC com topo em OCR1A
			| (0<<CS12)|(0<<CS11)|(1<<CS10); //Prescaler unitário
	OCR1A	= 15999; //Per�odo de 1ms
	OCR1B	= 0;
}

int main(void) {
	DDRB = (1<<DDB1)|(1<<DDB0); //Pinos PB0 e PB como saídas
	TMR1_config();
	ADC_config();
	sei();
    while(1) {
        //TODO:: Please write your application code 
    }
}
