#include <Servo.h>
#include "Adafruit_TSC2007.h"
Adafruit_TSC2007 touch;

const int servoXDataPin = A0;
const int servoYDataPin = A1;
Servo myServoX;
Servo myServoY;
const int servoRange = 180;


void setup() {
  Serial.begin(115200);
  while (!Serial) delay(10);

  if (!touch.begin()) {
    Serial.println("Couldn't find touch controller");
    while (1) delay(10);
  }

  Serial.println("Found touch controller");
  // put your setup code here, to run once:
  myServoX.attach(servoXDataPin);
  myServoY.attach(servoYDataPin);
}

void loop() {
  // put your main code here, to run repeatedly:
  static int Xangle = 90;
  static int Yangle = 90;

    uint16_t x, y, z1, z2;
  if (touch.read_touch(&x, &y, &z1, &z2)) {
    Serial.print("Touch point: (");
    Serial.print(x); Serial.print(", ");
    Serial.print(y); Serial.print(", ");
    Serial.print(z1); Serial.print(" / ");
    Serial.print(z2); Serial.println(")");
    int XposStart = 0;
    int YposStart = 0;
    int XposEnd = x; //-10;
    int YposEnd = y - 500;
    int Xvec = XposEnd - XposStart;
    int Yvec = YposEnd - YposStart;
  
    int Xangle = map(Xvec, 0, 4000, 0, 180);
    //int Xangle = 90;
    int Yangle = map(Yvec, 0, 4000, 90, 120);
    //int Yangle = 120;
      myServoX.write(Xangle);
    delay(10);
    myServoY.write(Yangle);
    delay(10);
  }
}
