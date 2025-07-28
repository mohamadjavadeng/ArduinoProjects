
#include <Arduino.h>
#include <RF24.h>
// put function declarations here:
#define dePin D4

void transmitLevel(void){
  digitalWrite(dePin, HIGH);
}


void recieveLevel(void){
  digitalWrite(dePin, LOW);
}


RF24 radio(D8,D1);

const byte address[][6] = {"00001", "00002"};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600,SERIAL_8N1);
  // Serial.println("Program started");
  pinMode(dePin, OUTPUT);

  radio.begin();
  if(radio.isChipConnected()){
    Serial.println("chip connected");
  }
  else{
    Serial.println("chip failed");
  }
  radio.closeReadingPipe(0);
  radio.closeReadingPipe(1);
  radio.closeReadingPipe(2);
  radio.closeReadingPipe(3);
  radio.closeReadingPipe(4);
  radio.closeReadingPipe(5);
  radio.setAddressWidth(5);
  radio.setDataRate(RF24_1MBPS);
  radio.setPALevel(RF24_PA_MIN);
  radio.enableDynamicPayloads();
  radio.openWritingPipe(address[0]);
  radio.openReadingPipe(1, address[1]);
  radio.startListening();
  radio.printPrettyDetails();

}

void loop() {
  // put your main code here, to run repeatedly:
  if (radio.available()) {
    uint8_t len = radio.getDynamicPayloadSize();
    uint8_t buffer[32] = {0};
    bool timeoutflag = false;
    uint8_t i = 0;
    uint8_t resbuff[32] = {0};
    radio.read(&buffer, len);

    transmitLevel();
    Serial.write(buffer, len);
    delay(10);
    recieveLevel();
    uint32_t timein = millis();
    uint32_t timeout = 0;
    while(!Serial.available() && timeout < 1000) {
      // wait for serial to be available
      timeout = millis() - timein;
      delay(10);
    }
    timeoutflag = false;
    while(Serial.available() > 0) {
      // read the response from serial
      resbuff[i] = Serial.read();
      i++;
      if (i >= 32) {
        break; // prevent buffer overflow
      }
    }
    if(i == 0){
      timeoutflag = true;
    }
    radio.stopListening();
    transmitLevel();
    if(timeoutflag) {
      uint8_t timeoutResponse[] = "Timeout";
      radio.write(&timeoutResponse, sizeof(timeoutResponse));
    } else {
      bool sent = radio.write(&resbuff, i+3);
      if (!sent) {
        // Serial.println("Send response failed!");
      } else {
        // Serial.print("Sent response");
      }
    }
    // Serial.println();
    delay(10);
    radio.startListening();
  }
  // radio.startListening();
  delay(30);
}

// put function definitions here:
