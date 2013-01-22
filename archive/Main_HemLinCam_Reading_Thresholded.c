#include "KJunior.h"
// Linear camera
#include "HemLinCam.h"

#define LEFT_PIXELS   HemLinCam_Pixels_Zone1
#define CENTER_PIXELS HemLinCam_Pixels_Zone2
#define RIGHT_PIXELS  HemLinCam_Pixels_Zone3

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
      fprintf(USB, "%u ", array[i]);
   }
}

void main(void)
{
 // Initialization
 KJunior_init();
 HemLinCam_Init(); // currently all this does is sleeping for 1 second...
 HemLinCam_Set_Exposition_Time(5);
 HemLinCam_Set_Threshold(127);
 
 //*******************************Main loop***************************************//

While (1)
{
   if((SerialCommandOK == 1) && (Enable_RS232_Control == 1))
     SerialCommandHandler();
       
   HemLinCam_Read_Pixels_Thresholded();
   
   print_pixels(LEFT_PIXELS);
   // fprintf(USB, "\r\n");
   print_pixels(CENTER_PIXELS);
   // fprintf(USB, "\r\n");
   print_pixels(RIGHT_PIXELS);
   fprintf(USB, "\r\n");
   KJunior_delay_ms(40);
}

}
