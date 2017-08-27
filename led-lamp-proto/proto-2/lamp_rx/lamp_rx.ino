// LED Pins
int ledw1 = 3;
int test_led = 6;

void setup() {
  Serial.begin(115200);
  pinMode(ledw1, OUTPUT);
  pinMode(test_led, OUTPUT);
  analogWrite(ledw1, 0);
  Serial.println("Senic Lamp Control Panel Receiver");
}

String received_uart_data = "";
void loop() {
  if (Serial.available() > 0) {

    char rx_data = Serial.read();
    if (rx_data != '\n')
    {
      received_uart_data += rx_data;
    }
    else
    {
      int val = received_uart_data.toInt();
      analogWrite(ledw1, val);
      received_uart_data = "";

      if (val == 255) digitalWrite(test_led, val);
      else if (val == 0) digitalWrite(test_led, val);
    }
  }
}
