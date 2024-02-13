/*
* Name : Mouse mover
* Description: Move the mouse while you're drinking you coffee (home office)
* Author: BARJO
* Version : 1.0
*/

#include <Mouse.h>

// btn
const byte enableBtn = 3;
int btnState = 0;

// led
const byte led = 8;
int ledState = 0;

// direction, speed and distance
int xDir = 1;
int yDir = 1;
int wheel = 0;
int pxToMove = 100;
int speed = 20;

// 0 = move right / 1 = move left
int direction = 0;

// ON or OFF
bool mode = false;

void setup() {
  // led
  pinMode(led, OUTPUT);

  // interrupt (when button is pressed, toggle mode)
  pinMode(enableBtn, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(enableBtn), changeMode, RISING);

  // blink led at start
  digitalWrite(led, LOW);
  delay(300);
  digitalWrite(led, HIGH);
  delay(300);
  digitalWrite(led, LOW);
  delay(300);
  digitalWrite(led, HIGH);
  delay(300);
  digitalWrite(led, LOW);
}

void loop() {
  // random distance, speed and direction
  pxToMove = random(100, 300);
  speed = random(5, 50);
  do {
    xDir = random(-1, 2);
  } while(xDir == 0);
  do {
    yDir = random(-1, 2);
  } while(yDir == 0);


  // move the mouse if switched on
  if (mode) {
    // move the mouse
    for (int i=0;i<=pxToMove;i++) {
      Mouse.move(xDir, yDir, wheel);
      delay(speed);
    }

    // move the mouse back
    for (int j=0;j<=pxToMove;j++) {
      Mouse.move(-(xDir), -(yDir), wheel);
      delay(speed);
    }

  }
  
}

void changeMode() {
  // switch ON/OFF
  btnState = digitalRead(enableBtn);

  // change mode if button pressed (ON/OFF)
  if (btnState == HIGH) {
    if (mode) {
      mode = false;
      digitalWrite(led, LOW);
    } else {
      mode = true;
      digitalWrite(led, HIGH);
    }
  }
  // make sure this event is trigger only once when the button is pressed
  delay(500);
}
