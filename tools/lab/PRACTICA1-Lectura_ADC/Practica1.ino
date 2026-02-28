/*
Potenciómetro:
1->GND
2->35
3->3.3V

FOTORESISTENCIA
1->3.3V
2-> COLUMNA 22( CABLE(34), RESISTENCIA)

RESISTENCIA 1K
1->Fotoresistencia
2->GND

*/


const int PIN_POT = 35;
const int PIN_LDR = 34;

const float REF_VOLTAGE = 3.3;
const float POT_MAX_R = 50000.0;

void setup() {
  Serial.begin(115200);
  analogReadResolution(12);
  Serial.println("--- POTENCIOMETRO Y LUZ ---");
}

void loop() {

  // POTENCIÓMETRO
  int potAdc = analogRead(PIN_POT);
  float potVolts = (potAdc * REF_VOLTAGE) / 4095.0;
  float potResistance = (potVolts / REF_VOLTAGE) * POT_MAX_R;

  delay(10);

  // LDR
  int ldrAdc = analogRead(PIN_LDR);
  float lightPercent = (ldrAdc * 100.0) / 4095.0;
  // int lightPercent = map(ldrAdc, 0, 4095, 0, 100);


  // SALIDA
  Serial.print("POTENCIÓMETRO -> ADC: ");
  Serial.print(potAdc);
  Serial.print(" | V: ");
  Serial.print(potVolts, 2);
  Serial.print(" V | R: ");
  Serial.print(potResistance, 0);
  Serial.print(" Ohms");

  Serial.print("   ||   ");

  Serial.print("LUZ -> ADC: ");
  Serial.print(ldrAdc);
  Serial.print(" | ");
  Serial.print(lightPercent, 2);
  Serial.println(" %");

  delay(500);
}