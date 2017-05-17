// 
// 
// 

#include "GCodeExecute.h"

void GCodeExecute::Init(vector<String>* gCodeQueue)
{
	this->GCodeQueue = gCodeQueue;
}

void GCodeExecute::Add(String Code, char argu1, char argu2, char argu3, void(*func)(float, float, float))
{ 
	ThreeArgumentFunction arguFuncTemp;

	arguFuncTemp.Code = Code;
	arguFuncTemp.Keys[0] = argu1;
	arguFuncTemp.Keys[1] = argu2;
	arguFuncTemp.Keys[2] = argu3;
	arguFuncTemp.Function = func;

	ThreeArgumentFunctions.push_back(arguFuncTemp);
}
void GCodeExecute::Add(String Code, char argu1, char argu2, void(*func)(float, float))
{
	TwoArgumentFunction arguFuncTemp;

	arguFuncTemp.Code = Code;
	arguFuncTemp.Keys[0] = argu1;
	arguFuncTemp.Keys[1] = argu2;
	arguFuncTemp.Function = func;

	TwoArgumentFunctions.push_back(arguFuncTemp);
}
void GCodeExecute::Add(String Code, char argu1, void(*func)(float))
{
	OneArgumentFunction arguFuncTemp;

	arguFuncTemp.Code = Code;
	arguFuncTemp.Key = argu1;
	arguFuncTemp.Function = func;

	OneArgumentFunctions.push_back(arguFuncTemp);
}
void GCodeExecute::Add(String Code, void(*func)())
{
	NoArgumentFunction arguFuncTemp;

	arguFuncTemp.Code = Code;
	arguFuncTemp.Function = func;

	NoArgumentFunctions.push_back(arguFuncTemp);
}

void GCodeExecute::Run()
{
	if (GCodeQueue->size() == 0 || IsRunning == true)
		return;

	String GcodeInProcessing = GCodeQueue->operator[](0);
	vector<KeyValue> keyValues = getKeyValues(GcodeInProcessing);

	for (uint8_t i = 0; i < keyValues.size(); i++)
	{
		Serial.print(keyValues[i].Key);
		Serial.print("-");
		Serial.println(keyValues[i].Value);
	}
	
	// Make a prefix like "G01" from key-value pair
	String prefix = String(keyValues[0].Key);
	if (keyValues[0].Value < 10)
	{
		prefix += String("0") + String((int)keyValues[0].Value);
	}
	else
	{
		prefix += String((int)keyValues[0].Value);
	}

	// Find corresponding function with prefix 
	for (uint8_t index = 0; index < ThreeArgumentFunctions.size(); index++)
	{
		if (prefix == ThreeArgumentFunctions[index].Code)		// find out 
		{
			for (uint8_t index2 = 0; index2 < 3; index2++)		// Find values for arguments
			{
				ThreeArgumentFunctions[index].Agruments[index2] = 98765;

				for (uint8_t index3 = 0; index3 < keyValues.size(); index3++) // Browse key-value pairs
				{
					if (ThreeArgumentFunctions[index].Keys[index2] == keyValues[index3].Key) // Have a corresponding key
					{
						ThreeArgumentFunctions[index].Agruments[index2] = keyValues[index3].Value;
					}
				}
				
			}

			float argu1 = ThreeArgumentFunctions[index].Agruments[0];
			float argu2 = ThreeArgumentFunctions[index].Agruments[1];
			float argu3 = ThreeArgumentFunctions[index].Agruments[2];

			Serial.print(argu1);
			Serial.print(", ");
			Serial.print(argu2);
			Serial.print(", ");
			Serial.println(argu3);

			ThreeArgumentFunctions[index].Function(argu1, argu2, argu3);
		}
	}

	GCodeQueue->erase(GCodeQueue->begin());
	IsRunning = true;

}

vector<KeyValue> GCodeExecute::getKeyValues(String code)
{
	String splitWord = "";
	vector<KeyValue> keyValues;
	code += " ";
	for (uint16_t i = 0; i < code.length(); i++)
	{
		if (code[i] == ' ')
		{
			if (splitWord == "")
				continue;
			KeyValue keyValue;
			keyValue.Key = splitWord[0];
			keyValue.Value = splitWord.substring(1).toFloat();
			keyValues.push_back(keyValue);
			splitWord = "";
			continue;
		}
		splitWord += String(code[i]);
	}
	return keyValues;
}

