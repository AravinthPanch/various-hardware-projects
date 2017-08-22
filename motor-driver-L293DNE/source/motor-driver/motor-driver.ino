int enPin = 28;
int oneApin = 30;
int twoApin = 38;

void setup() {
  pinMode(enPin, OUTPUT);
  pinMode(oneApin, OUTPUT);
  pinMode(twoApin, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  digitalWrite(enPin, HIGH);

  // Turn left
  Serial.println("Turn left");
  digitalWrite(oneApin, HIGH);
  digitalWrite(twoApin, LOW);
  delay(5000);


  // Motor Stop
  Serial.println("Motor Stop");
  digitalWrite(oneApin, HIGH);
  digitalWrite(twoApin, HIGH);
  delay(5000);

  // Turn right
  Serial.println("Turn right");
  digitalWrite(oneApin, LOW);
  digitalWrite(twoApin, HIGH);
  delay(5000);

  // Motor Stop
  Serial.println("Motor Stop");
  digitalWrite(oneApin, LOW);
  digitalWrite(twoApin, LOW);
  delay(5000);
}
