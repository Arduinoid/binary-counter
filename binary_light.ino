/*
 * This is a function that will take an integer inout and then
 * convert it to a binary number. This number then gets parsed out
 * to it's 1's and 0's to then reprisent the HIGH and LOW states 
 * for the pins. The output will be digitalWrite to the LED pins
 * which then sets each one to HIGH or LOW
 */
void binaryLight(int x) {
  //Convert the integer passed in to the binary equvilant
  byte binaryNumber = byte(x);
  //This loop will run through the sequence of LED's and
  //turn them all of to reset LED's state to LOW
  for (int i = 0; i < 7; i++) {
    //Write each LED to LOW
    digitalWrite(ledPins[i], LOW);
  }
  //Write each LED to the corosponding binary 1 or 0
  for (int i = 0; i < 7; i++) {
    //digitalWrite pin to HIGH if the bit is equal to 1
    if (bitRead(x, i) == 1) {
      digitalWrite(ledPins[i], HIGH);
    }
    else {
      //digitalWrite pin to LOW if the bit is equal to 0
      digitalWrite(ledPins[i], LOW);
    }
  }
}
