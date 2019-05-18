// CNC3Axis.h

#ifndef _CNC3AXIS_h
#define _CNC3AXIS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "fastio.h"

#define X_PULSE_PIN 60
#define Y_PULSE_PIN 46
#define Z_PULSE_PIN 54

#define X_DIRECTION_PIN 61
#define Y_DIRECTION_PIN 48
#define Z_DIRECTION_PIN 55

#define X_ENABLE_PIN 56
#define Y_ENABLE_PIN 62
#define Z_ENABLE_PIN 38

#define X_ENDSTOP_PIN 53
#define Y_ENDSTOP_PIN 51
#define Z_ENDSTOP_PIN 49

#define DEFAULT_X_MAX_FEEDRATE 300
#define DEFAULT_Y_MAX_FEEDRATE 300
#define DEFAULT_Z_MAX_FEEDRATE 5

#define DEFAULT_X_STEPS_PER_MM 80
#define DEFAULT_Y_STEPS_PER_MM 80
#define DEFAULT_Z_STEPS_PER_MM 800

#define X_COMPARE_VALUE OCR3A
#define Y_COMPARE_VALUE OCR4A
#define Z_COMPARE_VALUE OCR5A

#define X_TIMER 3
#define Y_TIMER 4
#define Z_TIMER 5

enum AXIS
{
	X_AXIS = 0,
	Y_AXIS,
	Z_AXIS
};

enum DIRECTION
{
	UP = 0,
	DOWN,
	LEFT,
	RIGHT,
	FORWARD,
	BACKWARD
};

enum VARIATION
{
	INCREASE = 0,
	DECREASE
};

class CNC3AxisClass
{
 protected:


 public:
	void Init();
	void SetAxisStepsPerUnit(uint16_t xSteps, uint16_t ySteps, uint16_t zSteps);
	void SetMaxFeedRate(uint16_t xSpeed, uint16_t ySpeed, uint16_t zSpeed);
	void SetMaxPosition(uint16_t xPos, uint16_t yPos, uint16_t zPos);
	void SetHomeDirection(DIRECTION xDir, DIRECTION yDir, DIRECTION zDir);
	void SetStepPulsePin(uint8_t xPin, uint8_t yPin, uint8_t zPin);
	void SetStepDirectionPin(uint8_t xDir, uint8_t yDir, uint8_t zDir);
	void SetEndstopPin(uint8_t xEndstopPin, uint8_t yEndstopPin, uint8_t zEndstopPin);
	void SetEndstopHomeVoltage(uint8_t value);
	uint32_t GetStepsToJumpAllRoad(AXIS axis);
	void MoveHome();
	void MoveXHome();
	void MoveYHome();
	void MoveZHome();
	void MoveX(uint16_t xPos);
	void MoveY(uint16_t yPos);
	void MoveZ(uint16_t zPos);
	void Move(uint16_t xPos, uint16_t yPos, uint16_t zPos);
	int GetXPosition();
	int GetYPosition();
	int GetZPosition();

	uint8_t X_PulsePin;
	uint8_t Y_PulsePin;
	uint8_t Z_PulsePin;

	uint8_t X_DirectionPin;
	uint8_t Y_DirectionPin;
	uint8_t Z_DirectionPin;

	uint8_t X_EndstopPin;
	uint8_t Y_EndstopPin;
	uint8_t Z_EndstopPin;

	DIRECTION X_HomeDirection;
	DIRECTION Y_HomeDirection;
	DIRECTION Z_HomeDirection;

	uint8_t X_EndstopHomeVoltage;
	uint8_t Y_EndstopHomeVoltage;
	uint8_t Z_EndstopHomeVoltage;

	uint16_t FeedRate;
	uint8_t NumberOfRunningMotor;
	bool IsRunningHome;

private:

	uint16_t X_MaxFeedRate;
	uint16_t Y_MaxFeedRate;
	uint16_t Z_MaxFeedRate;

	uint16_t X_StepsPerMm;
	uint16_t Y_StepsPerMm;
	uint16_t Z_StepsPerMm;

	uint16_t X_Position;
	uint16_t Y_Position;
	uint16_t Z_Position;

	VARIATION X_Direction;
	VARIATION Y_Direction;
	VARIATION Z_Direction;

	uint16_t X_MaxPosition;
	uint16_t Y_MaxPosition;
	uint16_t Z_MaxPosition;

	uint8_t X_UpValue;
	uint8_t Y_UpValue;
	uint8_t Z_UpValue;

	uint32_t X_StepsToJumpAllRoad;
	uint32_t Y_StepsToJumpAllRoad;
	uint32_t Z_StepsToJumpAllRoad;

	uint16_t calCompareValue(double time);
	void setDirection(AXIS axis, VARIATION variation);
private:
};

void TurnOnInterrupt(uint8_t timerOder, bool answer);

extern CNC3AxisClass CNC3Axis;

#endif

