#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <TinyGPS++.h>
#include <math.h>

Adafruit_MPU6050 mpu;
TinyGPSPlus gps;

// ESP32 pin configuration
#define LED_PIN 25
#define BUZZER_PIN 26
#define BUTTON_PIN 27
#define GPS_RX 16
#define GPS_TX 17

// Accident detection threshold
float accidentThreshold = 20.0;

void readGPS() {
  while (Serial2.available() > 0) {
    gps.encode(Serial2.read());
  }
}

void showGPSLocation() {
  Serial.println();
  Serial.println("GPS LOCATION");

  if (gps.location.isValid()) {
    double latitude = gps.location.lat();
    double longitude = gps.location.lng();

    Serial.print("Latitude: ");
    Serial.println(latitude, 6);

    Serial.print("Longitude: ");
    Serial.println(longitude, 6);

    Serial.println("Google Maps Location:");
    Serial.print("https://maps.google.com/?q=");
    Serial.print(latitude, 6);
    Serial.print(",");
    Serial.println(longitude, 6);
  } else {
    Serial.println("GPS location not available.");
  }
}

// Simulated GSM emergency message
void sendEmergencySMS() {
  Serial.println();
  Serial.println("================================");
  Serial.println("          GSM MODULE");
  Serial.println("================================");

  Serial.println("Connecting to GSM network...");
  delay(1000);
  Serial.println("Network registered.");

  Serial.println("Preparing emergency SMS...");
  delay(1000);
  Serial.println("Sending SMS...");
  delay(1000);

  Serial.println();
  Serial.println("--------------------------------");
  Serial.println("       EMERGENCY SMS SENT");
  Serial.println("--------------------------------");

  Serial.println("Vehicle ID: SV-001");
  Serial.println("ACCIDENT DETECTED!");

  if (gps.location.isValid()) {
    double latitude = gps.location.lat();
    double longitude = gps.location.lng();

    Serial.print("Latitude : ");
    Serial.println(latitude, 6);

    Serial.print("Longitude: ");
    Serial.println(longitude, 6);

    Serial.println("Google Maps Location:");
    Serial.print("https://maps.google.com/?q=");
    Serial.print(latitude, 6);
    Serial.print(",");
    Serial.println(longitude, 6);
  } else {
    Serial.println("Location unavailable.");
  }

  Serial.println("Please send immediate assistance.");
  Serial.println("--------------------------------");
  Serial.println("Emergency contact notified.");
  Serial.println("================================");
}

void setup() {
  Serial.begin(115200);

  Serial2.begin(9600, SERIAL_8N1, GPS_RX, GPS_TX);

  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  digitalWrite(LED_PIN, LOW);
  digitalWrite(BUZZER_PIN, LOW);

  Serial.println("================================");
  Serial.println(" SMART ACCIDENT DETECTION SYSTEM");
  Serial.println("================================");

  Serial.println("Starting MPU6050...");

  if (!mpu.begin()) {
    Serial.println("MPU6050 not found!");
    while (1) {
      delay(10);
    }
  }

  Serial.println("MPU6050 found!");
  Serial.println("GPS initialized!");
  Serial.println("System is ready.");
  Serial.println("Monitoring vehicle...");
}

void loop() {
  readGPS();

  sensors_event_t acceleration, gyro, temperature;
  mpu.getEvent(&acceleration, &gyro, &temperature);

  float x = acceleration.acceleration.x;
  float y = acceleration.acceleration.y;
  float z = acceleration.acceleration.z;

  float totalAcceleration = sqrt(x*x + y*y + z*z);

  Serial.print("Total Acceleration: ");
  Serial.print(totalAcceleration);
  Serial.println(" m/s^2");

  if (totalAcceleration > accidentThreshold) {
    Serial.println("POSSIBLE ACCIDENT DETECTED!");

    digitalWrite(LED_PIN, HIGH);
    digitalWrite(BUZZER_PIN, HIGH);

    bool alertCancelled = false;

    Serial.println("You have 10 seconds to cancel the alert.");

    for (int i = 10; i > 0; i--) {
      Serial.print("Time remaining: ");
      Serial.print(i);
      Serial.println(" seconds");

      readGPS();

      if (digitalRead(BUTTON_PIN) == LOW) {
        alertCancelled = true;
        break;
      }

      delay(1000);
    }

    if (alertCancelled) {
      Serial.println("ALERT CANCELLED");
      Serial.println("False accident assumed.");

      digitalWrite(LED_PIN, LOW);
      digitalWrite(BUZZER_PIN, LOW);
    } else {
      Serial.println("NO CANCELLATION RECEIVED");
      Serial.println("Accident alert confirmed.");

      digitalWrite(LED_PIN, LOW);
      digitalWrite(BUZZER_PIN, LOW);

      Serial.println("Getting GPS location...");

      unsigned long startTime = millis();

      while (millis() - startTime < 2000) {
        readGPS();
      }

      showGPSLocation();
      sendEmergencySMS();
    }

    Serial.println("Returning to monitoring...");
    delay(2000);

  } else {
    Serial.println("Vehicle movement is normal.");
  }

  delay(500);
}
