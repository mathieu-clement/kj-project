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

////////////////////////////////////////////////////////////////////////////////
/*!   \file constants.h
      \brief In this file all constants are defined
*/
////////////////////////////////////////////////////////////////////////////////

#define INIT_TRISA            0x2F   // b0010 1111
#define INIT_PORTA            0x00   // b0000 0000

#define INIT_TRISB            0xC1   // b1100 0001
#define INIT_PORTB            0x00   // b0000 0000

//#define INIT_TRISC            0x87   // b1000 0111
#define INIT_TRISC            0x9F   // b1001 1111
#define INIT_PORTC            0x00   // b0000 0000

#define INIT_TRISD            0x00   // b0000 0000
#define INIT_PORTD            0x00   // b0000 0000

#define INIT_TRISE            0x00   // b0000 0000
#define INIT_PORTE            0x00   // b0000 0000

#define INIT_TRISF            0xBF   // b1011 1111
#define INIT_PORTF            0x00   // b0000 0000

#define INIT_TRISG            0x04   // b0000 0100
#define INIT_PORTG            0x00   // b0000 0000


#BIT BOR = 0x8E.0
#BIT POR = 0x8E.1

#define SERIAL_BUFFER_SIZE  80
#define SERIAL_USB      0
#define SERIAL_BT       1

#define NB_IR                 10

#locate ADCON0      =       0x0FC2
#locate ADCON1      =       0x0FC1
#locate ADCON2      =       0x0FC0
#locate OSCCON      =       0x0FD3
#locate RCON        =       0x0FD0
#define IPEN        0x80

#locate IPR1        =       0x0F9F
#define RC1IP       0x20
#locate IPR2        =       0x0FA2
#locate IPR3        =       0x0FA5
#define RC2IP       0x20
#locate IPR4        =       0x0FB8
#locate IPR5        =       0x0FD2
#locate IPR6        =       0x0FA9

#define LEFT                  0
#define FRONTLEFT             1
#define FRONT                 2
#define FRONTRIGHT            3
#define RIGHT                 4
#define REAR                  5
#define GROUNDLEFT            9
#define GROUNDFRONTLEFT       7 
#define GROUNDFRONTRIGHT      8
#define GROUNDRIGHT           10

#define VBAT_AN               6

#define EEPROM_ADD            10

#define IR_GROUP1             PIN_D1
#define IR_GROUP2             PIN_D2
#define IR_GROUP3             PIN_D3

#define IR_CALIB_TH           20

#define LEFT_EMITTER                  PIN_D1
#define FRONTLEFT_EMITTER             PIN_D2
#define FRONT_EMITTER                 PIN_D1
#define FRONTRIGHT_EMITTER            PIN_D3
#define RIGHT_EMITTER                 PIN_D1
#define REAR_EMITTER                  PIN_D3
#define GROUNDLEFT_EMITTER            PIN_D2
#define GROUNDFRONTLEFT_EMITTER       PIN_D3
#define GROUNDFRONTRIGHT_EMITTER      PIN_D2
#define GROUNDRIGHT_EMITTER           PIN_D3


#define ENABLE                1
#define DISABLE               0
#define FAST                  1
#define NORMAL                0
#define MANUAL                0
#define REFRESH               1
#define ON                    1
#define OFF                   0

#define KJ_FW_VERSION   "B"
#define KJ_FW_REVISION  1                                                       // Please set revision!
#define KJ_FW_REFERENCE "510.0055"

#define RC5_HEADER       0xC0
#define RC5_TOGGLE       0x20
#define MANCHESTER_0     0x2
#define MANCHESTER_1     0x1

#define RC5_KJ_ADDR      0x00             // RC5 address of the K-Junior robot ! it's a TV!
#define RC5_KJ_CMD_GO    0x02
#define RC5_KJ_CMD_BACK  0x00
#define RC5_KJ_CMD_LEFT  0x04
#define RC5_KJ_CMD_RIGHT 0x06
#define RC5_KJ_CMD_STOP  0x05
#define RC5_KJ_CMD_Sp    0x10             // Speed+ = Vol +
#define RC5_KJ_CMD_Sm    0x11             // Speed- = Vol -

#define StartBit1        0
#define StartBit2        1
#define ToggleBit        2
#define AddrBit4       3
#define AddrBit3       4
#define AddrBit2       5
#define AddrBit1       6
#define AddrBit0       7
#define DataBit5         8
#define DataBit4         9
#define DataBit3         10
#define DataBit2         11
#define DataBit1         12
#define DataBit0         13

#define MotD1           PIN_E6
#define MotD2           PIN_E5
#define MotG1           PIN_E4
#define MotG2           PIN_E3

#define BUZZER          PIN_E2

#define IR_IN           PIN_B0
#define IR_OUT          PIN_D4

#define VBAT_M          PIN_F1

#define LED0            PIN_B1
#define LED1            PIN_B2
#define LED2            PIN_B3
#define LED3            PIN_B4
#define LED4            PIN_B5

#define MODE1           PIN_C0
#define MODE2           PIN_C1
#define MODE3           PIN_C2

#define TIMER1_VALUE    64585
#locate INTCON =        0x0FF2
#locate PIR1   =        0x0F9E

// Timer 0 is used for the rc5 decoding     
#define TIMER0_1780     58415                                                   // = 1.78ms
#define TIMER0_1140     60975                                                   // = 1.14ms
#define TIMER0_2100     57135                                                   // = 2.10ms
#define TIMER0_886      61991                                                   // = 886us

// Timer 2 used for the Buzzer, Timer4 For the motors
#define MOTOR_MAX       200                                                     // Define the frequency of the PWM motor (=20kHz)
#define MOTOR_MIN       60                                                      // Minimum PWM set on the motor
#define MOTOR_CONV      7                                                       // value to convert the 0-20 speed value to the PWM
#define SPEED_MIN       15                                                      // Define the speed where an acceleration is needed
#define ACCEL           30                                                      // Time of the acceleration in us

#locate CCP1CON   =     0x0FBB
#locate CCP2CON   =     0x0F4E
#locate CCP3CON   =     0x0F49
#locate CCPTMRS0  =     0x0F2D
#locate PSTR1CON  =     0x0F9C    
#locate PSTR2CON  =     0x0F1B
#locate PSTR3CON  =     0x0F1A
#locate SSP1CON1  =     0x0FC6

// Timer3 value for the note frequency
#define BUZ_NUMBER      48                                                      // Number of available notes
#define BUZ_DO          63626                                                   // = 262Hz (if Timer3/4)
#define BUZ_RE_BEMOL    63729                                                   // = 277Hz (if Timer3/4)
#define BUZ_RE          63834                                                   // = 294Hz (if Timer3/4)
#define BUZ_MI_BEMOL    63927                                                   // = 311Hz (if Timer3/4)
#define BUZ_MI          64019                                                   // = 330Hz (if Timer3/4)
#define BUZ_FA          64115                                                   // = 349Hz (if Timer3/4)
#define BUZ_SOL_BEMOL   64183                                                   // = 370Hz (if Timer3/4)
#define BUZ_SOL         64259                                                   // = 392Hz (if Timer3/4)
#define BUZ_LA_BEMOL    64330                                                   // = 415Hz (if Timer3/4)
#define BUZ_LA          64398                                                   // = 440Hz (if Timer3/4)
#define BUZ_SI_BEMOL    64462                                                   // = 466Hz (if Timer3/4)
#define BUZ_SI          64522                                                   // = 494Hz (if Timer3/4)



