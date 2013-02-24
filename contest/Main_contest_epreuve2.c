#include "KJunior.h"
#include "HemLinCam.h"

#include "basic_functions.h"
#include "simple_camera_reading.h"
#include "simple_camera_settings_with_tv_remote.h"
#include "contest/contest_barcode.h"
#include "contest/contest_beep.h"
#include "binary_led_transcoder.h"


void main(void)
{ 
   // Initialization
   KJunior_init () ;
   cs_init();
   Enable_RS232_Control = 1; // Enable robot control over the serial connection
   // KJunior_config_tv_remote_control (ENABLE) ;
   
   int1 light_on = 0;
   int1 first_time_light_on = 0;
   unsigned int32 flash_counter = -1; // do not count first flash
   
   unsigned int32 light_on_time;
   int32 timer = 0;
   
   // Main loop
   while (1)
   {
      if((SerialCommandOK == 1) && (Enable_RS232_Control == 1))                    // Test if a Serial Command was received ...
         SerialCommandHandler();
         
      cs_set_camera_with_tv_remote();

      /*************/
      while(KJunior_get_time() - light_on_time < 6000 || !first_time_light_on) {
      
      HemLinCam_Read_Pixels () ;
      char* pixels = cr_make_single_pixels_array();
      
      // Compute total
      int32 pixels_total = 0;
      for(int8 i=0; i < 102; i++) {
         pixels_total += pixels[i];
      }
      // Compute average
      int8 pixels_average = pixels_total / 102.0;
      
      fprintf(USB, "average: %d\r\n", pixels_average);
      
     if(pixels_average > 50) {
         if(!light_on) {
            // If light is now on but previously wasn't, then:
            light_on = 1;
            KJunior_beep(10);
            sleep_ms(30);
            KJunior_beep(MUTE);
            flash_counter++;
            fprintf(USB, "counter=%ld\r\n", flash_counter);
            
            if(!first_time_light_on) {
            // if this is the first time we see the light is on, then
            light_on_time = KJunior_get_time();
            first_time_light_on = 1;
            }
         }
      } else {
         light_on = 0;
      }
      
      sleep_ms(100);
      
      } // end while timer
      
      
      // At this point we know there were X flashes during 6 seconds, i.e.
      // X/6 flashes per second. This is the tempo we are looking for
      // 60 is a constant
      unsigned int8 tempo = flash_counter * 60 / 6;
      fprintf(USB, "%d bpm\r\n", tempo);
      
      if(tempo > 20) {
      beep_la_marseillaise(tempo);
      } else {
         // pause
         sleep_ms(60000);
      }
      
      /*************/
      
      cs_reset_tv_remote();
      sleep_ms(100);
   } // end while
}