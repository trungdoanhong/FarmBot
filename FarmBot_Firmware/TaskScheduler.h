// TaskScheduler.h

#ifndef _TASKSCHEDULER_h
#define _TASKSCHEDULER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

struct Thread
{
	void(*Func)(void) = NULL;
	uint16_t Time = 0;
	uint16_t CountDown = 0;
	bool Enough = true;
};

class TaskSchedulerClass
{
public:
	Thread *ThreadArray;
	void Init();
	void Add(void(*func)(), uint16_t time);
	void Change(void(*func)(), uint16_t time);
	void Run();
	void Stop();
	void Stop(void(*func)());
	void Resum(void(*func)());
	void Delete(void(*func)());
	bool IsFunctionExit(void(*func)());
	void Execute();
private:
	uint8_t threadNumber = 0;
	uint16_t interruptTime = 0;
	uint16_t timeCounter = 0;
	uint16_t funcCallingTime = 0;
	uint8_t nearestThreadOrder = 0;

	void sort();
};

extern TaskSchedulerClass TaskScheduler;

#endif

