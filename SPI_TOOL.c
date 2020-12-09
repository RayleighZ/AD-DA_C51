//
// Created by Lenovo on 2020-12-09.
//

#ifndef ADDA_SPI_TOOL_C
#define ADDA_SPI_TOOL_C
#include "SPI_TOOL.h"
#include <intrins.h>
void spiWrite(unsigned char dat){
    unsigned char i;
    CLK = 0;//时钟端置零，方便之后形成上升沿
    for (i = 0; i < 8; i++) {
        DIN = dat >> 7;//左移七位
        dat <<= 1;//右移一位
        CLK = 0;//形成上升沿
        CLK = 1;
    }
}

unsigned int spiRead(){
    unsigned int i, dat = 0;
    CLK = 0;

    for (i = 0; i < 12; ++i) {
        dat <<=1;
        CLK = 1;
        CKK = 0;

        dat |= DOUT;
    }

    return dat;
}

unsigned int readAdc(unsigned char cmd){
    unsigned char i;
    unsigned int adValue;
    CLK = 0;
    spiWrite(cmd);//写入指令
    for (int i = 6; i > 0; --i);
    CLK = 1;
    _nop_();
    _nop_();
    CLK = 0;
    _nop_();
    _nop_();
    adValue = spiRead();
    CS = 1;
    return adValue;
}

#endif //ADDA_SPI_TOOL_C
