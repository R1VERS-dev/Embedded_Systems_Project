# Overview - S.A.P.O  
## Sistema de Alerta de Partículas y Oxígeno

---

## 1. Descripción del Proyecto

S.A.P.O (Sistema de Alerta de Partículas y Oxígeno) es un sistema embebido basado en ESP32 diseñado para detectar la presencia de humo y monitorear la calidad del aire en espacios cerrados como hogares, oficinas o laboratorios.

El sistema integra sensores ambientales, procesamiento embebido y una interfaz web local que permite monitoreo en tiempo real, visualización de gráficas históricas y gestión de alarmas.

Ante la detección de condiciones críticas, el sistema activa alertas sonoras y visuales, además de permitir la desactivación tanto física como remota.

---

## 2. Objetivo del Proyecto

Diseñar e implementar un sistema embebido capaz de:

- Detectar condiciones de posible incendio mediante sensores de humo.
- Monitorear la calidad del aire en tiempo real.
- Emitir alertas físicas (buzzer y LED).
- Permitir la desactivación de la alarma de forma física y remota.
- Almacenar histórico de datos durante 7 días.
- Mostrar gráficas e información en tiempo real mediante una interfaz web local.
- Operar de manera autónoma sin requerir conexión a internet.

---

## 3. Factibilidad del Proyecto

### 3.1 Factibilidad Técnica

El proyecto es técnicamente viable debido al uso de la ESP32, que integra conectividad WiFi, entradas ADC y memoria suficiente para ejecutar lógica de control y servidor web simultáneamente.

### 3.2 Factibilidad Económica

Los componentes utilizados son de bajo costo y fácil disponibilidad comercial, lo que hace viable su implementación en contexto académico y doméstico.

### 3.3 Factibilidad Operativa

El sistema opera en red local (modo Access Point), sin depender de servicios en la nube o conexión a internet, lo que simplifica su implementación.

---

## 4. Arquitectura y Requerimientos

La especificación formal de requerimientos y arquitectura del sistema se encuentra documentada en:

- [SRS – Software Requirements Specification](../docs/architecture/SRS/SRS.pdf)
---

## 5. Hardware Utilizado y Justificación

### 5.1 Microcontrolador

| Componente | Justificación |
|------------|--------------|
| **ESP32 (Steren)** | Integra conectividad WiFi, múltiples entradas ADC, capacidad suficiente de procesamiento y memoria interna para almacenamiento mediante LittleFS. Permite ejecutar servidor web y lógica del sistema simultáneamente. |

---

### 5.2 Sensores

| Sensor | Función | Justificación |
|--------|----------|---------------|
| **MQ-2** | Detección de humo y gases inflamables | Permite identificar condiciones asociadas a posibles incendios mediante señal analógica compatible con ADC de la ESP32. |
| **MQ-135** | Monitoreo de calidad del aire | Permite medir de forma relativa la presencia de gases contaminantes y evaluar el estado ambiental del espacio monitoreado. |

---

### 5.3 Actuadores

| Actuador | Función | Justificación |
|-----------|----------|---------------|
| **Buzzer activo** | Generar alerta sonora | Proporciona notificación inmediata en caso de condición crítica detectada. |
| **LED rojo** | Indicar estado de alarma | Permite identificación visual rápida del estado del sistema. |
| **Pulsador físico** | Desactivar alarma manualmente | Ofrece mecanismo alternativo de control ante verificación presencial del evento. |

---

## 6. Metodología de Desarrollo

El proyecto se desarrolla mediante la metodología ágil Scrum, organizada en dos sprints definidos. La gestión de tareas se realiza utilizando Trello, permitiendo planificación estructurada, seguimiento de avances y división clara de responsabilidades.

---

## 7. Equipo de Trabajo y Roles

| Integrante | Rol | Responsabilidades |
|------------|------|------------------|
| **Gustavo Ugalde Rios** | Desarrollo principal | Diseño electrónico, programación del ESP32, arquitectura del sistema y documentación técnica. |
| **Gael Olguín Rangel** | Desarrollo de apoyo | Pruebas del sistema, validación funcional y apoyo en documentación. |

---

## 8. Estado del Proyecto

Fase actual: Primer entregable – Overview y SRS inicial.
