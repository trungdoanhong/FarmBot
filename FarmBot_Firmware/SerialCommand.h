#ifndef _SerialCommand_
#define _SerialCommand_

#include <string.h>
#include <Arduino.h>

struct Command
{
  String message;
  void(*function)() = NULL;
  float* value = NULL;
};

class SerialCommand
{
public:
  Command* cmdContainer;
  uint8_t cmdCounter = 0;
  
  SerialCommand();
  SerialCommand(uint16_t);
  ~SerialCommand();
  
  void AddCommand(String message, void(*function)());
  void AddCommand(String message, float* value);
  void Execute();
  
private:
  boolean stringComplete;
  String inputString;
};

#endif
