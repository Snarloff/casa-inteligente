//#define ENABLE_DEBUG

#ifdef ENABLE_DEBUG
#define DEBUG_ESP_PORT Serial
#define NODEBUG_WEBSOCKETS
#define NDEBUG
#endif

#include <Arduino.h>
#include <WiFi.h>
#include <Wire.h>
#include "SinricPro.h"
#include "SinricProSwitch.h"
#include "SSD1306Wire.h"

#define WIFI_SSID ""
#define WIFI_PASS ""
#define APP_KEY ""
#define APP_SECRET ""
#define SWITCH_SALA ""
#define SWITCH_QUARTO ""
#define SWITCH_COZINHA ""

#define LED_AZUL 21
#define LED_AMARELO 5
#define LED_VERDE 4

bool onPowerSala(const String &deviceId, bool &state) {
  digitalWrite(LED_AZUL, state);
  if (state == HIGH) {
    powerMessage("Ligando a luz da sala...");
  } else {
    powerMessage("Desligando a luz da sala...");
  }
  return true;
}

bool onPowerQuarto(const String &deviceId, bool &state) {
  digitalWrite(LED_VERDE, state);
  if (state == HIGH) {
    powerMessage("Ligando a luz do quarto...");
  } else {
    powerMessage("Desligando a luz do quarto...");
  }
  return true;
}

bool onPowerCozinha(const String &deviceId, bool &state) {
  digitalWrite(LED_AMARELO, state);
  if (state == HIGH) {
    powerMessage("Ligando a luz da cozinha...");
  } else {
    powerMessage("Desligando a luz da cozinha...");
  }
  return true;
}

SSD1306Wire display(0x3c, 18, 19);

void setup() {
  pinMode(LED_AZUL, OUTPUT);
  pinMode(LED_AMARELO, OUTPUT);
  pinMode(LED_VERDE, OUTPUT);
  pinMode(2, OUTPUT);

  digitalWrite(2, HIGH);

  WiFi.begin(WIFI_SSID, WIFI_PASS);
  display.init();
  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_10);

  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.drawString(30, 20, "Bem vindo (a)");
  display.drawString(20, 30, "a Casa Inteligente");
  display.display();

  SinricProSwitch &salaSwitch = SinricPro[SWITCH_SALA];
  SinricProSwitch &quartoSwitch = SinricPro[SWITCH_QUARTO];
  SinricProSwitch &cozinhaSwitch = SinricPro[SWITCH_COZINHA];

  salaSwitch.onPowerState(onPowerSala);
  quartoSwitch.onPowerState(onPowerQuarto);
  cozinhaSwitch.onPowerState(onPowerCozinha);

  SinricPro.begin(APP_KEY, APP_SECRET);
}

void loop() {
  SinricPro.handle();
}

void powerMessage(const String &message) {
  display.clear();
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.setFont(ArialMT_Plain_10);
  display.drawString(10, 20, message);
  display.display();
}
