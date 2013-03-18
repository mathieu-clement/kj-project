//-------------------------------------------------------------------------------//
//-                             HemGripper Lib. 1.0                             -//
//-                                                                             -//
//-  Copyright (C) Frederic Lambercy, K-Team S.A. 2008                          -//
//-  This library is free software; you can redistribute it and/or              -//
//-  modify it under the terms of the GNU Lesser General Public                 -//
//-  License as published by the Free Software Foundation; either               -//
//-  version 2.1 of the License, or any later version.                          -//
//-                                                                             -//
//-  This library is distributed in the hope that it will be useful,            -//
//-  but WITHOUT ANY WARRANTY; without even the implied warranty of             -//
//-  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU          -//
//-  Lesser General Public License for more details.                            -//
//-                                                                             -//
//-  You should have received a copy of the GNU Lesser General Public           -//
//-  License along with this library; if not, write to the Free Software        -//
//-  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA  -//
//-                                                                             -//
//-                                                                             -//
//-                               __  __  ________                              -//
//- K-Team S.A.                  |  |/  /|__    __|___  _____  ___  ___         -//
//- Rue Galilee 9, Y-Park        |     / __ |  | _____|/  _  \|   \/   |        -//
//- 1400 Yverdon-les-Bains       |  |  \    |  | ____|/  /_\  |        |        -//
//- Switzerland                  |__|\__\   |__|______|_/   \_|__|\/|__|        -//
//- lambercy@k-team.com   tel:+41 24 423 8973 fax:+41 24 423 8960               -//
//-                                                                             -//
//-------------------------------------------------------------------------------//

#include <string.h>

#define HEMGR_I2C_ADDRESS           0x96
/* Register Address */
#define HEMGR_VERSION               0x30
#define ARM_POSITION_ADD            0x31
#define GRIPPER_POSITION_ADD        0x33
#define ARM_CONSIGN_ADD             0x35
#define GRIPPER_CONSIGN_ADD         0x37
#define ARM_Speed_ADD        0x39
#define GRIPPER_Speed_ADD    0x3A
#define ARM_DISABLE_ADD             0x3B
#define GRIPPER_DISABLE_ADD         0x3C
#define BATTERY_VOLTAGE_ADD         0x3D
#define BATTERY_CAPACITY_ADD        0x3F


void HemGripper_Init( void )
{
  delay_ms(1000);
}

char HemGripper_Read_Version( void )
{
   unsigned char value = 0x00;
   i2c_start();                                                // I2C Start Sequence
   i2c_write(HEMGR_I2C_ADDRESS);                               // HemGR I2C Address
   i2c_write(HEMGR_VERSION );                                  // Firmware version Register
   i2c_start();
   i2c_write(HEMGR_I2C_ADDRESS + 1 );                         // HemGripper I2C Read Address
   value = i2c_read(0);
   i2c_stop();                                                 // I2C Stop Sequence
   delay_ms(1);
   return value;
}
/* Read the actual Position of the Arm Servo */
unsigned int16 HemGripper_Read_Arm_Position(void)
{
   unsigned int16 value = 0;
   i2c_start();                                                // I2C Start Sequence
   i2c_write(HEMGR_I2C_ADDRESS);                               // HemGR I2C Address
   i2c_write(Arm_POSITION_ADD);                           // Arm position Register
   i2c_start();
   i2c_write(HEMGR_I2C_ADDRESS + 1 );                         // HemGripper I2C Read Address
   value = (unsigned int16)i2c_read()& 0x00FF ;
   value = value | ((unsigned int16)i2c_read(0) << 8);
   i2c_stop();                                                 // I2C Stop Sequence
   delay_ms(1);
   return value;
}

/* Read the actual Position of the Gripper Servo */
unsigned int16 HemGripper_Read_Gripper_Position(void)
{
   unsigned int16 value = 0;
   i2c_start();                                                // I2C Start Sequence
   i2c_write(HEMGR_I2C_ADDRESS);                               // HemGR I2C Address
   i2c_write(GRIPPER_POSITION_ADD);                            // Gripper Position Register
   i2c_start();
   i2c_write(HEMGR_I2C_ADDRESS + 1 );                         // HemGripper I2C Read Address
   value = (unsigned int16)i2c_read()& 0x00FF ;
   value = value | ((unsigned int16)i2c_read(0) << 8);
   i2c_stop();                                                 // I2C Stop Sequence
   delay_ms(1);
   return value;
}

