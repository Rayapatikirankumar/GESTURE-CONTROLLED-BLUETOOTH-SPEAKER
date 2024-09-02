#include <SoftwareSerial.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>

#define BT_SERIAL_RX 10
#define BT_SERIAL_TX 11

SoftwareSerial bluetoothSerial(BT_SERIAL_RX, BT_SERIAL_TX);
Adafruit_ADXL345_Unified accel;

void setup() {
  Serial.begin(9600);
  bluetoothSerial.begin(9600);

  if (!accel.begin()) {
    Serial.println("Could not find a valid ADXL345 sensor, check wiring!");
    while (1);
  }

  accel.setRange(ADXL345_RANGE_16_G);
}

void loop() {
  sensors_event_t event;
  accel.getEvent(&event);

  int x = event.acceleration.x;
  int y = event.acceleration.y;
  int z = event.acceleration.z;

  // Check for specific gestures
  if (x < -9) {
    bluetoothSerial.write('L'); // Left gesture
  } else if (x > 9) {
    bluetoothSerial.write('R'); // Right gesture
  } else if (y < -9) {
    bluetoothSerial.write('U'); // Up gesture
  } else if (y > 9) {
    bluetoothSerial.write('D'); // Down gesture
  } else if (z < -9) {
    bluetoothSerial.write('S'); // Shake gesture
  }

  delay(100);
}
