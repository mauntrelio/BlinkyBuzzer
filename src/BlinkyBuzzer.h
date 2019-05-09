#ifndef _BlinkyBuzzer_h
#define _BlinkyBuzzer_h

class BlinkyBuzzer
{
public:
  BlinkyBuzzer(byte _pinLed, byte _pinBeep, unsigned int frequency=1000, unsigned int onTime=500, unsigned int offTime=500);
  
  ~BlinkyBuzzer();

  // inspections
  bool isBlinking(); // is blinking
  bool isBeeping(); // is beeping
  bool isBuzzing(); // is beeping && buzzing
  bool isRunning(); // is beeping || buzzing
  unsigned int getRepetitions(); // get number of repetitions left

  // blink only operations
  void blinkOnce();
  void blinkOnce(unsigned int onTime);
  void blink();
  void blink(int times);
  void blink(int times, unsigned int onOffTime);
  void startBlinking();
  void startBlinking(unsigned int onOffTime);
  void stopBlinking();

  // beep only operations
  void beepOnce();
  void beepOnce(unsigned int onTime);
  void beep();
  void beep(int times);
  void beep(int times, unsigned int onOffTime);
  void startBeeping();
  void startBeeping(unsigned int onOffTime);
  void stopBeeping();

  // blink and beep operations
  void buzzOnce();
  void buzzOnce(unsigned int onTime);
  void buzz();
  void buzz(int times);
  void buzz(int times, unsigned int onOffTime);
  void startBuzzing();
  void startBuzzing(unsigned int onOffTime);
  void stopBuzzing();
  void start();
  void stop();

  // runtime configurations
  void setOnTime(unsigned int duration);
  void setOffTime(unsigned int duration);
  void setOnOffTime(unsigned int duration);
  void setFrequency(unsigned int tone);
  void setRepetitions(int times);
  
  // perform the actual business
  void update();

protected:
  const byte pinLed;
  const byte pinBeep;
  unsigned int onTime;
  unsigned int offTime;
  unsigned int frequency;

  unsigned long currentTime;
  unsigned long lastChange;

  bool ledStatus;
  bool beepStatus;
  bool buzzStatus;

  bool beeping;
  bool blinking;
  bool buzzing;

  int repetitions;

};

#endif
