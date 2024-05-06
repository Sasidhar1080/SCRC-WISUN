#include <ezButton.h>

ezButton mySwitch(17);  // create ezButton object that attaches to ESP32 pin GPIO17
int count = 0; // initialize count variable

void setup() {
  Serial.begin(9600);
  mySwitch.setDebounceTime(50); // set debounce time to 50 milliseconds
}

void loop() {
  mySwitch.loop(); // MUST call the loop() function first

  if (mySwitch.isPressed()) {
    Serial.print("Count: ");
    Serial.println(++count); // increment and print the count variable
    delay(200); // optional delay to avoid rapid counting due to button debounce
  }
}
