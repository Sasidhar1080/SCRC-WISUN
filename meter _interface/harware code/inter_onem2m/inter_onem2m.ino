#include <WiFi.h>
#include <HTTPClient.h>


const char* ssid = "SCRC_LAB_IOT";
const char* password = "Scrciiith@123";

// const int interruptPin = 17; // ESP32 pin connected to the interrupt
#define interruptPin D3            // Led in NodeMCU at pin GPIO16 (D3).

volatile int count = 0; // volatile because it's modified in an ISR
volatile bool countIncreased = false;

WiFiClient client;
HTTPClient http;
  
#define CSE_IP      "dev-onem2m.iiit.ac.in"
#define OM2M_ORGIN    "Tue_20_12_22:Tue_20_12_22"
#define CSE_PORT    443
#define HTTPS     false 
#define OM2M_MN     "/~/in-cse/in-name/"
#define OM2M_AE     "AE-DT"
#define OM2M_NODE_ID   "DT-WM-Node-1"
#define OM2M_DATA_CONT  "WM-Node-1/Data"

// #define OM2M_NODE_ID   "DT-WM-Node-2"
// #define OM2M_DATA_CONT  "WM-Node-2/Data"

#define POST_INTERVAL 60000 // Interval for posting data (1 minute = 60000 milliseconds)

unsigned long lastPostTime = 0; // Variable to store the time of the last post

void IRAM_ATTR handleInterrupt() {
  count++; // increment count when the interrupt occurs
  countIncreased = true; // set the flag to indicate count increase
}

void connectToWiFi() {
  Serial.println("Connecting to WiFi");

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

void post_onem2m() {
  String data =  String(count) ;
 
  String server = (HTTPS ? "https://" : "http://") + String(CSE_IP) + ":" + String(CSE_PORT) + String(OM2M_MN);

  http.begin(client, server + OM2M_AE + "/" + OM2M_DATA_CONT);
  http.addHeader("X-M2M-Origin", OM2M_ORGIN);
  http.addHeader("Content-Type", "application/json;ty=4");
  
  String req_data = String() + "{\"m2m:cin\": {"
                    + "\"con\": \"" + data + "\","
                    + "\"rn\": \"" + "cin_" + String(millis()) + "\","
                    + "\"cnf\": \"text\""
                    + "}}";

  Serial.println("Server URL: " + server);
  Serial.println("Request Data: " + req_data);

  int code = http.POST(req_data);
  Serial.println("HTTP Response Code: " + String(code));
  http.end();
}

void setup() {
  Serial.begin(9600);

  pinMode(interruptPin, INPUT_PULLUP); // configure the interrupt pin as input with pull-up resistor
  attachInterrupt(digitalPinToInterrupt(interruptPin), handleInterrupt, FALLING);

  // Connect to Wi-Fi
  connectToWiFi();
}

void loop() {
  // Your main loop code goes here
  // You can add other non-blocking tasks here if needed
  // Note: Avoid using delay() in the loop, as it can affect interrupt responsiveness

  unsigned long currentTime = millis();

  // Check if it's time to post data
  if (currentTime - lastPostTime >= POST_INTERVAL) {
    // Update the last post time
    lastPostTime = currentTime;

    // Call the post_onem2m() function
    post_onem2m();
  }

  // Print count only when it has increased
  if (countIncreased) {
    Serial.print("Count: ");
    Serial.println(count);
    countIncreased = false; // reset the flag
  }
  // Add any other non-blocking tasks or logic here
}
