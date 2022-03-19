#include <Arduino.h>
#include <string>
#include <FastLED.h>
#include <M5Atom.h>

#define A_PIN   22

#define BOUNCE_LEVEL 7 //10

float accel() 
{
  int16_t x, y, z;
  float xf, yf, zf;
  M5.IMU.getAccelAdc(&x, &y, &z);
  xf = x;
  yf = y;
  zf = z;
  return sqrt(xf * xf + yf * yf + zf * zf);
}

void displayAccelLevel(int level)
{
  std::string s = "";

  for (int i = 0;  i < level; i++) {
    s += "=";
  }
  Serial.printf("%03d: %s\n", level, s.c_str());
}


void setup() {
  M5.begin(true, false, true);
  delay(10);
  M5.IMU.Init();
  Serial.begin(115200);
  delay(500);
  pinMode(A_PIN, OUTPUT);
}

void loop() {
  static bool bounced, ex_bounced;
  int f = (int)(accel() / 1000.0);
  //displayAccelLevel(f);

  bounced = BOUNCE_LEVEL < f;
  bool changed = ex_bounced != bounced && bounced;
  ex_bounced = bounced;  

  if (changed) {
    Serial.print(".");
    digitalWrite(A_PIN, true);
    delay(20);
    digitalWrite(A_PIN, false);
  }
  //displayAccelLevel(f);
}