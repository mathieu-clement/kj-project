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
   
   int8 detected_barcode;
   
   // Main loop
   while (1)
   {
      if((SerialCommandOK == 1) && (Enable_RS232_Control == 1))                    // Test if a Serial Command was received ...
         SerialCommandHandler();

      cs_set_camera_with_tv_remote();
      
      cr_print_pixels_bluetooth();
      
      detected_barcode = detect_barcode(cr_make_single_pixels_array(), 128);
      if (detected_barcode != -1)
         led_display_number(detected_barcode);
      else
         led_display_number(15);
      
      cs_reset_tv_remote();
      sleep_ms(300);
   } // end while
}
