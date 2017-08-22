/*
 Example Arduino sketch for
 SainSmart IIC/I2C/TWI Serial 2004 20x4 LCD Module Shield For Arduino UNO MEGA R3
 http://www.sainsmart.com/sainsmart-iic-i2c-twi-serial-2004-20x4-lcd-module-shield-for-arduino-uno-mega-r3.html
 
 and
 
 Real Time Clock DS3231 (when displaying temperature will be omitted can be used also for DS1307
 http://macetech.com/store/index.php?main_page=product_info&products_id=8 
 http://nicegear.co.nz/raspberry-pi/high-precision-real-time-clock-for-raspberry-pi/

 
 This example uses F Malpartida's NewLiquidCrystal library. Obtain from:
 https://bitbucket.org/fmalpartida/new-liquidcrystal 
 
 This example also uses Tennsy Time.h library. Obtain from:
 http://www.pjrc.com/teensy/td_libs_Time.html 
 
 Tested on:
 Arduino Pro Mini, Arduino Uno - A4 (SDA), A5 (SCL)
 Arduino Mega 2560 - 20 (SDA), 21 (SCL)
 
 Last modified: 16-Dec-2013
 
*/
#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>
#include <Time.h>

#define I2C_ADDR      0x27 // I2C address of PCF8574A
#define BACKLIGHT_PIN 3
#define En_pin        2
#define Rw_pin        1
#define Rs_pin        0
#define D4_pin        4
#define D5_pin        5
#define D6_pin        6
#define D7_pin        7

LiquidCrystal_I2C twilcd(I2C_ADDR,En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin, BACKLIGHT_PIN, POSITIVE);

//////////////////////////////////////////////////////////////
#define TRIGGER_INIT_VALUE  0
#define INTERVAL_INIT_VALUE 1
#define INTERVAL_MAX_VALUE  512
#define EMBEDDED_LED_PIN    13
unsigned long previousMillis = 0;
unsigned long currentMillis = 0;
long interval = INTERVAL_INIT_VALUE;
byte trigger;
byte ledState = LOW;
//////////////////////////////////////////////////////////////
#define DS3231_ADDRESS 104
int rtc_second; //00-59;
int rtc_minute; //00-59;
int rtc_hour;//1-12 - 00-23;
int rtc_weekday;//1-7
int rtc_day;//01-31
int rtc_month;//01-12
int rtc_year;//0-99 + 2000;
#define MAX_TEMPERATURE_EXCEED 111.11   // Celsius, bad sensor if exceed
tmElements_t tm;
unsigned long previousHodinyMillis;
unsigned long currentHodinyMillis;
bool colon_blink = false;
float TemperatureC = MAX_TEMPERATURE_EXCEED;
int lastdiggingtemperature = -1;
//////////////////////////////////////////////////////////////
//override printf output
int my_putc(char outtext, FILE *t){
  Serial.print( outtext );
  twilcd.print( outtext );
};
//////////////////////////////////////////////////////////////
void setup(){
  fdevopen( &my_putc, 0 ); //override printf output, this allows to print to more than one output device
  Serial.begin(115200);
  Serial.println(F("Start..."));
  pinMode(EMBEDDED_LED_PIN, OUTPUT);
  trigger = TRIGGER_INIT_VALUE;
  twilcd.begin(16,2);
  twilcd.home();
  //1234567890123456
  //I2C/TWI BackPack
  twilcd.print("I2C/TWI BackPack");
  twilcd.setBacklight(HIGH);
  delay(3000);
  twilcd.setBacklight(LOW);
  delay(3000);
  twilcd.setBacklight(HIGH);
  delay(3000);
  twilcd.setBacklight(LOW);
  delay(3000);
  twilcd.setBacklight(HIGH);
  Serial.println(F("Blinking done."));
  twilcd.clear();
  previousHodinyMillis = millis() - 1000;
};
//////////////////////////////////////////////////////////////

byte bcdToDec(byte val)
{
  return ( (val/16*10) + (val%16) );
};

//////////////////////////////////////////////////////////////

