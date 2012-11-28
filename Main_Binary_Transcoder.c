#include "KJunior.h"

//--------------------------------------------------------------------------------//
//- Main program / Transcodeur binaire (4 bits) avec télécommande                                                                -//
//--------------------------------------------------------------------------------//
#separate

#include "binary_led_transcoder.h"
#include "tv_remote_utils.h"

void main(void)
{
 // Initialization
 KJunior_init();
 
 // Raw input from TV remote control
 unsigned char remote_control_input_data = -1;
 
 //*******************************Main loop***************************************//
 while (1)
 { 
   if((SerialCommandOK == 1) && (Enable_RS232_Control == 1))                    // Test if a Serial Command was received ...
      SerialCommandHandler();
      
      // if new button pressed on TV remote
      if(remote_control_input_data != KJunior_get_tv_data())
      {
      
         // Remember what button was pressed to ignore this event at next iteration.
         remote_control_input_data = KJunior_get_tv_data();
         // Debug
         fprintf(USB, "TV Remote raw input: %d\r\n", (int8) remote_control_input_data);
      
         // Convert raw input from TV remote to the number printed on the button in the key pad.
         int8 tv_number_input = to_pad_number(remote_control_input_data);
        
        // Display this number in binary format (4 bits) with the four supplied LEDs.
        led_display_number(tv_number_input);
         
         // Wait 1/10th of a second
         KJunior_delay_ms(100);
      } // end if new button from TV remote
 } // end while

} // end main
