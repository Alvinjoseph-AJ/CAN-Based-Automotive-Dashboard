/*
 * File:   main.c
 * Author: Alvin
 *
 * Created on 22 May, 2025, 1:49 PM
 */

//Header files
#include <xc.h>
#include <stdint.h>
#include "main.h"
#include "function.h"
#include "can.h"
#include "adc.h"

//Delay macro
#define _XTAL_FREQ 20000000

//Configuration function
void init_config() {
    init_adc();
    init_can();
    init_digital_keypad();
}

void main(void) {

    //configuration function call
    init_config();

    while (1) {
        //function call
        gearshift();
        //delay
        __delay_ms(5);
        
        //function call
        speed();
        //delay
        __delay_ms(5);
        
        //function call
        temp();
        //delay
        __delay_ms(5);
        
    }
    return;
}


