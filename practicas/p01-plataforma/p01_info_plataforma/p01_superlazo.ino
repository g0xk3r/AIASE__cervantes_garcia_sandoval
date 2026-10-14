// Práctica 1 · Superlazo no bloqueante con dos tareas periódicas
const int LED_PIN = 2; // LED de usuario (GPIO 2 en muchas DevKit)
const uint32_t T_LED_MS = 250; // 2 Hz: el LED cambia de estado cada 250 ms
const uint32_t T_REPORTE_MS = 1000; // 1 Hz

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

  if (ahora - tLed >= T_LED_MS) { // resta sin signo: válida aun con desbordamiento
  tLed += T_LED_MS; // pregunta 3: ¿por qué no tLed = ahora?
  ledEncendido = !ledEncendido;
  digitalWrite(LED_PIN, ledEncendido ? HIGH : LOW);
  }

  if (ahora - tReporte >= T_REPORTE_MS) {
    tReporte += T_REPORTE_MS;
    // TODO: imprime t (ms), iteraciones del último segundo y ESP.getFreeHeap();
    // después reinicia el contador de iteraciones
  }
  // TODO (Parte B, paso 3): mide el efecto de agregar aquí delay(1) y, después,
  // un Serial.printf en cada iteración
}