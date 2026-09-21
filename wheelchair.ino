/*
 * Automated Wheelchair Prototype - Final Integrated Firmware
 * Hardware Serial configured on D0 (RX) and D1 (TX).
 * Fixed turning logic so Left ('A') pivots left and Right ('D') pivots right.
 */

// --- HARDWARE PIN DEFINITIONS ---
// IR Sensors (Active-LOW: 0 = Obstacle Detected, 1 = Clear)
const int PIN_IR_LEFT  = 13; // Left IR from user's POV
const int PIN_IR_RIGHT = 12; // Right IR from user's POV

// Motor Driver Direction Pins (L298N)
const int PIN_IN1 = 11; // PWM Left Motor Forward
const int PIN_IN2 = 7;  // Left Motor Direction (Reverse)
const int PIN_IN3 = 9;  // PWM Right Motor Forward
const int PIN_IN4 = 5;  // Right Motor Direction (Reverse)

// Ultrasonic Distance Sensor
const int PIN_TRIG = 10;
const int PIN_ECHO = 8;

// Sound Warning
const int PIN_BUZZER = 6;

// HC-05 Bluetooth Module Connection State
const int PIN_BT_STATE = 4; // Data goes via Hardware Serial D0 (RX) and D1 (TX)

// KY-023 2-Axis Joystick Module
const int PIN_JOY_Y  = A0;
const int PIN_JOY_X  = A1;
const int PIN_JOY_SW = A2; // Push button stop

// --- JOYSTICK THRESHOLDS ---
const int JOY_LOW_THRESHOLD  = 200; 
const int JOY_HIGH_THRESHOLD = 800;

// Non-blocking timing variables
unsigned long lastUltrasonicTime = 0;
const unsigned long ULTRASONIC_INTERVAL = 50; 

unsigned long lastBuzzerToggleTime = 0;
bool buzzerState = LOW;

// Global state variables
float currentDistanceCm = 999.0;
char lastBtCommand = 'X'; // Default to Stop when Bluetooth connects
bool lastBtState = false;

// --- MOTOR CONTROLS ---

void stopMotors() {
  analogWrite(PIN_IN1, 0);
  digitalWrite(PIN_IN2, LOW);
  analogWrite(PIN_IN3, 0);
  digitalWrite(PIN_IN4, LOW);
}

void moveForward(int pwmSpeed) {
  analogWrite(PIN_IN1, pwmSpeed);
  digitalWrite(PIN_IN2, LOW);
  analogWrite(PIN_IN3, pwmSpeed);
  digitalWrite(PIN_IN4, LOW);
}

void moveReverse() {
  analogWrite(PIN_IN1, 0);
  digitalWrite(PIN_IN2, HIGH);
  analogWrite(PIN_IN3, 0);
  digitalWrite(PIN_IN4, HIGH);
}

void turnLeft() {
  // Pivot LEFT: Left Motor OFF, Right Motor ON
  analogWrite(PIN_IN1, 0);
  digitalWrite(PIN_IN2, LOW);
  analogWrite(PIN_IN3, 255);
  digitalWrite(PIN_IN4, LOW);
}

void turnRight() {
  // Pivot RIGHT: Left Motor ON, Right Motor OFF
  analogWrite(PIN_IN1, 255);
  digitalWrite(PIN_IN2, LOW);
  analogWrite(PIN_IN3, 0);
  digitalWrite(PIN_IN4, LOW);
}

// --- SENSORS & ALERTS ---

void updateUltrasonicDistance() {
  unsigned long currentMillis = millis();
  if (currentMillis - lastUltrasonicTime >= ULTRASONIC_INTERVAL) {
    lastUltrasonicTime = currentMillis;

    digitalWrite(PIN_TRIG, LOW);
    delayMicroseconds(2);
    digitalWrite(PIN_TRIG, HIGH);
    delayMicroseconds(10);
    digitalWrite(PIN_TRIG, LOW);

    long duration = pulseIn(PIN_ECHO, HIGH, 25000); 
    if (duration == 0) {
      currentDistanceCm = 999.0;
    } else {
      currentDistanceCm = duration / 58.0; 
    }
  }
}

void updateBuzzer(float distance) {
  unsigned long currentMillis = millis();
  int toggleInterval = 0; 

  if (distance > 30.0 && distance < 40.0) {
    toggleInterval = 200; 
  } else if (distance > 20.0 && distance < 30.0) {
    toggleInterval = 100; 
  } else {
    toggleInterval = 0;   
  }

  if (toggleInterval == 0) {
    buzzerState = LOW;
    digitalWrite(PIN_BUZZER, LOW);
  } else {
    if (currentMillis - lastBuzzerToggleTime >= (unsigned long)toggleInterval) {
      lastBuzzerToggleTime = currentMillis;
      buzzerState = !buzzerState;
      digitalWrite(PIN_BUZZER, buzzerState ? HIGH : LOW);
    }
  }
}

