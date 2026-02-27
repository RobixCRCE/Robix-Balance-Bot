// Motor pins
#define IN1 8
#define IN2 7
#define IN3 5
#define IN4 4
#define ENA 11
#define ENB 6

// Ultrasonic Left (Downward-Facing)
#define TRIG_L 9
#define ECHO_L 10

// Ultrasonic Right (Downward-Facing)
#define TRIG_R 2
#define ECHO_R 3

// Balancing constants
const int targetDist = 5; // Adjust as needed; distance in cm from ground
const int threshold = 1;  // Deadzone for balancing in cm

void setup() {
  // Motor pin setup
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  // Ultrasonic pin setup
  pinMode(TRIG_L, OUTPUT);
  pinMode(ECHO_L, INPUT);
  pinMode(TRIG_R, OUTPUT);
  pinMode(ECHO_R, INPUT);

  Serial.begin(9600);
}

// Distance measurement function
long measureDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 30000); // Timeout 30ms
  // Convert to cm
  long distance = duration * 0.034 / 2;
  return distance;
}

void setMotor(int leftSpeed, int rightSpeed) {
  // Direction control
  if (leftSpeed > 0) {
    digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  } else if (leftSpeed < 0) {
    digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);
  } else {
    digitalWrite(IN1, LOW); digitalWrite(IN2, LOW);
  }
  if (rightSpeed > 0) {
    digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
  } else if (rightSpeed < 0) {
    digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);
  } else {
    digitalWrite(IN3, LOW); digitalWrite(IN4, LOW);
  }
  analogWrite(ENA, min(abs(leftSpeed), 255));
  analogWrite(ENB, min(abs(rightSpeed), 255));
}

void loop() {
  long leftDist = measureDistance(TRIG_L, ECHO_L);
  long rightDist = measureDistance(TRIG_R, ECHO_R);

  int error = (leftDist - rightDist);

  int baseSpeed = 25;   // Adjust for minimal movement
  int correction = error * 30; // Proportional control, adjust gain '30' as needed

  int leftSpeed = baseSpeed - correction;
  int rightSpeed = baseSpeed + correction;

  // Maintain both within target range
  if (abs(leftDist - targetDist) < threshold && abs(rightDist - targetDist) < threshold) {
    setMotor(0, 0); // Balanced; stop motors
  } else {
    setMotor(leftSpeed, rightSpeed);
  }

  Serial.print("L: "); Serial.print(leftDist);
  Serial.print(" R: "); Serial.print(rightDist);
  Serial.print(" E: "); Serial.println(error);

  delay(30); // Tune as necessary for your hardware
}