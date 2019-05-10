# Combinar desafios

## Motor y LDR

Vamos a combinar dos desafios: Motor y LDR.
Vamos a utilizar el LDR para controlar la valocidad del motor.

### Hardware

Empezamos por analizar el esquematico de ambos desafios y notar los pines que se ultilizan:

#### Motor:

![img](/motoryldr/motor.png)

Utiliza el puerto 1 del shield de motores.

#### LDR:

![img](/motoryldr/LDRySpeaker.png)

Utiliza los 5V y el GND para alimentar el LDR y el parlante.
Tambien utiliza los pins analogicos: El A0 esta conecta conectado al LDR y el A1 esta conectado al parlante.

Dado que no vamos a utilizar el parlante, podemos sacarlo, liberando el pin Analogico A0.

![img](/motoryldr/img/ldr_sinspeaker.png)

Debemos utilizar el shield, asi que desconectamos los cables del Arduino, coloquemos el shield y volvamos a conectar los cables, 5V, GND y ya que A0 ahora esta libre, vamos a conectar ahi nuestro LDR.

*NOTA: Muchos shields cuentan con mas pins de los que vienen "habilitados" cuando los compramos y necesitaremos soldar nosotros los "pins hembra" en los cuales podemos conectar para no perder funcionalidades de nuestro Arduino al conectar el shield.*

![img](/motoryldr/img/ldr_conshield.png)

Finalmente conectamos el motor en el puerto 1

![img](/motoryldr/motoryldr.png)

### Software

Vamos a ver la estructura del codigo de cada desafio primero y luego veremos como combinarlos para lograr nuestro objetivo.

#### Estructura del sketch Motor

![img](/motoryldr/img/motor_sections.png)


#### Estructura del sketch LDR

![img](/motoryldr/img/ldr_sections.png)


#### Nuevo sketch

Vamos a crear un nuevo sketch y comenzar por copiar las definiciones de variables y los includes de las librerias del motor:

*NOTA: Lo importante a la hora de combinar estos códigos es respetar a que seccion del codigo pertenecen.*

![img](/motoryldr/img/newsketch_0_sections.png)

<!-- Miremos ahora en detalle las definiciones de variables del código del LDR, la mayoria hacen referencia al parlante y la parte musical, nosotros solo necesitamos lo relacionado al LDR: -->

![img](/motoryldr/img/newsketch_1_sections.png)

Agregamos las definiciones a nuestro nuevo sketch:

![img](/motoryldr/img/newsketch_2_sections.png)

Ahora vamos con los setups de los desafios! El del Motor es facil, copiamos las dos lineas al nuevo sketch.

![img](/motoryldr/img/newsketch_3_sections.png)

En el LDR solo necesitamos el serial.begin() que nos servira para escribir valor en la consola serial.

![img](/motoryldr/img/monitor_serie_boton.png)

*NOTA: dentro de la IDE de Arduino. Tenemos la consola serial, que se abre clickeando el icono de la lupa en la esquina superior derecha de la aplicacion.
Esta consola es especialmente util para calibrar y detectar errores en nuestros programas.*

Asi nos deberia quedar el código con el nuevo setup:

![img](/motoryldr/img/newsketch_4_sections.png)

Pasemos ahora a la ultima seccion, el Loop.
Para lograr nuestro objetivo, necesitamos que el motor gire constantemente y que podamos controlar su velocidad con el LDR.
Asi que vamos a empezar por ubicar las partes del código del loop del LDR que se encargan de obtener el valor sensado:

![img](/motoryldr/img/newsketch_6_sections.png)

Ahora veamos el loop del motor, necesitamos encontrar lo que hace que el motor gire!

![img](/motoryldr/img/newsketch_5_sections.png)

Combinemos ambos códigos en nuestro nuevo sketch:

![img](/motoryldr/img/newsketch_7_sections.png)

*NOTA: La funcion Map se utiliza frecuentemente para "normalizar" valores. en este caso, el LDR mide valores que van entre 380 y 980. Y la velocidad del motor se controla con valores entre 0 y 255, para resolver esta conversion que debemos realizar, utilizamos la funcion map().*

![img](/motoryldr/img/newsketch_8_sections.png)

Necesitamos definir una nueva variable que contenga el valor "normalizado" del LDR, podriamos llamarla "valorSensor".

![img](/motoryldr/img/newsketch_9_sections.png)

Vamos a mover el "motor.speed()" que tenemos en el setup y lo vamos a ubicar justo luego de normalizar el valor del LDR y lo utilizaremos como parametro para indicar la velocidad.

![img](/motoryldr/img/newsketch_10_sections.png)

Luego de refactorizar un poco, el código queda asi:

```
// Adafruit Motor shield library
// copyright Adafruit Industries LLC, 2009
// Este código de ejemplo es de dominio público, que lo disfrutes!

// Incluimos la librería
#include <AFMotor.h>

// Crea el objeto Motor y selecciona e  l 'puerto' ('port' en inglés) M1, M2, M3 or M4. En este caso, M1
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
```
