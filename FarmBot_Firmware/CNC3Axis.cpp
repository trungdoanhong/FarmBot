#include "CNC3Axis.h"

#define PRESCALER 8

uint32_t X_StepCounter;
uint32_t Y_StepCounter;
uint32_t Z_StepCounter;

void CNC3AxisClass::Init()
{
	X_UpValue = HIGH;
	Y_UpValue = HIGH;
	Z_UpValue = HIGH;

	SetStepPulsePin(X_PULSE_PIN, Y_PULSE_PIN, Z_PULSE_PIN);
	SetStepDirectionPin(X_DIRECTION_PIN, Y_DIRECTION_PIN, Z_DIRECTION_PIN);
	SetEndstopPin(X_ENDSTOP_PIN, Y_ENDSTOP_PIN, Z_ENDSTOP_PIN);

	SetMaxFeedRate(DEFAULT_X_MAX_FEEDRATE, DEFAULT_Y_MAX_FEEDRATE, DEFAULT_Z_MAX_FEEDRATE);
	SetAxisStepsPerUnit(DEFAULT_X_STEPS_PER_MM, DEFAULT_Y_STEPS_PER_MM, DEFAULT_Z_STEPS_PER_MM);

	FeedRate = X_MaxFeedRate / 2;

	X_StepsToJumpAllRoad = 0;
	Y_StepsToJumpAllRoad = 0;
	Z_StepsToJumpAllRoad = 0;

	X_Position = Y_Position = Z_Position = 0;

	X_StepCounter = Y_StepCounter = Z_StepCounter = 0;

	NumberOfRunningMotor = 0;
	IsRunningHome = false;

	noInterrupts();

	// Reset register relate to Timer 3, 4, 5
	TCCR3A = TCCR4A = TCCR5A = 0;
	TCCR3B = TCCR4B = TCCR5B = 0;
	TCNT3 = TCNT4 = TCNT5 = 0;

	// Set prescaler 8 to Timer 3, 4, 5
	TCCR3B |= (1 << WGM32);
	TCCR5B |= (1 << WGM52);
	TCCR4B |= (1 << WGM42);
	
	// Set CTC mode to Timer 3, 4, 5
	TCCR4B |= (1 << CS41);
	TCCR3B |= (1 << CS31);
	TCCR5B |= (1 << CS51);

	interrupts();

	pinMode(X_ENABLE_PIN, OUTPUT);
	pinMode(Y_ENABLE_PIN, OUTPUT);
	pinMode(Z_ENABLE_PIN, OUTPUT);

	digitalWrite(X_ENABLE_PIN, LOW);
	digitalWrite(Y_ENABLE_PIN, LOW);
	digitalWrite(Z_ENABLE_PIN, LOW);
}


ISR(TIMER3_COMPA_vect)
{ 
	X_StepCounter++;

	if (X_StepCounter > CNC3Axis.GetStepsToJumpAllRoad(X_AXIS) || (CNC3Axis.IsRunningHome == true && READ(X_ENDSTOP_PIN) == 0))
	{
		TurnOnInterrupt(X_TIMER, false);
		X_StepCounter = 0;
		--CNC3Axis.NumberOfRunningMotor;
		if (CNC3Axis.NumberOfRunningMotor == 0)
		{
			CNC3Axis.IsRunningHome = false;			
		}
		return;
	}

	TOGGLE(X_PULSE_PIN);
}

ISR(TIMER4_COMPA_vect)
{
	Y_StepCounter++;

	if (Y_StepCounter > CNC3Axis.GetStepsToJumpAllRoad(Y_AXIS) || (CNC3Axis.IsRunningHome == true && READ(Y_ENDSTOP_PIN) == 0))
	{
		TurnOnInterrupt(Y_TIMER, false);
		Y_StepCounter = 0;
		--CNC3Axis.NumberOfRunningMotor;
		if (CNC3Axis.NumberOfRunningMotor == 0)
		{
			CNC3Axis.IsRunningHome = false;
		}
		return;
	}

	TOGGLE(Y_PULSE_PIN);
	
}

