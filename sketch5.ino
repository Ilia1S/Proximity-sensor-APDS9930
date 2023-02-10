#include <Wire.h>
#include <APDS9930.h> // sensor library
#define SER 8
#define LATCH 9
#define CLK 10

APDS9930 apds;
uint16_t proximity_data = 0;

void setup() 
{
  Serial.begin(9600);
  pinMode(SER, OUTPUT);
  pinMode(LATCH, OUTPUT);
  pinMode(CLK, OUTPUT);
  apds.init();
  apds.enableProximitySensor(false);
  delay(500);
}
void loop() 
{
  apds.readProximity(proximity_data);
  Serial.print("Proximity: ");
  Serial.println(proximity_data);
  digitalWrite(LATCH, LOW);
  switch (proximity_data)
  {
    case 0 ... 99:
      shiftOut(SER, CLK, LSBFIRST, B00000000);
      break;
    case 100 ... 146:
      shiftOut(SER, CLK, LSBFIRST, B10000000);
      break;
    case 147 ... 293:
      shiftOut(SER, CLK, LSBFIRST, B11000000);
      break;
    case 294 ... 439:
      shiftOut(SER, CLK, LSBFIRST, B11100000);
      break;
    case 440 ... 585:
      shiftOut(SER, CLK, LSBFIRST, B11110000);
      break;
    case 586 ... 732:
      shiftOut(SER, CLK, LSBFIRST, B11111000);
      break;
    case 733 ... 879:
      shiftOut(SER, CLK, LSBFIRST, B11111100);
      break;
    case 880 ... 1023:
      shiftOut(SER, CLK, LSBFIRST, B11111110);
      break;
  }
  digitalWrite(LATCH, HIGH);
}
