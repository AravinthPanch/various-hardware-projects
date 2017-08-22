/*
  The circuit:
 * LCD RS pin to digital pin 8
 * LCD Enable pin to digital pin 9
 * LCD D4 pin to digital pin 4
 * LCD D5 pin to digital pin 5
 * LCD D6 pin to digital pin 6
 * LCD D7 pin to digital pin 7
 * LCD BL pin to digital pin 10
 * KEY pin to analogl pin 0
 *Vcc pin to  +5
 *Trig pin to digital pin 12
 *Echo pin to digital pin 13
fuction :  when the serial port sen an "a" to the Board .the Board will show" holl sainsmart "in the lcdkeypad"   
 */

#include <LiquidCrystal.h>
#define CM 1      //Centimeter
#define INC 0     //Inch
#define TP 12      //Trig_pin
#define EP 13      //Echo_pin

LiquidCrystal lcd(8, 13, 9, 4, 5, 6, 7);
const char nomber_[]="0123456789";
char nomber_s[]="000";
char  rword;
char msgs[5][16] = {"Right Key OK ",
                    "Up Key OK    ",               
                    "Down Key OK  ",
                    "Left Key OK  ",
                    "Select Key OK" };

int adc_key_val[5] ={50, 200, 400, 600, 800 };
int NUM_KEYS = 5;
int adc_key_in;
int key=-1;
int oldkey=-1;

void setup()
{
  lcd.clear(); 
  lcd.begin(16, 2);
  lcd.setCursor(0,0); 
  Serial.begin(9600); // 打开串口，设置波特率为9600 bps
  pinMode(TP,OUTPUT);       // set TP output for trigger  
  pinMode(EP,INPUT);        // set EP input for echo
}

void loop()
{

   long microseconds = TP_init();
   long distacne_cm = Distance(microseconds, CM);
 //  LCD_cover_data(distacne_cm,nomber_s);
   lcd.setCursor(0,0); 
   lcd.print(" Dis_CM :  "); 
   lcd.print(distacne_cm); 
   lcd.print(" CM"); 
    Serial.println(distacne_cm); //从串口发送字符串
  // Serial.println(" Holl SainSmart"); //从串口发送字符串并换行
}

long Distance(long time, int flag)
{
  /*
  
  */
  long distacne;
  if(flag)
    distacne = time /29 / 2  ;     // Distance_CM  = ((Duration of high level)*(Sonic :340m/s))/2
                                   //              = ((Duration of high level)*(Sonic :0.034 cm/us))/2
                                   //              = ((Duration of high level)/(Sonic :29.4 cm/us))/2
  else
    distacne = time / 74 / 2;      // INC
  return distacne;
}

long TP_init()
{                     
  digitalWrite(TP, LOW);                    
  delayMicroseconds(2);
  digitalWrite(TP, HIGH);                 // pull the Trig pin to high level for more than 10us impulse 
  delayMicroseconds(10);
  digitalWrite(TP, LOW);
  long microseconds = pulseIn(EP,HIGH);   // waits for the pin to go HIGH, and returns the length of the pulse in microseconds
  return microseconds;                    // return microseconds
}

//cover number to string 
void LCD_cover_data(unsigned int data_tem,char *nomber_s){
  char k=0;
  if(data_tem!=0){
     for(int i=5;i!=0&&data_tem!=0;i--){
         k=data_tem%10;
         nomber_s[i]=nomber_[k];
         data_tem/=10;
     
	}
	}
}





