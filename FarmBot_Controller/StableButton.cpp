// 
// 
// 

#include "StableButton.h"

void StableButtonClass::Init(uint8_t* btArr, uint8_t number)
{	
	if (buttonArray != NULL)
	{
		delete[] buttonArray;
	}

	if (maxDelayArray != NULL)
	{
		delete[] maxDelayArray;
	}

	if (isUpArray != NULL)
	{
		delete[] isUpArray;
	}

	if (counterArray != NULL)
	{
		delete[] counterArray;
	}

	buttonNumber = number;

	buttonArray = new Button[number];
	maxDelayArray = new uint16_t[number];
	isUpArray = new bool[number];
	counterArray = new unsigned long[number];

	for (uint8_t index = 0; index < buttonNumber; index++)
	{
		buttonArray[index].pin = btArr[index];
		pinMode(buttonArray[index].pin, INPUT_PULLUP);

		maxDelayArray[index] = 1000;
		isUpArray[index] = true;
		counterArray[index] = 0;
	}
}

bool StableButtonClass::IsPressing(uint8_t pin)
{
	if (digitalRead(pin) == 0)
		return true;
	return false;
}

bool StableButtonClass::IsPressed(uint8_t pin)
{
	uint8_t index;				// order of pin in button array

	for (index = 0; index < buttonNumber; index++)		// find order of pin in array
	{
		if (buttonArray[index].pin == pin)
			break;
	}

	if (index == buttonNumber)	// if use check a button undeclare. Exit function
		return false;

	if (IsPressing(pin) == true)  // if button is pressing
	{
		if ((millis() - counterArray[index]) > maxDelayArray[index])
		{
			isUpArray[index] = true;
			maxDelayArray[index] = 100;
		}

		if (isUpArray[index] == true)
		{
      if ((millis() - counterArray[index]) < 20)   // avoid noise
        return false;
			counterArray[index] = millis();
			isUpArray[index] = false;
			return true;
		}
	}
	else
	{
		counterArray[index] = millis();
		isUpArray[index] = true;
		maxDelayArray[index] = 1000;
	}
	return false;
}

StableButtonClass StableButton;

