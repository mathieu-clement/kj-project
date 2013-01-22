
/**
 * Init program to read camera settings from TV remote and set them.
 */
void cs_init(void)
{
   // Force TV remote value to 60, which is the '1' key
   // because exposition time must be 1 by default
   TV_DATA = 60;
   // We use leds to show the exposition (just for fun!)
   led_display_number (cr_exposition_time) ;
   // Enable TV remote
   KJunior_config_tv_remote_control (ENABLE) ;
}

/**
 * Reset the last pressed key of the TV remote.
 * This is needed to detect multiple presses of the very same key.
 */
void cs_reset_tv_remote(void)
{
  TV_DATA = 0; // important trick to know when using TV remote !
}

/**
 * Returns true if user pressed the key on the TV remote control to set a greater exposition time.
 */
int1 cs_exp_time_up(void)
{
   return KJunior_get_tv_data() == TV_CH_PLUS;
}

/**
 * Returns true if user pressed the key on the TV remote control to set a smaller exposition time.
 */
int1 cs_exp_time_down(void)
{
   return KJunior_get_tv_data() == TV_CH_MINUS;
}

/**
 * Returns true if user pressed the power key on the TV remote control 
 */
int1 cs_power_button(void) {
   return KJunior_get_tv_data() == TV_POWER;
}

/**
 * Returns true if user pressed the key on the TV remote control to set a greater threshold value.
 */
int1 cs_threshold_up(void) {
   return KJunior_get_tv_data() == TV_VOL_PLUS;
}

/**
 * Returns true if user pressed the key on the TV remote control to set a smaller threshold value.
 */
int1 cs_threshold_down(void) {
   return KJunior_get_tv_data() == TV_VOL_MINUS;
}

/**
 * Read key pressed on the TV remote control and set the corresponding camera setting
 * accordingly.
 */
void cs_set_camera_with_tv_remote(void)
{
     // Reset camera settings to default values
     if(KJunior_get_tv_data() == TV_MUTE)
     {
         cr_exposition_time = 1;
         led_display_number(cr_exposition_time);
         cr_threshold = 120;
         cr_threshold_enabled = false;
         HemLinCam_Set_Led_State(cr_threshold_enabled);
     }  
        
      // POWER_BUTTON => Activate/Disable threshold. Is disabled by default.
      if(cs_power_button())
      {
         // Toggle threshold
         cr_threshold_enabled = !cr_threshold_enabled;
         
         // Enable / Disable On/Off LED
         HemLinCam_Set_Led_State(cr_threshold_enabled);
      }
      
      // Exposition time UP
      if(cs_exp_time_up())
      {
         // We don't check for 255 (max value), user won't try that because
         // image is already full white around 10-15...
         cr_exposition_time++;
         
	 // Set the exposition time for real
         HemLinCam_Set_Exposition_Time(cr_exposition_time);
         // Show exposition time with LEDs
         // 16 will be shown as 0, 17 as 1, 18 as 2, ... (modulo 16)
         led_display_number(cr_exposition_time % 16);
      }
      
      // Exposition time DOWN
      if(cs_exp_time_down())
      {
         if(exposition_time != 0) // do not go below 0
         {
            exposition_time--;
         }
         
         // Set the exposition time for real
         HemLinCam_Set_Exposition_Time(exposition_time);
         led_display_number(cr_exposition_time % 16);
      }
      
      // Threshold UP
      if(cs_threshold_up())
      {
         // Do not go over 240
         if(cr_threshold != 240)
         {
            threshold += CS_THRESHOLD_INCREMENT; // Move threshold 40 up
         }
         
         HemLinCam_Set_Threshold(cr_threshold);
      }
      
      // Threshold DOWN
      if(cs_threshold_down())
      {
         // Do not go below 0
         if(cr_threshold != 0)
         {
            cr_threshold -= CS_THRESHOLD_INCREMENT;
         }
         
         HemLinCam_Set_Threshold(cr_threshold);
      }
}