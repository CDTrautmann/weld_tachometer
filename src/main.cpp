#include <Arduino.h>
#include <LiquidCrystal.h>

// adding comments later
//TODO: measure and update the dimensions
// test on the LCD library
const int tachPin = 0;
float value=0;
int tach=0;
float sfm=0;
float rpm = 0;
int oldtime=0;
int time;
const int holdRad = 457;
const int tachWidth = 5;
const int wheelRad = 914;

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void isr() {
  tach++;
}

void writeSpeed(float rpm) {
  sfm = rpm*(wheelRad*6.2832)*(1/1000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print('_ROTATION SPEED_');
  lcd.setCursor(0,1);
  lcd.print(sfm);
  lcd.print('  M/min');
}

void setup() {
  digitalWrite(2, HIGH);
  attachInterrupt(tachPin,isr,RISING);
  attachInterrupt(tachPin,isr,FALLING);
  lcd.begin(16, 2);
  Serial.begin(9600);
}

void loop() {
  delay(500);
  detachInterrupt(tachPin);
  time = millis()-oldtime;
  rpm = (tach/time)*(1/tachWidth)*(1/(holdRad*6.2832))*60000;
  oldtime = millis();
  tach = 0;
  writeSpeed(rpm);
}