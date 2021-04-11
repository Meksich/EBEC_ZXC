#pragma once
#define WHEEL_L  float(120)
#define RADIUS float(280)
int Steps_r = 0;
int IN1 = 10;
int IN2 = 11;
int IN3 = 12;
int IN4 = 13;
bool Direction_r = true;

void SetDirection_r(){
if(Direction_r==1) Steps_r--;
if(Direction_r==0) Steps_r++; 
if(Steps_r>7) Steps_r=0;
if(Steps_r<0) Steps_r=7; 
}

void stepper_r(){
  switch(Steps_r){
     case 0:
       digitalWrite(IN1, LOW); 
       digitalWrite(IN2, LOW);
       digitalWrite(IN3, LOW);
       digitalWrite(IN4, HIGH);
     break; 
     case 1:
       digitalWrite(IN1, LOW); 
       digitalWrite(IN2, LOW);
       digitalWrite(IN3, HIGH);
       digitalWrite(IN4, HIGH);
     break; 
     case 2:
       digitalWrite(IN1, LOW); 
       digitalWrite(IN2, LOW);
       digitalWrite(IN3, HIGH);
       digitalWrite(IN4, LOW);
     break; 
     case 3:
       digitalWrite(IN1, LOW); 
       digitalWrite(IN2, HIGH);
       digitalWrite(IN3, HIGH);
       digitalWrite(IN4, LOW);
     break; 
     case 4:
       digitalWrite(IN1, LOW); 
       digitalWrite(IN2, HIGH);
       digitalWrite(IN3, LOW);
       digitalWrite(IN4, LOW);
     break; 
     case 5:
       digitalWrite(IN1, HIGH); 
       digitalWrite(IN2, HIGH);
       digitalWrite(IN3, LOW);
       digitalWrite(IN4, LOW);
     break; 
       case 6:
       digitalWrite(IN1, HIGH); 
       digitalWrite(IN2, LOW);
       digitalWrite(IN3, LOW);
       digitalWrite(IN4, LOW);
     break; 
     case 7:
       digitalWrite(IN1, HIGH); 
       digitalWrite(IN2, LOW);
       digitalWrite(IN3, LOW);
       digitalWrite(IN4, HIGH);
     break; 
     default:
       digitalWrite(IN1, LOW); 
       digitalWrite(IN2, LOW);
       digitalWrite(IN3, LOW);
       digitalWrite(IN4, LOW);
     break; 
  }
  SetDirection_r();
}

void roll_r(float distance, bool direct){
  Direction_r = direct;
  unsigned long steps_left = (distance/WHEEL_L) * 4095;
  pinMode(IN1, OUTPUT); 
  pinMode(IN2, OUTPUT); 
  pinMode(IN3, OUTPUT); 
  pinMode(IN4, OUTPUT); 
  
  while(steps_left>0){
    delay(1);
    stepper_r(); 
    steps_left--;
  }
}
