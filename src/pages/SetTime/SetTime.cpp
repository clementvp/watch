#include "SetTime.h";

int settingIndex = 0;
int hours = 0, minutes = 0, seconds = 0;

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
        M5.Lcd.printf("A: Switch  B: +  PWR: save");
        needRedraw = false;
    }

    M5.Lcd.setTextSize(4);
    M5.Lcd.setCursor(M5.Lcd.width() / 2 - 50, M5.Lcd.height() / 2 - 20);
    M5.Lcd.printf("%02d:%02d", hours, minutes);

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