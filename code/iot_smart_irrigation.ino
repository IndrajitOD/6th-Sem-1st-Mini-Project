#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// -------------------- BLYNK CONFIG --------------------
#define BLYNK_TEMPLATE_ID "YOUR_TEMPLATE_ID"
#define BLYNK_TEMPLATE_NAME "Smart Irrigation System"
#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// -------------------- LCD SETUP -----------------------
LiquidCrystal_I2C lcd(0x27, 16, 2);

// -------------------- CREDENTIALS ---------------------
char auth[] = "YOUR_BLYNK_TOKEN";
char ssid[] = "YOUR_WIFI_NAME";
char pass[] = "YOUR_WIFI_PASSWORD";

// -------------------- VARIABLES -----------------------
BlynkTimer timer;
bool manualMode = 0;   // 0 = AUTO, 1 = MANUAL

// -------------------- PINS ----------------------------
#define sensor A0
#define waterPump D3

// -------------------- THRESHOLD -----------------------
int moistureThreshold = 30;   // % below which watering starts

// -------------------- SETUP ---------------------------
void setup() {
  Serial.begin(9600);

  pinMode(waterPump, OUTPUT);
  digitalWrite(waterPump, HIGH); // Pump OFF initially (active LOW relay)

  lcd.begin();
  lcd.backlight();

  // Blynk connection
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);

  // Loading screen
  lcd.setCursor(0, 0);
  lcd.print("Smart Irrigation");
  lcd.setCursor(0, 1);
  lcd.print("System Starting");
  delay(2000);
  lcd.clear();

  timer.setInterval(1000L, soilMoistureSensor);
}

// -------------------- MANUAL CONTROL ------------------
BLYNK_WRITE(V1) {
  manualMode = param.asInt();

  if (manualMode == 1) {
    digitalWrite(waterPump, LOW);  // Pump ON
    lcd.setCursor(0, 1);
    lcd.print("Manual: ON  ");
  } else {
    digitalWrite(waterPump, HIGH); // Pump OFF
    lcd.setCursor(0, 1);
    lcd.print("Manual: OFF ");
  }
}

// -------------------- SENSOR FUNCTION -----------------
void soilMoistureSensor() {
  int value = analogRead(sensor);
  value = map(value, 0, 1024, 100, 0); // Convert to %

  // Send data to Blynk
  Blynk.virtualWrite(V0, value);

  // Display moisture on LCD
  lcd.setCursor(0, 0);
  lcd.print("Moisture:");
  lcd.print(value);
  lcd.print("%  ");

  // ---------------- AUTO MODE ----------------
  if (manualMode == 0) {
    if (value < moistureThreshold) {
      digitalWrite(waterPump, LOW);  // Pump ON
      lcd.setCursor(0, 1);
      lcd.print("Auto: ON   ");
    } else {
      digitalWrite(waterPump, HIGH); // Pump OFF
      lcd.setCursor(0, 1);
      lcd.print("Auto: OFF  ");
    }
  }
}

// -------------------- LOOP ----------------------------
void loop() {
  Blynk.run();
  timer.run();
}
