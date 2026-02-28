// --- 1. CONFIGURACIÓN DE PINES ---
const int PIN_BTN_A = 13;
const int PIN_BTN_B = 12;
const int PIN_BTN_C = 14;
const int PIN_BTN_D = 27;
const int PIN_RESET = 26;

const int PIN_LED_A = 19;
const int PIN_LED_B = 18;
const int PIN_LED_C = 5;
const int PIN_LED_D = 17;

// --- 2. CONSTANTES DE TIEMPO ---
const unsigned long TIEMPO_ESPERA_VOTO = 3000; 
const unsigned long TIEMPO_PARPADEO = 300; 

// --- 3. VARIABLES DE ESTADO ---
int votosA = 0;
int votosB = 0;
int votosC = 0;
int votosD = 0;

unsigned long ultimaVezParpadeo = 0;
bool estadoLedParpadeo = LOW; 

struct Boton {
  int pin;                
  int estadoAnterior;     
  unsigned long ultimaVezPresionado; 
};

Boton btnA = {PIN_BTN_A, HIGH, 0};
Boton btnB = {PIN_BTN_B, HIGH, 0};
Boton btnC = {PIN_BTN_C, HIGH, 0};
Boton btnD = {PIN_BTN_D, HIGH, 0};
Boton btnReset = {PIN_RESET, HIGH, 0};


bool fuePresionado(Boton &b);
void verificarVotos();
void verificarReset();
void actualizarLeds();

void setup() {
  Serial.begin(115200);
  
  pinMode(PIN_BTN_A, INPUT_PULLUP);
  pinMode(PIN_BTN_B, INPUT_PULLUP);
  pinMode(PIN_BTN_C, INPUT_PULLUP);
  pinMode(PIN_BTN_D, INPUT_PULLUP);
  pinMode(PIN_RESET, INPUT_PULLUP);

  pinMode(PIN_LED_A, OUTPUT);
  pinMode(PIN_LED_B, OUTPUT);
  pinMode(PIN_LED_C, OUTPUT);
  pinMode(PIN_LED_D, OUTPUT);
}

void loop() {
  verificarVotos();
  verificarReset();
  actualizarLeds();
}

// --- 4. FUNCIÓN CON BLOQUEO DE 3 SEGUNDOS ---
bool fuePresionado(Boton &b) {
  int lecturaActual = digitalRead(b.pin); 
  bool votoValido = false;

  // 1. Detectar si se presiono
  if (lecturaActual == LOW && b.estadoAnterior == HIGH) {
    
    // 2. REGLA DE3 seg para bloquear el voto
    if (millis() - b.ultimaVezPresionado > TIEMPO_ESPERA_VOTO) {
      
      votoValido = true;
      b.ultimaVezPresionado = millis();
      Serial.println(">> Voto Aceptado (no se puede votar por 3 seg...)");
      
    } 
  }

  b.estadoAnterior = lecturaActual; 
  return votoValido;
}

void verificarVotos() {
  if (fuePresionado(btnA)) { votosA++; Serial.print("Total A: "); Serial.println(votosA); }
  if (fuePresionado(btnB)) { votosB++; Serial.print("Total B: "); Serial.println(votosB); }
  if (fuePresionado(btnC)) { votosC++; Serial.print("Total C: "); Serial.println(votosC); }
  if (fuePresionado(btnD)) { votosD++; Serial.print("Total D: "); Serial.println(votosD); }
}

void verificarReset() {
  if (fuePresionado(btnReset)) {
    votosA = 0; votosB = 0; votosC = 0; votosD = 0;
    Serial.println("--- RESET ---");
    digitalWrite(PIN_LED_A, LOW); digitalWrite(PIN_LED_B, LOW);
    digitalWrite(PIN_LED_C, LOW); digitalWrite(PIN_LED_D, LOW);
  }
}

void actualizarLeds() {
  int maxVotos = votosA;
  if (votosB > maxVotos) maxVotos = votosB;
  if (votosC > maxVotos) maxVotos = votosC;
  if (votosD > maxVotos) maxVotos = votosD;

  if (maxVotos == 0) return; 

  int cantidadGanadores = 0;
  if (votosA == maxVotos) cantidadGanadores++;
  if (votosB == maxVotos) cantidadGanadores++;
  if (votosC == maxVotos) cantidadGanadores++;
  if (votosD == maxVotos) cantidadGanadores++;

  unsigned long tiempoActual = millis();
  if (tiempoActual - ultimaVezParpadeo >= TIEMPO_PARPADEO) {
    ultimaVezParpadeo = tiempoActual;
    estadoLedParpadeo = !estadoLedParpadeo;
  }

  if (cantidadGanadores > 1) { 
    digitalWrite(PIN_LED_A, (votosA == maxVotos) ? estadoLedParpadeo : LOW);
    digitalWrite(PIN_LED_B, (votosB == maxVotos) ? estadoLedParpadeo : LOW);
    digitalWrite(PIN_LED_C, (votosC == maxVotos) ? estadoLedParpadeo : LOW);
    digitalWrite(PIN_LED_D, (votosD == maxVotos) ? estadoLedParpadeo : LOW);
  } else { 
    digitalWrite(PIN_LED_A, (votosA == maxVotos) ? HIGH : LOW);
    digitalWrite(PIN_LED_B, (votosB == maxVotos) ? HIGH : LOW);
    digitalWrite(PIN_LED_C, (votosC == maxVotos) ? HIGH : LOW);
    digitalWrite(PIN_LED_D, (votosD == maxVotos) ? HIGH : LOW);
  }
}