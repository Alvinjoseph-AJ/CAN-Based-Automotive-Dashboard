#include <xc.h>
#include <stdint.h>
#include "adc.h"
#include "function.h"
#include "can.h"

//speed function definition
void speed() {

    uint16_t speed = read_adc(CHANNEL4) / 10.33;
    can_transmit(SPEED_MSG_ID, &speed, sizeof (speed));
}

//Digital keypad configuration
void init_digital_keypad() {
    TRISC = TRISC | 0X0F;

}

//current gear function definition
unsigned char normalize_gear_pos(uint8_t gear_pos) {
    if (gear_pos == 0)
        return 'N';
    else if (gear_pos == 6)
        return 'R';
    else if (gear_pos == 7)
        return 'C';
    else
        return (gear_pos + 48);
}

//gear function definition
void gearshift() {
    unsigned char key;
    static int i = 0;
    key = read_switch(0);
    if (key == Switch1) {
        if (i < 6) {
            i++;
        }
    }
    if (key == Switch2) {
        if (i > 0) {
            i--;
        }
    }
    if (key == Switch3) {
        i = 7;
    }
    char gear = normalize_gear_pos(i);
    
    //Can Transmit function call
    can_transmit(GEAR_MSG_ID, &gear, sizeof (gear));
}

void temp() {
    int digit = read_adc(CHANNEL6);
    float volts = (float) digit * 0.004887;
    uint16_t temperature = ((volts * 1000) / 10);
    
    //Can Transmit function call
    can_transmit(ENG_TEMP_MSG_ID, &temperature, sizeof (temperature));
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