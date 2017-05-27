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
	
	checkAndRunFunction3Argument(prefix, keyValues);
	checkAndRunFunction2Argument(prefix, keyValues);
	checkAndRunFunction1Argument(prefix, keyValues);
	checkAndRunFunction0Argument(prefix, keyValues);

	//------

	GCodeQueue->erase(GCodeQueue->begin());
	IsRunning = true;

}

void GCodeExecute::checkAndRunFunction3Argument(String prefix, vector<KeyValue> keyValues)
{
	for (uint8_t index = 0; index < ThreeArgumentFunctions.size(); index++)
	{
		if (prefix == ThreeArgumentFunctions[index].Code)		// find out 
		{
			for (uint8_t index2 = 0; index2 < 3; index2++)		// Find values for arguments
			{
				ThreeArgumentFunctions[index].Agruments[index2] = NULL_NUMBER;

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
}

void GCodeExecute::checkAndRunFunction2Argument(String prefix, vector<KeyValue> keyValues)
{
	for (uint8_t index = 0; index < TwoArgumentFunctions.size(); index++)
	{
		if (prefix != TwoArgumentFunctions[index].Code)		// find out 
			return;
		for (uint8_t index2 = 0; index2 < 2; index2++)		// Find values for arguments
		{
			TwoArgumentFunctions[index].Agruments[index2] = NULL_NUMBER;

			for (uint8_t index3 = 0; index3 < keyValues.size(); index3++) // Browse key-value pairs
			{
				if (TwoArgumentFunctions[index].Keys[index2] == keyValues[index3].Key) // Have a corresponding key
				{
					TwoArgumentFunctions[index].Agruments[index2] = keyValues[index3].Value;
				}
			}

		}

		float argu1 = TwoArgumentFunctions[index].Agruments[0];
		float argu2 = TwoArgumentFunctions[index].Agruments[1];

		Serial.print(argu1);
		Serial.print(", ");
		Serial.println(argu2);

		TwoArgumentFunctions[index].Function(argu1, argu2);
		
	}
}

void GCodeExecute::checkAndRunFunction1Argument(String prefix, vector<KeyValue> keyValues)
{
	for (uint8_t index = 0; index < OneArgumentFunctions.size(); index++)
	{
		if (prefix != OneArgumentFunctions[index].Code)		// find out 
			continue;
		OneArgumentFunctions[index].Agrument = NULL_NUMBER;

		for (uint8_t index3 = 0; index3 < keyValues.size(); index3++) // Browse key-value pairs
		{
			if (OneArgumentFunctions[index].Key == keyValues[index3].Key) // Have a corresponding key
			{
				OneArgumentFunctions[index].Agrument = keyValues[index3].Value;
			}
		}

		float argu1 = OneArgumentFunctions[index].Agrument;

		Serial.println(argu1);

		OneArgumentFunctions[index].Function(argu1);
	}
}

void GCodeExecute::checkAndRunFunction0Argument(String prefix, vector<KeyValue> keyValues)
{
	for (uint8_t index = 0; index < NoArgumentFunctions.size(); index++)
	{
		if (prefix != NoArgumentFunctions[index].Code)		// find out 
			continue;

		NoArgumentFunctions[index].Function();
	}
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

