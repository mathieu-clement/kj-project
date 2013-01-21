/**
 * @file
 * 
 * @brief Utilities to play notes with the buzzer
 */

/**
 * Go up the scale very quickly with the buzzer.
 */
void incremental_beep(void)
{
   for(int8 i=0; i<=48; i++)
   {
      KJunior_beep(i);
      KJunior_delay_ms(10);
   }
   
   // Stop buzzing
   KJunior_beep(MUTE);
}

/**
 * Returns the duration in ms of the specified note value depending on the tempo.
 *
 * @param value Note value. E.g. 1 for whole note, 2 for half note,
 * 4 for quarter note, 8 for eighth note, 16 for sixteenth note, ...
 * (and also 3 for a dotted quarter note for instance).
 * @param tempo Tempo in beats per minute
 * @return the duration in ms of the specified note value depending on the tempo. 
 */
float note_length_ms(int8 value, int8 tempo)
{
   // We know the tempo means : how many quarters note are they in one minute?
   // E.g. at 60 bpm, one quarter note has a duration of 1 second.
   // at 120 bpm, one quarter note has a duration of 0.5 second
   
   // The formula is: (60 / tempo) * 4 * (1/value) [seconds]
   // As we want the answer in miliseconds, we multiply by 1000.
   float length = 240000 / tempo / value;
   fprintf(USB, "Value: 1/%d at %d bpm is %f\r\n", value, tempo, length);
   return length;
}

// Last number shown with leds (see binary led transcoder.c)
int8 bp_last_led = 0;

/**
 * Toggle leds to give visual feedback of the playing tune.
 */
void toggle_led(void)
{
   // This function has to be lightning FAST!

   if(bp_last_led >= 0 && bp_last_led < 3)
   {
      bp_last_led++;
   }
   else
   {
      bp_last_led = 0;
   }
   
   if(bp_last_led == 0) {
      KJunior_led_left(1);
      KJunior_led_right(0);
   } else if (last_led == 1) {
      KJunior_led_left(0);
      KJunior_led_frontleft(1);
   } else if (last_led == 2) {
      KJunior_led_frontleft(0);
      KJunior_led_frontright(1);
   } else {
      KJunior_led_frontright(0);
      KJunior_led_right(1);
   }
}

/**
 * Beep a note.
 * 
 * @param note the note to play (see simple_beep.h constants)
 * @param note_value the note value (e.g. 4 for a quarter note, 1 for a whole note)
 * @param tempo the tempo
 */
void beep_note(int8 note, int8 note_value, int8 tempo)
{
   KJunior_beep(note);
   float total_length = note_length_ms(note_value, tempo);
   toggle_led();
   sleep_ms(total_length);
   KJunior_beep(MUTE);
   // note spacing by muting in-between
   sleep_ms(10);
}

/**
 * Play the Blues scale (C - Eb - F - F# - G - Bb - C)
 */
void beep_blues_scale(void)
{
   int8 tempo = 120;
   int8 note_value = 4;
  
   beep_note(C_2, note_value, tempo);
   beep_note(E_FLAT_2, note_value, tempo);
   beep_note(F_2, note_value, tempo);
   beep_note(F_SHARP_2, note_value, tempo);
   beep_note(G_2, note_value, tempo);
   beep_note(B_FLAT_2, note_value, tempo);
   beep_note(C_3, note_value, tempo);
}

/**
 * Play Star wars tune
 */
