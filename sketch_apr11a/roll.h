#pragma once
#include "roll_l.h"
#include "roll_r.h"
void roll (float distance, bool direct){
  unsigned long steps_left = (distance/WHEEL_L) * 4095;
  pinMode(IN1L, OUTPUT); 
  pinMode(IN2L, OUTPUT); 
  pinMode(IN3L, OUTPUT); 
  pinMode(IN4L, OUTPUT);
  pinMode(IN1, OUTPUT); 
  pinMode(IN2, OUTPUT); 
  pinMode(IN3, OUTPUT); 
  pinMode(IN4, OUTPUT);  
  
  while(steps_left>0){
    delay(1);
    stepper_l();
    stepper_r(); 
    steps_left--;
  }
}
