#include <Arduino.h>
#include <ArduinoJson.h>
#include <SPIFFS.h>

#include "settings.hpp"
#include "functions.hpp"
#include "settingsReset.hpp"
#include "settingsRead.hpp"
#include "settingsSave.hpp"
#include "esp32_wifi.hpp"


void setup() {
    // Baudrate
    Serial.begin(115200);
    // CPU Freq
    setCpuFrequencyMhz(240);
    // Inicio del Log por serial
    log("\nInfo: Iniciando Setup");

    // Configurar los Pines
    settingsPines();
    

    // Inicio del SPIFFS                 
    if (!SPIFFS.begin()){
        log(F("Error: Falló la inicialización del SPIFFS"));
        while (true);
    }
    // Lee la Configuración WiFi
    settingsReadWiFi();

    // Configuracion WIFI
    WiFi.disconnect(true);
    delay(1000);

    // Setup del WiFI
    wifi_setup(); 


}

void loop() {
   yield();
    // -------------------------------------------------------------------
    // WIFI
    // -------------------------------------------------------------------
    if (wifi_mode == WIFI_STA){
        wifiLoop();
    }else if (wifi_mode == WIFI_AP){
        wifiAPLoop();
    } 

}




