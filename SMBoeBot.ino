/* A recreation of Boe-Bot, an autonomous obstacle avoiding robot

   IR receiver: looking at the IR receiver from left to right, data, gnd, vin.
   Using delay(ms) after a continousServo.write() tells the servo the time
   duration for write() to run.
   Created: 31/12/2015
   Modified: 13/3/2016

   Changelog:-
   * Unblinded the robot.
   * Added a servo motor that acts as the "neck/head" for the robot.
   
   Known issues:-
   * Turn radius is WAY too big
*/

// ------------- Libraries and Global Variables ---------------
#include <SM.h>
#include <Servo.h>
#include <NewPing.h>

// general stuff
#define REVERSE_DURATION 500
#define ROTATION_DURATION 681.818 // value is around 45º for MY mechanical setup
#define TRIGGER_PIN 12
#define ECHO_PIN 13
#define THRESHOLD 10
#define TREST 500

// driving constants
const int LFORWARD = 2000;
const int RBACKWARD = 2000;
const int RFORWARD = 1000;
const int LBACKWARD = 1000;
const int NEUTRAL = 1500;
unsigned long tnow;

// peripherals
Servo leftServo;
Servo rightServo;
Servo sweep; // Servo to sweep distance sensor around
NewPing sonar(TRIGGER_PIN, ECHO_PIN); // Initiate distance sensor

// Finite state machine setup
SM autonomous(S1);

void setup() {

  // attach servos to their pins on arduino
  leftServo.attach(3);
  rightServo.attach(2);
  sweep.attach(9);

  // Center servo
  sweep.write(90);
  //Serial.begin(9600);

}

void loop() {
  EXEC(autonomous);
}

// Move forward
State S1(){
int distance = sonar.ping_cm();
  leftServo.writeMicroseconds(LFORWARD);
  rightServo.writeMicroseconds(RFORWARD);
  if ((distance <= THRESHOLD) && (distance != 0)) {
    autonomous.Set(S2);
  }
}

// Obstacle detected
State S2() {
  // Stop
  leftServo.writeMicroseconds(NEUTRAL);
  rightServo.writeMicroseconds(NEUTRAL);
  
  // Scan surrounding
  sweep.write(0);
  int leftDistance = sonar.ping_cm();
  delay(750);
  sweep.write(180);
  int rightDistance = sonar.ping_cm();
  delay(750);
  sweep.write(90);
  delay(500);
  compare(leftDistance, rightDistance);

  // Return to state 1
  autonomous.Set(S1);
}


// ------------ Auxilliary functions ------------
void compare(int l, int r) {
  if (l < r) {
    turnLeft();
  }
  else if (r < l) {
    turnRight();
  }
  else {
    return;
  }
}

void turnLeft() {
  
  tnow = millis ();
  while(millis() - tnow <= REVERSE_DURATION){
    // Reverse
    leftServo.writeMicroseconds(LBACKWARD);
    rightServo.writeMicroseconds(RBACKWARD);
    delay(TREST);
    // Stop
    leftServo.writeMicroseconds(NEUTRAL);
    rightServo.writeMicroseconds(NEUTRAL);
    delay(TREST);

    // Rotate left
    leftServo.writeMicroseconds(LBACKWARD);
    rightServo.writeMicroseconds(RFORWARD);
    delay(TREST);
    // Stop
    leftServo.writeMicroseconds(NEUTRAL);
    rightServo.writeMicroseconds(NEUTRAL);
    delay(TREST);
  }
  
}

void turnRight() {
  
  tnow = millis ();
  while(millis() - tnow <= REVERSE_DURATION) {
  // Reverse
  leftServo.writeMicroseconds(LBACKWARD);
  rightServo.writeMicroseconds(RBACKWARD);
  delay(REVERSE_DURATION);
  // Stop
  leftServo.writeMicroseconds(NEUTRAL);
  rightServo.writeMicroseconds(NEUTRAL);
  delay(REVERSE_DURATION);
  
  // Rotate right
  leftServo.writeMicroseconds(LFORWARD);
  rightServo.writeMicroseconds(RBACKWARD);
  delay(ROTATION_DURATION);
  // Stop
  leftServo.writeMicroseconds(NEUTRAL);
  rightServo.writeMicroseconds(NEUTRAL);
  delay(REVERSE_DURATION);
  }
}

