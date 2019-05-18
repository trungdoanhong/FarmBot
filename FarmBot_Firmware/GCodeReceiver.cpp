// 
// 
// 

#include "GCodeReceiver.h"

void GCodeReceiver::Init(vector<String>* gCodeQueue, HardwareSerial* serial, int baudrate)
{
	ReceiveSerial = serial;
	ReceiveSerial->begin(baudrate);
	receiveString.reserve(100);

	isStringComplete = false;
	receiveString = "";

	this->GCodeQueue = gCodeQueue;
}

void GCodeReceiver::Execute()
{
	serialEvent();

	if (!isStringComplete)
		return;

	if (receiveString[0] == 'M' || receiveString[0] == 'G')
	{
		GCodeQueue->push_back(receiveString);
	}

	/*Serial.print("Respond : ");
	Serial.println(receiveString);*/

	for (uint8_t i = 0; i < CodeFunctionPairs.size(); i++)
	{
		if (receiveString == CodeFunctionPairs[i].Key)
		{
			void (*func)() = CodeFunctionPairs[i].GetValue();
			func();
		}
	}

	for (uint8_t i = 0; i < CodeStringPairs.size(); i++)
	{
		if (receiveString.substring(0, CodeStringPairs[i].Key.length()) == CodeStringPairs[i].Key)
		{
			CodeStringPairs[i].Value->operator=(receiveString.substring(CodeStringPairs[i].Key.length() + 1));
		}
	}

	receiveString = "";
	isStringComplete = false;
}

void GCodeReceiver::serialEvent()
{
	// receive every character
	while (ReceiveSerial->available())
	{
		char inChar = (char)ReceiveSerial->read();
		//ReceiveSerial->print(inChar);

		if (inChar == '\n')
		{
			if (receiveString != "")
			{
				isStringComplete = true;
			}
			
			break;
		}

		if (inChar != '\r')
		{
			receiveString += inChar;
		}
	}
}

void GCodeReceiver::AddPriorityOrder(String code, void(*func)())
{
	CodeFunctionPair pairTemp;
	pairTemp.Key = code;
	pairTemp.GetValue() = func;
	CodeFunctionPairs.push_back(pairTemp);
}

void GCodeReceiver::AddPriorityOrder(String code, String* string)
{
	CodeStringPair pairTemp;
	pairTemp.Key = code;
	pairTemp.Value = string;
	CodeStringPairs.push_back(pairTemp);
}


