//functions for granular stepper control
void runRL(boolean stepDir, int numSteps){
  //unsigned int stepV, unsigned int stepA
  if (stepDir){
    digitalWrite(RL_MOTOR_A_DIR, HIGH);
    digitalWrite(RL_MOTOR_B_DIR, LOW);
  }
  else{
    digitalWrite(RL_MOTOR_A_DIR, LOW);
    digitalWrite(RL_MOTOR_B_DIR, HIGH);
  }
  
  for(int i = 0; i < numSteps; i++){
    digitalWrite(STEP_RL, HIGH);
    //digitalWrite(3, HIGH);
    delay(4);
    digitalWrite(STEP_RL, LOW);
    //digitalWrite(3, LOW);
    delay(2);
  }
}

void runFB(boolean stepDir, int numSteps){
   //, unsigned int stepV, unsigned int stepA
   if (stepDir){
    digitalWrite(FB_MOTOR_A_DIR, HIGH);
    digitalWrite(FB_MOTOR_B_DIR, LOW);
  }
  else{
    digitalWrite(FB_MOTOR_A_DIR, LOW);
    digitalWrite(FB_MOTOR_B_DIR, HIGH);
  }


  for(int i = 0; i < numSteps; i++){
    digitalWrite(STEP_FB, HIGH);
    //digitalWrite(12, HIGH);
    delay(4);
    digitalWrite(STEP_FB, LOW);
    //digitalWrite(12, LOW);
    delay(2);
  }
}

