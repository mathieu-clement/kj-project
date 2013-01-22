//!< used in order to make the robot beep 
#include "simple_beep.h"
/*******************************************************************************
 * @file
 * 
 * @brief The Multitasking program
 * See the multitasking.h file for more informations...
 *
 *******************************************************************************/
/**
 * simple method to make the robot turn left at normal speed
 */
void mt_turn_left()  { KJunior_set_speed( -MT_NORMAL_SPEED,  MT_NORMAL_SPEED ); }

/**
 * simple method to make the robot turn right at normal speed 
 */
void mt_turn_right() { KJunior_set_speed(  MT_NORMAL_SPEED, -MT_NORMAL_SPEED ); }


/**
 * Increments the led_control variable in the following sequence :
 *    0 - 1 - 2 - 3 - 4 - 3 - 2 - 1 - 0 - 1 - ...
 * Uses the "increment" variable to do a +1 or a -1 operation.
 **/
void mt_led_incr()
{
   mt_set_led( mt_led_control, 0 ); //turns of the current led
   mt_led_control += mt_increment; 
   mt_set_led( mt_led_control, 1 ); //turns on the next led 
   
   if( mt_led_control == 0 || mt_led_control == 3) 
      mt_increment = -mt_increment;
      
}//end led_incr


/**
 * lights on or off the specified led.
 * nbr : led 
 *   0 = left led
 *   1 = front left led
 *   2 = front right led
 *   3 = right led
 * control : 1 = ON, 0 = OFF
 **/
void mt_set_led(int nbr, int state){

   switch(nbr){
      case 0:
         KJunior_led_left(state);
         return;
      case 1:
         KJunior_led_frontleft(state);
         return;
      case 2:
         KJunior_led_frontright(state);
         return;
      case 3:
         KJunior_led_right(state);
         return;
   }
}//end set_led



/**
 * returns true (1) if the ground is not detected by the ground front captors
 *
 **/
int1 mt_ground_is_missing()
{
   return KJunior_get_proximity( GROUNDFRONTLEFT  ) < MT_GROUND_MISSING_LIMIT || 
          KJunior_get_proximity( GROUNDFRONTRIGHT ) < MT_GROUND_MISSING_LIMIT;
}


/*********************** main method ******************************************/
void multitasking()
{
 int32 beep_last_time = KJunior_get_time();
 int32 led_last_time =  beep_last_time;
 int32 ground_missing_timer = 0;
 int8  ground_missing_state = 0;
 
 
 While (1)
 { 
   //beeps
   if( !mt_be_silent_please )
   {
      if( (KJunior_get_time() - beep_last_time) > MT_BEEP_DELTA ) 
      {
     
         mt_should_beep_A = !mt_should_beep_A;
         KJunior_beep( mt_should_beep_A ? A_3 : E_3 ); 
         beep_last_time = KJunior_get_time();
      }
   }
   
   
   //leds
   if((KJunior_get_time() - led_last_time) > MT_LED_DELTA ) 
   {
      mt_led_incr();
      led_last_time = KJunior_get_time();
   }
 
   //checks that the floor is still here
   if( mt_ground_is_missing() ) 
   {   
         KJunior_set_speed(-20, -20);  
         ground_missing_state = 1;
         ground_missing_timer = KJunior_get_time();
   }
   
   //if the robot is going backwards to avoid a missing ground
   if ( ground_missing_state == 1 ) 
   {
   
      if( KJunior_get_time() - ground_missing_timer > MT_GROUND_MISSING_BACKWARDS_DELTA )
      {
         //if the robot moved backwards enough, go to step 2 (rotate)
         ground_missing_state = 2;
         ground_missing_timer = KJunior_get_time();
         mt_turn_left();
      }
      
      CONTINUE;
   }
   
   //if the robot is turing in order to avoid a missing ground
   if( ground_missing_state == 2 )
   {
   
      if( KJunior_get_time() - ground_missing_timer <= MT_GROUND_MISSING_ROTATE_DELTA )
      {
         CONTINUE;
      }
      
      ground_missing_state = 0;
   }
   
   
   //if obstacles on the right and on the left, stops
   if( KJunior_get_proximity(FRONTLEFT) > MT_PROXIMITY && KJunior_get_proximity(FRONTRIGHT) > MT_PROXIMITY ) 
   {
      KJunior_set_speed(0, 0);   
   }
   //if obstacle to the left, turns right
   else if( KJunior_get_proximity(LEFT) > MT_PROXIMITY || KJunior_get_proximity(FRONTLEFT) > MT_PROXIMITY )
   {
      mt_turn_right();
   
   }
   //if obstacle to the right, turns left
   else if( KJunior_get_proximity(RIGHT) > MT_PROXIMITY || KJunior_get_proximity(FRONTRIGHT) > MT_PROXIMITY ) 
   {
      mt_turn_left();
   }
   //if obstacle to the front, checks the sides proximity to choose where to go
   else if( KJunior_get_proximity(FRONT) > MT_PROXIMITY ) 
   {
      if( KJunior_get_proximity(LEFT) > KJunior_get_proximity(RIGHT) ) 
      {
         mt_turn_right();
      }
      else
      {
         mt_turn_left();
      }
   }
   //else, go forward
   else
   {
      KJunior_set_speed( MT_NORMAL_SPEED, MT_NORMAL_SPEED );
   }
   
   //sleeps a while to avoid changing rotor speed to quickly
   sleep_ms(100);
      
 }// end while

}// end multitasking
