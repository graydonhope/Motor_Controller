#include <SoftwareSerial.h>
#include <Servo.h>

SoftwareSerial mySerial(10, 11); //TX, RX
Servo esc;

const uint8_t VescOutputPin = 5;
const int statusPin = 3;
int mappedSpeed = 0;
unsigned int btInputValue;

void setup() {
  // put your setup code here, to run once:  
  pinMode(statusPin, INPUT);
  Serial.begin(9600);
  mySerial.begin(9600);

  esc.attach(VescOutputPin);
}

void loop() {
  // put your main code here, to run repeatedly:

  int statusValue = digitalRead(statusPin);

  if (statusValue == 0) {
    Serial.print("No Signal");
    stopBoard();
  }
  else {
    if (mySerial.available() >= 2) {
      unsigned int btInputA = mySerial.read();
      unsigned int btInputB = mySerial.read();
      btInputValue = (btInputB * 256) + btInputA;
      
      if (btInputValue == 2000) {
        stopBoard();
      }
      else if (btInputValue >= 0 && btInputValue <= 255) {
        mappedSpeed = map(btInputValue, 50, 255, 1000, 2000);
        esc.writeMicroseconds(mappedSpeed);
        
        Serial.print("Mapped Speed");
        Serial.print('\n');
        Serial.print(mappedSpeed);
      }  
    }
  }
}

void stopBoard() {

  if (mappedSpeed > 1840) {
    Serial.print("Long Stop");
    Serial.print('\n');
    for (int i = 0; i < 200; i++){
      int newSpeed = mappedSpeed - 2.5;

      if (newSpeed < 1500) {
        break;
      }
      else {
        mappedSpeed = newSpeed;
        esc.writeMicroseconds(mappedSpeed);
        Serial.print("Mapped Speed");
        Serial.print('\n');
        Serial.print(mappedSpeed);
      }
      delay(60);
    }
  }
  else if (mappedSpeed > 1750) {
    Serial.print("Medium Stop");
    Serial.print('\n');
    for (int i = 0; i < 227; i++) {
      int newSpeed = mappedSpeed - 1.5;

      if (newSpeed < 1500) {
        break;
      }
      else {
        mappedSpeed = newSpeed;
        esc.writeMicroseconds(mappedSpeed);

        Serial.print("Mapped Speed");
        Serial.print('\n');
        Serial.print(mappedSpeed);
      }
      delay(85);
    }
  }
  else {
    Serial.print("Short Stop");
    Serial.print('\n');
    for (int i = 0; i < 187; i++) {
      int newSpeed = mappedSpeed - 1.5;

      if (newSpeed < 1500) {
        break;
      }
      else {
        mappedSpeed = newSpeed;
        esc.writeMicroseconds(mappedSpeed);

        Serial.print("Mapped Speed");
        Serial.print('\n');
        Serial.print(mappedSpeed);
      }
      delay(63);
    }       
  }
}