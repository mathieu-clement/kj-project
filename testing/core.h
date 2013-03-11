#ifndef CORE_DD
#define CORE_DD

#define BARCODE STATE 12 //detect barcodes
#define POSITION_STATE 23 //try to position correctly for the line detection
#define NORMAL_STATE 34 //nothing special
#define DETECT_LINE_STATE 56 // black on both
#define HIGH_SPEED 10
#define SPEED 5


#define BC_ON_LEFT 1
#define BC_ON_RIGHT 0


#define stop() KJunior_set_speed(0, 0); 
#define turn_left() KJunior_set_speed(0, SPEED); 
#define turn_right() KJunior_set_speed(SPEED, 0); 
#define move_forward() KJunior_set_speed(SPEED, SPEED);
#define move_backward() KJunior_set_speed(-SPEED, -SPEED);


extern unsigned int16 bw_threshold_left, bw_threshold_right;

// Returns true (1) if one of the ground front sensors is on black.
int1 black_detected();
int1 black_on_both();
int1 black_on_left();
int1 black_on_right();

void rotate_right(int8 s);
void rotate_left(int8 s);
void debug();


#include "core.c"
#endif
