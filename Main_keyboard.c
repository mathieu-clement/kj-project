#include "KJunior.h"

#include "Basic_functions.h"
#include "simple_beep.h"


//--------------------------------------------------------------------------------//
//- Main program                                                                 -//
//--------------------------------------------------------------------------------//
#separate

void main(void)
{
 // Initialization
 KJunior_init();

   int16 threshold = 3000;

While (1)
{
   if((SerialCommandOK == 1) && (Enable_RS232_Control == 1))
     SerialCommandHandler();
     
   // Each proximity sensor (from left to right) is used as a key to play a note.
   // The note is played as long as the player has his finger on it.
   
   // The code below will let play the scale of D minor
     
   // detect if finger is near the sensor  
   if(KJunior_get_proximity(LEFT) > threshold) {
      // in that case play a note
      KJunior_beep(D_2);
   } else if(KJunior_get_proximity(FRONTLEFT) > threshold) {
      KJunior_beep(E_2);
   } else if(KJunior_get_proximity(FRONT) > threshold) {
      KJunior_beep(F_2);
   } else if(KJunior_get_proximity(FRONTRIGHT) > threshold) {
      KJunior_beep(G_2);
   } else if(KJunior_get_proximity(RIGHT) > threshold) {
      KJunior_beep(A_2);
   } else {
      // Stop playing when finger is not in front of any sensor
      KJunior_beep(MUTE);
   }
   
   // Sleep for a moment
   sleep_ms(10);
   
   
} // end while

} // end main
       
