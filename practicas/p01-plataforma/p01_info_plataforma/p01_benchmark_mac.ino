// Práctica 1 · Costo de y = Σ w[i]·x[i] en float32 e int8 a distintas frecuencias de CPU
const int N = 1024; // longitud del vector (prueba también 256 y 4096)
const int REPS = 1000; // repeticiones para promediar

float wf[N], xf[N];
int8_t wq[N], xq[N];
volatile float sumideroF; // 'volatile': el compilador no puede descartar el resultado
volatile int32_t sumideroQ;

__attribute__((noinline)) float macFloat() {
float acc = 0.0f;
for (int i = 0; i < N; i++) acc += wf[i] * xf[i];
return acc;
}

__attribute__((noinline)) int32_t macInt8() {
int32_t acc = 0; // acumulador de 32 bits: cada producto int8·int8 cabe en 16
for (int i = 0; i < N; i++) acc += (int32_t)wq[i] * xq[i];
return acc;
}

void medir(uint32_t mhz) {
  if (!setCpuFrequencyMhz(mhz)) {
    Serial.printf("%lu MHz no soportado en este chip\n", (unsigned long)mhz);
  return;
}
  delay(20);
  // asm volatile("" ::: "memory") es una barrera: obliga a recalcular en cada repetición
  uint32_t c0 = ESP.getCycleCount(), t0 = micros();
  for (int r = 0; r < REPS; r++) { sumideroF = macFloat(); asm volatile("" ::: "memory"); }
  uint32_t tf = micros() - t0, cf = ESP.getCycleCount() - c0;

  c0 = ESP.getCycleCount(); t0 = micros();
  for (int r = 0; r < REPS; r++) { sumideroQ = macInt8(); asm volatile("" ::: "memory"); }
  uint32_t tq = micros() - t0, cq = ESP.getCycleCount() - c0;

  const float total = (float)N * REPS;
  Serial.printf("%3lu MHz | float32: %6.2f ns/MAC, %5.2f ciclos/MAC | "
                "int8: %6.2f ns/MAC, %5.2f ciclos/MAC\n",
                (unsigned long)getCpuFrequencyMhz(), 1000.0f * tf / total, cf / total,
                1000.0f * tq / total, cq / total);
}

void setup() {
  Serial.begin(115200);
  delay(1500);
  for (int i = 0; i < N; i++) {
    wf[i] = random(-1000, 1000) / 1000.0f; xf[i] = random(-1000, 1000) / 1000.0f;
    wq[i] = (int8_t)random(-128, 128); xq[i] = (int8_t)random(-128, 128);
  }
  const uint32_t frecuencias[] = {240, 160, 80}; // ESP32-C3: el máximo es 160 MHz
  for (uint32_t f : frecuencias) medir(f);
}
void loop() {}