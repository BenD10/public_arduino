//This is an Arduino source file to power an arduino connected to an LM35 temperature sensor and
//a standard LCD board. Keeps track of the last 5 temperatures and averages them to display the 
//current temperature. Also shows the highest and lowest recorded temperature.
#include <Wire.h>  // Comes with Arduino IDE
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address

float temp, average, high, low; 
int tempPin=0, x=0;
float temps[5];
void setup()
{
  Serial.begin(9600);
  analogReference(INTERNAL);
  lcd.begin(16,2);
  lcd.setCursor(0,0); //Start at character 0 on line 0
  lcd.print("Starting...");
  temps[0] = getTemp();
  delay(1000);
  temps[1] = getTemp();
  delay(1000);
  temps[2] = getTemp();
  delay(1000);
  temps[3] = getTemp();
  delay(1000);
  temps[4] = getTemp();
  low = avgTemp();
  high = avgTemp();
}

void loop()
{
  average = avgTemp();
  if(average < low){
    low = average;
  }
  else if(average > high){
    high = average;
  }
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Temp: ");
  lcd.print(average);
  lcd.print("C");
  lcd.setCursor(0,1);
  lcd.print("L:");
  lcd.print(low);
  lcd.print(" H:");
  lcd.print(high);
  temp = getTemp();
  temps[x] = temp;
  x++;
  if(x==4){
    x=0;
  }
  delay(1000);
}


float getTemp(){
  return analogRead(tempPin)/9.31;
}
float avgTemp(){
  float total;
  for(int x=0; x <5; x++){
    total = total + temps[x];
  }
  return total/5;
}