bool get_rtc_datum()
{
  Wire.beginTransmission(DS3231_ADDRESS);
  Wire.write(3);//set register to day
  Wire.endTransmission();
  if( Wire.requestFrom(DS3231_ADDRESS, 4) == 4 ){ //get ?5? bytes(day,date,month,year);
    rtc_weekday = bcdToDec(Wire.read());
    rtc_day     = bcdToDec(Wire.read());
    rtc_month   = bcdToDec(Wire.read());
    rtc_year    = bcdToDec(Wire.read())+2000;
    return true;
  }
  else{
    return false;
  };
};
bool get_rtc_time()
{
  Wire.beginTransmission(DS3231_ADDRESS);
  Wire.write(0);//set register to time
  Wire.endTransmission();
  if( Wire.requestFrom(DS3231_ADDRESS, 3) == 3 ){ //get 3 bytes (seconds,minutes,hours);
    rtc_second = bcdToDec(Wire.read() & 0x7f);
    rtc_minute = bcdToDec(Wire.read());
    rtc_hour   = bcdToDec(Wire.read() & 0x3f);
    return true;
  }
  else{
    return false;
  };
};
float get_rtc_temperature()
{
  Wire.beginTransmission(DS3231_ADDRESS);
  Wire.write(17);//set register to DS3132 internal temperature sensor
  Wire.endTransmission();
  if( Wire.requestFrom(DS3231_ADDRESS, 2) == 2 ){
    float ttc = (float)(int)Wire.read();
    byte portion = Wire.read();
    if(portion == 0b01000000) ttc += 0.25;
    if(portion == 0b10000000) ttc += 0.5;
    if(portion == 0b11000000) ttc += 0.75;
    return ttc;
  }
  else{
    return MAX_TEMPERATURE_EXCEED;
  };
};
bool read_rtc(time_t& cas){
  if( get_rtc_datum() ){
    get_rtc_time();
    tm.Year   = rtc_year - 1970;
    tm.Month  = rtc_month;
    tm.Day    = rtc_day;
    tm.Hour   = rtc_hour;
    tm.Minute = rtc_minute;
    tm.Second = rtc_second;
    cas = makeTime(tm);
    return true;
  }
  else{
    return false;
  };
};

/////////////////////////////////////////////////////////////////////////////////////

void hodiny(bool blink_colon){
  time_t datum;
  if( !read_rtc(datum) ){
    Serial.println(F("Failed to get the current time from RTC chip."));
  }
  else{
    if( minute(datum) != lastdiggingtemperature ){
      lastdiggingtemperature = minute(datum);
      TemperatureC = get_rtc_temperature();
    };
    twilcd.setCursor (0,0);
    printf("%02d.%02d.%04d", day(datum), month(datum), year(datum));
    Serial.print(" ");
    twilcd.setCursor (0,1);
    if( blink_colon ){
      printf("%02d %02d %02d", hour(datum), minute(datum), second(datum));
    }
    else{
      printf("%02d:%02d:%02d", hour(datum), minute(datum), second(datum));
    };
    // minimalistic version of printf library does not know %f and %s :-(
    String TempStrC = "", TempStr = "";
    if( TemperatureC < MAX_TEMPERATURE_EXCEED ){
      char buffer[16];
      TempStr = dtostrf(TemperatureC,5,2,buffer);
      TempStr = " " + TempStr;
      TempStrC = TempStr + "\xDF\x43"; //oC for Asian Character Set
      twilcd.print( TempStrC );
      TempStrC = TempStr + "\xB0\x43"; //oC for Western Character Set
      Serial.println( TempStrC );
    }
    else{
      TempStr = " --.- \xDF\x43";
      twilcd.print( TempStr );
      TempStr = " --.- \xB0\x43";
      Serial.println( TempStr );
    };
  };
};

/////////////////////////////////////////////////////////////////////////////////////

void loop(){
  currentMillis = millis();
  if( currentMillis - previousMillis > interval ){
    previousMillis = currentMillis; 
    if( ledState == LOW ){
      ledState = HIGH;
      if( trigger++ > 20 ){
        trigger = TRIGGER_INIT_VALUE;
        interval = interval * 2;
        if( interval > INTERVAL_MAX_VALUE ){
          interval = INTERVAL_INIT_VALUE;
        };
      };
    }
    else{
      ledState = LOW;
    };
    digitalWrite(EMBEDDED_LED_PIN, ledState);
  };
  currentHodinyMillis = millis();
  if( currentHodinyMillis - previousHodinyMillis >= 500 ){
    previousHodinyMillis = currentHodinyMillis;
    hodiny(colon_blink);
    colon_blink = !colon_blink;
  };
};

/////////////////////////////////////////////////////////////////////////////////////
