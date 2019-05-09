# BlinkyBuzzer

## About

An Arduino library for managing a blinking led associated with a buzzer/beeper in a **non-blocking** fashion.

Available at: https://github.com/mauntrelio/BlinkyBuzzer

### Features

- Non-blocking. Do not use `delay()` in your code for consistent behavior 
- Performs blink only, beep only, or blinking and beeping synced (referred as _buzzing_ in the helper methods and in the following explanations)
- Supports a single beep, blink or buzz as well as a given number of beeps, blinks, buzzes or endless beeping, blinking or buzzing
- Supports runtime configuration of On Time, Off Time, beep tone frequency and number of repetitions
- Supports stopping/starting beeping, blinking, buzzing at runtime (you can keep it blinking, while stopping the beeping, and vice versa)

### Using the library

```c++

#include <BlinkyBuzzer.h>

#define PIN_LED 13
#define PIN_BUZZ 4

BlinkyBuzzer buzzer = BlinkyBuzzer(PIN_LED, PIN_BUZZ);

void setup() {
	buzzer.setOnTime(200);
	buzzer.setOffTime(500);
	buzzer.start();
}

void loop() {
	buzzer.update();
}

```

### Constructor / Destructor

***BlinkyBuzzer(byte _pinLed, byte _pinBeep, unsigned int frequency=1000, unsigned int onTime=500, unsigned int offTime=500);**

Creates a BlinkyBuzzer object:
- pin that controls the led
- pin that controls the buzzer
- frequency of the buzzer (default 1000 Hz)
- on time when blinking/beeping (default 500 ms)
- off time when blinking/beeping (default 500 ms)

***~BlinkyBuzzer()***<br>
Destructor for BlinkyBuzzer object.

### Methods

### Inspection

**bool isBlinking()**<br>
Returns true if the BlinkyBuzzer object is blinking.

**bool isBeeping()**<br>
Returns true if the BlinkyBuzzer object is beeping.

**bool isBuzzing()**<br>
Returns true if the BlinkyBuzzer object is beeping AND blinking.

**bool isRunning()**<br>
Returns true if the BlinkyBuzzer object is either beeping OR blinking (or both).

**unsigned int getRepetitions()**<br>
Gets the number of repetitions left.

A negative number of repetitions means "for ever".

### Blink only operations
**void blinkOnce()**<br>
Make one single flash of the LED.

If the BlinkyBuzzer is also already beeping, it will make the first and unique blink synced to the next beep, and then it will stop all together, since the repetitions are shared among beeps and blinks.

**void blinkOnce(unsigned int onTime)**<br>
Make one single flash of the LED of the specified duration.

**void blink()**<br>
Start blinking the LED, forever. 

If the BlinkyBuzzer is already beeping, it will start to blink as well, with blinks synced to the beeps. Otherwise it will start blinking immediately.

**void blink(int times)**<br>
Start blinking the LED a specified number of times.

Repetitions are shared with the beeps, so if the BlinkyBuzzer is also already beeping, it will start to blink as well, with blinks synced to the beeps, and will stop all together after the given number of repetitions.

**void blink(int times, unsigned int onOffTime)**
Start blinking the LED a specified number of times, with the specified ON and OFF intervals. The same consideration for the previous methods about the repetitions apply here to the intervals as well: setting them will have effect on any already ongoing effect. 

**void startBlinking()**<br>
An alias for `blink()`

**void startBlinking(unsigned int onOffTime)**<br>
Start blinking the LED endless, with the specified ON and OFF intervals.

**void stopBlinking()**<br>
Stop the blinking immediately, independently of the number of repetitions (and  switch off the LED). If the BlinkyBuzzer is also beeping, it will continue beeping only (for the left number of repetitions, or forever)

### Beep only operations

The following methods are identical to the ones described in the previous paragraph, except they work on the beeps instead of the blinks.

**void beepOnce()**<br>
**void beepOnce(unsigned int onTime)**<br>
**void beep()**<br>
**void beep(int times)**<br>
**void beep(int times, unsigned int onOffTime)**<br>
**void startBeeping()**<br>
**void startBeeping(unsigned int onOffTime)**<br>
**void stopBeeping()**<br>

### Blink and beep operations

The following methods are identical to the ones described in the previous paragraphs, except they work on both beeps and blinks.

**void buzzOnce()**<br>
**void buzzOnce(unsigned int onTime)**<br>
**void buzz()**<br>
**void buzz(int times)**<br>
**void buzz(int times, unsigned int onOffTime)**<br>
**void startBuzzing()**<br>
**void startBuzzing(unsigned int onOffTime)**<br>
**void stopBuzzing()**<br>

**void start()**<br>
An alias for `startBuzzing()`

**void stop()**<br>
An alias for `stopBuzzing()`

### Runtime configurations

**void setOnTime(unsigned int duration)**<br>
Set the interval (in ms), the led and the tone should stay on.

**void setOffTime(unsigned int duration)**<br>
Set the interval (in ms), the led and the tone should stay off.

**void setOnOffTime(unsigned int duration)**<br>
Set the interval (in ms), the led and the tone should stay on and off (they get set the same given value).

**void setFrequency(unsigned int tone)**<br>
Set the frequency (in Herz), for the beep. If the BlinkyBuzzer object is already beeping when you call this, the change will be applied at the immediately next beep.

**void setRepetitions(int times)**<br>
Set the number of repetitions at runtime. Only works if the BlinkyBuzzer object is running. A negative number of repetitions means endless repetition.

### Perform the actual business

**void update()**<br>
This is the method to be called to perform the actual beeping/blinking/buzzing. It should be called in the `loop()` function.
