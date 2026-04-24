#include <Servo.h>

Servo myServo;

void setup() {
  myServo.attach(9);
}

void loop() {
  myServo.write(0);    // go to 0°
  delay(2000);

  myServo.write(90);   // go to center
  delay(2000);

  myServo.write(180);  // go to 180°
  delay(2000);
}