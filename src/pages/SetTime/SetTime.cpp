#include "SetTime.h"

int settingIndexTime = 0;
int hours = 0, minutes = 0, seconds = 0;
int settingIndexDate = 0;
int date = 1, month = 1, year = 2024;

void updateRTCTime()
{
    M5.Rtc.setTime({hours, minutes, seconds});
}

void updateRTCDate()
{
    M5.Rtc.setDate({year, month, date});
}

void setDate()
{
    {
        static bool needRedraw = true;
        M5.Lcd.setTextDatum(MC_DATUM);
        if (needRedraw)
        {
            M5.Lcd.clear();
            M5.Lcd.setTextSize(2);
            M5.Lcd.setCursor(10, 10);
            M5.Lcd.printf("Set Date");
            M5.Lcd.setTextSize(1);
            M5.Lcd.setCursor(10, M5.Lcd.height() - 20);
            M5.Lcd.printf("A: Switch  B: +  PWR: save");
            auto dt = M5.Rtc.getDate();
            date = dt.date;
            month = dt.month;
            year = dt.year;
            needRedraw = false;
        }

        M5.Lcd.setTextSize(3);
        char dateStr[11];
        snprintf(dateStr, sizeof(dateStr), "%02d/%02d/%04d", date, month, year);
        M5.Lcd.drawString(dateStr, M5.Lcd.width() / 2, M5.Lcd.height() / 2);

        if (settingIndexDate == 0)
        {
            M5.Lcd.drawLine(M5.Lcd.width() / 2 - 60, M5.Lcd.height() / 2 + 20, M5.Lcd.width() / 2 - 40, M5.Lcd.height() / 2 + 20, WHITE);
            M5.Lcd.drawLine(M5.Lcd.width() / 2 - 35, M5.Lcd.height() / 2 + 20, M5.Lcd.width() / 2 - 15, M5.Lcd.height() / 2 + 20, BLACK);
            M5.Lcd.drawLine(M5.Lcd.width() / 2 - 10, M5.Lcd.height() / 2 + 20, M5.Lcd.width() / 2 + 60, M5.Lcd.height() / 2 + 20, BLACK);
        }
        else if (settingIndexDate == 1)
        {
            M5.Lcd.drawLine(M5.Lcd.width() / 2 - 60, M5.Lcd.height() / 2 + 20, M5.Lcd.width() / 2 - 40, M5.Lcd.height() / 2 + 20, BLACK);
            M5.Lcd.drawLine(M5.Lcd.width() / 2 - 35, M5.Lcd.height() / 2 + 20, M5.Lcd.width() / 2 - 15, M5.Lcd.height() / 2 + 20, WHITE);
            M5.Lcd.drawLine(M5.Lcd.width() / 2 - 10, M5.Lcd.height() / 2 + 20, M5.Lcd.width() / 2 + 60, M5.Lcd.height() / 2 + 20, BLACK);
        }
        else
        {
            M5.Lcd.drawLine(M5.Lcd.width() / 2 - 60, M5.Lcd.height() / 2 + 20, M5.Lcd.width() / 2 - 40, M5.Lcd.height() / 2 + 20, BLACK);
            M5.Lcd.drawLine(M5.Lcd.width() / 2 - 35, M5.Lcd.height() / 2 + 20, M5.Lcd.width() / 2 - 15, M5.Lcd.height() / 2 + 20, BLACK);
            M5.Lcd.drawLine(M5.Lcd.width() / 2 - 10, M5.Lcd.height() / 2 + 20, M5.Lcd.width() / 2 + 60, M5.Lcd.height() / 2 + 20, WHITE);
        }
        if (M5.BtnA.wasPressed())
        {
            settingIndexDate = (settingIndexDate + 1) % 3;
        }

        if (M5.BtnB.wasPressed())
        {
            if (settingIndexDate == 0)
            {
                date = (date % 31) + 1;
            }
            else if (settingIndexDate == 1)
            {
                month = (month % 12) + 1;
            }
            else
            {
                year = (year + 1) % 2099;
            }
        }

        if (M5.BtnA.wasDoubleClicked())
        {
            M5.Lcd.clear();
            currentPage = 0;
            needRedraw = true;
        }

        if (M5.BtnPWR.wasPressed())
        {
            updateRTCDate();
            M5.Lcd.clear();
            currentPage = 0;
            needRedraw = true;
        }
    }
}

void setTime()
{
    static bool needRedraw = true;
    M5.Lcd.setTextDatum(MC_DATUM);
    if (needRedraw)
    {
        M5.Lcd.clear();
        M5.Lcd.setTextSize(2);
        M5.Lcd.setCursor(10, 10);
        M5.Lcd.printf("Set Time");
        M5.Lcd.setTextSize(1);
        M5.Lcd.setCursor(10, M5.Lcd.height() - 20);
        M5.Lcd.printf("A: Switch  B: +  PWR: save");
        auto dt = M5.Rtc.getTime();
        hours = dt.hours;
        minutes = dt.minutes;
        needRedraw = false;
    }

    M5.Lcd.setTextSize(4);
    M5.Lcd.setCursor(M5.Lcd.width() / 2 - 50, M5.Lcd.height() / 2 - 20);
    M5.Lcd.printf("%02d:%02d", hours, minutes);

    if (settingIndexTime == 0)
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
        settingIndexTime = 1 - settingIndexTime;
    }

    if (M5.BtnB.wasPressed())
    {
        if (settingIndexTime == 0)
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
        updateRTCTime();
        M5.Lcd.clear();
        currentPage = 2;
        needRedraw = true;
    }

    if (M5.BtnA.wasDoubleClicked())
    {
        M5.Lcd.clear();
        currentPage = 2;
        needRedraw = true;
    }
}
