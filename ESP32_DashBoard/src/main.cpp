#include <Arduino.h>
#include <SmoothThermistor.h>
SmoothThermistor smoothThermistor(12);
float readTemp(void);

void setup()
{
  Serial.begin(115200);
}

void loop()
{
  Serial.println(readTemp());
  delay(1000);
}

float readTemp(void)
{
  float average = 0;
  for (uint8_t i = 0; i < 10; i++)
  {
    average += analogRead(12);
    delay(10);
  }
  average /= 10;
  average = 10000 * (4095 / average - 1);
  Serial.println(average);
  // Steinhart–Hart equation, based on https://learn.adafruit.com/thermistor/using-a-thermistor
  float steinhart = (log(average / 10000)) / 3950;
  Serial.println(steinhart);
  steinhart += 1.0 / (25 + 273.15);
  steinhart = 1.0 / steinhart; // invert
  steinhart -= 273.15;         // convert to celsius
  return steinhart;
}
