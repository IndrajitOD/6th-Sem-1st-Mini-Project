/*
 * Smart Plant Watering System
 * 6th-semester academic project reconstruction.
 *
 * Target: ESP8266 / NodeMCU-class board
 *
 * A0 -> soil moisture sensor
 * D3 -> relay control
 * LCD -> I2C
 * V0 -> Blynk moisture value
 * V1 -> Blynk manual pump control
 *
 * Replace credential placeholders before uploading.
 */

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define BLYNK_TEMPLATE_ID "YOUR_TEMPLATE_ID"
#define BLYNK_TEMPLATE_NAME "Smart Irrigation System"
#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

char auth[] = "YOUR_BLYNK_TOKEN";
char ssid[] = "YOUR_WIFI_NAME";
char pass[] = "YOUR_WIFI_PASSWORD";

BlynkTimer timer;

const uint8_t SENSOR_PIN = A0;
const uint8_t WATER_PUMP_PIN = D3;
const int MOISTURE_THRESHOLD = 30;

bool manualMode = false;

void pumpOn() {
  digitalWrite(WATER_PUMP_PIN, LOW);   // active-LOW relay
}

void pumpOff() {
  digitalWrite(WATER_PUMP_PIN, HIGH);
}

void soilMoistureSensor();

void setup() {
  Serial.begin(9600);

  pinMode(WATER_PUMP_PIN, OUTPUT);
  pumpOff();

  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("Smart Irrigation");
  lcd.setCursor(0, 1);
  lcd.print("System Starting");
  delay(2000);
  lcd.clear();

  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
  timer.setInterval(1000L, soilMoistureSensor);
}

// V1: 1 = manual pump ON, 0 = automatic mode
BLYNK_WRITE(V1) {
  manualMode = param.asInt();

  if (manualMode) {
    pumpOn();
    lcd.setCursor(0, 1);
    lcd.print("Manual: ON     ");
  } else {
    pumpOff();
    lcd.setCursor(0, 1);
    lcd.print("Manual: OFF    ");
  }
}

void soilMoistureSensor() {
  int rawValue = analogRead(SENSOR_PIN);

  // Approximate conversion from the recovered project code.
  int moisture = map(rawValue, 0, 1023, 100, 0);
  moisture = constrain(moisture, 0, 100);

  Serial.print("Raw: ");
  Serial.print(rawValue);
  Serial.print(" | Moisture: ");
  Serial.print(moisture);
  Serial.println("%");

  Blynk.virtualWrite(V0, moisture);

  lcd.setCursor(0, 0);
  lcd.print("Moisture:");
  lcd.print(moisture);
  lcd.print("%   ");

  if (!manualMode) {
    if (moisture < MOISTURE_THRESHOLD) {
      pumpOn();
      lcd.setCursor(0, 1);
      lcd.print("Auto: ON       ");
    } else {
      pumpOff();
      lcd.setCursor(0, 1);
      lcd.print("Auto: OFF      ");
    }
  }
}

void loop() {
  Blynk.run();
  timer.run();
}
