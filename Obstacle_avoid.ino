#include <Servo.h>
#include <NewPing.h>

//Ultrasonic
#define TRIG_PIN      9
#define ECHO_PIN      10
#define MAX_DISTANCE  200
NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE);

//Servo
Servo scanServo;
#define SERVO_PIN     6

// Motor Pins (IN1-IN8, EN tied to 5V)
// Left  Front: IN1, IN2
// Right Front: IN3, IN4
// Left  Rear:  IN5, IN6
// Right Rear:  IN7, IN8
#define IN1  2
#define IN2  3
#define IN3  4
#define IN4  5
#define IN5  7
#define IN6  8
#define IN7  11
#define IN8  12

#define OBSTACLE_DIST 30

void setup() {
  Serial.begin(9600);

  pinMode(IN1, OUTPUT); pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT); pinMode(IN4, OUTPUT);
  pinMode(IN5, OUTPUT); pinMode(IN6, OUTPUT);
  pinMode(IN7, OUTPUT); pinMode(IN8, OUTPUT);

  scanServo.attach(SERVO_PIN);
  scanServo.write(90);
  delay(500);
}

void loop() {
  int dist = sonar.ping_cm();
  if (dist == 0) dist = 999; // 0 means no echo = clear
  Serial.print("Distance: "); Serial.println(dist);

  if (dist < OBSTACLE_DIST) {
    // STOP
    digitalWrite(IN1, LOW); digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW); digitalWrite(IN4, LOW);
    digitalWrite(IN5, LOW); digitalWrite(IN6, LOW);
    digitalWrite(IN7, LOW); digitalWrite(IN8, LOW);
    delay(200);

    // SCAN LEFT
    scanServo.write(0);
    delay(600);
    int leftDist = sonar.ping_cm();
    if (leftDist == 0) leftDist = 999;

    // SCAN RIGHT
    scanServo.write(180);
    delay(600);
    int rightDist = sonar.ping_cm();
    if (rightDist == 0) rightDist = 999;

    // RETURN SERVO TO CENTER
    scanServo.write(90);
    delay(300);

    Serial.print("Left: "); Serial.print(leftDist);
    Serial.print(" | Right: "); Serial.println(rightDist);

    // BOTH BLOCKED → REVERSE
    if (leftDist < OBSTACLE_DIST && rightDist < OBSTACLE_DIST) {
      digitalWrite(IN1, LOW);  digitalWrite(IN2, HIGH);
      digitalWrite(IN3, LOW);  digitalWrite(IN4, HIGH);
      digitalWrite(IN5, LOW);  digitalWrite(IN6, HIGH);
      digitalWrite(IN7, LOW);  digitalWrite(IN8, HIGH);
      delay(700);
      digitalWrite(IN1, LOW); digitalWrite(IN2, LOW);
      digitalWrite(IN3, LOW); digitalWrite(IN4, LOW);
      digitalWrite(IN5, LOW); digitalWrite(IN6, LOW);
      digitalWrite(IN7, LOW); digitalWrite(IN8, LOW);
      delay(200);
    }

    if (leftDist > rightDist) {
      // TURN LEFT
      // Left  motors backward, Right motors forward
      digitalWrite(IN1, LOW);  digitalWrite(IN2, HIGH);
      digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
      digitalWrite(IN5, LOW);  digitalWrite(IN6, HIGH);
      digitalWrite(IN7, HIGH); digitalWrite(IN8, LOW);
    } else {
      // TURN RIGHT
      // Left  motors forward, Right motors backward
      digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
      digitalWrite(IN3, LOW);  digitalWrite(IN4, HIGH);
      digitalWrite(IN5, HIGH); digitalWrite(IN6, LOW);
      digitalWrite(IN7, LOW);  digitalWrite(IN8, HIGH);
    }
    delay(400);

    // STOP AFTER TURN
    digitalWrite(IN1, LOW); digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW); digitalWrite(IN4, LOW);
    digitalWrite(IN5, LOW); digitalWrite(IN6, LOW);
    digitalWrite(IN7, LOW); digitalWrite(IN8, LOW);
    delay(100);

  } else {
    // FORWARD
    digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
    digitalWrite(IN5, HIGH); digitalWrite(IN6, LOW);
    digitalWrite(IN7, HIGH); digitalWrite(IN8, LOW);
  }
}