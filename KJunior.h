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


#include "18f66k22.h"
#device *=16 ADC=10 


#fuses INTRC,NOWDT,NOPROTECT,BROWNOUT,NOWDT,NOCPD,SOSC_DIG                      // Configuration Bits
#use   delay(clock=16000000)                                                    // Clock @ 16 MHz
#use   rs232(stream=USB, baud=57600,parity=N,bits=8,xmit=PIN_C6,rcv=PIN_C7)     // USB Serial Config. 57600,8,N,1
#use   rs232(stream=BT, baud=57600,parity=N,bits=8,xmit=PIN_G1,rcv=PIN_G2)      // Bluetooth Serial Config. 57600,8,N,1
#use   i2c(master,sda=PIN_C4,scl=PIN_C3,FORCE_HW,SLOW)                          // I2C Master Configuration
#use   fast_io(A)
#use   fast_io(B)
#use   fast_io(C)
#use   fast_io(D)
#use   fast_io(E)
#use   fast_io(F)
#use   fast_io(G)



#include "constants.h"
#include "variables.c"
#include "KJunior.c"



//#org 0xFC00, 0xFFFE {}                                                          // Bootloader Protection

////////////////////////////////////////////////////////////////////////////////
/*!   \file KJunior.h
      \brief This file is the library of all high level functions that can be used when programming KJunior
*/
////////////////////////////////////////////////////////////////////////////////

/**
   * \defgroup Configuration_Functions
   */
/*@{*/
////////////////////////////////////////////////////////////////////////////////
/*!   \fn void KJunior_init(void)
      \brief KJunior Initialisation. This function initialise all KJunior peripherals
      \param None
      \retval None
*/
////////////////////////////////////////////////////////////////////////////////
void KJunior_init(void);


////////////////////////////////////////////////////////////////////////////////
/*!   \fn void KJunior_config_auto_refresh_sensors(int1 Bit)
      \brief Set the refresh mode of all IRs sensors
      \param int1 Manual or Refresh (Default)
      \retval None
*/
////////////////////////////////////////////////////////////////////////////////
void KJunior_config_auto_refresh_sensors(int1 Bit)
{
     Auto_Refresh_Sensors=Bit;
}

////////////////////////////////////////////////////////////////////////////////
/*!   \fn void KJunior_config_auto_refresh_tv_remote(int1 Bit)
      \brief Configure the refresh mode of the TV remote receiver
      \param int1 Manual or Refresh(Default)
      \retval None
*/
////////////////////////////////////////////////////////////////////////////////
void KJunior_config_auto_refresh_tv_remote(int1 Bit)
{
      Auto_Refresh_TV_Remote=Bit;
}

////////////////////////////////////////////////////////////////////////////////
/*!   \fn void KJunior_config_rs232_control(int1 Bit)
      \brief Configure the Serial Remote Control
      \param int1 Disable or Enable (Default)
      \retval None
*/
////////////////////////////////////////////////////////////////////////////////
void KJunior_config_rs232_control(int1 Bit)
{
      Enable_RS232_Control=Bit;
}

////////////////////////////////////////////////////////////////////////////////
/*!   \fn void KJunior_config_tv_remote_control(int1 Bit)
      \brief Configure the TV Remote Control
      \param int1 Disable or Enable (Default)
      \retval None
*/
////////////////////////////////////////////////////////////////////////////////
void KJunior_config_tv_remote_control(int1 Bit)
{
      Enable_TV_Remote_Control=Bit;
}
/*@}*/

/**
   * \defgroup Flags
   */
