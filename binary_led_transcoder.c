/**
 * Display the specified number in binary format with the four supplied LEDs.
 *
 * @param number A number from 0 to 9 (limitation due to the TV remote)
 */
void led_display_number(int8 number)
{
   // binary code of decimal numbers from 0 to 9
   int8 codes[10][4] = {
                  {0,0,0,0}, // 0
                  {0,0,0,1}, // 1
                  {0,0,1,0}, // 2
                  {0,0,1,1}, // 3
                  {0,1,0,0}, // 4
                  {0,1,0,1}, // 5
                  {0,1,1,0}, // 6
                  {0,1,1,1}, // 7
                  {1,0,0,0}, // 8
                  {1,0,0,1}  // 9
   };
   
   // Lit the leds accordling to the table above
   KJunior_led_left(codes[number][0]);
   KJunior_led_frontleft(codes[number][1]);
   KJunior_led_frontright(codes[number][2]);
   KJunior_led_right(codes[number][3]);
}

