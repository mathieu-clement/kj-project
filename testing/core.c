

enum STATE curr_state; 


// Returns true (1) if one of the side ground sensors is on black.
int1 black_detected()
{
   return KJunior_get_proximity(GROUNDLEFT)  < bw_threshold_left ||
          KJunior_get_proximity(GROUNDRIGHT) < bw_threshold_right;
}

// Returns true (1) if both side ground front sensors are on black.
int1 black_on_both()
{
   return KJunior_get_proximity(GROUNDLEFT)  < bw_threshold_left &&
          KJunior_get_proximity(GROUNDRIGHT) < bw_threshold_right;
}

// Returns true (1) if the left side ground sensors is on black.
int1 black_on_left()
{
   return KJunior_get_proximity(GROUNDLEFT)  < bw_threshold_left;
}

// Returns true (1) if the right side ground sensors is on black.
int1 black_on_right()
{
   return KJunior_get_proximity(GROUNDRIGHT) < bw_threshold_right;
}


//********************************************************//


void turn_left()
{
   if(curr_state == normal_state)
      KJunior_set_speed(0, HIGH_SPEED); 
   else
      KJunior_set_speed(0, SPEED); 
}

void turn_right()
{
   if(curr_state == normal_state)
      KJunior_set_speed(HIGH_SPEED, 0); 
   else
      KJunior_set_speed(SPEED, 0); 
}

void move_forward()
{
   if(curr_state == normal_state)
      KJunior_set_speed(HIGH_SPEED, HIGH_SPEED); 
   else
      KJunior_set_speed(SPEED, SPEED); 
}

void move_backward()
{
   if(curr_state == normal_state)
      KJunior_set_speed(-HIGH_SPEED, -HIGH_SPEED); 
   else
      KJunior_set_speed(-SPEED, -SPEED); 
}
 

void rotate_left(int8 s)
{
   KJunior_set_speed(-s, s);
}

void rotate_right(int8 s)
{
   KJunior_set_speed(s, -s);
}

//********************************************************//

void debug()
{
   fprintf(USB, "Left prox       %04ld, \r\nRight prox      %04ld\r\n", 
      KJunior_get_proximity(GROUNDLEFT),
      KJunior_get_proximity(GROUNDRIGHT));
}

