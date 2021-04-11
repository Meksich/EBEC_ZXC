#pragma once
#define WHEEL_L  float(120)
#define RADIUS float(280)
int Steps_l = 0;
int IN1L = 6;
int IN2L = 7;
int IN3L = 8;
int IN4L = 9;
bool Direction_l = true;

void SetDirection_l(){
if(Direction_l==1) Steps_l++;
if(Direction_l==0) Steps_l--; 
if(Steps_l>7) Steps_l=0;
if(Steps_l<0) Steps_l=7; 
}

void stepper_l(){
  switch(Steps_l){
     case 0:
       digitalWrite(IN1L, LOW); 
       digitalWrite(IN2L, LOW);
       digitalWrite(IN3L, LOW);
       digitalWrite(IN4L, HIGH);
     break; 
     case 1:
       digitalWrite(IN1L, LOW); 
       digitalWrite(IN2L, LOW);
       digitalWrite(IN3L, HIGH);
       digitalWrite(IN4L, HIGH);
     break; 
     case 2:
       digitalWrite(IN1L, LOW); 
       digitalWrite(IN2L, LOW);
       digitalWrite(IN3L, HIGH);
       digitalWrite(IN4L, LOW);
     break; 
     case 3:
       digitalWrite(IN1L, LOW); 
       digitalWrite(IN2L, HIGH);
       digitalWrite(IN3L, HIGH);
       digitalWrite(IN4L, LOW);
     break; 
     case 4:
       digitalWrite(IN1L, LOW); 
       digitalWrite(IN2L, HIGH);
       digitalWrite(IN3L, LOW);
       digitalWrite(IN4L, LOW);
     break; 
     case 5:
       digitalWrite(IN1L, HIGH); 
       digitalWrite(IN2L, HIGH);
       digitalWrite(IN3L, LOW);
       digitalWrite(IN4L, LOW);
     break; 
       case 6:
       digitalWrite(IN1L, HIGH); 
       digitalWrite(IN2L, LOW);
       digitalWrite(IN3L, LOW);
       digitalWrite(IN4L, LOW);
     break; 
     case 7:
       digitalWrite(IN1L, HIGH); 
       digitalWrite(IN2L, LOW);
       digitalWrite(IN3L, LOW);
       digitalWrite(IN4L, HIGH);
     break; 
     default:
       digitalWrite(IN1L, LOW); 
       digitalWrite(IN2L, LOW);
       digitalWrite(IN3L, LOW);
       digitalWrite(IN4L, LOW);
     break;
  }
  SetDirection_l();
}



void roll_l(float distance, bool direct){
  Direction_l = direct;
  unsigned long steps_left = (distance/WHEEL_L) * 4095;
  pinMode(IN1L, OUTPUT); 
  pinMode(IN2L, OUTPUT); 
  pinMode(IN3L, OUTPUT); 
  pinMode(IN4L, OUTPUT); 
  
  while(steps_left>0){
    delay(1);
    stepper_l(); 
    steps_left--;
  }
}
