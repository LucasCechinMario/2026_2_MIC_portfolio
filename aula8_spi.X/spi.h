/*
 * spi.h
 *
 * Created: 08/10/2026 10:40:40
 *  Author: lucascechinmario
 */ 


#ifndef SPI_H_
#define SPI_H_

void SPI_master_config();
uint8_t SPI_transceive(uint8_t pTxByte);

#endif /* SPI_H_ */