#include "Arduino.h"

#include "BlinkyBuzzer.h"

BlinkyBuzzer::BlinkyBuzzer(byte _pinLed, byte _pinBeep, unsigned int frequency, unsigned int onTime, unsigned int offTime):
pinLed(_pinLed), pinBeep(_pinBeep), frequency(frequency), onTime(onTime), offTime(offTime)
{
   pinMode(pinLed, OUTPUT);
   pinMode(pinBeep, OUTPUT);
   stop();
}

BlinkyBuzzer::~BlinkyBuzzer() {}

/*********************/
/* INSPECTION        */
/*********************/

// return if is blinking or not
bool BlinkyBuzzer::isBlinking()
{
  return blinking;
}

// return if is beeping or not
bool BlinkyBuzzer::isBeeping()
{
  return beeping;
}

// return if is buzzing or not
bool BlinkyBuzzer::isBuzzing()
{
  return (blinking && beeping);
}

// return if is doing something
bool BlinkyBuzzer::isRunning()
{
  return (blinking || beeping);
}

// get the number of repetitions left
unsigned int BlinkyBuzzer::getRepetitions()
{
  return repetitions;
}


/********************/
/* BLINK OPERATIONS */
/********************/

// blink a certain number of times
void BlinkyBuzzer::blink(int times)
{
  blinking = true;
  setRepetitions(times);
}

// blink a certain number of times at specified rythm
void BlinkyBuzzer::blink(int times, unsigned int onOffTime)
{
  setOnOffTime(onOffTime);
  blink(times);
}

// blink one time
void BlinkyBuzzer::blinkOnce()
{
  blink(1);
}

// blink one time for specified duration
void BlinkyBuzzer::blinkOnce(unsigned int onTime)
{
  setOnTime(onTime);
  blink(1);
}

// blink forever
void BlinkyBuzzer::blink()
{
  blink(-1);
}

// if it is already beeping, will add the blink
// otherwise will start
void BlinkyBuzzer::startBlinking()
{
  if (isBeeping()) {
    blinking = true;
  } else {
    blink();
  }
}

// if it is already beeping, will add the blink
// otherwise will start
// always setting the specified rythm
void BlinkyBuzzer::startBlinking(unsigned int onOffTime)
{
  setOnOffTime(onOffTime);
  startBlinking();
}

// stop blinking immediately
// will continue beeping if is buzzing
void BlinkyBuzzer::stopBlinking()
{
  blinking = false;
  digitalWrite(pinLed, LOW);
  ledStatus = LOW;
}

/********************/
/* BEEP OPERATIONS */
/********************/

// beep a certain number of times
void BlinkyBuzzer::beep(int times)
{
  beeping = true;
  setRepetitions(times);
}

// beep a certain number of times at specified rythm
void BlinkyBuzzer::beep(int times, unsigned int onOffTime)
{
  setOnOffTime(onOffTime);
  beep(times);
}

// beep one time
void BlinkyBuzzer::beepOnce()
{
  beep(1);
}

// beep one time for specified duration
void BlinkyBuzzer::beepOnce(unsigned int onTime)
{
  setOnTime(onTime);
  beep(1);
}

// beep forever
void BlinkyBuzzer::beep()
{
  beep(-1);
}

// start beeping
// if it is already blinking, will add the beep
// otherwise will start
void BlinkyBuzzer::startBeeping()
{
  if (isBlinking()) {
    beeping = true;
  } else {
    beep();
  }
}

// start beeping
// if it is already blinking, will add the beep
// otherwise will start at specified rythm
void BlinkyBuzzer::startBeeping(unsigned int onOffTime)
{
  setOnOffTime(onOffTime);
  startBeeping();
}

// stop beeping immediately
// will continue blinking if it's buzzing
void BlinkyBuzzer::stopBeeping()
{
  beeping = false;
  noTone(pinBeep);
  beepStatus = LOW;
}


/********************/
/* BUZZ OPERATIONS  */
/********************/

// buzz a certain number of times
void BlinkyBuzzer::buzz(int times)
{
  beeping = true;
  blinking = true;
  setRepetitions(times);
}

// buzz a certain number of times at specified ryhtm
void BlinkyBuzzer::buzz(int times, unsigned int onOffTime)
{
  setOnOffTime(onOffTime);
  buzz(times);
}

// buzz one time
void BlinkyBuzzer::buzzOnce()
{
  buzz(1);
}

// buzz one time for specified duration
void BlinkyBuzzer::buzzOnce(unsigned int onTime)
{
  setOnTime(onTime);
  buzz(1);
}

// buzz forever
void BlinkyBuzzer::buzz()
{
  buzz(-1);
}

// alias for buzz forever
void BlinkyBuzzer::startBuzzing()
{
  buzz(-1);
}

// stat buzzing at specified rythm
void BlinkyBuzzer::startBuzzing(unsigned int onOffTime)
{
  setOnOffTime(onOffTime);
  buzz(-1);
}

// stop buzzing immediately
void BlinkyBuzzer::stop()
{
  stopBlinking();
  stopBeeping();
  lastChange = 0;
}

// alias for stop
void BlinkyBuzzer::stopBuzzing()
{
  stop();
}

// alias for startBuzzing
void BlinkyBuzzer::start()
{
  startBuzzing();
}


/***************************/
/* SETTER METHODS          */
/***************************/

// set time BUZZ should stay on
void BlinkyBuzzer::setOnTime(unsigned int duration)
{
  onTime = duration;
}

// set time BUZZ should stay off
void BlinkyBuzzer::setOffTime(unsigned int duration)
{
  offTime = duration;
}

// set time BUZZ should stay on and off
void BlinkyBuzzer::setOnOffTime(unsigned int duration)
{
  onTime = duration;
  offTime = duration;
}

// set beep frequency
void BlinkyBuzzer::setFrequency(unsigned int tone)
{
  frequency = tone;
}

// set the number of repetitions
void BlinkyBuzzer::setRepetitions(int times)
{
  repetitions = times;
}


/********************/
/* LOOP OPERATIONS  */
/********************/

// do the actual JOB: to be called in the loop
void BlinkyBuzzer::update() {

  // return immediately if not running
  if (!(blinking || beeping)) {
    return;
  }

  // get current time
  currentTime = millis();

  // low / high status
  buzzStatus = (ledStatus || beepStatus);

  // still repetitions left to run or infinite
  if (repetitions != 0) {

    // time to switch off
    if ((currentTime - lastChange) >= onTime && buzzStatus == HIGH) {
      // beep off if we are beeping
      if (beeping) {
        noTone(pinBeep);
        beepStatus = LOW;
      }
      // led off if we are blinking
      if (blinking) {
        digitalWrite(pinLed, LOW);
        ledStatus = LOW;
      }
      // update last status change
      lastChange = currentTime;
      // decrement repetitions
      if (repetitions > 0) {
        repetitions--;
      }
    }

    // time to switch on
    if ((currentTime - lastChange) >= offTime && buzzStatus == LOW) {
      // beep on if we are beeping
      if (beeping) {
        tone(pinBeep, frequency);
        beepStatus = HIGH;
      }
      // led on if we are blinking
      if (blinking) {
        digitalWrite(pinLed, HIGH);
        ledStatus = HIGH;
      }
      // update last status change
      lastChange = currentTime;
    }
  }

  // stop at 0 repetitions
  if (repetitions == 0) {
    stop();
  }
}
