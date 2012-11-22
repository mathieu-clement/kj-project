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
/*!   \file KJunior.c
      \brief The Os functions, all functions are called through an interrupt
*/
////////////////////////////////////////////////////////////////////////////////
#include <stdlib.h>

#PRIORITY RDA,RDA2,TIMER0,EXT

//----------------------------------------------------------------//
//-                Conversion Function                           -//
char chartohex( char valuetoconvert )
{
   char convertedval;
      if( valuetoconvert >= 'A' )
      {
            convertedval = valuetoconvert-'A'+10;
      }   
      else
      {
            convertedval = valuetoconvert -'0';
      }
      return convertedval;
}

//----------------------------------------------------------------//
//-                Robot Initialisation                          -//

void KJunior_init(void)
{
 unsigned int i=0;
 // configure ports direction
 set_tris_a(INIT_TRISA);
 set_tris_b(INIT_TRISB);
 set_tris_c(INIT_TRISC);
 set_tris_d(INIT_TRISD);
 set_tris_e(INIT_TRISE);
 set_tris_f(INIT_TRISF);
 set_tris_g(INIT_TRISG);

 // set default value for each pin
 output_a(INIT_PORTA);
 output_b(INIT_PORTB);
 output_c(INIT_PORTC);
 output_d(INIT_PORTD);
 output_e(INIT_PORTE);
 output_f(INIT_PORTF);
 output_g(INIT_PORTG);
   


  
 setup_oscillator(OSC_16MHZ);                                                   // use internal osc@16 MHz, no clockout
 for (i=0;i<=GROUNDRIGHT;i++)                                                   // Init the IR table values and the read the calibrate value in the EEPROM
             {
   IR_Light[i]= 0;
   IR_Proximity[i] = 0;
   IR_Calibrate[i] = read_eeprom((EEPROM_ADD*2*i)+1);
   IR_Calibrate[i] = (signed int16)(IR_Calibrate[i]<<8) + read_eeprom(EEPROM_ADD*2*i);
   if(IR_Calibrate[i] == 0xFFFF)                                                // If the Eeprom has not been initialize, reset the value
     IR_Calibrate[i] = 0;
   
 }  
 PwmMotLeft = 0;                                                                // Init the Speed to 0
 PwmMotRight = 0;
 
 // Disable IR sensor emitter
 output_low(IR_GROUP1);
 output_low(IR_GROUP2);
 output_low(IR_GROUP3);
 
 // init the pin map table for the IR sensor
 // Emitter E0
 IR_AN_Table[0]       = LEFT;
 IR_AN_Table[1]       = FRONT;
 IR_AN_Table[2]       = RIGHT;
 // Emitter E1
 IR_AN_Table[3]       = FRONTLEFT;
 IR_AN_Table[4]       = GROUNDFRONTRIGHT;
 IR_AN_Table[5]       = GROUNDLEFT;
 // Emitter E2
 IR_AN_Table[6]       = FRONTRIGHT;
 IR_AN_Table[7]       = REAR;
 IR_AN_Table[8]       = GROUNDFRONTLEFT;
 IR_AN_Table[9]       = GROUNDRIGHT;
 
 
 
  
 

 // Setup the adc converter to start with the LEFT IR sensor
 setup_adc_ports(sAN0 | sAN1 | sAN2 | sAN3 | sAN4 | sAN5 | sAN6 | sAN7 | sAN8| sAN9 | sAN10 );
 ADCON1 = 0x00;                                                                 // Set the ADC reference to AVdd and AVss
 //ADCON1 = 0x30;                                                                 // Set the ADC reference to AVdd and AVss
 set_adc_channel( IR_AN_Table[0] );
 ADCON2 = 0xA5;                                                                 // Configure the ADC clock DIV/16 with 8TAD
 ADCON0 |= 0x01;                                                                // Turn on the AD module
 enable_interrupts(INT_AD);



 // Set the timer 1 used for the internal tasks management
 set_timer1(TIMER1_VALUE);                                                      // set default value to get an interrupt each 250us
 setup_timer_1(T1_INTERNAL);                                                    // used for scheduler
 // Activate the interrupts
 enable_interrupts(INT_TIMER1);
 if( Enable_RS232_Control == 1 )
 {
    enable_interrupts(INT_RDA);
    enable_interrupts(INT_RDA2);
//    RCON |= IPEN;                                                               // Enable the level interrupt
 }
 while(kbhit(BT)) fgetc(BT);                                                    // Flush the RS232 buffer
 while(kbhit(USB)) fgetc(USB);
 
 // Read the Switch the first time
 Switchs  =   !input(MODE1);        
 Switchs |= ((!input(MODE2))<<1);   
 Switchs |= ((!input(MODE3))<<2);   
 
 setup_timer_0(T0_OFF);                                                         // used for Rc5 decoding, Initially OFF
 
 setup_timer_3(T3_DISABLED | T3_DIV_BY_4);                                      // Configure the Timer3 for the buzzer, initially OFF
 Buzzer_Table[1] = BUZ_DO;                                                      // Configure the frequency note table
 Buzzer_Table[2] = BUZ_RE_BEMOL;
 Buzzer_Table[3] = BUZ_RE;
 Buzzer_Table[4] = BUZ_MI_BEMOL;
 Buzzer_Table[5] = BUZ_MI;
 Buzzer_Table[6] = BUZ_FA;
 Buzzer_Table[7] = BUZ_SOL_BEMOL;
 Buzzer_Table[8] = BUZ_SOL;
 Buzzer_Table[9] = BUZ_LA_BEMOL;
 Buzzer_Table[10] = BUZ_LA;
 Buzzer_Table[11] = BUZ_SI_BEMOL;
 Buzzer_Table[12] = BUZ_SI;
 

 setup_timer_4(T4_DIV_BY_1,MOTOR_MAX,1);                                        // Configure the PWM motor at 20kHz
 
 CCP1CON = 0x0C;                                                                // Configure the ECCP1 module in single PWM mode
 CCP3CON = 0x0C;                                                                // Configure the ECCP3 module in single PWM mode
 
 CCPTMRS0 = 0x41;                                                               // Select the Timer4 for the Motor, and the Timer2 for the Buzzer
 PSTR1CON = 0x00;                                                               // Set M1_A and M1_B as standard output
 PSTR3CON = 0x00;                                                               // Set M2_A and M2_B as standard output
 
 // Configure the I2C bus
 SSP1CON1 = 0x28;                                                               // Configure the I2C bus as Master and enable it


 // Enable and configure the interrupts
 ext_int_edge(H_TO_L);                                                         
 enable_interrupts(INT_EXT);
 enable_interrupts(GLOBAL);


 // Display boot message
 delay_ms(50);
 
 fprintf(USB,"\r\nK-Junior v2 Operating System\r\n");
 fprintf(USB,"kJOS %s-%02d (%s), K-Team SA\r\n",KJ_FW_VERSION,KJ_FW_REVISION, KJ_FW_REFERENCE );
 fprintf(USB,"E-Mail : info@k-team.com\r\n");
 fprintf(BT,"\r\nK-Junior v2 Operating System\r\n");
 fprintf(BT,"kJOS %s-%02d (%s), K-Team SA\r\n",KJ_FW_VERSION,KJ_FW_REVISION, KJ_FW_REFERENCE );
 fprintf(BT,"E-Mail : info@k-team.com\r\n");



}

//---------------------------------------------------------------//
// Convert the intial motor value (0-20) to the final PWM (0-100%)
//---------------------------------------------------------------//
void Set_left_motor(void)
{
      if(PwmMotLeft == 0)                                                       // Stop the motor left
      {
        set_pwm3_duty(0);                                                       // Set the duty cycle to 0
        PSTR3CON = 0x00;                                                        // Set M2_A and M2_B as standard output
        return;
      }
      else if(PwmMotLeft > 0)
      {
        if((PwmMotLeft < SPEED_MIN) && (Old_PwmMotLeft <= 0) && (PwmMotLeft != Old_PwmMotLeft))            // If the actual and new speed is too low
         Acceleration_flag |= ACCEL_LEFT;
        TimerMotLeft = (MOTOR_CONV * PwmMotLeft)+MOTOR_MIN;                     // calculate the duty cycle
        PSTR3CON = 0x04;                                                        // Enable M2_A as PWM output
      }
      else
      {
        if((-PwmMotLeft < SPEED_MIN) && (-Old_PwmMotLeft <= 0) && (PwmMotLeft != Old_PwmMotLeft))          // If the actual and new speed is too low
         Acceleration_flag |= ACCEL_LEFT;
        TimerMotLeft = (MOTOR_CONV * -PwmMotLeft)+MOTOR_MIN;                    // calculate the duty cycle
        PSTR3CON = 0x02;                                                        // And enable M2_B as PWM output
      }
      set_pwm3_duty(TimerMotLeft);                                              // Set the duty cycle

}

