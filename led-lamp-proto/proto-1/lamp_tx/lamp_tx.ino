// Description: Senic Lamp Control Panel Transmitter
// Author:      Ibrahim

#include <SoftwareSerial.h>
SoftwareSerial serial_uart(0, 1);

int p0_pin = A0;
int p1_pin = A1;
int p2_pin = A2;
int p3_pin = A3;
int b0_pin = 7 ;
int b1_pin = 8;

void setup() {
  Serial.begin(19200);
  serial_uart.begin(19200);

  pinMode(b0_pin, INPUT);
  pinMode(b1_pin, INPUT);
  pinMode(p0_pin, INPUT);
  pinMode(p1_pin, INPUT);
  pinMode(p2_pin, INPUT);
  pinMode(p3_pin, INPUT);

  Serial.println("Senic Lamp Control Panel Transmitter");
}

void loop() {
  String b0_str = String(digitalRead(b0_pin), DEC);
  String b1_str = String(digitalRead(b1_pin), DEC);

  String p0_str = String(map(analogRead(p0_pin), 0, 1023, 0, 255), DEC);
  String p1_str = String(map(analogRead(p1_pin), 0, 1023, 0, 255), DEC);
  String p2_str = String(map(analogRead(p2_pin), 0, 1023, 0, 255), DEC);
  String p3_str = String(map(analogRead(p3_pin), 0, 1023, 0, 255), DEC);

  Serial.println("b0/" + b0_str + "/b1/" + b1_str + "/p0/" + p0_str + "/p1/" + p1_str + "/p2/" + p2_str + "/p3/" + p3_str );
  serial_uart.println("b0/" + b0_str + "/b1/" + b1_str + "/p0/" + p0_str + "/p1/" + p1_str + "/p2/" + p2_str + "/p3/" + p3_str );
}

