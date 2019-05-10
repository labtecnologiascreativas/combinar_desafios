# Combinar desafios

## Servo y Botones

Vamos a combinar dos desafios, Servo y Boton (2 botones!).
Vamos a utilizar los botones para hacer que el servo se mueva hacia un lado y hacia el otro.

Empezamos por analizar el hardware, que sera lo mas determinante, por que podemos encontrarnos con PINS fisicos del Arduino que estan siendo utilizados para distintas cosas y tengamos que modificar alguna conexion.

Boton usa los pins 2 y 13 y el Servo usa el pin 9, asi que no tenemos ninguna moficicacion que hacer en ese frente.

Vamos a empezar con el esquematico del servo, vemos que utiliza 5V, GND y PIN 9, conectados directamente al Arduino.

![img](/servoybotones/img/servoybotones_0.png)

Tomamos la protoboard y colocamos los dos botones.

![img](/servoybotones/img/servoybotones_1.png)

En lugar de conectar el servo directamente el Arduino, vamos a conectar primero el 5V y el GND del Arduino en la protoboard y ahi mismo conectaremos el servo. De esta forma alimentamos el servo y podemos tambien alimentar los botones!

*NOTA: Explicar como funciona un boton*

Colocaremos una resistencia de 10K conectando uno de los pins del boton a la tierra.
Conectamos el otro pin del boton a 5v.
<!--  -->
![img](/servoybotones/img/servoybotones_2.png)

Vamos a conectar el primer boton al pin 2 y el segundo boton al pin 3.

![img](/servoybotones/img/servoybotones_3.png)

Con esto la parte del hardware deberia estar resuelta.

Vamos ahora a ver los sketches de los desafios:

#### Boton

![img](/servoybotones/img/button_code_sections.png)

#### Servo

![img](/servoybotones/img/servo_sections.png)

#### Nuevo Sketch

Comenzamos con un nuevo sketch:

![img](/servoybotones/img/newsketch_0_sections.png)

Vamos a copiar primero las definiciones de variables y la importacion de la libreria del Servo.
A continuacion, copiamos las definiciones de variables del boton, ignorando la linea que hace referencia al led.

![img](/servoybotones/img/newsketch_1_sections.png)

Ahora hacemos lo mismo con los setups.
Copiamos la inicializacion del servo y el pinMode del boton.

![img](/servoybotones/img/newsketch_2_sections.png)

Continuamos con el Loop. Empezamos por el del boton que tiene la estructura basica que necesitamos (hacer algo cuando se presiona el boton)

![img](/servoybotones/img/newsketch_3_sections.png)

Ahora vamos a identificar las linease que hacen que el servo se mueva en el otro sketch...

![img](/servoybotones/img/newsketch_4_sections.png)

myservo.write(pos);

hace que el servo se mueva hasta la posicion que le indicamos en grados.

Vamos ahora a hacer que cuando pulsamos el boton, el servo se mueva a posicion 180°

![img](/servoybotones/img/newsketch_5_sections.png)

Bien! Ahora nos falta duplicar algunas lineas para implementar el segundo boton:

![img](/servoybotones/newsketch_6_sections.png)


El código resultante deberia ser algo asi:

```
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
```
