#include <Arduino.h>
#include <SPI.h>
#include <SD.h>

// Use SPI2 instead of default SPI1
// #define SDCARD_SPI SPI_2
#define SD_CS_PIN PA4

SPIClass SPI_2(PB13, PB14, PB15); // SCK, MISO, MOSI for SPI2

void setup() {
  Serial.setTx(PB6);
  Serial.setRx(PB7);
  Serial.begin(115200);
  Serial.println("Hi");
  pinMode(PD12, OUTPUT);
  pinMode(PD13, OUTPUT);
  pinMode(PD14, OUTPUT);
  pinMode(PD15, OUTPUT);

  // Initialize SD using SPI2
  if (!SD.begin(SD_CS_PIN)) {
    digitalWrite(PD12, HIGH);
    Serial.println("SD init failed!");
    return;
  }
  digitalWrite(PD13, HIGH);
  digitalWrite(PD15, HIGH);
  Serial.println("SD init successful!");
  delay(500);

  digitalWrite(PD14, HIGH);
  File file = SD.open("test.txt", FILE_WRITE);
  file.println("Hello SD via SPI2!");
  file.close();
  delay(2000);
  digitalWrite(PD14, LOW);
}
void loop(){
  // digitalWrite(PD12, !digitalRead(PD12));
  delay(500);
}