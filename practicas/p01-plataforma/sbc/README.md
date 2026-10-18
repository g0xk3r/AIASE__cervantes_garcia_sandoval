# SBC · Parte D (Raspberry Pi)

**Equipo 1 · 7BM1** — Cervantes Gómez David Joacim · García Jiménez Alan · Sandoval Vásquez Gonzalo

`p01_benchmark_sbc.py` es el **Listado 6** del PDF de la Práctica 1.

Mide el mismo tipo de operación MAC que el ESP32, pero en la Pi:

- Python puro (float)
- NumPy float32
- NumPy int8 → int32

Esos ns/MAC llenan la **Tabla 8** y la pregunta 7 del cuestionario (comparar con el ESP32).

**Aún no se ha ejecutado** (falta Raspberry). Cuando la tengan:

```bash
scp sbc/p01_benchmark_sbc.py usuario@pi:~
# en la Pi, con venv + numpy:
python3 p01_benchmark_sbc.py
```