ISR(TIMER5_COMPA_vect)
{
	Z_StepCounter++;

	if (Z_StepCounter > CNC3Axis.GetStepsToJumpAllRoad(Z_AXIS) || (CNC3Axis.IsRunningHome == true && READ(Z_ENDSTOP_PIN) == 0))
	{
		TurnOnInterrupt(Z_TIMER, false);
		Z_StepCounter = 0;
		--CNC3Axis.NumberOfRunningMotor;
		if (CNC3Axis.NumberOfRunningMotor == 0)
		{
			CNC3Axis.IsRunningHome = false;
		}
		return;
	}

	TOGGLE(Z_PULSE_PIN);
	
}

void CNC3AxisClass::SetAxisStepsPerUnit(uint16_t xSteps, uint16_t ySteps, uint16_t zSteps)
{
	X_StepsPerMm = xSteps;
	Y_StepsPerMm = ySteps;
	Z_StepsPerMm = zSteps;
}

void CNC3AxisClass::SetMaxFeedRate(uint16_t xSpeed, uint16_t ySpeed, uint16_t zSpeed)
{
	X_MaxFeedRate = xSpeed;
	Y_MaxFeedRate = ySpeed;
	Z_MaxFeedRate = zSpeed;
}

void CNC3AxisClass::SetMaxPosition(uint16_t xPos, uint16_t yPos, uint16_t zPos)
{
	X_MaxPosition = xPos;
	Y_MaxPosition = yPos;
	Z_MaxPosition = zPos;
}

void CNC3AxisClass::SetHomeDirection(DIRECTION xDir, DIRECTION yDir, DIRECTION zDir)
{
	X_HomeDirection = xDir;
	Y_HomeDirection = yDir;
	Z_HomeDirection = zDir;

	if (X_HomeDirection == LEFT)
	{
		X_UpValue = HIGH;
	}
	else
	{
		X_UpValue = LOW;
	}

	if (Y_HomeDirection == BACKWARD)
	{
		Y_UpValue = HIGH;
	}
	else
	{
		Y_UpValue = LOW;
	}

	if (Z_HomeDirection == UP)
	{
		Z_UpValue = HIGH;
	}
	else
	{
		Z_UpValue = LOW;
	}

	digitalWrite(X_Direction, X_UpValue);
	digitalWrite(Y_Direction, Y_UpValue);
	digitalWrite(Z_Direction, Z_UpValue);

}

void CNC3AxisClass::SetStepPulsePin(uint8_t xPin, uint8_t yPin, uint8_t zPin)
{
	X_PulsePin = xPin;
	Y_PulsePin = yPin;
	Z_PulsePin = zPin;

	pinMode(X_PulsePin, OUTPUT);
	pinMode(Y_PulsePin, OUTPUT);
	pinMode(Z_PulsePin, OUTPUT);

	digitalWrite(X_PulsePin, LOW);
	digitalWrite(Y_PulsePin, LOW);
	digitalWrite(Z_PulsePin, LOW);
}

void CNC3AxisClass::SetStepDirectionPin(uint8_t xDir, uint8_t yDir, uint8_t zDir)
{
	X_DirectionPin = xDir;
	Y_DirectionPin = yDir;
	Z_DirectionPin = zDir;

	pinMode(X_DirectionPin, OUTPUT);
	pinMode(Y_DirectionPin, OUTPUT);
	pinMode(Z_DirectionPin, OUTPUT);

	digitalWrite(X_DirectionPin, X_UpValue);
	digitalWrite(Y_DirectionPin, Y_UpValue);
	digitalWrite(Z_DirectionPin, Z_UpValue);
}

void CNC3AxisClass::SetEndstopPin(uint8_t xEndstopPin, uint8_t yEndstopPin, uint8_t zEndstopPin)
{
	X_EndstopPin = xEndstopPin;
	Y_EndstopPin = yEndstopPin;
	Z_EndstopPin = zEndstopPin;

	pinMode(X_EndstopPin, INPUT_PULLUP);
	pinMode(Y_EndstopPin, INPUT_PULLUP);
	pinMode(Z_EndstopPin, INPUT_PULLUP);
}

