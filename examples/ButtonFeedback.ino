/*

In this example we show how to give a buzzer "feedback" when pressing a button.
Button non-blocking debouncing is based on the example at https://www.arduino.cc/en/tutorial/debounce

If you need to perform more complex operations and/or manage many buttons 
you may consider using a library, like, for instance, Switch (https://github.com/avandalen/avdweb_Switch/) 

*/
#include <BlinkyBuzzer.h>

#define PIN_LED 13
#define PIN_BUZZ 4
#define PIN_BUTTON 5

BlinkyBuzzer buzzer = BlinkyBuzzer(PIN_LED, PIN_BUZZ);

unsigned long currentTime = 0;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;
int lastButtonState = HIGH;
int buttonState;

void setup() {
  pinMode(PIN_BUTTON, INPUT_PULLUP);
}

void loop() {
	buzzer.update();
	currentTime = millis();

  int reading = digitalRead(PIN_BUTTON);
  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((currentTime - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != buttonState) {
      buttonState = reading;
      // only beep the buzzer if the new button state is LOW
      if (buttonState == LOW) {
        buzzer.buzzOnce(100);
      }
    }
  }

  // save the reading. Next time through the loop, it'll be the lastButtonState:
  lastButtonState = reading;

}
