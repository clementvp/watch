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

String getWifiListOptions()
{
    String wifiList = "";
    int n = WiFi.scanNetworks();
    for (int i = 0; i < n; ++i)
    {
        wifiList += "<option value=\"" + WiFi.SSID(i) + "\">" + WiFi.SSID(i) + "</option>";
        delay(10);
    }
    return wifiList;
}

void handleRoot()
{
    String html = "<!DOCTYPE html>"
                  "<html lang='fr'>"
                  "<head>"
                  "<meta charset='UTF-8'>"
                  "<title>Réseaux Wi-Fi disponibles</title>"
                  "</head>"
                  "<body>"
                  "<h1>Réseaux Wi-Fi disponibles</h1>"
                  "<form>"
                  "<select name='wifi'>" +
                  getWifiListOptions() +
                  "</select>"
                  "<input type='submit' value='Connecter'>"
                  "</form>"
                  "</body></html>";
    server.send(200, "text/html; charset=utf-8", html);
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