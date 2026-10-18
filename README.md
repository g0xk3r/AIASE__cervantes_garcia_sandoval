# AIASE · Equipo 1 · Grupo 7BM1

**Instituto Politécnico Nacional · ESCOM**  
**Ingeniería en Inteligencia Artificial**  
**Academia:** Aplicaciones de Inteligencia Artificial en Sistemas Embebidos (Plan 2020)  
**Profesor:** Rodriga Ojeda Santillan  
**Semestre:** 27/1

## Integrantes

| Nombre | Boleta |
|--------|--------|
| Cervantes Gómez, David Joacim | 2024630229 |
| García Jiménez, Alan | 2024630325 |
| Sandoval Vásquez, Gonzalo | 2024630527 |

## Proyecto integrador

**Estación Agrícola Inteligente para Automatización del Riego**

### Problema

El cuidado de plantas y pequeños cultivos exige monitorear humedad del suelo y condiciones ambientales. El riego suele depender de una persona que decide cuándo y cuánta agua aplicar, con riesgo de exceso, falta o mal timing, lo que afecta el desarrollo de la planta.

### Propuesta

Estación agrícola inteligente de pequeña escala (maceta / cultivo menor) que:

- mide humedad del suelo (sensor capacitivo) y ambiente (DHT22: temperatura y humedad);
- decide en el microcontrolador cuándo activar el riego;
- acciona una bomba de 5 V mediante módulo relevador cuando la humedad baja del umbral.

Así se reduce la intervención manual y se mantienen condiciones de humedad más estables.

### Usuarios

Personas que cultivan en casa, estudiantes o aficionados que quieran automatizar el riego básico sin ser especialistas. Alcance inicial: una maceta o cultivo pequeño.

### Hardware

Controlador previsto: Arduino Uno R3; sensor capacitivo de humedad; DHT22; bomba 5 V + relevador; fuente, protoboard, manguera y depósito. Costo estimado del prototipo: ~$230–$300 MXN.

### Alcance del semestre

Prototipo funcional: lectura de sensores, procesamiento, decisión y control de la bomba para mantener la humedad del suelo en un rango. Mejora opcional: sensor de nivel en el depósito.