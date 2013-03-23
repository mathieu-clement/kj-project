#include "../KJunior.h"

#include "../Basic_functions.h"
#include "../testing/find_barcode.h"
#include "contest_beep.h"
#include "../binary_led_transcoder.h"

// Obstacle detection

int1 too_close(int8 sensor) {
   return KJunior_get_proximity(sensor) > 1200;
}

int1 was_turning_left = 0;
#define INT_TURN_SPEED 10
#define EXT_TURN_SPEED 15
#define FORWARD_SPEED 10
#define stop() KJunior_set_speed(0, 0)
#define turn_left()  KJunior_set_speed(-INT_TURN_SPEED, EXT_TURN_SPEED); was_turning_left=1; 
#define turn_right() KJunior_set_speed(INT_TURN_SPEED, -EXT_TURN_SPEED); was_turning_left=0; 
#define move_forward() KJunior_set_speed(FORWARD_SPEED, FORWARD_SPEED)

void play_random()
{
   unsigned int8 random = ( 0x7 & KJunior_get_time() ); 
   beep_barcode( random == 0 ? 1 : random );   
}



signed int8 find_barcode(unsigned int32 timeout)
{   

   unsigned int8 bc_found[7];
   unsigned int32 start_time = KJunior_get_time();
   
   while ( ( KJunior_get_time() - start_time ) < timeout && !too_close(FRONT))
   {    
      HemLinCam_Read_Pixels () ;
      pixels = cr_make_single_pixels_array();
      getLines(pixels);
      printStats();
      fprintf(USB, "\r\n");
      
      barcodeFound = findBarcode();
      if( barcodeFound > NOT_FOUND )
      {
         fprintf(USB, "    DETECTED BARCODE No %d\r\n", barcodeFound);
         bc_found[ barcodeFound - 1]++;
         
         if(bc_found[barcodeFound - 1] > 20){ 
            fprintf(USB, "    DEFINITELY DETECTED BARCODE No %d\r\n", barcodeFound);
            return barcodeFound;
         }
      }
      
      fprintf(USB, "\r\n\r\n");
      sleep_ms(500);
      
   } // end while
   
   fprintf(USB, "    TIMEOUT");
   return NOT_FOUND;
   
} // end find_barcode



// Barcode positioning
#define BP_TURN_SPEED 4
#define left_on_black()  ( KJunior_get_proximity(GROUNDLEFT) < threshold_left )
#define right_on_black() ( KJunior_get_proximity(GROUNDRIGHT) < threshold_right )
#define both_on_black()  ( left_on_black() && right_on_black() )

unsigned int16 threshold_left = 1000, threshold_right = 2000;
unsigned int32 avoid_black_counter = 0, counter = 0;
// Barcode detection
#define BT_TIMEOUT 5000

