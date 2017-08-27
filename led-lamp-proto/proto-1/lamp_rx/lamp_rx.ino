// Description: Senic Lamp Control Panel Receiver
// Author:      Ibrahim

#include <SoftwareSerial.h>
SoftwareSerial serial_uart(0, 1);

#include <Adafruit_NeoPixel.h>
int RGBW = 7;
int NUMPIXELS = 12 ;
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, RGBW, NEO_GRBW);

// LED Pins
int ledw1 = 3;
int ledc1 = 5;
int ledw2 = 6;
int ledc2 = 9;
int doublewarmled = 10;
int doublecoolled = 11;

// Input values
int b0 = 0;
int b1 = 0;
int p0 = 0;
int p1 = 0;
int p2 = 0;
int p3 = 0;
int b0_old = 0;
int b1_old = 0;
int p0_old = 0;
int p1_old = 0;
int p2_old = 0;
int p3_old = 0;

// State machine
int last_state = 3;
unsigned long debounce_delay = 2;
enum states {
  NO_CHANGE_STATE = 0,
  B0_STATE = 1,
  B1_STATE = 2,
  P0_STATE = 3,
  P1_STATE = 4,
  P2_STATE = 5,
  P3_STATE = 6,
  UNKNOWN_STATE = 255,
};


void setup() {
  Serial.begin(19200);
  serial_uart.begin(19200);

  pinMode(ledw1, OUTPUT);
  pinMode(ledc1, OUTPUT);
  pinMode(ledw2, OUTPUT);
  pinMode(ledc2, OUTPUT);
  pinMode(doublewarmled, OUTPUT);
  pinMode(doublecoolled , OUTPUT);

  pixels.begin();
  pixels.show();

  Serial.println("Senic Lamp Control Panel Receiver");
}

// Split string by / delimiter
String split_string(String data, int index)
{
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length() - 1;
  char separator = '/';

  for (int i = 0; i <= maxIndex && found <= index; i++) {
    if (data.charAt(i) == separator || i == maxIndex) {
      found++;
      strIndex[0] = strIndex[1] + 1;
      strIndex[1] = (i == maxIndex) ? i + 1 : i;
    }
  }
  return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}

// Buffer the received data till newline and return true if data is fullly received
String received_uart_data = "";
bool parse_uart_data()
{
  if (serial_uart.available()) {
    char rx_data = serial_uart.read();
    if (rx_data != '\n')
    {
      received_uart_data += rx_data;
      return false;
    }
    else
    {
      b0 = split_string(received_uart_data, 1).toInt();
      b1 = split_string(received_uart_data, 3).toInt();
      p0 = split_string(received_uart_data, 5).toInt();
      p1 = split_string(received_uart_data, 7).toInt();
      p2 = split_string(received_uart_data, 9).toInt();
      p3 = split_string(received_uart_data, 11).toInt();

      Serial.println(received_uart_data);
      Serial.print("#");
      Serial.print(b0);
      Serial.print("/");
      Serial.print(b1);
      Serial.print("/");
      Serial.print(p0);
      Serial.print("/");
      Serial.print(p1);
      Serial.print("/");
      Serial.print(p2);
      Serial.print("/");
      Serial.print(p3);
      Serial.println("#");
      received_uart_data = "";

      return true;
    }
  }
}

void switch_warm_leds_off()
{
  analogWrite(ledw1, 0);
  analogWrite(ledw2, 0);
  analogWrite(doublewarmled, 0);
}

void switch_warm_leds_on()
{
  analogWrite(ledw1, 255);
  analogWrite(ledw2, 255);
  analogWrite(doublewarmled, 255);
}

void switch_cool_leds_off()
{
  analogWrite(ledc1, 0);
  analogWrite(ledc2, 0);
  analogWrite(doublecoolled, 0);
}

void switch_cool_leds_on()
{
  analogWrite(ledc1, 255);
  analogWrite(ledc2, 255);
  analogWrite(doublecoolled, 255);
}

void switch_rgbw_leds_off()
{
  for (int i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, 0, 0, 0, 0);
    pixels.show();
    delay(25);
  }
}

void do_animation_1() {
  for (int i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, 250, 0, 0, 0);
    pixels.show();
    delay(50);
  }

  for (int i = (NUMPIXELS - 1); i > 0; i--) {
    pixels.setPixelColor(i, 0, 255, 0, 0);
    pixels.show();
    delay(50);
  }

  switch_rgbw_leds_off();
}


void do_animation_2() {
  switch_rgbw_leds_off();

  for (int i = 0; i < 256; i++)
  {
    analogWrite(ledw1, i);
    delay(5);
  }
  for (int i = 0; i < 256; i++)
  {
    analogWrite(ledw2, i);
    delay(5);
  }
  for (int i = 0; i < 256; i++)
  {
    analogWrite(doublewarmled, i);
    delay(5);
  }

  for (int i = 255; i > 0; i--)
  {
    analogWrite(doublewarmled, i);
    delay(5);
  }

  for (int i = 255; i > 0; i--)
  {
    analogWrite(ledw2, i);
    delay(5);
  }

  for (int i = 255; i > 0; i--)
  {
    analogWrite(ledw1, i);
    delay(5);
  }

  switch_warm_leds_off();
}

