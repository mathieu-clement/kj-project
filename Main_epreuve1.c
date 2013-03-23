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
#define left_on_black() left_proximity < threshold_left
#define right_proximity KJunior_get_proximity(GROUNDRIGHT)
#define right_on_black() right_proximity < threshold_right

int16 threshold_left = 1000;
int16 threshold_right = 1000;

void main(void)
{ 
   // Initialization
   KJunior_init () ;

   while(1)
   {
      if(KJunior_get_tv_data() == 60 ||
         KJunior_get_tv_data() == TV_CH_PLUS ||
         KJunior_get_tv_data() == TV_CH_MINUS ||
         KJunior_get_tv_data() == TV_VOL_PLUS ||
         KJunior_get_tv_data() == TV_VOL_MINUS) {
         fprintf(USB, 
            "Left: %4ld, Right: %4ld, Threshold (Left): %4ld, Threshold (Right): %4ld\r\n",
            left_proximity, right_proximity, threshold_left, threshold_right);
         
         if(KJunior_get_tv_data() == TV_CH_PLUS) {
            threshold_left += 50;
            TV_DATA = 60;
         } else if(KJunior_get_tv_data() == TV_CH_MINUS) {
            threshold_left -= 50;
            TV_DATA = 60;
         } else if(KJunior_get_tv_data() == TV_VOL_PLUS) {
            threshold_right += 50;
            TV_DATA = 60;
         } else if (KJunior_get_tv_data() == TV_VOL_MINUS) {
            threshold_right -= 50;
            TV_DATA = 60;
         }
         
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

