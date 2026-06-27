int coilL = A0;
int coilR = A2;
int motorL = 10;
int motorR = 9;

int baseSpeed = 160;      // forward speed
float Kp = 1.2;           // steering strength
int tolerance = 50;       // ignore small sensor noise

void setup() {
  pinMode(motorL, OUTPUT);
  pinMode(motorR, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int leftSignal = analogRead(coilL);
  int rightSignal = analogRead(coilR);

  int error = leftSignal - rightSignal;

  if (abs(error) < tolerance) {
    error = 0;
  }

  int correction = error * Kp;

  int speedL = constrain(baseSpeed - correction, 0, 255);
  int speedR = constrain(baseSpeed + correction, 0, 255);

  analogWrite(motorL, speedL);
  analogWrite(motorR, speedR);

  Serial.print("Left: ");
  Serial.print(leftSignal);
  Serial.print(" Right: ");
  Serial.print(rightSignal);
  Serial.print(" Error: ");
  Serial.println(error);
}