/* Read the Consign of the Arm Servo */
unsigned int16 HemGripper_Read_Arm_Consign(void)
{
   unsigned int16 value = 0;
   i2c_start();                                                // I2C Start Sequence
   i2c_write(HEMGR_I2C_ADDRESS);                               // HemGR I2C Address
   i2c_write(Arm_CONSIGN_ADD);                            // Arm Consign Register
   i2c_start();
   i2c_write(HEMGR_I2C_ADDRESS + 1 );                         // HemGripper I2C Read Address
   value = (unsigned int16)i2c_read()& 0x00FF ;
   value = value | ((unsigned int16)i2c_read(0) << 8);
   i2c_stop();                                                 // I2C Stop Sequence
   delay_ms(1);
   return value;
}

/* Read the Consign of the Gripper Servo */
unsigned int16 HemGripper_Read_Gripper_Consign(void)
{
   unsigned int16 value = 0;
   i2c_start();                                                // I2C Start Sequence
   i2c_write(HEMGR_I2C_ADDRESS);                               // HemGR I2C Address
   i2c_write(GRIPPER_CONSIGN_ADD);                             // Gripper Consign Register
   i2c_start();
   i2c_write(HEMGR_I2C_ADDRESS + 1 );                         // HemGripper I2C Read Address
   value = (unsigned int16)i2c_read()& 0x00FF ;
   value = value | ((unsigned int16)i2c_read(0) << 8);
   i2c_stop();                                                 // I2C Stop Sequence
   delay_ms(1);
   return value;
}

/* Read the Speed of the Arm Servo */
unsigned char HemGripper_Read_Arm_Speed(void)
{
   unsigned char value = 0;
   i2c_start();                                                // I2C Start Sequence
   i2c_write(HEMGR_I2C_ADDRESS);                               // HemGR I2C Address
   i2c_write(Arm_Speed_ADD);                       // Arm Speed Register
   i2c_start();
   i2c_write(HEMGR_I2C_ADDRESS + 1 );                         // HemGripper I2C Read Address
   value = i2c_read(0);
   i2c_stop();                                                 // I2C Stop Sequence
   delay_ms(1);
   return value;
}

/* Read the Speed of the Gripper Servo */
unsigned char HemGripper_Read_Gripper_Speed(void)
{
   unsigned char value = 0;
   i2c_start();                                                // I2C Start Sequence
   i2c_write(HEMGR_I2C_ADDRESS);                               // HemGR I2C Address
   i2c_write(GRIPPER_Speed_ADD);                        // Gripper Speed Register
   i2c_start();
   i2c_write(HEMGR_I2C_ADDRESS + 1 );                         // HemGripper I2C Read Address
   value = i2c_read(0);
   i2c_stop();                                                 // I2C Stop Sequence
   delay_ms(1);
   return value;
}

/* Read if the Arm servo is disable */
unsigned char HemGripper_Read_Arm_Disable(void)
{
   unsigned char value = 0;
   i2c_start();                                                // I2C Start Sequence
   i2c_write(HEMGR_I2C_ADDRESS);                               // HemGR I2C Address
   i2c_write(Arm_DISABLE_ADD);                            // Arm Disable Register
   i2c_start();
   i2c_write(HEMGR_I2C_ADDRESS + 1 );                         // HemGripper I2C Read Address
   value = i2c_read(0);
   i2c_stop();                                                 // I2C Stop Sequence
   delay_ms(1);
   return value;
}

/* Read if the Gripper Servo is disable or not */
unsigned char HemGripper_Read_Gripper_Disable(void)
{
   unsigned char value = 0;
   i2c_start();                                                // I2C Start Sequence
   i2c_write(HEMGR_I2C_ADDRESS);                               // HemGR I2C Address
   i2c_write(GRIPPER_DISABLE_ADD);                             // Gripper Disable Register
   i2c_start();
   i2c_write(HEMGR_I2C_ADDRESS + 1 );                         // HemGripper I2C Read Address
   value = i2c_read(0);
   i2c_stop();                                                 // I2C Stop Sequence
   delay_ms(1);
   return value;
}

/* Read the Voltage of the battery */
unsigned int16 HemGripper_Read_Battery_Voltage(void)
{
   unsigned int16 value = 0;
   i2c_start();                                                // I2C Start Sequence
   i2c_write(HEMGR_I2C_ADDRESS);                               // HemGR I2C Address
   i2c_write(BATTERY_VOLTAGE_ADD);                             // Battery voltage Register
   i2c_start();
   i2c_write(HEMGR_I2C_ADDRESS + 1 );                         // HemGripper I2C Read Address
   value = (unsigned int16)i2c_read()& 0x00FF ;
   value = value | ((unsigned int16)i2c_read(0) << 8);
   i2c_stop();                                                 // I2C Stop Sequence
   delay_ms(1);
   return value;
}

