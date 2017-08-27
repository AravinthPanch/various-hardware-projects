

#define encoder0PinA 2
#define encoder0PinB 4

#define MAX_VALUE 255
#define MIN_VALUE 0

volatile unsigned int encoder0Pos = 0;
static boolean rotating=false;

void setup() {
  pinMode(encoder0PinA, INPUT); 
  digitalWrite(encoder0PinA, HIGH);       
  pinMode(encoder0PinB, INPUT); 
  digitalWrite(encoder0PinB, HIGH); 

  attachInterrupt(0, rotEncoder, CHANGE);  
  Serial.begin (9600);
}

void rotEncoder(){
  rotating=true; 
  // If a signal change (noise or otherwise) is detected
  // in the rotary encoder, the flag is set to true
}

void loop() {
  while(rotating) {
    delay(2);
    // When signal changes we wait 2 milliseconds for it to 
    // stabilise before reading (increase this value if there
    // still bounce issues)
    if (!(encoder0Pos>MAX_VALUE) && digitalRead(encoder0PinA) == digitalRead(encoder0PinB)) {  
      encoder0Pos++;
    } 
    else if(encoder0Pos != 0){                                   
      encoder0Pos--;
    }
    rotating=false; // Reset the flag back to false

    if(encoder0Pos>MAX_VALUE)
      encoder0Pos = MAX_VALUE;

    
    Serial.println(encoder0Pos);
  }
}

