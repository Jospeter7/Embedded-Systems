 int relayPin = 8          ; // Pin connected to relay IN
int sensor = 12; // RCWL-0516 OUT pin
int state = LOW; // Track motion state
int val = 0; // Sensor reading
unsigned long lastMotionTime = 0; // To track last motion
const unsigned long holdTime = 10000; // Keep relay ON for 10 seconds after last motion

void setup() {
  pinMode(relayPin, OUTPUT); // Relay as output
  pinMode(sensor, INPUT); // Sensor as input
  digitalWrite(relayPin, LOW); // Initially OFF (assuming active HIGH relay)
  Serial.begin(9600);
}

void loop() {
  val = digitalRead(sensor);

  if (val == HIGH) {
    digitalWrite(relayPin, LOW); // Turn bulb ON
    lastMotionTime = millis(); // Update motion timestamp

    if (state == LOW) {
      Serial.println("Motion detected!");
      state = HIGH;
    }
  } else {
    if (millis() - lastMotionTime > holdTime) {
      digitalWrite(relayPin, HIGH); // Turn bulb OFF after hold time
      if (state == HIGH) {
        Serial.println("Motion stopped!");
        state = LOW;
      }
    }
  }
}
