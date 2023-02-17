#include <Arduino.h>
#include <LiquidCrystal.h>

// adding comments later
//TODO: measure and update the dimensions
// test on the LCD library
const int tachPin = 2;
int unsigned tach=0;
double sfm=0;
double rpm = 0;
int unsigned long oldtime=0;
int unsigned long time =0;
const unsigned int holdDia = 457;
const unsigned int tachWidth = 17;
const unsigned int wheelDia = 914;


const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void isr() {
  static unsigned long lastInterruptTime = 0;
  unsigned long interruptTime = millis();
  if (interruptTime - lastInterruptTime > 100){
    tach++;
  }
  lastInterruptTime = interruptTime;
}

void writeSpeed(float rpm) {
  sfm = (rpm*(wheelDia*6.2832)/1000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("_SURFACE SPEED_");
  lcd.setCursor(0,1);
  lcd.print(sfm);
  lcd.print(" M/min");
  Serial.print("M/min: ");
  Serial.println(sfm);
}

void setup() {
  digitalWrite(2, HIGH);
  attachInterrupt(digitalPinToInterrupt(tachPin),isr,RISING);
  lcd.begin(16, 2);
  Serial.begin(9600);
}

void loop() {
  detachInterrupt(tachPin);
  time = millis()-oldtime;
  Serial.print("tach: ");
  Serial.print(tach);
  rpm = (((tach*60000/time)*tachWidth)/(holdDia*3.1415));
  Serial.print("  RPM: ");
  Serial.println(rpm);
  oldtime = millis();
  tach = 0;
  writeSpeed(rpm);
  attachInterrupt(digitalPinToInterrupt(tachPin),isr,RISING);
  delay(10000);
}