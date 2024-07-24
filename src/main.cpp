#include <M5Unified.h>
#include "pages/DisplayTime/DisplayTime.h"
#include "pages/SetTime/SetTime.h"
#include "pages/ServerWebPage/ServerWebPage.h"

const unsigned long SLEEP_TIMEOUT = 60000; // 1 minute en millisecondes
const int DISPLAY_PAGE = 0;
const int SET_TIME_PAGE = 1;
const int SET_DATE_PAGE = 2;
const int SERVER_WEB_PAGE = 3;
int currentPage = DISPLAY_PAGE;
unsigned long lastInteractionTime = 0;

void setup()
{
  auto cfg = M5.config();
  M5.begin(cfg);
  M5.Rtc.begin();
  M5.Lcd.setRotation(1);
  M5.Lcd.setBrightness(1);
  lastInteractionTime = millis();
}

void goToSleep()
{
  M5.Power.powerOff();
}

bool isTimeToSleep()
{
  millis() - lastInteractionTime > SLEEP_TIMEOUT;
}

void updateLastInteractionTime()
{
  if (currentPage != DISPLAY_PAGE)
  {
    lastInteractionTime = millis();
  }
}

void handleCurrentPage()
{
  switch (currentPage)
  {
  case DISPLAY_PAGE:
    displayTime();
    break;
  case SET_TIME_PAGE:
    setTime();
    break;
  case SET_DATE_PAGE:
    setDate();
    break;
  case SERVER_WEB_PAGE:
    serverWebPage();
    break;
  }
}

void loop()
{
  M5.update();
  updateLastInteractionTime();

  if (isTimeToSleep())
  {
    goToSleep();
  }

  handleCurrentPage();
}