/* Read the remaining capacity in % */
unsigned char HemGripper_Read_Battery_Capacity(void)
{
   unsigned char value = 0;
   i2c_start();                                                // I2C Start Sequence
   i2c_write(HEMGR_I2C_ADDRESS);                               // HemGR I2C Address
   i2c_write(BATTERY_CAPACITY_ADD);                            // Remaining battery Capacity register 
   i2c_start();
   i2c_write(HEMGR_I2C_ADDRESS + 1 );                         // HemGripper I2C Read Address
   value = i2c_read(0);
   i2c_stop();                                                 // I2C Stop Sequence
   delay_ms(1);
   return value;
}

/* Set the position of the Arm to reach without speed control */
void HemGripper_Set_Arm_Position( unsigned int16 value )
{
   i2c_start();                                                // I2C Start Sequence
   i2c_write(HEMGR_I2C_ADDRESS);                               // HemGripper I2C Address
   i2c_write(Arm_POSITION_ADD);                                // Arm Position register
   i2c_write((char)(value &0x00FF));
   i2c_write((char)((value >> 8) & 0x00FF));
   i2c_stop();                                                 // I2C Stop Sequence
   delay_ms(1);
}

/* Set the position of the Gripper to reach without speed control */
void HemGripper_Set_Gripper_Position( unsigned int16 value )
{
   i2c_start();                                                // I2C Start Sequence
   i2c_write(HEMGR_I2C_ADDRESS);                               // HemGripper I2C Address
   i2c_write(GRIPPER_POSITION_ADD);                            // Gripper Position register
   i2c_write((char)(value &0x00FF));
   i2c_write((char)((value >> 8) & 0x00FF));
   i2c_stop();                                                 // I2C Stop Sequence
   delay_ms(1);
}
/* Set the consigne of the Arm's Position to reach with a speed control */
void HemGripper_Set_Arm_Consign( unsigned int16 value )
{
   i2c_start();                                                // I2C Start Sequence
   i2c_write(HEMGR_I2C_ADDRESS);                               // HemGripper I2C Address
   i2c_write(Arm_CONSIGN_ADD);                                 // Arm Consign register
   i2c_write((char)(value &0x00FF));
   i2c_write((char)((value >> 8) & 0x00FF));
   i2c_stop();                                                 // I2C Stop Sequence
   delay_ms(1);
}

/* Set the consigne of the Gripper's Position to reach with a speed control */
void HemGripper_Set_Gripper_Consign( unsigned int16 value )
{
   i2c_start();                                                // I2C Start Sequence
   i2c_write(HEMGR_I2C_ADDRESS);                               // HemGripper I2C Address
   i2c_write(GRIPPER_CONSIGN_ADD);                             // Gripper Consign register
   i2c_write((char)(value &0x00FF));
   i2c_write((char)((value >> 8) & 0x00FF));
   i2c_stop();                                                 // I2C Stop Sequence
   delay_ms(1);
}
/* Set the Speed of the Arm when use the speed control move */
void HemGripper_Set_Arm_Speed( unsigned char value )
{
   i2c_start();                                                // I2C Start Sequence
   i2c_write(HEMGR_I2C_ADDRESS);                               // HemGripper I2C Address
   i2c_write(Arm_Speed_ADD);                                   // Arm Speed register
   i2c_write(value);
   i2c_stop();                                                 // I2C Stop Sequence
   delay_ms(1);
}

/* Set the Speed of the Gripper when use the speed control move */
void HemGripper_Set_Gripper_Speed( unsigned char value )
{
   i2c_start();                                                // I2C Start Sequence
   i2c_write(HEMGR_I2C_ADDRESS);                               // HemGripper I2C Address
   i2c_write(GRIPPER_Speed_ADD);                               // Arm Speed register
   i2c_write(value);
   i2c_stop();                                                 // I2C Stop Sequence
   delay_ms(1);
}

/* Define if the servo must be disable after a complete move */
void HemGripper_Arm_Disable( unsigned char value )
{
   i2c_start();                                                // I2C Start Sequence
   i2c_write(HEMGR_I2C_ADDRESS);                               // HemGripper I2C Address
   i2c_write(Arm_DISABLE_ADD);                                 // Arm Disable register
   i2c_write(value);
   i2c_stop();                                                 // I2C Stop Sequence
   delay_ms(1);
}
/* Define if the servo must be disable after a complete move */
void HemGripper_Gripper_Disable( unsigned char value )
{
   i2c_start();                                                // I2C Start Sequence
   i2c_write(HEMGR_I2C_ADDRESS);                               // HemGripper I2C Address
   i2c_write(GRIPPER_DISABLE_ADD);                             // Gripper Disable register
   i2c_write(value);
   i2c_stop();                                                 // I2C Stop Sequence
   delay_ms(1);
}
