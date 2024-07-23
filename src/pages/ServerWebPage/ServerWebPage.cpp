#include <M5Unified.h>
#include "ServerWebPage.h"

const char *ssid = "M5StackAP";
const char *password = "12345678";

WebServer server(80);

void handleRoot()
{
    server.send(200, "text/html", "<html><body><h1>Hello</h1></body></html>");
}

void serverWebPage()
{
    WiFi.softAP(ssid, password);
    IPAddress IP = WiFi.softAPIP();
    M5.Lcd.setTextSize(2);
    M5.Lcd.setCursor(0, 100);
    M5.Lcd.print("Hello World");

    server.on("/", handleRoot);
    server.begin();

    // Boucle de gestion du serveur
    while (true)
    {
        server.handleClient();
        M5.update();

        if (M5.BtnA.wasDoubleClicked())
        {
            // Double-clic détecté, on sort de la boucle et retourne à la page display
            break;
        }
    }

    // Nettoyage avant de quitter la page
    server.stop();
    WiFi.softAPdisconnect(true);
    M5.Lcd.clear();
    currentPage = 0;
}