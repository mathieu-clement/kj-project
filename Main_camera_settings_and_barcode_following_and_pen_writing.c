#include "KJunior.h"
// Linear camera
#include "HemLinCam.h"

#include "Basic_functions.h"
#include "simple_beep.h"
#include "binary_led_transcoder.h"
#include "tv_remote_utils.h"

#define LEFT_PIXELS   HemLinCam_Pixels_Zone1
#define CENTER_PIXELS HemLinCam_Pixels_Zone2
#define RIGHT_PIXELS  HemLinCam_Pixels_Zone3

#define A30_DEGREES_TIME    1800
#define A45_DEGREES_TIME    2400
#define A75_DEGREES_TIME    3000
#define A90_DEGREES_TIME    3760
#define A180_DEGREES_TIME   7900
#define A360_DEGREES_TIME   16600


//--------------------------------------------------------------------------------//
//- Main program                                                                 -//
//--------------------------------------------------------------------------------//
#separate

void print_pixels(unsigned char *array)
{
   // NB: Assume size of 34
   int array_size = 34;
   
   for(int i=0; i<array_size; i++)
   {
      fprintf(BT, "%u ", array[i]);
   }
}

int1 exp_time_up()
{
   return KJunior_get_tv_data() == TV_CH_PLUS;
}

int1 exp_time_down()
{
   return KJunior_get_tv_data() == TV_CH_MINUS;
}

int1 power_button() {
   return KJunior_get_tv_data() == TV_POWER;
}

int1 threshold_up() {
   return KJunior_get_tv_data() == TV_VOL_PLUS;
}

int1 threshold_down() {
   return KJunior_get_tv_data() == TV_VOL_MINUS;
}

void turn(int8 angle, int1 should_turn_left)
{
   int32 sleep_time;
   
   switch(angle)
   {
      case 30:
         sleep_time = A30_DEGREES_TIME;
         led_display_number(should_turn_left ? 10 : 5);
         break;
      case 45:
         sleep_time = A45_DEGREES_TIME;
         led_display_number(should_turn_left ? 4 : 2);
         break;
      case 75:
         sleep_time = A75_DEGREES_TIME;
         led_display_number(should_turn_left ? 4 : 2);
         break;
      case 90:
         sleep_time = A90_DEGREES_TIME;
         led_display_number(should_turn_left ? 8 : 1);
         break;
      case 180:
         sleep_time = A180_DEGREES_TIME;
         led_display_number(should_turn_left ? 12 : 3);
         break;
      case 360:
         sleep_time = A360_DEGREES_TIME;
         led_display_number(9);
         break;
      default:
         sleep_time = 0;
         // Tell user about a problem...
         KJunior_beep(A_3);
         sleep_ms(2000);
         KJunior_beep(MUTE);
   }
   
   if(should_turn_left)
      KJunior_set_speed(-3, 3);
   else
      KJunior_set_speed(3, -3);
      
   sleep_ms(sleep_time);
   KJunior_set_speed(0,0);
   led_display_number(0);
}

void turn_left(int8 angle)
{
   turn(angle, 1);
}

void turn_right(int8 angle)
{
   turn(angle, 0);  
}

// distance:
// 1 : 3.0cm   500   1x500
// 2 : 3.5cm   1500  3x500
// 3 : 5.5cm   2500  5x500
// 4 : 8.2cm   3500  7x500
// ...

void move_no_turn(int8 distance, int1 go_forward)
{
   led_display_number(6);
   if(go_forward)
      KJunior_set_speed(3,3);
   else
      KJunior_set_speed(-3,-3);
      
   delay_ms(distance*500);
   KJunior_set_speed(0,0);
   led_display_number(0);
}

void move_forward(int8 distance)
{
   move_no_turn(distance, 1);
}

void move_backward(int8 distance)
{
   move_no_turn(distance, 0);
}

int1 is_barcode_near_enough()
{
   return 0;
}

char* make_entire_pixels_array()
{
   char array[102];
   
   int current_index = 0;
   int i;
   
   for(i=0; i<34; i++)
   {
      array[current_index++] = LEFT_PIXELS[i];
   }
   for(i=0; i<34; i++)
   {
      array[current_index++] = CENTER_PIXELS[i];
   }
   for(i=0; i<34; i++)
   {
      array[current_index++] = RIGHT_PIXELS[i];
   }
   
   return array;
}

int1 is_barcode_in_view(char* array)
{
   // Try to find 5 black lines (barcode)
  
    int black_lines = 0;

    int into_black_line = 0;

    // Iterate through array
    // if pixel is black: into_black_line = 1
    // if pixel is white: if into_black_line==1, then increment black_lines, into_black_lines=0

    int i;
    for(i=0; i<102; i++)
    {
        // printf("Pixel %3d: %3d. into_black_lines=%d, black_lines=%d\n", i, array[i],
        //            into_black_line, black_lines); // (GNU C)
        if(array[i] == 0)
        {
            into_black_line = 1;
        } else //if(array[i] == 255) // else is not sufficient because we don't know how 
                                    // array is initialized (GNU C)
        {
            if(into_black_line)
            {
                black_lines++;
            }
            into_black_line = 0;
        } 
    } // end for

    return black_lines >= 5;
}

