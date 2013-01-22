#include "KJunior.h"

#include "Basic_functions.h"
#include "tv_remote_utils.h"




//--------------------------------------------------------------------------------//
//- Main program                                                                 -//
//--------------------------------------------------------------------------------//
#separate

void main(void)
{
 // Initialization
 KJunior_init();
 
 

While (1)
{
   //if((SerialCommandOK == 1) && (Enable_RS232_Control == 1))
   //  SerialCommandHandler();
    
   int key = get_tv_remote_pad_number();
   int speed = 10;
   
   switch(key)
   {
      case 0:
         // Go backward
         KJunior_set_speed(-speed, -speed);
         break;
         
      case 1:
         // Turn left while going forwards
         KJunior_set_speed(speed/2, speed);
         break;
         
      case 2:
         // Go forwards
         KJunior_set_speed(speed, speed);
         break;
         
      case 3:
         // Turn right while going forwards
         KJunior_set_speed(speed, speed/2);
         break;
         
      case 4:
         // Rotate itself to the left
         KJunior_set_speed(-speed, speed);
         break;
         
      case 5:
      default:
         // Stop
         KJunior_set_speed(0, 0);
         break;
         
      case 6:
         // Rotate itself to the right
         KJunior_set_speed(speed, -speed);
         break;
         
      case 7:
         // Turn left while going backwards
         KJunior_set_speed(-speed/2, -speed);
         break;
         
      case 8:  
         // Go backwards
         KJunior_set_speed(-speed, -speed);
         break;
         
      case 9:
         // Turn right while going backwards
         KJunior_set_speed(-speed, -speed/2);
         break;
   } // end switch
   
   sleep_ms(50);
   
 } // end while

} // end main

