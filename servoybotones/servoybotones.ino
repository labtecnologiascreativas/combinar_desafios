#include <Servo.h> // Incluimos la libreria Servo.h
Servo myservo;  // crea un objeto "servo" para controlar el servo motor
int pos = 0;    // en esta variable guardamos la posición del servo motor

const int button1Pin = 2;     // el numero de pin del botón pulsador
const int button2Pin = 3;     // el numero de pin del botón pulsador

int button1State = 0;         // variable para leer el estado del botón
int button2State = 0;         // variable para leer el estado del botón

void setup() {
  myservo.attach(9);  // conecta el servo conectado al pin 9 al objeto "servo"
  
  // inicializa el pin del botón pulsador como entrada (INPUT):
  pinMode(button1Pin, INPUT);
  pinMode(button2Pin, INPUT);
}

void loop() {
  // lee el estado del botón pulsador:
  button1State = digitalRead(button1Pin);
  button2State = digitalRead(button2Pin);

  if (button1State == HIGH) {
    myservo.write(180);
  }
  if (button2State == HIGH) {
    myservo.write(0);
  }
}