/*@{*/
////////////////////////////////////////////////////////////////////////////////
/*!   \fn int1 KJunior_flag_sensors_refreshed(void)
      \brief Test if IRs sensors have been refreshed
      \param None
      \retval int1 1 if sensors have been refreshed
      \warning You must then call KJunior_flag_sensors_reset() to clear the flag
*/
////////////////////////////////////////////////////////////////////////////////
int1 KJunior_flag_sensors_refreshed(void)
{
      return Sensors_Refreshed_Flag;
}
////////////////////////////////////////////////////////////////////////////////
/*!   \fn void KJunior_flag_sensors_reset(void)
      \brief Clear IRs sensors refreshed flag
      \param None
      \retval None
*/
////////////////////////////////////////////////////////////////////////////////
void KJunior_flag_sensors_reset(void)
{
      Sensors_Refreshed_Flag = 0;
}
////////////////////////////////////////////////////////////////////////////////
/*!   \fn int1 KJunior_flag_rs232_filtering(void)
      \brief Test if Serial Remote Control is active or not
      \param None
      \retval int1 1 if active otherwise 0
*/
////////////////////////////////////////////////////////////////////////////////
int1 KJunior_flag_rs232_filtering(void)
{
      return Enable_RS232_Control;
}
////////////////////////////////////////////////////////////////////////////////
/*!   \fn int1 KJunior_flag_tv_data_refreshed(void)
      \brief Test if Tv Data have been refreshed
      \param None
      \retval int1 1 if active otherwise 0
      \warning You must then call KJunior_flag_tv_data_reset() to clear the flag
*/
////////////////////////////////////////////////////////////////////////////////
int1 KJunior_flag_tv_data_refreshed(void)
{
      return TV_Data_Available;
}
////////////////////////////////////////////////////////////////////////////////
/*!   \fn int1 KJunior_flag_tv_data_emitting(void)
      \brief Test if Tv Data the data is completely send
      \param None
      \retval int1 1 the data is still emitting otherwise 0 if it's done
      \warning You must then call KJunior_flag_tv_data_reset() to clear the flag
*/
////////////////////////////////////////////////////////////////////////////////
int1 KJunior_flag_tv_data_emitting(void)
{
      return TV_Data_emitting;
}

////////////////////////////////////////////////////////////////////////////////
/*!   \fn void KJunior_flag_tv_data_reset(void)
      \brief Clear TV Data flag
      \param None
      \retval None
*/
////////////////////////////////////////////////////////////////////////////////
void KJunior_flag_tv_data_reset(void)
{
      TV_Data_Available = 0;
}
/*@}*/

/**
   * \defgroup Peripheral_Access_Functions
   */
/*@{*/
////////////////////////////////////////////////////////////////////////////////
/*!   \fn unsigned char KJunior_get_proximity(char Sensor)
      \brief Get proximity value of one IR sensor
      \param char Front, FrontLeft, FrontRight, Left, Right, Rear, GroundLeft, GroundRight
      \retval unsigned_char Proximity Value (0 when nothing)
*/
////////////////////////////////////////////////////////////////////////////////
signed int16 KJunior_get_proximity(char Sensor)
{
      return IR_Proximity[Sensor];
}

////////////////////////////////////////////////////////////////////////////////
/*!   \fn unsigned char KJunior_get_brightness(char Sensor)
      \brief Get brightness value of one IR sensor
      \param char Front, FrontLeft, FrontRight, Left, Right, Rear, GroundLeft, GroundRight
      \retval unsigned_char Brightness Value (0 when lot of light)
*/
////////////////////////////////////////////////////////////////////////////////
signed int16 KJunior_get_brightness(char Sensor)
{
      return IR_Light[Sensor];
}

////////////////////////////////////////////////////////////////////////////////
/*!   \fn int1 KJunior_get_switch_state(char Switch_Number)
      \brief Get Switch State
      \retval int8 Value of the 3 switch (0 to 7)
*/
////////////////////////////////////////////////////////////////////////////////
unsigned char KJunior_get_switch_state()
{
      return Switchs;
}

////////////////////////////////////////////////////////////////////////////////
/*!   \fn char KJunior_get_tv_data(void)
      \brief Get latest data from the TV remote receiver
      \param None
      \retval char Byte that have been received
*/
////////////////////////////////////////////////////////////////////////////////
unsigned char KJunior_get_tv_data(void)
{
      return TV_DATA;
}

////////////////////////////////////////////////////////////////////////////////
/*!   \fn char KJunior_get_tv_addr(void)
      \brief Get latest address from the TV remote receiver
      \param None
      \retval char Byte that have been received
*/
////////////////////////////////////////////////////////////////////////////////
unsigned char KJunior_get_tv_addr(void)
{
      return TV_ADDR;
}

