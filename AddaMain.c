#include <reg52.h>

unsigned int count, value, timer1;
bit DIR;
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

int getKeyValue() {
    if (P3 != ~0x00) {
        delay10ms();
        if (P3 != ~0x00) {
            switch (P3) {
                case ~0x01: {//0001
                    return 0;
                }
                case ~0x02: {//0010
                    return 1;
                }
                case ~0x04: {//0100
                    return 2;
                }
                case ~0x08: {
                    return 3;
                }
            }
        }
    }
}

void main() {
    unsigned int totalTime = 100;
    timeConfig();
    while (count) {//���ϵı������������ٶ�Ҫ���ڼ�������ʱ
        //�����жϵ�ǰ�ĵ�λ�Ƕ��٣�֮���ѭ�����ڸ�ֵ
        switch (getKeyValue()) {
            case 0: {
                totalTime = 100;
                break;
            }
            case 1: {
                totalTime = 200;
                break;
            }
            case 2: {
                totalTime = 300;
                break;
            }
            case 3: {
                totalTime = 400;
            }
        }
        if (count > totalTime) {//�����totalTime������value�仯�Ŀ���
            count = 0;//��count����
            if (1 == DIR){//����DIR����value�ı仯����
                value++;
            } else {
                value--;
            }
        }

        if (value == 1000){//value�仯��1000֮����ᷢ���ı�
            DIR = 0;
        } else {
            DIR = 1;
        }

        if (timer1 > 1000){//timer1���Ϊ1000����value�����Ǻ�
            timer1 = 0;
        }
        if (timer1 < value){//����timer1/value��ȷ��ռ�ձ�
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