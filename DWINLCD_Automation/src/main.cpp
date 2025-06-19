#include <Arduino.h>
#include <DWIN_LCD.h>
#include <HardwareSerial.h>
// put function declarations here:

#define RX_PIN PA3
#define TX_PIN PA2

HardwareSerial dwinSerial(RX_PIN, TX_PIN);
DWIN_LCD dwin(dwinSerial);
// DWIN_LCD dwin1(Serial);
// DWIN_LCD dwin2(Serial2);

void setup() {
  // put your setup code here, to run once:
  Serial.setTx(PB6);
  Serial.setRx(PB7);
  Serial.begin(115200);
  dwin.begin(115200);
  // dwin1.begin(115200);
  // dwin2.begin(115200);
  pinMode(PD12, OUTPUT);
  
  pinMode(PD13, OUTPUT);
  
  pinMode(PD14, OUTPUT);
  
  pinMode(PD15, OUTPUT);
  Serial.println("Program start");


}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(PD12, HIGH);
  uint16_t address = 0x2000;
  String user = "Mohammadjavad";
  String pass = "123456";
  char buffchar[30];
  byte page;
  page = 7;
  digitalWrite(PD13, HIGH);
  for(int i=0; i < 10; i++){
    dwin.nextPage();
    delay(1000);
  }
  digitalWrite(PD13, HIGH);
  for(int i = 0; i < 5; i++){
    dwin.previousPage();
    delay(1000);
  }
  digitalWrite(PD14, HIGH);
  dwin.gotoPage(page);
  delay(1000);
  digitalWrite(PD15, HIGH);
  user.toCharArray(buffchar, user.length());
  dwin.writeData(address, (uint8_t *) buffchar, user.length());
  pass.toCharArray(buffchar, pass.length());
  dwin.writeData(0x2010, (uint8_t *)buffchar, pass.length());
  dwin.gotoPage(0);
  while(1) delay(20);
}

// put function definitions here: