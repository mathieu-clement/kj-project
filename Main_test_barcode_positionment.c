/**
 * @file
 * 
 * @brief File containing the Main function for the presentation.
 */

// K-Junior
#include "KJunior.h" 

// Linear camera
#include "HemLinCam.h" 

// Utilities to read and output pixels read on linear camera
#include "simple_camera_reading.h"

// Set camera settings with TV remote control
#include "simple_camera_settings_with_tv_remote.h" 

// Basic functions such as sleep_ms()
#include "basic_functions.h" 

// Melodies to be played on the buzzer and utilities to play notes
#include "simple_beep.h" 


// Utilities to read keys pressed on the TV remote control
#include "tv_remote_utils.h" 

#define THRESHOLD 1500

//------------------

//------------------

void main(void)
{
   // Initialization
   KJunior_init () ;
   HemLinCam_Init (); // currently all this does is sleeping for 1 second...
   cs_init(); // Init camera settings and TV remote control
   //Enable_RS232_Control = 1; // Enable robot control over the serial connection
   
   int1 isOnWhite = 1;
  // Kjunior_set_speed(5,5);
   // Main loop
   while (1)
   {   
      HemLinCam_Read_Pixels () ;

      fprintf(USB, "Ground front  left proximity: %4ld, brightness: %4ld\r\n", 
         KJunior_get_proximity(GROUNDFRONTLEFT),KJunior_get_brightness(GROUNDFRONTLEFT));
      fprintf(USB, "Ground front right proximity: %4ld, brightness: %4ld\r\n",
          KJunior_get_proximity (GROUNDFRONTRIGHT),
          KJunior_get_brightness(GROUNDFRONTRIGHT));
      fprintf(USB, "Side          left proximity: %4ld, brightness: %4ld\r\n", 
         KJunior_get_proximity(GROUNDLEFT),KJunior_get_brightness(GROUNDLEFT));
      fprintf(USB, "Side         right proximity: %4ld, brightness: %4ld\r\n",
          KJunior_get_proximity (GROUNDRIGHT),
          KJunior_get_brightness(GROUNDRIGHT));
      fprintf(USB, "\r\n\r\n");
      
      if(KJunior_get_proximity(GROUNDFRONTLEFT)  < THRESHOLD && 
         KJunior_get_proximity(GROUNDFRONTRIGHT) < THRESHOLD)
         {
            if(!isOnWhite)
            {
               isOnWhite = 0;
               KJunior_beep(40);
            }else
            {
               isOnWhite = 1;
               KJunior_beep(0);
            }
         }
      sleep_ms(50);
      
   } // end while
   
} // end main


