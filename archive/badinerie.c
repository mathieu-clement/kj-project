
void beep_badinerie()
{

int8 tempo = 120;

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
beep_note(C_3, 8, tempo);

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
beep_note(F_3, 8, tempo); // E#

// (ici: deuxième partie de double-croche liée)
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
// TRILLE
beep_note(G_SHARP_3, 32, tempo);
beep_note(A_SHARP_3, 32, tempo);
beep_note(G_SHARP_3, 32, tempo);
beep_note(A_SHARP_3, 32, tempo);
beep_note(F_SHARP, 4, tempo);
} // end for repeat two times


/*
beep_note(_3, 16, tempo);
beep_note(_3, 16, tempo);
beep_note(_3, 16, tempo);
beep_note(_3, 16, tempo);
beep_note(_3, 16, tempo);
beep_note(_3, 16, tempo);
beep_note(_3, 16, tempo);
beep_note(_3, 16, tempo);
beep_note(_3, 16, tempo);
beep_note(_3, 16, tempo);
beep_note(_3, 16, tempo);
beep_note(_3, 16, tempo);
beep_note(_3, 16, tempo);
beep_note(_3, 16, tempo);
beep_note(_3, 16, tempo);
beep_note(_3, 16, tempo);
beep_note(_3, 16, tempo);
beep_note(_3, 16, tempo);
beep_note(_3, 16, tempo);
beep_note(_3, 16, tempo);
beep_note(_3, 16, tempo);
beep_note(_3, 16, tempo);
beep_note(_3, 16, tempo);
beep_note(_3, 16, tempo);
beep_note(_3, 16, tempo);
beep_note(_3, 16, tempo);
*/

} // end beep_badinerie()
