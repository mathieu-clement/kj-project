//!< used in order to make the robot beep 
/*******************************************************************************
 * @file
 * 
 * @brief The Multitasking program
 * See the multitasking.h file for more informations...
 *
 *******************************************************************************/


/*********************** main method ******************************************/
void avoid_obstacles()
{

 
 
 While (1)
 { 

   //if obstacles on the right and on the left, stops
   if( KJunior_get_proximity(FRONTLEFT) > MT_PROXIMITY && KJunior_get_proximity(FRONTRIGHT) > MT_PROXIMITY ) 
   {
      KJunior_set_speed(0, 0);   
   }
   //if obstacle to the left, turns right
   else if( KJunior_get_proximity(LEFT) > MT_PROXIMITY || KJunior_get_proximity(FRONTLEFT) > MT_PROXIMITY )
   {
      turn_right();
   
   }
   //if obstacle to the right, turns left
   else if( KJunior_get_proximity(RIGHT) > MT_PROXIMITY || KJunior_get_proximity(FRONTRIGHT) > MT_PROXIMITY ) 
   {
     turn_left();
   }
   //if obstacle to the front, checks the sides proximity to choose where to go
   else if( KJunior_get_proximity(FRONT) > MT_PROXIMITY ) 
   {
      if( KJunior_get_proximity(LEFT) > KJunior_get_proximity(RIGHT) ) 
      {
        turn_right();
      }
      else
      {
         turn_left();
      }
   }
   //else, go forward
   else
   {
      KJunior_set_speed( HIGH_SPEED, HIGH_SPEED );
   }
   
   //sleeps a while to avoid changing rotor speed to quickly
   sleep_ms(100);
      
 }// end while

}// end multitasking
