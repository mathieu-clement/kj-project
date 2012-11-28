
void incremental_beep()
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
 * @returns the duration in ms of the specified note value depending on the tempo. 
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

void beep_note(int8 note, int8 note_value, int8 tempo)
{
   KJunior_beep(note);
   float total_length = note_length_ms(note_value, tempo);
   KJunior_delay_ms(total_length);
   KJunior_beep(MUTE);
   // note spacing by muting in-between
   KJunior_delay_ms(10);
}

#define note_value 4

void beep_blues_scale()
{
   int8 tempo = 120;
  
   beep_note(C_2, note_value, tempo);
   beep_note(E_FLAT_2, note_value, tempo);
   beep_note(F_2, note_value, tempo);
   beep_note(F_SHARP_2, note_value, tempo);
   beep_note(G_2, note_value, tempo);
   beep_note(B_FLAT_2, note_value, tempo);
   beep_note(C_3, note_value, tempo);
}

void beep_star_wars()
{
   int8 tempo = 160;
   
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


