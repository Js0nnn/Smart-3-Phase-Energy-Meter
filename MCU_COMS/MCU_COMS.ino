
#include <LiquidCrystal_I2C.h>
#include <Encoder.h>
#include <SoftwareSerial.h>

#define BLYNK_TEMPLATE_ID "TMPL3KeuVp1kT"
#define BLYNK_TEMPLATE_NAME "Smart Energy Meter"
#define BLYNK_AUTH_TOKEN "Wwv3-bYqQeLf8kLKsQHuZtDSSHdDBP2F"


#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

LiquidCrystal_I2C lcd(0x27,20,4);
Encoder myEnc(D5, D6);
//Encoder MenuEnc(D5, D6);
SoftwareSerial MCU(D3,D4);

#define button A0
#define USE_NODE_MCU_BOARD
#define DEFAULT_DELAY 300

#define BLYNK_TEMPLATE_ID "TMPL3KeuVp1kT"
#define BLYNK_TEMPLATE_NAME "Smart Energy Meter"
#define BLYNK_AUTH_TOKEN "Wwv3-bYqQeLf8kLKsQHuZtDSSHdDBP2F"


BlynkTimer timer;
BlynkTimer timer2;

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Redmi Note 7 Pro_9408";
char pass[] = "12345678";


char c;
String dataIn;
int8_t indexOfA, indexOfB, indexOfC, indexOfD, indexOfE, indexOfF,
       indexOfG, indexOfH, indexOfI, indexOfJ, indexOfK, indexOfL,
       indexOfM, indexOfN, indexOfO;

byte newpos=0;
byte oldpos=0;

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

void setup() {
  Serial.begin(57600);
  MCU.begin(9600);
  delay(100);

  pinMode(button, INPUT_PULLUP);
  
  Blynk.begin(auth, ssid, pass);
  
  lcd.backlight();

  timer.setInterval(5000L, sendToBlynkServer);
  timer2.setInterval(1000L, readDataKwh);

  lcd.setCursor(7,0);
  lcd.print("SMART");
  lcd.setCursor(7,1);
  lcd.print("ENERGY METER");
  lcd.setCursor(7,2);
  lcd.print("VERSION: 0.8");
  
  delay(5000);
//  lcd.clear();
}
 
void loop() 
{
  encoder();
  Blynk.run();
  timer.run();
  timer2.run();
}


void readDataKwh()
{
  readData();
  calckWh();
}


void encoder()
{
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
}

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

void calckWh()
{
  kWh0 += rPower0*(millis()-lastmillis)/3600000000.0;
  kWh1 += rPower1*(millis()-lastmillis)/3600000000.0;
  kWh2 += rPower2*(millis()-lastmillis)/3600000000.0;

  Total_kWh=kWh0+kWh1+kWh2;


  lastmillis=millis();
}


void readData()
{
  while(MCU.available()>0)
 {
  c=MCU.read();


  if(c=='\n')
    break;
  else
    dataIn+=c;
 }

 if(c=='\n')
 {
  parseData();
  c=0;
  dataIn="";
 }
}

void parseData()
{
  indexOfA=dataIn.indexOf("A");
  indexOfB=dataIn.indexOf("B");
  indexOfC=dataIn.indexOf("C");
  indexOfD=dataIn.indexOf("D");
  indexOfE=dataIn.indexOf("E");
  indexOfF=dataIn.indexOf("F");
  indexOfG=dataIn.indexOf("G");
  indexOfH=dataIn.indexOf("H");
  indexOfI=dataIn.indexOf("I");
  indexOfJ=dataIn.indexOf("J");
  indexOfK=dataIn.indexOf("K");
  indexOfL=dataIn.indexOf("L");
  indexOfM=dataIn.indexOf("M");
  indexOfN=dataIn.indexOf("N");
  indexOfO=dataIn.indexOf("O");

  vrms0 = (dataIn.substring(0, indexOfA)).toFloat();
  irms0 = (dataIn.substring(indexOfA+1, indexOfB)).toFloat();
  aPower0=(dataIn.substring(indexOfB+1, indexOfC)).toFloat();
  rPower0=(dataIn.substring(indexOfC+1, indexOfD)).toFloat();
  pF0  =  (dataIn.substring(indexOfD+1, indexOfE)).toFloat();
  vrms1 = (dataIn.substring(indexOfE+1, indexOfF)).toFloat();
  irms1 = (dataIn.substring(indexOfF+1, indexOfG)).toFloat();
  aPower1=(dataIn.substring(indexOfG+1, indexOfH)).toFloat();
  rPower1=(dataIn.substring(indexOfH+1, indexOfI)).toFloat();
  pF1  =  (dataIn.substring(indexOfI+1, indexOfJ)).toFloat();
  vrms2 = (dataIn.substring(indexOfJ+1, indexOfK)).toFloat();
  irms2 = (dataIn.substring(indexOfK+1, indexOfL)).toFloat();
  aPower2=(dataIn.substring(indexOfL+1, indexOfM)).toFloat();
  rPower2=(dataIn.substring(indexOfM+1, indexOfN)).toFloat();
  pF2  =  (dataIn.substring(indexOfN+1, indexOfO)).toFloat();

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
  Total_curr=irms0+irms1+irms2;
  
  lcd.setCursor(0, 0);
  lcd.print(Total_curr, 2);
  lcd.print("A(total) ");
  lcd.setCursor(0, 1);
  lcd.print("Phase1: ");
  lcd.print(irms0, 2);
  lcd.print("A ");
  lcd.setCursor(0, 2);
  lcd.print("Phase2: ");
  lcd.print(irms1, 2);
  lcd.print("A ");
  lcd.setCursor(0, 3);
  lcd.print("Phase3: ");
  lcd.print(irms2, 2);
  lcd.print("A ");
}

