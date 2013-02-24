
#include "contest_beep.h"

void beep_la_marseillaise(int8 tempo)
{
    // Allons en-
    beep_note ( D_2, 16, tempo);
    beep_note ( D_2, 12, tempo);
    beep_note ( D_2, 16, tempo);
    
    // -fants de la Pa-
    beep_note ( G_2, 4, tempo);
    beep_note ( G_2, 4, tempo);
    beep_note ( A_2, 4, tempo);
    beep_note ( A_2, 4, tempo);
    
    // -trie, Le jour de
    beep_note ( D_3, 3, tempo);
    beep_note ( B_2, 8, tempo);
    beep_note ( G_2, 12, tempo);
    beep_note ( G_2, 16, tempo);
    beep_note ( B_2, 12, tempo);
    beep_note ( G_2, 16, tempo);
    
    // gloire est arri-
    beep_note ( E_2, 4, tempo);
    beep_note ( C_2, 2, tempo);
    beep_note ( A_2, 12, tempo);
    beep_note ( F_SHARP_2, 16, tempo);
    
    // vé. Contre
    beep_note ( G_2, 2, tempo);
    beep_note ( MUTE, 4, tempo);
    beep_note ( G_2, 12, tempo);
    beep_note ( A_2, 16, tempo);
    
    // nous, de la tyran-
    beep_note ( B_2, 4, tempo);
    beep_note ( B_2, 4, tempo);
    beep_note ( B_2, 4, tempo);
    beep_note ( C_3, 12, tempo);
    beep_note ( B_2, 16, tempo);
    
    // -nie, L'étendard
    beep_note ( B_2, 8, tempo);
    beep_note ( A_2, 8, tempo);
    beep_note ( A_2, 4, tempo);
    beep_note ( MUTE, 4, tempo);
    beep_note ( A_2, 8, tempo);
    beep_note ( A_2, 12, tempo);
    beep_note ( B_2, 16, tempo);
    
    // sanglant est le-
    beep_note ( C_3, 4, tempo);
    beep_note ( C_3, 4, tempo);
    beep_note ( C_3, 4, tempo);
    beep_note ( D_3, 12, tempo);
    beep_note ( C_3, 16, tempo);
    
    // vé, l'étendard
    beep_note ( B_2, 2, tempo);
    beep_note ( MUTE, 4, tempo);
    beep_note ( D_3, 8, tempo);
    beep_note ( D_3, 12, tempo);
    beep_note ( D_3, 16, tempo);
    
    // sanglant est le-
    beep_note ( D_3, 4, tempo);
    beep_note ( B_2, 12, tempo);
    beep_note ( G_2, 16, tempo);
    beep_note ( D_3, 4, tempo);
    beep_note ( B_2, 12, tempo);
    beep_note ( G_2, 16, tempo);
    
    // vé...
    beep_note ( D_2, 2, tempo);
    
} // end beep_la_marseillaise()

void beep_barcode(int8 barcode_id)
{
    int8 tempo = 160;
    
    switch(barcode_id) {
        case 1:
            // C - E - G - C
            beep_note(C_2, 4, tempo);
            beep_note(E_2, 4, tempo);
            beep_note(G_2, 4, tempo);
            beep_note(C_3, 4, tempo);
            break;
        case 2:
            // Au clair de la lune
            beep_note(C_3, 4, tempo);
            beep_note(C_3, 4, tempo);
            beep_note(C_3, 4, tempo);
            beep_note(D_3, 4, tempo);
            beep_note(E_3, 2, tempo);
            beep_note(D_3, 2, tempo);
            beep_note(C_3, 4, tempo);
            break;
        case 3:
            // Switzerland national anthem
            beep_note(C_3, 12, tempo);
            beep_note(C_3, 16, tempo);
            beep_note(C_3, 8, tempo);
            beep_note(F_3, 8, tempo);
            beep_note(F_3, 12, tempo);
            beep_note(E_3, 16, tempo);
            beep_note(E_3, 4, tempo);
            break;
        case 4:
            // La danse des canards
            beep_note(G_3, 4, tempo);
            beep_note(G_3, 4, tempo);
            beep_note(A_3, 4, tempo);
            beep_note(A_3, 4, tempo);
            beep_note(E_3, 4, tempo);
            beep_note(E_3, 4, tempo);
            beep_note(G_3, 4, tempo);
            break;
        case 5:
            // We are the champions
            beep_note(C_3, 4, tempo);
            beep_note(B_2, 8, tempo);
            beep_note(C_3, 8, tempo);
            beep_note(B_2, 8, tempo);
            beep_note(G_2, 4, tempo);
            beep_note(E_2, 8, tempo);
            beep_note(A_2, 8, tempo);
            beep_note(E_2, 4, tempo);
            break;
        case 6:
            // Beethoven's 5th...
            beep_note(E_3, 4, tempo);
            beep_note(E_3, 4, tempo);
            beep_note(E_3, 4, tempo);
            beep_note(C_3, 4, tempo);
            break;
        case 7:
            // Our own melody: Futurama Start Theme
            beep_note(C_3, 4, tempo);
            beep_note(C_3, 4, tempo);
            beep_note(MUTE, 8, tempo);
            beep_note(F_3, 8, tempo);
            beep_note(F_3, 4, tempo);
            
            beep_note(B_FLAT_2, 4, tempo);
            beep_note(B_FLAT_2, 4, tempo);
            beep_note(MUTE, 8, tempo);
            beep_note(C_3, 8, tempo);
            beep_note(C_3, 4, tempo);
            break;
    } // end switch
    
} // end beep_barcode()
