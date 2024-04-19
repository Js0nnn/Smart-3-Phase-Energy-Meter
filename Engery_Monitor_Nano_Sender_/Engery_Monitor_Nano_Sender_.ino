#include "EmonLib.h"
#include <SoftwareSerial.h>
SoftwareSerial Nano(10,11);

EnergyMonitor emon0;
#define vCalib0    665.3
#define currCalib0 36.1

EnergyMonitor emon1;
#define vCalib1    665.3
#define currCalib1 36.1

EnergyMonitor emon2;
#define vCalib2    182.3
#define currCalib2 9.2

void setup() {
  Serial.begin(57600);
  Nano.begin(9600);

  //phase1
  emon0.voltage(A0, vCalib0, 1.7);  // Voltage: input pin, calibration, phase_shift
  emon0.current(A1, currCalib0);    // Current: input pin, calibration.
  //phase2
  emon1.voltage(A2,vCalib1, 1.7);
  emon1.current(A3,currCalib1);
  //phase3
  emon2.voltage(A6,vCalib2, 1.7);
  emon2.current(A7,currCalib2);

  delay(3000);
}

void loop() {

      emon0.calcVI(20,300);
      emon1.calcVI(20,300);
      emon2.calcVI(20,300);
      
  Nano.print(emon0.Vrms); Nano.print("A");
  Nano.print(emon1.Vrms); Nano.print("B");
  Nano.print(emon2.Vrms); Nano.print("C");
  Nano.print(emon0.Irms); Nano.print("D");
  Nano.print(emon1.Irms); Nano.print("E");
  Nano.print(emon2.Irms); Nano.print("F");
  Nano.print(emon0.realPower); Nano.print("H");
  Nano.print(emon1.realPower); Nano.print("I");
  Nano.print(emon2.realPower); Nano.print("J");
  Nano.print(emon0.apparentPower); Nano.print("K");
  Nano.print(emon1.apparentPower); Nano.print("L");
  Nano.print(emon2.apparentPower); Nano.print("M");
  Nano.print("\n");
  
  //delay(500);
  
}
