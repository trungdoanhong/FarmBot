// GCodeExecute.h

#ifndef _GCODEEXECUTE_h
#define _GCODEEXECUTE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <StandardCplusplus.h>
#include <vector>

using namespace std;

class KeyValue
{
public:
	char Key;
	float Value;
};

class ThreeArgumentFunction
{
public:
	String Code;
	char Keys[3];
	float Agruments[3];
	void(*Function)(float, float, float);
};

class TwoArgumentFunction
{
public:
	String Code;
	char Keys[2];
	float Agruments[2];
	void(*Function)(float, float);
};

class OneArgumentFunction
{
public:
	String Code;
	char Key;
	float Agrument;
	void(*Function)(float);
};

class NoArgumentFunction
{
public:
	String Code;
	void(*Function)();
};

class GCodeExecute
{
public:
	void Init(vector<String>*);
	void Add(String Code, char argu1, char argu2, char argu3, void(*func)(float, float, float));
	void Add(String Code, char argu1, char argu2, void(*func)(float, float));
	void Add(String Code, char argu1, void(*func)(float));
	void Add(String Code, void(*func)());
	void Run();

	vector<String>* GCodeQueue;
	bool IsRunning;
private:
	vector<KeyValue> getKeyValues(String code);

	vector<ThreeArgumentFunction> ThreeArgumentFunctions;
	vector <TwoArgumentFunction> TwoArgumentFunctions;
	vector <OneArgumentFunction> OneArgumentFunctions;
	vector<NoArgumentFunction> NoArgumentFunctions;
};

#endif

