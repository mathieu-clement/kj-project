#include "KJunior.h"
#include "HemLinCam.h"

#include "basic_functions.h"
#include "simple_camera_reading.h"
#include "simple_camera_settings_with_tv_remote.h"
#include "contest/contest_barcode.h"
#include "binary_led_transcoder.h"


void main(void)
{ 
   // Initialization
   KJunior_init () ;
   cs_init();
   Enable_RS232_Control = 1; // Enable robot control over the serial connection
   // KJunior_config_tv_remote_control (ENABLE) ;
   
   int1 light_on = 0;
   int32 flash_counter = 0;
   int32 timer = 0;
   
   // Main loop
   while (1)
   {
      if((SerialCommandOK == 1) && (Enable_RS232_Control == 1))                    // Test if a Serial Command was received ...
         SerialCommandHandler();

      cs_set_camera_with_tv_remote();
      
      /*************/
      HemLinCam_Read_Pixels () ;
      char* pixels = cr_make_single_pixels_array();
      int32 total = 0;
      
      for(int8 i=0; i < 102; i++) {
         //fprintf(USB, "%d " pixels[i]);
         total += pixels[i];
      }
      //fprintf(USB, "\r\nTotal: %ld\r\n", total);
      
      int8 average = total / 102.0;
      
      //fprintf(USB, "%d\r\n", average);
      
      if(average > 127) {
         if(!light_on) {
            light_on = 1;
            KJunior_beep(10);
            sleep_ms(40);
            KJunior_beep(0);
         }
      } else {
         light_on = 0;
      }
      
      /*************/
      
      cs_reset_tv_remote();
      sleep_ms(100);
   } // end while
}