// --- INITIALIZATION ---

void setup() {
  pinMode(PIN_IR_LEFT, INPUT);
  pinMode(PIN_IR_RIGHT, INPUT);

  pinMode(PIN_IN1, OUTPUT);
  pinMode(PIN_IN2, OUTPUT);
  pinMode(PIN_IN3, OUTPUT);
  pinMode(PIN_IN4, OUTPUT);

  pinMode(PIN_TRIG, OUTPUT);
  pinMode(PIN_ECHO, INPUT);

  pinMode(PIN_BUZZER, OUTPUT);
  pinMode(PIN_BT_STATE, INPUT);
  pinMode(PIN_JOY_SW, INPUT_PULLUP);

  // Initialize Hardware Serial for HC-05 (D0 RX, D1 TX)
  Serial.begin(9600);

  bool btConnected = (digitalRead(PIN_BT_STATE) == HIGH);
  lastBtState = btConnected;

  if (!btConnected) {
    moveForward(255); 
  } else {
    stopMotors();     
  }
}

// --- MAIN CONTROL LOOP ---

void loop() {
  bool btConnected = (digitalRead(PIN_BT_STATE) == HIGH);

  // Check Bluetooth Connection State Transition
  if (btConnected && !lastBtState) {
    lastBtCommand = 'X'; // Force stop as soon as connection is established
  }
  lastBtState = btConnected;

  // Read incoming Bluetooth characters over Hardware Serial (D0/D1)
  while (Serial.available() > 0) {
    char c = Serial.read();
    
    // Auto-convert lowercase inputs (w, a, s, d, x) to uppercase
    if (c >= 'a' && c <= 'z') {
      c = c - 32;
    }
    
    // Filter out white space and newlines
    if (c == 'W' || c == 'A' || c == 'S' || c == 'D' || c == 'X') {
      lastBtCommand = c;
    }
  }

  // Refresh non-blocking sensors
  updateUltrasonicDistance();
  updateBuzzer(currentDistanceCm);

  // Read hardware inputs
  bool leftIrObstacle  = (digitalRead(PIN_IR_LEFT) == LOW);  
  bool rightIrObstacle = (digitalRead(PIN_IR_RIGHT) == LOW); 
  bool joyStopPressed  = (digitalRead(PIN_JOY_SW) == LOW);    

  int joyX = analogRead(PIN_JOY_X);
  int joyY = analogRead(PIN_JOY_Y);

  char desiredCommand = 'X';

  if (btConnected) {
    // Bluetooth mode
    desiredCommand = lastBtCommand;
  } else {
    // Joystick Mode (When Bluetooth is disconnected)
    if (joyY < JOY_LOW_THRESHOLD) {
      desiredCommand = 'W'; // Forward
    } else if (joyY > JOY_HIGH_THRESHOLD) {
      desiredCommand = 'S'; // Reverse
    } else if (joyX < JOY_LOW_THRESHOLD) {
      desiredCommand = 'D'; // Swap direction mapping to match wheelchair movement
    } else if (joyX > JOY_HIGH_THRESHOLD) {
      desiredCommand = 'A'; // Swap direction mapping to match wheelchair movement
    } else {
      desiredCommand = 'W'; // Default movement when joystick is idle
    }
  }

  // --- SAFETY HIERARCHY EVALUATION ---

  // Priority 1: Emergency Stop (Button pressed or BT 'X')
  if (joyStopPressed || (btConnected && desiredCommand == 'X')) {
    stopMotors();
    return;
  }

  // Priority 2: Both IR sensors detect an obstacle simultaneously
  if (leftIrObstacle && rightIrObstacle) {
    stopMotors();
    return;
  }

  // Priority 3: Directional IR Obstacle Overrides
  // If Right IR sees an obstacle, pivot Left
  if (rightIrObstacle) {
    turnLeft(); 
    return;
  }
  // If Left IR sees an obstacle, pivot Right
  if (leftIrObstacle) {
    turnRight(); 
    return;
  }

  // Priority 4: Reverse Movement (Allowed even if an obstacle is in front)
  if (desiredCommand == 'S') {
    moveReverse();
    return;
  }

  // Priority 5: User Turning Commands
  if (desiredCommand == 'A') {
    turnLeft();
    return;
  }
  if (desiredCommand == 'D') {
    turnRight();
    return;
  }

  // Priority 6: Forward Drive (Ultrasonic distance stops or scales speed)
  if (desiredCommand == 'W') {
    if (currentDistanceCm <= 20.0) {
      stopMotors(); // Block ONLY forward movement if front distance <= 20 cm
    } else if (currentDistanceCm > 30.0 && currentDistanceCm < 40.0) {
      moveForward(190);
    } else if (currentDistanceCm > 20.0 && currentDistanceCm <= 30.0) {
      moveForward(120);
    } else {
      moveForward(255);
    }
    return;
  }

  stopMotors();
}
