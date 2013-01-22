/**
 * @file
 * 
 * @brief Barcode Finder Program
 */

#include "simple_camera_reading.h"

/**
 * The Barcode Finder looks for a five stripes barcode and moves to it.
 * 
 */
void barcode_finder(void)
{
      // Build entire_pixels_array
      char* entire_pixels_array = cr_make_single_pixels_array();
     
      if(bf_is_barcode_in_view(entire_pixels_array))
      {
   // Move forward
   KJunior_set_speed(3,3);
      }
      else
      {
   // Rotate left. Maybe next time we look for it, we'll find it.
   KJunior_set_speed(-3,3);
      }
}

/**
 * Returns true if the camera (whose output reference is passed in array parameter) has a five
 * stripes barcode in view.
 * 
 * @param array An array of 102 (char) pixels values
 * @return true if the camera (whose output reference is passed in array parameter) has a five
 * stripes barcode in view.
 */
int1 bf_is_barcode_in_view(char* array)
{
   // Initialize some variables
   int black_lines = 0;
   int into_black_line = 0;
   
   // Iterate through array
   // Pseudo code:
   // if pixel is black: into_black_line = 1
   // if pixel is white: if into_black_line == 1, then increment black_lines, into_black_lines = 0
   int i;
   for (i = 0; i<102; i++)
   {
      if (array[i] == 0)
      {
         into_black_line = 1;
      } 
      else 
      {
         if (into_black_line)
         {
            black_lines++;
         }
         into_black_line = 0;
      } // end else
   } // end for
   return black_lines >= 5; // check there are five stripes in camera view
}
