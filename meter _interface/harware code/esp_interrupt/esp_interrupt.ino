// const int interruptPin = D3; // ESP32 pin connected to the interrupt
#define interruptPin D3            // Led in NodeMCU at pin GPIO16 (D3).

volatile int count = 0; // volatile because it's modified in an ISR
volatile bool countIncreased = false;

void IRAM_ATTR handleInterrupt() {
  count++; // increment count when the interrupt occurs
  countIncreased = true; // set the flag to indicate count increase
}

void setup() {
  Serial.begin(9600);

  pinMode(interruptPin, INPUT_PULLUP); // configure the interrupt pin as input with pull-up resistor

  attachInterrupt(digitalPinToInterrupt(interruptPin), handleInterrupt, FALLING);
}

void loop() {
  // Your main loop code goes here
  // You can add other non-blocking tasks here if needed
  // Note: Avoid using delay() in the loop, as it can affect interrupt responsiveness

  // Print count only when it has increased
  if (countIncreased) {
    Serial.print("Count: ");
    Serial.println(count);
    countIncreased = false; // reset the flag
  }

  // Add any other non-blocking tasks or logic here
}