void Set_right_motor(void)
{
      if(PwmMotRight == 0)                                                       // Stop the motor right
      {
        set_pwm1_duty(0);                                                       // Set the duty cycle to 0
        PSTR1CON = 0x00;                                                        // Set M2_A and M2_B as standard output
        return;
      }
      else if(PwmMotRight > 0)
      {
        if((PwmMotRight < SPEED_MIN) && (Old_PwmMotRight <= 0) && (PwmMotRight != Old_PwmMotRight))            // If the actual and new speed is too low
         Acceleration_flag |= ACCEL_RIGHT;
        TimerMotRight = (MOTOR_CONV * PwmMotRight)+MOTOR_MIN;                   // Calculate the duty cycle
        PSTR1CON = 0x04;                                                        // And enable M1_A as PWM output
      }
      else
      {
        if((-PwmMotRight < SPEED_MIN) && (-Old_PwmMotRight <= 0) && (PwmMotRight != Old_PwmMotRight))            // If the actual and new speed is too low
         Acceleration_flag |= ACCEL_RIGHT;
        TimerMotRight = (MOTOR_CONV * -PwmMotRight)+MOTOR_MIN;                  // Calculate the duty cycle
        PSTR1CON = 0x02;                                                        // And enable M1_B as PWM output
      } 
      set_pwm1_duty(TimerMotRight);

}


void  Motor_Conversion(void)
{
   Acceleration_flag = 0;                                                       // reset the flag
   Set_right_motor();                                                           // Set the right motor PWM
   Set_left_motor();                                                            // Set the left motor PWM
   if(Acceleration_flag != 0)                                                   // If too low speed is set, make a small acceleration on the desired motor
   {
     if(Acceleration_flag & ACCEL_RIGHT)
     {
       set_pwm1_duty(MOTOR_MAX);                                                // make a small acceleration to start the rotation of the motor
     }
     if(Acceleration_flag & ACCEL_LEFT)
     {
       set_pwm3_duty(MOTOR_MAX);                                                // make a small acceleration to start the rotation of the motor
     }
     Acceleration_Timer = ACCEL;                                                // Set the timer to stop the acceleration after x ms
   }
   Old_PwmMotLeft = PwmMotLeft;                                                 // Save the speed value 
   Old_PwmMotRight = PwmMotRight;
}

//---------------------------------------------------------------//
// Convert the intial buzzer value (0-48) to the corresponding frequency note
//---------------------------------------------------------------//
void Set_Freq_note(void)
{
  if(buzzValue == 0)                                                            // Turn off the buzzer
  {
    disable_interrupts(INT_TIMER3);
    setup_timer_3(T3_DISABLED | T3_DIV_BY_4);
    output_low(BUZZER);
  }
  else
  {
    if(buzzValue <= 12 )                                                        // Octave n°2 (131Hz-247Hz)
    {
      Buzzer_Timer = Buzzer_Table[buzzValue];                                   // Set the timer3 to the frequency of the selected note
      setup_timer_3(T3_INTERNAL | T3_DIV_BY_8);                                 // Set the timer to play on the second Octave
    }
    else if(buzzValue <= 24 )                                                   // Octave n°3 (262Hz-494Hz)
    {
      Buzzer_Timer = Buzzer_Table[buzzValue-12];                                // Set the timer3 to the frequency of the selected note
      setup_timer_3(T3_INTERNAL | T3_DIV_BY_4);                                 // Set the timer to play on the third Octave
    }
    else if(buzzValue <= 36 )                                                   // Octave n°4 (523Hz-988Hz)
    {
      Buzzer_Timer = Buzzer_Table[buzzValue-24];                                // Set the timer3 to the frequency of the selected note
      setup_timer_3(T3_INTERNAL | T3_DIV_BY_2);                                 // Set the timer to play on the fourth Octave
    }
    else                                                                        // Octave n°5 (1046.5Hz-1975Hz)
    {
      Buzzer_Timer = Buzzer_Table[buzzValue-36];                                // Set the timer3 to the frequency of the selected note
      setup_timer_3(T3_INTERNAL | T3_DIV_BY_1);                                 // Set the timer to play on the fifth Octave
    }
    enable_interrupts(INT_TIMER3);
  }

}


//---------------------------------------------------------------//
//-                        TV Remote                            -//

// TV Remote Control
void TV_Remote_Control( void )
{
   switch( TV_DATA )
   {
      case 1 :
         PwmMotLeft = 5;
         PwmMotRight = 18;
         break;
      case 2 :
         PwmMotLeft = 14;
         PwmMotRight = 14;
         break;
      case 3 :
         PwmMotLeft = 18;
         PwmMotRight = 5;
         break;
      case 4:
         PwmMotLeft = -14;
         PwmMotRight = 14;
         break;
      case 5 :
         PwmMotLeft = 0;
         PwmMotRight = 0;
         break;
      case 6 :
         PwmMotLeft = 14;
         PwmMotRight = -14;
         break;
      case 7 :
         PwmMotLeft = -5;
         PwmMotRight = -18;
         break;
      case 8:
         PwmMotLeft = -14;
         PwmMotRight = -14;
         break;
      case 9 :
         PwmMotLeft = -18;
         PwmMotRight = -5;
         break;
      case 12 :            // Touche On/Off
         return;
         break;
      case 16 :            // Touche Son +
         return;
         break;
      case 17 :            // Touche Son -
         return;
         break;
      default:
        return;
        break;
   }
   Motor_Conversion();  
}
#INT_AD
void Analog_Interrupt(void)
{
   
   // Read the battery voltage
   if(IR_ADC_flag == 0)
   {   
     BatteryVoltage = read_adc(ADC_READ_ONLY);                                // Read the battery voltage
     IR_ADC_flag++;
     set_adc_channel(IR_AN_Table[ IR_Counter ]);                                // Set the analog input to the first sensor
   }
 
    // Read all the ambiant value
   else if(IR_ADC_flag == 1)
   {
     IR_light[IR_AN_Table[ IR_Counter ]] = read_adc(ADC_READ_ONLY);             // Read the ambiant light value
     if(++IR_Counter >= NB_IR)                                                   // If all the ambiant light value are readed
     {
       IR_Counter = 0;                                                          // Reset the counter
       set_adc_channel(IR_AN_Table[ IR_Counter ]);                              // And set the Analog input to the first IR
       IR_ADC_flag++;
     }
     else
     {
       set_adc_channel(IR_AN_Table[ IR_Counter ]);                              // Set the analog input to next sensor
       delay_us(2);
       read_adc(ADC_START_ONLY);                                                // Start the new conversion
     }
   }
   // Read distance value of the first group
   else if(IR_ADC_flag == 3)
   {
     IR_Temp_Proximity[IR_AN_Table[ IR_Counter ]] = read_adc(ADC_READ_ONLY);    // Read the Distance
     IR_Temp_Proximity[ IR_AN_Table[ IR_Counter ]] = abs(IR_light[IR_AN_Table[ IR_Counter ]] - IR_Temp_Proximity[ IR_AN_Table[ IR_Counter ] ]); // Substract the proximity to the ambiant value to obtain the correct distance value
     if(IR_Temp_Proximity[IR_AN_Table[ IR_Counter ]] < IR_Calibrate[IR_AN_Table[ IR_Counter ]])  // Check if the value is greater than the calibrated value
       IR_Proximity[IR_AN_Table[ IR_Counter ]] = 0;
     else
       IR_Proximity[IR_AN_Table[ IR_Counter ]] = IR_Temp_Proximity[IR_AN_Table[ IR_Counter ]] - IR_Calibrate[IR_AN_Table[ IR_Counter ]];
     IR_Counter++;
     set_adc_channel(IR_AN_Table[ IR_Counter ]);                                 // Set the analog input to next sensor
     delay_us(2);
    if(IR_Counter > 2)
    {
      output_low(IR_GROUP1);                                                    // Turn off the IR emitter of the first Group
      IR_ADC_flag++;
    }
    else
      read_adc(ADC_START_ONLY);                                                 // Start the new conversion

  
   }
   // Read distance value of the second group
   else if(IR_ADC_flag == 5)
   {
      IR_Temp_Proximity[IR_AN_Table[ IR_Counter ]] = read_adc(ADC_READ_ONLY);    // Read the Distance
     IR_Temp_Proximity[ IR_AN_Table[ IR_Counter ]] = abs(IR_light[IR_AN_Table[ IR_Counter ]] - IR_Temp_Proximity[ IR_AN_Table[ IR_Counter ] ]); // Substract the proximity to the ambiant value to obtain the correct distance value
     if(IR_Temp_Proximity[IR_AN_Table[ IR_Counter ]] < IR_Calibrate[IR_AN_Table[ IR_Counter ]])  // Check if the value is greater than the calibrated value
       IR_Proximity[IR_AN_Table[ IR_Counter ]] = 0;
     else
       IR_Proximity[IR_AN_Table[ IR_Counter ]] = IR_Temp_Proximity[IR_AN_Table[ IR_Counter ]] - IR_Calibrate[IR_AN_Table[ IR_Counter ]];
      IR_Counter++;
      set_adc_channel(IR_AN_Table[ IR_Counter ]);                                 // Set the analog input to next sensor
      delay_us(2);
      if(IR_Counter > 5)
      {
        output_low(IR_GROUP2);                                                    // Turn off the IR emitter of the second Group
        IR_ADC_flag++;
      }
      else
        read_adc(ADC_START_ONLY);                                                 // Start the new conversion
   }
   // Read distance value of the third group
   else if(IR_ADC_flag == 7)
   {
    IR_Temp_Proximity[IR_AN_Table[ IR_Counter ]] = read_adc(ADC_READ_ONLY);    // Read the Distance
     IR_Temp_Proximity[ IR_AN_Table[ IR_Counter ]] = abs(IR_light[IR_AN_Table[ IR_Counter ]] - IR_Temp_Proximity[ IR_AN_Table[ IR_Counter ] ]); // Substract the proximity to the ambiant value to obtain the correct distance value
     if(IR_Temp_Proximity[IR_AN_Table[ IR_Counter ]] < IR_Calibrate[IR_AN_Table[ IR_Counter ]])  // Check if the value is greater than the calibrated value
       IR_Proximity[IR_AN_Table[ IR_Counter ]] = 0;
     else
       IR_Proximity[IR_AN_Table[ IR_Counter ]] = IR_Temp_Proximity[IR_AN_Table[ IR_Counter ]] - IR_Calibrate[IR_AN_Table[ IR_Counter ]];
    IR_Counter++;
    set_adc_channel(IR_AN_Table[ IR_Counter ]);                                 // Set the analog input to next sensor
    delay_us(2);
    if(IR_Counter > 9)
    {
      output_low(IR_GROUP3);                                                    // Turn off the IR emitter of the third Group
      IR_Counter = 0;
      Sensors_Refreshed_Flag = 1;                                               // Set the flag to indicate that all the sensor was refresh
      Manual_Refresh_sensors = 0;                                               // reset the manual refresh flag, to refresh only one time   
      IR_ADC_flag++;
      set_adc_channel(VBAT_AN);                                                 // Set the analog input to measure the battery voltage
    }
    else
      read_adc(ADC_START_ONLY);                                                 // Start the new conversion
   }

}


