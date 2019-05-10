# Combinar desafios

## RGB y Boton

Vamos a combinar dos desafios, RGB y Boton.
Vamos a utilizar el Boton para cambiar el color del led RGB.

Empezamos por analizar el hardware, que sera lo mas determinante, por que podemos encontrarnos con PINS fisicos del Arduino que estan siendo utilizados para distintas cosas y tengamos que modificar alguna conexion.

Boton usa los pins 2 y 13 y el RGB usa los pins 11, 12 y 13, asi que no tenemos ninguna moficicacion que hacer en ese frente.

Pasamos a mirar ahora el código de cada desafio y analizar su estructura.

![img](/rgbyboton/img/button_code_sections.png)

Primero tenemos las Definiciones de variables, señaladas en color verde.
Luego tenemos el Setup, en color amarillo.
Y por ultimo tenemos el Loop, en color rojo.

Ahora veamos la estructura del desafio RGB led:

![img](/rgbyboton/img/rgbled_code_sections.png)

La estructura es igual, definiciones de variables, setup y loop.

Para poder combinar estos desafios, debemos respetar estas estructuras,
Vamos a empezar creando un nuevo sketch en la IDE de Arduino:

![img](/rgbyboton/img/newsketch_sections.png)

Podemos ver que ya tenemos la estructura basica, un Setup y un Loop.

Vamos a empezar con el Setup, copiemos el del boton y debajo el del RGB led.

Recordá que los comentarios son opcionales, copialos si te parece que son necesarios y agrega los que quieras!

Deberiamos tener algo asi:

![img](/rgbyboton/img/newsketch_1_sections.png)

Ahora a empezar con el Loop, primero copiaremos el código del boton, que tiene el comportamiento basico que necesitamos (hacer algo cuando se pulse el boton).

![img](/rgbyboton/img/newsketch_2_sections.png)

El codigo dentro del loop ahora se divide en dos: Lo que sucede cuando se presiona el boton y lo que sucede cuando no se lo presiona:

![img](/rgbyboton/img/newsketch_3_sections.png)

Vamos a tomar el código del RGB y colocarlo dentro del IF (cuando esta presionado)

![img](/rgbyboton/img/newsketch_4_sections.png)

Podemos borrar el ELSE, ya que si el boton no esta presionado, no hacemos nada.

![img](/rgbyboton/img/newsketch_5_sections.png)

Solo nos faltan las definiciones de variables... Vamos a juntar las de ambas desafios en el nuevo sketch.

![img](/rgbyboton/img/newsketch_6_sections.png)

Perfecto, ahora vamos a limpiar el codigo de las cosas que no necesitamos, por ejemplo, podemos borrar la definicion de variable y el pinMode de "ledPin", ya que no lo necesitamos.

![img](/rgbyboton/img/newsketch_7_sections.png)


El código resultante deberia ser algo asi:

```
// las "constantes" no cambian, su usan aquí para
// definir los numeros de pin:
const int buttonPin = 2;     // el numero de pin del botón pulsador
// las "variables" cambian:
int buttonState = 0;         // variable para leer el estado del botón

int colorLed = 0;
int tiempoEspera = 1000; // Este es el tiempo que vamos a esperar entre color y color.
int red = 13; // Este es el numero del pin que conectaremos al pin rojo (red) del LED.
int green = 12; // Este es el numero del pin que conectaremos al pin verde (green) del LED.
int blue = 11; // Este es el numero del pin que conectaremos al pin azul (blue) del LED.

void setup() {
  // inicializa el pin del botón pulsador como entrada (INPUT):
  pinMode(buttonPin, INPUT);

  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
}

void loop() {
  // lee el estado del botón pulsador:
  buttonState = digitalRead(buttonPin);

  if (buttonState == HIGH) {
    colorLed = random(7); // random (aleatorio en ingles) es una funcion que devuelve un numero al azar, entre 0 y X.
    switch (colorLed) {
      case 0: // si el  colorLed es 0 entonces prendemos rojo
        digitalWrite(red, LOW);
        digitalWrite(green, HIGH);
        digitalWrite(blue, HIGH);
      break;

      case 6: // si el  colorLed es 6 entonces prendemos  blanco
        digitalWrite(blue, LOW);
        digitalWrite(red, LOW);
        digitalWrite(green, LOW);
      break;
    }
  delay(tiempoEspera);
  }
}
```
