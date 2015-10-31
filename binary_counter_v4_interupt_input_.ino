//Variables
int ledPins [] = {9,8,7,6,5,4};
//There used to be two buttons in the original
//design but for testing sake there will be only one
int buttonPins [] = {2,3};
int leftButtonState = 1;
int rightButtonState = 1;
int lastPressState;
volatile int total_1 = 0;
volatile int total_2 = 0;
int listSwitch = 1;
int lastSwitch;
// These variables are used for checking and storing times
int initialTime;
int lastTime;
int timeNow;
int difference;
//The amount of time the right button needs to be held to reset the count
int holdTime = 2500;
int quickPress = 200;

//Testing code declarition
void switchSequence(int listSet, int blinkDelay = 100) {
  if (listSet == 1) {
    binaryLight(7);
    delay(blinkDelay);
    binaryLight(0);
    delay(blinkDelay);
    }
  else {
    binaryLight(56);
    delay(blinkDelay);
    binaryLight(0);
    delay(blinkDelay);
    }
  }
//End function test

void setup() {
  Serial.begin(9600);
//Sets up all of the output pins fo LED's and default to LOW
  for (int i = 0; i < 7; i++) {
    pinMode(ledPins[i], OUTPUT);
    digitalWrite(ledPins[i], LOW);
  }

//Sets the input pin for buttons
   pinMode(buttonPins[0], INPUT_PULLUP);
   pinMode(buttonPins[1], INPUT_PULLUP);

   attachInterrupt(digitalPinToInterrupt(buttonPins[0]), countUp, FALLING);

}

