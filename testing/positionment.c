
int1 do_positioning()
{
   while(! black_on_both() )
   {
      int8 counter = 0;
      debug();

      if( black_on_left() ){
         fprintf(USB, "                 black on left\r\n");
         turn_left();
         counter = 0;
      }else if( black_on_right() ){
         fprintf(USB, "                 black on right\r\n");
         turn_right();
         counter = 0;
      }else{
         counter++;
         if(counter > 5){
           return 0;
           fprintf(USB, "                 POSITION SUCKS\r\n");
         }
      }
    
      sleep_ms(100);
  }//end while
  
  fprintf(USB, "                 POSITION OK\r\n");
  KJunior_set_speed(0,0);
  return 1;
}


unsigned int8 do_rotation_based_on_line()
{
   unsigned int16 counter = 0, limit = 10000000000;
   
   //move_backward();
   //while(!black_on_both());
   unsigned int32 start_time = KJunior_get_time();     
   KJunior_set_speed(5,5);
   
   // Continue rolling until we found white again
   while(black_on_both() && counter < limit) {
      //sleep_ms(10);
      fprintf(USB, "black    %ld    %ld\r\n", 
         KJunior_get_proximity(GROUNDLEFT),
         KJunior_get_proximity(GROUNDRIGHT));
      counter++;
   }   
   // How much time did we stay on that black line?
   unsigned int32 time_on_black = KJunior_get_time() - start_time;
   
   if(counter == limit){
      fprintf(USB, "Time on black: %ld ms\r\n", time_on_black);
      return -1;
   }
   // Debug
   fprintf(USB, "Time on black: %ld ms\r\n", time_on_black);
   // Stop
   KJunior_set_speed(0,0);

   // If time on black over 200 ms:
   // that's the largest line
   if(time_on_black > LINE_TIME_THRESHOLD) {
      // Rotate left
      rotate_90degree_left();
      fprintf(USB, "LARGE LINE DETECTED\r\n");
      return BC_ON_LEFT;
  } else {
      // that's the smallest line
      // Rotate right
      rotate_90degree_right();
      fprintf(USB, "SMALL LINE DETECTED\r\n");
      return BC_ON_RIGHT;
  }
      
}


void do_rotation_back(int1 direction)
{
   if(direction == BC_ON_LEFT){
      rotate_90degree_right();     
   }else{
     rotate_90degree_left();
   }
}


void avoid_black_lines(){
   while(black_detected())
      avoid_obstacles();
}

void rotate_90degree_left()
{
   KJunior_set_speed(-10, 10);
   sleep_ms(1400);
   KJunior_set_speed(0,0);

}


void rotate_90degree_right()
{
   KJunior_set_speed(10, -10);
   sleep_ms(1400);
   KJunior_set_speed(0,0);

}
