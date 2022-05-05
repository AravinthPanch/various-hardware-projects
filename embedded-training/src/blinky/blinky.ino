int buttonPin = 4; 

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(buttonPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  digitalWrite(LED_BUILTIN, digitalRead(buttonPin));
  Serial.println(digitalRead(buttonPin));
  delay(1000);
}
