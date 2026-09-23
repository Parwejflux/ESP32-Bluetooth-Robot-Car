#include "BluetoothSerial.h"

BluetoothSerial SerialBT;

#define IN1 12
#define IN2 13
#define IN3 27
#define IN4 14
#define ENA 25
#define ENB 26

int valSpeed = 255;

void setSpeed(int speedVal) {
  speedVal = constrain(speedVal, 0, 255);
  analogWrite(ENA, speedVal);
  analogWrite(ENB, speedVal);
}

void stopMotors() {
  digitalWrite(IN1, LOW); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW); digitalWrite(IN4, LOW);
  analogWrite(ENA, 0); analogWrite(ENB, 0);
}

void forward() {
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
  setSpeed(valSpeed);
}

void backward() {
  digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);
  setSpeed(valSpeed);
}

void left() {
  digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
  setSpeed(valSpeed);
}

void right() {
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);
  setSpeed(valSpeed);
}

void setup() {
  pinMode(IN1, OUTPUT); pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT); pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT); pinMode(ENB, OUTPUT);
  Serial.begin(115200);
  SerialBT.begin("ESP32_RC_Car");
  stopMotors();
}

void loop() {
  if (SerialBT.available()) {
    char command = SerialBT.read();
    switch (command) {
      case 'F': case 'f': forward(); break;
      case 'B': case 'b': backward(); break;
      case 'L': case 'l': left(); break;
      case 'R': case 'r': right(); break;
      case 'S': case 's': stopMotors(); break;
    }
  }
}
