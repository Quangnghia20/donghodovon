// khai bao gia tri vol
#define voltage_max 2
float voltage;
float vol_high;
// khai bao gia tri milis()
unsigned long previousMillis = 0;
const long interval = 1000;
unsigned long init_time = 0;
const long time_sensor = 1000;
// khia bao led
int ledState = LOW;
const int ledpin = 2;
// thu vien
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);

void setup()
{

  lcd.init();         // khoi tao lcd
  lcd.backlight();     // bat den lcd
  //lcd.setCursor(3, 1); // con tro toi vi tri (3,1)
  //lcd.print("Analog");
  lcd.setCursor(0, 2);
  lcd.print("vol:");

  // Serial.begin(9600);
  pinMode(ledpin, OUTPUT);
  vol_high = voltage_max;
}

void gioi_han()
{
  if ((voltage) < vol_high)
  {
    char chuoi[] = ("vuot_nguon");
    lcd.setCursor(4, 1);
    lcd.print(chuoi);
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= interval)
    {
      // save the last time you blinked the LED
      previousMillis = currentMillis;

      // if the LED is off turn it on and vice-versa:
      if (ledState == LOW)
      {
        ledState = HIGH;
      }
      else
      {
        ledState = LOW;
      }

      // set the LED with the ledState of the variable:
      digitalWrite(ledpin, ledState);
      // Serial.println("vuot nguon");
    }
  }
  else
  {
    digitalWrite(ledpin, LOW);
    lcd.setCursor(4, 3);
    lcd.print("           ");
    // lcd.clear();
  }
}

void sensor()
{

  unsigned long time_sensor_GO = millis();

  if (time_sensor_GO - init_time >= time_sensor)
  {
    // save the last time you blinked the LED
    init_time = time_sensor_GO;
    int sensorValue = analogRead(A0);

    voltage = sensorValue * (5.0 / 1023.0);
    Serial.println(voltage);
    lcd.setCursor(5, 0);

    lcd.print(voltage);
  }
}

void loop()
{

  sensor();
  gioi_han();
}
