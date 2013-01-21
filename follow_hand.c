/**
 * This method makes the robot follow a hand or an object. IF the object is detected
 * by the front captor, the robot will move forward until the object either disappear or come too close.
 * IF the robot detects that the floor is missing, it will hurriedly move backward and stop.
 * IF the object is detected to the left or to the right of the robot, the latter will rotate
 * in its direction.
 * The robot will finally go backward and follow the hand IF it is detected by the robot's
 * rear captor.
 *
 * Note : there is plenty of room FOR improvement. For example, the robot is not really fast 
 * nor smooth, and sometimes the hand is not correctly detected. 
 * When an object is detected by the front and sides captors, the robot should normally
 * either move forward or stop. but it will aslo sometimes rotate left to right repeatedly.
 * 
 * @version : 1
 * @author : Lucy Linder
 * @date : 02.12.2012
 *
 **/
void follow_hand(VOID)
{
   //moves forward
   IF (KJunior_get_proximity (FRONT) > low_prox) 
   {
      //moves forward as LONG as the hand is in sight but not too close
      WHILE (KJunior_get_proximity (FRONT) > low_prox&&KJunior_get_proximity (FRONT) < high_prox)
      {
         KJunior_set_speed (speed, speed);

         //IF the ground is missing, moves hurrieldy backward and stops.
         IF (ground_is_missing () )
         {
            KJunior_set_speed ( - 20, - 20);
            sleep_ms (400);
            BREAK;
         }
      }
      KJunior_set_speed (0, 0);
   }

   //moves backwards
   else IF (KJunior_get_proximity (REAR) > low_prox) 
   {
      WHILE (KJunior_get_proximity (REAR) > low_prox&&KJunior_get_proximity (REAR) < high_prox)
      {
         KJunior_set_speed (-speed, - speed);
      }

      KJunior_set_speed (0, 0);
   }

   //rotates left
   else IF (KJunior_get_proximity (LEFT) > low_prox_side) 
   {
      //WHILE a hand is in sight of one of the front left or left captor (but not too close), rotates left
      WHILE ((KJunior_get_proximity (LEFT) > low_prox_side&&KJunior_get_proximity (LEFT) < high_prox_side)||
      (KJunior_get_proximity (FRONTLEFT) > low_prox_side&&KJunior_get_proximity (FRONTLEFT) < high_prox_side) )
      {
         KJunior_set_speed ( - speed, speed);
      }

   }

   //rotates right
   else IF (KJunior_get_proximity (RIGHT) > low_prox_side) 
   {
      //WHILE a hand is in sight of one of the front right or right captor (but not too close), rotates right
      WHILE ((KJunior_get_proximity (RIGHT) > low_prox_side&&KJunior_get_proximity (RIGHT) < high_prox_side)||
      (KJunior_get_proximity (FRONTRIGHT) > low_prox_side&&KJunior_get_proximity (FRONTRIGHT) < high_prox_side) )
      {
         KJunior_set_speed (speed, - speed);
      }
   }

   //else, be sure that the robot stops
   ELSE 
   {
      KJunior_set_speed (0, 0);
   }
}//end follow_hand



/**
 * this function checks the two ground front captors and return true (1) is the floor is missing,
 * false (0) otherwise.
 **/
int1 ground_is_missing()
{
   INT16 lim = 2800;

   IF (KJunior_get_proximity (GROUNDFRONTLEFT) < lim||KJunior_get_proximity (GROUNDFRONTLEFT) < lim)
   {
      RETURN 1;
   }

   RETURN 0;
}

