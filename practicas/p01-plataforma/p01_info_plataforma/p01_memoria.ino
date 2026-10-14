// Práctica 1 · Experimento de memoria: compila tres veces (a, b, c) y compara la Tabla 5
const int8_t pesos[16384] = {1, 2, 3}; // (a) con const: .flash.rodata (solo flash)
// int8_t pesos[16384] = {1, 2, 3}; // (b) sin const: .dram0.data (RAM + flash)
// int8_t pesos[16384]; // (c) sin inicializar: .dram0.bss (solo RAM)
void setup() {
Serial.begin(115200);
Serial.println((int)pesos[micros() % 16384]); // usarlo evita que el enlazador lo descarte
}
void loop() {}