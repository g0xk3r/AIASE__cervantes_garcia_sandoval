# Resultados · Práctica 1

Placa: NodeMCU / DevKit ESP32 (CP210x)  
Puerto usado: `/dev/cu.usbserial-0001`  
Núcleo Arduino-ESP32: 3.3.12

---

## Tabla 4. Datos de la plataforma

Fuente: salida limpia del Listado 1 (`p01_info_plataforma.ino`).

| Dato | Reportado por el firmware | Hoja de datos (típico) | ¿Coincide? |
|------|---------------------------|-------------------------|------------|
| Modelo y revisión del chip | ESP32-D0WD-V3 v3.1 | ESP32-D0WD-V3 (revisión 3) | Sí |
| Núcleos y frecuencia de CPU | 2 núcleos, 240 MHz | 2 × Xtensa LX6, hasta 240 MHz | Sí |
| Tamaño de la flash | 4 194 304 bytes (4 MB) | Módulo típico con flash externa 4 MB | Sí |
| Heap total, libre y bloque máximo | 377 696 total; 331 676 libre; bloque máx. 110 580 | SRAM del chip ~520 KB; el heap usable depende del firmware/IDF | Coherente |
| PSRAM | 0 bytes | Esta placa no trae PSRAM | Sí |
| Firmware y partición OTA siguiente | Firmware 274 304 bytes; OTA siguiente 1 310 720 bytes | Esquema default ~1.25 MB por app (1 310 720) | Sí |
| Versión del núcleo / ESP-IDF | 3.3.12 / v5.5.5 | — (dato del toolchain instalado) | — |
| MAC de Wi-Fi (estación) | C8:85:41:E3:70:5C | Única por módulo | — |

### Salida limpia del monitor (la que cuenta)

```
Chip : ESP32-D0WD-V3 v3.1, 2 nucleo(s)
CPU : 240 MHz
Flash : 4194304 bytes
Heap : 377696 total, 331676 libre, bloque max. 110580
PSRAM : 0 bytes
Firmware : 274304 bytes (particion OTA siguiente: 1310720)
Nucleo / IDF : 3.3.12 / v5.5.5
MAC Wi-Fi (STA): C8:85:41:E3:70:5C
```

> Nota: el texto raro del principio (`ets Jul 29...`, símbolos ``) es el bootloader / ruido de baud. Se ignora. Si el mensaje se repite a medias, fue por varios resets; usa solo el bloque completo de arriba.

---

## Tabla 5. Uso de memoria (bytes)

Valores del IDE + `xtensa-esp32-elf-size -A`. Tabla 5 completa.

| Compilación | Programa (IDE) | Memoria dinámica (IDE) | .flash.text | .flash.rodata | .dram0.data | .dram0.bss |
|-------------|----------------|------------------------|-------------|---------------|-------------|------------|
| Listado 1 (base) | 274 152 (≈20%) | 22 236 (≈6%) | **136 024** | **54 072** | **16 961** | **5 272** |
| Listado 2 (a) con const | **285 616 (21%)** | **22 116 (6%)** | **133 320** | **68 568** | **16 849** | **5 264** |
| Listado 2 (b) sin const | **285 616 (21%)** | **38 500 (11%)** | **133 320** | **52 184** | **33 233** | **5 264** |
| Listado 2 (c) sin inicializar | **269 232 (20%)** | **38 500 (11%)** | **133 320** | **52 184** | **16 849** | **21 648** |

Notas:
- (a) `const`: pesos en flash (`.flash.rodata`) → más programa (285 616), poca RAM (22 116).
- (b) sin `const`: pesos en RAM (`.dram0.data`) + valores iniciales en flash → programa 285 616, RAM **38 500**.
- (c) sin inicializar: pesos en RAM (`.dram0.bss`), sin copia en flash → programa **más chico** (269 232), RAM igual **38 500**.
- Regla práctica: pesos de un modelo → `const` (flash), no globals sin `const` en RAM.

---

## Tabla 6. Superlazo

Salida limpia (a), tras reinicio:

```
t=1000 ms  iter/s=763233  heap=331780
t=2000 ms  iter/s=765853  heap=331780
t=3000–16000 ms  iter/s≈765965  heap=331780
```

Salida limpia (b) con `delay(1)`, tras Upload:

```
t=1000 ms  iter/s=991  heap=331780
t=2000–26000 ms  iter/s=1000  heap=331780
```

Salida limpia (c) con `Serial.printf("x")` por iteración (monitor inundado de `x`):

```
t=7006 ms  iter/s=11573  heap=331780
t=8007 ms  iter/s=11573  heap=331780
t=9008 ms  iter/s=11572  heap=331780
t=10010 ms  iter/s=11573  heap=331780
t=11000 ms  iter/s=11548  heap=331780
```

