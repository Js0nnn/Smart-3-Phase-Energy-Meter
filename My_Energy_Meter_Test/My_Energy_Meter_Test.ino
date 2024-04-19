#include <LiquidCrystal_I2C.h>
#include <Encoder.h>
#include "EmonLib.h"

#define button 2

Encoder myEnc(3, 4);
LiquidCrystal_I2C lcd(0x27,20,4);

EnergyMonitor emon0;
#define vCalib0    665.3
#define currCalib0 36.1

EnergyMonitor emon1;
#define vCalib1    665.3
#define currCalib1 36.1

EnergyMonitor emon2;
#define vCalib2    182.3
#define currCalib2 9.2


bool currState = HIGH;
bool prevState = HIGH; 
unsigned long waitTime = 50;


long newpos=0;
long oldpos=0;
int ctr=0;


float Total_kWh = 0;
float Total_aPower=0;
float Total_rPower=0;
float Total_pF=0;
float Total_curr=0;

float kWh0=0;
float vrms0=0;
float irms0=0;
float aPower0=0;
float rPower0=0;
float pF0=0;

float kWh1=0;
float vrms1=0;
float irms1=0;
float aPower1=0;
float rPower1=0;
float pF1=0;

float kWh2=0;
float vrms2=0;
float irms2=0;
float aPower2=0;
float rPower2=0;
float pF2=0;



unsigned long lastmillis = millis();
//unsigned long lastmillis1 = millis();
//unsigned long lastmillis2 = millis();
//
//
//unsigned long currentmillis1 = millis();
//unsigned long currentmillis2 = millis();

void setup()
{
  Serial.begin(9600);
  lcd.begin();
  lcd.backlight();
  pinMode(2, INPUT_PULLUP);
//  attachInterrupt(digitalPinToInterrupt(2), triggerMenu, FALLING);
  
  //phase1
  emon0.voltage(A0, vCalib0, 1.7);  // Voltage: input pin, calibration, phase_shift
  emon0.current(A1, currCalib0);    // Current: input pin, calibration.
  //phase2
  emon1.voltage(A2,vCalib1, 1.7);
  emon1.current(A3,currCalib1);
  //phase3
  emon2.voltage(A6,vCalib2, 1.7);
  emon2.current(A7,currCalib2);

  lcd.setCursor(5, 0);
  lcd.print("Smart Energy");
  lcd.setCursor(7, 2);
  lcd.print("Meter");  

   
  delay(3000);
  lcd.clear();
}
 
void loop()
{
  //unsigned long currentmillis0 = millis();

//  if(millis()-lastmillis > 500)
//  {
    
      emon0.calcVI(20,300);
      emon1.calcVI(20,300);
      emon2.calcVI(20,300);
//  }

  kWh0 += emon0.realPower*(millis()-lastmillis)/3600000000.0;
  kWh1 += emon1.realPower*(millis()-lastmillis)/3600000000.0;
  kWh2 += emon2.realPower*(millis()-lastmillis)/3600000000.0;

  Total_curr=emon0.Irms+emon1.Irms+emon2.Irms;
  Total_kWh=kWh0+kWh1+kWh2;
   
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
//    lcd.setCursor(0,0);
//    lcd.print(newpos);
//    lcd.print("    ");

    if(newpos != oldpos)
    {
      lcd.clear();
      oldpos=newpos;
    }
     callfunc(newpos);
  }

  lastmillis=millis();

//  checkButton();

  
}

//void checkButton() 
//{
//
//  // Button Debouncing
//  bool currRead = digitalRead(button);
//
//  if (currRead != prevState) 
//  {
//    prevTime = millis();
//  }
//
//  if ((millis() - prevTime) > waitTime) 
//  {
//    if (currRead != currState) 
//    {
//      currState = currRead;
//      if (currState == LOW) 
//      {
//        buttonPressed = 'B';
//      } 
//    }
//  } 
//  else
//  { 
//    buttonPressed = '0';
//  }
//  
//
//  prevState = currRead;
//
//
//   processButton(buttonPressed);
//}


void callfunc(int counter)
{
  switch(counter)
      {
        case 0:
          kWh();
          break;
        case 1:
          phase1();
          break;
        case 2:
          phase2();
          break;
        case 3:
          phase3();
          break;
        case 4:
          amps();
          break;
        case 5:
          volts();
          break;
        default:
          break;
      }
}

void kWh()
{
  lcd.setCursor(0, 0);
  lcd.print(Total_kWh, 4);
  lcd.print("kWh(total) ");
  lcd.setCursor(0, 1);
  lcd.print("Phase1: ");
  lcd.print(kWh0, 4);
  lcd.print("kWh ");
  lcd.setCursor(0, 2);
  lcd.print("Phase2: ");
  lcd.print(kWh1, 4);
  lcd.print("kWh ");
  lcd.setCursor(0, 3);
  lcd.print("Phase3: ");
  lcd.print(kWh2, 4);
  lcd.print("kWh ");
}

