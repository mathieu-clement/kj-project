#include "KJunior.h"
#include "HemLinCam.h"

#include "basic_functions.h"
#include "simple_camera_reading.h"
#include "simple_camera_settings_with_tv_remote.h"
#include "contest/contest_barcode.h"
#include "contest/contest_beep.h"
#include "binary_led_transcoder.h"

#define SAMPLE_DURATION 2 // seconds
#define NBR_NOTES 50


void main(void)
{ 
   // Initialization
   KJunior_init () ;
   cs_init();
   //Enable_RS232_Control = 1; // Enable robot control over the serial connection
   // KJunior_config_tv_remote_control (ENABLE) ;
   
   int1 light_on = 0;
   unsigned int32 flash_counter = -1; // do not count first flash
   
   unsigned int32 timer;
   
   // Declared here to save some memory but may not be needed
   int32 pixels_total;
   int8 pixels_average;
   int8 i;
   char* pixels;
   unsigned int8 tempo = 0;
   int16 note_delta; // beware the float to int conversion!
   unsigned int32 note_on_time;
   
   // Put "La Marseillaise" in an array
   // Array length = Number of notes * 2
   // To find number of notes, I use 
   // $ grep add_note_to_array contest_barcode_array.c | wc -l
   int8 marseillaise_array[NBR_NOTES * 2]; // why 100? Read above.
   add_marseillaise_to_array(marseillaise_array);
   unsigned int16 marseillaise_index = 0;
   
   // Main loop
   while (1)
   {
      //if((SerialCommandOK == 1) && (Enable_RS232_Control == 1))                    // Test if a Serial Command was received ...
      //   SerialCommandHandler();
         
      cs_set_camera_with_tv_remote();
      
      
         HemLinCam_Read_Pixels () ;
         pixels = cr_make_single_pixels_array();
         
         // Compute total
         pixels_total = 0;
         for(i=0; i < 102; i++) {
            pixels_total += pixels[i];
         }
         // Compute average
         pixels_average = pixels_total / 102.0;
         
         //fprintf(USB, "average: %d\r\n", pixels_average);
      
      /* BLOCK 1 */
      
        if(pixels_average > 50) {
            if(!light_on) {
               // If light is now on but previously wasn't, then:
               light_on = 1;
               flash_counter++;
               fprintf(USB, "counter=%ld\r\n", flash_counter);
            }
         } else {
            light_on = 0;
        }
        
      if(KJunior_get_time() - timer > SAMPLE_DURATION * 1000) {
         // Compute tempo
         tempo = flash_counter * 60 / SAMPLE_DURATION;
         fprintf(USB, "%d bpm\r\n", tempo);
         
         flash_counter = 0;
         timer = KJunior_get_time();
      }
      
      /* BLOCK 2 */
      
      // Do not try to play anything until we get some light or a decent tempo
      if (tempo < 40) {
         continue;
      }
      
      //*
      if(KJunior_get_time() - note_on_time > note_delta) {
         // Start the music from the beginning at the end
         if(marseillaise_index >= NBR_NOTES*2) {
            marseillaise_index = 0;
         }
         /*
         fprintf(USB, "(%ld) Play %d during %ld ms (1/%d bar at %d bpm) \r\n", 
                        marseillaise_index/2,
                        marseillaise_array[marseillaise_index],
                        (int16) note_length_ms(marseillaise_array[marseillaise_index+1], tempo),
                        marseillaise_array[marseillaise_index+1],
                        tempo);
        */
        
        // Necessary to play the same note several times 
        KJunior_beep(0);
        sleep_ms(10);
                        
         KJunior_beep(marseillaise_array[marseillaise_index++]);
         note_delta = note_length_ms(marseillaise_array[marseillaise_index++], tempo); // beware float to int conversion!
         note_on_time = KJunior_get_time();
      }
      //*/
      
      /*************/
      
      cs_reset_tv_remote();
      sleep_ms(100);
   } // end while
}
