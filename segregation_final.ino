#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// === Constants ===
const int trigPin = 12;
const int echoPin = 11;   // waste detection
const int echoPin2 = 7;   // bin level sensor 1
const int echoPin3 = 5;   // bin level sensor 2

const int potPin = A0;

const int Ultra_Distance = 20;       // cm
const int binFullThreshold = 9;      // cm

const int dryServoAngle = 10;
const int wetServoAngle = 170;
const int servoResetAngle = 115;

const int maxDryValue = 5;           // moisture <5% = dry

// === Objects ===
Servo servo1;
LiquidCrystal_I2C lcd(0x27, 16, 2);

// === Functions ===

// Read ultrasonic sensor with multiple samples & average
long readUltrasonicAvg(int echoPin, int samples=3) {
  long sum = 0;
  int valid = 0;
  for (int i=0; i<samples; i++) {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    long duration = pulseIn(echoPin, HIGH, 20000); // 20 ms timeout
    long dist = duration * 0.034 / 2;

    // Filter invalid
    if (dist > 1 && dist < 400) {
      sum += dist;
      valid++;
    }
    delay(10);
  }
  if (valid > 0) return sum / valid;
  else return 400;  // fallback: no reading
}

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(echoPin2, INPUT);
  pinMode(echoPin3, INPUT);

  servo1.attach(8);
  servo1.write(servoResetAngle); // initial position

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print(" Smart Dustbin ");
  delay(2000);
}

void loop() {
  // Read distances
  long distance = readUltrasonicAvg(echoPin);
  long binLevel1 = readUltrasonicAvg(echoPin2);
  long binLevel2 = readUltrasonicAvg(echoPin3);

  // Check bin full
  bool isBinFull = (binLevel1 < binFullThreshold || binLevel2 < binFullThreshold);
  if (isBinFull) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("** Bin Full! **");
    lcd.setCursor(0, 1);
    lcd.print("Please Empty Bin");
    while (1); // stop program here
  }

  // Waste detection
  if (distance < Ultra_Distance && distance > 1) {
    delay(500); // debounce

    // Read soil moisture average
    int fsoil = 0;
    for (int i = 0; i < 3; i++) {
      int soil = analogRead(potPin);
      soil = constrain(soil, 485, 1023);
      fsoil += map(soil, 485, 1023, 100, 0);
      delay(50);
    }
    fsoil /= 3;

    Serial.print("Moisture: "); Serial.print(fsoil);
    Serial.print("% Dist: "); Serial.print(distance);
    Serial.print("cm Bin1: "); Serial.print(binLevel1);
    Serial.print("cm Bin2: "); Serial.println(binLevel2);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("M:");
    lcd.print(fsoil);
    lcd.print("% D:");
    lcd.print(distance);

    lcd.setCursor(0, 1);
    if (fsoil < maxDryValue) {
      lcd.print("Dry Waste");
      servo1.write(dryServoAngle);
    } else {
      lcd.print("Wet Waste");
      servo1.write(wetServoAngle);
    }
    delay(2000);
    servo1.write(servoResetAngle); // reset
    delay(5000);
  } else {
    // No waste: show bin levels
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Bin1:");
    lcd.print(binLevel1);
    lcd.print("cm B2:");
    lcd.print(binLevel2);
    lcd.setCursor(0, 1);
    lcd.print("Status: OK");
    delay(1000);
  }

  delay(300); // small delay
}
