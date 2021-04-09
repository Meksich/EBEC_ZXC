#include <math.h>
#include <Servo.h> 
#include <Stepper.h>


Servo myservo;
Stepper leftStepper = Stepper(1, 1, 2, 3, 4);
Stepper rightStepper = Stepper(1, 5, 6, 7, 8);
float ASIXRAD = 0.2;  //in meters
float STEP = 0.407; //in meters

struct Cord
{
  float cordX
  float cordY  
}

float getDistanceInSteps(Cord start, Cord finish)
{
  return sqrt(pow((start.cordX - finish.cordX),2) + pow((start.cordY - finish.cordY),2))) / STEP;
}

float getAngleRad(Cord start, Cord finish)
{
  return atan((finish.cordY - start.cordY) / (finish.cordX - start.cordX));
}

void rotateStill(float angle)
{
  float arcLengthSteps = (angle * ASIXRAD) / STEP;
  if (angle <= 3.14)
  {
    leftStepper.step(arcLengthSteps);
    rightStepper.step(-arcLengthSteps);
  }
  else  
  {
    leftStepper.step(-arcLengthSteps);
    rightStepper.step(arcLengthSteps);
  };
}
  

void doMision(Cord start, Cord finish)
{
  rotateStill(getAngleRad(start, finish))
  dellay(1000)
  leftStepper.step(getDistanceInSteps(start, finish));
  rightStepper.step(getDistanceInSteps(start, finish));
}

void setup() {
  // put your setup code here, to run once:
  myservo.attach(9);
  myservo.write(90);
  myStepper.setSpeed(100);
}

void loop() {
  // put your main code here, to run repeatedly:
  int xMyCord = 12;
  int yMyCord = 15;
  int xObjCord = 20;
  int yObjCord = 30;
  int xDifCord = xMyCord - xObjCord;
  int yDifCord = yMyCord - yObjCord;
  int degree = atan(yDifCord / xDifCord)
  
  
}
