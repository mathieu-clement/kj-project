// Returns true (1) if one of the ground front sensors is on black.

int1 black_detected()
{
   return KJunior_get_proximity(GROUNDLEFT)  < bw_threshold_left ||
          KJunior_get_proximity(GROUNDRIGHT) < bw_threshold_right;
}

int1 black_on_both()
{
   return KJunior_get_proximity(GROUNDLEFT)  < bw_threshold_left &&
          KJunior_get_proximity(GROUNDRIGHT) < bw_threshold_right;
}

int1 black_on_left()
{
   return KJunior_get_proximity(GROUNDLEFT)  < bw_threshold_left;
}

int1 black_on_right()
{
   return KJunior_get_proximity(GROUNDRIGHT) < bw_threshold_right;
}


void rotate_left(int8 s)
{
   KJunior_set_speed(-s, s);
}

void rotate_right(int8 s)
{
   KJunior_set_speed(s, -s);
}


void debug()
{
 fprintf(USB, "Left prox      %04ld, \r\nRight prox      %04ld\r\n", 
   KJunior_get_proximity(GROUNDLEFT),
   KJunior_get_proximity(GROUNDRIGHT));
}