////////////////////////////////////////////////////////////////////////////////
/*!   \fn char KJunior_send_tv_value(void)
      \brief Send a value on the IR emitter
      \param addr set the address of the communication
      \param data value of the code to send
      \retval char Byte that have been received
*/
////////////////////////////////////////////////////////////////////////////////
void KJunior_send_tv_value(unsigned char addr, unsigned char data)
{
      TV_Addr_send = addr;                                                      // load the address register
      TV_Data_send = data;                                                      // Set the data register
      TV_Data_emitting = 1;                                                     // Set the flag to indicate that a mesasge must be send
      while(TV_Data_pending == 1);                                              // If a IR data is receiving, wait until it's done
      set_timer0(TIMER0_886);
      setup_timer_0(T0_INTERNAL | T0_DIV_1);                                    // Interrupt every 886 us
      TV_Counter = 0;                                                           // reset TV_Counter
      TV_Counter_flag = 0;                                                      // reset the sending phase flag
      disable_interrupts(INT_EXT);                                              // Disable interrupt of the receiving IR, to avoid receiving its own data
      enable_interrupts(INT_TIMER0);                                            // enable the timer0 interrupt to start the emitting    
}

////////////////////////////////////////////////////////////////////////////////
/*!   \fn void KJunior_set_speed(signed int8 Left, signed int8 Right)
      \brief Set speed of each motor
      \param signed_int8 Speed of motor (from -20 to 20, 0 = Stop)
      \retval None
*/
////////////////////////////////////////////////////////////////////////////////
void KJunior_set_speed(signed int8 LeftSpeed,signed int8 RightSpeed)
{
      PwmMotLeft = LeftSpeed;
      PwmMotRight = RightSpeed;
      if(PwmMotLeft >20)                                                        // Limit the minimum and maximum PWM value to -20 and 20
         PwmMotLeft = 20;
      else if(PwmMotLeft < -20) 
         PwmMotLeft = -20;
      if(PwmMotRight >20)                                                       // Limit the minimum and maximum PWM value to -20 and 20
         PwmMotRight = 20;
      else if(PwmMotRight < -20) 
         PwmMotRight = -20;  
         
      Motor_Conversion();                                                       // Convert the value to the real PWM and set the PWM output

}

////////////////////////////////////////////////////////////////////////////////
/*!   \fn void KJunior_beep(int1 State)
      \brief Set the buzzer State
      \param int8 Freq (0 to 48), 1 = 131Hz (Do 2st Octave & 48 = 1.975kHz (Si 5st Octave)
      \retval None
*/
////////////////////////////////////////////////////////////////////////////////
void KJunior_beep(unsigned char Freq)
{
      buzzValue = Freq;
      Set_Freq_note();
}

////////////////////////////////////////////////////////////////////////////////
/*!   \fn void KJunior_led_left(int1 State)
      \brief Set the Left Led State
      \param int1 State (0=Off,1=On)
      \retval None
*/
////////////////////////////////////////////////////////////////////////////////
void KJunior_led_left(int1 State)
{
      output_bit(LED0, State);
}
////////////////////////////////////////////////////////////////////////////////
/*!   \fn void KJunior_led_frontleft(int1 State)
      \brief Set the FrontLeft Led State
      \param int1 State (0=Off,1=On)
      \retval None
*/
////////////////////////////////////////////////////////////////////////////////
void KJunior_led_frontleft(int1 State)
{
      output_bit(LED1, State);
}
////////////////////////////////////////////////////////////////////////////////
/*!   \fn void KJunior_led_frontright(int1 State)
      \brief Set the FrontRight Led State
      \param int1 State (0=Off,1=On)
      \retval None
*/
////////////////////////////////////////////////////////////////////////////////
void KJunior_led_frontright(int1 State)
{
      output_bit(LED2, State);
}

////////////////////////////////////////////////////////////////////////////////
/*!   \fn void KJunior_led_right(int1 State)
      \brief Set the Right Led State
      \param int1 State (0=Off,1=On)
      \retval None
*/
////////////////////////////////////////////////////////////////////////////////
void KJunior_led_right(int1 State)
{
      output_bit(LED3,State);
}

////////////////////////////////////////////////////////////////////////////////
/*!   \fn void KJunior_led_onoff(int1 State)
      \brief Set the OnOff Led State
      \param int1 State (0=Off,1=On)
      \retval None
      \warning This Led is controlled in background by the Scheduler
*/
////////////////////////////////////////////////////////////////////////////////
void KJunior_led_onoff(int1 State)
{
      output_bit(LED4,State);
}

