#include <Wire.h>
#include <Servo.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>
int LedRED = 12;
int LEDgreen = 11;
int smokeA0 = A0;
int buzzer = 3;

int sensorThres = 125;  

LiquidCrystal_I2C lcd(0x27, 16, 2);

Servo servo_2;

void setup() {

  lcd.init();
  lcd.backlight();
  lcd.noCursor();
  lcd.noBlink();
  noTone(3);

  Serial.begin(9600);
  pinMode(LedRED, OUTPUT);
  pinMode(LEDgreen, OUTPUT);
  pinMode(smokeA0, INPUT);
  servo_2.attach(2);
  pinMode(3, OUTPUT);
  

}

void loop() {
  int analogSensor = analogRead(smokeA0);
  Serial.print("Pin A0: ");
  Serial.println(analogSensor); 

  if (analogSensor > sensorThres)  {

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("     Fire!");
    lcd.setCursor(0, 1);
    lcd.print("    CALL 199");

    tone(buzzer,1000);
    digitalWrite(LedRED, HIGH);
    digitalWrite(LEDgreen, LOW);
    delay(100);
    servo_2.write(180);
    
  }
  else  {
    noTone(buzzer);
    digitalWrite(LedRED, LOW);
    digitalWrite(LEDgreen, HIGH);
    lcd.clear();
    lcd.setCursor(0, 0);
    delay(3000);
    servo_2.write(0);
    
  }
  delay(100);
  
}