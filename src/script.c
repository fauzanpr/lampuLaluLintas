/*******************
AVR Core Clock frequency: 16.000000 MHz
Memory model            : Small
External RAM size       : 0
Data Stack size         : 256
*******************/

#include <mega16.h>
#include <delay.h>

#define LED1 PORTA.0 // hijau
#define LED2 PORTA.1 // kuning
#define LED3 PORTA.2 // merah

unsigned int seven_seg[] = {0x3F, 0x06, 0x5b, 0x4f, 0x66, 0x6e, 0x7e, 0x07, 0x7f, 0x6f};
int i, j;
int isMerah;

void turnMerah() {
    LED1 = 0; 
    LED2 = 0;
    LED3 = 1; 
}

void turnKuning() {
    if (isMerah == 1) {
        LED1 = 0;
        LED2 = 1;
        LED3 = 0;   
    } else {
        LED1 = 0;
        LED2 = 1;
        LED3 = 0;
    }
}

void turnHijau() {
    LED2 = 0;
    LED1 = 1;
    LED3 = 0;
}

void counterMerah() {
    for (i = 2; i >= 0; i--) {
        for (j = 9; j >= 0; j--) {
            if (i == 0 && j < 5 && j >= 0) {
                turnKuning();
            } else {
                turnMerah();
            }
            PORTB = seven_seg[i];
            PORTC = seven_seg[j];
            delay_ms(1000);
        }
    }
    isMerah = 0;
}

void counterHijau() {
    for (i = 1; i >= 0; i--) {
        if (i == 1) {
            for (j = 5; j >= 0; j--) {
                PORTB = seven_seg[i];
                PORTC = seven_seg[j];
                turnHijau();
                delay_ms(1000);
            }        
        } else {
            for (j = 9; j >= 0; j--) {
                PORTB = seven_seg[i];
                PORTC = seven_seg[j];
                if (j >= 6) {
                    turnHijau();
                } else {
                    turnKuning();    
                }
                delay_ms(1000);
            }
        }
    }
    isMerah = 1; 
}

void main(void) {

    // declare
    DDRA = 0xff;
    DDRB = 0xff;
    DDRC = 0xff;
    PORTA = 0b00000000;
    PORTB = seven_seg[0];
    PORTC = seven_seg[0];
    isMerah = 1;

    while (1) { 
        if (isMerah == 1) {
            counterMerah();    
        } else {
            counterHijau();
        } 
    }
}