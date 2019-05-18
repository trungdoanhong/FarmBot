#include "SerialCommand.h"
#include <ArduinoJson.h>

SerialCommand::SerialCommand()
{
	_Serial = &Serial;
	_Serial->begin(9600);
	//inputString.reserve(100);

	boolean stringComplete = false;
	String inputString = "";

	cmdCounter = 0;
	//cmdContainer = new Command[10];
	cmdContainer = NULL;
}

SerialCommand::SerialCommand(HardwareSerial* serial, uint16_t baudrate)
{
	_Serial = serial;
	_Serial->begin(baudrate);
	//inputString.reserve(100);

	boolean stringComplete = false;
	String inputString = "";

	cmdCounter = 0;
	//cmdContainer = new Command[cmdCounter];
	cmdContainer = NULL;
}

SerialCommand::~SerialCommand()
{
  //free(cmdContainer);
  delete[] cmdContainer;
}

void SerialCommand::ForwardData(HardwareSerial* forwardSerial, uint16_t baudrate)
{
	ForwardSerial = forwardSerial;
	ForwardSerial->begin(baudrate);
}

void SerialCommand::AddCommand(String message, void(*function)())
{
  cmdCounter++;
  //cmdContainer = (Command *) realloc(cmdContainer, cmdCounter * sizeof(Command));

  
   Command* newContainer = new Command[cmdCounter];
   for( uint8_t i = 0; i < cmdCounter - 1; i++ )
   {
     newContainer[i] = cmdContainer[i];
   } 
   if( cmdContainer != NULL ) 
   {
     delete[] cmdContainer;
   }   
   cmdContainer = newContainer;
   
  
  cmdContainer[cmdCounter - 1].message = message;
  cmdContainer[cmdCounter - 1].function = function;
  cmdContainer[cmdCounter - 1].value = NULL;
  cmdContainer[cmdCounter - 1].contain = NULL;
}

void SerialCommand::AddCommand(String message, float* value)
{  
  cmdCounter++;
  //cmdContainer = (Command *) realloc(cmdContainer, cmdCounter * sizeof(Command));

   Command* newContainer = new Command[cmdCounter];
   for( uint8_t i = 0; i < cmdCounter - 1; i++ )
   {
     newContainer[i] = cmdContainer[i];
   } 
   if( cmdContainer != NULL )
   {
     delete[] cmdContainer;
   }   
   cmdContainer = newContainer;
  
  cmdContainer[cmdCounter - 1].message = message;
  cmdContainer[cmdCounter - 1].value = value;
  cmdContainer[cmdCounter - 1].function = NULL;
  cmdContainer[cmdCounter - 1].contain = NULL;
}

void SerialCommand::AddCommand(String message, String* contain)
{
	cmdCounter++;
	//cmdContainer = (Command *) realloc(cmdContainer, cmdCounter * sizeof(Command));

	Command* newContainer = new Command[cmdCounter];
	for (uint8_t i = 0; i < cmdCounter - 1; i++)
	{
		newContainer[i] = cmdContainer[i];
	}
	if (cmdContainer != NULL)
	{
		delete[] cmdContainer;
	}
	cmdContainer = newContainer;

	cmdContainer[cmdCounter - 1].message = message;
	cmdContainer[cmdCounter - 1].value = NULL;
	cmdContainer[cmdCounter - 1].function = NULL;
	cmdContainer[cmdCounter - 1].contain = contain;
}


void SerialCommand::Execute()
{
  // receive every character
  while (_Serial->available()) 
  {
    char inChar = (char)_Serial->read();
	if (ForwardSerial != NULL)
	{
		ForwardSerial->print(inChar);
	}
    
	if (inChar == '\n' || inChar == '\r')
    {
      stringComplete = true;
      break;
    }

    inputString += inChar;
  }
  
  if (!stringComplete)
    return;

  //Serial.println(inputString);
   
  // when complete receiving
  for( uint8_t index = 0; index < cmdCounter; index++ )
  {
	if (cmdContainer[index].message == inputString.substring(0, cmdContainer[index].message.length()))
    { 
      if( cmdContainer[index].value != NULL )
      {
        *cmdContainer[index].value = inputString.substring(cmdContainer[index].message.length() + 1).toFloat();        
      }
	  else if (cmdContainer[index].contain != NULL)
	  {
		  //*cmdContainer[index].contain = inputString.substring(cmdContainer[index].message.length() + 1);

		  *cmdContainer[index].contain = "";

		  for (uint16_t i = cmdContainer[index].message.length() + 1; i < inputString.length(); i++)
		  {
			  *cmdContainer[index].contain += inputString[i];
		  }

		  /*uint16_t num = inputString.length() - cmdContainer[index].message.length();
		  
		  inputString.toCharArray(cmdContainer[index].contain, num + 1, 5);*/
		  Serial.println(*cmdContainer[index].contain);
		  Serial.println("Done");
	  }
      else
      {
		  if (cmdContainer[index].function != NULL)
			cmdContainer[index].function();
      }
    }
  }

  inputString = "";
  stringComplete = false;
}
