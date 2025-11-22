//Header file
#include <xc.h>
#include "function.h"
#include <stdint.h>
#include "adc.h"
#include "can.h"

//Led configuration
void init_led() {
    TRISB0 = 0;
    TRISB1 = 0;
    TRISB6 = 0;
    TRISB7 = 0;
    PORTB = 0x00;
}

//Digital keypad configuration
void init_digital_keypad() {
    TRISC = TRISC | 0X0F;

}
int sec = 0;

//RPM function definition
void rpm() {

    //    uint16_t adc_value = read_adc(CHANNEL4);
    //    uint16_t rpm = (adc_value * 6000UL) / 1023;
    uint8_t rpm = (read_adc(CHANNEL4) / 10.23);
    
    //Can Transmit function call
    can_transmit(RPM_MSG_ID, &rpm, sizeof (rpm));
}

//Indicator function definition
void indicator() {

    char key = read_switch(0);
    static int flag = 0;
    static int ind = 0;

    if (key == Switch1) {
        flag = 1;
        ind = 1;
    } else if (key == Switch2) {
        flag = 2;
        ind = 0;
    } else if (key == Switch3) {
        flag = 3;
        ind = 2;
    }

    if (flag == 1) {

        if (sec >= 1) {
            RB0 = !RB0;
            RB1 = !RB1;
            sec = 0;
        }


        RB6 = 0;
        RB7 = 0;


    }
    if (flag == 2) {

        RB0 = 0;
        RB1 = 0;
        RB6 = 0;
        RB7 = 0;

    }
    if (flag == 3) {

        if (sec >= 1) {
            RB6 = !RB6;
            RB7 = !RB7;
            sec = 0;
        }
        RB0 = 0;
        RB1 = 0;
    }
    
    //Can Transmit function call
    can_transmit(INDICATOR_MSG_ID, &ind, sizeof (ind));
}

//Function definition for read switch in digital keypad
char read_switch(int detection) {
    static int flag = 0;
    if (detection == 0) {
        if ((PORTC & 0x0F) != All_released && flag == 0) {
            flag = 1;
            return PORTC & 0X0F;
        } else if ((PORTC & 0X0F) == All_released) {
            flag = 0;
        }
    } else {
        return PORTC & 0X0F;
    }
    return All_released;
}


//Timer configuration
void init_timer() {
    TRISB0 = 0;
    TRISB1 = 0;
    TRISB6 = 0;
    TRISB7 = 0;

    PORTB = 0X00;
    GIE = 1;
    PEIE = 1;
    TMR0IE = 1;
    TMR0IF = 0;
    TMR0ON = 1;
    T08BIT = 1;
    T0CS = 0;
    PSA = 1;
    TMR0 = 6;
}

unsigned int count = 0;

//Interrupt definition
void __interrupt() isr(void) {
    if (TMR0IF == 1) {
        count++;
        TMR0 = TMR0 + 8;
        if (count == 20000) {
            sec++;
            count = 0;
        }
        TMR0IF = 0;
    }
}

