#include <Arduino.h>
#include <RF24.h>

RF24 radio(16, 17);
// put function declarations here:
const byte addresses[][6] = {"00001", "00002"};


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  radio.begin();
  if (radio.isChipConnected()) {
    Serial.println("Chip is connected");
  }
  else{
    Serial.println("chip fialed");
  }
  // radio.closeReadingPipe(4);
  radio.closeReadingPipe(0);
  radio.closeReadingPipe(1);
  radio.closeReadingPipe(2);
  radio.closeReadingPipe(3);
  radio.closeReadingPipe(4);
  radio.closeReadingPipe(5);
  radio.setAddressWidth(5);
  radio.setDataRate(RF24_1MBPS);
  radio.setPALevel(RF24_PA_MIN);
  radio.openWritingPipe(addresses[1]);  // to receiver
  radio.openReadingPipe(1, addresses[0]);  // from receiver
  radio.stopListening();  // start in TX mode
  radio.enableDynamicPayloads();
  radio.printPrettyDetails();

  
}

void loop() {
  // put your main code here, to run repeatedly:
  byte buff[32] = {0};
  radio.stopListening();
  while(!Serial.available()){delay(5);}
  if(Serial.available())
  {
    
    uint8_t i = 0;
    while(Serial.available() > 0 && i < 32){
      buff[i] = Serial.read();
      i++;
    }

    bool status = radio.write(&buff, i);
    if(status){
      // Serial.println("Data send");
    }
    else{
      // Serial.println("send failed");
    }
  }
  delay(10); // small wait before listening for response
  radio.startListening();
  unsigned long startTime = millis();
  bool timeout = false;
  while (!radio.available()) {
    if (millis() - startTime > 1000) {
      timeout = true;
      break;
    }
   delay(5);
  }
  if (!timeout) {
    uint8_t len = radio.getDynamicPayloadSize();
    char rxbuff[32] = {0};
    radio.read(&rxbuff,len);
    Serial.write(rxbuff, len);
  } else {
  }

  delay(200);
}