//-----------------------------------------------------------//
//                  Internal Interrupts                     -//


#INT_TIMER1
void Sheduler_Interrupt(void)                                                   // Internal Task Manager, Interrupt every 250 us
{
   
   set_timer1(TIMER1_VALUE+get_timer1());                                       // set default value to get an interrupt each 250us


//--------------------------------------------------------------------------------//
//- Time Function                                                                -//
//--------------------------------------------------------------------------------//  
   if(++TimeTipDivider >= 4)
   {
      TimeTipDivider = 0;
      TimeTip++;                                                                // TimeTip incremented every 1 ms (counter up to 4294967296 ms = 1193 hours ...)
      if(MotorTime > 0)                                                         // If the motor must be stopped after n ms
      {
        if(++MotorTimeDivider >= 100)                                           // each unit is 10ms
        {
          MotorTimeDivider = 0;
          if(--MotorTime == 0)                                                  // If the time reach its end
          {
           PwmMotRight = 0;                                                     // Stop the motor
           PwmMotLeft = 0;
           Motor_Conversion();                                                  
          }
        
        }
      
      }
      if(Acceleration_Timer != 0)                                               // If an acceleration is in progress
      {
        if(--Acceleration_Timer == 0)                                           // Decrement the timer untill it reach 0
        {
         set_pwm1_duty(TimerMotRight);                                          // Reset the desired value of the two motors
         set_pwm3_duty(TimerMotLeft); 
        }
      }
      

//--------------------------------------------------------------------------------//
//- Read the value of the mode switches all the ms                               -//
//--------------------------------------------------------------------------------//
      Switchs  =   !input(MODE1);        // MODE1
      Switchs |= ((!input(MODE2))<<1);   // MODE2
      Switchs |= ((!input(MODE3))<<2);   // MODE3
   }

//--------------------------------------------------------------------------------//
//- manage the Auto mode of the LED, each LED is ON during 100ms                 -//
//--------------------------------------------------------------------------------//
   if(LED_mode != 0)                                                            // If one of the LED is in auto mode
   {
      switch(LED_Counter)
      {
         case 0:
            if(LED_mode & 0x10)                                                 // Check if the LED4 is in auto mode
               output_low(LED4);                                                // Turn OFF the LED4         
            if(LED_mode & 0x01)                                                 // Check if the LED0 is in auto mode
               output_high(LED0);                                               // Turn ON the LED0
            break;
         case 500:
            if(LED_mode & 0x01)                                                 // Check if the LED0 is in auto mode
               output_low(LED0);                                                // Turn OFF the LED0
            if(LED_mode &0x02)                                                  // Check if the LED1 is in auto mode
               output_high(LED1);                                               // then turn ON the LED1
            break;
         case 1000:
            if(LED_mode & 0x02)                                                 // Check if the LED1 is in auto mode
               output_low(LED1);                                                // Turn OFF the LED1
            if(LED_mode &0x04)                                                  // Check if the LED2 is in auto mode
               output_high(LED2);                                               // then turn ON the LED2
            break;         
         case 1500:
            if(LED_mode & 0x04)                                                 // Check if the LED2is in auto mode
               output_low(LED2);                                                // Turn OFF the LED2
            if(LED_mode &0x08)                                                  // Check if the LED3is in auto mode
               output_high(LED3);                                               // then turn ON the LED3
            break;    
         case 2000:
            if(LED_mode & 0x08)                                                 // Check if the LED2is in auto mode
               output_low(LED3);                                                // Turn OFF the LED2
            if(LED_mode &0x10)                                                  // Check if the LED3is in auto mode
               output_high(LED4);                                               // then turn ON the LED3
            break;             
      }
      if(++LED_Counter >= 2499)
         LED_Counter = 0;
   
   }

//--------------------------------------------------------------------------------//
//- IR Sensor Management  (10ms to refresh all the IR sensor)                    -//
//--------------------------------------------------------------------------------//     
 
 if( (Auto_Refresh_Sensors == 1) || (Manual_Refresh_sensors == 1) )
 {
       // Read the battery voltage
      if(IR_ADC_Flag == 0)
      {
         read_adc(ADC_START_ONLY);                                              // read the analog value of the proximity
      }
      // Read ambiant value
      else if(IR_ADC_Flag == 1)
      {
         read_adc(ADC_START_ONLY);                                              // Start the AD conversion to read the whole ambiant light value
      }
      // Turn on the IR emitter
      else if(IR_ADC_Flag == 2)
      {
         IR_ADC_Flag++;  
         output_high(IR_GROUP1);                                                // Turn on the IR emitter of Group1
         
      }      
      // Read proximity value of the first group
      else if(IR_ADC_Flag == 3)
      {
         read_adc(ADC_START_ONLY);                                              // read the analog value of the proximity
      }
      // Turn on the IR emitter
      else if(IR_ADC_Flag == 4)
      {
         IR_ADC_Flag++;  
         output_high(IR_GROUP2);                                                // Turn on the IR emitter of Group2
         
      }      
      // Read proximity value of the second group
      else if(IR_ADC_Flag == 5)
      {
         read_adc(ADC_START_ONLY);                                              // read the analog value of the proximity
      }
      // Turn on the IR emitter
      else if(IR_ADC_Flag == 6)
      {
         IR_ADC_Flag++;  
         output_high(IR_GROUP3);                                                // Turn on the IR emitter of Group3
         
      }      
      // Read proximity value of the third group
      else if(IR_ADC_Flag == 7)
      {
         read_adc(ADC_START_ONLY);                                              // read the analog value of the proximity
      }


      else
      {
         if(++IR_ADC_Flag > 40)                                                 // Restart the refresh of the IR sensor
           IR_ADC_Flag = 0;
      }

   }
}

#INT_TIMER3
void Buzzer_Interrupt(void)                                                     // Buzzer interrupt
{
  set_timer3(Buzzer_Timer+ get_timer3());                                       // Set the timer to match the frequency note
  output_bit(BUZZER,!input(BUZZER));                                            // Toggle the buzzer output
}

#INT_EXT
void TV_Remote_Interrupt(void)
{
   if( Auto_Refresh_TV_Remote == 1 )                                            // Only if the Auto refresh TV flag is set
   {
       TV_Counter=0;                                                            // Reset the TV Counter
       TV_table[TV_Counter] = !input(IR_IN);                                    // read the first start bit, invert it to match with the modulation of the receiver
       disable_interrupts(INT_EXT);
       setup_timer_0(T0_DIV_1  | T0_INTERNAL );                                 // The first time is longer to read on the End of the coding
       set_timer0(TIMER0_2100);
       enable_interrupts(INT_TIMER0);  
       TV_Data_pending = 1;                                                     // Indicate that a reception of a TV Data is in progress
   }
   
}

//--------------------------------------------------------------------------------//
//- Modulate at 36 kHz with 50 duty-cycle                                        -//
//--------------------------------------------------------------------------------//
void KJunior_IR_Send32x(void)
{
 unsigned int i = 0;
 
 for (i=0;i<32;i++)
  {
   output_bit(IR_OUT,1);
   delay_us(13);                                                                 // This value was choose to match exactly with the rc5 timing
   output_bit(IR_OUT,0);
   delay_us(12);                                                                 // This value was choose to match exactly with the rc5 timing
  }
}


#INT_TIMER0
void RC5_Decoding_Interrupt(void)
{
   int1 RC5_Bit = 0;
   if(TV_Data_pending == 1)                                                     // Verify if a data is coming on the receiver, or ...
   {
      set_timer0(TIMER0_1780+get_timer0());                                     // Interrupt every 1.780 ms
      if(++TV_Counter <= 13)
      {
         TV_Table[TV_Counter] = !input(IR_IN);                                  // Read the bit of the manchester coding
      }
      else
      {
         if(TV_Table[StartBit1] == 1 && TV_Table[StartBit2] == 1)               // Verify that the two start bit are correct (value must be 1)
         {
            // If correct, save the data and address of the receiveing command
            TV_RX_Toggle_Bit = TV_Table[ToggleBit];
            TV_ADDR = (TV_Table[AddrBit4] << 4) |(TV_Table[AddrBit3] << 3) | (TV_Table[AddrBit2] << 2) | (TV_Table[AddrBit1] << 1) | (TV_Table[AddrBit0]);
            TV_DATA = (TV_Table[DataBit5] << 5) | (TV_Table[DataBit4] << 4) | (TV_Table[DataBit3] << 3) | (TV_Table[DataBit2] << 2) | (TV_Table[DataBit1] << 1) | (TV_Table[DataBit0]);
            TV_DATA_Available = 1;                                              // Set the flag to know that a TV data is available
            if(Enable_TV_Remote_Control == 1)                                   // If the control remote is activate
               TV_Remote_Control();                                             // Set the speed for each motor
         }
         enable_interrupts(INT_EXT);                                            // Enable the external interrupt after receiving a complete data
         disable_interrupts(INT_TIMER0);                                        // Disable the timer 0 interrupt
         setup_timer_0(RTCC_OFF);                                               // stop the timer0
         bit_clear(INTCON,1);                                                   // Clear the INTF bit to avoid a interrupt on the RB port
         TV_Data_pending = 0;                                                   // Clear the flag to indicate that the data is completely received
      }
   }
   else if(TV_Data_emitting == 1)                                               // .. if a data must be send on the emitter
   {
      set_timer0(TIMER0_886 + get_timer0());                                    // Interrupt every 886 us   
      do
      {
         TV_Data_loop = 0;                                                      // reset the flag, the loop can be done only one times
         if(TV_Counter < 2)                                                     // the first 2 bits are always 1 (start bit)
            RC5_Bit = 1;
         else if(TV_Counter == 2)                                               // Toggle bit
            RC5_Bit = TV_TX_Toggle_Bit;
         else if(TV_Counter > 13)                                               // if all the bits are send, 
         {
            TV_Data_emitting = 0;                                               // Stop the emitting
            TV_TX_Toggle_Bit = !TV_TX_Toggle_Bit;                               // Change the toggle Bit for the next emitting
            enable_interrupts(INT_EXT);                                         // Enable the external interrupt after emitting a complete rc5 code
            disable_interrupts(INT_TIMER0);                                     // Disable the timer 0 interrupt
            setup_timer_0(RTCC_OFF);                                            // stop the timer0
            enable_interrupts(INT_TIMER1);
            bit_clear(INTCON,1);                                                // Clear the INTF bit to avoid a interrupt on the RB port
            TV_Counter_flag = 0;                                                // Set the flag and the rc5 bit to ensure the output will be down
            RC5_Bit = 1;                                                          
         }
         else if((TV_Counter > 8) && (TV_Counter <= 13))                        // The last 6 bits are the Data
         {
            if(TV_Data_send & (0x20 >> (TV_Counter - 8)))                       // Mask the Data to keep only the bit to send
               RC5_Bit = 1 ;                 
            else 
               RC5_Bit = 0;         
         }
         else                                                                   // Address Bits
         {
            if(TV_Addr_send & (0x10 >> (TV_Counter - 3)))                       // Mask the Data to keep only the bit to send
               RC5_Bit = 1 ;                 
            else 
               RC5_Bit = 0;         
         }      
         if((TV_Counter_flag == 0) && (RC5_bit == 0))                           // First phase of bit = 0
         {
            KJunior_IR_Send32x();                                               // Modulate the bit at 36kHz to send on the emitter
            TV_Counter_flag = 0;                                                // Clear the flag to go to the next bit,  
            TV_Counter++;                                                       // No need to make a second phase
            set_timer0(TIMER0_886);                                             // reset the timer0 to have a proper time
            bit_clear(PIR1,1);                                                  // clear the flag of the Timer2 interrupt
         }
         else if((TV_Counter_flag == 1) && (RC5_bit == 1))                      // Second phase when a bit is = 1
         {
            KJunior_IR_Send32x();                                               // Modulate the bit at 36kHz to send on the emitter
            TV_Counter++;                                                       // Increment the Counter to send the next bit
            TV_Counter_flag = 0; 
            TV_Data_loop = 1;
            set_timer0(TIMER0_886);                                             // reset the timer0 to have a proper time
            bit_clear(PIR1,1);                                                  // clear the flag of the Timer2 interrupt         
         }
         else
         {
            TV_Counter += TV_Counter_Flag;                                      // If the flag is set (second phase) increment the counter
            TV_Counter_flag = !TV_Counter_flag;                                 // Change phase of bit
            output_low(IR_OUT);                                                 // Clear the IR output
         
         }
      
      }while(TV_Data_loop == 1);                                                // loop to manage the case when a 1 is following by a zero (emitting two times with no interruption)
   }
   else                                                                         // Otherwise 
   {
      enable_interrupts(INT_EXT);                                               // Enable the external interrupt 
      disable_interrupts(INT_TIMER0);                                           // Disable the timer 0 interrupt
      setup_timer_0(RTCC_OFF);                                                  // stop the timer0
      bit_clear(INTCON,1);                                                      // Clear the INTF bit to avoid a interrupt on the RB port

   }
   
}

void __default()
{
  if(SerialPort == SERIAL_USB)
   fprintf(USB, "Unknown Command ?!\r\n" );
  else
   fprintf(BT, "Unknown Command ?!\r\n" );
}

//--------------------------------------------------------------------------------//
//- Reset the KJunior uC                                                         -//
//--------------------------------------------------------------------------------//  
void __Z()
{
  if(SerialPort == SERIAL_USB)
   fprintf(USB,"z\r\n");
  else
   fprintf(BT,"z\r\n");
  
  reset_cpu();
}

//--------------------------------------------------------------------------------//
//- Set the speed of the 2 motors during n second. Value are +/- 20 for the speed //
//  and 0-255 for the time (unit base is the ms) 
//--------------------------------------------------------------------------------//
void __A(void)
{
   unsigned char Arg[5];
   unsigned char i, j;
   signed int8 MotG_temp;
   i = 2;                                                                       // Begin with the 3 char (after the first ",")
   j = 0;
   // While there no END of line "\n" or End of Char ",", place the value in a table to convert it 
   while((SerialBuffer[ i ] != ',') &&  (SerialBuffer[ i ] != 10) && (SerialBuffer[ i ] != 13))
   {
      Arg[j] = SerialBuffer[ i ];
      i++;     
      j++;
   }
   Arg[j] ='\0';                                                                // PLace a End of sentence at the end of the values
   MotG_Temp = atoi(Arg);                                                       // Convert the table of value into a signed int8
   if((SerialBuffer[ i ] == 10) || (SerialBuffer[ i ] == 13))                   // If the second argument is not set (i.e. "D,20\r\n") return a error
   {
     if(SerialPort == SERIAL_USB)
      fprintf(USB,"Unknown Command ?!\r\n" );
     else
      fprintf(BT,"Unknown Command ?!\r\n" );
   }
   else
   {
      i++;
      j = 0;
      // While there no END of line "\n" place the value in a table to convert it 
      while((SerialBuffer[ i ] != ',') &&  (SerialBuffer[ i ] != 10) && (SerialBuffer[ i ] != 13))
      {
         Arg[j] = SerialBuffer[ i ];
         i++;     
         j++;
      }
      Arg[j] ='\0';                                                             // PLace a End of sentence at the end of the values
      if((SerialBuffer[ i ] == 10) || (SerialBuffer[ i ] == 13))                // If the second argument is not set (i.e. "D,20\r\n") return a error
      {
        if(SerialPort == SERIAL_USB)
          fprintf(USB,"Unknown Command ?!\r\n" );
        else
          fprintf(BT,"Unknown Command ?!\r\n" );
      }
      else
      {
        PwmMotLeft = MotG_Temp;
        PwmMotRight = atoi(Arg);  
        i++;
        j = 0;
        // While there no END of line "\n" place the value in a table to convert it 
        while((SerialBuffer[ i ] != 10) && (SerialBuffer[ i ] != 13))
        {
           Arg[j] = SerialBuffer[ i ];
           i++;     
           j++;
        }
        Arg[j] ='\0';                                                           // PLace a End of sentence at the end of the values        
        if(PwmMotLeft >20)                                                      // Limit the minimum and maximum PWM value to -20 and 20
           PwmMotLeft = 20;
        else if(PwmMotLeft < -20) 
           PwmMotLeft = -20;
        if(PwmMotRight >20)                                                     // Limit the minimum and maximum PWM value to -20 and 20
          PwmMotRight = 20;
        else if(PwmMotRight < -20) 
          PwmMotRight = -20;           
        MotorTime = atoi(Arg);                                                  // Convert the table of value into a unsigned char               
        Motor_Conversion();                                                     // Configure the PWM output
        if(SerialPort == SERIAL_USB)
          fprintf(USB,"a\r\n"); 
        else
          fprintf(BT,"a\r\n"); 
      }
      
   }
}

