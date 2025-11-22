/*
 * File:   main.c
 * Author: Alvin
 *
 * Created on 8 June, 2025, 11:16 AM
 */

//Header files
#include <xc.h>
#include "main.h"
#include <stdint.h>
#include "can.h"
#include "clcd.h"


//Led and timer configuration
void init_config() {
    TRISB0 = 0;
    TRISB1 = 0;
    TRISB4 = 0;
    TRISB5 = 0;
    TRISB6 = 0;
    TRISB7 = 0;
    PORTB = 0X00;
    
    //Configuration
    init_clcd();
    init_can();
    init_timer();

}

//used for delay
int sec = 0;

void main(void) {

    //configuration function call
    init_config();
    
    //Variable declaration
    uint16_t msg_id;
    uint8_t data, len;

    clcd_print("SP G TM RPM  IN", LINE1(0));

    while (1) {
        
        //can receive function
        can_receive(&msg_id, &data, &len);
        
        //condition checking based on message id
        if (msg_id == GEAR_MSG_ID) {
            clcd_putch(data, LINE2(3));
        }
        if (msg_id == SPEED_MSG_ID) {
            clcd_putch(data / 10 + 48, LINE2(0));
            clcd_putch(data % 10 + 48, LINE2(1));
        }
        if (msg_id == ENG_TEMP_MSG_ID) {
            clcd_putch(data / 10 + 48, LINE2(5));
            clcd_putch(data % 10 + 48, LINE2(6));
        }
        if (msg_id == RPM_MSG_ID) {
            clcd_putch(((data * 60) / 1000) + '0', LINE2(8));
            clcd_putch((((data * 60) / 100) % 10) + '0', LINE2(9));
            clcd_putch((((data * 60) / 10) % 10) + '0', LINE2(10));
            clcd_putch(((data * 60) % 10) + '0', LINE2(11));
        }
        if (msg_id == INDICATOR_MSG_ID) {
            
            //data = 1, Left indicator
            if (data == 1) {
                clcd_print("<--", LINE2(13));
                RB6 = 0;
                RB7 = 0;
                if (sec >= 1) {
                    RB0 = !RB0;
                    RB1 = !RB1;
                    sec = 0;
                }
            }
            
            //data = 0, Indicator off
            if (data == 0) {
                clcd_print("OFF", LINE2(13));
                RB0 = 0;
                RB1 = 0;
                RB6 = 0;
                RB7 = 0;
            }
            
            //data = 2, Right indicator
            if (data == 2) {
                clcd_print("-->", LINE2(13));
                RB0 = 0;
                RB1 = 0;
                if (sec >= 1) {
                    RB6 = !RB6;
                    RB7 = !RB7;
                    sec = 0;
                }
            }

        }
    }
}

//Timer configuration
void init_timer() {

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