void main() {

   KJunior_Init();
   // calibrate threshold :
   // use MUTE to toggle between left and right threshold calibration
   // use VOL_PLUS/MINUS to 
   
   while(1)
   { 
      TV_DATA = 0;
      int1 flag_left=1, flag_right=1;
      while(flag_left){
      fprintf(USB, "threshold left   %4ld  gr_left   %4ld  gr_right   %4ld\r\n", 
               threshold_left,  KJunior_get_proximity(GROUNDLEFT),  KJunior_get_proximity(GROUNDRIGHT));
      switch(KJunior_get_tv_data() )
      {
         case TV_POWER: goto camera;
         case TV_MUTE: flag_left=0; break;
         case TV_CH_PLUS:
            if(threshold_left < 4000) threshold_left += 100; break;
         case TV_CH_MINUS:
            if(threshold_left > 0) threshold_left -= 100; break;
         case TV_VOL_PLUS:
            if(threshold_left < 4000) threshold_left += 10; break;
         case TV_VOL_MINUS:
            if(threshold_left > 0) threshold_left -= 10; break;
      }
      TV_DATA = 0;
      sleep_ms(100);
       
      }//end while
      TV_DATA = 0;
      while(flag_right){
         fprintf(USB, "threshold right   %4ld  gr_left   %4ld  gr_right   %4ld\r\n", 
                  threshold_right,  KJunior_get_proximity(GROUNDLEFT),  KJunior_get_proximity(GROUNDRIGHT));
         switch(KJunior_get_tv_data())
         {
            case TV_MUTE: flag_right=0; break;
            case TV_POWER: goto camera;
            case TV_CH_PLUS:
               if(threshold_right < 4000) threshold_right += 100; break;
            case TV_CH_MINUS:
               if(threshold_right > 0) threshold_right -= 100; break; 
            case TV_VOL_PLUS:
               if(threshold_right < 4000) threshold_right += 10; break;
            case TV_VOL_MINUS:
               if(threshold_right > 0) threshold_right -= 10; break;
         }
         TV_DATA = 0;
         sleep_ms(100);
      }//end while
   }//end while
   
camera:
   while (KJunior_get_tv_data() != TV_POWER)
   {    
     TV_DATA = 0;     
      HemLinCam_Read_Pixels () ;
      pixels = cr_make_single_pixels_array();
      getLines(pixels);
      printStats();
      fprintf(USB, "\r\n");
      barcodeFound = findBarcode();     
      if( barcodeFound > NOT_FOUND )
         fprintf(USB, "    DETECTED BARCODE No %d", barcodeFound);
      fprintf(USB, "\r\n\r\n");
      sleep_s(1);      
   } // end while
   

   //wait for signal to begin
   while( KJunior_get_tv_data() != TV_POWER );
   
   while(1)
   {
   
begin:
      fprintf(USB, " frontleft %ld frontright %ld \r\n", KJunior_get_proximity(FRONTLEFT), KJunior_get_proximity(FRONTRIGHT));
      // Obstacle detection
      if(too_close(FRONTLEFT)  && too_close(FRONTRIGHT)) {
         if(was_turning_left){ turn_left(); }
         else { turn_right(); }
         led_display_number(15);
      } else if (too_close(LEFT) || too_close(FRONTLEFT)) {
         turn_right();
         led_display_number(1);
      } else if (too_close(RIGHT) || too_close(FRONTRIGHT)) {
         turn_left();
         led_display_number(8);
      } else {
         move_forward();
         led_display_number(6);
      } // end too_close(...)
      
      if(avoid_black_counter && avoid_black_counter++ < 50){
         sleep_ms(100);
         goto begin;
      }
position:  
      avoid_black_counter = 0;
      if (left_on_black() || right_on_black()) { 
      counter = 0;
      if(left_on_black())
      {
         while (!right_on_black()) {
            counter += 1;
            if(counter > 300 || KJunior_get_proximity(FRONT) > 2000 ){
               fprintf(USB, "TIMEOUT placement, doing random");
               stop();              
               play_random();
               KJunior_set_speed(-20, -20);
               while(too_close(FRONT)) sleep_ms(20);
               KJunior_set_speed(2 * BP_TURN_SPEED, 0);
               sleep_s(1);
               avoid_black_counter = 1;
               goto begin;
            }
            fprintf(USB, "black detected  gr_left   %4ld  gr_right   %4ld\r\n", 
               KJunior_get_proximity(GROUNDLEFT),  KJunior_get_proximity(GROUNDRIGHT));
            KJunior_set_speed(0, BP_TURN_SPEED);
            sleep_ms(20);             
         }
      } 
      else 
      {
           while(!left_on_black()){
           counter += 1;
           if(counter > 300 || KJunior_get_proximity(FRONT) > 2000 ){
               fprintf(USB, "TIMEOUT placement, doing random");
               stop();
               play_random();
               KJunior_set_speed(-20, -20);
               while(too_close(FRONT)) sleep_ms(20);
               KJunior_set_speed(0, 2 * BP_TURN_SPEED);
               sleep_s(1);
               avoid_black_counter = 1;
               goto begin;
            }
            fprintf(USB, "black detected  gr_left   %4ld  gr_right   %4ld\r\n", 
               KJunior_get_proximity(GROUNDLEFT),  KJunior_get_proximity(GROUNDRIGHT));
            KJunior_set_speed(BP_TURN_SPEED, 0);
            sleep_ms(20);
           }
       }

         // Now perpendicular to the line on the ground
         // Measure black line to distinguish between line to turn left and
         // line to turn right
         KJunior_set_speed(5, 5);
         
         unsigned int32 start_time = KJunior_get_time();

         // Continue rolling until we found white again
         while(both_on_black());

         // How much time did we stay on that black line?
         unsigned int32 time_on_black = KJunior_get_time() - start_time;

         // Debug
         fprintf(USB, "Time on black: %ld ms\r\n", time_on_black);

         // If time on black over 200 ms:
         // that's the largest line
         if(time_on_black > 200) {
            // Rotate left
            KJunior_set_speed(-10, 10);
            sleep_ms(1400);
        } else {
            // that's the smallest line
            // Rotate right
            move_forward();
            sleep_ms(20);
            KJunior_set_speed(10, -10);
            sleep_ms(1400);
        } // end time_on_black > ...
        
        // Go backwards until very close to the wall behind the robot
        KJunior_set_speed(-20, -20);
        while(!too_close(REAR)) {
            sleep_ms(20);
        }
        
        
        signed int8 barcode;
        KJunior_set_speed(5, 5);
        sleep_ms(2000);
        int1 found = 0;
        while(!too_close(FRONT)) {
            
           // Detect barcode
           barcode = find_barcode(BT_TIMEOUT);
           
           if(barcode) {
               KJunior_set_speed(0, 0);
               beep_barcode(barcode);
               found = 1;
               break;
           }
        } // while not too close too front wall
        
        if(!found){
           stop();
           play_random();
        }
        
        if(time_on_black > 200) {
            // Rotate back to right
            KJunior_set_speed(10, -10);
            sleep_ms(1400);
         } else {
            // Rotate back to left
            KJunior_set_speed(-10, 10);
            sleep_ms(1400);
         }
         
         // Before going further in the track, go full speed again
         move_forward();
         
      } // end if left or right on black
      
      sleep_ms(100);
   } // end while
} // end main

