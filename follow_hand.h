/**
 * @file
 * 
 * @brief The Follow Hand program
 *
 * This program makes the robot follow a hand or an object. IF the object is detected
 * by the front captor, the robot will move forward until the object either disappear or come too close.
 * If the robot detects that the floor is missing, it will hurriedly move backward and stop.
 * If the object is detected to the left or to the right of the robot, the latter will rotate
 * in its direction.
 * The robot will finally go backward and follow the hand IF it is detected by the robot's
 * rear captor.
 *
 * Note : there is plenty of room FOR improvement. For example, the robot is not really fast 
 * nor smooth, and sometimes the hand is not correctly detected. 
 * When an object is detected by the front and sides captors, the robot should normally
 * either move forward or stop. but it will aslo sometimes rotate left to right repeatedly.
 * 
 * @version : 1
 * @author : Lucy Linder
 * @date : 02.12.2012
 *
 **/
 
 
#ifndef FOLLOW_HAND_bla
#define FOLLOW_HAND_bla 


#define fh_low_prox 500 //!< limit under which the hand is not followed
#define fh_high_prox 3200 //!< limit up to which the hand is followed
#define fh_low_prox_side 400 //!< limit under which the hand is not followed [on the sides]
#define fh_high_prox_side 3500 //!< limit up to which the hand is followed [on the sides]
#define fh_speed 10 //!< normal speed
#define fh_quick_rear_speed 20 //!< rear speed
#define fh_ground_missing_limit 2800 //!< limit under which we interpret the ground as missing


void follow_hand(); //!< contains the main method
int1 fh_ground_is_missing(void); //!< returns true if the ground is missing

#include "follow_hand.c"

#endif
