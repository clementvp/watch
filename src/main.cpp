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
}

void loop()
{

  M5.update();

  if (currentPage == 0)
  {
    displayTime();
  }
  else if (currentPage == 1)
  {
    setTime();
  }
  else
  {
    setDate();
  }
}