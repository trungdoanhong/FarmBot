#include "CNC3Axis.h"
#include "GCodeExecute.h"
#include "GCodeReceiver.h"
#include "TaskScheduler.h"
#include <StandardCplusplus.h> // Copy StandardCplusplus folder to Mydocument\Arduino\libraries to use below libraries
#include <vector>
#include "Constants.h"
#include "idDHTLib.h"

#define SOIL_SENSOR_SERVO_PIN 6
#define SOIL_SENSOR_PIN A15
#define LAMP_PIN 26
#define FAN_PIN 28
#define VACCUM_PIN 9
#define PUMP_PIN 10

#define ON HIGH
#define OFF LOW

#define RELAY_ON LOW
#define RELAY_OFF HIGH

#define SERVO_COMPARE_VALUE OCR1A

using namespace std;

vector<String> GCodeQueue;

uint16_t Timer1InterruptCounter = 0;
uint16_t ValueForServoPeriod = 200;	// 20 ms = 20 000 us
uint16_t ValueForServoFallingEdge = 10; // 1 ms = 1000 us

GCodeReceiver GcodeReceiver;
GCodeExecute GcodeExecute;

bool IsPause = false;

// Sensor

int idDHTLibPin = 2; 
int idDHTLibIntNumber = 0;

void dhtLib_wrapper(); 

idDHTLib DHTLib(idDHTLibPin, idDHTLibIntNumber, dhtLib_wrapper);

void dhtLib_wrapper() {
	DHTLib.dht11Callback(); 
}

float HumidityValue = 0;
float TemperatureValue = 0;
float SoilMoistureValue = 0;

void setup()
{
	Serial.begin(9600);

	TaskScheduler.Init();
	/*TaskScheduler.Add(WatchDog, 1000);
	TaskScheduler.Add(WatchDog2, 1500);*/
	TaskScheduler.Run();

	CNC3Axis.Init();
	CNC3Axis.SetAxisStepsPerUnit(80, 80, 400);
	CNC3Axis.SetMaxFeedRate(50, 50, 10);
	CNC3Axis.SetMaxPosition(300, 800, 200);
	CNC3Axis.SetHomeDirection(LEFT, BACKWARD, UP);
	CNC3Axis.FeedRate = 50;
	CNC3Axis.SetEndstopHomeVoltage(LOW);

	GcodeReceiver.Init(&GCodeQueue, &Serial, 9600);
	GcodeReceiver.AddPriorityOrder("IsFarmBot", Confirm);	
	GcodeReceiver.AddPriorityOrder("State", GetGCodeState);
	GcodeReceiver.AddPriorityOrder("EndStopState", EndStopState);
	GcodeReceiver.AddPriorityOrder("Position", Position);

	GcodeExecute.Init(&GCodeQueue);
	GcodeExecute.Add("G00", 'X', 'Y', 'Z', MoveEndActuator);
	GcodeExecute.Add("G01", 'X', 'Y', 'Z', MoveEndActuator);
	GcodeExecute.Add("G28", 'X', 'Y', 'Z', AutoHome);

	GcodeExecute.Add("G04", 'P', 'S', Pause);
	GcodeExecute.Add("G40", 'S', ReverseSoilSensor);
	GcodeExecute.Add("G41", 'P', TurnOnPump);
	GcodeExecute.Add("G42", 'V', TurnVaccum);
	GcodeExecute.Add("G43", 'F', TurnFan);
	GcodeExecute.Add("G44", 'L', TurnLamp);

	GcodeExecute.Add("M10", ReadSoilSensor);
	GcodeExecute.Add("M11", ReadAirTemperature);
	GcodeExecute.Add("M12", ReadAirHumidity);

	Serial.println(" Init Success !");

	InitPinMode();
	InitServo();
}

void loop()
{
	GcodeReceiver.Execute();
	GcodeExecute.Run();
	WhenFinishMove();
}

void InitServo()
{
	// Reset register relate to Timer 1
	TCCR1A = 0;
	TCCR1B = 0;
	TCNT1 = 0;
	
	TCCR1B |= (1 << WGM12);				// Set prescaler 8 to Timer 1	
	TCCR1B |= (1 << CS11);				// Set CTC mode to Timer 1

	SERVO_COMPARE_VALUE = 199;			// Interrupt every 0.1 ms

	TurnOffServo();
}

void TurnOnServo()
{
	TIMSK1 |= (1 << OCIE1A);
}

void TurnOffServo()
{
	TIMSK1 &= ~(1 << OCIE1A);
}

void RotateServo(uint8_t angle)
{
	ValueForServoFallingEdge = map(angle, 0, 180, 5, 24);
}

ISR(TIMER1_COMPA_vect)
{
	Timer1InterruptCounter++;
	if (Timer1InterruptCounter == ValueForServoFallingEdge)
	{
		digitalWrite(SOIL_SENSOR_SERVO_PIN, LOW);
	}
	
	if (Timer1InterruptCounter == ValueForServoPeriod)
	{
		digitalWrite(SOIL_SENSOR_SERVO_PIN, HIGH);
		Timer1InterruptCounter = 0;
	}
}

