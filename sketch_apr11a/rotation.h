#pragma once
#include "roll_l.h"
#include "roll_r.h"
#define RADIUS 250

void rotate (float angle){
  float len = angle * RADIUS * PI/180;
  unsigned long steps_left = (abs(len)/WHEEL_L) * 4095;
  pinMode(IN1L, OUTPUT); 
  pinMode(IN2L, OUTPUT); 
  pinMode(IN3L, OUTPUT); 
  pinMode(IN4L, OUTPUT);
  pinMode(IN1, OUTPUT); 
  pinMode(IN2, OUTPUT); 
  pinMode(IN3, OUTPUT); 
  pinMode(IN4, OUTPUT);  
  if (len >=0){
    Direction_r = false;
    Direction_l = true;
  }
  if (len <0){
    Direction_r = true;
    Direction_l = false;
   }
  while(steps_left>0){
    delay(1);
    stepper_l();
    stepper_r(); 
    steps_left--;
  }
}