void volts()
{
  lcd.setCursor(0, 0);
  lcd.print("RMS Voltage");
  lcd.setCursor(0, 1);
  lcd.print("Phase1: ");
  lcd.print(vrms0, 2);
  lcd.print("V ");
  lcd.setCursor(0, 2);
  lcd.print("Phase2: ");
  lcd.print(vrms1, 2);
  lcd.print("V ");
  lcd.setCursor(0, 3);
  lcd.print("Phase3: ");
  lcd.print(vrms2, 2);
  lcd.print("V ");
}

void phase1()
{
  if(vrms0<10) vrms0=0;
  if(irms0<0.02) irms0=0;
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
  lcd.setCursor(0, 1);
  lcd.print(vrms0, 2);
  lcd.print("V  ");
  lcd.setCursor(0, 2);
  lcd.print(irms0, 2);
  lcd.print("A  ");
  lcd.setCursor(0, 3);
  lcd.print(rPower0, 2);
  lcd.print("W  ");
  
  lcd.setCursor(9, 1);
  lcd.print(aPower0, 2);
  lcd.print("VA ");
  lcd.setCursor(9, 2);
  lcd.print(kWh0, 2);
  lcd.print("kWh ");
  lcd.setCursor(11, 3);
  lcd.print(pF0, 2);

}

void phase2()
{
  if(vrms1<10) vrms1=0;
  if(irms1<0.02) irms1=0;
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
  lcd.setCursor(0, 1);
  lcd.print(vrms1, 2);
  lcd.print("V  ");
  lcd.setCursor(0, 2);
  lcd.print(irms1, 2);
  lcd.print("A  ");
  lcd.setCursor(0, 3);
  lcd.print(rPower1, 2);
  lcd.print("W  ");
  
  lcd.setCursor(9, 1);
  lcd.print(aPower1, 2);
  lcd.print("VA ");
  lcd.setCursor(9, 2);
  lcd.print(kWh1, 2);
  lcd.print("kWh ");
  lcd.setCursor(11, 3);
  lcd.print(pF1, 2);

}

void phase3()
{
  if(vrms2<10) vrms2=0;
  if(irms2<0.02) irms2=0;
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
  lcd.setCursor(0, 1);
  lcd.print(vrms2, 2);
  lcd.print("V  ");
  lcd.setCursor(0, 2);
  lcd.print(irms2, 2);
  lcd.print("A  ");
  lcd.setCursor(0, 3);
  lcd.print(rPower2, 2);
  lcd.print("W  ");
  
  lcd.setCursor(9, 1);
  lcd.print(aPower2, 2);
  lcd.print("VA ");
  lcd.setCursor(9, 2);
  lcd.print(kWh2, 2);
  lcd.print("kWh ");
  lcd.setCursor(11, 3);
  lcd.print(pF2, 2);

}

void sendToBlynkServer()
{
  Blynk.virtualWrite(V0, vrms0);
  Blynk.virtualWrite(V1, rPower0);
  Blynk.virtualWrite(V2, kWh0);
  Blynk.virtualWrite(V3, vrms1);
  Blynk.virtualWrite(V4, rPower1);
  Blynk.virtualWrite(V5, kWh1);
  Blynk.virtualWrite(V6, vrms2);
  Blynk.virtualWrite(V7, rPower2);
  Blynk.virtualWrite(V8, kWh2);
  Blynk.virtualWrite(V9, Total_kWh);
}
