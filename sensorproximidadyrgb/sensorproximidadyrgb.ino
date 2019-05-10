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
