 /**
 * @file
 * 
 * @brief A melting pot of basic functions
 *
 * See the basic_function.h file for more informations.
 *
 *@author Lucy Linder, Mathieu Clement, Yves Kalberer
 *@version 0.1
 *@date 11.11.2012
 */
 
 
/**
 * This method is an alternative to the KJunior_delay_s
 * which is badly implemented and highly imprecise.
 * the time to hold is expressed in seconds.
 */
void sleep_s(unsigned int32 seconds)
{
    unsigned int32 t1 = KJunior_get_time();
    while( (KJunior_get_time() - t1) < seconds);
}

/**
 * This method is an alternative to the KJunior_delay_ms
 * which is badly implemented and highly imprecise.
 * the time to hold is expressed in milliseconds.
 */
void sleep_ms(unsigned int32 ms)
{
    unsigned int32 t1 = KJunior_get_time();
    while( (KJunior_get_time() - t1) < ms);
}


/**
 * This method was a try in order to make the robot rotate on itself the specified angle 
 * according to its speed. The problem is that the actual speed of the 
 * robot is not precise, so even if the calculation is right, it is impossible
 * to really make it stop where we want.
 */
void rotate_no_move(unsigned int32 angle, int speed)
{
   unsigned int speed_ms = get_speed_in_mms(speed);
   fprintf(USB, "speed ms : %ud \r\n", speed_ms);
   unsigned int32 ms = (unsigned int32) (PERIM * 1000 / speed_ms);
   fprintf(USB, "ms : %Ld \r\n", ms);
   KJunior_set_speed(speed, -speed);
   sleep_ms(ms);
   KJunior_set_speed(0, 0);
   
}

/**
 * returns the speed in meter/milliseconds according to the 
 * formula found in the KJunior documentation.
 */
unsigned int get_speed_in_mms(int32 speed)
{
   return (unsigned int)((speed * 70.0 / 20.0) + 30);
}


