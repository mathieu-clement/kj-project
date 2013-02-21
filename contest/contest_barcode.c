#include "contest_barcode.h"

#define MIN_WHITE_LENGTH 2
#define WHITE_LIMIT 40

/**
 * Returns the left bound of barcode (index of first black pixel after a minimum
 * width of white pixels).
 * If not found, returns -1.
 */
int8 barcode_left_bound(unsigned char* pixels, int8 threshold)
{
   int8 consecutive_white = 0;
   for(int8 i=0; i < WHITE_LIMIT; i++) {
      if(pixels[i] >= threshold) {
         consecutive_white++;
      }
      if(consecutive_white == MIN_WHITE_LENGTH) {
         fprintf(USB, "white on left!\r\n");
         return i+1;
      } else {
         consecutive_white = 0;
      }
   }
   
   return -1;
}

/**
 * Returns the right bound of barcode (index of first black pixel after a minimum
 * width of white pixels).
 * If not found, returns -1.
 */
int8 barcode_right_bound(unsigned char* pixels, int8 threshold)
{
   int8 consecutive_white = 0;
   for(int8 i=101; i > 101-WHITE_LIMIT; i--) {
      if(pixels[i] >= threshold) {
         consecutive_white++;
      }
      if(consecutive_white == MIN_WHITE_LENGTH) {
      fprintf(USB, "white on right!\r\n");
         return i+1;
      } else {
         consecutive_white = 0;
      }
   }
   
   return -1;
}

/**
 * Detect which barcode is matched by the camera (whose output is provided as argument).
 * 
 * @param pixels 102 pixels (3*34) as read by the linear camera
 * @param threshold above (and including) this value the pixel is considered white,
 *                  otherwise it will be detected as black
 * @return barcode matching the pixels or -1 if there is no match.
 */
int8 detect_barcode(unsigned char* pixels, int8 threshold)
{
    // We suppose that the camera is exactly in front of the barcode.
    // Therefore we don't account for perspective distortion and other naughty problems.
    
    // The base principle is to divide 102 pixels in 9 zones of 11 pixels.
    // (Yeah, 9 x 11 = 99, then the last 3 pixels are ignored.)
    
    // Each zone has the value 1 (white) or 0 (black) based on the average value.
    int8 zones[9];
    
    int8 i = barcode_left_bound(pixels, threshold);
    
    int8 r = barcode_right_bound(pixels, threshold);
    int8 incr = (r-i) / 9.0;
    
    fprintf(USB, "Left=%3d Right=%3d\r\n", i, r);
    
    if(i == -1 || r == -1) {
      return -1;
    }
    
    int8 zoneCounter = 0;
    
    for( ; i <= r; i += incr ) {
        // Compute the zone average
        
        int32 total = 0; // total used to compute the average of the zone
        for(int8 j=0; j < incr; j++) {
            total += pixels[i+j];
        }
        int8 average = total / incr;
        
        zones[zoneCounter++] = average >= threshold;
    }
    
    // DEBUG
    //*
    fprintf(USB, "%d %d %d %d %d %d %d %d %d\r\n", zones[0], 
    zones[1], zones[2], zones[3], zones[4], zones[5], zones[6], zones[7], zones[8]);
    
    
    
    //*/
    
    // Now compare the barcode read and see if it matches any of the 7 known barcodes.
    for (i=1; i <= 7; i++) {
    
        if (compare_array(zones, contest_barcodes, sizeof(zones)/sizeof(zones[0]))) {
            fprintf(USB, "%d MATCHES!\r\n", i);
            // Return the barcode ID if it matches
            return i-1;
        }
    }
    
    // Return -1 if no barcode matches the pixels read from the camera
    return -1;
}

/**
 * Compare two arrays of int1[].
 * 
 * @param arr1 an array of int1[]
 * @param arr2 another array of int1[]. Must be as big as arr1.
 * @param size length of array
 * @return true (1) or (false) if arr1 has the same content as arr2.
 */
int1 compare_array(int1* arr1, int1* arr2, int8 size)
{
    // Unfortunately it looks that CCS Compiler is not POSIX, then memcmp is missing.
    // This is the reason why we re-invent the wheel here...
    
    for(int8 i=0; i < size; i++) {
        if (arr1[i] != arr2[i]) {
            return 0; // false
        }
    }
    
     // Return true if there was no mismatch.
    return 1;
}

