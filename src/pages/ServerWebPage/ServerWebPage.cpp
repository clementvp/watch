#include "ServerWebPage.h"
#include "Preferences.h"
IPAddress apIP;
WebServer server(80);

void setupWiFiAP()
{
    char *M5Ssid = "M5StackAP";
    char *M5Password = "12345678";
    WiFi.softAP(M5Ssid, M5Password);
    delay(500);
    apIP = WiFi.softAPIP();
}

void setupDisplay()
{
    M5.Lcd.setTextDatum(MC_DATUM);
    M5.Lcd.setTextSize(2);
    M5.Lcd.drawString("Wifi AP", M5.Lcd.width() / 2, M5.Lcd.height() / 2);
    M5.Lcd.setTextSize(1);
    M5.Lcd.drawString("IP: " + apIP.toString(), M5.Lcd.width() / 2, M5.Lcd.height() / 2 + 20);
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
                  "<meta name='viewport' content='width=device-width, initial-scale=1.0'>"
                  "<title>Réseaux Wi-Fi disponibles</title>"
                  "</head>"
                  "<body>"
                  "<h1>Réseaux Wi-Fi disponibles</h1>"
                  "<form action='/save' method='post'>"
                  "<select name='ssid'>" +
                  getWifiListOptions() +
                  "</select><br><br>"
                  "<input name='password' placeholder='Mot de passe Wi-Fi'><br><br>"
                  "<input type='submit' value='Connecter et Sauvegarder'>"
                  "</form>"
                  "</body></html>";
    server.send(200, "text/html; charset=utf-8", html);
}

void handleSave()
{
    String ssid = server.arg("ssid");
    String password = server.arg("password");

    Preferences preferences;
    preferences.begin("wifi", false);
    preferences.putString("ssid", ssid);
    preferences.putString("password", password);
    preferences.end();

    String html = "<!DOCTYPE html>"
                  "<html lang='fr'>"
                  "<head>"
                  "<meta charset='UTF-8'>"
                  "<meta name='viewport' content='width=device-width, initial-scale=1.0'>"
                  "<title>Paramètres sauvegardés</title>"
                  "</head>"
                  "<body>"
                  "<h1>Paramètres Wi-Fi sauvegardés</h1>"
                  "<p>SSID: " +
                  ssid +
                  "</p>"
                  "<p>SSID: " +
                  password +
                  "</p>"
                  "<p>Les paramètres ont été enregistrés.</p>"
                  "<a href='/'>Retour</a>"
                  "</body></html>";
    server.send(200, "text/html; charset=utf-8", html);
}

void configureServer()
{
    server.on("/", handleRoot);
    server.on("/save", HTTP_POST, handleSave);
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