void CNC3AxisClass::SetEndstopHomeVoltage(uint8_t value)
{
	X_EndstopHomeVoltage = value;
	Y_EndstopHomeVoltage = value;
	Z_EndstopHomeVoltage = value;
}

void CNC3AxisClass::MoveHome()
{
	IsRunningHome = true;
	X_Position = 5000;
	Y_Position = 5000;
	Z_Position = 5000;
	Move(0, 0, 0);
}

void CNC3AxisClass::MoveXHome()
{
	IsRunningHome = true;
	X_Position = 5000;
	MoveX(0);
}

void CNC3AxisClass::MoveYHome()
{
	IsRunningHome = true;
	Y_Position = 5000;
	MoveY(0);
}

void CNC3AxisClass::MoveZHome()
{
	IsRunningHome = true;
	Z_Position = 5000;
	MoveZ(0);
}

int CNC3AxisClass::GetXPosition()
{
	return X_Position;
}

int CNC3AxisClass::GetYPosition()
{
	return Y_Position;
}

int CNC3AxisClass::GetZPosition()
{
	return Z_Position;
}

void CNC3AxisClass::Move(uint16_t xPos, uint16_t yPos, uint16_t zPos)
{
	int x_Offset = xPos - X_Position;
	int y_Offset = yPos - Y_Position;
	int z_Offset = zPos - Z_Position;

	if (x_Offset > 0)
	{
		setDirection(X_AXIS, INCREASE);
	}
	else if (x_Offset < 0)
	{
		setDirection(X_AXIS, DECREASE);
	}

	if (y_Offset > 0)
	{
		setDirection(Y_AXIS, INCREASE);
	}
	else if (y_Offset < 0)
	{
		setDirection(Y_AXIS, DECREASE);
	}

	if (z_Offset > 0)
	{
		setDirection(Z_AXIS, INCREASE);
	}
	else if (z_Offset < 0)
	{
		setDirection(Z_AXIS, DECREASE);
	}

	x_Offset = abs(x_Offset);
	y_Offset = abs(y_Offset);
	z_Offset = abs(z_Offset);

	double lengthOfRoad = sqrt(pow(x_Offset, 2) + pow(y_Offset, 2) + pow(z_Offset, 2));
	double timeForCompleteRoad = lengthOfRoad / FeedRate;
	double timeForCompleteXRoad = (double)x_Offset / X_MaxFeedRate;
	double timeForCompleteYRoad = (double)y_Offset / Y_MaxFeedRate;
	double timeForCompleteZRoad = (double)z_Offset / Z_MaxFeedRate;

	if (timeForCompleteRoad < timeForCompleteXRoad)
	{
		timeForCompleteRoad = timeForCompleteXRoad;
	}

	if (x_Offset != 0)
	{
		X_Position = xPos;
		X_StepsToJumpAllRoad = (uint32_t)x_Offset * (uint32_t)X_StepsPerMm;
		double x_TimeForJumpOneStep = timeForCompleteRoad / X_StepsToJumpAllRoad;

		//Serial.println();
		//Serial.println(X_StepsToJumpAllRoad);

		if (IsRunningHome == true)
		{
			x_TimeForJumpOneStep = (float)1 / (X_MaxFeedRate * X_StepsPerMm);
		}

		X_COMPARE_VALUE = calCompareValue(x_TimeForJumpOneStep);

		X_StepsToJumpAllRoad *= 2;
		digitalWrite(X_PulsePin, LOW);
		X_StepCounter = 0;
		TurnOnInterrupt(X_TIMER, true);
		NumberOfRunningMotor++;
	}
	if (y_Offset != 0)
	{
		Y_Position = yPos;
		Y_StepsToJumpAllRoad = (uint32_t)y_Offset * (uint32_t)Y_StepsPerMm;
		double y_TimeForJumpOneStep = timeForCompleteRoad / Y_StepsToJumpAllRoad;

		if (IsRunningHome == true)
		{
			y_TimeForJumpOneStep = (float)1 / (Y_MaxFeedRate * Y_StepsPerMm);
		}

		Y_COMPARE_VALUE = calCompareValue(y_TimeForJumpOneStep);

		Y_StepsToJumpAllRoad *= 2;
		digitalWrite(Y_PulsePin, LOW);
		Y_StepCounter = 0;
		TurnOnInterrupt(Y_TIMER, true);
		NumberOfRunningMotor++;
	}
	if (z_Offset != 0)
	{
		Z_Position = zPos;
		Z_StepsToJumpAllRoad = (uint32_t)z_Offset * (uint32_t)Z_StepsPerMm;
		double z_TimeForJumpOneStep = (float)1 / (Z_MaxFeedRate * Z_StepsPerMm); //timeForCompleteZRoad / Z_StepsToJumpAllRoad;

		if (IsRunningHome == true)
		{
			z_TimeForJumpOneStep = (float)1 / (Z_MaxFeedRate * Z_StepsPerMm);
		}

		Z_COMPARE_VALUE = calCompareValue(z_TimeForJumpOneStep);

		Z_StepsToJumpAllRoad *= 2;
		digitalWrite(Z_PulsePin, LOW);
		Z_StepCounter = 0;
		TurnOnInterrupt(Z_TIMER, true);
		NumberOfRunningMotor++;
	}
}

