#!/usr/bin/env python3
"""Gráfica ns/MAC vs MHz · Práctica 1 (Tabla 7, N=1024).

Salida: evidencias/grafica_ns_mac_vs_mhz.png
Uso:    python3 grafica_ns_mac.py

Si falta matplotlib:
    python3 -m pip install matplotlib
"""

from pathlib import Path

import matplotlib

matplotlib.use("Agg")  # sin ventana; evita errores de display en Mac
import matplotlib.pyplot as plt

# Tabla 7 · N = 1024
mhz = [80, 160, 240]
float32_ns = [76.32, 37.92, 25.23]
int8_ns = [177.46, 88.20, 58.68]

here = Path(__file__).resolve().parent
out = here.parent / "evidencias" / "grafica_ns_mac_vs_mhz.png"
out.parent.mkdir(parents=True, exist_ok=True)

fig, ax = plt.subplots(figsize=(7, 4.5), dpi=150)
ax.plot(mhz, float32_ns, "o-", label="float32", linewidth=2, markersize=7)
ax.plot(mhz, int8_ns, "s-", label="int8", linewidth=2, markersize=7)

ax.set_xlabel("Frecuencia de CPU (MHz)")
ax.set_ylabel("Costo (ns/MAC)")
ax.set_title("ESP32 · ns/MAC vs frecuencia (N = 1024)")
ax.set_xticks(mhz)
ax.grid(True, linestyle="--", alpha=0.5)
ax.legend()
fig.tight_layout()
fig.savefig(out)
print(f"Guardado: {out}")
