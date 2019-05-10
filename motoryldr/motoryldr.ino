// Adafruit Motor shield library
// copyright Adafruit Industries LLC, 2009
// Este código de ejemplo es de dominio público, que lo disfrutes!

// Incluimos la librería
#include <AFMotor.h>

// Crea el objeto Motor y selecciona el 'puerto' ('port' en inglés) M1, M2, M3 or M4. En este caso, M1
AF_DCMotor motor(1);
int sensorLDR = A0; // Donde conectaremos el sensor LDR.
int valorSensorLDR = 0; // Almacena el ultimo valor leido del sensor.
int valorSensor = 0; // Almacena el ultimo valor leido del sensor.


void setup() {
 // Prendemos el motor
  motor.run(RELEASE);
  Serial.begin(9600);
  pinMode(sensorLDR, INPUT);
}

void loop() {
  valorSensorLDR = analogRead(sensorLDR);
  valorSensor = map(valorSensorLDR, 50 , 1000, 0 , 255); 
  Serial.println(valorSensor);
  motor.setSpeed(valorSensor);
  motor.run(FORWARD);
  delay(10);
}
