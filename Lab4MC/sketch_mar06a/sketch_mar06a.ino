//in1 - left forward
//in2 - left back
//in3 - right forward
//in4 - right back
#define enA 5
#define enB 6
#define in1 7
#define in2 8
#define in3 11
#define in4 9

void setup() {
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

void moveForward() {
  analogWrite(enA, 255);   
  analogWrite(enB, 255);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW); 
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void moveBack() {
  analogWrite(enA, 255);   
  analogWrite(enB, 255);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH); 
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

void rotateLeft() {
  analogWrite(enA, 255);   
  analogWrite(enB, 255);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

void rotateRight() {
  analogWrite(enA, 255);   
  analogWrite(enB, 255);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

void stopCar() {
  analogWrite(enA, 255);   
  analogWrite(enB, 255);
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

void moveByExactWay() {
  moveForward();
  delay(2500);
  rotateLeft();
  delay(900);
  moveForward();
  delay(1500);
  rotateLeft();
  delay(1650);
}

void loop() {
  moveByExactWay();
}
