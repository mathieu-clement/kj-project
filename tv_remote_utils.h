/**
 * Convert the raw button id from TV remote to the button number.
 *
 * @param raw_input Raw input from TV remote.
 * @returns the corresponding button number matching the TV remote raw input.
 */
int8 to_pad_number(unsigned char raw_input);
/**
 * Returns the last number pressed on the TV remote number pad.
 *
 * @return the last number pressed on the TV remote number pad.
 */
int8 get_tv_remote_pad_number();

#include "tv_remote_utils.c"

