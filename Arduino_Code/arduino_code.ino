#include <Arduino.h>
#include <Servo.h>

#define NUM_SERVOS 6
#define MAX_STEPS 50
#define STEP_DELAY 15
#define HOME_POS 90

Servo servos[NUM_SERVOS];
int pins[NUM_SERVOS] = { 4, 5, 6, 7, 8, 9 }; // change it your servo control pins from Base of robot to end effector

int currentPos[NUM_SERVOS] = { HOME_POS, HOME_POS, HOME_POS, HOME_POS, HOME_POS, HOME_POS };
int targetPos[NUM_SERVOS] = { HOME_POS, HOME_POS, HOME_POS, HOME_POS, HOME_POS, HOME_POS };

int program[MAX_STEPS][NUM_SERVOS];
int programLength = 0;

bool resetting = false;

String cmd;

void setup() {
  Serial.begin(9600);

  for (int i = 0; i < NUM_SERVOS; i++) {
    servos[i].attach(pins[i]);
    servos[i].write(currentPos[i]);
  }
}

void loop() {
  readCommand();
  smoothMove();
}

void readCommand() {
  if (!Serial.available()) return;

  cmd = Serial.readStringUntil('\n');
  cmd.trim();

  // Live move
  if (cmd.startsWith("M")) {  //M,2,120
    int c1 = cmd.indexOf(',');
    int c2 = cmd.lastIndexOf(',');

    int id = cmd.substring(c1 + 1, c2).toInt() - 1;
    int ang = cmd.substring(c2 + 1).toInt();

    if (id >= 0 && id < NUM_SERVOS && ang >= 0 && ang <= 180 && !resetting) {

      if (id == 5) {
        // Servo 6: map 0–180 from GUI to 5–100 real angle
        targetPos[id] = map(ang, 0, 180, 3, 90);
      }else if(id == 3){
         targetPos[id] = map(ang, 0, 180, 20, 160);
      } 
      else {
        targetPos[id] = ang;
      }
    }

  }

  // Save pose
  else if (cmd == "SAVE") {
    if (programLength < MAX_STEPS) {
      for (int i = 0; i < NUM_SERVOS; i++) {
        program[programLength][i] = currentPos[i];
      }
      programLength++;
    }
  }

  // Play program
  else if (cmd == "PLAY") {
    runProgram();
  }

  // Smooth Reset
  else if (cmd == "RESET") {
    startReset();
  }
}

void smoothMove() {
  for (int i = 0; i < NUM_SERVOS; i++) {
    if (currentPos[i] < targetPos[i]) {
      currentPos[i]++;
      servos[i].write(currentPos[i]);
    } else if (currentPos[i] > targetPos[i]) {
      currentPos[i]--;
      servos[i].write(currentPos[i]);
    }
  }
  delay(STEP_DELAY);
}

void startReset() {
  resetting = true;

  // set home target
  for (int i = 0; i < NUM_SERVOS; i++) {
    targetPos[i] = HOME_POS;
  }

  // wait until all servos reach home
  bool moving = true;
  while (moving) {
    moving = false;
    for (int i = 0; i < NUM_SERVOS; i++) {
      if (currentPos[i] < HOME_POS) {
        currentPos[i]++;
        servos[i].write(currentPos[i]);
        moving = true;
      } else if (currentPos[i] > HOME_POS) {
        currentPos[i]--;
        servos[i].write(currentPos[i]);
        moving = true;
      }
    }
    delay(STEP_DELAY);
  }

  // clear program
  programLength = 0;
  resetting = false;
}

void runProgram() {
  for (int step = 0; step < programLength; step++) {
    bool moving = true;
    while (moving) {
      moving = false;
      for (int i = 0; i < NUM_SERVOS; i++) {
        if (currentPos[i] < program[step][i]) {
          currentPos[i]++;
          servos[i].write(currentPos[i]);
          moving = true;
        } else if (currentPos[i] > program[step][i]) {
          currentPos[i]--;
          servos[i].write(currentPos[i]);
          moving = true;
        }
      }
      delay(STEP_DELAY);
    }
    delay(300);
  }
}