// Debounce and do animation based on button 1
unsigned long b0_last_time = 0;
void update_button_1() {
  if (b0 != b0_old && (millis() - b0_last_time) > debounce_delay)
  {
    if (b0 == 1) do_animation_1();

    b0_last_time = millis();
    b0_old = b0;
    last_state = B0_STATE;
    Serial.println("Updating B0");
  }
  else
    Serial.println("Staying in B0");
}

// Debounce and do animation based on button 2
unsigned long b1_last_time = 0;
void update_button_2() {
  if (b1 != b1_old && (millis() - b1_last_time) > debounce_delay)
  {
    if (b1 == 1) do_animation_2();

    b1_last_time = millis();
    b1_old = b1;
    last_state = B1_STATE;
    Serial.println("Updating b1");
  }
  else
    Serial.println("Staying in b1");
}

// Debounce and update Warm LEDs based on p1
unsigned long p0_last_time = 0;
void update_warm_leds() {
  if (p0 != p0_old && (millis() - p0_last_time) > debounce_delay)
  {
    analogWrite(ledw1, p0);
    analogWrite(ledw2, p0);
    analogWrite(doublewarmled, p0);

    if (last_state == P2_STATE) switch_cool_leds_off();

    p0_last_time = millis();
    p0_old = p0;
    last_state = P0_STATE;
    Serial.println("Updating P0");
  }
  else
    Serial.println("Staying in P0");
}

// Debounce and update Cool LEDs based on p1
unsigned long p1_last_time = 0;
void update_cool_leds() {
  if (p1 != p1_old && (millis() - p1_last_time) > debounce_delay)
  {
    analogWrite(ledc1, p1);
    analogWrite(ledc2, p1);
    analogWrite(doublecoolled, p1);

    if (last_state == P2_STATE) switch_warm_leds_off();

    p1_last_time = millis();
    p1_old = p1;
    last_state = P1_STATE;
    Serial.println("Updating P1");
  }
  else
    Serial.println("Staying in P1");
}


// Debounce and update all leds based on p2
unsigned long p2_last_time = 0;
void update_all_leds() {
  if (p2 != p2_old && (millis() - p2_last_time) > debounce_delay)
  {
    
    for (int i = 0; i < NUMPIXELS; i++) {

      pixels.setPixelColor(i, 0, 0, p2, p3);
      pixels.show();
    }

    p2_last_time = millis();
    p2_old = p2;
    last_state = P2_STATE;
    Serial.println("Updating P2");
    
    //    analogWrite(ledw1, p2);
    //    analogWrite(ledw2, p2);
    //    analogWrite(doublewarmled, p2);
    //
    //    analogWrite(ledc1, p2);
    //    analogWrite(ledc2, p2);
    //    analogWrite(doublecoolled, p2);
    //
    //    p2_last_time = millis();
    //    p2_old = p2;
    //    last_state = P2_STATE;
    //    Serial.println("Updating P2");
}
else
  Serial.println("Staying in P2");
}

// Debounce and update RGBW LED
unsigned long p3_last_time = 0;
void update_rgbw() {
  if (p3 != p3_old && (millis() - p3_last_time) > debounce_delay)
  {
    for (int i = 0; i < NUMPIXELS; i++) {

      pixels.setPixelColor(i, 0, 0, p2, p3);
      pixels.show();
    }

    p3_last_time = millis();
    p3_old = p3;
    last_state = P3_STATE;
    Serial.println("Updating RGBW");
  }
  else
    Serial.println("Staying in RGBW");
}

// Get which input changed
int get_state() {
  if (parse_uart_data())
  {
    if (b0 != b0_old) return B0_STATE;
    else if (b1 != b1_old) return B1_STATE;
    else if (p0 != p0_old) return P0_STATE;
    else if (p1 != p1_old) return P1_STATE;
    else if (p2 != p2_old) return P2_STATE;
    else if (p3 != p3_old) return P3_STATE;
    else return NO_CHANGE_STATE;
  }
  else return UNKNOWN_STATE;
}

// Main
void loop() {
  int current_state = get_state();

  if (current_state == NO_CHANGE_STATE)
    current_state = last_state;

  switch (current_state)
  {
    case B0_STATE:
      update_button_1();
      break;
    case B1_STATE:
      update_button_2();
      break;
    case P0_STATE:
      update_warm_leds();
      break;
    case P1_STATE:
      update_cool_leds();
      break;
    case P2_STATE:
      update_all_leds();
      break;
    case P3_STATE:
      update_rgbw();
      break;
    case UNKNOWN_STATE:
      break;
  }
}