void amps()
{
  lcd.setCursor(0, 0);
  lcd.print(Total_curr, 2);
  lcd.print("A(total) ");
  lcd.setCursor(0, 1);
  lcd.print("Phase1: ");
  lcd.print(emon0.Irms, 2);
  lcd.print("A ");
  lcd.setCursor(0, 2);
  lcd.print("Phase2: ");
  lcd.print(emon1.Irms, 2);
  lcd.print("A ");
  lcd.setCursor(0, 3);
  lcd.print("Phase3: ");
  lcd.print(emon2.Irms, 2);
  lcd.print("A ");
}

void volts()
{
  lcd.setCursor(0, 0);
  lcd.print("RMS Voltage");
  lcd.setCursor(0, 1);
  lcd.print("Phase1: ");
  lcd.print(emon0.Vrms, 2);
  lcd.print("V ");
  lcd.setCursor(0, 2);
  lcd.print("Phase2: ");
  lcd.print(emon1.Vrms, 2);
  lcd.print("V ");
  lcd.setCursor(0, 3);
  lcd.print("Phase3: ");
  lcd.print(emon2.Vrms, 2);
  lcd.print("V ");
}

void phase1()
{
  vrms0=emon0.Vrms;
  if(vrms0<10) vrms0=0;
  irms0=emon0.Irms;
  if(irms0<0.02) irms0=0;

  aPower0=emon0.apparentPower;
  rPower0=emon0.realPower;
  pF0=emon0.powerFactor;

  if(rPower2<0) rPower2=0;
  if(vrms2==0 || irms2==0) 
  {
    kWh2=0;
    aPower2=0;
    pF2=0;
    rPower2=0;
  }
  lcd.setCursor(0, 0);
  lcd.print("Phase: 1");
  lcd.setCursor(14,0);
  lcd.print("50.0");
  lcd.print("Hz");
  lcd.setCursor(0, 1);
  lcd.print(vrms0, 2);
  lcd.print("V  ");
  lcd.setCursor(0, 2);
  lcd.print(irms0, 2);
  lcd.print("A  ");
  lcd.setCursor(0, 3);
  lcd.print(rPower0, 2);
  lcd.print("W  ");
  
  lcd.setCursor(10, 1);
  lcd.print(aPower0, 2);
  lcd.print("VA ");
  lcd.setCursor(10, 2);
  lcd.print(kWh0, 2);
  lcd.print("kWh ");
  lcd.setCursor(10, 3);
  lcd.print(pF0, 2);

}

void phase2()
{
  vrms1=emon1.Vrms;
  if(vrms1<10) vrms1=0;
  irms1=emon1.Irms;
  if(irms1<0.02) irms1=0;

  aPower1=emon1.apparentPower;
  rPower1=emon1.realPower;
  pF1=emon1.powerFactor;

  if(rPower1<0) rPower1=0;
  if(vrms1==0 || irms1==0) 
  {
    kWh1=0;
    aPower1=0;
    pF1=0;
    rPower1=0;
  }
  lcd.setCursor(0, 0);
  lcd.print("Phase: 2");
  lcd.setCursor(14,0);
  lcd.print("50.0");
  lcd.print("Hz");
  lcd.setCursor(0, 1);
  lcd.print(vrms1, 2);
  lcd.print("V  ");
  lcd.setCursor(0, 2);
  lcd.print(irms1, 2);
  lcd.print("A  ");
  lcd.setCursor(0, 3);
  lcd.print(rPower1, 2);
  lcd.print("W  ");
  
  lcd.setCursor(10, 1);
  lcd.print(aPower1, 2);
  lcd.print("VA ");
  lcd.setCursor(10, 2);
  lcd.print(kWh1, 2);
  lcd.print("kWh ");
  lcd.setCursor(10, 3);
  lcd.print(pF1, 2);

}

void phase3()
{
    
  

  vrms2=emon2.Vrms;
  if(vrms2<10) vrms2=0;
  irms2=emon2.Irms;
  if(irms2<0.02) irms2=0;

  aPower2=emon2.apparentPower;
  rPower2=emon2.realPower;
  pF2=emon2.powerFactor;

  if(rPower2<0) rPower2=0;
  if(vrms2==0 || irms2==0) 
  {
    kWh2=0;
    aPower2=0;
    pF2=0;
    rPower2=0;
  }
  lcd.setCursor(0, 0);
  lcd.print("Phase: 3");
  lcd.setCursor(14,0);
  lcd.print("50.0");
  lcd.print("Hz");
  lcd.setCursor(0, 1);
  lcd.print(vrms2, 2);
  lcd.print("V  ");
  lcd.setCursor(0, 2);
  lcd.print(irms2, 2);
  lcd.print("A  ");
  lcd.setCursor(0, 3);
  lcd.print(rPower2, 2);
  lcd.print("W  ");
  
  lcd.setCursor(10, 1);
  lcd.print(aPower2, 2);
  lcd.print("VA ");
  lcd.setCursor(10, 2);
  lcd.print(kWh2, 2);
  lcd.print("kWh ");
  lcd.setCursor(10, 3);
  lcd.print(pF2, 2);

}
