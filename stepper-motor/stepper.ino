#include <Stepper.h>

unsigned long m_time;
// 1.8 angle per step. 360 /1.8 = 200
#define STEPS 200
// Steps and Motor pins
Stepper stepper(STEPS, 4, 5, 6, 7);

void setup()
{
  Serial.begin(9600);
  Serial.println("Stepper test!");
  // RPM
  stepper.setSpeed(150);
  m_time = millis();
}

void loop()
{
  stepper.step(200);
  Serial.print("Elapsed time ");
  Serial.println(millis() - m_time);
  m_time = millis();
  Serial.println(""); 
}