//--------------------------------------------------------------------------------//
//- Read the KJunior OS version and revision                                     -//
//--------------------------------------------------------------------------------//  
void __B(void)
{
  if(SerialPort == SERIAL_USB)
   fprintf(USB, "b,%s-%02d\r\n" , KJ_FW_VERSION,KJ_FW_REVISION );
  else
   fprintf(BT, "b,%s-%02d\r\n" , KJ_FW_VERSION,KJ_FW_REVISION );
}

//--------------------------------------------------------------------------------//
//- Set the speed of the 2 motors. Valure are +/- 20 for each one                -//
//--------------------------------------------------------------------------------//
void __D(void)
{
   unsigned char Arg[5];
   unsigned char i, j;
   signed int8 MotG_temp;
   i = 2;                                                                       // Begin with the 3 char (after the first ",")
   j = 0;
   // While there no END of line "\n" or End of Char ",", place the value in a table to convert it 
   while((SerialBuffer[ i ] != ',') &&  (SerialBuffer[ i ] != 10) && (SerialBuffer[ i ] != 13))
   {
      Arg[j] = SerialBuffer[ i ];
      i++;     
      j++;
   }
   Arg[j] ='\0';                                                                // PLace a End of sentence at the end of the values
   MotG_Temp = atoi(Arg);                                                       // Convert the table of value into a signed int8
   if((SerialBuffer[ i ] == 10) || (SerialBuffer[ i ] == 13))                   // If the second argument is not set (i.e. "D,20\r\n") return a error
   {
    if(SerialPort == SERIAL_USB)
      fprintf(USB,"Unknown Command ?!\r\n" );
    else
      fprintf(BT,"Unknown Command ?!\r\n" );
   }
   else
   {
      i++;
      j = 0;
      // While there no END of line "\n" place the value in a table to convert it 
      while((SerialBuffer[ i ] != 10) && (SerialBuffer[ i ] != 13))
      {
         Arg[j] = SerialBuffer[ i ];
         i++;     
         j++;
      }
      Arg[j] ='\0';                                                             // PLace a End of sentence at the end of the values
      PwmMotLeft = MotG_Temp;
      if(PwmMotLeft >20)                                                        // Limit the minimum and maximum PWM value to -20 and 20
         PwmMotLeft = 20;
      else if(PwmMotLeft < -20) 
         PwmMotLeft = -20;
      PwmMotRight = atoi(Arg);                                                  // Convert the table of value into a signed int8               
      if(PwmMotRight >20)                                                       // Limit the minimum and maximum PWM value to -20 and 20
         PwmMotRight = 20;
      else if(PwmMotRight < -20) 
         PwmMotRight = -20;
      Motor_Conversion();
      if(SerialPort == SERIAL_USB)
        fprintf(USB,"d\r\n");     
      else
        fprintf(BT,"d\r\n");     
      
   }
}
//--------------------------------------------------------------------------------//
//- Read the Speed of the two motors (-20 to +20)                                -//
//--------------------------------------------------------------------------------//       
void __E()
{
  if(SerialPort == SERIAL_USB)
   fprintf(USB,"e,%d,%d\r\n",PwmMotLeft,PwmMotRight);
  else
   fprintf(BT,"e,%d,%d\r\n",PwmMotLeft,PwmMotRight);
}
//--------------------------------------------------------------------------------//
//- Set the frequency of the buzzer, 0 = Off , 1 = 500Hz, 100 = 5kHz             -//
//--------------------------------------------------------------------------------//              
void __H(void)
{
   unsigned char Arg[5];
   unsigned char i, j;
   i = 2;                                                                       // Begin with the 3 char (after the first ",")
   j = 0;
   // While there no END of line "\n" or End of Char ",", place the value in a table to convert it 
   while((SerialBuffer[ i ] != 10) && (SerialBuffer[ i ] != 13))
   {
      Arg[j] = SerialBuffer[ i ];
      i++;     
      j++;
   }
   Arg[j] ='\0';                                                                // PLace a End of sentence at the end of the values
   buzzValue = atoi(Arg);                                                       // Convert the table of value into a unsigned int8
   if(buzzvalue > BUZ_NUMBER)                                                   // Limit the value to 100
      buzzValue = BUZ_NUMBER;
   Set_Freq_note();                                                             // Convert the value to the corresponding note
   if(SerialPort == SERIAL_USB)
     fprintf(USB,"h\r\n");                                                      // Send the response
   else
     fprintf(BT,"h\r\n");                                                       // Send the response

}

//--------------------------------------------------------------------------------//
//- Calibrate the IR Sensor                                                      -//
//--------------------------------------------------------------------------------//  
void __K()
{
   unsigned char i,j,Eeprom_temp;
   signed int16 IR_Temp_Calibrate[12];
   if(SerialPort == SERIAL_USB)                                                 // If a serial cable is plugged, do not calibrate the IR (as it can disturb the measure)
     fprintf(USB,"Couldn't calibrate with the USB cable plugged\r\n");          // Send the response
   else
   {
     fprintf(BT,"Place the K-Junior on a surface without obstacle near from it.\n\r"); // Send the response
     fprintf(BT,"Press ENTER to proceed\n\r");
     SerialCommandOK = 0;
     for(i=0;i<=GROUNDRIGHT;i++)
     {
       IR_Calibrate[i]  = 0;                                                     // Reset the calibrated value    
       IR_Temp_Calibrate[i] = 0;
     }
     while(SerialCommandOK == 0);                                               // Wait the ENTER press
     Auto_Refresh_Sensors = 0;
     for(j = 0; j < 8; j++)
     {
       Sensors_Refreshed_Flag = 0;                                                // Start a new measure of the IR sensor
       Manual_Refresh_sensors = 1;
       while(Sensors_Refreshed_Flag == 0);                                        // Wait until the sensor are refreshed
       for(i=0;i<=REAR;i++)
       {
         IR_Temp_Calibrate[i] += IR_Proximity[i];                                 // Save the value of the proximity when no obstacle are present
       }
     }
     fprintf(BT,"Now return the K-Junior. The ground sensor must be free of obstacle.\n\r"); // Send the response
     fprintf(BT,"Press ENTER to proceed\n\r");
     SerialCommandOK = 0;
     while(SerialCommandOK == 0);                                               // Wait the ENTER press
     for(j = 0; j < 8; j++)
     {
       Sensors_Refreshed_Flag = 0;                                                // Start a new measure of the IR sensor
       Manual_Refresh_sensors = 1;
       while(Sensors_Refreshed_Flag == 0);                                        // Wait until the sensor are refreshed
       for(i=GROUNDFRONTLEFT ;i<=GROUNDRIGHT;i++)
         IR_Temp_Calibrate[i] += IR_Proximity[i];                                        // Save the value of the proximity when no obstacle are present
     }
     for(i = 0; i<=GROUNDRIGHT; i++)
     {
       IR_Calibrate[i] = IR_Temp_Calibrate[i] >> 3;                             // Divide all the Calibrated value and store them in the final table
       IR_Calibrate[i] += IR_CALIB_TH;
       Eeprom_temp = IR_Calibrate[i] & 0x00FF;                                  // Save the calibrate data in the EEPROM
       write_eeprom(EEPROM_ADD*2*i,Eeprom_temp);
       Eeprom_temp = (IR_Calibrate[i] & 0xFF00) >> 8;
       write_eeprom((EEPROM_ADD*2*i)+1,Eeprom_temp);
       
     }
     Auto_Refresh_Sensors = 1;
     fprintf(BT,"Calibration done\n\r");                                        // Send the response
     

   }
}


//--------------------------------------------------------------------------------//
//- Scan the I2C Bus                                                             -//
//--------------------------------------------------------------------------------//  
void __J()
{
   unsigned char i;
   unsigned char TempVal;
   printf("j");
   for(i=3;i<254;i=i+2)                                                         // Try all the available I2C address (0x00 to 0xFF)
   {
      i2c_start();
      if(i2c_write(i-1)==0)                                                     // If a device is detected
      {
         i2c_write(0x00);                                                       // Version Register
         i2c_start();
         i2c_write(i);
         TempVal=i2c_read(0);                                                   // Read the Version register to validate the communication
         i2c_stop();
         if(SerialPort == SERIAL_USB)
           fprintf(USB,",%2x",i-1);
         else
           fprintf(BT,",%2x",i-1); 
      }
      else
      {
         i2c_stop();                                                            // Stop the I2C communication
      }
   }
   if(SerialPort == SERIAL_USB)
     fprintf(USB,"\r\n");
   else
     fprintf(BT,"\r\n");
}
//--------------------------------------------------------------------------------//
//- Set the LED value                                                            -//
//--------------------------------------------------------------------------------//  
//#separate
void __L(void)
{
   unsigned char LED_temp;

  switch(SerialBuffer[2])
   {
      case '0':
         LED_temp = LED0;
         break;
      case '1':
         LED_temp = LED1;
         break;
      case '2':
         LED_temp = LED2;
         break;
      case '3':
         LED_temp = LED3;
         break;
      case '4':
         LED_temp = LED4;
         break;
      default:
         if(SerialPort == SERIAL_USB)
           fprintf(USB,"Unknown Command ?!\r\n" );
         else
           fprintf(BT,"Unknown Command ?!\r\n" );
         break;
   }
   if(SerialBuffer[4] == '3')                                                   // Activate the auto mode of the LED
      LED_Mode |= (0x01 << (SerialBuffer[2] - '0'));
   else
   {
      if(SerialBuffer[4] == '2')                                                // Toggle the Selected LED
      {
         if(input(LED_temp))
            output_low(LED_TEMP);
         else
            output_high(LED_TEMP);
      }
      else if(SerialBuffer[4] == '0')
          output_low(LED_temp);                                                 // Turn OFF the selected LED
      else                                                  
         output_high(LED_temp);                                                 // Turn ON the selected LED
      LED_Mode &= 0xff - (0x01 << (SerialBuffer[2] - '0'));                     // Reset the flag of the auto mode
   }               
   if(SerialPort == SERIAL_USB)
     fprintf(USB,"l\r\n");
   else
     fprintf(BT,"l\r\n");
}


