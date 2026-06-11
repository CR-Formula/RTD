void setup() {
  pinMode(9, OUTPUT);       // Speaker (PWM Output)
  pinMode(4, INPUT_PULLUP); // Tractive System Voltage
  pinMode(5, INPUT_PULLUP); // Button
  pinMode(6, OUTPUT);       // Reference Voltage for Pedals (Inverted)
  pinMode(7, OUTPUT);       // Power Amplifier Enable Pin

  // Enable pin for power amplifier (always on) 
  digitalWrite(7, HIGH);
}

void loop() {
  // (1) Retry if tractive voltage is not enabled
  if (digitalRead(4) == LOW) { 
    digitalWrite(6, HIGH); // Disable pedal reference signal
    return; // Retry
  }

  // (2) Check if the button is enabled
  if (digitalRead(5) == HIGH) {
    // Send the brake reference voltage (enable brake read)
    digitalWrite(6, LOW);

    // (3) Check the brake pedal position (0-1023)
    if (analogRead(A0) < 950) {
      enablingBeep();
    }
    else {
      digitalWrite(6, HIGH); // Disable brake read if not ready to drive yet
      errorBeep();
    } 
  }
}



void enablingBeep() {
  analogWrite(9, 127);
  delay(1500);
  analogWrite(9, 0);
}

void errorBeep() {
  analogWrite(9, 127);
  delay(200);
  analogWrite(9, 0);
  delay(200);
  analogWrite(9, 127);
  delay(200);
  analogWrite(9, 0);
}