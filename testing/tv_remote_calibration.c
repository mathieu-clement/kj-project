/**
 * Init program to read camera settings from TV remote and set them.
 */
void calibrate_thresholds(void)
{
   // Force TV remote value to 60, which is the '1' key
   // because exposition time must be 1 by default
   TV_DATA = 0;
   
   while(1)
   { 
   
      while(KJunior_get_tv_data() != TV_CH_PLUS){
         
         debug();
         fprintf(USB, "threshold left = %4ld\r\n", bw_threshold_left);
         
         if(KJunior_get_tv_data() == TV_POWER) return;
         
         if(KJunior_get_tv_data() == TV_VOL_PLUS && bw_threshold_left < 4000){
            bw_threshold_left += 10;
            
         }else if(KJunior_get_tv_data() == TV_VOL_Minus && bw_threshold_left > 0){
            bw_threshold_left -= 10; 
         }
         
         TV_DATA = 0;
         sleep_ms(100);
         
      }//end while
      
      
      TV_DATA = 0;
      
      
      while(KJunior_get_tv_data() != TV_CH_PLUS){
         
         debug();
         fprintf(USB, "threshold right = %4ld\r\n", bw_threshold_right);
         
         if(KJunior_get_tv_data() == TV_POWER) return;
         
         if(KJunior_get_tv_data() == TV_VOL_PLUS && bw_threshold_right < 4000){
            bw_threshold_right += 10; 
            
         }else if(KJunior_get_tv_data() == TV_VOL_Minus && bw_threshold_right > 0){
            bw_threshold_right -= 10;
         }
         
         TV_DATA = 0;
         sleep_ms(100);
         
      }//end while
      TV_DATA = 0;
      
   }//end while
      
   return;
}

void calibrate_camera()
{
   TV_DATA = 0;
   
   while (KJunior_get_tv_data() != TV_POWER)
   {    
     TV_DATA = 0;
     
      HemLinCam_Read_Pixels () ;
      pixels = cr_make_single_pixels_array();
      getLines(pixels);
      printStats();

      fprintf(USB, "\r\n");
      fprintf(USB, "distance  : %ld \r\n", KJunior_get_proximity(FRONT));
      fprintf(USB, "brightness: %ld \r\n", KJunior_get_brightness(FRONT));
      int i = 0;
      /*for(; i < 102; i++)
         fprintf(USB, " %u", pixels[i]);
      fprintf(USB, " \r\n\r\n");*/
      
      barcodeFound = findBarcode();
      
      if( barcodeFound > NOT_FOUND )
      {
         fprintf(USB, "    DETECTED BARCODE N° %d", barcodeFound);
      }
      fprintf(USB, "\r\n\r\n");
      sleep_s(1);
      
   } // end while
}


void calibrate_rotations(void)
{
   // Force TV remote value to 60, which is the '1' key
   // because exposition time must be 1 by default

   TV_DATA = 0;
   
   while(KJunior_get_tv_data() != TV_VOL_PLUS);   
   TV_DATA = 0;
   unsigned int32 start_time = KJunior_get_time();
   KJunior_set_speed(-10, 10);
   while(KJunior_get_tv_data() != TV_VOL_MINUS);
   fprintf(USB, "rotation time: %ld\r\n",KJunior_get_time() - start_time);
   TV_DATA = 0;
   KJunior_set_speed(0,0);
    
   return;
}

