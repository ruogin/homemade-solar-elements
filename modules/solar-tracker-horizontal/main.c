// Author: ruogin
// Date: 11.05.2017

// System part: solar treker.
// Controller: (?) attiny13a
// Compiler: avr studio (v 1.8+)

#include "Servo.h"

// Photoresotors, Servo, RX/TX channel (serial)
#define PIN_LEFT 5
#define PIN_RIGHT 4
#define PIN_SERVO 3
#define PIN_RX 2
#define PIN_TX 1

#define CMD_GET_SERVO_MIN 0x0A
#define CMD_GET_SERVO_MAX 0x0B
#define CMD_SET_LOG       0x10

// Will be redifined on check
int servo_min=0;
int servo_max=180;
int deadband = 10;

int r_left = 0;
int r_right = 0;

int servoRotate = 0;
int diff = 0;

SoftwareSerial sserial_cmd(rxPin, txPin);
Servo servoMotor;

void check_min_max() {
  hServo.write(servo_min);
  delay(10000); // long start
  hServo.write(servo_max);
  delay(10000); // long start
  hServo.write(output);
  delay(5000); // long start
}

void setup() {
  sserial_cmd.begin(9600);
  servoMotor.attach(PIN_SERVO);
 
}

void loop() {
  r_left = analogRead(PIN_LEFT);
  r_right = analogRead(PIN_RIGHT);
  
  diff = r_left - r_right;
  
  if (diff < (- deadband)) {
    servoRotate = 1;
  } else {
  if (diff > deadband) {
    servoRotate = -1;
  } else {
    servoRotate = 0;
  }
  servoMotor.write(servoRotate);
}
