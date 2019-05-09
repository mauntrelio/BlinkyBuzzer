/*

In this example we start a buzzer and then we perform several 
effects at different points in time.

*/
#include <BlinkyBuzzer.h>

#define PIN_LED 13
#define PIN_BUZZ 4

BlinkyBuzzer buzzer = BlinkyBuzzer(PIN_LED, PIN_BUZZ);

unsigned long currentTime = 0;

void setup() {
	buzzer.start();
}

void loop() {
	buzzer.update();
	currentTime = millis();

	if (currentTime == 5000) {
		buzzer.stopBeeping();
	}
	if (currentTime == 10000) {
    buzzer.setFrequency(2500);
		buzzer.startBeeping();
	}
  if (currentTime == 15000) {
		buzzer.stopBuzzing();
	}
  if (currentTime == 20000) {
    buzzer.startBlinking(200);
	}
  if (currentTime == 25000) {
    buzzer.setFrequency(500);
    buzzer.setOffTime(100);
    buzzer.startBeeping();
  }
  if (currentTime == 30000) {
    buzzer.stop();
    buzzer.setOffTime(1000);
    buzzer.setOnTime(200);
    buzzer.startBlinking();
	}

}