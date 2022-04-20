#include <LiquidCrystal.h>
#include "DS1307.h"
#include <arduino-timer.h>
DS1307 clock;
const int buttonPin = 8; 
bool mot_dir = LOW;
int speed;
boolean reverse;
const int rs = 12, en = 10, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
auto timer = timer_create_default();


void setup()
{
  pinMode(13, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(A0,INPUT);  // 10k Potentiometer
  //digitalWrite(13, HIGH);//set this pin to HIGH to enable motor driver
  clock.begin();
  clock.fillByHMS(2,56,0);
  timer.every(1000, lcdprint);
}

void loop()
{
  speed = analogRead(A0)/4;
  if(!digitalRead(buttonPin)){                // If direction button is pressed
    while(!digitalRead(buttonPin));           // Wait until direction button released
    mot_dir = !mot_dir; 
  }
  direction(mot_dir, speed);
  timer.tick();
  
}

void direction (boolean reverse, int speed) {
  analogWrite(13, speed);
  digitalWrite(9, !reverse);
  digitalWrite(11, reverse);
}

bool lcdprint(void *){
  lcd.begin(16, 2);
  clock.getTime();
  lcd.print(clock.hour,DEC);
  lcd.print(":");
  lcd.print(clock.minute,DEC);
  lcd.print(":");
  lcd.print(clock.second,DEC);
  lcd.print(" ");
  if(mot_dir){
    lcd.print("C");
  }
  else{
    lcd.print("CC");
  }
  lcd.print(" ");
  if(speed >= 191){
    lcd.print("FULL");
  }
  else if(speed < 191 && speed >=100){
    lcd.print("1/2");
  }
  else{
    lcd.print("0");
  }
    
}
