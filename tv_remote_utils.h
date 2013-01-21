/**
 * @file
 * 
 * @brief Utilities to read keys pressed from the TV remote control
 */

#ifndef TV_REMOTE_UTILS_H
#define TV_REMOTE_UTILS_H

// Constants for buttons of the TV remote control
#define TV_POWER        38
#define TV_MUTE         36
#define TV_CH_PLUS      30
#define TV_CH_MINUS     28
#define TV_VOL_PLUS     18
#define TV_VOL_MINUS    20
#define TV_TV_AV        34
#define TV_I_II         56
#define TV_3            56
#define TV_ARROW        56
// TV_0 ---> TV_11 : Please use to_pad_number if needed
#define TV_CH_PC        32

/**
 * Convert the raw button id from TV remote to the button number.
 *
 * @param raw_input Raw input from TV remote.
 * @return the corresponding button number matching the TV remote raw input.
 */
int8 to_pad_number(unsigned char raw_input);

/**
 * Returns the last number pressed on the TV remote number pad.
 *
 * @return the last number pressed on the TV remote number pad.
 */
int8 get_tv_remote_pad_number(void);

#include "tv_remote_utils.c"

#endif