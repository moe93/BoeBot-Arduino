/* A recreation of Boe-Bot, an autonomous obstacle avoiding robot

   IR receiver: looking at the IR receiver from left to right, data, gnd, vin.
   Using delay(ms) after a continousServo.write() tells the servo the time
   duration for write() to run.
   Created: 31/12/2015
   Modified: 7/1/2016

   SCHEMATIC:
   Left servo motor attaches to PIN 3
   Right servo motor attaches to PIN 2
   Left whisker to PIN 13
   Right whisker to PIN 8
   Any ground wire to chassis.

   ***FULLY FUNCTIONAL VERSION***
    Ver 0.5 - solves issue with whiskers. Apparently chassis of vehicle is not
              ground therefore ground wire was connected to the chassis to
              discharge any current going through the whiskers.
            - further simplifies code

*/
// ------------- Libraries and Global Variables ---------------

#include <Servo.h>

#define REVERSE_DURATION 1000
#define ROTATION_DURATION 681.818 // value is around 45º for MY mechanical setup
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

// ------------------- Main program -------------------
void loop() {

  // --------------- Initiate variables ---------------
  leftWhisker = digitalRead(13);
  rightWhisker = digitalRead(8);

  // ------------------ Drive Forward -----------------
  if ((leftWhisker != 0) && (rightWhisker != 0)) {
    forward();
  }

  // ------------------ Rotate right ------------------
  else if (leftWhisker == 0) {
    turnRight();
  }

  // ------------------ Rotate left -------------------
  else if (rightWhisker == 0) {
    turnLeft();
  }

  // --------------- Rotate left/right ----------------
  else if ((leftWhisker == 0) && (rightWhisker == 0)) {
    leftRight();
  }

}


// ----------------------- FUNCTIONS --------------------
// --------------------- Drive forward ------------------
void forward() {

  // write both servos to move in one direction.
  leftServo.write(LEFT_FORWARD); // 180 is counter clockwise
  rightServo.write(RIGHT_FORWARD); // 0 is clockwise

}

// ---------------------- Rotate right ------------------
void turnRight() {

  // Reverse
  leftServo.write(LEFT_BACKWARD);
  rightServo.write(RIGHT_BACKWARD);
  delay(REVERSE_DURATION);

  // detach servos to completely stop and delay for stability, then reattach
  leftServo.detach();
  rightServo.detach();
  delay(1000);
  leftServo.attach(3);
  rightServo.attach(2);

  // Rotate right
  leftServo.write(LEFT_FORWARD);
  rightServo.write(RIGHT_BACKWARD);
  delay(ROTATION_DURATION);

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
  leftServo.write(LEFT_BACKWARD);
  rightServo.write(RIGHT_BACKWARD);
  delay(REVERSE_DURATION);

  // detach servos to completely stop and delay for stability, then reattach
  leftServo.detach();
  rightServo.detach();
  delay(1000);
  leftServo.attach(3);
  rightServo.attach(2);

  // Rotate left
  leftServo.write(LEFT_BACKWARD);
  rightServo.write(RIGHT_FORWARD);
  delay(ROTATION_DURATION);

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
  leftServo.write(LEFT_BACKWARD);
  rightServo.write(RIGHT_BACKWARD);
  delay(REVERSE_DURATION);

  // detach servos to completely stop and delay for stability, then reattach
  leftServo.detach();
  rightServo.detach();
  delay(1000);
  leftServo.attach(3);
  rightServo.attach(2);

  // Rotate
  leftServo.write(LEFT_BACKWARD);
  rightServo.write(RIGHT_FORWARD);
  delay(ROTATION_DURATION);

  // detach servos to completely stop and delay for stability, then reattach
  leftServo.detach();
  rightServo.detach();
  delay(1000);
  leftServo.attach(3);
  rightServo.attach(2);
}