| Condición | Periodo del LED medido (ms) | Error frente a 500 ms (%) | Iteraciones del lazo por segundo |
|-----------|------------------------------|---------------------------|----------------------------------|
| (a) Listado 3 tal cual | **500** (20 ciclos en 10 s de video) | **0 %** | **≈ 765 965** (estable; heap 331 780) |
| (b) con delay(1) | ~500 ms (mismo T_LED_MS; el delay no cambia el periodo del LED) | ~0 % (mismo criterio; no recontado) | **≈ 1 000** (estable; heap 331 780) |
| (c) con Serial.printf por iteración | LED irregular / monitor saturado | — | **≈ 11 573** (UART cuello de botella; heap 331 780) |

Notas:
- El ruido `□□□` / marejada de `x` se ignora; cuenta solo las líneas `t=… iter/s=…`.
- Conclusión: `delay(1)` y `Serial.printf` en cada vuelta del lazo matan el throughput; el reporte a 1 Hz no.
- Medición LED (a): 20 parpadeos/ciclos en 10 s → periodo = 10000/20 = 500 ms → error 0 %.

---

## Tabla 7. Costo de la MAC en el ESP32

Fuente: `p01_benchmark_mac.ino` (REPS = 1000). Completa.

```
# N=1024
240 MHz | float32:  25.23 ns/MAC,  6.05 ciclos/MAC | int8:  58.68 ns/MAC, 14.08 ciclos/MAC
160 MHz | float32:  37.92 ns/MAC,  6.07 ciclos/MAC | int8:  88.20 ns/MAC, 14.11 ciclos/MAC
 80 MHz | float32:  76.32 ns/MAC,  6.11 ciclos/MAC | int8: 177.46 ns/MAC, 14.20 ciclos/MAC

# N=256 (tras Upload; RAM IDE 24 788)
240 MHz | float32:  25.60 ns/MAC,  6.14 ciclos/MAC | int8:  59.03 ns/MAC, 14.17 ciclos/MAC

# N=4096 (tras Upload; RAM IDE 63 188)
240 MHz | float32:  25.13 ns/MAC,  6.03 ciclos/MAC | int8:  58.59 ns/MAC, 14.06 ciclos/MAC
```

| Configuración | float32 (ns/MAC) | float32 (ciclos/MAC) | int8 (ns/MAC) | int8 (ciclos/MAC) |
|---------------|------------------|----------------------|---------------|-------------------|
| 240 MHz, N = 1024 | **25.23** | **6.05** | **58.68** | **14.08** |
| 160 MHz, N = 1024 | **37.92** | **6.07** | **88.20** | **14.11** |
| 80 MHz, N = 1024 | **76.32** | **6.11** | **177.46** | **14.20** |
| 240 MHz, N = 256 | **25.60** | **6.14** | **59.03** | **14.17** |
| 240 MHz, N = 4096 | **25.13** | **6.03** | **58.59** | **14.06** |

Notas:
- float32 ~6 ciclos/MAC; al bajar MHz el tiempo en ns sube ~lineal.
- int8 ~14 ciclos/MAC (más lento que float en este software puro).
- ns/MAC casi independiente de N (256≈1024≈4096): el costo por MAC se amortiza bien.
- Si el monitor muestra dos bloques iguales al de N=1024, ignora el primero (residuo); usa el de después del Upload (RAM distinta en el IDE).

---

## Tabla 8. Datos y rendimiento de la SBC

No ejecutada: aún no se dispone de Raspberry Pi. Celdas explicadas (no en blanco), salvo la fila ESP32 que sí se midió.

| Dato | Valor |
|------|-------|
| Modelo (`/proc/device-tree/model`) | No medido — falta Raspberry Pi |
| Arquitectura (`uname -m`) y núcleos (`nproc`) | No medido — falta Raspberry Pi |
| RAM total y disponible | No medido — falta Raspberry Pi |
| Espacio libre en la microSD | No medido — falta Raspberry Pi |
| Temperatura en reposo | No medido — falta Raspberry Pi |
| Dirección IP | No medido — falta Raspberry Pi |
| Python puro (ns/MAC) | No medido — falta Raspberry Pi |
| NumPy float32 (ns/MAC) | No medido — falta Raspberry Pi |
| NumPy int8 → int32 (ns/MAC) | No medido — falta Raspberry Pi |
| ESP32 float32 a 240 MHz (ns/MAC, de Tabla 7) | **25.23** |

### Estimación Parte C.3 — capa 1024×64 (65 536 MAC) @ 240 MHz

| Tipo | Tiempo |
|------|--------|
| float32 | 65 536 × 25.23 ns ≈ **1.65 ms** |
| int8 | 65 536 × 58.68 ns ≈ **3.85 ms** |
