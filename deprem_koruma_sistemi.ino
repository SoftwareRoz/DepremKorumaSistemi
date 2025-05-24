#include <LiquidCrystal.h>

// LCD pin tanımları (RS, E, D4, D5, D6, D7)
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

// Pin tanımları
#define SENSOR_PIN A0
#define LED1_PIN 2    
#define LED2_PIN 3    
#define LED3_PIN 4    
#define BUZZER_PIN 5  
#define RELAY_PIN 13 

int sensorValue = 0;
bool ampulKapali = false;

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.print("Sensor Sistemi");

  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);
  pinMode(LED3_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(RELAY_PIN, OUTPUT);

  digitalWrite(RELAY_PIN, HIGH); 
}

void loop() {
  sensorValue = analogRead(SENSOR_PIN);

  Serial.print("Sensor Value: ");
  Serial.println(sensorValue);

  lcd.setCursor(0, 1);
  lcd.print("deger:");
  lcd.print(sensorValue);
  lcd.print(" m/s^2   "); 

  if (sensorValue >= 500) {
    
    setOutputs(false, false, true, true);

    digitalWrite(RELAY_PIN, HIGH);  
    ampulKapali = true;
  }
  else if (sensorValue >= 300) {
    
    setOutputs(false, true, false, false);

    if (!ampulKapali) digitalWrite(RELAY_PIN, LOW); 
  }
  else if (sensorValue >= 200) {
    
    setOutputs(true, false, false, false);

    if (!ampulKapali) digitalWrite(RELAY_PIN, LOW);
  }
  else {
    setOutputs(false, false, false, false);

    if (!ampulKapali) digitalWrite(RELAY_PIN, HIGH);
  }

  delay(100);
}

void setOutputs(bool led1, bool led2, bool led3, bool buzzer) {
  digitalWrite(LED1_PIN, led1 ? HIGH : LOW);
  digitalWrite(LED2_PIN, led2 ? HIGH : LOW);
  digitalWrite(LED3_PIN, led3 ? HIGH : LOW);
  digitalWrite(BUZZER_PIN, buzzer ? HIGH : LOW);
}
