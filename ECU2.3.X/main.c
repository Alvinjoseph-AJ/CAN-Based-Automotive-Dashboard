/*
 * File:   main.c
 * Author: Alvin
 *
 * Created on 27 May, 2025, 12:22 PM
 */

//Header files
#include <xc.h>
#include "function.h"
#include <stdint.h>
#include "adc.h"
#include "main.h"
#include "can.h"

//Delay macro
#define _XTAL_FREQ 20000000

//Configuration function
void intit_config() {
    init_adc();
    init_can();
    init_led();
    init_digital_keypad();
    init_timer();
}



void main(void) {

    //configuration function call
    intit_config();


    while (1) {

        //function call
        rpm();
        //delay
        __delay_us(5);
        
        //function call
        indicator();
        //delay
        __delay_us(5);
        
    }
    return;
}