void main(void)
{
 // Initialization
 KJunior_init();
 HemLinCam_Init(); // currently all this does is sleeping for 1 second...
 TV_DATA = 60; // exposure time set to 1 by default
 int1 threshold_enabled = 0;
 
 int8 exposition_time = 1; // exposition time default to 1
 led_display_number(exposition_time);
 int8 threshold = 120; // default threshold
 
 //KJunior_config_tv_remote_control(ENABLE);
 
 
 int1 barcode_found = 0;

 //*******************************Main loop***************************************//

 Enable_RS232_Control = 1;

While (1)
{
   if((SerialCommandOK == 1) && (Enable_RS232_Control == 1))
     SerialCommandHandler();

 if(KJunior_get_switch_state() == 3)
 {
 
   // Draw CAT
   
   
   // Draw C
   move_forward(2);
   turn_left(90);
   move_forward(4);
   turn_left(90);
   //move_forward(2);
   
   // Go to A
   move_forward(4);
   
   // Draw A
   turn_left(75);
   move_forward(2); // middle of left / of A
   
   // Make straight - (from /-\)
   turn_right(75);
   move_forward(2);
   move_backward(2);
   
   // Make ^ of A and go down to finish letter
   turn_left(75);
   move_forward(2);
   turn_left(30);
   move_backward(6);
   turn_right(30);
   turn_right(45);
   
   // Go to T
   move_forward(3);
   
   // Draw T
   turn_left(90);
   move_forward(4);
   
   // Make left line
   turn_left(90);
   move_forward(2);
   // Make right line
   move_backward(6);
   
   while(1)
   {
      // Blink leds
      led_display_number(15);
      sleep_ms(300);
      led_display_number(0);
      sleep_ms(300);
   }

 } 
 else if(KJunior_get_switch_state() == 7 || KJunior_get_switch_state() == 6) // Read dip switch value
 {  
     // Normal program reads TV remote to set Linear camera settings (switch_state 7)
     
     // Barcode finder tries to find a barcode and moves to it (switch_state 6)
     
     if(KJunior_get_switch_state() == 6)
     {
     
         // Force barcode not found when 0 is pressed on remote
         if(get_tv_remote_pad_number() == 0)
         {
            barcode_found = 0;
            KJunior_beep(C_2);
            delay_ms(1000);
            KJunior_beep(MUTE);
         }
     
         // Beep and stop when barcode found
         if(barcode_found)
         {
            KJunior_set_speed(0,0); // Should not be needed but KJunior is imprevisible...
            KJunior_beep(C_3);
            delay_ms(300);
            KJunior_beep(MUTE);
         } else {
         
         // Build entire_pixels_array
         char* entire_pixels_array = make_entire_pixels_array();
     
            if(is_barcode_in_view(entire_pixels_array))
            {
               if(is_barcode_near_enough())
               {
                  barcode_found = 1;
                  KJunior_set_speed(0,0);
               } else {
                  // Move forward
                  KJunior_set_speed(3,3);
               }
            }
            else
            {
            
               // Rotate left. Maybe next time we look for it, we'll find it.
               KJunior_set_speed(-3,3);
            }
            
         } // end barcode found
         
         // sleep_ms(2000);
        
     } // end switch state 6
     
     // Reset
     if(KJunior_get_tv_data() == TV_MUTE)
     {
         exposition_time = 1;
         led_display_number(exposition_time);
         threshold = 120;
         threshold_enabled = false;
         HemLinCam_Set_Led_State(threshold_enabled);
     }
     
        
      // POWER_BUTTON => Activate/Disable threshold. Is disabled by default.
      if(power_button())
      {
         // Toggle threshold
         threshold_enabled = !threshold_enabled;
         
         // Enable / Disable On/Off LED
         HemLinCam_Set_Led_State(threshold_enabled);
      }
      
      // Exposition time UP
      if(exp_time_up())
      {
         // We don't check for 255, user won't try that...
         exposition_time++;
         
         HemLinCam_Set_Exposition_Time(exposition_time);
         // Show exposition time with LEDs
         // 16 will be shown as 0, 17 as 1, 18 as 2, ... (modulo 16)
         led_display_number(exposition_time % 16);
      }
      if(exp_time_down())
      {
         //if(exposition_time != 0) // do not go below 0
         //{
         //   exposition_time--;
         //}
         if(exposition_time == 0)
         {
            exposition_time = 15;
         } else {
            exposition_time--;
         }
         
         HemLinCam_Set_Exposition_Time(exposition_time);
         led_display_number(exposition_time % 16);
      }
      
      // TODO Threshold + / -
      
      if(threshold_up())
      {
         // Do not go over 240
         if(threshold != 240)
         {
            threshold += 40; // Move threshold 40 up
         }
         
         HemLinCam_Set_Threshold(threshold);
      }
      if(threshold_down())
      {
         // Do not go below 0
         if(threshold != 0)
         {
            threshold -= 40;
         }
         HemLinCam_Set_Threshold(threshold);
      }
       
   if(threshold_enabled)
      HemLinCam_Read_Pixels_Thresholded();
   else
      HemLinCam_Read_Pixels();
      
      
   print_pixels(LEFT_PIXELS);
   print_pixels(CENTER_PIXELS);
   print_pixels(RIGHT_PIXELS);
   fprintf(BT, "\r\n");
   
   TV_DATA = 0; // important trick to know when using TV remote!
   
   sleep_ms(200);
   
 } // end get_switch_state == 7
   
} // end while

} // end main
