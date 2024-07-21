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

void setTime()
{
  M5.Display.setCursor(0, 0);
  M5.Display.setTextSize(2);
  M5.Display.printf("Set time");
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

  if (M5.BtnA.wasPressed())
  {
    M5.Lcd.clear();
    currentPage = 1 - currentPage; // Basculer entre les pages
    settingIndex = 0;              // Réinitialiser l'index de réglage
  }

  if (currentPage == 0)
  {
    displayTime();
  }
  else
  {
    setTime();
  }
  delay(100);
}