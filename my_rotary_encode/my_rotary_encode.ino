#include <LiquidCrystal_I2C.h>
#include <Encoder.h>

LiquidCrystal_I2C lcd(0x27,20,4);
Encoder myEnc(3, 4);

long newpos=0;
long oldpos=0;
int ctr=0;
void setup() 
{
  Serial.begin(9600);
  lcd.begin();
  lcd.backlight();
  pinMode(2, INPUT_PULLUP);
  //attachInterrupt(digitalPinToInterrupt(2), triggerMenu, FALLING);
  
  delay(2000);
}


void loop() {

  newpos=(myEnc.read())/2;
  if(newpos>5)
  {
    newpos=0;
    myEnc.write(0);
  }
  else if(newpos<0)
  {
    newpos=5;
    myEnc.write(10);
  }
  else
  {
    lcd.setCursor(0,0);
    lcd.print(newpos);
    lcd.print("    ");
  }
}
