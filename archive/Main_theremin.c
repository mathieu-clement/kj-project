#include "KJunior.h"

#include "Basic_functions.h"


//--------------------------------------------------------------------------------//
//- Main program                                                                 -//
//--------------------------------------------------------------------------------//
#separate

// This very practical function converts a value (which is within a defined range)
// to an output value (within another defined range).
// So for instance if input is a temperature between 0 and 20°, and say it's 10° now,
// and we want to output a note from 0 to 48 depending on the temprature, then that note 
// would be around 24, because 24 is half of the range [0; 48].
char proximityToBeepValue(int16 proxVal, int16 proxMin, int16 proxMax, char beepMin, char beepMax)
{
   // (destMax - destMin) * ( (sourceValue - sourceMin) / (sourceMax - sourceMin) )
   // For our example:
   // (48 - 0) * ( (10 - 0) / (20 - 0) ) = 24
   
   char returnedValue = (beepMax - beepMin) * ( (float) (proxVal - proxMin) / (proxMax - proxMin) );
   
   // For values out of the range, return -1. ==> OK, this assumes we don't have ranges with negative numbers
   // otherwise we have to find another way to output illegal values.
   if(returnedValue < beepMin || returnedValue > beepMax)
   {
      return -1;
   }
}

void main(void)
{
 // Initialization
 KJunior_init();
 
 // CALIBRATION
 // During the first 5 seconds after the robot is switched on
 // there is a calibration phase.
 // To make it work, wave your hand back and forth in front of the center proximity sensor.
 // During this phase, the front right led is on.
 
 int16 sensorMinDistance = 4095;
 int16 sensorMaxDistance = 0;
 
 KJunior_led_frontright(1);
 
 while(KJunior_get_time() < 5000)
 {
   int16 sensorVal = KJunior_get_proximity(FRONT);
   
   if(sensorVal > sensorMaxDistance)
   {
      sensorMaxDistance = sensorVal;
   }
   
   if(sensorVal <sensorMinDistance)
   {
      sensorMinDistance = sensorVal;
   }
 } // end while
 
 // BEGIN DEBUG
 fprintf(USB, "Min value: %ld, Max value: %ld\r\n", sensorMinDistance, sensorMaxDistance);
 sleep_ms(3000);
 // END DEBUG
 
 KJunior_led_frontright(0);

While (1)
{
   if((SerialCommandOK == 1) && (Enable_RS232_Control == 1))
     SerialCommandHandler();
     
   // Read value from front right proximity sensor
   int16 proximity = KJunior_get_proximity(FRONT);
   fprintf(USB, "Proximity: %ld ", proximity);
   
   // Convert that value to the note to play
   char beepValue = proximityToBeepValue(proximity, sensorMinDistance, sensorMaxDistance, 0, 48);
   fprintf(USB, "Beep value: %d\r\n", beepValue);
   
   // Mute buzzer if value is higher or lower than the lower and upper limits set during the calibration phase
   if(beepValue != -1)
   {
      KJunior_beep(beepValue);
   } else {
      KJunior_beep(0);
   }
   
   // Sleep for a moment
   sleep_ms(10);
   
   // fprintf(USB, "%d\r\n", proximity);
   
} // end while

} // end main
       