void loop() {
//  testSequence(300, 64);
//  testSwitch(1);

//Begin button logic
/*
 * First we need to catch the button values in variables
 * then we will set statements to check these variables to
 * now whether or not to count up or down
 */
   //Variable is currently HIGH and then gets set to LOW
   //when button is pressed
   leftButtonState = digitalRead(buttonPins[0]);
   rightButtonState = digitalRead(buttonPins[1]);

   //This checks if the left button is pressed as well as the right
   //button not being pressed to increase the total count
   if (leftButtonState == 0 && rightButtonState == 1) {
     //Button has gone low and no count is incremented up by one
     if (listSwitch == 1) {
       total_1++;
     //Reset count to zero if it gets to 64
      if (total_1 == 64) {
        total_1 = 0;
      }
      binaryLight(total_1);
     }
      else if (listSwitch == 2) {
       total_2++;
     //Reset count to zero if it gets to 64
      if (total_2 == 64) {
        total_2 = 0;
      }
      binaryLight(total_2);
     }
     //Write current count variable to the LED's

     while (leftButtonState == 0) {
      leftButtonState = digitalRead(buttonPins[0]);
      }
      leftButtonState = 1;
   }
   delay(50);

/*
 * >>>>>>TESTING NEW CODE FOR RIGHT BUTTON DECREAMENT NESTED IN COUNT RESET STATEMENT
 */
      // This code will start when the right button is pressed which will then allow
      // for either total count decrement or total count reset to zero. The logic is set to
      // reset the count so long as the right button has been pressed and the left button has
      // not been pressed during this time. If the left button is pressed while the right
      // is pressed then the reset function will not run and the total count function will run.
      // One then must release the right button and then once more press and hold the right
      // to engage the reset function for the duration of the set hold time without pressing
      // the left button.

      if (rightButtonState == 0) {

      lastTime = initialTime;
      // Here we store the initial time to for reference to see how long the
      // button has been held down for
      initialTime = millis();
      rightButtonState = digitalRead(buttonPins[1]);

      /*
       * *****TESTING CODE SNIPPET HERE
       */

       // Capture time to see how long the right button has been depressed
      timeNow = millis();

      // Store the difference in time between the right button was initial held down
      // and the how long it has been since being held down
      difference = timeNow - lastTime;

      // Now this will check to see how long the button is being held down by checking
      // it agianst the initial time that was stored the when the button was initially pressed.
      // If the difference in time is 3 seconds then the if statment will run
      if (difference == holdTime && lastPressState == 1) {

          // This will set the total count back to zero
          if (listSwitch == 1) {
            total_1 = 0;
            binaryLight(total_1);
            }
          else if (listSwitch == 2) {
            total_2 = 0;
            binaryLight(total_2);
           }
          }

       /*
        * ****END CODE SNIPPET
        */


      // This will engage the switch mode to change lists
      if (initialTime - lastTime <= quickPress && rightButtonState == 1) {

        rightButtonState = digitalRead(buttonPins[1]);
        leftButtonState = digitalRead(buttonPins[0]);

        // Loop to catch the switch mode
        while (rightButtonState == 1) {
          leftButtonState = digitalRead(buttonPins[0]);
          rightButtonState = digitalRead(buttonPins[1]);
          // Write code to change the switch variable
          if (listSwitch == 1 && leftButtonState == 0) {
            listSwitch = 2;
          }
          else if (listSwitch == 2 && leftButtonState == 0) {
            listSwitch = 1;
            }

          switchSequence(listSwitch);
          }
          if (listSwitch == 1) {
            binaryLight(total_1);
            }
          else if (listSwitch == 2) {
            binaryLight(total_2);
            }
        }

      //Checking the state of the left and right buttons
      rightButtonState = digitalRead(buttonPins[1]);
      leftButtonState = digitalRead(buttonPins[0]);

      // Storing the state of the left button to be used later
      lastPressState = leftButtonState;

      //This loop will run if the right button is still held down
      while (rightButtonState == 0) {

          // Check the state of both buttons again
          leftButtonState = digitalRead(buttonPins[0]);
          rightButtonState = digitalRead(buttonPins[1]);

          // When the left button is pressed then decrease count
          if (leftButtonState == 0) {
             // Button has gone low and now count is reduced by one
            if (listSwitch == 1) {
               total_1--;

               // Reset count to zero if total is equal to zero
               if (total_1 <= 0) {
                 total_1 = 0;
               }
               binaryLight(total_1);
             }
             else if (listSwitch == 2) {
                total_2--;

               // Reset count to zero if total is equal to zero
               if (total_2 <= 0) {
                 total_2 = 0;
               }
               binaryLight(total_2);
             }
             // Display current total to the LED's


             // If the button is still pressed then catch and hold program until the
             // left buttonis released to prevent run away decrement of total count
             while (leftButtonState == 0) {

               // Cheking left button state to see when it is disengeged
               leftButtonState = digitalRead(buttonPins[0]);
             }

             // Set the storing the state of the left button as being pressed
             lastPressState = 0;

             // Delay to keep from debouncing issue when pressing left button
             delay(50);
          }

//          // Capture time to see how long the right button has been depressed
//          timeNow = millis();
//
//          // Store the difference in time between the right button was initial held down
//          // and the how long it has been since being held down
//          difference = timeNow - initialTime;
//
//          // Now this will check to see how long the button is being held down by checking
//          // it agianst the initial time that was stored the when the button was initially pressed.
//          // If the difference in time is 3 seconds then the if statment will run
//          if (difference == holdTime && lastPressState == 1) {
//
//              // This will set the total count back to zero
//              if (listSwitch == 1) {
//                total_1 = 0;
//                binaryLight(total_1);
//                }
//              else if (listSwitch == 2) {
//                total_2 = 0;
//                binaryLight(total_2);
//               }
//              }

              // Now we run the binaryLight function to display the new total


              // This will now set the right button variable to a "not pressed" state to
              // break out of the while loop
              rightButtonState = 1;
          }

          // Check to make sure the right button is still in fact still held down
//          rightButtonState = digitalRead(buttonPins[1]);
        }

/*
 * Counter switch between two totals. Lights will be indicate which total
 * is currently choosen. The chat count will be reflected by flashing the left 3
 * sets of LED's and the emails count will be the right 3 LED's. To engage the count select
 * menu one must press the right button twice in quick succession. Then the left button
 * will be used to slecet between the two counts. After selection has been choosen one
 * can then press the right button once to exit the selection menu.
 */

}

void countUp() {
  total_1 ++;
}
