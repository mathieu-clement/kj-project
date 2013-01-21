#ifndef FOLLOW_HAND_bla
#define FOLLOW_HAND_bla 1


#define fh_low_prox 500
#define fh_high_prox 3200
#define fh_low_prox_side 400
#define fh_high_prox_side 3500
#define fh_speed 10
#define fh_quick_rear_speed 20
#define fh_ground_missing_limit 2800


void follow_hand();

int1 fh_ground_is_missing(void);

#include "follow_hand.c"

#endif
