#ifndef FUNCTION_H
#define FUNCTION_H


#define Switch1 0X0E
#define Switch2 0X0D
#define Switch3 0X0B
#define Switch4 0X07
#define All_released 0X0F
#define SPEED_MSG_ID 0x10
#define GEAR_MSG_ID 0x20
#define ENG_TEMP_MSG_ID 0x40

void speed();
void init_digital_keypad();
unsigned char normalize_gear_pos(uint8_t gear_pos);
void gearshift();
void temp();
char read_switch(int detection);

#endif