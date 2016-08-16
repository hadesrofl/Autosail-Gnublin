#include <QueueList.h>
#include <stdint.h>
#include <Wire.h>

#define SYNC_BYTE 0x52
QueueList<uint8_t> queue;
byte reads;
uint8_t frame_length;
void setup()
{
  Wire.begin(0x55);
  Wire.onReceive(receive);
  Wire.onRequest(send);
  Serial.begin(9600);
  reads = 1;
  frame_length = 0;
  pinMode(6, OUTPUT);
  queue.setPrinter(Serial);
}
void send() {
  uint8_t tmp;
  Serial.println("\nSending: \nData: ");
  //Sending IP Frame
  if (reads == 1) {
    // TAG
    tmp = queue.pop();
    Serial.print(tmp, DEC);
    Serial.print(" ");
    Wire.send(tmp);
    // LENGTH
    frame_length = queue.pop();
    Serial.print(frame_length, DEC);
    Serial.print(" ");
    Wire.send(frame_length);
    reads = 2;
  } else if (reads == 2) {
    for (uint8_t i = 0; i < frame_length; i++) {
      tmp = queue.pop();
      Serial.print(tmp, DEC);
      Serial.print(" ");
      Wire.send(tmp);
    }
    reads = 1;
  }
}
void receive(int howMany) {
  uint8_t tmp = 0;
  uint8_t tag_ip, length_ip;
  tag_ip = Wire.read();
  length_ip = Wire.read();
  tmp = Wire.read();
  // Check if tag is for response tag of boatside
  if (tmp != 0x08 && tmp != 0x91 && tmp != 0x92 && tmp != 0x93 &&
      tmp != 0x81 && tmp != 0x82 && tmp != 0x89 && tmp != 0x8A) {
    Serial.println("\nReceiving: \nData: ");
    queue.push(tag_ip);
    queue.push(length_ip);
    queue.push(tmp);
    Serial.print(tag_ip, DEC);
    Serial.print(" ");
    Serial.print(length_ip, DEC);
    Serial.print(" ");
    Serial.print(tmp, DEC);
    Serial.print(" ");
    while (tmp != SYNC_BYTE) {
      tmp = Wire.read();
      Serial.print(tmp, DEC);
      Serial.print(" ");
      queue.push(tmp);
    }
    digitalWrite(6, HIGH);
    digitalWrite(6, LOW);
  }
}
void loop()
{
  delay(1000);
}
