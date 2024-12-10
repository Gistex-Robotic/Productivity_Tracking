// Define pins
const int buttonPin = 2;

// Variables for tracking times
unsigned long nonEfficientTime = 0;
unsigned long efficientTime = 0;
unsigned long previousMillis = 0;
bool lastButtonState = HIGH; // Last known state of the button (HIGH = not pressed)

void setup() {
  pinMode(buttonPin, INPUT_PULLUP); // Use internal pull-up resistor
  Serial.begin(115200);              // Start Serial Monitor
}

void loop() {
  unsigned long currentMillis = millis();

  // Read the current button state (LOW when pressed, HIGH when not pressed)
  bool currentButtonState = digitalRead(buttonPin);

  // If the button is released (transition from LOW to HIGH), reset the timers
  if (lastButtonState == LOW && currentButtonState == HIGH) {
    
    nonEfficientTime = 0;
    efficientTime = 0;
    Serial.println("Times reset!");
  }

  // Update the time calculations
  if (currentButtonState == LOW) {
    // Button pressed, calculate efficiency time
    efficientTime += currentMillis - previousMillis;
  } else {
    // Button not pressed, calculate non-efficiency time
    nonEfficientTime += currentMillis - previousMillis;
  }

  previousMillis = currentMillis; // Update time tracking
  lastButtonState = currentButtonState; // Update the last button state

  // Check periodically (every second) to print the results
  static unsigned long lastPrintTime = 0;
  if (currentMillis - lastPrintTime >= 1000) {
    lastPrintTime = currentMillis;
    Serial.print("Machine run Time: ");
    Serial.print(efficientTime / 1000); // Convert to seconds
    Serial.print("s | Machine off Time: ");
    Serial.print(nonEfficientTime / 1000); // Convert to seconds
    Serial.println("s");
  }
}
