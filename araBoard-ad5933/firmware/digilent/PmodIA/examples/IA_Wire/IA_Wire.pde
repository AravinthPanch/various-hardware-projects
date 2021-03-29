#include <WireIA.h>
#include <inttypes.h>
#include <Wire.h>
#include <EEPROM.h>


IA testIA;
void setup()
{

	Serial.begin(9600);
	
	Serial.println("PmodIA Demo");
	Serial.println("Press 'r' when ready!!");
	while(Serial.read() != 'r');	
	
	//testIA.IA_test();
	delay(20);	
	
	range();	
	
	//If GF value is not set, perform calibration for both 100K and 20Ohm
	if(testIA.getGF())
	{
		Serial.println("Perform a frequency sweep for an unknown impedance");
	}
	else{
		Serial.println("Perform Two PT Calibration!!");
	}
	
	menuCommand();
}

void loop()
{
	
	if(Serial.available())
	{
		char ch = Serial.read();
		if(ch == 'p')
		{
			Serial.println("Frequency Sweep");
			testIA.setSweepParameters(false, 15000, 1000, 5, false);
			testIA.PerformFrequencySweep();
			
			double imp = testIA.getImpedance();
			double phase = testIA.getPhase();
			Serial.print("Impedance: ");
			Serial.println(imp);
			Serial.print("Phase: ");
			Serial.println(phase);
		}
		else if(ch == 'c')
		{
			Serial.println("Calibration");
			testIA.TwoPTCalibration();
			testIA.getGF();
		}
		else {
			Serial.print("Typed Character: ");
			Serial.println(ch);
			menuCommand();
		}
	}
	
}

void range()
{
	int value;
	char *ptr;
	
	
	Serial.println("*********************************************");
	Serial.println("Please choose a beginning voltage range: ");
	Serial.println("Option 1: 200mV RFB: 20Ohm");
	Serial.println("Option 2: 400mV RFB: 20Ohm");
	Serial.println("Option 3: 1V 	RFB: 20Ohm");
	Serial.println("Option 4: 2V 	RFB: 20Ohm");
	Serial.println("Option 5: 200mV RFB: 100K_ohm");
	Serial.println("Option 6: 400mV RFB: 100K_ohm");
	Serial.println("Option 7: 1V 	RFB: 100K_ohm");
	Serial.println("Option 8: 2V	RFB: 100K_ohm");
	Serial.println("*********************************************"); 
	
	while(1)
	{
		if(Serial.available())
		{
			char ch = Serial.read();
			ptr =  &ch;
			value = atoi(ptr);
		
 			break;
		}
		else 
		{
			continue;
		}
	}
} 

int atoi (char *str)
{
  unsigned int digit = 0, value = 0; 
  
  while(*str)
  {
    if(*str >= '0' && *str <= '9')
    {
      digit = (uint8_t)(*str - '0');
    }
    else
    {
       Serial.print("Non Integer Value\n");
       break;
    }
    value = (value * 10) + digit;
    str++;
  }
  return value;
}	

void menuCommand()
{
	Serial.println("*********************************************");
	Serial.println("Below are the Commands to use the IA");
	Serial.println("Input 'p' for to perform a frequency sweep");	
	Serial.println("Input 'c' for perform the IA calibration ");
	Serial.println("\n");
}
