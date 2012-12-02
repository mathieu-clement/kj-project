#include "KJunior.h"

//--------------------------------------------------------------------------------//
//- Main program / Mélodies avec télécommande                                                                -//
//--------------------------------------------------------------------------------//
#separate

#include "tv_remote_utils.h"
#include "simple_beep.h"

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
      
      if(remote_control_input_data != KJunior_get_tv_data())
      {
      
         // Remember which button was pressed to ignore this event at next iteration.
         remote_control_input_data = KJunior_get_tv_data();
         // Prints TV remote code of the last pressed button
         fprintf(USB, "TV Remote raw input: %d\r\n", (int8) remote_control_input_data);
      
         // Convert raw input from TV remote to the number printed on the button in the key pad.
         int8 tv_number_input = to_pad_number(remote_control_input_data);
         
         // Test if the button pressed was in the keypad
         if(tv_number_input != -1)
         {
            switch(tv_number_input)
            {
               case 1:
                  beep_blues_scale();
                  break;
               case 2:
                  for(int i=0; i<4; i++)
                  {
                     KJunior_beep(C_4);
                     KJunior_delay_ms(500);
                     
                     KJunior_beep(G_3);
                     KJunior_delay_ms(500);
                  }
                  KJunior_beep(MUTE);
                  break;
                  
               case 3:
                  int8 notes[] = {
                                 C_2, E_2, G_2,
                                 D_2, F_2, A_2,
                                 E_2, G_2, B_2,
                                 F_2, A_2, C_3,
                                 G_2, B_2, D_3,
                                 A_2, C_3, E_3,
                                 B_2, D_3, F_3,
                                 E_3
                  };
                  
                  for(int j=0; j<(sizeof(notes)/sizeof(int8)); j++)
                  {
                     KJunior_beep(notes[j]);
                     KJunior_delay_ms(100);
                  }
                  
                  KJunior_beep(MUTE);
                  break;
                  
               case 4:
                  beep_star_wars();
                  break;
            }
         }
         
         // Red power button on TV remote
         if((int8)remote_control_input_data == 38)
         {
            incremental_beep();
         }
         
         
         // Wait 1/10th of a second
         KJunior_delay_ms(100);
         
      }
 }

}
