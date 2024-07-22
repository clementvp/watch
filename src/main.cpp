#include <Arduino.h>
#include <M5Unified.h>
#include "pages/DisplayTime/DisplayTime.h"
#include "pages/SetTime/SetTime.h"

int currentPage = 0;
unsigned long lastActivityTime = 0;
void setup()
{
  auto cfg = M5.config();
  M5.begin(cfg);
  M5.Rtc.begin();
  M5.Lcd.setRotation(1);
  M5.Lcd.setBrightness(1);
  lastActivityTime = millis(); // Initialiser lastActivityTime dans setup
}

void goToSleep()
{

  M5.Power.powerOff();
}

void resetActivityTimer()
{
  lastActivityTime = millis();
}

void loop()
{
  static int previousPage = -1;
  M5.update();

  if (currentPage == 0 && previousPage != 0)
  {
    resetActivityTimer();
  }

  if (currentPage == 0 && millis() - lastActivityTime > 60000)
  {
    goToSleep();
  }

  if (currentPage == 0)
  {
    displayTime();
  }
  else if (currentPage == 1)
  {
    setTime();
  }
  else if (currentPage == 2)
  {
    setDate();
  }

  previousPage = currentPage;
}