//--------------------------------------------------------------------------------//
//- Return the values of the IR Proximity sensor                                 -//
//--------------------------------------------------------------------------------//   
//#separate
void __N(void)
{
  if(SerialPort == SERIAL_USB)
   fprintf(USB, "n,%04ld,%04ld,%04ld,%04ld,%04ld,%04ld,%04ld,%04ld,%04ld,%04ld\r\n" , IR_Proximity[ LEFT ] , IR_Proximity[ FrontLEFT ] ,
         IR_Proximity[ FRONT ] , IR_Proximity[ FRONTRIGHT] , IR_Proximity[ RIGHT] , IR_Proximity[ REAR ] ,
         IR_Proximity[ GROUNDLEFT ] , IR_Proximity[ GROUNDFRONTLEFT ], IR_Proximity[ GROUNDFRONTRIGHT ] , IR_Proximity[ GROUNDRIGHT ]  );
  else
   fprintf(BT, "n,%04ld,%04ld,%04ld,%04ld,%04ld,%04ld,%04ld,%04ld,%04ld,%04ld\r\n" , IR_Proximity[ LEFT ] , IR_Proximity[ FrontLEFT ] ,
         IR_Proximity[ FRONT ] , IR_Proximity[ FRONTRIGHT] , IR_Proximity[ RIGHT] , IR_Proximity[ REAR ] ,
         IR_Proximity[ GROUNDLEFT ] , IR_Proximity[ GROUNDFRONTLEFT ], IR_Proximity[ GROUNDFRONTRIGHT ] , IR_Proximity[ GROUNDRIGHT ]  );
  
}
//--------------------------------------------------------------------------------//
//- Return the values of the IR Ambient light sensor                             -//
//--------------------------------------------------------------------------------//                  
//#separate
void __O(void)
{
  if(SerialPort == SERIAL_USB)
   fprintf(USB, "o,%04ld,%04ld,%04ld,%04ld,%04ld,%04ld,%04ld,%04ld,%04ld,%04ld\r\n" , IR_Light[ LEFT ] , IR_Light[ FrontLEFT ] ,
         IR_Light[ FRONT ] , IR_Light[ FRONTRIGHT] , IR_Light[ RIGHT] , IR_Light[ REAR ] ,
         IR_Light[ GROUNDLEFT ] , IR_Light[ GROUNDFRONTLEFT ], IR_Light[ GROUNDFRONTRIGHT ] , IR_Light[ GROUNDRIGHT ]  );
  else
   fprintf(BT, "o,%04ld,%04ld,%04ld,%04ld,%04ld,%04ld,%04ld,%04ld,%04ld,%04ld\r\n" , IR_Light[ LEFT ] , IR_Light[ FrontLEFT ] ,
         IR_Light[ FRONT ] , IR_Light[ FRONTRIGHT] , IR_Light[ RIGHT] , IR_Light[ REAR ] ,
         IR_Light[ GROUNDLEFT ] , IR_Light[ GROUNDFRONTLEFT ], IR_Light[ GROUNDFRONTRIGHT ] , IR_Light[ GROUNDRIGHT ]  );

}

//--------------------------------------------------------------------------------//
//- Read on the I2C Bus                                                          -//
//--------------------------------------------------------------------------------// 
//#separate
void __R(void)
{
   unsigned char memaddress = 0;
   unsigned char rcvalue = 0;
   unsigned char nb_bytes = 0;
   unsigned char TempVal;
   memaddress = chartohex(SerialBuffer[2]);
   memaddress = (memaddress<<4) + chartohex(SerialBuffer[3]);
   rcvalue = chartohex(SerialBuffer[5]);
   rcvalue = (rcvalue<<4) + chartohex(SerialBuffer[6]);
   nb_bytes = chartohex(SerialBuffer[8]);
   nb_bytes = (nb_bytes<<4) + chartohex(SerialBuffer[9]);
   i2c_start();
   i2c_write( memaddress );                                      // Writing Address of the module
   i2c_write( rcvalue );                                         // Writing Address of the register
   i2c_start();
   i2c_write( memaddress + 1 );                                  // Writing Address of the module in Read Mode
   if(SerialPort == SERIAL_USB)
     fprintf(USB,"r");
   else
     fprintf(BT,"r");
   while(nb_bytes> 1)
   {
     TempVal = i2c_read();
     if(SerialPort == SERIAL_USB)
       fprintf(USB,",%03u",TempVal);
     else
       fprintf(BT,",%03u",TempVal);
     nb_bytes--;
   }
   TempVal = i2c_read(0);
   if(SerialPort == SERIAL_USB)
     fprintf(USB,",%03u\r\n",TempVal);
   else
     fprintf(BT,",%03u\r\n",TempVal);
   i2c_stop();
}
//--------------------------------------------------------------------------------//
//- Return the receiving TV data                                                 -//
//--------------------------------------------------------------------------------// 
//#separate
void __T()
{
 if(SerialPort == SERIAL_USB)
   fprintf(USB, "t,%03u,%03u\r\n" , TV_ADDR,TV_DATA );
 else
   fprintf(BT, "t,%03u,%03u\r\n" , TV_ADDR,TV_DATA );
}
//--------------------------------------------------------------------------------//
//- Send a RC5 data on the IR emitter                                            -//
//--------------------------------------------------------------------------------// 
//#separate
void __V()
{
   unsigned char Arg[5];
   unsigned char i, j;
   i = 2;                                                                       // Begin with the 3 char (after the first ",")
   j = 0;
   // While there no END of line "\n" or End of Char ",", place the value in a table to convert it 
   while((SerialBuffer[ i ] != ',') &&  (SerialBuffer[ i ] != 10) && (SerialBuffer[ i ] != 13))
   {
      Arg[j] = SerialBuffer[ i ];
      i++;     
      j++;
   }
   Arg[j] ='\0';                                                                // PLace a End of sentence at the end of the values
   TV_Addr_send = atoi(Arg);                                                    // Convert the table of value into a unsigned int8
   if((SerialBuffer[ i ] == 10) || (SerialBuffer[ i ] == 13))                   // If the second argument is not set (i.e. "D,20\r\n") return a error
   {
     if(SerialPort == SERIAL_USB)
      fprintf(USB,"Unknown Command ?!\r\n" );
     else
      fprintf(BT,"Unknown Command ?!\r\n" );
   }
   else
   {
      i++;
      j = 0;
      // While there no END of line "\n" place the value in a table to convert it 
      while((SerialBuffer[ i ] != 10) && (SerialBuffer[ i ] != 13))
      {
         Arg[j] = SerialBuffer[ i ];
         i++;     
         j++;
      }
      Arg[j] ='\0';                                                             // PLace a End of sentence at the end of the values
      TV_Data_send = atoi(Arg);                                                 // Convert the table of value into a unsigned int8
      TV_Data_emitting = 1;                                                     // Set the flag to indicate that a mesasge must be send
      if(SerialPort == SERIAL_USB)
        fprintf(USB,"v\r\n");
      else
        fprintf(BT,"v\r\n");
      while(TV_Data_pending == 1);                                              // If a IR data is receiving, wait until it's done
      set_timer0(TIMER0_886);
      setup_timer_0(T0_INTERNAL | T0_DIV_1);                                    // Interrupt every 886 us
      TV_Counter = 0;                                                           // reset TV_Counter 
      TV_Counter_flag = 0;                                                      // reset the sending phase flag
      disable_interrupts(INT_EXT);                                              // Disable interrupt of the receiving IR, to avoid receiving its own data
      disable_interrupts(INT_TIMER1);                                           // disable the timer1 interrupt to avoid perturbation
      enable_interrupts(INT_TIMER0);                                            // enable the timer0 interrupt to start the emitting
   }      
      
}

