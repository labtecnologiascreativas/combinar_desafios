# Combinar desafios

## Sensor Proximidad y RGB

Vamos a combinar dos desafios, Sensor Proximidad y RGB Led.
Vamos a utilizar el LED RGB para mostrar distintos colores segun la proximidad de un objeto al sensor.

Empezamos por analizar el hardware, que sera lo mas determinante, por que podemos encontrarnos con PINS fisicos del Arduino que estan siendo utilizados para distintas cosas y tengamos que modificar alguna conexion.

### Sensor proximidad

![img](/sensorproximidadyrgb/sensor_proximidad.png)

Vemos que utiliza 5V y GND para alimentar el sensor y los pins 8 y 7 para transmitir los datos.

### RGB LED

![img](/sensorproximidadyrgb/rgbled.png)

Utiliza 5V para alimentar el LED y los pins digitales para controlar los colores 13 (rojo), 12 (verde) y 11 (azul).

No tenemos ninguna moficicacion que hacer en ese frente, no hay conflictos, vamos a combinar los esquematicos:

Empezamos haciendo a un lado el Sensor, en lugar de conectar 5V y GND del Arduino, al sensor, vamos a conectarlos al protoboard y de alli llevarlos al sensor.

![img](/sensorproximidadyrgb/img/sensorproximidadyrgb_0.png)

De esta forma nos queda lugar para colocar el LED RGB, conectaremos la pata mas larga (positiva en nuestro caso) a 5V y los otros pins a sus correspondientes pins digitales (13, 12 y 11)

![img](/sensorproximidadyrgb/img/sensorproximidadyrgb_1.png)

Con esto la parte del hardware deberia estar resuelta.

Vamos ahora a ver los sketches de los desafios:

#### Sensor Proximidad

![img](/sensorproximidadyrgb/img/sensor_proximidad_sections.png)

La estructura de este desafio tiene una particularidad y es que define una funcion auxiliar, esta funcion auxiliar es utilizada dentro del loop y su finalidad es calcular la distancia en centimetros basandose en el tiempo que tardo el ultrasonido en captar el rebote de la onda emitida.

#### RGB LED

![img](/sensorproximidadyrgb/img/rgbled_sections.png)

Este desafio tiene la estructura basica, definicion de variables, setup y loop.
Vamos a comenzar con un sketch vacio:

#### Nuevo Sketch

Comenzamos con un nuevo sketch:

![img](/sensorproximidadyrgb/img/newsketch_0_sections.png)

Vamos a copiar primero las definiciones de variables de ambos desafios al nuevo sketch.

![img](/sensorproximidadyrgb/img/newsketch_1_sections.png)

Ahora vamos a copiar los setups de ambos desafios en el nuevo sketch:

![img](/sensorproximidadyrgb/img/newsketch_2_sections.png)

A continuacion vamos a copiar los loop al nuevo sketch.

![img](/sensorproximidadyrgb/img/newsketch_3_sections.png)

En la imagen pusimos solo los case 0 y 6 para que no sea tan extenso el código, al momento de llevar esto a la practica, debemos copiar todo el loop.

Ahora vamos a hacer unos pequeños ajustes al código para lograr nuestro cometido.
Vamos a eliminar el ultimo delay que copiamos del loop del sensor de proximidad
y tambien vamos a cambiar la primer linea del loop del RGB:

No queremos utilizar la aleatoriedad (random) para elegir el color que queremos mostrar, vamos a utilizar el valor que retorna la funcion microsecondsToCentimeters para calcular el color.

Para esto vamos a utilizar la funcion map en lugar de random para obtener el valor de la variable colorLed.

*NOTA: Explicar como y para que se utiliza la funcion map*

![img](/sensorproximidadyrgb/img/newsketch_4_sections.png)

Lo unico que nos falta ahora es copiar la funcion auxiliar del sensor de proximidad y agregarla al final del nuevo sketch:

![img](/sensorproximidadyrgb/img/newsketch_5_sections.png)

El código resultante deberia ser algo asi:

```
const int trigPin = 8;
const int echoPin= 7;

int colorLed = 0;
int tiempoEspera = 250; // Este es el tiempo que vamos a esperar entre color y color.
int red = 13; // Este es el numero del pin que conectaremos al pin rojo (red) del LED.
int green = 12; // Este es el numero del pin que conectaremos al pin verde (green) del LED.
int blue = 11; // Este es el numero del pin que conectaremos al pin azul (blue) del LED.

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
}

void loop() {
  long duration,cm;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  cm = microsecondsToCentimeters(duration);
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();

  colorLed = map(cm, 4, 42, 0 ,7);

  switch (colorLed) {
    case 0: // si el  colorLed es 0 entonces prendemos rojo
      digitalWrite(red, LOW);
      digitalWrite(green, HIGH);
      digitalWrite(blue, HIGH);
    break;

    case 1: // si el  colorLed es 1 entonces prendemos verde
      digitalWrite(green, LOW);
      digitalWrite(red, HIGH);
      digitalWrite(blue, HIGH);
    break;

    case 2: // si el  colorLed es 2 entonces prendemos azul
      digitalWrite(blue, LOW);
      digitalWrite(red, HIGH);
      digitalWrite(green, HIGH);
    break;

    case 3: // si el  colorLed es 3 entonces prendemos amarillo
      digitalWrite(red, LOW);
      digitalWrite(green, LOW);
      digitalWrite(blue, HIGH);
    break;

    case 4: // si el  colorLed es 4 entonces prendemos  cyan
      digitalWrite(blue, 0);
      digitalWrite(green, 0);
      digitalWrite(red, HIGH);
    break;

    case 5: // si el  colorLed es 5 entonces prendemos  magenta
      digitalWrite(red, LOW);
      digitalWrite(blue, LOW);
      digitalWrite(green, HIGH);
    break;

    case 6: // si el  colorLed es 6 entonces prendemos  blanco
      digitalWrite(blue, LOW);
      digitalWrite(red, LOW);
      digitalWrite(green, LOW);
    break;
  }
  delay(tiempoEspera);
}

long microsecondsToCentimeters(long microseconds) {
  return microseconds / 29 / 2;
}
```
