// ECG con AD8232 + Arduino Uno
// Envía una muestra por línea a 250 Hz por el puerto serial (115200 baudios).
// Si los electrodos están sueltos envía "!" en lugar del valor.
//
// Conexiones:
//   AD8232 OUTPUT -> A0
//   AD8232 LO-    -> D11
//   AD8232 LO+    -> D10
//   AD8232 3.3V   -> 3.3V
//   AD8232 GND    -> GND

const int ECG_PIN = A0;
const int LO_PLUS = 10;
const int LO_MINUS = 11;

const unsigned long PERIODO_US = 4000;  // 4000 us = 250 muestras por segundo
unsigned long siguiente;

void setup() {
  Serial.begin(115200);
  pinMode(LO_PLUS, INPUT);
  pinMode(LO_MINUS, INPUT);
  siguiente = micros();
}

void loop() {
  if ((long)(micros() - siguiente) >= 0) {
    siguiente += PERIODO_US;

    if (digitalRead(LO_PLUS) == HIGH || digitalRead(LO_MINUS) == HIGH) {
      Serial.println("!");
    } else {
      Serial.println(analogRead(ECG_PIN));
    }
  }
}
