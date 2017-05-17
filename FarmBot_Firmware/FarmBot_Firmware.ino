#include "CNC3Axis.h"
#include "GCodeExecute.h"
#include "GCodeReceiver.h"
#include "TaskScheduler.h"
#include <StandardCplusplus.h> // Copy StandardCplusplus folder to Mydocument\Arduino\libraries to use below libraries
#include <vector>


using namespace std;

vector<String> GCodeQueue;

GCodeReceiver GcodeReceiver;
GCodeExecute GcodeExecute;

void setup()
{
	Serial.begin(9600);

	TaskScheduler.Init();

	CNC3Axis.Init();
	CNC3Axis.SetAxisStepsPerUnit(80, 80, 800);
	CNC3Axis.SetMaxFeedRate(300, 300, 5);
	CNC3Axis.SetMaxPosition(300, 800, 200);
	CNC3Axis.SetHomeDirection(LEFT, BACKWARD, UP);
	CNC3Axis.FeedRate = 150;
	CNC3Axis.SetEndstopHomeVoltage(LOW);

	GcodeReceiver.Init(&GCodeQueue, &Serial, 9600);
	GcodeReceiver.AddPriorityOrder("IsFarmBot", Confirm);	

	GcodeExecute.Init(&GCodeQueue);
	GcodeExecute.Add("G0", "X", "Y", "Z", MoveEndActuator);
	GcodeExecute.Add("G28", "X", "Y", "Z", AutoHome);
	GcodeExecute.Add("G40", "S", ReverseSoilSensor);
	GcodeExecute.Add("G43", "F", TurnOnFan);

	Serial.println(" Init Success !");
}

void loop()
{
	GcodeReceiver.Execute();
	GcodeExecute.Run();
}

void Confirm()
{
	Serial.println("YesFarmBot");
}

void MoveEndActuator(float xPos, float yPos, float zPos)
{

}

void AutoHome(float xHome, float yHome, float zHome)
{

}

void ReverseSoilSensor(float turnAngle)
{

}

void TurnOnFan(float time)
{

}