/* A recreation of Boe-Bot, an autonomous obstacle avoiding robot
   IR receiver: looking at the IR receiver from left to right, data, gnd, vin.
*/
// ------------- Libraries and Global Variables ---------------

#include <Servo.h>

Servo leftServo;
Servo rightServo;
int leftWhisker, rightWhisker;
const long reverseDuration = 1500;
const long rotationDuration = 500;
unsigned long currentTime = millis();
unsigned long previousTime = 0;


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

  leftWhisker = digitalRead(8);
  rightWhisker = digitalRead(9);
  //Serial.print(leftWhisker);      //UNCOMMENT TO DEBUG

  if ((leftWhisker != 0) && (rightWhisker != 0)) {

    // write both servos to move in one direction.
    leftServo.write(0); // 0 is clockwise
    rightServo.write(180); // 180 is counter clockwise
  }

  else if ((leftWhisker == 0) && (rightWhisker != 0)) {
    previousTime = currentTime;
    while (currentTime < previousTime + reverseDuration) {
      leftServo.write(180);
      rightServo.write(0);
    }
    delay(1000);

    previousTime = currentTime;
    while (currentTime < previousTime + rotationDuration) {
      leftServo.write(180);
      rightServo.write(180);
    }
    delay(1000);
  }


  else if ((leftWhisker != 0) && (rightWhisker == 0)) {
    previousTime = currentTime;
    while (currentTime < previousTime + reverseDuration) {
      leftServo.write(180);
      rightServo.write(0);
    }
    delay(1000);
    previousTime = currentTime;
    while (currentTime < previousTime + rotationDuration) {
      leftServo.write(0);
      rightServo.write(0);
    }
    delay(1000);
  }

}
