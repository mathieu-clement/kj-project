 

void sleep_s(unsigned int32 seconds)
{
    unsigned int32 t1 = KJunior_get_time();
    while( (KJunior_get_time() - t1) < seconds);
}

void rotate_no_move(unsigned int32 angle, int speed)
{
   unsigned int speed_ms = get_speed_in_mms(speed);
   fprintf(USB, "speed ms : %ud \r\n", speed_ms);
   unsigned int32 ms = (unsigned int32) (PERIM / speed_ms)  * 1000;
   fprintf(USB, "ms : %Ld \r\n", ms);
   KJunior_set_speed(speed, -speed);
   sleep_ms(ms);
   KJunior_set_speed(0, 0);
   
}

unsigned int get_speed_in_mms(int32 speed)
{
   return (speed * 70 / 20) + 30;
}

void sleep_ms(unsigned int32 ms)
{
    unsigned int32 t1 = KJunior_get_time();
    while( (KJunior_get_time() - t1) < ms);
}
