/**
 * @file
 * 
 * @brief The Multitasking program
 * 
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
 * @authors Mathieu Clement, Lucy Linder
 */

#ifndef AVOID_OBST_DD
#define AVOID_OBST_DD

#include "core.h"

#define MT_PROXIMITY  1200   //!< limit under which an obstacle is not avoided


//methods
void avoid_obstacles(void); //!< contains the main method (while loop) for the multitasking program


#include "avoid_obstacles.c"

#endif
