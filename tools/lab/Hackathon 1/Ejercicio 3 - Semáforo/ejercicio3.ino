// Semaforo 


// pines donde estan conectados los leds
const int led_verde = 18;
const int led_amarillo = 19;
const int led_rojo = 21;


const int boton = 23;
const int buzzer = 5;


// estados posibles del semaforo
enum Estado { VERDE, AMARILLO, ROJO };

// estado actual del semaforo
Estado estado = VERDE;

// guarda momento en que inicio el estado actual
unsigned long t_inicio = 0;

unsigned long t_boton = 0;
bool peaton = false;
int lectura_ant = HIGH;

const int debounce = 30;


const unsigned long t_verde = 5000;
const unsigned long t_amarillo = 2000;
const unsigned long t_rojo = 5000;
const unsigned long t_rojo_peaton = 8000;

void setup() {
  
  pinMode(led_verde, OUTPUT);
  pinMode(led_amarillo, OUTPUT);
  pinMode(led_rojo, OUTPUT);
  pinMode(boton, INPUT_PULLUP);
  // buzzer como salida
  pinMode(buzzer, OUTPUT);

  
  t_inicio = millis();
}

void loop() {
 
  leerBoton();
  actualizarSemaforo();
  actualizarLeds();
  sonidoPeaton();
}

// detecta presion del boton 
void leerBoton() {
  int lectura = digitalRead(boton);
  unsigned long ahora = millis();

  // detecta cambio en lectura
  if (lectura != lectura_ant) {
    t_boton = ahora;
    lectura_ant = lectura;
  }

  // confirma lectura estable
  if ((ahora - t_boton) > debounce && lectura == LOW) {
    peaton = true;
  }
}

// cambia estado del semaforo segun tiempo transcurrido
void actualizarSemaforo() {
  unsigned long ahora = millis();

  // determina cuanto dura el estado actual
  unsigned long duracion =
    (estado == VERDE) ? t_verde :
    (estado == AMARILLO) ? t_amarillo :
    (peaton ? t_rojo_peaton : t_rojo);

  // cambia al siguiente estado si se cumplio tiempo
  if (ahora - t_inicio >= duracion) {
    if (estado == VERDE) {
      estado = AMARILLO;
    } else if (estado == AMARILLO) {
      estado = ROJO;
    } else {
      estado = VERDE;
      peaton = false;
    }

    t_inicio = ahora;
  }
}

// enciende el led correspondiente al estado
void actualizarLeds() {
  digitalWrite(led_verde, estado == VERDE);
  digitalWrite(led_amarillo, estado == AMARILLO);
  digitalWrite(led_rojo, estado == ROJO);
}

// sonido
void sonidoPeaton() {

  // si no esta en rojo o no hay solicitud se apaga sonido
  if (estado != ROJO || !peaton) {
    noTone(buzzer);
    return;
  }

  // calcula cuanto tiempo lleva en rojo
  unsigned long tiempo_en_rojo = millis() - t_inicio;

  // sonido lento al inicio del cruce
  if (tiempo_en_rojo < 5000) {
    tone(buzzer, 2000);
    delay(200);
    noTone(buzzer);
    delay(300);
  }
  // sonido rapido cuando esta por terminar
  else {
    tone(buzzer, 2000);
    delay(80);
    noTone(buzzer);
    delay(120);
  }
}