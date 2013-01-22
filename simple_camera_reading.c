/**
 * @file
 * 
 * @brief Utilities to read and print pixels from the linear camera
 */

#include "simple_camera_reading.h"

/**
 * Prints an array of 34 pixels to Bluetooth output.
 *
 * @param array an array of 34 char values (as provided by HemLinCam)
 */
void cr_print_pixels(unsigned char *array34)
{
   // NB: Assume size of 34
   int array_size = 34;
   
   for (int i = 0; i<array_size; i++)
   {
      fprintf (BT, "%u ", array34[i]);
   }
}

/**
 * Concatenate the three 34 pixels arrays into one single 102 pixels array.
 */
char* cr_make_single_pixels_array()
{
   char array[102];
   
   int current_index = 0;
   int i;
   
   for (i = 0; i<34; i++)
   {
      array[current_index++] = LEFT_PIXELS[i];
   }
   for (i = 0; i<34; i++)
   {
      array[current_index++] = CENTER_PIXELS[i];
   }
   for (i = 0; i<34; i++)
   {
      array[current_index++] = RIGHT_PIXELS[i];
   }
   
   return array;
}

/**
 * Prints a line of 102 pixel values to Bluetooth serial port.
 */
void cr_print_pixels_bluetooth() {
   // Fire the camera shutter to update the pixels arrays
   if (cr_threshold_enabled)
      HemLinCam_Read_Pixels_Thresholded () ;
   else
      HemLinCam_Read_Pixels () ;
  
    cr_print_pixels (LEFT_PIXELS) ;
    cr_print_pixels (CENTER_PIXELS) ;
    cr_print_pixels (RIGHT_PIXELS) ;
    fprintf (BT, "\r\n"); // Windows line break
}
