#include <Stepper.h>

const int stepsPerRevolutionX = 2038;
const int stepsPerRevolutionY = 2038;

Stepper stepperX = Stepper(stepsPerRevolutionX, 2, 4, 3, 5);
Stepper stepperY = Stepper(stepsPerRevolutionY, 6, 8, 7, 9);

const int fieldSizeX = 200;
const int fieldSizeY = 200;

int currentPositionX = 0;
int currentPositionY = 0;

void setup() {
  Serial.begin(19200);
}

void loop() {
  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n');
    if (input.startsWith("M")) {
      processInput(input.substring(1));
    }
    else if (input.startsWith("P")) {
      Serial.println("-------------------");
      Serial.print("X = ");
      Serial.println(currentPositionX);
      Serial.print("Y = ");
      Serial.println(currentPositionY);
      Serial.println("-------------------");
    }
    else if (input.startsWith("?")) {
      // Print the help screen
      printHelpScreen();
    }
  }
}

void processInput(String input) {
  int x, y;
  sscanf(input.c_str(), "%d,%d", &x, &y);
  
  move_motors(x, y, currentPositionX, currentPositionY, fieldSizeX, fieldSizeY);
}

void move_motors(int targetPositionX, int targetPositionY, int& currentPositionX, int& currentPositionY, int fieldSizeX, int fieldSizeY) {
  int stepsX = int((targetPositionX - currentPositionX) * (stepsPerRevolutionX / fieldSizeX));
  int stepsY = int((targetPositionY - currentPositionY) * (stepsPerRevolutionY / fieldSizeY));

  currentPositionX = targetPositionX;
  currentPositionY = targetPositionY;

  int maxSteps = max(abs(stepsX), abs(stepsY));

  if (maxSteps >= 0) {
    for (int i = 0; i < maxSteps; i++) {
      stepperX.setSpeed(5);
      stepperY.setSpeed(5);

      if (i < abs(stepsX)) {
        stepperX.step(stepsX > 0 ? 1 : -1);
      }

      if (i < abs(stepsY)) {
        stepperY.step(stepsY > 0 ? 1 : -1);
      }
    }
    Serial.println("Done");
  }
}

void printHelpScreen() {
  Serial.println("    ___  _____    _____  _       _   _               _____            _             _     ");
  Serial.println("   |__ \\|  __ \\  |  __ \\| |     | | | |             / ____|          | |           | |    ");
  Serial.println("      ) | |  | | | |__) | | ___ | |_| |_ ___ _ __  | |     ___  _ __ | |_ _ __ ___ | |___ ");
  Serial.println("     / /| |  | | |  ___/| |/ _ \\| __| __/ _ \\ '__| | |    / _ \\| '_ \\| __| '__/ _ \\| / __|");
  Serial.println("    / /_| |__| | | |    | | (_) | |_| ||  __/ |    | |___| (_) | | | | |_| | | (_) | \\__ \\");
  Serial.println("   |____|_____/  |_|    |_|\\___/ \\___|\\___|_|     \\_____\\___/|_| |_|\\__|_|  \\___/|_|___/");
  Serial.println("   |  _ \\            /\\         | | | |                                                  ");
  Serial.println("   | |_) |_   _     /  \\   _ __ | |_| |__   ___  _ __  _   _                            ");
  Serial.println("   |  _ <| | | |   / /\\ \\ | '_ \\| __| '_ \\ / _ \\| '_ \\| | | |                            ");
  Serial.println("   | |_) | |_| |  / ____ \\| | | | |_| | | | (_) | | | | |_| |                            ");
  Serial.println("   |____/ \\__, | /_/    \\_\\_| |_|\\__|_| |_|\\___/|_| |_|\\__, |                            ");
  Serial.println("           __/ |                                        __/ |                            ");
  Serial.println("          |___/                                        |___/                             ");
  Serial.println("---------------------------------------------------------------------------------------------------");
  Serial.println("Available Commands:");
  Serial.println("  M         Moves the position manually.");
  Serial.println("  P         Prints the current position.");
  Serial.println("  ?         Prints this help screen");
  Serial.println("-------------------------------");
  Serial.println();
  Serial.println("-------------------------------");
  Serial.println("Command: M");
  Serial.println("Description: Moves the position manually.");
  Serial.println("Usage: M[Xposition],[Yposition]");
  Serial.println("Notes:");
  Serial.println("Xposition & Yposition must be an integer");
  Serial.println("-------------------------------");
  Serial.println("Command: P");
  Serial.println("Description: Prints the current position of the head.");
  Serial.println("Usage: P");
  Serial.println("-------------------------------$");
}
