// Water Meter repetition counter

int pulse1 = 2;
int counter1 = 0;
long lastDebounce1 = 0;
long debounceDelay = 500;	// Ignore bounces under 1/2 second, need to calibrate with water meter

void setup() {
  Serial.begin(9600);
  pinMode(pulse1, INPUT_PULLUP); //Pullup internal resister
  digitalWrite(pulse1, HIGH);
  attachInterrupt(0, trigger1, FALLING);
  Serial.println("Water Pulse");
  //Serial.print("\t");
}

void loop() {
  // Count and total pulses
}

void trigger1() {
  if ( (millis() - lastDebounce1) > debounceDelay) {
    counter1++;
    Serial.print(counter1);
    Serial.print(" ");
    lastDebounce1 = millis();
  }
}