//--------------------------------------------------------------------------------//
//- Write a data on the I2C Bus                                                  -//
//--------------------------------------------------------------------------------// 
//#separate
void __W(void)
{
   unsigned char rcvalue = 0;
   rcvalue = chartohex(SerialBuffer[2]);
   rcvalue = (rcvalue<<4) + chartohex(SerialBuffer[3]);
   i2c_start();
   i2c_write( rcvalue );                                         // Writing Address of the module
   rcvalue = chartohex(SerialBuffer[5]);
   rcvalue = (rcvalue<<4) + chartohex(SerialBuffer[6]);
   i2c_write( rcvalue );                                         // Writing Address of the register
   rcvalue = chartohex(SerialBuffer[8]);
   rcvalue = (rcvalue<<4) + chartohex(SerialBuffer[9]);
   i2c_write( rcvalue );                                         // Writing Data in the register
   i2c_stop();
   if(SerialPort == SERIAL_USB)
     fprintf(USB,"w\r\n");
   else
     fprintf(BT,"w\r\n");

}

void __X(void)
{
 if(SerialPort == SERIAL_USB)
 {
    fprintf(USB,"x%c%c%c%c",IR_Proximity[ LEFT ] & 0x00FF, (IR_Proximity[ LEFT ]>>8) & 0x00FF  , IR_Proximity[ FrontLEFT ]  & 0xFF , (IR_Proximity[ FrontLEFT ] >> 8)  & 0xFF);
    fprintf(USB,"%c%c%c%c",IR_Proximity[ FRONT ]  & 0xFF, (IR_Proximity[ FRONT ] >> 8) & 0xFF , IR_Proximity[ FRONTRIGHT] & 0xFF, (IR_Proximity[ FRONTRIGHT] >> 8) & 0xFF );
    fprintf(USB,"%c%c%c%c",IR_Proximity[ RIGHT] & 0xFF, (IR_Proximity[ RIGHT] >> 8) & 0xFF , IR_Proximity[ REAR ] & 0xFF ,(IR_Proximity[ REAR ] >> 8) & 0xFF); 
    fprintf(USB,"%c%c%c%c",IR_Proximity[ GROUNDLEFT ] & 0xFF, (IR_Proximity[ GROUNDLEFT ] >> 8) & 0xFF , IR_Proximity[ GROUNDFRONTLEFT ] & 0xFF, (IR_Proximity[ GROUNDFRONTLEFT ] >> 8) & 0xFF);
    fprintf(USB,"%c%c%c%c",IR_Proximity[ GROUNDFRONTRIGHT ] & 0xFF, (IR_Proximity[ GROUNDFRONTRIGHT]>>8) & 0xFF  , IR_Proximity[ GROUNDRIGHT ] & 0xFF, (IR_Proximity[ GROUNDRIGHT ] >> 8) & 0xFF );
    fprintf(USB,"%c%c%c%c",IR_Light[ LEFT ] & 0x00FF, (IR_Light[ LEFT ]>>8) & 0x00FF  , IR_Light[ FrontLEFT ]  & 0xFF , (IR_Light[ FrontLEFT ] >> 8)  & 0xFF);
    fprintf(USB,"%c%c%c%c",IR_Light[ FRONT ]  & 0xFF, (IR_Light[ FRONT ] >> 8) & 0xFF , IR_Light[ FRONTRIGHT] & 0xFF, (IR_Light[ FRONTRIGHT] >> 8) & 0xFF );
    fprintf(USB,"%c%c%c%c",IR_Light[ RIGHT] & 0xFF, (IR_Light[ RIGHT] >> 8) & 0xFF , IR_Light[ REAR ] & 0xFF ,(IR_Light[ REAR ] >> 8) & 0xFF); 
    fprintf(USB,"%c%c%c%c",IR_Light[ GROUNDLEFT ] & 0xFF, (IR_Light[ GROUNDLEFT ] >> 8) & 0xFF , IR_Light[ GROUNDFRONTLEFT ] & 0xFF, (IR_Light[ GROUNDFRONTLEFT ] >> 8) & 0xFF);
    fprintf(USB,"%c%c%c%c",IR_Light[ GROUNDFRONTRIGHT ] & 0xFF, (IR_Light[ GROUNDFRONTRIGHT]>>8) & 0xFF  , IR_Light[ GROUNDRIGHT ] & 0xFF, (IR_Light[ GROUNDRIGHT ] >> 8) & 0xFF );
    fprintf(USB,"%c%c%c%c%c%c%c%c%c\r\n",PwmMotLeft, PwmMotRight, Switchs, TV_ADDR, TV_DATA, TimeTip & 0xFF, (TimeTip >> 8) &0xFF, (TimeTip >> 16) & 0xFF, (TimeTip >> 24) &0xFF );
}
 else
 {
    fprintf(BT,"x%c%c%c%c",IR_Proximity[ LEFT ] & 0x00FF, (IR_Proximity[ LEFT ]>>8) & 0x00FF  , IR_Proximity[ FrontLEFT ]  & 0xFF , (IR_Proximity[ FrontLEFT ] >> 8)  & 0xFF);
    fprintf(BT,"%c%c%c%c",IR_Proximity[ FRONT ]  & 0xFF, (IR_Proximity[ FRONT ] >> 8) & 0xFF , IR_Proximity[ FRONTRIGHT] & 0xFF, (IR_Proximity[ FRONTRIGHT] >> 8) & 0xFF );
    fprintf(BT,"%c%c%c%c",IR_Proximity[ RIGHT] & 0xFF, (IR_Proximity[ RIGHT] >> 8) & 0xFF , IR_Proximity[ REAR ] & 0xFF ,(IR_Proximity[ REAR ] >> 8) & 0xFF); 
    fprintf(BT,"%c%c%c%c",IR_Proximity[ GROUNDLEFT ] & 0xFF, (IR_Proximity[ GROUNDLEFT ] >> 8) & 0xFF , IR_Proximity[ GROUNDFRONTLEFT ] & 0xFF, (IR_Proximity[ GROUNDFRONTLEFT ] >> 8) & 0xFF);
    fprintf(BT,"%c%c%c%c",IR_Proximity[ GROUNDFRONTRIGHT ] & 0xFF, (IR_Proximity[ GROUNDFRONTRIGHT]>>8) & 0xFF  , IR_Proximity[ GROUNDRIGHT ] & 0xFF, (IR_Proximity[ GROUNDRIGHT ] >> 8) & 0xFF );
    fprintf(BT,"%c%c%c%c",IR_Light[ LEFT ] & 0x00FF, (IR_Light[ LEFT ]>>8) & 0x00FF  , IR_Light[ FrontLEFT ]  & 0xFF , (IR_Light[ FrontLEFT ] >> 8)  & 0xFF);
    fprintf(BT,"%c%c%c%c",IR_Light[ FRONT ]  & 0xFF, (IR_Light[ FRONT ] >> 8) & 0xFF , IR_Light[ FRONTRIGHT] & 0xFF, (IR_Light[ FRONTRIGHT] >> 8) & 0xFF );
    fprintf(BT,"%c%c%c%c",IR_Light[ RIGHT] & 0xFF, (IR_Light[ RIGHT] >> 8) & 0xFF , IR_Light[ REAR ] & 0xFF ,(IR_Light[ REAR ] >> 8) & 0xFF); 
    fprintf(BT,"%c%c%c%c",IR_Light[ GROUNDLEFT ] & 0xFF, (IR_Light[ GROUNDLEFT ] >> 8) & 0xFF , IR_Light[ GROUNDFRONTLEFT ] & 0xFF, (IR_Light[ GROUNDFRONTLEFT ] >> 8) & 0xFF);
    fprintf(BT,"%c%c%c%c",IR_Light[ GROUNDFRONTRIGHT ] & 0xFF, (IR_Light[ GROUNDFRONTRIGHT]>>8) & 0xFF  , IR_Light[ GROUNDRIGHT ] & 0xFF, (IR_Light[ GROUNDRIGHT ] >> 8) & 0xFF );
    fprintf(BT,"%c%c%c%c%c%c%c%c%c\r\n",PwmMotLeft, PwmMotRight, Switchs, TV_ADDR, TV_DATA, TimeTip & 0xFF, (TimeTip >> 8) &0xFF, (TimeTip >> 16) & 0xFF, (TimeTip >> 24) &0xFF );
 
 }

}

void __C(void)
{
  unsigned char BT_name;

  SerialCounter = 0;  
  SerialCommandOK = 0;
  BT_config = 1;                                                                // Set the flag to receive more than one line
  delay_ms(500);
  fprintf(BT,"+++");                                                                // Deconnect the Bluetooth communication
  delay_ms(800);
  SerialCounter = 0;  
  SerialCommandOK = 0;
  fprintf(BT,"SET\n");                                                              // Ask for the different info of the Bluetooth module
  delay_ms(1500);
  BT_Name = SerialBuffer[54];                                                   // Save the letter which define the Type of K-Junior
  SerialCounter = 0;                                                            // Reset the serial buffer
  fprintf(BT,"SELECT 0\n");                                                         // Re-active the communication
  delay_ms(1000);                                                               // Wait until the communication has restart
  BT_config = 0;
  if(SerialPort == SERIAL_USB)
    fprintf(USB,"c,%c\r\n",BT_name) ;                                           // Send the return command and the type of the K-Junior (0 = Standard, P = Pedagogique)
  else
    fprintf(BT,"c,%c\r\n",BT_name) ;                                            // Send the return command and the type of the K-Junior (0 = Standard, P = Pedagogique)
}