void InitPinMode()
{
	pinMode(SOIL_SENSOR_SERVO_PIN, OUTPUT);
	pinMode(LAMP_PIN, OUTPUT);
	pinMode(PUMP_PIN, OUTPUT);
	pinMode(VACCUM_PIN, OUTPUT);
	pinMode(FAN_PIN, OUTPUT);

	digitalWrite(FAN_PIN, RELAY_OFF);
	digitalWrite(LAMP_PIN, RELAY_OFF);
}

void Confirm()
{
	Serial.println("YesFarmBot");
}

void GetGCodeState()
{
	if (GcodeExecute.IsRunning == true)
	{
		//Serial.println("GcodeRunning");
	}
	else
	{
		Serial.println("GcodeDone");
	}
}

void WhenFinishMove()
{
	if (CNC3Axis.NumberOfRunningMotor == 0 & IsPause == false)
	{
		GcodeExecute.IsRunning = false;
	}
}

void MoveEndActuator(float xPos, float yPos, float zPos)
{
	if (xPos == NULL_NUMBER)
	{
		xPos = CNC3Axis.GetXPosition();
	}

	if (yPos == NULL_NUMBER)
	{
		yPos = CNC3Axis.GetYPosition();
	}

	if (zPos == NULL_NUMBER)
	{
		zPos = CNC3Axis.GetZPosition();
	}

	//Serial.print(xPos);
	//Serial.print(", ");
	//Serial.print(yPos);
	//Serial.print(", ");
	//Serial.print(zPos);

	CNC3Axis.Move((uint16_t)xPos, (uint16_t)yPos, (uint16_t)zPos);
}

void AutoHome(float xHome, float yHome, float zHome)
{
	if (xHome != NULL_NUMBER && yHome != NULL_NUMBER && zHome != NULL_NUMBER)
	{
		CNC3Axis.MoveHome();
		return;
	}
	if (xHome != NULL_NUMBER)
	{
		CNC3Axis.MoveXHome();
	}
	if (yHome != NULL_NUMBER)
	{
		CNC3Axis.MoveYHome();
	}
	if (zHome != NULL_NUMBER)
	{
		CNC3Axis.MoveZHome();
	}
}

void Pause(float sec, float milisec)
{
	if (sec == NULL_NUMBER)
	{
		sec = 0;
	}
	if (milisec == NULL_NUMBER)
	{
		milisec = 0;
	}
	IsPause = true;
	TaskScheduler.Change(Resume, sec * 1000 + milisec);
	TaskScheduler.Resum(Resume);
}

void Resume()
{
	IsPause = false;
	TaskScheduler.Stop(Resume);
}

void ReverseSoilSensor(float turnAngle)
{
	TurnOnServo();
	RotateServo(turnAngle);

	GcodeExecute.IsRunning = false;
}

void TurnFan(float value)
{
	if (value != 0)
	{
		digitalWrite(FAN_PIN, ON);
	}
	else
	{
		digitalWrite(FAN_PIN, OFF);
	}
}

void TurnLamp(float value)
{
	if (value != 0)
	{
		digitalWrite(LAMP_PIN, ON);
	}
	else
	{
		digitalWrite(LAMP_PIN, OFF);
	}
}

void TurnVaccum(float value)
{
	if (value != 0)
	{
		digitalWrite(VACCUM_PIN, ON);
	}
	else
	{
		digitalWrite(VACCUM_PIN, OFF);
	}
}

void TurnOnPump(float time)
{
	digitalWrite(PUMP_PIN, ON);
	TaskScheduler.Change(StopPump, time);
	TaskScheduler.Resum(StopPump);
	Serial.println("Pump On");
}

void StopPump()
{
	digitalWrite(PUMP_PIN, OFF);
	TaskScheduler.Stop(StopPump);
	Serial.println("Pump Off");
}

void ReadSoilSensor()
{
	uint16_t analogValue = analogRead(SOIL_SENSOR_PIN);
	SoilMoistureValue = map(analogValue, 0, 1023, 0, 100);
	Serial.println(String("Soil-") + analogValue);
}

void ReadAirTemperature()
{
	DHTLib.acquire();
	while (DHTLib.acquiring())
		;
	TemperatureValue = DHTLib.getCelsius();
	Serial.println(String("Temp-") + TemperatureValue);
}

void ReadAirHumidity()
{
	DHTLib.acquire();
	while (DHTLib.acquiring())
		;
	HumidityValue = DHTLib.getHumidity();
	Serial.println(String("Humi-") + HumidityValue);
}

void WatchDog()
{
	Serial.print("W-");
	Serial.println(millis());
}

void WatchDog2()
{
	Serial.print("W2-");
	Serial.println(millis());
}

void EndStopState()
{
	Serial.print(digitalRead(X_ENDSTOP_PIN));
	Serial.print(" ,");
	Serial.print(digitalRead(Y_ENDSTOP_PIN));
	Serial.print(" ,");
	Serial.println(digitalRead(Z_ENDSTOP_PIN));
}

void Position()
{
	Serial.print(CNC3Axis.GetXPosition());
	Serial.print(" ,");
	Serial.print(CNC3Axis.GetYPosition());
	Serial.print(" ,");
	Serial.println(CNC3Axis.GetZPosition());
}