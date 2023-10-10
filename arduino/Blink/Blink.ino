const int ledPin = 13;
const int blinkTime = 100; // in miliseconds = 0.001 seconds

void setup() {
  pinMode(ledPin, OUTPUT);
}

void loop() {
  digitalWrite(ledPin, HIGH);   // set the LED on
  delay(blinkTime);             // wait for 'blinkTime'
  digitalWrite(ledPin, LOW);    // set the LED off
  delay(blinkTime);             // wait for 'blinkTime'
}