void beep_star_wars(void)
{
   int8 tempo = 100;
   
   int8 triolet= 14;
   
   // Intro
   beep_note(D_2, triolet, tempo);
   beep_note(D_2, triolet, tempo);
   beep_note(D_2, triolet, tempo);
   
   // Theme
   beep_note(G_2, 2, tempo);
   beep_note(D_3, 2, tempo);
   
   beep_note(C_3, triolet, tempo);
   beep_note(B_2, triolet, tempo);
   beep_note(A_2, triolet, tempo);
   
   beep_note(G_3, 2, tempo),
   beep_note(D_3, 4, tempo);
   
   beep_note(C_3, triolet, tempo);
   beep_note(B_2, triolet, tempo);
   beep_note(A_2, triolet, tempo);
   
   beep_note(G_3, 2, tempo),
   beep_note(D_3, 4, tempo);
   
   beep_note(C_3, triolet, tempo);
   beep_note(B_2, triolet, tempo);
   beep_note(C_3, triolet, tempo);
   
   beep_note(A_2, 2, tempo);
   
   beep_note(D_2, 6, tempo);
   beep_note(D_2, 16, tempo);
   
   
   // Theme again
   beep_note(G_2, 2, tempo);
   beep_note(D_3, 2, tempo);
   
   beep_note(C_3, triolet, tempo);
   beep_note(B_2, triolet, tempo);
   beep_note(A_2, triolet, tempo);
   
   beep_note(G_3, 2, tempo),
   beep_note(D_3, 4, tempo);
   
   beep_note(C_3, triolet, tempo);
   beep_note(B_2, triolet, tempo);
   beep_note(A_2, triolet, tempo);
   
   beep_note(G_3, 2, tempo),
   beep_note(D_3, 4, tempo);
   
   beep_note(C_3, triolet, tempo);
   beep_note(B_2, triolet, tempo);
   beep_note(C_3, triolet, tempo);
   
   beep_note(A_2, 2, tempo);
   beep_note(MUTE, 4, tempo);
   
   beep_note(D_2, 6, tempo);
   beep_note(D_2, 16, tempo);
   
   // Secundo
   beep_note(E_2, 3, tempo);
   beep_note(E_2, 8, tempo);
   beep_note(C_3, 8, tempo);
   beep_note(B_2, 8, tempo);
   beep_note(A_2, 8, tempo);
   beep_note(G_2, 8, tempo);
   
   beep_note(G_2, triolet, tempo);
   beep_note(A_2, triolet, tempo);
   beep_note(B_2, triolet, tempo);
   beep_note(A_2, 6, tempo);
   beep_note(E_2, 16, tempo);
   beep_note(F_SHARP_2, 4, tempo);
   
   beep_note(D_2, 6, tempo);
   beep_note(D_2, 16, tempo); 
   
   beep_note(E_2, 3, tempo);
   beep_note(E_2, 8, tempo);
   beep_note(C_3, 8, tempo);
   beep_note(B_2, 8, tempo);
   beep_note(A_2, 8, tempo);
   beep_note(G_2, 8, tempo);
   
   beep_note(D_3, 3, tempo);
   beep_note(A_2, 16, tempo);
   beep_note(A_2, 2, tempo);
   
   beep_note(MUTE, 4, tempo);
   beep_note(G_2, 4, tempo);
   beep_note(B_2, 4, tempo);
   beep_note(D_2, 4, tempo);
   beep_note(G_3, 8, tempo);
   beep_note(G_3, 8, tempo);
}

/**
 * Play Bach Badinerie (BWV1067)
 */
