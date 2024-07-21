#include "DisplayTime.h"

char lastTimeStr[9] = "";

void displayTime()
{
    auto dt = M5.Rtc.getDateTime();
    char timeStr[9];
    snprintf(timeStr, sizeof(timeStr), "%02d:%02d:%02d", dt.time.hours, dt.time.minutes, dt.time.seconds);
    char dateStr[11];
    snprintf(dateStr, sizeof(dateStr), "%02d/%02d/%04d", dt.date.date, dt.date.month, dt.date.year);
    int batteryLevel = M5.Power.getBatteryLevel();

    if (strcmp(timeStr, lastTimeStr) != 0)
    {
        M5.Lcd.setTextSize(2);
        M5.Lcd.setTextDatum(TL_DATUM);
        M5.Display.setCursor(0, 0);
        M5.Display.printf("%d%%", batteryLevel);
        M5.Lcd.setTextColor(WHITE, BLACK);
        M5.Lcd.setTextSize(4);
        M5.Lcd.setTextDatum(MC_DATUM);
        M5.Lcd.drawString(timeStr, M5.Lcd.width() / 2, M5.Lcd.height() / 2);
        M5.Lcd.setTextSize(2);
        M5.Lcd.setTextDatum(BC_DATUM);
        M5.Lcd.drawString(dateStr, M5.Lcd.width() / 2, M5.Lcd.height());
        strcpy(lastTimeStr, timeStr);
    }

    if (M5.BtnA.wasDoubleClicked())
    {
        M5.Lcd.clear();
        currentPage = 1;
    }
}