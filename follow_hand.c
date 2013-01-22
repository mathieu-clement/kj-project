/*******************************************************************************
 * @file
 * 
 * @brief The Follow Hand program
 * See the follow_hand.h file for more informations...
 *
 *******************************************************************************/
 
 
 /**
 * this function checks the two ground front captors and return true (1) is the floor is missing,
 * false (0) otherwise.
 **/
 
int1 fh_ground_is_missing()
{
   RETURN (KJunior_get_proximity (GROUNDFRONTLEFT) < fh_ground_missing_limit ||
       KJunior_get_proximity (GROUNDFRONTLEFT) < fh_ground_missing_limit );
}


/******************** main method *********************************************/
void follow_hand()
{
   //moves forward
   if( KJunior_get_proximity (FRONT) > fh_low_prox ) 
   {
      //moves forward as LONG as the hand is in sight but not too close
      while( KJunior_get_proximity (FRONT) > fh_low_prox &&
             KJunior_get_proximity (FRONT) < fh_high_prox )
      {
         KJunior_set_speed (fh_speed, fh_speed);

         //IF the ground is missing, moves hurrieldy backward and stops.
         if( fh_ground_is_missing () )
         {
            KJunior_set_speed ( - 20, - 20);
            sleep_ms (400);
            break;
         }
      }
      KJunior_set_speed (0, 0);
      
   }
   //moves backwards
   else if( KJunior_get_proximity (REAR) > fh_low_prox ) 
   {
      while( KJunior_get_proximity (REAR) > fh_low_prox && 
             KJunior_get_proximity (REAR) < fh_high_prox )
      {
         KJunior_set_speed (-fh_speed, -fh_speed);
      }

      KJunior_set_speed (0, 0);
      
   }
   //rotates left
   else if( KJunior_get_proximity (LEFT) > fh_low_prox_side ) 
   {
      //while a hand is in sight of one of the front left or left captor (but not too close), rotates left
      while(( KJunior_get_proximity (LEFT) > fh_low_prox_side &&
              KJunior_get_proximity (LEFT) < fh_high_prox_side )||
            ( KJunior_get_proximity (FRONTLEFT) > fh_low_prox_side && 
              KJunior_get_proximity (FRONTLEFT) < fh_high_prox_side ) )
      {
         KJunior_set_speed ( - fh_speed, fh_speed);
      }

   }
   //rotates right
   else if( KJunior_get_proximity (RIGHT) > fh_low_prox_side ) 
   {
      //while a hand is in sight of one of the front right or right captor (but not too close), rotates right
      while(( KJunior_get_proximity (RIGHT) > fh_low_prox_side &&
              KJunior_get_proximity (RIGHT) < fh_high_prox_side )||
            ( KJunior_get_proximity (FRONTRIGHT) > fh_low_prox_side &&
              KJunior_get_proximity (FRONTRIGHT) < fh_high_prox_side) )
      {
         KJunior_set_speed (fh_speed, - fh_speed);
      }
   }
   //else, be sure that the robot stops
   else 
   {
      KJunior_set_speed (0, 0);
   }
   
}//end follow_hand

