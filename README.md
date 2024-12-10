# Button-Based Efficiency Timer

This project is an Arduino-based program to monitor and calculate the active (efficient) and idle (non-efficient) times of a machine using a button as input. It is simple to implement and can be adapted for various efficiency-tracking purposes.

## Features
- **Real-Time Tracking**: Continuously tracks the machine's run and idle times.
- **Reset Functionality**: Automatically resets the time counters when the button state transitions from pressed to released.
- **Periodic Output**: Displays the efficiency and non-efficiency times in seconds on the Serial Monitor every second.

## Hardware Requirements
- An Arduino board (e.g., Uno, Nano, etc.)
- A button (configured with an internal pull-up resistor or an external resistor)
- USB cable to connect the Arduino to a computer

## Circuit Diagram
1. Connect the button to pin `2` and ground.
2. Ensure the button is configured to use an internal pull-up resistor, as specified in the code.

## Software Requirements
- [Arduino IDE](https://www.arduino.cc/en/software) for uploading the sketch to the board.

## How to Use
1. Upload the provided code to your Arduino board.
2. Open the Serial Monitor (set the baud rate to `115200`).
3. Press and release the button to simulate machine operation:
   - **Pressed (LOW)**: Simulates the machine running.
   - **Released (HIGH)**: Simulates the machine being idle.
4. View real-time efficiency data on the Serial Monitor:
   - **Machine Run Time**: Time the button is pressed (machine active).
   - **Machine Off Time**: Time the button is released (machine idle).
5. Reset the counters by transitioning the button state from pressed to released.

## Code
```cpp
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
