#include "KJunior.h"

#include "simple_beep.h"
#include "Basic_functions.h"

//--------------------------------------------------------------------------------//
//- Main program                                                                 -//
//--------------------------------------------------------------------------------//
#separate


void turn_left() { KJunior_set_speed(-5, 5); }
void turn_right() { KJunior_set_speed(5, -5); }

int1 should_beep_A=0;
int16 beep_delta = 500;
int16 led_delta = 100;
int16 ground_missing_backwards_delta = 500;
int16 ground_missing_rotate_delta = 2000;
int8 increment = 1, led_control = 0;

void set_led(int nbr, int state){
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
}

void led_incr(){
   set_led(led_control, 0);
   led_control += increment;
   set_led(led_control, 1);
   
   if(led_control == 0 || led_control == 3) increment = -increment;
}


int1 ground_is_missing()
{
   int16 lim = 2800;
   return KJunior_get_proximity(GROUNDFRONTLEFT) < lim || KJunior_get_proximity (GROUNDFRONTLEFT) < lim;
}

void main(void)
{
 // Initialization
 KJunior_init();
 
 // Raw input from TV remote control
 unsigned char remote_control_input_data = -1;
 
 //*******************************Main loop***************************************//
 
 int16 proximity = 1200;
 
 int32 beep_last_time = KJunior_get_time();
 int32 led_last_time = beep_last_time;
 int32 ground_missing_timer = 0;
 int8 ground_missing_state = 0;
 
 
 While (1)
 { 
   if((KJunior_get_time() - beep_last_time) > beep_delta) {
      should_beep_A = !should_beep_A;
      if(should_beep_A) { KJunior_beep(A_3); } else { KJunior_beep(E_3); }
      beep_last_time = KJunior_get_time();
   }
   
   if((KJunior_get_time() - led_last_time) > led_delta) {
      led_incr();
      led_last_time = KJunior_get_time();
   }
 
   if(ground_is_missing()) 
   {   
         KJunior_set_speed(-20, -20);  
         ground_missing_state = 1;
         ground_missing_timer = KJunior_get_time();
   }
   
   if (ground_missing_state == 1) {
      if(KJunior_get_time() - ground_missing_timer > ground_missing_backwards_delta){
         ground_missing_state = 2;
         ground_missing_timer = KJunior_get_time();
         turn_left();
      }
      
      CONTINUE;
   }
   
   if(ground_missing_state == 2){
      if(KJunior_get_time() - ground_missing_timer <= ground_missing_rotate_delta){
         CONTINUE;
      }
      ground_missing_state = 0;
   }
   
   if(KJunior_get_proximity(FRONTLEFT) > proximity && KJunior_get_proximity(FRONTRIGHT)) {
      KJunior_set_speed(0, 0);
   } else if(KJunior_get_proximity(LEFT) > proximity || KJunior_get_proximity(FRONTLEFT) > proximity) {
      turn_right();
   } else if (KJunior_get_proximity(RIGHT) > proximity || KJunior_get_proximity(FRONTRIGHT) > proximity) {
      turn_left();
   } else if(KJunior_get_proximity(FRONT) > proximity) {
      if(KJunior_get_proximity(LEFT) > KJunior_get_proximity(RIGHT)) {
         turn_right();
      } else {
         turn_left();
      }
   } else {
      KJunior_set_speed(5, 5);
   }
   
   sleep_ms(100);
   
   
} // end while

} // end main
