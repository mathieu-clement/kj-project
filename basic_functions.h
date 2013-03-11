/**
 * @file
 * 
 * @brief A melting pot of basic functions
 *
 * This file holds some pretty basicu functions, for example sleep or rotate functions.
 * Note that it is not complete at the time...
 *
 *@author Lucy Linder, Mathieu Clement, Yves Kalberer
 *@version 0.1
 *@date 11.11.2012
 *
 */

#ifndef BASIC_FUNC
#define BASIC_FUNC 1

#define DIAMETER 100 //!< diameter of the robot, wheel to wheel
#define PI 3.141592653
#define PERIM (DIAMETER * PI) //!< perimeter of the robot, wheel to wheel


void sleep_s(unsigned int32); //!< alternative to the KJunior_delay_s function
void sleep_ms(unsigned int32); //!< alternative to the KJunior_delay_ms function
void rotate_no_move(unsigned int32 angle, int); //!< a try to make the robot rotate on itself at the specified angle
unsigned int get_speed_in_mms(int32); //!< returns the speed in m/ms according to the formula found in the KJunior documentation

#include "basic_functions.c"

#endif
