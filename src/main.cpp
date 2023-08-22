#include <Arduino.h>
#include "DepthSensor.h"
#include "Servo.h"

#define HALL_SENSOR_PIN A0
#define ESC_PIN 4
#define RGB_LED_R_PIN 0
#define RGB_LED_G_PIN 0
#define RGB_LED_B_PIN 0
#define THRUSTER_PIN 0

DepthSensor dp_sensor;
Servo thruster;

float getDepth();
bool isMagnetNearby();

void setLed(int r, int g, int b);
void setThrust(int val);
void printDebugInfo();

void ascent();
void descent();

void setup()
{
  pinMode(HALL_SENSOR_PIN, INPUT);
  pinMode(ESC_PIN, OUTPUT);
  thruster.attach(THRUSTER_PIN);
  dp_sensor.init();

  Serial.begin(9600);

  delay(1000);
  Serial.println("Starting test shit.");

  while (isMagnetNearby())
    ;
  setThrust(100);
  // ascent();
  descent();
}

void loop()
{
  float depth = getDepth();
  if (depth > 90)
  {
    setLed(255, 0, 0);
  }
  else if (depth > 60)
  {
    setLed(255, 255, 0);
  }
  else if (depth > 30)
  {
    setLed(0, 0, 255);
  }
  else
  {
    setLed(0, 0, 0);
  }

  descent();

  printDebugInfo();

  delay(100);
}

void printDebugInfo()
{
  Serial.print("Hall: ");
  Serial.print(isMagnetNearby() ? "true" : "false");
  Serial.print(" Depth: ");
  Serial.println(getDepth());
}

bool isMagnetNearby()
{
  return digitalRead(HALL_SENSOR_PIN);
}

void ascent()
{
  delay(10000);
  setThrust(100);
}

void setLed(int r, int g, int b)
{
}

void setThrust(int val)
{
  thruster.write(map(val, -100, 100, 0, 180));
}

float getDepth()
{
  return dp_sensor.getDepth();
}

void descent()
{
  setThrust(-100);
}