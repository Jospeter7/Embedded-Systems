#include <Adafruit_AS7341.h>

Adafruit_AS7341 as7341;

void setup() {
  Serial.begin(115200);
  while (!Serial) delay(1);

  if (!as7341.begin()) {
    Serial.println("AS7341 not detected. Check wiring.");
    while (1) delay(10);
  }

  // Sensor setup
  as7341.setATIME(100);
  as7341.setASTEP(999);
  as7341.setGain(AS7341_GAIN_256X);

  // LED setup for consistent illumination
  as7341.setLEDCurrent(4);  // 100 mA for maximum brightness
  as7341.enableLED(true);     // Continuous illumination
}

void loop() {
  if (!as7341.readAllChannels()) {
    Serial.println("Sensor read error!");
    return;
  }

  // Read raw spectral data
  uint16_t ch_415 = as7341.getChannel(AS7341_CHANNEL_415nm_F1);
  uint16_t ch_445 = as7341.getChannel(AS7341_CHANNEL_445nm_F2);
  uint16_t ch_480 = as7341.getChannel(AS7341_CHANNEL_480nm_F3);
  uint16_t ch_515 = as7341.getChannel(AS7341_CHANNEL_515nm_F4);
  uint16_t ch_555 = as7341.getChannel(AS7341_CHANNEL_555nm_F5);  // Green peak
  uint16_t ch_590 = as7341.getChannel(AS7341_CHANNEL_590nm_F6);
  uint16_t ch_630 = as7341.getChannel(AS7341_CHANNEL_630nm_F7);  // Red
  uint16_t ch_680 = as7341.getChannel(AS7341_CHANNEL_680nm_F8);  // Deep Red
  uint16_t clear  = as7341.getChannel(AS7341_CHANNEL_CLEAR);
  uint16_t nir    = as7341.getChannel(AS7341_CHANNEL_NIR);

  // Calculate indices (NDI, SR, etc.)
  float red = (float)ch_630;
  float green = (float)ch_555;
  float deepRed = (float)ch_680;

  // Normalized Difference Index (NDI)
  float ndi = (red - green) / (red + green + 1e-5);

  // Simple Ratio (SR)
  float sr = red / (green + 1e-5);

  // Deep Red to Red Ratio
  float dr_r_ratio = deepRed / (red + 1e-5);

  // Structured data output
  Serial.println("=== CROP QUALITY DATA ===");
  Serial.print("F1 415nm: "); Serial.println(ch_415);
  Serial.print("F2 445nm: "); Serial.println(ch_445);
  Serial.print("F3 480nm: "); Serial.println(ch_480);
  Serial.print("F4 515nm: "); Serial.println(ch_515);
  Serial.print("F5 555nm (Green): "); Serial.println(ch_555);
  Serial.print("F6 590nm: "); Serial.println(ch_590);
  Serial.print("F7 630nm (Red): "); Serial.println(ch_630);
  Serial.print("F8 680nm (Deep Red): "); Serial.println(ch_680);
  Serial.print("Clear: "); Serial.println(clear);
  Serial.print("NIR: "); Serial.println(nir);

  // Output indices
  Serial.print("NDI (Red-Green): "); Serial.println(ndi, 4);
  Serial.print("Simple Ratio (Red/Green): "); Serial.println(sr, 4);
  Serial.print("Deep Red/Red Ratio: "); Serial.println(dr_r_ratio, 4);

  Serial.println("------------------------------");

  delay(1000); // One reading per second
}
