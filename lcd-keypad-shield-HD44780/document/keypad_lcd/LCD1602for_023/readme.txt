NOTE:copy the code to arduino-0022\libraries

Introduction
The LCD Keypad shield is developed for Arduino compatible boards, to provide a user-friendly interface that allows users to go through the menu, make selections etc. It consists of a 1602 white character blue backlight LCD. The keypad consists of 5 keys ¡ª select, up, right, down and left. To save the digital IO pins, the keypad interface uses only one ADC channel. The key value is read through a 5 stage voltage divider. 

Pin Allocation
Pin 	        Function
Analog 0 	Button (select, up, right, down and left)
Digital 4 	DB4
Digital 5 	DB5
Digital 6 	DB6
Digital 7 	DB7
Digital 8 	RS (Data or Signal Display Selection)
Digital 9 	Enable
Digital 10 	Backlit Control


Example use of LCD4Bit_mod library
//
#include <LCD4Bit_mod.h> 
//create object to control an LCD.  
//number of lines in display=1
LCD4Bit_mod lcd = LCD4Bit_mod(2); 
//Key message
char msgs[5][15] = {"Right Key OK ", 
                    "Up Key OK    ", 
                    "Down Key OK  ", 
                    "Left Key OK  ", 
                    "Select Key OK" };
int  adc_key_val[5] ={30, 150, 360, 535, 760 };
int NUM_KEYS = 5;
int adc_key_in;
int key=-1;
int oldkey=-1;
void setup() { 
  pinMode(13, OUTPUT);  //we'll use the debug LED to output a heartbeat

  lcd.init();
  //optionally, now set up our application-specific display settings, overriding whatever the lcd did in lcd.init()
  //lcd.commandWrite(0x0F);//cursor on, display on, blink on.  (nasty!)
   lcd.clear();
  lcd.printIn("KEYPAD testing... pressing");
}
void loop() 
{
adc_key_in = analogRead(0);    // read the value from the sensor  
digitalWrite(13, HIGH);  
key = get_key(adc_key_in);    // convert into key press
	if (key != oldkey)	// if keypress is detected
	{
    delay(50);		// wait for debounce time
    adc_key_in = analogRead(0);    // read the value from the sensor  
    key = get_key(adc_key_in);    // convert into key press
    if (key != oldkey)				
    {			
      oldkey = key;
      if (key >=0){
      lcd.cursorTo(2, 0);  //line=2, x=0
  	lcd.printIn(msgs[key]);
      }
    }
  }
  digitalWrite(13, LOW);
}
// Convert ADC value to key number
int get_key(unsigned int input)
{	int k;
	for (k = 0; k < NUM_KEYS; k++)
	{
		if (input < adc_key_val[k])
		{  return k;  }
	}
    if (k >= NUM_KEYS)
        k = -1;     // No valid key pressed
    return k; 

}