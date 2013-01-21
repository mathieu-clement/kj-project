#ifndef SIMPLE_BEEP
#define SIMPLE_BEEP 1
// This library is useful to make some frickin' noise with the Robot!

#define MUTE      0

#define C_2       1
#define C_SHARP_2 2
#define D_FLAT_2  2
#define D_2       3
#define D_SHARP_2 4
#define E_FLAT_2  4
#define E_2       5
#define F_2       6
#define F_SHARP_2 7
#define G_FLAT_2  7
#define G_2       8
#define G_SHARP_2 9
#define A_FLAT_2  9
#define A_2       10
#define A_SHARP_2 11
#define B_FLAT_2  11
#define B_2       12

#define C_3       13
#define C_SHARP_3 14
#define D_FLAT_3  14
#define D_3       15
#define D_SHARP_3 16
#define E_FLAT_3  16
#define E_3       17
#define F_3       18
#define F_SHARP_3 19
#define G_FLAT_3  19
#define G_3       20
#define G_SHARP_3 21
#define A_FLAT_3  21
#define A_3       22
#define A_SHARP_3 23
#define B_FLAT_3  23
#define B_3       24

#define C_4       25
#define C_SHARP_4 26
#define D_FLAT_4  26
#define D_4       27
#define D_SHARP_4 28
#define E_FLAT_4  28
#define E_4       29
#define F_4       30
#define F_SHARP_4 31
#define G_FLAT_4  31
#define G_4       32
#define G_SHARP_4 33
#define A_FLAT_4  33
#define A_4       34
#define A_SHARP_4 35
#define B_FLAT_4  35
#define B_4       36

#define C_5       37
#define C_SHARP_5 38
#define D_FLAT_5  38
#define D_5       39
#define D_SHARP_5 40
#define E_FLAT_5  40
#define E_5       41
#define F_5       42
#define F_SHARP_5 43
#define G_FLAT_5  43
#define G_5       44
#define G_SHARP_5 45
#define A_FLAT_5  45
#define A_5       46
#define A_SHARP_5 47
#define B_FLAT_5  47
#define B_5       48


void incremental_beep();

/**
 * Returns the duration in ms of the specified note value depending on the tempo.
 *
 * @param value Note value. E.g. 1 for whole note, 2 for half note,
 * 4 for quarter note, 8 for eighth note, 16 for sixteenth note, ...
 * (and also 3 for a dotted quarter note for instance).
 * @param tempo Tempo in beats per minute
 * @returns the duration in ms of the specified note value depending on the tempo. 
 */
float note_length_ms(int8 value, int8 tempo);

void beep_note(int8 note, int8 note_value, int8 tempo);

void beep_blues_scale();

void beep_star_wars();

void beep_badinerie();

#include "simple_beep.c"


#endif
