//#include "KJunior.h"
//#include "simple_beep.h"
//#include "Basic_functions.h"

/*******************************************************************************
 *
 * Multitasking 
 *--------------
 * This program makes the robot :
 *   - play a "police" sound
 *   - light on and off the leds in a "circular" way
 *   - avoid obstacles : on the sides, forward, backward
 *   - the robot will also go backward for a while if a missing ground is detected
 *
 * purpose : to demonstrate how we can simulate multitasking with sequential 
 * instructions. We got inspired by the processors, which often simply use 
 * quick context switch between applications to simulate multithreading.
 *
 *
 * authors : Mathieu Clement, Lucy Linder
 * version : 0.1
 * date : 28.12.2012
 *
 *******************************************************************************/

#ifndef MULTITASKING_bla
#define MULTITASKING_bla 1

#define MT_NORMAL_SPEED 5
#define MT_GROUND_MISSING_LIMIT 2800
#define MT_PROXIMITY  1200   //limit under which an obstacle is not avoided
#define MT_BEEP_DELTA 500    //milliseconds between each beep
#define MT_LED_DELTA  100     //milliseconds between led switches
#define MT_GROUND_MISSING_BACKWARDS_DELTA 500 //the time during which to go backwards when a "missing ground" is detected, in ms
#define MT_GROUND_MISSING_ROTATE_DELTA    2000 //the time during which to turn after a "backward ground missing avoidance"


//variables
int1  mt_should_beep_A=0;  //boolean, to know which sound (A or B) is the next to play
int8  mt_increment = 1; //used to switch between leds - varies between 1 and -1
int8  mt_led_control = 0; //used to keep track of which is the current lit led
int1  mt_be_silent_please = 0; //to run the multitasking method without the sirens

//methods
void mt_set_led(int nbr, int state); //lights on or off the specified led (state : 0 = OFF, 1 = ON )
void mt_led_incr(); //increment or decrement the led counter (the leds are lit in the sequence 0 - 1 - 2 -... - 4 - 3 ... - 0 - 1 etc)
int1 mt_ground_is_missing(); //returns true if the ground captor does not detect the ground
void mt_turn_left(); //turns left
void mt_turn_right(); //turns right

void multitasking(); //contains the main method (while loop) for the multitasking program


#include "multitasking.c"

#endif
