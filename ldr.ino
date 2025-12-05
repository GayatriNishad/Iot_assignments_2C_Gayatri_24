int LDR_Pin = A0;     // LDR connected to analog pin A0
int LDR_Value = 0;    // Variable to store light value
void setup() {
  Serial.begin(9600);  // Start serial monitor
  pinMode(13, OUTPUT);
}
void loop() {
  LDR_Value = analogRead(LDR_Pin);  // Read the LDR value (0–1023)
  Serial.print("Light Intensity: ");
  Serial.println(LDR_Value);        // Print value to Serial Monitor
  if (LDR_Value > 400) {   
    digitalWrite(13, HIGH);
  } else {
    digitalWrite(13, LOW);
  }
  delay(500);                       // Small delay
}