//Arduino 1.0+ Only
//Arduino 1.0+ Only
#include <Adafruit_BMP085.h>
// initialize the library with the numbers of the interface pins

#include "Wire.h"
#define DS1307_ADDRESS 0x68
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display

Adafruit_BMP085 bmp;
void setup(){
  Wire.begin();
  Serial.begin(9600);
  if (!bmp.begin()) {
	Serial.println("Could not find a valid BMP085 sensor, check wiring!");
	while (1) {}
  }
lcd.init();                      // initialize the lcd 
  lcd.init();
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(3,0);
  lcd.print("Hello, world!");
  lcd.setCursor(2,1);
  lcd.print("Ywrobot Arduino!");
   lcd.setCursor(0,2);
  lcd.print("Arduino LCM IIC 2004");
   lcd.setCursor(2,3);
  lcd.print("Power By Ec-yuan!");
  delay(2000);
}

void loop(){
  printDate();
  delay(1000);
}

byte bcdToDec(byte val)  {
// Convert binary coded decimal to normal decimal numbers
  return ( (val/16*10) + (val%16) );
}

void printDate(){

  // Reset the register pointer
  Wire.beginTransmission(DS1307_ADDRESS);

  byte zero = 0x00;
  Wire.write(zero);
  Wire.endTransmission();

  Wire.requestFrom(DS1307_ADDRESS, 7);

  int second = bcdToDec(Wire.read());
  int minute = bcdToDec(Wire.read());
  int hour = bcdToDec(Wire.read() & 0b111111); //24 hour time
  int weekDay = bcdToDec(Wire.read()); //0-6 -> sunday - Saturday
  int monthDay = bcdToDec(Wire.read());
  int month = bcdToDec(Wire.read());
  int year = bcdToDec(Wire.read());
lcd.clear();
  //print the date EG   3/1/11 23:59:59
 lcd.setCursor(2,0);
    lcd.print("Tarih: ");
    lcd.print(monthDay);
  lcd.print("/");
  lcd.print(month);
  lcd.print("/");
  lcd.print(year);
 lcd.setCursor(0,1);
  lcd.print("  Saat :");
   lcd.print(" ");
  lcd.print(hour);
  lcd.print(":");
  lcd.print(minute);
  lcd.print(":");
  lcd.print(second);
  
  
 lcd.setCursor(0,2);
lcd.print("Sicaklik : ");
    lcd.print(bmp.readTemperature());
    lcd.print(" *C");
 lcd.setCursor(0,3);   
    lcd.print(" Basinc : ");
    lcd.print(bmp.readPressure());
    lcd.print(" Pa");
    
    // Calculate altitude assuming 'standard' barometric
    // pressure of 1013.25 millibar = 101325 Pascal
  //  lcd.print("Yukseklik: ");
  //  lcd.print(bmp.readAltitude());
  //  lcd.print("m");

  // you can get a more precise measurement of altitude
  // if you know the current sea level pressure which will
  // vary with weather and such. If it is 1015 millibars
  // that is equal to 101500 Pascals.
    Serial.print("Real altitude = ");
    Serial.print(bmp.readAltitude(101500));
    Serial.println(" meters");
    
    Serial.println();
    delay(1);

}
