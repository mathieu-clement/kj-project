#include "../KJunior.h"
#include "tv_remote_calibration.h"
#include "core.h"
#include "positionment.h"
#include "find_barcode.h"
#include "avoid_obstacles.h"
#include "tv_remote_calibration.h"
#include "../basic_functions.h"


unsigned int16 bw_threshold_left = 3800;
unsigned int16 bw_threshold_right = 3600;

void main(void)
{ 
   
   // Initialization
   KJunior_init () ;
   HemLinCam_Init (); // currently all this does is sleeping for 1 second...
   cs_init(); // Init camera settings and TV remote control
   
   KJunior_set_speed(0,0);
   calibrate_thresholds();
   move_forward();
   
   while (1)
   {
      if((SerialCommandOK == 1) && (Enable_RS232_Control == 1))                    // Test if a Serial Command was received ...
         SerialCommandHandler();
      
      //while(1)
      debug();
      
      if (black_detected()) 
      {
         KJunior_set_speed(5, 5);
         fprintf(USB, "        BLACK DETECTED\r\n");
         if(!do_positioning())
             continue;
       
       unsigned int8 direction = do_rotation_based_on_line();
       
       if(direction == -1){
         continue;
       }
       
       //signed int8 bc = find_barcode();
       sleep_ms(800);
       do_rotation_back(direction);
       avoid_black_lines();
       sleep_s(1);
      } else {
         avoid_obstacles();        
      } // end if black_detected()
      
      sleep_ms(100);
      
   } // end while
} // end main
