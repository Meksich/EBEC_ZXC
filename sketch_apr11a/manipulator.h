
#include <Servo.h>
Servo base; // moving base of arm  
Servo mid;
Servo clamp_rotate;
Servo clamp;


  
int base_pos, mid_pos, clamp_rotate_pos, clamp_pos = 0;   

void move_base(int angle){
  for(int i =base_pos; i< base_pos + angle ;i++)
  base.write(i);
  delay(10);
  } 
  

void move_mid(int angle){
  for(int i =mid_pos; i< mid_pos + angle ;i++)
  mid.write(i);
  delay(10);
  } 
    
void move_clamp_rotate(int angle){
  for(int i =clamp_rotate_pos; i< clamp_rotate_pos + angle ;i++)
  clamp_rotate.write(i);
  delay(10);
  } 

  
void move_clamp(int angle){
  for(int i =clamp_pos; i< clamp_pos + angle ;i++)
  clamp.write(i);
  delay(10);
  } 
