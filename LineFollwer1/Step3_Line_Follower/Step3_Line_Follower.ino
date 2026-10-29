// ==========================================================
//  LINE FOLLOWER - PART 1 : STEP 3 (FINAL)
//  Simple 2-sensor line follower for ESP32 + L298N
//
//  Wiring summary (ESP32 classic DevKit):
//    GPIO 34 <- Left  IR OUT
//    GPIO 35 <- Right IR OUT
//    GPIO 32 -> ENA   GPIO 33 -> IN1   GPIO 25 -> IN2
//    GPIO 26 -> IN3   GPIO 27 -> IN4   GPIO 13 -> ENB
//    Left motor -> OUT1/OUT2     Right motor -> OUT3/OUT4
// ==========================================================
 
// -------- Sensor Pins --------
const int LEFT_SENSOR  = 34;
const int RIGHT_SENSOR = 35;
 
// -------- Motor Driver Pins --------
const int IN1 = 33;
const int IN2 = 25;
const int IN3 = 26;
const int IN4 = 27;
 
const int ENA = 32;
const int ENB = 13;
 
// -------- Calibration from Step 1B --------
// Value your sensor gives on BLACK (1 for most sensors, 0 for inverted ones)
const int BLACK = 1;
 
// Slow motor speed (0-255)
int motorSpeed = 130;
 
void setup() {
 
  Serial.begin(115200);
 
  pinMode(LEFT_SENSOR, INPUT);
  pinMode(RIGHT_SENSOR, INPUT);
 
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
 
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
 
  stopMotors();        // make sure the bot does not jump at power-on
  delay(2000);         // 2 seconds to place the bot on the line
 
  Serial.println("Line Follower Started");
}
 
void loop() {
 
  int leftValue  = digitalRead(LEFT_SENSOR);
  int rightValue = digitalRead(RIGHT_SENSOR);
 
  bool leftOnBlack  = (leftValue  == BLACK);
  bool rightOnBlack = (rightValue == BLACK);
 
  Serial.print("Left:");
  Serial.print(leftValue);
  Serial.print(" Right:");
  Serial.print(rightValue);
  Serial.print(" -> ");
 
  // Both sensors on white
  if (!leftOnBlack && !rightOnBlack) {
    Serial.println("FORWARD");
    moveForward();
  }
 
  // Left sees line
  else if (leftOnBlack && !rightOnBlack) {
    Serial.println("TURN LEFT");
    turnLeft();
  }
 
  // Right sees line
  else if (!leftOnBlack && rightOnBlack) {
    Serial.println("TURN RIGHT");
    turnRight();
  }
 
  // Both on line (junction or lost)
  else {
    Serial.println("STOP");
    stopMotors();
  }
 
  delay(50);
}
 
 
// -------- Motor Functions --------
 
void moveForward() {
 
  analogWrite(ENA, motorSpeed);
  analogWrite(ENB, motorSpeed);
 
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
 
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}
 
void turnLeft() {
 
  analogWrite(ENA, motorSpeed / 2);
  analogWrite(ENB, motorSpeed);
 
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
 
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}
 
void turnRight() {
 
  analogWrite(ENA, motorSpeed);
  analogWrite(ENB, motorSpeed / 2);
 
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
 
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
 
void stopMotors() {
 
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
 
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}