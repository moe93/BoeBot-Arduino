/* A recreation of Boe-Bot, an autonomous obstacle avoiding robot
   IR receiver: looking at the IR receiver from left to right, data, gnd, vin.
   Created: 31/12/2015
   Modified: 5/1/2016

   SCHEMATIC:
   Left servo motor attaches to PIN 3
   Right servo motor attaches to PIN 2
   Left whisker to PIN 13
   Right whisker to PIN 8

   ***FIRST FUNCTIONAL VERSION (to some degree)***
    Ver 0.4 clears and simplifies code into various functions.
          - Known issues: whiskers unresponsive at times.
*/
// ------------- Libraries and Global Variables ---------------

#include <Servo.h>

#define REVERSE_DURATION 1000
#define ROTATION_DURATION 500
const int LEFT_FORWARD = 120;
const int RIGHT_FORWARD = 60;
const int LEFT_BACKWARD = 60;
const int RIGHT_BACKWARD = 120;
const int LEFT_NEUTRAL = 90;
const int RIGHT_NEUTRAL = 90;
Servo leftServo;
Servo rightServo;
int leftWhisker, rightWhisker;
unsigned long previousTime;

// ---------------------- Setup ------------------------
void setup() {
  // attach both continous servos to their pins on arduino
  leftServo.attach(3);
  rightServo.attach(2);

  // Set both servos to start at rest
  leftServo.write(90);
  rightServo.write(90);

}


// ------------------------- Main program ------------------------
void loop() {

  // --------------- Initiate variables ----------------
  leftWhisker = digitalRead(13);
  rightWhisker = digitalRead(8);

  // ------------------ Drive Forward ------------------
  if ((leftWhisker != 0) && (rightWhisker != 0)) {

    forward();

  }

  // ------------------- rotate right --------------------
  else if (leftWhisker == 0) {

    turnRight();

  }

  // --------------------- Rotate left ------------------
  else if (rightWhisker == 0) {

    turnLeft();

  }

  // --------------- Rotate left/right ----------------
  else if ((leftWhisker == 0) && (rightWhisker == 0)) {

    leftRight();

  }

}


// -----------------------FUNCTIONS ---------------------
// --------------------- Drive forward ------------------
void forward() {

  // write both servos to move in one direction.
  leftServo.write(LEFT_FORWARD); // 180 is counter clockwise
  rightServo.write(RIGHT_FORWARD); // 0 is clockwise

}

// ---------------------- Rotate right --------------------
void turnRight() {

  // Reverse
  previousTime = millis();
  while (millis() - previousTime < REVERSE_DURATION) {
    leftServo.write(LEFT_BACKWARD);
    rightServo.write(RIGHT_BACKWARD);
  }

  // detach servos to completely stop and delay for stability, then reattach
  leftServo.detach();
  rightServo.detach();
  delay(1000);
  leftServo.attach(3);
  rightServo.attach(2);

  // Rotate right
  previousTime = millis();
  while (millis() - previousTime < ROTATION_DURATION) {
    leftServo.write(LEFT_FORWARD);
    rightServo.write(RIGHT_BACKWARD);
  }

  // detach servos to completely stop and delay for stability, then reattach
  leftServo.detach();
  rightServo.detach();
  delay(1000);
  leftServo.attach(3);
  rightServo.attach(2);
}

// ---------------------- Rotate left -------------------
void turnLeft() {

  // Reverse
  previousTime = millis();
  while (millis() - previousTime < REVERSE_DURATION) {
    leftServo.write(LEFT_BACKWARD);
    rightServo.write(RIGHT_BACKWARD);
  }

  // detach servos to completely stop and delay for stability, then reattach
  leftServo.detach();
  rightServo.detach();
  delay(1000);
  leftServo.attach(3);
  rightServo.attach(2);

  // Rotate left
  previousTime = millis();
  while (millis() - previousTime < ROTATION_DURATION) {
    leftServo.write(LEFT_BACKWARD);
    rightServo.write(RIGHT_FORWARD);
  }

  // detach servos to completely stop and delay for stability, then reattach
  leftServo.detach();
  rightServo.detach();
  delay(1000);
  leftServo.attach(3);
  rightServo.attach(2);
}

// ----------------- Rotate left/right -----------------
void leftRight() {

  // Reverse
  previousTime = millis();
  while (millis() - previousTime < REVERSE_DURATION + 1000) {
    leftServo.write(LEFT_BACKWARD);
    rightServo.write(RIGHT_BACKWARD);
  }

  // detach servos to completely stop and delay for stability, then reattach
  leftServo.detach();
  rightServo.detach();
  delay(1000);
  leftServo.attach(3);
  rightServo.attach(2);

  // Rotate
  while (millis() - previousTime < ROTATION_DURATION + 250) {
    leftServo.write(LEFT_BACKWARD);
    rightServo.write(RIGHT_FORWARD);
  }

  // detach servos to completely stop and delay for stability, then reattach
  leftServo.detach();
  rightServo.detach();
  delay(1000);
  leftServo.attach(3);
  rightServo.attach(2);
}
