float ANGLE1 = -29.9118698;
float ANGLE2 = 96.7853494;
float ANGLE3 = -107.281268;
float LENGTH1 = 1377.7729753917625899280575539568;
float LENGTH2 = 1501.9956360591366906474820143898;
float LENGTH3 = 1270.7671414905035971223021582744;

bool moveForward = false;
bool moveBackwards = false;
bool turnRight = false;
bool turnLeft = false;


void doMision()
{
  rotate(ANGLE1);
  delay(1000);
  roll(LENGTH1);
  delay(1000);
  
  rotate(ANGLE2);
  delay(1000);
  roll(LENGTH2);
  delay(1000);
  
  rotate(ANGLE3);
  delay(1000);
  roll(LENGTH3);
  delay(1000);
};



void loop() 
{
  int commandButton = analogRead(1);
  if(commandButton == 1)
  {
    roll(0.01);
  };
  if(commandButton == 2)
  {
    roll(-0.01);
  };
  if(commandButton == 3)
  {
    rotate(0.01);
  };
  if(commandButton == 4)
  {
    rotate(-0.01);
  }; 
  if(commandButton == 3)
  {
    doMision();
  }
};
