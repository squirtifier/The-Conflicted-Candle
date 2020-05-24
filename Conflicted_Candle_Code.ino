// The Conflicted Candle
// Created May 4, 2020
//James Cochrane https://www.YouTube.com/BD594


#include <Servo.h>

Servo candleservo;  // create servo object to control a servo
int servoposition = 0;    // Servo's home position
int flameout; // Varible
int flameon; // Varible
int MotorClockWise = 2;  // Data pin D2 to IN1 on motor controller brd
int MotorCounterClockWise = 3;  //  Data pin D3 to IN2 on motor controller brd
int HallEffectSensor = 4; //KY-003 sensor output to pin D4
int ArcLighter = 5;  // Data pin D5 to relay module
int val; // Hall Effect sensor value
int MotorDir; // Motor Direction
int MotorEn;  // Motor Enable

void setup()
{
  candleservo.attach(9);  // attach servo to pin D9
  candleservo.write(0); delay (15);  //servo home postion
  flameout = 1;
  flameon = 0;
  pinMode(MotorClockWise, OUTPUT); //set D2 pin as output
  pinMode(MotorCounterClockWise, OUTPUT); //set D3 pin as output
  pinMode(HallEffectSensor, INPUT); //set D4 pin as input
  pinMode(ArcLighter, OUTPUT); //set D5 pin as output
  MotorDir = 0; // 0 for CW and 1 for CCW
  MotorEn = 1;  // 0 for motor off and 1 for motor on
}

void loop()
{

  if (MotorEn == 1 & MotorDir == 1) //Routine to light the candle
  {
    val = digitalRead(HallEffectSensor); //Read the halleffect sensor
    digitalWrite(MotorClockWise, LOW);
    digitalWrite(MotorCounterClockWise, HIGH);
    if (val == LOW)  // Hall effect sensor activated by magnet
    {
      MotorEn = 0; //  0 Than stop the motor
      delay (500);  // Timer adjustment for alignment of Arc Lighter
      digitalWrite(MotorCounterClockWise, LOW);
      digitalWrite(ArcLighter, HIGH)
      delay (3000); // Wait for the arc lighter to light the candle
      digitalWrite(ArcLighter, LOW)
      flameout = 1;
      MotorDir = 0;
      MotorEn = 1;
      digitalWrite(MotorClockWise, HIGH); // Move magnet away from HallEffect sensor
      delay (1000); // Delay before going back to main loop
    }
  }

  if (MotorEn == 1 & MotorDir == 0) //Routine to put out candle
  {
    val = digitalRead(HallEffectSensor); //Read the halleffect sensor
    digitalWrite(MotorCounterClockWise, LOW);
    digitalWrite(MotorClockWise, HIGH);
    if (val == LOW)  // Hall effect sensor activated by magnet
    {
      MotorEn = 0; //  0 Than stop the motor
      digitalWrite(MotorClockWise, LOW); // Motor stopped

      if (flameout == 1)
      {
        // 0 is servo home postion. 105 is servo's max position to put the flame out
        for (servoposition = 0; servoposition <= 125; servoposition += 1)
        {
          candleservo.write(servoposition);
          delay(15); // waits 15ms for the servo to reach the position
        }
        for (servoposition = 125; servoposition >= 0; servoposition -= 1) // Return servo to home position
        {
          candleservo.write(servoposition);
          delay(15); //  waits 15ms for the servo to reach the position
        }
        flameout = 0;
        MotorDir = 1;
        MotorEn = 1;
        digitalWrite(MotorCounterClockWise, HIGH); // Move magnet away from HallEffect sensor
        delay (1000); // Delay before going back to main loop

      }

    }
  }
}

