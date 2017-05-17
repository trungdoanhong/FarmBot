// GCodeReceiver.h

#ifndef _GCODERECEIVER_h
#define _GCODERECEIVER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <StandardCplusplus.h>
#include <vector>

using namespace std;

template <class F>
class Pair
{
public:
	String Key;
	F Value;
	F& GetValue() { return Value; }
	F const& GetValue() const { return Value; }
};

typedef Pair<void(*)()> CodeFunctionPair;
typedef Pair<String*> CodeStringPair;
typedef Pair<int> CodeIntNumerPair;
typedef Pair<float> CodeFloatNumberPair;

class GCodeReceiver
{
public:
	void Init(vector<String>* gCodeQueue, HardwareSerial* serial, int baudrate);
	void AddPriorityOrder(String code, void(*func)());
	void AddPriorityOrder(String code, String* string);
	void AddPriorityOrder(String code, int number);
	void AddPriorityOrder(String code, float number);
	void Execute();

	HardwareSerial* ReceiveSerial;
	int Baudrate;
	vector<String>* GCodeQueue;
	vector<CodeFunctionPair> CodeFunctionPairs;
	vector<CodeStringPair> CodeStringPairs;
	vector<CodeIntNumerPair> CodeIntNumerPairs;
	vector<CodeFloatNumberPair> CodeFloatNumberPairs;

private:
	void serialEvent();
	
	String receiveString;
	bool isStringComplete;
};

#endif

