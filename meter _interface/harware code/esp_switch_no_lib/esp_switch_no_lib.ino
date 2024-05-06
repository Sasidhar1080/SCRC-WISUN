const int buttonPin = 17; // ESP32 pin connected to the button
int buttonState = HIGH;   // current state of the button
int lastButtonState = HIGH; // previous state of the button
unsigned long lastDebounceTime = 0;  // last time the button state was changed
unsigned long debounceDelay = 50;    // debounce time; increase if the output flickers

int count = 0; // initialize count variable

void setup() {
  Serial.begin(9600);
  pinMode(buttonPin, INPUT_PULLUP); // configure the button pin as input with pull-up resistor
}

void loop() {
  int reading = digitalRead(buttonPin); // read the state of the button

  if (reading != lastButtonState) {
    lastDebounceTime = millis(); // update the debounce time
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;

      if (buttonState == LOW) {
        Serial.print("Count: ");
        Serial.println(++count); // increment and print the count variable
        delay(200); // optional delay to avoid rapid counting due to button debounce
      }
    }
  }

  lastButtonState = reading;
}