//--------------------------------------------------------------------------------//
//- Write many Data on the I2C Bus                                               -//
//--------------------------------------------------------------------------------// 
//#separate
void __Y(void)
{
   unsigned char Addresse = 0;
   unsigned char registre = 0;
   unsigned char rcvalue[50];
   unsigned char nb_bytes = 0;
   unsigned char i;
   Addresse = chartohex(SerialBuffer[2]);
   Addresse = (Addresse<<4) + chartohex(SerialBuffer[3]);

   registre = chartohex(SerialBuffer[5]);
   registre = (registre<<4) + chartohex(SerialBuffer[6]);
   nb_bytes = chartohex(SerialBuffer[8]);
   nb_bytes = (nb_bytes<<4) + chartohex(SerialBuffer[9]);        // Number of Data to Write

   for(i=0;i<nb_bytes;i++)
   {
      rcvalue[i] = chartohex(SerialBuffer[11+i+i+i]);
      rcvalue[i] = (rcvalue[i]<<4) + chartohex(SerialBuffer[12+i+i+i]);
      //delay_ms(1);                     // Needed for module ???
   }
   
   i2c_start();
   i2c_write( Addresse );                                           // Writing Address of the module
   i2c_write( registre );                                           // Writing Address of the register
   for(i=0;i<nb_bytes;i++)
   {
      i2c_write( rcvalue[i] );                                        // Writing Data in the register
   }


   i2c_stop();
   if(SerialPort == SERIAL_USB)
     fprintf(USB,"y\r\n");
   else
     fprintf(BT,"y\r\n");
}
//--------------------------------------------------------------------------------//
//- This function will be call when a serial command is completely received      -//
//--------------------------------------------------------------------------------//  
//#separate
void SerialCommandHandler (void)
{

   // If the second char is not a "," or "\r" or "\n"
   if((SerialBuffer[ 1 ] != ',') &&  (SerialBuffer[ 1 ] != 10) && (SerialBuffer[ 1 ] != 13))
   {
      SerialCounter = 0;                                                        // Flush the buffer and do nothing
      SerialCommandOK = 0;                                                      // For the Bluetooth when the connection is not made (communication with USB)
   }
   else
   {
 
      switch( SerialBuffer[ 0 ] )
      {
   //--------------------------------------------------------------------------------//
   //- Turn the K-Junior on the left or the right for n ms                          -//
   //--------------------------------------------------------------------------------//            
         case 'A' :
           __A();
           break;
   //--------------------------------------------------------------------------------//
   //- Read the KJunior OS version and revision                                     -//
   //--------------------------------------------------------------------------------//            
         case 'B' :                                                             // KJOs Version
            __B();
            break;

         case 'C' :
            __C();
            break;
       
   //--------------------------------------------------------------------------------//
   //- Set the speed of the 2 motors. Valure are +/- 20 for each one                -//
   //--------------------------------------------------------------------------------//
         case 'D' :                                                             // Set Motors Speed
            __D();
            break;
   //--------------------------------------------------------------------------------//
   //- Read the Speed of the two motors (-20 to +20)                                -//
   //--------------------------------------------------------------------------------//               
         case 'E' :                                                             // Read Motors Speed
            __E();
            break;
   //--------------------------------------------------------------------------------//
   //- read the Time base in ms                                                     -//
   //--------------------------------------------------------------------------------//
         case 'F' :
           if(SerialPort == SERIAL_USB)
            fprintf(USB,"f,%ld\r\n" TimeTip);
           else
            fprintf(BT,"f,%ld\r\n" TimeTip);
            break;
   //--------------------------------------------------------------------------------//
   //- reset the Time base                                                          -//
   //--------------------------------------------------------------------------------//
         case 'G' : 
            TimeTip = 0;
            if(SerialPort == SERIAL_USB)
              fprintf(USB,"g\r\n");
            else
              fprintf(BT,"g\r\n");
            break;
   //--------------------------------------------------------------------------------//
   //- Set the frequency of the buzzer, 0 = Off , 1 = 20Hz, 100 = 2kHz              -//
   //--------------------------------------------------------------------------------//              
         case 'H' : 
            __H();
            break;
   //--------------------------------------------------------------------------------//
   //- read the value of the mode switch                                            -//
   //--------------------------------------------------------------------------------//                
         case 'I' : 
           if(SerialPort == SERIAL_USB)
            fprintf(USB, "i,%x\r\n" , Switchs);
           else
            fprintf(BT, "i,%x\r\n" , Switchs);
            break;
            
   //--------------------------------------------------------------------------------//
   //- Calibrate the IR sensor                                                      -//
   //--------------------------------------------------------------------------------//                
         case 'K' : 
            __K();
            break;


//--------------------------------------------------------------------------------//
//- Scan the I2C Bus                                                             -//
//--------------------------------------------------------------------------------//             
         case 'J' :                        // Scan I2C Bus
            __J();
            break;
         //case 'K' : Unused
   //--------------------------------------------------------------------------------//
   //- Set the LED value                                                            -//
   //--------------------------------------------------------------------------------//                
         case 'L' :   
            __L();
             break;
   //--------------------------------------------------------------------------------//
   //- Return the values of the IR Proximity sensor                                 -//
   //--------------------------------------------------------------------------------//                 
         case 'N' : 
            __N();
            break;
   //--------------------------------------------------------------------------------//
   //- Return the values of the IR Ambient light sensor                             -//
   //--------------------------------------------------------------------------------//                  
         case 'O' :                      
            __O();
            break;

 
//--------------------------------------------------------------------------------//
//- Read on the I2C Bus                                                          -//
//--------------------------------------------------------------------------------//  
         case 'R' :                        // Read I2C
            __R();
            break;
            
//--------------------------------------------------------------------------------//
//- Return the battery voltage                                                   -//
//--------------------------------------------------------------------------------//  
         case 'S' :                        // Read I2C
           if(SerialPort == SERIAL_USB)
            fprintf(USB, "s,%4lu\r\n" , BatteryVoltage);
           else
            fprintf(BT, "s,%4lu\r\n" , BatteryVoltage);
            break;

//--------------------------------------------------------------------------------//
//- Return the receiving TV data                                                 -//
//--------------------------------------------------------------------------------// 
         case 'T' :                        // Read TV Remote Sensor
            __T();
            break;

         case 'V' : 
            __V();
            break;
//--------------------------------------------------------------------------------//
//- Write a data on the I2C Bus                                                  -//
//--------------------------------------------------------------------------------//          
         case 'W' :                        // Write I2C
            __W();
            break;

//--------------------------------------------------------------------------------//
//- Read all K-Junior Data in binary mode                                        -//
//--------------------------------------------------------------------------------//
        
         case 'X' :   // Fast binary read
            __X();
            break;
   

 //--------------------------------------------------------------------------------//
//- Write many Data on the I2C Bus                                               -//
//--------------------------------------------------------------------------------//         
         case 'Y' :                                                           
            __Y();
            break;
   //--------------------------------------------------------------------------------//
   //- Reset the KJunior uC                                                         -//
   //--------------------------------------------------------------------------------//                 
         case 'Z' :
            __Z();
            break;
     
         default :   // Unknown message command
            __default();  
            break;
      }

   }
   SerialCounter = 0;
   SerialCommandOK = 0;
   

}


#INT_RDA 
void USB_Serial_Interrupt(void)
{
 unsigned char FLUSH;
   
   SerialPort = SERIAL_USB;
   while(kbhit(USB))                                                               // Read while data available
   {
      if((SerialCommandOK == 1) && (BT_config == 0))                            // If a command is still in traitment (and no config Bluetooth is in process), Flush the buffer
      {
         FLUSH = getc(USB);
      }
      else
      {      
         SerialBuffer[ SerialCounter ] = getc(USB);
         if((SerialBuffer[ SerialCounter ] == 13) || (SerialBuffer[ SerialCounter ] == 10))   // '\n' & '\r'
         { 
            SerialCommandOK = 1;                                                   // Set the Received command Flag
         }
         if (SerialCounter < ( SERIAL_BUFFER_SIZE-1 ))                             // To discard buffer overflow
         {
            SerialCounter++;
         }
      }
   }
      
   
}


#INT_RDA2 
void BT_Serial_Interrupt(void)
{
 unsigned char FLUSH;
   SerialPort = SERIAL_BT;
   while(kbhit(BT))                                                               // Read while data available
   {
      if((SerialCommandOK == 1) && (BT_config == 0))                            // If a command is still in traitment (and no config Bluetooth is in process), Flush the buffer
      {
         FLUSH = getc(BT);
      }
      else
      {      
         SerialBuffer[ SerialCounter ] = getc(BT);
         if((SerialBuffer[ SerialCounter ] == 13) || (SerialBuffer[ SerialCounter ] == 10))   // '\n' & '\r'
         { 
            SerialCommandOK = 1;                                                   // Set the Received command Flag
         }
         if (SerialCounter < ( SERIAL_BUFFER_SIZE-1 ))                             // To discard buffer overflow
         {
            SerialCounter++;
         }
      }
   }
}











