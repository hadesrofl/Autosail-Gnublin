#include <Wire.h>
byte numA;
byte numB;
void setup() 
{
  Wire.begin(0x55);
  Wire.onReceive(receive);
  Wire.onRequest(send);
  Serial.begin(9600);
}
void send(){
  Wire.send(numA);
  Wire.send(numB);
}
void receive(int howMany){
  numA = Wire.read();
  Serial.print("numA = ");
  Serial.println(numA, HEX);
  numB = Wire.read();
  Serial.print("numB = ");
  Serial.println(numB, HEX);
}
void loop() 
{
  delay(100);
}
