int relayPin = 8;                   // Pin connected to relay IN
int sensor = 12;                    // RCWL-0516 OUT pin
int state = LOW;                    // Track motion state
int val = 0;                        // Sensor reading
unsigned long lastMotionTime = 0;   // To track last motion
const unsigned long holdTime = 5000; // Keep relay ON for 10 seconds after last motion

int ldrPin = A0;                    // LDR pin
int ldrValue = 0;                   // LDR reading
const int darkThreshold = 100;     // Adjust threshold (0-1023) for darkness

void setup() {
  pinMode(relayPin, OUTPUT);        // Relay as output
  pinMode(sensor, INPUT);           // Sensor as input
  digitalWrite(relayPin, LOW);     // OFF initially (active LOW relay)
  Serial.begin(9600);
}

void loop() {
  val = digitalRead(sensor);
  ldrValue = analogRead(ldrPin);    // Read LDR value

  Serial.print("LDR Value: ");
  Serial.println(ldrValue);

  if (val == HIGH && ldrValue < darkThreshold) {  
    // Motion detected AND it's dark
    digitalWrite(relayPin, LOW);    // Turn bulb ON
    lastMotionTime = millis();      // Update motion timestamp

    if (state == LOW) {
      Serial.println("Motion detected at night!");
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
