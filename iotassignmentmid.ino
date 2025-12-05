#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

// LCD at I2C address 0x20, 16x2 display
LiquidCrystal_I2C lcd(0x20, 16, 2);

Servo myservo;

// Pin definitions
int pirPin = 2;
int ledRed = 3;
int ledGreen = 4;
int buzzer = 5;
int trigPin = 6;
int echoPin = 7;
int servoPin = 9;
int tempPin = A0;
int gasPin = A1;

long duration;
int distance;
float temperature;
int gasValue;
int gasThreshold;

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("SmartHomeSystem");
  delay(1000);

  pinMode(pirPin, INPUT);
  pinMode(ledRed, OUTPUT);
  pinMode(ledGreen, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  myservo.attach(servoPin);
  Serial.begin(9600);

  // Calibrate gas sensor threshold
  long total = 0;
  for (int i = 0; i < 10; i++) {
    total += analogRead(gasPin);
    delay(20);
  }
  gasThreshold = (total / 10) + 100;

  lcd.clear();
}

void loop() {
  noTone(buzzer);

  // PIR motion sensor
  int motion = digitalRead(pirPin);
  digitalWrite(ledRed, motion);
  digitalWrite(ledGreen, !motion);
  if (motion) tone(buzzer, 1000);

  // Ultrasonic distance
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  if (distance < 20 && distance > 0)
    myservo.write(90);
  else
    myservo.write(0);

  // Temperature sensor (LM35)
  int tempADC = analogRead(tempPin);
  float voltage = tempADC * (5.0 / 1023.0);
  temperature = (voltage - 0.5) * 100.0; // adjust if using LM35

  if (temperature > 35) tone(buzzer, 1200);

  // Gas sensor
  gasValue = analogRead(gasPin);
  if (gasValue > gasThreshold) tone(buzzer, 1500);

  // LCD Display
  lcd.setCursor(0, 0);
  lcd.print("S:");
  lcd.print(motion ? "ALERT!" : "Safe");

  lcd.setCursor(8, 0);
  lcd.print("D:");
  lcd.print(distance < 20 && distance > 0 ? "Open" : "Closed");

  lcd.setCursor(0, 1);
  lcd.print("T:");
  if (temperature > 35)
    lcd.print("High!");
  else
    lcd.print(temperature, 1);

  lcd.print(" G:");
  lcd.print(gasValue > gasThreshold ? "Leak!" : "Normal");

  // Serial Monitor
  Serial.print("Temp: ");
  Serial.print(temperature);
  Serial.print(" | Gas: ");
  Serial.print(gasValue);
  Serial.print(" | Dist: ");
  Serial.print(distance);
  Serial.print(" | PIR: ");
  Serial.println(motion);

  delay(500);
}