#include <Arduino.h>
#include <M5Unified.h>
#include "pages/DisplayTime/DisplayTime.h"
#include "pages/SetTime/SetTime.h"

int currentPage = 0;
void setup()
{
  auto cfg = M5.config();
  M5.begin(cfg);
  M5.Rtc.begin();
  M5.Lcd.setRotation(1);
  M5.Lcd.setBrightness(1);
}

void goToSleep()
{

  M5.Power.powerOff();
}

void loop()
{
  static unsigned long lastActivityTime = millis();

  if (M5.BtnA.wasPressed() || M5.BtnB.wasPressed() || M5.BtnPWR.wasPressed())
  {
    lastActivityTime = millis();
  }

  if (currentPage == 0 && millis() - lastActivityTime > 60000)
  {
    goToSleep();
  }

  M5.update();

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
}
