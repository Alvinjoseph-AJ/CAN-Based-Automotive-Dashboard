#ifndef MAIN_H
#define MAIN_H

//message id macro 
#define SPEED_MSG_ID 0x10
#define GEAR_MSG_ID 0x20
#define ENG_TEMP_MSG_ID 0x40
#define RPM_MSG_ID 0x30
#define INDICATOR_MSG_ID 0x50


//Function prototype
void intit_config();
void init_timer();
void __interrupt() isr(void);

#endif