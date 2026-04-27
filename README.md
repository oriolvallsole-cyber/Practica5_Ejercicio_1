# Práctica 5 - Ejercicio 1: Lectura de tarjeta SD mediante SPI en ESP32-S3

## Descripción

En este ejercicio se implementa la lectura de un archivo almacenado en una tarjeta SD utilizando el protocolo de comunicación **SPI** sobre una placa **ESP32-S3**.

El programa inicializa la tarjeta SD, abre un archivo llamado `archivo.txt` y muestra su contenido a través del **puerto serie**.
En caso de error, se informa mediante mensajes de depuración en el monitor serie.

---

## Objetivos

* Comprender el funcionamiento básico del bus **SPI**.
* Aprender a inicializar una tarjeta **SD** en una ESP32-S3.
* Leer archivos desde la memoria SD.
* Mostrar información y mensajes de estado mediante el **monitor serie**.
* Utilizar **PlatformIO** como entorno de desarrollo.

---

## Material utilizado

* Placa **ESP32-S3**
* Módulo lector **MicroSD SPI**
* Tarjeta **MicroSD**
* Cables Dupont
* **Visual Studio Code + PlatformIO**

---

## Conexión SPI utilizada

Para la conexión entre la ESP32-S3 y el módulo SD se ha utilizado la interfaz SPI por defecto:

| Señal SPI | ESP32-S3 |
| --------- | -------: |
| MOSI      |  GPIO 11 |
| MISO      |  GPIO 13 |
| SCK       |  GPIO 12 |
| CS        |  GPIO 10 |

---

## Código implementado

```cpp
#include <SPI.h>
#include <SD.h>

File myFile;

#define SD_CS 10

void setup() {
    Serial.begin(115200);
    delay(2000);

    Serial.print("Iniciando SD ...");

    if (!SD.begin(SD_CS)) {
        Serial.println("No se pudo inicializar");
        return;
    }

    Serial.println("inicializacion exitosa");

    myFile = SD.open("/archivo.txt");

    if (myFile) {
        Serial.println("archivo.txt:");

        while (myFile.available()) {
            Serial.write(myFile.read());
        }

        myFile.close();
    } else {
        Serial.println("Error al abrir el archivo");
    }
}

void loop() {
}
```

---

## Explicación del funcionamiento

### 1. Inicialización del puerto serie

Se inicia la comunicación serie a **115200 baudios**:

```cpp
Serial.begin(115200);
```

Esto permite visualizar mensajes en el monitor serie durante la ejecución del programa.

---

### 2. Inicialización de la tarjeta SD

La tarjeta SD se inicializa mediante:

```cpp
SD.begin(SD_CS);
```

Donde `SD_CS` es el pin **Chip Select (CS)** configurado en el GPIO 10.

Si la inicialización falla, el programa muestra:

```text
No se pudo inicializar
```

---

### 3. Apertura del archivo

El programa intenta abrir el archivo `archivo.txt` almacenado en la tarjeta:

```cpp
myFile = SD.open("/archivo.txt");
```

Si el archivo existe, se procede a leer su contenido.

---

### 4. Lectura del archivo

Mientras haya datos disponibles:

```cpp
while (myFile.available()) {
    Serial.write(myFile.read());
}
```

Cada carácter leído se envía al monitor serie.

---

### 5. Cierre del archivo

Tras finalizar la lectura, el archivo se cierra:

```cpp
myFile.close();
```

Esto libera recursos y finaliza correctamente la operación.

---

## Salida esperada por el monitor serie

Si la tarjeta SD y el archivo funcionan correctamente, la salida será:

```text
Iniciando SD ...
inicializacion exitosa
archivo.txt:
Hola mundo desde la SD
```

---

## Posibles errores

### Error al inicializar la SD

Si la tarjeta no responde:

```text
Iniciando SD ...
No se pudo inicializar
```

Las posibles causas son:

* Conexión incorrecta del módulo SD.
* Pin `CS` incorrecto.
* Tarjeta SD mal insertada.
* Tarjeta no formateada en FAT32.

---

### Error al abrir el archivo

Si el archivo no existe:

```text
Iniciando SD ...
inicializacion exitosa
Error al abrir el archivo
```

---

## Configuración de PlatformIO

En el archivo `platformio.ini` se ha configurado:

```ini
monitor_speed = 115200
```

Esto permite que la velocidad del monitor serie coincida con:

```cpp
Serial.begin(115200);
```

---

## Conclusión

Este ejercicio permite comprender cómo establecer comunicación SPI entre la **ESP32-S3** y una **tarjeta SD**, inicializar el dispositivo de almacenamiento y leer archivos desde memoria externa.

Además, se utilizan mensajes por puerto serie para verificar el estado del sistema y facilitar la depuración del programa.

Se trata de una práctica fundamental para proyectos que requieren **almacenamiento externo**, como registros de datos, configuración o lectura de archivos.
