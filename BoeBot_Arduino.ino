/* A recreation of Boe-Bot, an autonomous obstacle avoiding robot
   IR receiver: looking at the IR receiver from left to right, data, gnd, vin.
   Created: 31/12/2015
   Modified: 1/1/2016

   ***FIRST FUNCTIONAL VERSION (to some degree)***
*/
// ------------- Libraries and Global Variables ---------------

#include <Servo.h>

Servo leftServo;
Servo rightServo;
int leftWhisker, rightWhisker;
const long reverseDuration = 500;
const long rotationDuration = 250;
unsigned long previousTime;


// ---------------------- Setup ------------------------
void setup() {

  //  Serial.begin(9600);     //UNCOMMENT TO DEBUG
  leftServo.attach(2);
  rightServo.attach(3);

  // Set both servos to start at rest
  leftServo.write(90);
  rightServo.write(90);
}


// ------------------------- Main program ------------------------
void loop() {

  leftWhisker = digitalRead(9);
  rightWhisker = digitalRead(8);
  //Serial.print(leftWhisker);      //UNCOMMENT TO DEBUG

  // ------------------ Drive Forward ------------------
  if ((leftWhisker != 0) && (rightWhisker != 0)) {

    // write both servos to move in one direction.
    leftServo.write(180); // 180 is counter clockwise
    rightServo.write(0); // 0 is clockwise
  }

  // ------------------- rotate right --------------------
  else if ((leftWhisker == 0) && (rightWhisker != 0)) {

    previousTime = millis();
    while (millis() - previousTime < reverseDuration) {
      leftServo.writeMicroseconds(1000);
      rightServo.writeMicroseconds(2000);
    }
    delay(1000);

    previousTime = millis();
    while (millis() - previousTime < rotationDuration) {
      leftServo.writeMicroseconds(2000);
      rightServo.writeMicroseconds(2000);
    }
    delay(1000);
  }

  // --------------------- Rotate left ------------------
  else if ((leftWhisker != 0) && (rightWhisker == 0)) {
    previousTime = millis();
    while (millis() - previousTime < reverseDuration) {
      leftServo.writeMicroseconds(1000);
      rightServo.writeMicroseconds(2000);
    }
    delay(1000);

    previousTime = millis();
    while (millis() - previousTime < rotationDuration) {
      leftServo.writeMicroseconds(1000);
      rightServo.writeMicroseconds(1000);
    }
    delay(1000);
  }

  // --------------- rotate left/right ----------------
  else if ((leftWhisker == 0) && (rightWhisker == 0)) {
    previousTime = millis();
    while (millis() - previousTime < reverseDuration + 1000) {
      leftServo.writeMicroseconds(1000);
      rightServo.writeMicroseconds(2000);
    }

    while (millis() - previousTime < rotationDuration + 250) {
      leftServo.writeMicroseconds(1000);
      rightServo.writeMicroseconds(1000);
    }
  }

}
