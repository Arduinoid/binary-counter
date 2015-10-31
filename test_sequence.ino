/*
 * This is a test routine to run through the LED's in sequence.
 * This function will take two input values. The first is the delay
 * time between counts and the second is the max number the LED's
 * will count to. 
 * 
 * **********NOTE************ 
 * The max number the current configuration
 * of 6 LED's can display is 64 values including zero
 */
void testSequence(int delayTime, int count) {
  for (int i = 0; i <= count; i++) {
    //Call binaryLight function and pass in the loop iteration
    binaryLight(i + 1);
    delay(delayTime);
  }
}
