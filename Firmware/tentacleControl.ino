//Basic robotic arm stepper motor control with DRV8825 drivers
//Created: 7/30/17
//Last Updated: 7/30/17
//by Daniel Lytle 
//website: daniellytle.com   github: github.com/codebylytle

#include "tentacleConfig.h"

boolean busy = false;
//creates integer variables to track position of arm relative to start point
short relRL = 0;
short relFB = 0;
//limits maximum distance from startpoint by a number of steps in any direction
unsigned int maxSteps = 1000000;
//stores number of steps to be done along each axis. Forward & right = positive
int fbCommand = 0;
int rlCommand = 0;
//sets control mode. a = autonomous. s = serial monitor. b = bluetooth
char mode = 's';

void setup() {
  // put your setup code here, to run once:
  pinMode(STEP_EN, OUTPUT);
  pinMode(STEP_RL, OUTPUT);
  pinMode(STEP_FB, OUTPUT);
  pinMode(RL_MOTOR_A_DIR, OUTPUT);
  pinMode(RL_MOTOR_B_DIR, OUTPUT);
  pinMode(FB_MOTOR_A_DIR, OUTPUT);
  pinMode(FB_MOTOR_B_DIR, OUTPUT);
  //pinMode(3, OUTPUT);
  //pinMode(12, OUTPUT);
  
  digitalWrite(STEP_EN, LOW);
  digitalWrite(STEP_RL, LOW);
  digitalWrite(STEP_FB, LOW);
  //digitalWrite(3, LOW);
  //digitalWrite(12, LOW);

  Serial.begin(9600);
  Serial.println("Use WASD keys to control robot movement in 10-step increments.");
}

void loop() {
  // put your main code here, to run repeatedly:
  if(mode == 's' && Serial.available() > 0 && !busy){
    char incomingByte = Serial.read();

    Serial.print("Recieved:");
    Serial.println(incomingByte);
    if (incomingByte == 'w' || incomingByte == 'W'){
      fbCommand += 30;
    }
    else if(incomingByte == 's' || incomingByte == 'S'){
      fbCommand -= 30;
    }
    else if(incomingByte == 'a' || incomingByte == 'A'){
      rlCommand += 30;
    }
    else if(incomingByte == 'd' || incomingByte == 'D'){
      rlCommand -= 30;
    }
    else if(incomingByte == 'P'){
      Serial.println("Current Position: F/B: " + String(relFB) + " R/L: " + String(relRL));
    }
    else{
      Serial.println("Use WASD keys to control robot movement in 10-step increments.");
    }
  }

  if(fbCommand){
    boolean stepDir = false;
    if (fbCommand > 0){
      stepDir = true;
    }
    if(abs(relFB + fbCommand) <= maxSteps){
      relFB += fbCommand;
      runFB(stepDir, abs(fbCommand));
    }
    else{
      Serial.println("Endstop hit.");
    }
    fbCommand = 0;
  }
  
  if(rlCommand){
    boolean stepDir = false;
    if(rlCommand > 0){
      stepDir = true;
    }
    if(abs(relRL + rlCommand) <= maxSteps){
      relRL += rlCommand;
      runRL(stepDir, abs(rlCommand));
    }
    else{
      Serial.println("Endstop hit.");
    }
    rlCommand = 0;
  }

}

