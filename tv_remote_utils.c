/**
 * @file
 * 
 * @brief Utilities to read keys pressed from the TV remote control
 */

/**
 * Convert the raw button id from TV remote to the button number.
 *
 * @param raw_input Raw input from TV remote.
 * @returns the corresponding button number matching the TV remote raw input.
 */
int8 to_pad_number(unsigned char raw_input)
{
   switch((int8) raw_input)
   {
      case 62:
         return 0;
      case 60:
         return 1;
      case 58:
         return 2;
      case 56:
         return 3;
      case 54:
         return 4;
      case 52:
         return 5;
      case 50:
         return 6;
      case 48:
         return 7;
      case 46:
         return 8;
      case 44:
         return 9;
      case 42:
         return 11;
      default:
         return -1;
   }
}

/**
 * Returns the last number pressed on the TV remote number pad.
 *
 * @return the last number pressed on the TV remote number pad.
 */
int8 get_tv_remote_pad_number(void) {
   return to_pad_number(KJunior_get_tv_data());
}