void beep_badinerie(void)
{

int8 tempo = 130;

// Pause 2 seconds
sleep_ms(2000);

// Repeat two times
for(int i=0; i<2; i++)
{
beep_note(B_3, 8, tempo);
beep_note(D_4, 16, tempo);
beep_note(B_3, 16, tempo);
beep_note(F_SHARP_3, 8, tempo);
beep_note(B_3, 16, tempo);
beep_note(F_SHARP_3, 16, tempo);
beep_note(D_3, 8, tempo);
beep_note(F_SHARP_3, 16, tempo);
beep_note(D_3, 16, tempo);
beep_note(B_2, 4, tempo);

beep_note(F_SHARP_2, 16, tempo);
beep_note(B_2, 16, tempo);
beep_note(D_3, 16, tempo);
beep_note(B_2, 16, tempo);
beep_note(C_SHARP_3, 16, tempo);
beep_note(B_2, 16, tempo);
beep_note(C_SHARP_3, 16, tempo);
beep_note(B_2, 16, tempo);
beep_note(A_SHARP_2, 16, tempo);
beep_note(C_SHARP_3, 16, tempo);
beep_note(E_3, 16, tempo);
beep_note(C_SHARP_3, 16, tempo);
beep_note(D_3, 8, tempo);
beep_note(B_2, 8, tempo);

// very first section again
beep_note(B_3, 8, tempo);
beep_note(D_4, 16, tempo);                                                                           
beep_note(B_3, 16, tempo);                                                                           
beep_note(F_SHARP_3, 8, tempo);                                                                      
beep_note(B_3, 16, tempo);                                                                           
beep_note(F_SHARP_3, 16, tempo);                                                                     
beep_note(D_3, 8, tempo);
beep_note(F_SHARP_3, 16, tempo);
beep_note(D_3, 16, tempo);
beep_note(B_2, 4, tempo);

beep_note(D_3, 8, tempo);
beep_note(D_3, 8, tempo);
beep_note(D_3, 8, tempo); // 2nd row
beep_note(D_3, 8, tempo);
beep_note(B_3, 8, tempo);
beep_note(D_3, 8, tempo);
// trille
beep_note(D_3, 32, tempo);
beep_note(E_3, 32, tempo);
beep_note(D_3, 32, tempo);
beep_note(E_3, 32, tempo);
beep_note(C_SHARP_3, 8, tempo);

beep_note(F_SHARP_3, 8, tempo);
beep_note(F_SHARP_3, 8, tempo);
beep_note(F_SHARP_3, 8, tempo);
beep_note(F_SHARP_3, 8, tempo);
beep_note(D_4, 8, tempo);
beep_note(F_SHARP_3, 8, tempo);
// trille
beep_note(F_SHARP_3, 32, tempo);
beep_note(G_SHARP_3, 32, tempo);
beep_note(F_SHARP_3, 32, tempo);
beep_note(G_SHARP_3, 32, tempo);
beep_note(F_3, 8, tempo); // E#

beep_note(C_SHARP_3, 16, tempo);
beep_note(F_SHARP_3, 16, tempo);
beep_note(A_3, 16, tempo);
beep_note(F_SHARP_3, 16, tempo);
beep_note(G_SHARP_3, 16, tempo);
beep_note(F_SHARP_3, 16, tempo);
beep_note(G_SHARP_3, 16, tempo);
beep_note(F_SHARP_3, 16, tempo);
beep_note(F_3, 16, tempo); // E#
beep_note(G_SHARP_3, 16, tempo);
beep_note(B_3, 16, tempo);
beep_note(G_SHARP_3, 16, tempo);

beep_note(A_3, 16, tempo);
beep_note(G_SHARP_3, 16, tempo);
beep_note(A_3, 16, tempo);
beep_note(G_SHARP_3, 16, tempo);
beep_note(F_SHARP_3, 16, tempo);
beep_note(A_3, 16, tempo);
beep_note(F_SHARP_3, 16, tempo);
beep_note(F_3, 16, tempo); // E#

beep_note(F_SHARP_3, 16, tempo); // E#
beep_note(B_3, 16, tempo);
beep_note(F_SHARP_3, 16, tempo);
beep_note(F_3, 16, tempo); // E#
beep_note(F_SHARP_3, 16, tempo);
beep_note(C_SHARP_4, 16, tempo);
beep_note(F_SHARP_3, 16, tempo);
beep_note(E_3, 16, tempo);
beep_note(F_SHARP_3, 16, tempo);
beep_note(D_4, 16, tempo);
beep_note(F_SHARP_3, 16, tempo);
beep_note(F_3, 16, tempo); // E#
beep_note(F_SHARP_3, 16, tempo);
beep_note(D_4, 16, tempo);
beep_note(C_SHARP_4, 16, tempo);
beep_note(B_3, 16, tempo);
beep_note(C_SHARP_4, 16, tempo);
beep_note(A_3, 16, tempo);
beep_note(G_SHARP_3, 16, tempo);
beep_note(F_SHARP_3, 16, tempo);
beep_note(A_3, 8, tempo);
// trille
beep_note(G_SHARP_3, 32, tempo);
beep_note(A_3, 32, tempo);
beep_note(G_SHARP_3, 32, tempo);
beep_note(A_3, 32, tempo);
beep_note(F_SHARP_3, 4, tempo);
} // end for repeat two times (1st part)

/*
   ##################
   #### 2nd PART ####
   ##################
*/
for(int i2=0; i2<2; i2++)
{

beep_note(F_SHARP_3, 8, tempo);
beep_note(A_3, 16, tempo);
beep_note(F_SHARP_3, 16, tempo);
beep_note(C_SHARP_3, 8, tempo);
beep_note(F_SHARP_3, 16, tempo);
beep_note(C_SHARP_3, 16, tempo);
beep_note(A_2, 8, tempo);
beep_note(C_SHARP_3, 16, tempo);
beep_note(A_2, 16, tempo);
beep_note(F_SHARP_2, 4, tempo);

beep_note(C_3, 8, tempo); // C becarre
beep_note(B_2, 8, tempo);
beep_note(E_3, 8, tempo);
beep_note(D_SHARP_3, 16, tempo);
beep_note(F_SHARP_3, 16, tempo);
beep_note(A_3, 8, tempo);
beep_note(G_3, 16, tempo);
beep_note(F_SHARP_3, 16, tempo);
beep_note(G_3, 8, tempo);
beep_note(E_3, 8, tempo);

beep_note(G_3, 8, tempo);
beep_note(B_3, 16, tempo);
beep_note(G_3, 16, tempo);
beep_note(E_3, 8, tempo);
beep_note(G_3, 16, tempo);                                        
beep_note(E_3, 16, tempo);                                        
beep_note(C_SHARP_3, 8, tempo);                                   
beep_note(E_3, 16, tempo);                                        
beep_note(C_SHARP_3, 16, tempo);                                  
beep_note(A_2, 4, tempo);
beep_note(MUTE, 16, tempo); // mute instead of quarter + sixteenth

beep_note(D_3, 16, tempo);
beep_note(F_SHARP_3, 16, tempo);
beep_note(D_3, 16, tempo);
beep_note(E_3, 16, tempo);
beep_note(D_3, 16, tempo);
beep_note(E_3, 16, tempo);
beep_note(D_3, 16, tempo);
beep_note(C_SHARP_3, 16, tempo);
beep_note(E_3, 16, tempo);
beep_note(G_3, 16, tempo);
beep_note(E_3, 16, tempo);
beep_note(F_SHARP_3, 16, tempo);
beep_note(E_3, 16, tempo);
beep_note(F_SHARP_3, 16, tempo);
beep_note(E_3, 16, tempo);
beep_note(D_3, 16, tempo);
beep_note(F_SHARP_3, 16, tempo);
beep_note(D_3, 16, tempo);
beep_note(C_SHARP_3, 16, tempo);

beep_note(D_3, 16, tempo);
beep_note(G_3, 16, tempo); // !
beep_note(D_3, 16, tempo);
beep_note(C_SHARP_3, 16, tempo);
beep_note(D_3, 16, tempo);
beep_note(A_3, 16, tempo); // !
beep_note(D_3, 16, tempo);
beep_note(C_SHARP_3, 16, tempo);
beep_note(D_3, 16, tempo);
beep_note(B_3, 16, tempo); // !
beep_note(D_3, 16, tempo);
beep_note(C_SHARP_3, 16, tempo);

beep_note(D_3, 16, tempo);
beep_note(B_3, 16, tempo);
beep_note(A_3, 16, tempo);
beep_note(G_3, 16, tempo);
beep_note(A_3, 16, tempo);
beep_note(F_SHARP_3, 16, tempo);
beep_note(E_3, 16, tempo);
beep_note(D_3, 16, tempo);
beep_note(F_SHARP_3, 8, tempo);
// trille
beep_note(E_3, 32, tempo);
beep_note(F_SHARP_3, 32, tempo);
beep_note(E_3, 32, tempo);
beep_note(F_SHARP_3, 32, tempo);
beep_note(D_3, 4, tempo);

beep_note(F_SHARP_3, 8, tempo);
beep_note(F_SHARP_3, 8, tempo);
beep_note(F_SHARP_3, 8, tempo);
beep_note(F_SHARP_3, 8, tempo);
beep_note(D_4, 8, tempo);
beep_note(F_SHARP_3, 8, tempo);
// trille
beep_note(F_SHARP_3, 32, tempo);
beep_note(G_3, 32, tempo);
beep_note(F_SHARP_3, 32, tempo);
beep_note(G_3, 32, tempo);
beep_note(E_3, 8, tempo);

beep_note(E_3, 8, tempo);
beep_note(E_3, 8, tempo);
beep_note(E_3, 8, tempo);
beep_note(E_3, 8, tempo);
beep_note(C_SHARP_4, 8, tempo);
beep_note(E_3, 8, tempo);
// trille
beep_note(E_3, 32, tempo);
beep_note(F_SHARP_3, 32, tempo);
beep_note(E_3, 32, tempo);
beep_note(F_SHARP_3, 32, tempo);
beep_note(D_3, 4, tempo);
beep_note(D_3, 8, tempo);

beep_note(B_3, 8, tempo);
beep_note(D_4, 16, tempo);
beep_note(B_3, 16, tempo);
beep_note(G_3, 6, tempo); // noire pointée
beep_note(B_3, 32, tempo);
beep_note(A_3, 32, tempo);
beep_note(G_3, 32, tempo);
beep_note(F_SHARP_3, 32, tempo);

beep_note(E_3, 6, tempo); // noire pointée
beep_note(G_3, 32, tempo);
beep_note(F_SHARP_3, 32, tempo);
beep_note(E_3, 32, tempo);
beep_note(D_3, 32, tempo);
beep_note(C_3, 16, tempo); // do bécarre
beep_note(E_3, 16, tempo);
beep_note(G_3, 16, tempo);
beep_note(E_3, 16, tempo);
beep_note(C_3, 16, tempo); // do bécarre (mesure)
beep_note(B_2, 16, tempo);
beep_note(C_3, 16, tempo); // do bécarre (mesure)
beep_note(B_2, 16, tempo);

beep_note(A_SHARP_2, 8 tempo);
beep_note(F_SHARP_2, 8, tempo);
beep_note(G_2, 8 tempo);
beep_note(F_SHARP_2, 8, tempo);

beep_note(B_2, 8, tempo);
beep_note(A_SHARP_2, 16, tempo);
beep_note(C_SHARP_3, 16, tempo);
beep_note(E_3, 8, tempo);
beep_note(D_3, 16, tempo);
beep_note(C_SHARP_3, 16, tempo);
beep_note(D_3, 8, tempo);

beep_note(B_2, 32, tempo);
beep_note(C_SHARP_3, 32, tempo);
beep_note(D_3, 32, tempo);
beep_note(E_3, 32, tempo);
beep_note(F_SHARP_3, 8, tempo);

beep_note(D_3, 16, tempo);
beep_note(F_SHARP_3, 16, tempo);
beep_note(B_3, 8, tempo);
beep_note(F_SHARP_3, 8, tempo);

beep_note(E_3, 16, tempo);
beep_note(D_3, 16, tempo);
beep_note(C_SHARP_3, 16, tempo);
beep_note(D_3, 16, tempo);

// Very last note is special and played outside the for loop
if(i2==0){ 
   beep_note(B_2, 4, tempo);
   beep_note(MUTE, 2, tempo);
}

} // end for repeat two times (2nd part)

// Ending / CODA
beep_note(MUTE, 4, tempo);
beep_note(C_SHARP_3, 4, tempo);
beep_note(B_2, 2, tempo);

} // end beep_badinerie()