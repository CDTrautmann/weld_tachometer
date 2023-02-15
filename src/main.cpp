#include <Arduino.h>
#include <LiquidCrystal.h>

// adding comments later
//TODO: measure and update the dimensions
// test on the LCD library
const int tachPin = 0;
double rounded=0;
int tach=0;
double sfm=0;
double rpm = 0;
int oldtime=0;
int time;
const int holdDia = 457;
const int tachWidth = 6;
const int wheelDia = 914;

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void isr() {
  tach++;
}

void writeSpeed(float rpm) {
  sfm = rpm*(wheelDia*6.2832)*(1/1000);
  rounded = round(sfm*100)/100;
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("_SURFACE SPEED_");
  lcd.setCursor(0,1);
  lcd.print(rounded);
  lcd.print(" M/min");
}

void setup() {
  digitalWrite(2, HIGH);
  attachInterrupt(tachPin,isr,RISING);
  attachInterrupt(tachPin,isr,FALLING);
  lcd.begin(16, 2);
}

void loop() {
  delay(500);
  detachInterrupt(tachPin);
  time = millis()-oldtime;
  rpm = (tach/time)*(1/tachWidth)*(1/(holdDia*6.2832))*60000;
  oldtime = millis();
  tach = 0;
  writeSpeed(rpm);
  attachInterrupt(tachPin,isr,RISING);
  attachInterrupt(tachPin,isr,FALLING);
}