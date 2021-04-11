void setup() {
  Serial.begin(9600);
}

void loop() {
  char cmd = '\0';
  while (Serial.available()) {
    cmd = Serial.read();
    Serial.println(cmd);
    switch (cmd) {
      case 'f':
        //roll(1.4, FORWARD);
        break;
      case 'b':
        //roll(1.4, BACKWARD);
        break;
      case 'l':
        //rotate(-4);
        break;
      case 'r':
        //rotate(4);
        break;
      case 'w':
        // crane w (up)
        break;
      case 's':
        // crane s (down)
        break;
      case 'a':
        // crane a (left)
        break;
      case 'd':
        // crane d (right)
        break;
      case ' ':
        // crane space
        break;
      case 'm':
        //doMision();
        break;
      default:
        break;
    }
  }
}
