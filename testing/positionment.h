#ifndef POSIT_DD
#define POSIT_DD

#define LINE_TIME_THRESHOLD 200
#include "core.h"
#include "../basic_functions.h"
#include "avoid_obstacles.h"

int1 do_positioning();
signed int8 do_rotation_based_on_line();
void do_rotation_back(int1);

void rotate_90degree_left();
void rotate_90degree_right();
void avoid_black_lines();
#include "positionment.c"

#endif
