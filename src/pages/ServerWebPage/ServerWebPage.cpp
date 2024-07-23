#include "ServerWebPage.h"

const char *ssid = "M5StackAP";
const char *password = "12345678";

WebServer server(80);

void setupWiFiAP()
{
    WiFi.softAP(ssid, password);
    IPAddress IP = WiFi.softAPIP();
}

void setupDisplay()
{
    M5.Lcd.setTextDatum(MC_DATUM);
    M5.Lcd.setTextSize(2);
    M5.Lcd.drawString("Wifi AP", M5.Lcd.width() / 2, M5.Lcd.height() / 2);
}

void handleRoot()
{
    server.send(200, "text/html", "<html><body><h1>Hello</h1></body></html>");
}

void configureServer()
{
    server.on("/", handleRoot);
    server.begin();
}

void runServer()
{
    while (true)
    {
        server.handleClient();
        M5.update();

        if (M5.BtnA.wasDoubleClicked())
        {
            break;
        }
    }
}

void cleanup()
{
    server.stop();
    WiFi.softAPdisconnect(true);
    M5.Lcd.clear();
    currentPage = 0;
}

void serverWebPage()
{
    setupWiFiAP();
    setupDisplay();
    configureServer();
    runServer();
    cleanup();
}