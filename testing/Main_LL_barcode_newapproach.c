/**
 * @file
 * 
 * @brief File containing the Main function for the presentation.
 */

// K-Junior
#include "KJunior.h" 

// Linear camera
#include "HemLinCam.h" 

// Utilities to read and output pixels read on linear camera
#include "simple_camera_reading.h"

// Set camera settings with TV remote control
#include "simple_camera_settings_with_tv_remote.h" 

// Basic functions such as sleep_ms()
#include "basic_functions.h" 

// Melodies to be played on the buzzer and utilities to play notes
#include "simple_beep.h" 


// Utilities to read keys pressed on the TV remote control
#include "tv_remote_utils.h" 

#define MY_THRESHOLD 240
#define DELTA 2


#define NOT_FOUND 0
#define ALL_WHITE -1
#define ALL_BLACK -2
#define TOO_MUCH_WHITE_LINES -3
#define NOT_ENOUGH_BLACK_LINES -4
#define WHITE_LINES_SUCK -5

//------------------
char* pixels;
signed int8 barcodeFound = 0;
unsigned int8 blackIndex = 0, whiteIndex = 0;
unsigned int16 white_lines[52], black_lines[52];
//------------------



void getLines(char* pixels)
{
   //reset arrays
   blackIndex = whiteIndex = 0;
   
   int8 i = 1, counter = 1;
   int1 isWhite = (pixels[0] > MY_THRESHOLD);
   
   fprintf(USB, "first pixel is white %d\r\n", isWhite);
   for(;i < 102; i++)
   {
      if( ( pixels[i] > MY_THRESHOLD ) == isWhite )
      {
         counter++;
      }
      else
      {
         if(isWhite)
         {
            white_lines[whiteIndex++] = counter;
            isWhite = 0;
         }
         else
         {        
            black_lines[blackIndex++] = counter;
            isWhite = 1;
         }
         counter = 1;
         //isWhite = !isWhite;
      }
           
   }
   
   if(isWhite)
      white_lines[whiteIndex++] = counter;
   else
      black_lines[blackIndex++] = counter;     
}



void printStats()
{
   int8 i = 0;
   
   if(whiteIndex != 0)
   {
      fprintf(USB, "\r\nWhite lines detected: %d \r\nLength in pixels : ", whiteIndex);
      for(; i < whiteIndex; i++)
      {
         fprintf(USB, " %ld ", white_lines[i]);
      }
   }
   i = 0;
   if(blackIndex != 0)
   {
      fprintf(USB, "\r\nBlack lines detected: %d \r\nLength in pixels : ", blackIndex);
      for(; i < blackIndex; i++)
      {
         fprintf(USB, " %ld ", black_lines[i]);
      }
   }
   
}

int1 isSizeExpected( int8 expected, int8 value )
{
   return ( ( value >= expected - DELTA ) && ( value <= expected + DELTA ) );   
}

unsigned int8 diffBetween( int8 v1, int8 v2 )
{
   return ( v1 > v2 ? (v1 - v2) : (v2 - v1) );   
}



signed int8 findBarcode()
{
   //----------------- checks that we have the correct number of lines
   
   if( whiteIndex == 1 && blackIndex == 0 )
      return ALL_WHITE;
   
   if( blackIndex == 1 )
      return ALL_BLACK;
      
   if( whiteIndex > 2 )
      return TOO_MUCH_WHITE_LINES;
   
   if( blackIndex < 2 )
      return NOT_ENOUGH_BLACK_LINES;
   
   
   //----------------- gets a standard
      
    int8 lineWidth = white_lines[0];
    

   
   //----------------- tries to find barcode
   
   if( whiteIndex == 1 && blackIndex == 2 && white_lines[0] > 3 )// a single white line
   {  
      if(lineWidth < 2)
         return WHITE_LINES_SUCK;

      // 2: 00 11 00000   
      if( black_lines[0] <= black_lines[1] + 20 )
      {
         fprintf(USB, "                      DETECTED BARCODE N°2\r\n\r\n");
         return 2;
      }

      // 3: 00000 11 00
      if( black_lines[0] + 20 >= black_lines[1] )
      {
         fprintf(USB, "                      DETECTED BARCODE N°3\r\n\r\n");
         return 3; 
      }
   }
   else if( whiteIndex == 2 && blackIndex == 3 )// 2 white lines
   {
      if( white_lines[0] < 2 || white_lines[1] < 2 || 
          diffBetween( white_lines[0], white_lines[1] ) > 10 )
         return WHITE_LINES_SUCK;
         
      lineWidth = white_lines[0] + white_lines[1];
      lineWidth /= 2;
      fprintf(USB, "\r\n whiteline width = %d", lineWidth);
      
      // 1: 00 11 0 11 00
      //middle black line ~ 2 times narrower than white lines
      if( lineWidth > 14 && black_lines[1] < 10 )
      {
         fprintf(USB, "    DETECTED BARCODE N°1\r\n\r\n");
         return 1;
      }

      // 4: 00 1 000 1 00
      //middle black line ~ 3 times larger than white lines
      if( lineWidth < 11 && black_lines[1] >= 18 )
      {
         fprintf(USB, "    DETECTED BARCODE N°4\r\n\r\n");
         return 4;
      } 

      // 5: 000 1 0 1 000
      //middle black line ~ the same width than white lines
      if( lineWidth < 13 && black_lines[1] < 10 )
      {
         fprintf(USB, "    DETECTED BARCODE N°5\r\n\r\n");
         return 5;
      }


      // 6 - 7 
      //middle black line ~ 2 times larger than white lines
      if( isSizeExpected( (lineWidth * 2), black_lines[1] ) )
      {
         // 6: 000 1 00 1 00
         if( black_lines[0] >= ( lineWidth * 2) + DELTA )
         {
            fprintf(USB, "    DETECTED BARCODE N°6\r\n\r\n");
            return 6;
         }

         // 7: 00 1 00 1 000
         if( black_lines[2] >= ( lineWidth * 2) + DELTA )
            fprintf(USB, "    DETECTED BARCODE N°7\r\n\r\n");
            return 7;
      }
   }
   else
   {
      return NOT_FOUND;
   }
}



void main(void)
{
   // Initialization
   KJunior_init () ;
   HemLinCam_Init (); // currently all this does is sleeping for 1 second...
   cs_init(); // Init camera settings and TV remote control
   //Enable_RS232_Control = 1; // Enable robot control over the serial connection
   
   // Main loop
   while (1)
   {   
  
      HemLinCam_Read_Pixels () ;
      pixels = cr_make_single_pixels_array();
      getLines(pixels);
      printStats();

      fprintf(USB, "\r\n");
      int i = 0;
      /*for(; i < 102; i++)
         fprintf(USB, " %u", pixels[i]);
      fprintf(USB, " \r\n\r\n");*/
      
      barcodeFound = findBarcode();
      /*if( barcodeFound > NOT_FOUND )
         fprintf(USB, "    DETECTED BARCODE N° %d", barcodeFound);*/
      fprintf(USB, "\r\n\r\n");
      sleep_s(1);
      
   } // end while
   
} // end main



