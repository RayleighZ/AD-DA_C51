#include <reg52.h>

unsigned int count, value, timer1;
unsigned int DIR;
sbit PWM = P2^1;

void delay10ms(void)   //误差 0us
{
    unsigned char a, b, c;
    for (c = 1; c > 0; c--)
        for (b = 38; b > 0; b--)
            for (a = 130; a > 0; a--);
}

void timeConfig() {//定时器工作设置
    TMOD |= 0x10;
    TH1 = 0xff;
    TL1 = 0xff;
    ET1 = 1;
    EA = 1;
    TR1 = 1;
}

void main() {
    unsigned int totalTime = 100;
    timeConfig();
    while (1) {//不断的遍历检索，其速度要快于计数器计时
        //首先判断当前的档位是多少，之后给循环周期赋值
        if (P3 != ~0x00) {
            delay10ms();
            if (P3 != ~0x00) {
                switch (P3) {
                    case ~0x01: {//0001
                        totalTime = 100;
                        P0 = 0x5b;
                        break;
                    }
                    case ~0x02: {//0010
                        totalTime = 50;
                        P0 = 0x06;
                        break;
                    }
                    case ~0x04: {//0100
                        totalTime = 200;
                        P0 = 0x4f;
                        break;
                    }
                    case ~0x08: {
                        totalTime = 300;
                        P0 = 0x66;
                        break;
                    }
                }
            }
        }
        if (count > totalTime) {//这里的totalTime决定着value变化的快慢
            count = 0;//将count归零
            if (DIR == 1) {//根据DIR决定value的变化方向
                value++;
            }

            if (DIR == 0){
                value--;
            }
        }

        if (value == 1000) {//value变化到1000之后方向会发生改变
            DIR = 0;
        }
        if (value == 0){
            DIR = 1;
        }

        if (timer1 > 1000) {//timer1最大为1000，与value保持吻合
            timer1 = 0;
        }
        if (timer1 < value) {//根据timer1/value来确定占空比
            PWM = 1;
        } else {
            PWM = 0;
        }
    }
}

//在中断函数中完成对计时器的重新赋值和两个两个变量的累加
void time() interrupt 3{
TH1 = 0xff;
TL1 = 0xff;
timer1++;
count++;
}