////////////////////////////////////////////////////////////////////////////////
/*!   \fn void KJunior_manual_refresh_sensors(char Zone)
      \brief Manualy refresh a zone
      \param None
      \retval None
*/
////////////////////////////////////////////////////////////////////////////////
void KJunior_manual_refresh_sensors()
{
   Manual_Refresh_sensors = 1;
   Sensors_Refreshed_Flag = 0;
}
/*@}*/

/**
   * \defgroup Time_Functions
   */
/*@{*/
////////////////////////////////////////////////////////////////////////////////
/*!   \fn void KJunior_delay_s(int Delay)
      \brief This function stop program execution (but not the interrupts) during the defined time in second
      \param Delay 1 to 65535
      \retval None
*/
////////////////////////////////////////////////////////////////////////////////

void KJunior_delay_s(int16 Delay)
{
   int i, b;
   for(i = 0; i< Delay; i++)
   {
        b = delay_ms(1000);
   }
}

////////////////////////////////////////////////////////////////////////////////
/*!   \fn void KJunior_delay_ms(int Delay)
      \brief This function stop program execution (but not the interrupts) during the defined time in millisecond
      \param Delay 1 to 65535
      \retval None
*/
////////////////////////////////////////////////////////////////////////////////
void KJunior_delay_ms(int16 Delay)
{
   delay_ms(Delay);
}

////////////////////////////////////////////////////////////////////////////////
/*!   \fn void KJunior_delay_us(int Delay)
      \brief This function stop program execution (but not the interrupts) during the defined time in microsecond
      \param Delay 1 to 65535
      \retval None
*/
////////////////////////////////////////////////////////////////////////////////
void KJunior_delay_us(int16 Delay)
{
   delay_us(Delay);
}

////////////////////////////////////////////////////////////////////////////////
/*!   \fn unsigned int32 KJunior_get_time(void)
      \brief This function return a 32 bits value which is increased every ms
      \param None
      \retval unsigned int32 time value
*/
////////////////////////////////////////////////////////////////////////////////
unsigned int32 KJunior_get_time(void)
{
   return TimeTip;
}

////////////////////////////////////////////////////////////////////////////////
/*!   \fn void KJunior_set_time(unsigned int32 time)
      \brief This function allow user to set the current time value
      \param unsigned int32 time
      \retval None
*/
////////////////////////////////////////////////////////////////////////////////
void KJunior_set_time(unsigned int32 Time)
{
   TimeTip = Time;
}

/*@}*/


////////////////////////////////////////////////////////////////////////////////
/*!   \fn int1 KJunior_ext_read_PINB6(void)
      \brief Read input PORTB.6
      \param None
      \retval int1 input value (0 or 1)
*/
////////////////////////////////////////////////////////////////////////////////
int1 KJunior_ext_read_PINB6(void)
{
   set_tris_b(TRISB|0x40);
   return input(PIN_B6);
}
////////////////////////////////////////////////////////////////////////////////
/*!   \fn int1 KJunior_ext_read_PINB7(void)
      \brief Read input PORTB.7
      \param None
      \retval int1 input value (0 or 1)
*/
////////////////////////////////////////////////////////////////////////////////
int1 KJunior_ext_read_PINB7(void)
{
   set_tris_b(TRISB|0x80);
   return input(PIN_B7);
}

////////////////////////////////////////////////////////////////////////////////
/*!   \fn void KJunior_ext_write_PINB6(int1 Bit)
      \brief Write output PORTB.6
      \param int1 Value to write (0 or 1)
      \retval None
*/
////////////////////////////////////////////////////////////////////////////////
void KJunior_ext_write_PINB6(int1 Bit)
{
   set_tris_b(TRISB & 0xBF);
   output_bit(PIN_B6,bit);
}
////////////////////////////////////////////////////////////////////////////////
/*!   \fn void KJunior_ext_write_PINB7(int1 Bit)
      \brief Write output PORTB.7
      \param int1 Value to write (0 or 1)
      \retval None
*/
////////////////////////////////////////////////////////////////////////////////
void KJunior_ext_write_PINB7(int1 Bit)
{
   set_tris_b(TRISB & 0x7F);
   output_bit(PIN_B7,bit);
}


////////////////////////////////////////////////////////////////////////////////
/*!   \fn void KJunior_get_Battery(void)
      \brief Read the battery voltage
      \param None
      \retval BatteryVoltage
*/
////////////////////////////////////////////////////////////////////////////////
unsigned int16 KJunior_get_Battery(void)
{
  return BatteryVoltage;
}
/*@}*/




