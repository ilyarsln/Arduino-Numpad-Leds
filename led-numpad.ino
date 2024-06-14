#include <Keypad.h>

// Numpad settings
const byte numRows = 4; // Number of rows
const byte numCols = 4; // Number of columns

char keymap[numRows][numCols] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[numRows] = {2, 3, 4, 5}; // Row pins
byte colPins[numCols] = {6, 7, 8, 9}; // Column pins

Keypad myKeypad = Keypad(makeKeymap(keymap), rowPins, colPins, numRows, numCols);

// LED pins
const int ledPins[] = {10, 11, 12, A0, A1, A2};
const int numLeds = 6;

void setup() {
  // Set LED pins as output
  for (int i = 0; i < numLeds; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
  Serial.begin(9600); // Start serial communication
}

void loop() {
  char key = myKeypad.getKey(); // Read the pressed key

  if (key) { // If a key is pressed
    switch (key) {
      case 'A':
        turnOnAllLeds();
        break;

      case 'B':
        turnOffAllLeds();
        break;

      case 'C':
        handleToggleMode();
        break;

      case 'D':
        handleBlinkMode();
        break;
    }
  }
}

// Function to turn on all LEDs
void turnOnAllLeds() {
  for (int i = 0; i < numLeds; i++) {
    digitalWrite(ledPins[i], HIGH);
  }
}

// Function to turn off all LEDs
void turnOffAllLeds() {
  for (int i = 0; i < numLeds; i++) {
    digitalWrite(ledPins[i], LOW);
  }
}

// Function to handle toggle mode
void handleToggleMode() {
  while (true) {
    char newKey = myKeypad.getKey();
    if (newKey >= '1' && newKey <= '6') {
      int ledIndex = newKey - '1'; // Adjusting index to start from 0
      toggleLed(ledIndex);
    } else if (newKey == '0') {
      break; // Exit the loop
    }
  }
}

// Function to toggle a specific LED
void toggleLed(int index) {
  digitalWrite(ledPins[index], !digitalRead(ledPins[index]));
}

// Function to handle blink mode
void handleBlinkMode() {
  while (true) {
    char loopKey = myKeypad.getKey();
    if (loopKey == 'B') { // Check for 'B' key to exit the loop
      turnOffAllLeds();
      break;
    }
    blinkAllLeds();
  }
}

// Function to blink all LEDs
void blinkAllLeds() {
  for (int i = 0; i < numLeds; i++) {
    digitalWrite(ledPins[i], HIGH);
  }
  delay(200);
  for (int i = 0; i < numLeds; i++) {
    digitalWrite(ledPins[i], LOW);
  }
  delay(200);
}
