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
#include "PubSubClient.h"
#include <analogWrite.h>

#define WIFI_SSID       ""
#define WIFI_PASS       ""
#define APP_KEY         ""
#define APP_SECRET      ""
#define SWITCH_SALA     ""
#define SWITCH_QUARTO   ""
#define SWITCH_COZINHA  ""

#define LED_AZUL        21
#define LED_AMARELO     5
#define LED_VERDE       4

const char *mqttServer = "broker.hivemq.com";
const int port = 1883;
char clientId[50];

WiFiClient espClient;
PubSubClient client(espClient);

bool onPowerSala(const String &deviceId, bool &state) {
  if (state == HIGH) {
    analogWrite(LED_AZUL, 255);
    client.publish("Snarloff/sala", "on");
    powerMessage("Ligando a luz da sala...");
  } else {
    analogWrite(LED_AZUL, 0);
    client.publish("Snarloff/sala", "off");
    powerMessage("Desligando a luz da sala...");
  }
  return true;
}

bool onPowerQuarto(const String &deviceId, bool &state) {
  if (state == HIGH) {
    analogWrite(LED_VERDE, 255);
    client.publish("Snarloff/quarto", "on");
    powerMessage("Ligando a luz do quarto...");
  } else {
    analogWrite(LED_VERDE, 0);
    client.publish("Snarloff/quarto", "off");
    powerMessage("Desligando a luz do quarto...");
  }
  return true;
}

bool onPowerCozinha(const String &deviceId, bool &state) {
  if (state == HIGH) {
    analogWrite(LED_AMARELO, 255);
    client.publish("Snarloff/cozinha", "on");
    powerMessage("Ligando a luz da cozinha...");
  } else {
    analogWrite(LED_AMARELO, 0);
    client.publish("Snarloff/cozinha", "off");
    powerMessage("Desligando a luz da cozinha...");
  }
  return true;
}

SSD1306Wire display(0x3c, 18, 19);

void setup() {
  Serial.begin(115200);
  randomSeed(analogRead(0));

  pinMode(LED_AZUL, OUTPUT);
  pinMode(LED_AMARELO, OUTPUT);
  pinMode(LED_VERDE, OUTPUT);
  pinMode(2, OUTPUT);

  digitalWrite(2, HIGH);

  WiFi.begin(WIFI_SSID, WIFI_PASS);
  client.setServer(mqttServer, port);
  client.setCallback(callback);

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

  if (!client.connected()) {
    mqttReconnect();
  }

  client.loop();
}

void mqttReconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    long r = random(1000);
    sprintf(clientId, "clientId-%ld", r);
    if (client.connect(clientId)) {
      Serial.print(clientId);
      Serial.println(" connected");
      client.subscribe("Snarloff/sala");
      client.subscribe("Snarloff/quarto");
      client.subscribe("Snarloff/cozinha");
      client.subscribe("Snarloff/intensidade");
      client.subscribe("Snarloff/intensidadequarto");
      client.subscribe("Snarloff/intensidadecozinha");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void callback(char *topic, byte *message, unsigned int length) {
  Serial.print("Mensagem recebida no topico: ");
  Serial.print(topic);
  Serial.print(". Messagem: ");
  String stMessage;

  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
    stMessage += (char)message[i];
  }

  Serial.println();

  if (String(topic) == "Snarloff/sala") {
    Serial.print("Saida alterada para ");
    if (stMessage == "on") {
      powerMessage("Ligando a luz da sala...");
      Serial.println("on");
      analogWrite(LED_AZUL, 255);
    } else if (stMessage == "off") {
      powerMessage("Desligando a luz da sala...");
      Serial.println("off");
      analogWrite(LED_AZUL, 0);
    }
  }

  if (String(topic) == "Snarloff/cozinha") {
    Serial.print("Saida alterada para ");
    if (stMessage == "on") {
      powerMessage("Ligando a luz da cozinha...");
      Serial.println("on");
      analogWrite(LED_AMARELO, 255);
    } else if (stMessage == "off") {
      powerMessage("Desligando a luz da cozinha...");
      Serial.println("off");
      analogWrite(LED_AMARELO, 0);
    }
  }

  if (String(topic) == "Snarloff/quarto") {
    Serial.print("Saida alterada para");
    if (stMessage == "on") {
      powerMessage("Ligando a luz do quarto...");
      Serial.println("on");
      analogWrite(LED_VERDE, 255);
    } else if (stMessage == "off") {
      powerMessage("Desligando a luz do quarto...");
      Serial.println("off");
      analogWrite(LED_VERDE, 0);
    }
  }

  if (String(topic) == "Snarloff/intensidade") {
    Serial.print("Alterando intensidade para ");
    analogWrite(LED_AZUL, stMessage.toInt());
    powerMessage("Intensidade para " + String(stMessage));
  }
  
  if (String(topic) == "Snarloff/intensidadequarto") {
    Serial.print("Alterando intensidade para ");
    analogWrite(LED_VERDE, stMessage.toInt());
    powerMessage("Intensidade para " + String(stMessage));
  }
  
  if (String(topic) == "Snarloff/intensidadecozinha") {
    Serial.print("Alterando intensidade para ");
    analogWrite(LED_AMARELO, stMessage.toInt());
    powerMessage("Intensidade para " + String(stMessage));
  }
}

void powerMessage(const String &message) {
  display.clear();
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.setFont(ArialMT_Plain_10);
  display.drawString(0, 20, message);
  display.drawString(20, 40, "Casa Inteligente");
  display.drawString(20, 50, "Snarloff ©️ 2022");
  display.display();
}
