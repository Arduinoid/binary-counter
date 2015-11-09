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
  binaryLight(total_1);
}

void countUp() {
  static unsigned long last_interrupt_time = 0;
  unsigned long interrupt_time = millis();

  if (interrupt_time - last_interrupt_time > 150) {
    if (digitalRead(buttonPins[1]) == LOW) {
      total_1 --;
    }
    else {
      total_1 ++;
    }
  }
  last_interrupt_time = interrupt_time;
}
