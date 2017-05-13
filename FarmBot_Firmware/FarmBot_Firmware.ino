#include "SerialCommand.h"

#define X_DIR           A1
#define X_STEP          A0
#define X_EN            38
#define Y_DIR           A7
#define Y_STEP          A6
#define Y_EN            A2
#define MAX_Y           800
#define Z_DIR           48
#define Z_STEP          46
#define Z_EN            A8
#define MAX_Z           300
#define X_MIN           2
#define Y_MIN           14
#define Z_MIN           18
#define UP              HIGH
#define DOWN            LOW
#define MAX_X           300
#define STEPS_PER_MM_XY 80

SerialCommand serialCMD;
////thucommit
//////
typedef struct
{
  int X = 0;
  int Y = 0;
  int Z = 0;
} Point;

Point CurrentPosition;

float X, Y, Z;

void setup()
{
  serialCMD = SerialCommand(&Serial, 9600);

  serialCMD.AddCommand("X", &X);
  serialCMD.AddCommand("MoveX", MoveX);
  serialCMD.AddCommand("Y", &Y);
  serialCMD.AddCommand("MoveY", MoveY);
  serialCMD.AddCommand("Z", &Z);
  serialCMD.AddCommand("MoveZ", MoveZ);
  serialCMD.AddCommand("IsFarmBot", Confirm);

  StepperInit();

}

void loop()
{
  serialCMD.Execute();
}

void Confirm()
{
	Serial.println("YesFarmBot");
}

void StepperInit()
{
  pinMode(X_DIR, OUTPUT);
  pinMode(X_STEP, OUTPUT);
  pinMode(X_EN, OUTPUT);
  digitalWrite(X_EN, LOW);

  pinMode(Y_DIR, OUTPUT);
  pinMode(Y_STEP, OUTPUT);
  pinMode(Y_EN, OUTPUT);
  digitalWrite(Y_DIR, HIGH);
  digitalWrite(Y_EN, LOW);

  pinMode(Z_DIR, OUTPUT);
  pinMode(Z_STEP, OUTPUT);
  pinMode(Z_EN, OUTPUT);
  digitalWrite(Z_DIR, HIGH);
  digitalWrite(Z_EN, LOW);

  ForwardX();
  /*while ( digitalRead(X_MIN) == 0 )
  {
    JumpOneStepX();
  }*/
}

void JumpOneStepX()
{
  digitalWrite(X_STEP, HIGH);
  delayMicroseconds(100);
  digitalWrite(X_STEP, LOW);
  delayMicroseconds(100);
}

void ForwardX()
{
  digitalWrite(X_DIR, HIGH);
}

void MoveX(int posX)
{
  posX = constrain(posX, 0, MAX_X);
  int delta = CurrentPosition.X - posX;

  if (delta > 0)
  {
    digitalWrite(X_DIR, UP);
  }
  else
  {
    digitalWrite(X_DIR, DOWN);
  }

  int DesiredStepNumber = abs(delta) * STEPS_PER_MM_XY;
  Serial.print(DesiredStepNumber);
  for (uint16_t i = 0; i < DesiredStepNumber; i++)
  {
    digitalWrite(X_STEP, LOW);
    delayMicroseconds(100);
    digitalWrite(X_STEP, HIGH);
    delayMicroseconds(100);
  }
  CurrentPosition.X = posX;
  Serial.print("X : ");
  Serial.println(CurrentPosition.X);
}

void MoveX()
{
  MoveX(X);
}
void MoveY(int posY)
{
  posY = constrain(posY, 0, MAX_Y);
  int delta = CurrentPosition.Y - posY;

  if (delta > 0)
  {
    digitalWrite(Y_DIR, UP);
  }
  else
  {
    digitalWrite(Y_DIR, DOWN);
  }

  int DesiredStepNumber = abs(delta) * STEPS_PER_MM_XY;

  for (uint16_t i = 0; i < DesiredStepNumber; i++)
  {
    digitalWrite(Y_STEP, LOW);
    delayMicroseconds(100);
    digitalWrite(Y_STEP, HIGH);
    delayMicroseconds(100);
  }
  CurrentPosition.Y = posY;
  Serial.print("Y : ");
  Serial.println(CurrentPosition.Y);
}

void MoveY()
{
  MoveY(Y);
}
void MoveZ(int posZ)
{
  posZ = constrain(posZ, 0, MAX_Z);
  int delta = CurrentPosition.Z - posZ;

  if (delta > 0)
  {
    digitalWrite(Z_DIR, UP);
  }
  else
  {
    digitalWrite(Z_DIR, DOWN);
  }

  int DesiredStepNumber = abs(delta) * STEPS_PER_MM_XY;

  for (uint16_t i = 0; i < DesiredStepNumber; i++)
  {
    digitalWrite(Z_STEP, LOW);
    delayMicroseconds(100);
    digitalWrite(Z_STEP, HIGH);
    delayMicroseconds(100);
  }
  CurrentPosition.Z = posZ;
  Serial.print("Z : ");
  Serial.println(CurrentPosition.Z);
}

void MoveZ()
{
  MoveZ(Z);
}
