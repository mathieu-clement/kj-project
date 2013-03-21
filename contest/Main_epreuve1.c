#include "KJunior.h"

#include "basic_functions.h"
#include "tv_remote_utils.h"

#define EXT_SPEED 10
#define INT_SPEED 15
#define FORWARD_SPEED 20
#define turn_left() KJunior_set_speed(-INT_SPEED, EXT_SPEED)
#define turn_right() KJunior_set_speed(EXT_SPEED, -INT_SPEED)
#define move_forward() KJunior_set_speed(FORWARD_SPEED, FORWARD_SPEED)

#define left_proximity KJunior_get_proximity(GROUNDLEFT)
#define left_on_black() left_proximity < threshold
#define right_proximity KJunior_get_proximity(GROUNDRIGHT)
#define right_on_black() right_proximity < threshold

int16 threshold = 1000;

void main(void)
{ 
   // Initialization
   KJunior_init () ;

   while(1)
   {
      if(get_tv_remote_pad_number() == 1) {
         fprintf(USB, "Left: %4ld, Right: %4ld, Threshold (L+R): %4ld\r\n", left_proximity, right_proximity, threshold);
      } else if (get_tv_remote_pad_number() == 2) {
   
         if(left_on_black()) {
            turn_left(); sleep_ms(250);
         } else if (right_on_black()) {
            turn_right(); sleep_ms(250);
         } else {
            move_forward();
         } // end if black
         
      } // end if pad number
   
      sleep_ms(100);
   } // end while
   
} // end main

