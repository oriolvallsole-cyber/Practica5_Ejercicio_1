#include <SPI.h>
#include <SD.h>

File myFile;

#define SD_CS 10   // Cambiar según tu placa

void setup()
{
 Serial.begin(115200);
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

void loop() {}