
//void switchSequence(int listSet, int blinkDelay = 100) {
//  if (listSet == 1) {
//    binaryLight(7);
//    delay(blinkDelay);
//    binaryLight(0);
//    delay(blinkDelay);
//    }
//  else {
//    binaryLight(56);
//    delay(blinkDelay);
//    binaryLight(0);
//    delay(blinkDelay);
//    }
//  }

void testSwitch(int switchList) {
  while (true) {
    switchSequence(switchList);
    }
  }
