// Step1: Basic Analog Read

// int Potentiometer = A1; // Potentiometer is connected to analog pin A1 of Arduino. 
// int PotData = 0; 
 
// void setup()
// {
//   Serial.begin(9600); 
//   pinMode( Potentiometer, INPUT); 
  
// }
 
// void loop()
// {
 
// PotData = analogRead(Potentiometer);
 
// // Serial.print("PoT value: "); 
// Serial.println(PotData); 
// // Serial.println(""); 
// delay(100); 
  
// }



// // Step 2: Implementing Averaging: Arduino Analog Value Averaging: Implementing a Software Filter
/*I have modified the previous program. 
This time, it does not send the potentiometer value directly to the Serial Monitor. 
Instead, it reads the potentiometer value ten times, calculates the average, 
and then sends the final value to the Serial Monitor or Serial Plotter.
Let’s upload this program and see if it’s going to make any difference.
Alpha is a Filter coefficient between 0 and 1. It controls how much of the
 new sensor reading (PotData) will be included in the filtered value.

PotData: This is the raw sensor reading from the potentiometer.

filteredValue: This is the smoothed value that we get after applying the filter.

In this equation:

“alpha * PotData” This part of the equation takes the new sensor reading and multiplies it by alpha. 
If alpha is 0.1, it means that 10% of the new reading is used in the final filtered value. You can try different values from 0.1 to 0.9.
“(1 – alpha) * filteredValue” This part takes the previous filtered value and multiplies it by (1 – alpha).
 If alpha is 0.1, then (1 – alpha) is 0.9. This means that 90% of the previous filtered value is kept in the new filtered value.

By combining these two parts, the filter smooths out the fluctuations in the sensor readings.
The result is a filteredValue that changes more slowly and is less noisy compared to the raw PotData.*/


// int  Potentiometer = A1; // Potentiometer is connected to analog pin A1 of Arduino.
// int PotData = 0;
// const int numReadings = 10; // Number of readings for averaging
// int readings[numReadings];  // Array to hold the sensor readings
// int readIndex = 0;          // Index of the current reading
// int total = 0;              // Running total of the sensor readings
// int average = 0;            // Average of the sensor readings
 
// void setup() {
//   Serial.begin(9600);
//   pinMode(Potentiometer, INPUT);
  
//   // Initialize all the readings to 0
//   for (int i = 0; i < numReadings; i++) {
//     readings[i] = 0;
//   }
// }
 
// void loop() {
//   // Subtract the last reading
//   total = total - readings[readIndex];
  
//   // Read the sensor
//   readings[readIndex] = analogRead(Potentiometer);
  
//   // Add the reading to the total
//   total = total + readings[readIndex];
  
//   // Advance to the next position in the array
//   readIndex = readIndex + 1;
  
//   // If we're at the end of the array, wrap around to the beginning
//   if (readIndex >= numReadings) {
//     readIndex = 0;
//   }
  
//   // Calculate the average
//   average = total / numReadings;
  
//   // Print the average value
//   // Serial.print("Average PoT value: ");
//   Serial.println(average);
//   // Serial.println("");
  
//   // Add a delay if needed
//   delay(100);
// }



// // // 3. Software & Hardware (4.7/10uF cap low-pass filter) Filtering with a Capacitor
// int Potentiometer = A1; // Potentiometer is connected analog pin A1 of arduino.  
// int PotData = 0; 
 
// int filteredValue = 0;  // Initialize filtered value
// float alpha = 0.1;  // Filter coefficient (0 < alpha < 1)
 
// void setup()
// {
//   Serial.begin(9600); 
//   pinMode(Potentiometer, INPUT); 
  
// }
 
// void loop()
// {
 
//  PotData = analogRead(Potentiometer);
//  filteredValue = alpha * PotData + (1 - alpha) * filteredValue;  // Filter equation
 
// //vout = (filteredValue * 5.0) / 1023.0; 
// //vout = vout * cf ; 
// // Serial.print("Filtered Pot Value: "); 
// Serial.println(filteredValue); 
// // Serial.println(""); 
// delay(100); 
  
// }


