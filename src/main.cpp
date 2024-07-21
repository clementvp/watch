#include <Arduino.h>
#include <M5Unified.h>
int currentPage = 0;  // 0 pour l'affichage de l'heure, 1 pour le réglage
int settingIndex = 0; // 0 pour les heures, 1 pour les minutes
int hours = 0, minutes = 0, seconds = 0;
bool needUpdate = true;
char lastTimeStr[9] = "";

void displayTime()
{
  auto dt = M5.Rtc.getDateTime();
  char timeStr[9];
  snprintf(timeStr, sizeof(timeStr), "%02d:%02d:%02d", dt.time.hours, dt.time.minutes, dt.time.seconds);

  if (strcmp(timeStr, lastTimeStr) != 0)
  {
    M5.Lcd.setTextColor(WHITE, BLACK); // Texte blanc sur fond noir
    M5.Lcd.setTextSize(4);
    M5.Lcd.setTextDatum(MC_DATUM);
    M5.Lcd.drawString(timeStr, M5.Lcd.width() / 2, M5.Lcd.height() / 2);
    strcpy(lastTimeStr, timeStr);
  }
}

void updateRTC()
{
  M5.Rtc.setTime({hours, minutes, seconds});
}

void setTime()
{
  static bool needRedraw = true;

  if (needRedraw)
  {
    M5.Lcd.clear();
    M5.Lcd.setTextSize(2);
    M5.Lcd.setCursor(10, 10);
    M5.Lcd.printf("Set Time");
    M5.Lcd.setTextSize(1);
    M5.Lcd.setCursor(10, M5.Lcd.height() - 20);
    M5.Lcd.printf("A: Save  B: Switch  C: +");
    needRedraw = false;
  }

  M5.Lcd.setTextSize(4);
  M5.Lcd.setCursor(M5.Lcd.width() / 2 - 50, M5.Lcd.height() / 2 - 20);
  M5.Lcd.printf("%02d:%02d", hours, minutes);

  // Souligner la valeur en cours de réglage
  if (settingIndex == 0)
  {
    M5.Lcd.drawLine(M5.Lcd.width() / 2 - 50, M5.Lcd.height() / 2 + 20, M5.Lcd.width() / 2 - 10, M5.Lcd.height() / 2 + 20, WHITE);
    M5.Lcd.drawLine(M5.Lcd.width() / 2 + 10, M5.Lcd.height() / 2 + 20, M5.Lcd.width() / 2 + 50, M5.Lcd.height() / 2 + 20, BLACK);
  }
  else
  {
    M5.Lcd.drawLine(M5.Lcd.width() / 2 - 50, M5.Lcd.height() / 2 + 20, M5.Lcd.width() / 2 - 10, M5.Lcd.height() / 2 + 20, BLACK);
    M5.Lcd.drawLine(M5.Lcd.width() / 2 + 10, M5.Lcd.height() / 2 + 20, M5.Lcd.width() / 2 + 50, M5.Lcd.height() / 2 + 20, WHITE);
  }

  if (M5.BtnA.wasPressed())
  {
    settingIndex = 1 - settingIndex;
  }

  if (M5.BtnB.wasPressed())
  {
    if (settingIndex == 0)
    {
      hours = (hours + 1) % 24;
    }
    else
    {
      minutes = (minutes + 1) % 60;
    }
  }

  if (M5.BtnPWR.wasPressed())
  {
    updateRTC();
    currentPage = 0;
    needRedraw = true;
    M5.Lcd.clear();
  }
}

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

  if (M5.BtnA.wasDoubleClicked())
  {
    M5.Lcd.clear();
    currentPage = 1 - currentPage; // Basculer entre les pages
    settingIndex = 0;
  }

  if (currentPage == 0)
  {
    displayTime();
  }
  else
  {
    setTime();
  }
}