// 
// 
// 

#include "TaskScheduler.h"

void TaskSchedulerClass::Init()
{
	cli();                                  // Turn off global interrupt

	/* Reset Timer/Counter1 */
	TCCR1A = 0;
	TCCR1B = 0;
	TIMSK1 = 0;

	/* Setup Timer/Counter1 */
	TCCR1B |= (1 << CS11) | (1 << CS10);    // prescale = 64
	TCNT1 = 65286;
	TIMSK1 = (1 << TOIE1);                  // Overflow interrupt enable 

}

//Add a function into Thread Array and run every time

void TaskSchedulerClass::Add(void(*func)(), uint16_t time)
{
	threadNumber++;		// initial number is 0 and increase 1 value before add and function into array
	Thread *threadTemp = new Thread[threadNumber];	// temporary array use to save olde thread array

	for (uint8_t index = 0; index < (threadNumber - 1); index++)
	{
		threadTemp[index] = ThreadArray[index];
	}

	if (ThreadArray != NULL)
	{
		delete[] ThreadArray;
	}

	ThreadArray = threadTemp;
	
	Thread thread;
	thread.Func = func;
	thread.Time = time;
	thread.CountDown = 0;
 
	// Add new thread into array
	ThreadArray[threadNumber - 1] = thread;
}

// Sort every thread increase from small to big base on time.

void TaskSchedulerClass::sort()
{
	Thread tempThread;
	for (uint8_t index = 0; index < threadNumber - 1; index++)
	{
		for (uint8_t index1 = 1; index1 < threadNumber; index1++)
		{
			if (ThreadArray[index].Time > ThreadArray[index1].Time)
			{
				tempThread = ThreadArray[index];
				ThreadArray[index] = ThreadArray[index1];
				ThreadArray[index1] = tempThread;

			}
		}
	}
}

void TaskSchedulerClass::Run()
{
	sort();
	sei();

}

void TaskSchedulerClass::Stop()
{
	cli();
}

void TaskSchedulerClass::Execute()
{
	if (!threadNumber)
		return;

	timeCounter++;
	if (timeCounter < funcCallingTime)
		return;

	//when enough time to call function

	timeCounter = 0;

	if (ThreadArray[nearestThreadOrder].Enough == true)
		ThreadArray[nearestThreadOrder].Func();		// implement function

	for (uint8_t index = 0; index < threadNumber; index++)
	{
		// Set count down time every thread
		ThreadArray[index].CountDown -= funcCallingTime;
	}

	ThreadArray[nearestThreadOrder].CountDown = ThreadArray[nearestThreadOrder].Time;

	nearestThreadOrder = 0;

	for (uint8_t index = 1; index < threadNumber; index++)
	{
		// Find thread order has count down time is smallest
		if (ThreadArray[index].CountDown < ThreadArray[nearestThreadOrder].CountDown)
		{
			nearestThreadOrder = index;
		}
	}

	// Set time to call function in next time
	funcCallingTime = ThreadArray[nearestThreadOrder].CountDown;

}

void TaskSchedulerClass::Change(void(*func)(), uint16_t time)
{
	if (!this->IsFunctionExit(func))
	{
		this->Add(func, time);
		return;
	}
		

	for (uint8_t index = 0; index < threadNumber; index++)
	{ 
		if (ThreadArray[index].Func == func)
		{
			ThreadArray[index].Time = time;
			ThreadArray[index].CountDown = time;
		}
	}
}

void TaskSchedulerClass::Stop(void(*func)())
{
	for (uint8_t index = 0; index < threadNumber; index++)
	{
		if (ThreadArray[index].Func == func)
		{
			ThreadArray[index].Enough = false;
		}
	}
}

void TaskSchedulerClass::Resum(void(*func)())
{
	for (uint8_t index = 0; index < threadNumber; index++)
	{
		if (ThreadArray[index].Func == func)
		{
			ThreadArray[index].Enough = true;
		}
	}
}

void TaskSchedulerClass::Delete(void(*func)())
{
	if (threadNumber > 0)

	threadNumber--;	
	Thread *threadTemp = new Thread[threadNumber];	// temporary array use to save olde thread array

	uint8_t index1 = 0;
	for (uint8_t index2 = 0; index2 < threadNumber + 1; index2++)
	{
		if (ThreadArray[index2].Func != func)
		{
			threadTemp[index1] = ThreadArray[index2];
			index1++;
		}
	}

	if (ThreadArray != NULL)
	{
		delete[] ThreadArray;
	}

	ThreadArray = new Thread[threadNumber];
	for (uint8_t index = 0; index < threadNumber; index++)
	{
		ThreadArray[index] = threadTemp[index];
	}
}

bool TaskSchedulerClass::IsFunctionExit(void(*func)())
{
	for ( uint8_t index = 0; index < threadNumber; index++ )
	{
		if (ThreadArray[index].Func == func)
		{
			return true;
		}
	}
	return false;
}

ISR(TIMER1_OVF_vect)
{
	TCNT1 = 65286;	// Interrupt function was called every 0.001 s
	TaskScheduler.Execute();
}

TaskSchedulerClass TaskScheduler;

