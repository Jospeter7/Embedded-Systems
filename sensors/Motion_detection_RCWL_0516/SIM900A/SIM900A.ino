#include <SoftwareSerial.h>

// SIM900 connections
SoftwareSerial mySerial(6, 7);  // SIM900 Tx -> 7, Rx -> 8

int relayPin = 8;                     
int sensor = 12;                      
int state = LOW;                      
unsigned long lastMotionTime = 0;    
const unsigned long holdTime = 10000;

int ldrPin = A0;                     
int ldrValue = 0;                     
const int darkThreshold = 500;       

bool smsSent = false;                 

void setup() {
  pinMode(relayPin, OUTPUT);
  pinMode(sensor, INPUT);
  digitalWrite(relayPin, HIGH);       

  Serial.begin(9600);
  mySerial.begin(9600);

  Serial.println("Initializing SIM900...");
  delay(1000);

  mySerial.println("AT");           
  updateSerial();
  mySerial.println("AT+CMGF=1");      
  updateSerial();

  Serial.println("System ready...");
}

void loop() {
  int motion = digitalRead(sensor);
  ldrValue = analogRead(ldrPin);

  // Serial.print("LDR Value: ");
  // Serial.println(ldrValue);

  if (motion == HIGH && ldrValue < darkThreshold) {
    digitalWrite(relayPin, LOW);      
    lastMotionTime = millis();

    if (state == LOW) {
      Serial.println("Motion detected at night!");
      state = HIGH;

      if (!smsSent) {
        sendSMS("+255687688927", "Motion detected at night! Bulb ON.");
        smsSent = true;  
      }
    }
  } else {
    if (millis() - lastMotionTime > holdTime) {
      digitalWrite(relayPin, HIGH);    
      if (state == HIGH) {
        Serial.println("Motion stopped!");
        state = LOW;
        smsSent = false; 
      }
    }
  }
}

void sendSMS(String phoneNumber, String message) {
  Serial.println("Sending SMS...");
  // mySerial.println("AT+CMGS=\"" +  + "\"");
  mySerial.println("AT+CMGS=\"+255687688927\"");
  updateSerial();
  mySerial.print(message);
  updateSerial();
  mySerial.write(26);  // CTRL+Z to send
  delay(5000);
  Serial.println("SMS sent successfully.");
}

void updateSerial() {
  delay(500);
  while (Serial.available()) {
    mySerial.write(Serial.read());
  }
  while (mySerial.available()) {
    Serial.write(mySerial.read());
  }
}
