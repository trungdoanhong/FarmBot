// GCodeExecute.h

#ifndef _GCODEEXECUTE_h
#define _GCODEEXECUTE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class GCodeExecute
{
public:
	void Init(vector<String>*);
	void Add(String, String, String, String, void(*)(float, float, float));
	void Add(String, String, String, void(*)(float, float));
	void Add(String, String, void(*)(float));
	void Add(String, void(*func)());
	void Run();

	vector<String>* GCodeQueue;
	bool IsRunning;
private:
	vector<void(*)(float, float, float)> ThreeArgumentFunctions;
	vector <void(*)(float, float)> TwoArgumentFunctions;
	vector <void(*)(float)> OneArgumentFunctions;
	vector<void(*)> NoArgumentFunctions;
};

#endif

