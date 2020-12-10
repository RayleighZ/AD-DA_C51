#include <reg52.h>

unsigned int count, value, timer1;
unsigned int DIR;
sbit PWM = P2^1;

void delay10ms(void)   //��� 0us
{
    unsigned char a, b, c;
    for (c = 1; c > 0; c--)
        for (b = 38; b > 0; b--)
            for (a = 130; a > 0; a--);
}

void timeConfig() {//��ʱ����������
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
    while (1) {//���ϵı������������ٶ�Ҫ���ڼ�������ʱ
        //�����жϵ�ǰ�ĵ�λ�Ƕ��٣�֮���ѭ�����ڸ�ֵ
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
        if (count > totalTime) {//�����totalTime������value�仯�Ŀ���
            count = 0;//��count����
            if (DIR == 1) {//����DIR����value�ı仯����
                value++;
            }

            if (DIR == 0){
                value--;
            }
        }

        if (value == 1000) {//value�仯��1000֮����ᷢ���ı�
            DIR = 0;
        }
        if (value == 0){
            DIR = 1;
        }

        if (timer1 > 1000) {//timer1���Ϊ1000����value�����Ǻ�
            timer1 = 0;
        }
        if (timer1 < value) {//����timer1/value��ȷ��ռ�ձ�
            PWM = 1;
        } else {
            PWM = 0;
        }
    }
}

//���жϺ�������ɶԼ�ʱ�������¸�ֵ�����������������ۼ�
void time() interrupt 3{
TH1 = 0xff;
TL1 = 0xff;
timer1++;
count++;
}