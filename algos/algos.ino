#include <math.h>
#include <Servo.h> 
#include <Stepper.h>
#define _USE_MATH_DEFINES


Servo myservo;
Stepper leftStepper = Stepper(1, 1, 2, 3, 4);
Stepper rightStepper = Stepper(1, 5, 6, 7, 8);
float ASIXRAD = 0.2;  //in meters
float STEP = 0.407; //in meters
int currrentDegree = 90;

bool moveForward = false;
bool moveBackwards = false;
bool turnRight = false;
bool turnLeft = false;

enum TurnPositions {LEFT = 30, CENTER = 90, RIGHT = 150};

struct Cord
{
  float cordX;
  float cordY;
};

float getDistanceInSteps(Cord start, Cord finish)
{
  return sqrt(pow((start.cordX - finish.cordX),2) + pow((start.cordY - finish.cordY),2)) / STEP;
};

float getAngleRad(Cord start, Cord finish)
{
  return atan((finish.cordY - start.cordY) / (finish.cordX - start.cordX));
};

void move(float distanceLength)
{
  float distanceLengthSteps = distanceLength / STEP;
  for (float i = 0; i < distanceLengthSteps; i += 0.01)
    {
      leftStepper.step(0.01);
      rightStepper.step(0.01);
      digitalWrite(12, LOW);
      
    };
};

void rotateStill(float angleRad)
{
  float arcLengthSteps = (angleRad * ASIXRAD) / STEP;
  if (angleRad <= M_PI)
  {
    for (int i = 0; i < arcLengthSteps; i += 0.01)
    {
      leftStepper.step(0.01);
      rightStepper.step(-0.01);
    };
  }
  else  
  {
    for (int i = 0; i < arcLengthSteps; i += 0.01)
    {
      leftStepper.step(-0.01);
      rightStepper.step(0.01);
    };
  };
};

void doMision(Cord start, Cord finish)
{
  rotateStill(getAngleRad(start, finish));
  delay(1000);
  leftStepper.step(getDistanceInSteps(start, finish));
  rightStepper.step(getDistanceInSteps(start, finish));
};

void rotateFrontAsix(int angleGrad)
{
  myservo.write(90 + angleGrad);
};

void setup() {
  // put your setup code here, to run once:
  myservo.attach(9);
  myservo.write(90);
  leftStepper.setSpeed(100);
  rightStepper.setSpeed(100);
};

void loop() {
  int checkedPosition = TurnPositions::LEFT;
  int checkedDegree = static_cast < int > (checkedPosition);
  if(moveForward)
  {
    move(0.01);
  };
  if(moveBackwards)
  {
    move(-0.01);
  };
  if(checkedDegree > currrentDegree)
  {
    currrentDegree ++;
    myservo.write(currrentDegree);
  };
  if(checkedDegree < currrentDegree)
  {
    currrentDegree --;
    myservo.write(currrentDegree);
  }; 
};
