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

// Output a number on the 4 leds in a binary way
#include "binary_led_transcoder.h" 

// Utilities to read keys pressed on the TV remote control
#include "tv_remote_utils.h" 

// The Multitasking Program
#include "multitasking.h" 

// The Follow Hand Program
#include "follow_hand.h" 

void main(void)
{
   // Initialization
   KJunior_init () ;
   HemLinCam_Init (); // currently all this does is sleeping for 1 second...
   cs_init(); // Init camera settings and TV remote control
   Enable_RS232_Control = 1; // Enable robot control over the serial connection
   
   // Main loop
   while (1)
   {
      if ( (SerialCommandOK == 1)&& (Enable_RS232_Control == 1) )
         SerialCommandHandler () ;
      
      
      // Read dip switch value
      if (KJunior_get_switch_state () == 1)
      {
         follow_hand () ;
      } 
      else if (KJunior_get_switch_state () == 2 )
      {
	 // Multitasking Program with sound
         multitasking();
      } 
      else if (KJunior_get_switch_state () == 5) 
      {
	 // Multitasking Program *without* sound
         mt_be_silent_please = 1;
         multitasking();
      } 
      else if (KJunior_get_switch_state () == 3 || KJunior_get_switch_state () == 7)
      {
         // With switch state 7 program reads TV remote to set Linear camera settings
         // With switch state 3 programs does the same AND looks for a barcode then moves to it.
         
         if (KJunior_get_switch_state () == 3)
         {
	   // Barcode Finder Program
	   barcode_finder();
         }
         
         // Read remote control presses and set camera settings accordingly
         cs_set_camera_with_tv_remote();         
         
	 // Print values read by the linear camera on Bluetooth serial port
	 // (for live view on a computer or smartphone)
         cr_print_pixels_bluetooth();
         
	 // Reset TV remote last pressed key (this is to detect multiple key presses
	 // on the very same key, which otherwise would not be detected)
         cs_reset_tv_remote();
	 
	 // Hold on for a moment (200 ms)
	 sleep_ms (200) ;
      }
      else if (KJunior_get_switch_state () == 4)
      {
	 // Play Bach's Badinerie tune
         beep_badinerie () ;
      }
   } // end while
} // end main
