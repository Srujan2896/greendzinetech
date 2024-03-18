#define analogPin 1 // Define analog pin for LM35 sensor (A0)
#define ledPin 13   // Define pin for onboard LED (D13)

volatile unsigned long previousBlink = 0; // Flag for previous blink state
const unsigned int blinkIntervalLow = 250;  // Blink interval for low temperature (milliseconds)
const unsigned int blinkIntervalHigh = 500; // Blink interval for high temperature (milliseconds)
volatile unsigned long loopCount = 0;        // Declare a variable to store loop counter

void setup() {
  pinMode(ledPin, OUTPUT);  // Set LED pin as output
  pinMode(analogPin, INPUT); // Set analog pin as input
  Serial.begin(9600);       // Enable serial communication at 9600 baud
}

void loop() {
  unsigned long currentLoop = loopCount; // Use loop counter for timing

  // Calculate voltage based on LM35 output (10mV/°C)
  float voltage = analogRead(analogPin) * 5.0 / 1023.0;

  // Calculate temperature (in °C)
  float temperature = voltage / 0.01;

  // Check temperature and blinking interval
  if (temperature < 30) {
    // Low temperature - blink faster
    if (currentLoop - previousBlink >= 250) {
      digitalWrite(ledPin, !digitalRead(ledPin)); // Toggle LED state
      previousBlink = currentLoop;
    }
  } else {
    // High temperature - blink slower
    if (currentLoop - previousBlink >= blinkIntervalHigh) {
      digitalWrite(ledPin, !digitalRead(ledPin)); // Toggle LED state
      previousBlink = currentLoop;
    }
  }

  // Increment loop counter
  loopCount++;
}
