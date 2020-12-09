//
// Created by Lenovo on 2020-12-09.
//

#ifndef ADDA_SPI_TOOL_H
#define ADDA_SPI_TOOL_H
void spiWrite(unsigned char dat);

unsigned int spiRead();

unsigned int readAdc(unsigned char cmd);
#endif //ADDA_SPI_TOOL_H
