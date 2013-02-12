#include "KJunior.h"

#include "basic_functions.h"
#include "tv_remote_utils.h"
#include "binary_led_transcoder.h"

#define SPEED 5
#define stop() KJunior_set_speed(0, 0); led_display_number(6)
#define turn_left() KJunior_set_speed(0, SPEED); led_display_number(8)
#define turn_right() KJunior_set_speed(SPEED, 0); led_display_number(1)
#define move_forward() KJunior_set_speed(SPEED, SPEED); led_display_number(6)
#define left_on_black() (KJunior_get_proximity(GROUNDFRONTLEFT) < THRESHOLD) 
#define right_on_black() (KJunior_get_proximity(GROUNDFRONTRIGHT) < THRESHOLD)
#define is_up() (KJunior_get_proximity(GROUNDFRONTRIGHT) < 1000 && KJunior_get_proximity(GROUNDFRONTRIGHT) < 1000)

enum ACTION
{
   STOP, MOVE_FORWARD, TURN_LEFT, TURN_RIGHT
};

enum ACTION last_action = STOP;

int8 counter = 0;
int8 before_move_forward_counter = 0;

int16 THRESHOLD = 2800;

void main(void)
{ 
   // Initialization
   KJunior_init () ;
   Enable_RS232_Control = 1; // Enable robot control over the serial connection
   // KJunior_config_tv_remote_control (ENABLE) ;
   
   // Main loop
   while (1)
   {
      if((SerialCommandOK == 1) && (Enable_RS232_Control == 1))                    // Test if a Serial Command was received ...
         SerialCommandHandler();
         
         
         
      if (KJunior_get_tv_data() == TV_CH_PLUS) {
         if(THRESHOLD < 4100) {
            THRESHOLD += 100;
         }
      } else if (KJunior_get_tv_data() == TV_CH_MINUS) {
         if(THRESHOLD != 0) {
            THRESHOLD -= 100;
         }
      } // else Rien à taper! Apprends à utiliser la télécommande c*****
        
      TV_DATA = 0;  
        
      //fprintf(USB, "Threshold: %ld\r\n", THRESHOLD);        
      //fprintf(BT, "Threshold: %ld\r\n", THRESHOLD);
        
      fprintf(USB, "Threshold: %ld, Left: %ld, Right: %ld\r\n", THRESHOLD,
         KJunior_get_proximity(GROUNDFRONTLEFT),KJunior_get_proximity(GROUNDFRONTRIGHT));
      fprintf(BT, "Threshold: %ld, Left: %ld, Right: %ld\r\n", THRESHOLD,
         KJunior_get_proximity(GROUNDFRONTLEFT),KJunior_get_proximity(GROUNDFRONTRIGHT));
      if(is_up()){
         stop();
         last_action = STOP;
         counter = 0;
         continue;
      }else if(left_on_black() && right_on_black()) {
      
         if(counter < 20) // 5000 (5 seconds) / sleep_time
         {
            counter++;
            switch(last_action)
            {
               case MOVE_FORWARD:
                  move_forward();
                  break;
                  
               case TURN_LEFT:
                  turn_left();
                  break;
                  
               case TURN_RIGHT:
                  turn_right();
                  break;
            
               case STOP:
                  stop();
            }
         } else {
         last_action = STOP;
         stop();
         }
      } else if (left_on_black()) {
         turn_right();
         last_action = TURN_RIGHT;
         counter = 0;
      } else if (right_on_black()) {
         turn_left();
         last_action = TURN_LEFT;
         counter = 0;
      } else { // white everywhere
         if((last_action == TURN_LEFT || last_action == TURN_RIGHT ) && before_move_forward_counter < 4 ) {
            before_move_forward_counter++;          
         } else {
             move_forward();
            last_action = MOVE_FORWARD;
            counter = 0;
            before_move_forward_counter = 0;
         }
         
      }
         
      sleep_ms(300);
   } // end while
}
