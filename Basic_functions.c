 

void sleep_s(unsigned int32 seconds)
{
    unsigned int32 t1 = KJunior_get_time();
    while( (KJunior_get_time() - t1) < seconds);
}

void rotate_no_move(unsigned int32 angle, int speed)
{
   unsigned int speed_ms = get_speed_in_mms(speed);
   fprintf(USB, "speed ms : %ud \r\n", speed_ms);
   unsigned int32 ms = (unsigned int32) (PERIM * 1000 / speed_ms);
   fprintf(USB, "ms : %Ld \r\n", ms);
   KJunior_set_speed(speed, -speed);
   sleep_ms(ms);
   KJunior_set_speed(0, 0);
   
}

int16 abs(INT16 i)
{
   IF (i < 0)
      RETURN i * -1;

   RETURN i;
}

unsigned int get_speed_in_mms(int32 speed)
{
   return (unsigned int)((speed * 70.0 / 20.0) + 30);
}

void sleep_ms(unsigned int32 ms)
{
    unsigned int32 t1 = KJunior_get_time();
    while( (KJunior_get_time() - t1) < ms);
}
