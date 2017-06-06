#ifndef _SerialCommand_
#define _SerialCommand_

#include <string.h>
#include <Arduino.h>

struct Command
{
  String message = "";
  void(*function)() = NULL;
  float* value = NULL;
  char* contain;
};

class SerialCommand
{
public:
  HardwareSerial* _Serial;
  HardwareSerial* ForwardSerial = NULL;
  Command* cmdContainer;
  uint8_t cmdCounter = 0;
  
  SerialCommand();
  SerialCommand(HardwareSerial*, uint16_t);
  ~SerialCommand();
  
  void AddCommand(String message, void(*function)());
  void AddCommand(String message, float* value);
  void AddCommand(String message, char* contain);
  void Execute();
  void ForwardData(HardwareSerial*, uint16_t);
  
private:
  boolean stringComplete;
  String inputString;
};

#endif
