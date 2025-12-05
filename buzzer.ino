// Pins
const int touchPin = 2;   // TTP223 OUT pin
const int buzzerPin = 8;  // Buzzer pin

void setup() {
  pinMode(touchPin, INPUT);     // TTP223 outputs HIGH/LOW
  pinMode(buzzerPin, OUTPUT);   // Buzzer output
  Serial.begin(9600);
}

void loop() {
  int touchState = digitalRead(touchPin);  // Read touch sensor

  if (touchState == HIGH) {          // Touch detected
    digitalWrite(buzzerPin, HIGH);   // Turn buzzer ON
    Serial.println("Touch detected!");
  } 
  else {
    digitalWrite(buzzerPin, LOW);    // Turn buzzer OFF
    Serial.println("No touch");
  }

  delay(100);
}