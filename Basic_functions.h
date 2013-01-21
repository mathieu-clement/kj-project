#ifndef BASIC_FUNC
#define BASIC_FUNC 1

#define DIAMETER 100
#define PI 3.141592653
#define PERIM (DIAMETER * PI)

 
#define SECONDS_LOOP_CONTROL 46
#define MS_LOOP_CONTROL 100

int16 abs(int16);
void sleep_s(unsigned int32);
void sleep_ms(unsigned int32);
void rotate_no_move(unsigned int32 angle, int speed);
unsigned int get_speed_in_mms(int32 speed);



#include "basic_functions.c"

#endif
