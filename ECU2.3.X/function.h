#ifndef FUNCTION_H
#define FUNCTION_H

#define _XTAL_FREQ 20000000

#define Switch1 0X0E
#define Switch2 0X0D
#define Switch3 0X0B
#define Switch4 0X07
#define All_released 0X0F
#define RPM_MSG_ID 0x30
#define INDICATOR_MSG_ID 0x50

void init_led();
void rpm();
void indicator();
char read_switch();
void init_digital_keypad();
void init_timer();
void __interrupt() isr(void);
#endif