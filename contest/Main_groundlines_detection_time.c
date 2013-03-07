#include "KJunior.h"
#include "HemLinCam.h"

#include "basic_functions.h" // sleep_[m]s
#include "contest/contest_barcode.h" // not used yet, will be to decode barcodes
#include "contest/contest_beep.h" // not used yet, will be to play to correct music 
                                  // matching the docoded barcode
#include "binary_led_transcoder.h" // not used but is a great way to have 16 (debug) outputs!

#define HIGH_SPEED 15

// Threshold to distinguish black and white
// TODO: Set with TV remote
// TODO: Start with low value
// TODO: Use two pairs of button. The first pair will increase the threshold by a huge amount,
//       and the second pair will allow to fine tune.
unsigned int16 bw_threshold = 4000;

/***********************************************
 * HOW TO SET THE THRESHOLD WITH THE TV REMOTE *
 ***********************************************/
// 1. Hold the robot in your hands only microns from the ground on a black line.
// 2. Press the UP button on the TV remote until you hear / see the robot slowing down.
// 3. At that point, put it again on white.
// 4. Wait until you hear / see it's going at full speed again.
// 5. Put it on the ground (without holding it) to see if that works.
//    If it doesn't, start over.

// Returns true (1) if one of the ground front sensors is on black.
int1 black_detected()
{
   return KJunior_get_brightness(GROUNDFRONTLEFT)  > bw_threshold ||
          KJunior_get_brightness(GROUNDFRONTRIGHT) > bw_threshold;
}

void main(void)
{ 
   // Initialization
   KJunior_init () ;
   
   // Main loop
   while (1)
   {
      if((SerialCommandOK == 1) && (Enable_RS232_Control == 1))                    // Test if a Serial Command was received ...
         SerialCommandHandler();
      
      //* // Debug
      while(1)
      {
         fprintf(USB, "Left: prox %04ld bright %04ld, Right prox %04ld bright %04ld\r\n", 
            KJunior_get_proximity(GROUNDFRONTLEFT),
            KJunior_get_brightness(GROUNDFRONTLEFT),
            KJunior_get_proximity(GROUNDFRONTRIGHT),
            KJunior_get_brightness(GROUNDFRONTRIGHT));
         sleep_ms(500);
      }
      //*/
      
      if (black_detected()) {
         // If black is detected, go slowly and measure how much time we stay on black
         KJunior_set_speed(0, 0); // may not be necessary but 50 ms is nothing
         sleep_ms(50);
         KJunior_set_speed(5, 5);
         sleep_ms(50);
         
         unsigned int32 start_time = KJunior_get_time();
         
         // Continue rolling until we found white again
         while(black_detected()) {
            sleep_ms(30);
         }
         
         // How much time did we stay on that black line?
         unsigned int32 time_on_black = KJunior_get_time() - start_time;
         
         // Debug
         fprintf(USB, "Time on black: %ld ms\r\n", time_on_black);
         
         // Go forward a bit more
         sleep_ms(700);
         // Stop
         KJunior_set_speed(0,0);
         sleep_ms(50);


         // If time on black over 200 ms:
         // that's the largest line
         if(time_on_black > 200) {
            // Rotate left
            KJunior_set_speed(-HIGH_SPEED, HIGH_SPEED);
            sleep_ms(700);
        } else {
            // that's the smallest line
            // Rotate right
            KJunior_set_speed(HIGH_SPEED, -HIGH_SPEED);
            sleep_ms(700);
        }
            
        // TODO: Decode barcode here
        KJunior_set_speed(0,0);
        sleep_ms(1000); // "Simulate" barcode detection and playing music
          
        // Did we rotate right or left?  
        if(time_on_black > 200) {
            // Rotate back to right
            KJunior_set_speed(HIGH_SPEED, -HIGH_SPEED);
            sleep_ms(700);
         } else {
            // Rotate back to left
            KJunior_set_speed(-HIGH_SPEED, HIGH_SPEED);
            sleep_ms(700);
         }
         
         // Stop
         // TODO: In the contest go ahead...
         KJunior_set_speed(0, 0);
         sleep_ms(5000);
      } else {
         // Full throttle on white when not doing anything special
         // like measuring black lines
         KJunior_set_speed(HIGH_SPEED, HIGH_SPEED);
      } // end if black_detected()
      
      sleep_ms(100);
      
   } // end while
} // end main
