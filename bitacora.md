# Bitácora del equipo

**Equipo 1 · 7BM1** — Cervantes Gómez David Joacim · García Jiménez Alan · Sandoval Vásquez Gonzalo

---

## 2026-10-14 (martes) · Compra de materiales

En esta sesión no hubo trabajo en el laboratorio de la escuela: el equipo salió a **conseguir los materiales** de la lista del curso (placa ESP32, cable USB de datos, protoboard, jumpers, LED, resistencia y lo demás para las prácticas). Se revisó qué ya tenían y qué faltaba comprar para poder armar el circuito en la siguiente clase.

---

## 2026-10-16 (jueves) · Armado y preparación del entorno

Sesión de trabajo en el **armado del circuito** (ESP32 en protoboard, LED en GPIO 2, conexiones USB) y en la **preparación del entorno**: instalación/verificación de Arduino IDE, núcleo ESP32, drivers del puerto serie y organización inicial de carpetas del repositorio (`practicas/p01-plataforma/`, listados del PDF). Queda lista la placa para cargar firmware en la siguiente sesión de mediciones.

---

## 2026-10-19 (lunes) · Práctica 1 en placa (mediciones y reporte)

En esta sesión cerramos la parte de ESP32 de la Práctica 1:

- Cargamos Listados 1–4: datos de plataforma (Tabla 4), experimento de memoria con `xtensa-esp32-elf-size -A` (Tabla 5), superlazo con LED e iter/s en condiciones (a)/(b)/(c) (Tabla 6), y benchmark MAC float32/int8 a varias frecuencias y N (Tabla 7).
- Estimamos el tiempo de una capa densa 1024×64 (~1.65 ms float / ~3.85 ms int8 a 240 MHz).
- Generamos la gráfica ns/MAC vs MHz, reunimos evidencias (foto, captura del monitor, video del LED) y redactamos el README de la práctica con tablas, cuestionario y estructura del PDF.
- Dejamos el script de la SBC (`sbc/p01_benchmark_sbc.py`) listo; **Tabla 8 y pregunta 7** siguen pendientes hasta tener Raspberry Pi.

Pendiente inmediato: commits al remoto y Parte D cuando llegue la Pi.
