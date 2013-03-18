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
/*!   \file variables.c
      \brief Definition of all global functions
*/
////////////////////////////////////////////////////////////////////////////////

//- Motors
signed int8 PwmMotLeft = 0;                                                     // 0 : Stop ; 20 : Max Speed
signed int8 PwmMotRight = 0;                                                    // 0 : Stop ; 20 : Max Speed
signed int8 Old_PwmMotRight = 0;                                                // Save the speed value to compare with the new one
signed int8 Old_PwmMotLeft = 0;                                                 // Save the speed value to compare with the new one
signed int8 TimerMotLeft = 0;                                                   // Value which will be set in the PWM timer register
signed int8 TimerMotRight = 0;                                                  // Value which will be set in the PWM timer register
unsigned char Acceleration_Timer = 0;
unsigned char Acceleration_flag = 0;                                            // flag to indicate if an acceleration is needed
#define   ACCEL_LEFT      0x01
#define   ACCEL_RIGHT     0x02



//- Configuration Bits
int1 Auto_Refresh_Sensors = 1;                                                  // 1 : Auto   ; 0 : Manual
int1 Auto_Refresh_TV_Remote = 1;                                                // 1 : Auto   ; 0 : Never
int1 Enable_RS232_Control = 1;                                                  // 1 : Enable ; 0 : Disable
int1 Enable_TV_Remote_Control = 1;                                              // 1 : Enable ; 0 : Disable



//- RS232
char SerialBuffer[ SERIAL_BUFFER_SIZE ];
int1 SerialCommandOK = 0;
char SerialCounter = 0;
char SerialPort = 0;

//- Flag
int1 Sensors_Refreshed_Flag = 0;

//- TV Remote Control Bit
int8 TV_table[14];
int8 TV_ADDR = 0;                                                               // Address of the received RC5 code
int8 TV_DATA = 0;                                                               // Data of the received RC5 code
int8 TV_Counter = 0;                                                            // Counter for the RC5 code
int1 TV_Counter_flag = 0;                                                       // Flag to know if the emitting is in the first phase (=0) or the second (=1) of the bit to send
int8 TV_Data_send = 0;                                                          // Value of the rc5 code to send
int8 TV_Addr_send = 0;                                                          // Address of the rc5 code to send
int1 TV_Data_Available = 0;                                                     // Flag to indicate that a Data is available
int1 TV_Data_pending = 0;                                                       // Flag indicate that a data is coming on the IR receiver
int1 TV_Data_emitting = 0;                                                      // Flag indicate that a data must be send via the IR emitter
int1 TV_Data_loop = 0;                                                          // Flag to loop when a 1 is following by a zero
char TV_RX_Toggle_Bit = 0;                                                      // Flag to identify the tag of the message, only a different toggle bit means that the message is different than before
int1 TV_TX_Toggle_Bit = 0;                                                      // Flag to identify the tag of the message, only a different toggle bit means that the message is different than before



//- Time
unsigned int32 TimeTip = 0;
char TimeTipDivider = 0;
unsigned char MotorTime = 0;
unsigned char MotorTimeDivider = 0;

//- Irs Sensors
signed int16 IR_Light[ 12 ];
signed int16 IR_Proximity[ 12 ];                                                // 0 : nothing detected ; 4096 : obstacle near KJunior
signed int16 IR_Calibrate[ 12 ];                                                 // Value of the calibrated sensor
signed int16 IR_Temp_Proximity[ 12 ];                                           // 0 : nothing detected ; 4096 : obstacle near KJunior
unsigned char IR_Counter = 0 ;                                                  // counter to manage the refresh of the IR sensor
unsigned char IR_ADC_Flag = 0;                                                  // Flag to indicate when a sensor is completely refreshed
unsigned char IR_AN_Table[12];                                                  // Table where the analog pin map of the IR sensor are saved
int1 Manual_Refresh_sensors = 0;                                                // Flag to refresh manually the sensor

//- Battery voltage
unsigned int16  BatteryVoltage = 0;                                             // Analog value of the battery voltage

//- Switchs
char Switchs;


//- LED state (0 = Normal, 1 = Mode auto activate (chenillard))
unsigned char LED_mode = 0x10;                                                  // Start with the LED4 in auto mode
unsigned int16 LED_counter = 0;

//- Buzzer variable
unsigned char buzzValue   = 0;                                                  // Value of the Buzzer frequency 
unsigned int16 Buzzer_Timer = 0;
unsigned int16 Buzzer_Table[13];

// Variable for Bluetooth configuration
unsigned char BT_config = 0;

//- TRIS
#locate TRISB = 0x0F93



