#include "DisplayTime.h"

char lastTimeStr[9] = "";

void displayTime()
{
    auto dt = M5.Rtc.getDateTime();
    char timeStr[9];
    snprintf(timeStr, sizeof(timeStr), "%02d:%02d:%02d", dt.time.hours, dt.time.minutes, dt.time.seconds);

    if (strcmp(timeStr, lastTimeStr) != 0)
    {
        M5.Lcd.setTextColor(WHITE, BLACK);
        M5.Lcd.setTextSize(4);
        M5.Lcd.setTextDatum(MC_DATUM);
        M5.Lcd.drawString(timeStr, M5.Lcd.width() / 2, M5.Lcd.height() / 2);
        strcpy(lastTimeStr, timeStr);
    }

    if (M5.BtnA.wasDoubleClicked())
    {
        M5.Lcd.clear();
        currentPage = 1;
    }
}