#include <LiquidCrystal_I2C.h>
#include <Encoder.h>

LiquidCrystal_I2C lcd(0x27,20,4);
Encoder myEnc(D5, D6);

long oldPosition  = -999;
long initPosition = -999;
unsigned long menuTriggeredTime = 0;
const int numOfScreens = 5;
int currentScreen = -1;
String screens[numOfScreens][2] = {
  {"Ignition Time","Minutes"}, 
  {"Stabilization", "Minutes"}, 
  {"Cleaning","Minutes"},
  {"Start dose","Seconds"}, 
  {"Cut-off Temperature","Celsius"}, 
};
int parameters[numOfScreens];
bool updateScreen = true;

void setup() {
  Serial.begin(57600);
  pinMode(A0, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(A0), triggerMenu, FALLING);
  initScreen();
  delay(2000);
}


void loop() {
  long newPosition = myEnc.read();
  if (newPosition != oldPosition && newPosition % 2 == 0) {
    printPosition(newPosition / 2);
    if(menuTriggeredTime != 0 && currentScreen != -1) {
      if(newPosition > oldPosition) {
        parameters[currentScreen]++;
      } else {
        parameters[currentScreen]--;
      }
      //reset menu trigger time on parameter change
      menuTriggeredTime = millis();
      updateScreen = true;
    }
    oldPosition = newPosition;
  }

  if(menuTriggeredTime != 0 && currentScreen != -1) {
    displayMenu();
    if(menuTriggeredTime + 4000 < millis()) {
      menuTriggeredTime = 0;
      currentScreen = -1;
      myEnc.write(initPosition);
      oldPosition = initPosition;
      newPosition = initPosition;
      initPosition = -999;
      printPosition(oldPosition / 2);
      clearLCDLine(2);
      lcd.setCursor(5,2);
      lcd.print("Subscribe!");
      lcd.setCursor(3,3);
      lcd.print("Taste The Code");
    }
  } 
  

  delay(10);
}

void initScreen() {

  lcd.begin();
  lcd.backlight();
  lcd.setCursor(3,0);
  lcd.print("PELLET BURNER");
  lcd.setCursor(4,1);
  lcd.print("LCD Example");
  lcd.setCursor(5,2);
  lcd.print("Subscribe!");
  lcd.setCursor(3,3);
  lcd.print("Taste The Code");
}


void printPosition(long pos) {
  clearLCDLine(1);
  lcd.setCursor(0,1);
  lcd.print("Position: ");
  lcd.print(pos);
}

void clearLCDLine(int line)
{               
  lcd.setCursor(0,line);
  for(int n = 0; n < 20; n++) // 20 indicates symbols in line. For 2x16 LCD write - 16
  {
    lcd.print(" ");
  }
}

#define countof(a) (sizeof(a) / sizeof(a[0]))


void triggerMenu()
{
  if(menuTriggeredTime + 50 < millis()){
    if(menuTriggeredTime == 0) {
      initPosition = oldPosition;
    }
    menuTriggeredTime = millis();
    currentScreen++;
    if(currentScreen >= numOfScreens) {
      currentScreen = 0;
    }
    updateScreen = true;
  }
}

void displayMenu() {
  if(updateScreen) {
    lcd.clear();
    lcd.print(" ***  SETTINGS  *** ");
    lcd.setCursor(0,1);
    lcd.print(screens[currentScreen][0]);
    lcd.setCursor(0,2);
    lcd.print(parameters[currentScreen]);
    lcd.print(" ");
    lcd.print(screens[currentScreen][1]);
    updateScreen = false;
  }
}
