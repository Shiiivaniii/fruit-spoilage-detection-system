#include <WiFi.h>
#include <HTTPClient.h>
#include "DHT.h"
#include <LiquidCrystal.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>

// WiFi credentials
const char* ssid = "YOUR_WIFI";
const char* password = "YOUR_PASSWORD";

// ThingSpeak
String apiKey = "YOUR_THINGSPEAK_API_KEY";
const char* server = "api.thingspeak.com";

// Telegram
#define BOT_TOKEN "YOUR_BOT_TOKEN"
#define CHAT_ID "YOUR_CHAT_ID"

WiFiClientSecure client;
UniversalTelegramBot bot(BOT_TOKEN, client);

// Sensors
#define DHTPIN 15
#define DHTTYPE DHT11
#define MQ2PIN 34
#define MQ135PIN 35

DHT dht(DHTPIN, DHTTYPE);

// LCD
LiquidCrystal lcd(19, 23, 18, 5, 21, 4);

struct FruitStage {
  String stageName;
  int minMQ;
  int maxMQ;
};

FruitStage bananaStages[] = {
  {"Unripe", 0, 250},
  {"Fresh", 251, 420},
  {"Ripe", 421, 700},
  {"Spoiled", 701, 2000}
};

FruitStage appleStages[] = {
  {"Unripe", 0, 200},
  {"Fresh", 201, 360},
  {"Ripe", 361, 620},
  {"Spoiled", 621, 2000}
};

FruitStage tomatoStages[] = {
  {"Unripe", 0, 240},
  {"Fresh", 241, 410},
  {"Ripe", 411, 650},
  {"Spoiled", 651, 2000}
};

String selectedFruit = "";

String getRipenessStage(String fruit, int avgMQ) {

  FruitStage* stages;
  int size = 4;

  if (fruit == "banana") stages = bananaStages;
  else if (fruit == "apple") stages = appleStages;
  else if (fruit == "tomato") stages = tomatoStages;
  else return "Unknown";

  for (int i = 0; i < size; i++) {
    if (avgMQ >= stages[i].minMQ && avgMQ <= stages[i].maxMQ) {
      return stages[i].stageName;
    }
  }

  return "Unknown";
}

void setup() {

  Serial.begin(115200);

  dht.begin();
  lcd.begin(16,2);

  WiFi.begin(ssid,password);

  while(WiFi.status()!=WL_CONNECTED){
    delay(1000);
  }

  client.setInsecure();

  lcd.print("System Ready");
}

void loop() {

  float t = dht.readTemperature();
  float h = dht.readHumidity();

  int gas1 = analogRead(MQ2PIN);
  int gas2 = analogRead(MQ135PIN);

  int avgGas = (gas1 + gas2)/2;

  String stage = getRipenessStage(selectedFruit, avgGas);

  lcd.clear();
  lcd.print(stage);

  if(WiFi.status()==WL_CONNECTED){

    WiFiClient client;
    HTTPClient http;

    String url = "http://api.thingspeak.com/update?api_key="+apiKey+
    "&field1="+String(t)+
    "&field2="+String(h)+
    "&field3="+String(avgGas);

    http.begin(client,url);
    http.GET();
    http.end();
  }

  delay(50000);
}