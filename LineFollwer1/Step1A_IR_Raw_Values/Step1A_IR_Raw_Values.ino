// ==========================================================
//  LINE FOLLOWER - PART 1 : STEP 1B
//  Detect the black line with BOTH IR sensors and print
//  a clear message in the Serial Monitor.
//
//  Wiring is the SAME as Step 1A:
//    Left  IR OUT  -> GPIO 34
//    Right IR OUT  -> GPIO 35
//
//  Open Serial Monitor at 115200 baud.
// ==========================================================
 
const int LEFT_SENSOR  = 34;
const int RIGHT_SENSOR = 35;
 
// ----------------------------------------------------------
//  CALIBRATION SETTING  (VERY IMPORTANT)
//  Write here the value YOUR sensor showed on BLACK tape
//  in Step 1A.
//    Most sensors  : 1 on black, 0 on white  -> BLACK = 1
//    Inverted ones : 0 on black, 1 on white  -> BLACK = 0
//  You will copy this same line into every later sketch.
// ----------------------------------------------------------
const int BLACK = 1;
 
void setup() {
  Serial.begin(115200);
 
  pinMode(LEFT_SENSOR, INPUT);
  pinMode(RIGHT_SENSOR, INPUT);
 
  delay(500);
  Serial.println();
  Serial.println("STEP 1B : Line detection test");
  Serial.print("Calibration: BLACK = ");
  Serial.println(BLACK);
  Serial.println("----------------------------------------------------------------");
}
 
void loop() {
  int leftValue  = digitalRead(LEFT_SENSOR);
  int rightValue = digitalRead(RIGHT_SENSOR);
 
  bool leftOnBlack  = (leftValue  == BLACK);
  bool rightOnBlack = (rightValue == BLACK);
 
  // Print the raw numbers first
  Serial.print("L:");
  Serial.print(leftValue);
  Serial.print(" R:");
  Serial.print(rightValue);
  Serial.print("  ->  ");
 
  // Then print what it means
  if (leftOnBlack && rightOnBlack) {
    Serial.println("BOTH IR detecting BLACK");
  }
  else if (leftOnBlack) {
    Serial.println("LEFT IR detecting BLACK   (only one sensor on the line)");
  }
  else if (rightOnBlack) {
    Serial.println("RIGHT IR detecting BLACK  (only one sensor on the line)");
  }
  else {
    Serial.println("BOTH IR on WHITE          (line is between the sensors)");
  }
 
  delay(200);
}