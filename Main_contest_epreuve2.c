#include "KJunior.h"
#include "HemLinCam.h"

#include "basic_functions.h"
#include "simple_camera_reading.h"
#include "tv_remote_utils.h"
//#include "contest/contest_barcode.h"
#include "contest/contest_beep.h"
//#include "binary_led_transcoder.h"
#include "simple_beep.h"

void main(void)
{ 
   // Initialization
   KJunior_init () ;
   
   int1 light_on = 0;
   
   // Declared here to save some memory but may not be needed
   int32 pixels_total;
   int8 pixels_average;
   int8 i;
   char* pixels;
   
   int8 music[] = {
      MUTE, D_2, D_2, D_2,
      G_2, HOLD, G_2, HOLD, A_2, HOLD, A_2, HOLD,
      D_3, HOLD, HOLD, B_2, G_2, G_2, B_2, G_2,
      E_2, HOLD, C_3, HOLD, HOLD, HOLD, A_2, F_SHARP_2,
      G_2, HOLD, HOLD, HOLD, MUTE, HOLD, G_2, A_2,
      B_2, HOLD, B_2, HOLD, B_2, HOLD, C_3, B_2,
      B_2, A_2, A_2, HOLD, MUTE, HOLD, A_2, B_2,
      C_3, HOLD, C_3, HOLD, C_3, HOLD, D_3, C_3,
      B_2, HOLD, HOLD, HOLD, MUTE, HOLD, D_3, D_3,
      D_3, HOLD, B_2, G_2, D_3, HOLD, B_2, G_2,
      D_2, HOLD, HOLD, HOLD
   };
   int8 current_note = 0;
   int8 number_of_notes = sizeof(music)/sizeof(music[0]);
   if(number_of_notes % 2 != 0) {
      printf(USB, "ERROR!!! Number of notes must be odd!\r\n");
   }
   
   int8 threshold = 60;
   
   int32 light_delta = 0;
   int32 last_time = KJunior_get_time();
   
   
   fprintf(USB, "I'm on!\r\n");
   
   // Main loop
   while (1)
   {
         if(KJunior_get_tv_data() == TV_CH_MINUS) {
            threshold -= 25;
            fprintf(USB, "New threshold: %d\r\n", threshold);
         }
         if(KJunior_get_tv_data() == TV_CH_PLUS) {
            threshold += 25;
            fprintf(USB, "New threshold: %d\r\n", threshold);
         }
   
         HemLinCam_Read_Pixels () ;
         cr_make_single_pixels_array(pixels);
         
         // Compute total
         pixels_total = 0;
         for(i=0; i < 102; i++) {
            pixels_total += pixels[i];
         }
         // Compute average
         pixels_average = pixels_total / 102.0;
         
         fprintf(USB, "Average: %d, threshold: %d\r\n", pixels_average, threshold);
      
        if(pixels_average > threshold) {
            if(!light_on) {
               // If light is now on but previously wasn't, then:
               light_on = 1;
               
               light_delta = KJunior_get_time() - last_time;
               fprintf(USB, "Light delta: %ld ms\r\n", light_delta);
               last_time = KJunior_get_time();
               
               if(current_note == number_of_notes) {
                  current_note = 0;
               }
               
               if(music[current_note] != HOLD) {
                  KJunior_beep(MUTE); sleep_ms(10);
                  KJunior_beep(music[current_note]);
               }
               current_note++;
               sleep_ms(light_delta/2.0 - 20);
               
               if(music[current_note] != HOLD) {
                  KJunior_beep(MUTE); sleep_ms(10);
                  KJunior_beep(music[current_note]);
               }
               current_note++;
            }
         } else {
            light_on = 0;
        }
      //*/
      
      /*************/
      //TV_DATA = 0;
      
      sleep_ms(20);
   } // end while
}
