//--------------------------------------------------------------------------------//
//-                   KJOs ( K-Junior Operating System )                         -//
//                                                                               -//
//-  Copyright (C) Frédéric Lambercy, K-Team S.A. 2008                           -//
//-  This library is free software; you can redistribute it and/or               -//
//-  modify it under the terms of the GNU Lesser General Public                  -//
//-  License as published by the Free Software Foundation; either                -//
//-  version 2.1 of the License, or any later version.                           -//
//-                                                                              -//
//-  This library is distributed in the hope that it will be useful,             -//
//-  but WITHOUT ANY WARRANTY; without even the implied warranty of              -//
//-  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU           -//
//-  Lesser General Public License for more details.                             -//
//-                                                                              -//
//-  You should have received a copy of the GNU Lesser General Public            -//
//-  License along with this library; if not, write to the Free Software         -//
//-  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA   -//
//-                                                                              -//
//-                               __  __  ________                               -//
//- K-Team S.A.                  |  |/  /|__    __|___  _____  ___  ___          -//
//- Z.I. les Plans-Praz          |     / __ |  | _____|/  _  \|   \/   |         -//
//- 1337 Vallorbe                |  |  \    |  | ____|/  /_\  |        |         -//
//- Switzerland                  |__|\__\   |__|______|_/   \_|__|\/|__|         -//
//- lambercy@k-team.com   tel:+41 24 423 89 73 fax:+41 24 423 8960               -//
//-                                                                              -//
//--------------------------------------------------------------------------------//
#include "KJunior.h"


//--------------------------------------------------------------------------------//
//- Main program                                                                 -//
//--------------------------------------------------------------------------------//
#separate
void main(void)
{


 // Initialization
 KJunior_init();
 
 //*******************************Main loop***************************************//
 While (1)
 { 
   if((SerialCommandOK == 1) && (Enable_RS232_Control == 1))                    // Test if a Serial Command was received ...
      SerialCommandHandler();                                                   // .. and execute the select function (only if the serial mode control is activated)
      
                                                                                // ADD YOUR CODE HERE
 }

}

      
 



