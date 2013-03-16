#ifndef CORE_DD
#define CORE_DD


#define HIGH_SPEED 10
#define SPEED 5

#define BC_ON_LEFT 1
#define BC_ON_RIGHT 0

#define stop() KJunior_set_speed(0, 0); 

enum STATE  /* Declares an enumeration data type called BOOLEAN */
{
    normal_state,     /*  */
    position_state,
    detect_line_state,
    detect_barcode_state 
      
};

extern enum STATE curr_state;
extern unsigned int16 bw_threshold_left, bw_threshold_right;

int1 black_detected();
int1 black_on_both();
int1 black_on_left();
int1 black_on_right();

void turn_right(); 
void move_forward();
void move_backward();

void rotate_right(int8 s);
void rotate_left(int8 s);
void debug();


#include "core.c"
#endif