void CNC3AxisClass::MoveX(uint16_t xPos)
{
	Move(xPos, GetYPosition(), GetZPosition());
}

void CNC3AxisClass::MoveY(uint16_t yPos)
{
	Move(GetXPosition(), yPos, GetZPosition());
}

void CNC3AxisClass::MoveZ(uint16_t zPos)
{
	Move(GetXPosition(), GetYPosition(), zPos);
}

uint32_t CNC3AxisClass::GetStepsToJumpAllRoad(AXIS axis)
{
	switch (axis)
	{
	case X_AXIS:
		return X_StepsToJumpAllRoad;
		break;
	case Y_AXIS:
		return Y_StepsToJumpAllRoad;
		break;
	case Z_AXIS:
		return Z_StepsToJumpAllRoad;
		break;
	default:
		break;
	}
}

uint16_t CNC3AxisClass::calCompareValue(double timeForAStep)
{
	uint32_t f = (double)1 / timeForAStep;
	return (((double)F_CPU / (f * PRESCALER * 2)) - 1);
}

void TurnOnInterrupt(uint8_t timerOder, bool answer)
{
	if (answer == true)
	{
		switch (timerOder)
		{
		case 3:
			TIMSK3 |= (1 << OCIE3A);
			break;
		case 4:
			TIMSK4 |= (1 << OCIE4A);
			break;
		case 5:
			TIMSK5 |= (1 << OCIE5A);
			break;
		default:
			break;
		}
	}
	else
	{
		switch (timerOder)
		{
		case 3:
			TIMSK3 &= ~(1 << OCIE3A);
			break;
		case 4:
			TIMSK4 &= ~(1 << OCIE4A);
			break;
		case 5:
			TIMSK5 &= ~(1 << OCIE5A);
			break;
		default:
			break;
		}
	}
}

void CNC3AxisClass::setDirection(AXIS axis, VARIATION variation)
{
	if (variation == INCREASE)
	{
		switch (axis)
		{
		case X_AXIS:
			digitalWrite(X_DIRECTION_PIN, X_UpValue);
			X_Direction = variation;
			break;
		case Y_AXIS:
			digitalWrite(Y_DIRECTION_PIN, Y_UpValue);
			Y_Direction = variation;
			break;
		case Z_AXIS:
			digitalWrite(Z_DIRECTION_PIN, Z_UpValue);
			Z_Direction = variation;
			break;
		default:
			break;
		}
	}
	else
	{
		switch (axis)
		{
		case X_AXIS:
			digitalWrite(X_DIRECTION_PIN, X_UpValue ^ 1);
			X_Direction = variation;
			break;
		case Y_AXIS:
			digitalWrite(Y_DIRECTION_PIN, Y_UpValue ^ 1);
			Y_Direction = variation;
			break;
		case Z_AXIS:
			digitalWrite(Z_DIRECTION_PIN, Y_UpValue ^ 1);
			Z_Direction = variation;
			break;
		default:
			break;
		}
	}
}

CNC3AxisClass CNC3Axis;

