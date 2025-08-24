#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;

#define TRIG_PIN 2
#define ECHO_PIN 3
#define IR_PIN 4
#define WATER_PIN A0
#define BUZZER_PIN 10  // Arduino pin for buzzer

// Thresholds
#define OBSTACLE_DISTANCE 30   // cm
#define WATER_THRESHOLD 300    // adjust based on sensor
#define FALL_THRESHOLD 40000   // accelerometer magnitude (adjust to reduce false alerts)

int fallCounter = 0; // debounce counter for accelerometer

void setup() {
  Serial.begin(9600);

  // Ultrasonic
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  // IR
  pinMode(IR_PIN, INPUT);

  // Water sensor
  pinMode(WATER_PIN, INPUT);

  // Buzzer
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW); // start with buzzer OFF

  // MPU6050
  Wire.begin();
  mpu.initialize();
  if(!mpu.testConnection()){
    Serial.println("MPU6050 connection failed!");
  } else {
    Serial.println("MPU6050 ready");
  }
}

long readUltrasonicDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH);
  long distance = duration * 0.034 / 2; // cm
  return distance;
}

bool checkFall() {
  int16_t ax, ay, az;
  mpu.getAcceleration(&ax, &ay, &az);
  long magnitude = ax*ax + ay*ay + az*az - (16384*16384); // subtract gravity
  return magnitude > FALL_THRESHOLD;
}

bool checkFallDebounced() {
  bool currentFall = checkFall();
  if(currentFall){
    fallCounter++;
  } else {
    fallCounter = 0;
  }
  return fallCounter >= 2; // require 2 consecutive detections
}

void loop() {
  bool alert = false;  // flag to check if any sensor triggers

  // 1️⃣ Ultrasonic
  long distance = readUltrasonicDistance();
  if(distance > 0 && distance < OBSTACLE_DISTANCE){
    Serial.println("Obstacle detected by Ultrasonic!");
    alert = true;
  }

  // 2️⃣ IR
  if(digitalRead(IR_PIN) == LOW){ // LOW usually means obstacle
    Serial.println("Obstacle detected by IR!");
    alert = true;
  }

  // 3️⃣ Water
  int waterVal = analogRead(WATER_PIN);
  if(waterVal > WATER_THRESHOLD){
    Serial.println("Water detected!");
    alert = true;
  }

  // 4️⃣ Fall
  if(checkFallDebounced()){
    Serial.println("Fall detected!");
    alert = true;
  }

  // 5️⃣ Trigger buzzer if any alert
  if(alert){
    digitalWrite(BUZZER_PIN, HIGH); // buzzer ON
  } else {
    digitalWrite(BUZZER_PIN, LOW);  // buzzer OFF
  }

  delay(200); // small delay
}
