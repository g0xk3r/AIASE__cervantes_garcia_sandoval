// Práctica 1 · Superlazo no bloqueante con dos tareas periódicas
const int LED_PIN = 2;                 // LED externo / GPIO 2
const uint32_t T_LED_MS = 250;         // 2 Hz: cambia cada 250 ms
const uint32_t T_REPORTE_MS = 1000;    // 1 Hz

uint32_t tLed = 0, tReporte = 0;
uint32_t iteraciones = 0;
bool ledEncendido = false;

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  uint32_t ahora = millis();
  iteraciones++;

  if (ahora - tLed >= T_LED_MS) {      // resta sin signo: válida aun con desbordamiento
    tLed += T_LED_MS;                  // pregunta 3: ¿por qué no tLed = ahora?
    ledEncendido = !ledEncendido;
    digitalWrite(LED_PIN, ledEncendido ? HIGH : LOW);
  }

  if (ahora - tReporte >= T_REPORTE_MS) {
    tReporte += T_REPORTE_MS;
    // TODO hecho: imprime t (ms), iteraciones del último segundo y heap; reinicia contador
    Serial.printf("t=%lu ms  iter/s=%lu  heap=%lu\n",
                  (unsigned long)ahora,
                  (unsigned long)iteraciones,
                  (unsigned long)ESP.getFreeHeap());
    iteraciones = 0;
  }

  // TODO (Parte B, paso 3) hecho — medir efecto y dejar comentado:
  // (a) tal cual → ~765 965 iter/s
  // (b) delay(1) → ~1 000 iter/s
  // (c) Serial.printf("x") cada iteración → ~11 573 iter/s
  // delay(1);
  // Serial.printf("x");
}
