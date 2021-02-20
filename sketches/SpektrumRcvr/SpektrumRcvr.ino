/*
 * Example code for Arduino Micro. For bind feature on other boards 
 * please power your receiver directly from arduino pin or via MOSFET
 */
#include <Arduino.h>
#include <HardwareSerial.h>
#include <SpektrumSerialReceiver.h>

SpektrumSerialReceiver RX;                         // Creating receiver object with bind pin 0 (same as RX1 on Arduino Micro)

void setup() {
  pinMode(3, INPUT_PULLUP);                           // Button for binding
  RX = SpektrumSerialReceiver();
  if (!digitalRead(3)) RX.bindRX(DSMX_22ms);          // Binding in selected mode (DSM2_22ms/DSM2_11ms/DSMX_22ms/DSMX_11ms)
  Serial.begin(115200);                               // Serial port for monitoring data on PC
  RX.begin(Serial1);                                  // Starting getting data from receiver on Serial1

}

void loop() {
  RX.update();                                        // Updating channel values
  
  Serial.print(RX.getChannel(1));                     // Getting channel 0 (Throttle) data
  Serial.print('\t');
  Serial.print(RX.getRXLosses());                     // Getting signal losses
  Serial.print('\t');
  switch(RX.getBindMode()){                           // Getting bind mode (protocol) and comparing it to constants
    case DSM2_22ms:
      Serial.println("DSM2 1024/22ms");
      break;
    case DSM2_11ms:
      Serial.println("DSM2 2048/11ms");
      break;
    case DSMX_22ms:
      Serial.println("DSMX 22ms");
      break;
    case DSMX_11ms:
      Serial.println("DSMX 11ms");
      break;
    default:
      Serial.println("No connection");
  }

}