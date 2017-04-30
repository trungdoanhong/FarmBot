// LCDMenu.h

#ifndef _LCDMENU_h
#define _LCDMENU_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "LiquidCrystal_I2C.h"
#include <string.h>
#include "StableButton.h"

enum DisplayElementType
{
	SUBMENU = 0, 
	LABEL = 1,
	FUNCTIONTEXT = 2,
	VARIABLETEXT = 3
};

class DisplayElement;

struct Point
{
	int8_t X;
	int8_t Y;
};

class AbstractMenu
{
public:
	AbstractMenu();
	virtual ~AbstractMenu();

	void AddElement(DisplayElement* element);
	void DeleteElement(DisplayElement* element);

	DisplayElement** DisEleArray;
	uint8_t DisEleNumber = 0;

	bool CursorEnable = false;

};

class OriginMenu : public AbstractMenu
{
public:
};

class DisplayElement
{
public:
	DisplayElement(AbstractMenu* parent, String text, uint8_t col, uint8_t row);
	virtual ~DisplayElement();
	virtual DisplayElementType GetElementType();
	void SetText(String text);
	void SetPosition(uint8_t col, uint8_t row);

	bool IsDisplay = true;
	bool IsTextChanged = false;
	uint8_t Column;
	uint8_t Row;
	String Text;
	String oldText;

};

class SubMenu : public DisplayElement
{
public:
	SubMenu(AbstractMenu* parent, String text, uint8_t col, uint8_t row);
	~SubMenu();
	DisplayElementType GetElementType();

	AbstractMenu* Container;

};

class Label : public DisplayElement
{
public:
	Label(AbstractMenu* parent, String text, uint8_t col, uint8_t row);
	DisplayElementType GetElementType();
};

class VariableText : public DisplayElement
{
public:
	VariableText(AbstractMenu* parent, float, uint8_t col, uint8_t row);
	void Decrease();
	void Increase();
	DisplayElementType GetElementType();
	void SetText(String text);

	float Resolution;
	float Value;
	bool IsSelected;
	float Max;
	float Min;
};

class FunctionText : public DisplayElement
{
public:
	FunctionText(AbstractMenu* parent, String text, uint8_t col, uint8_t row);
	DisplayElementType GetElementType();

	void (*Function)(void);
};

class LCDMenuClass
{
 protected:


 public:
	 void Init(LiquidCrystal_I2C* lcd, String intro);	// give a pointer of lcd using module I2C and intro text
	 void AddMenu(OriginMenu* menu);
	 void MoveCursorUp();
	 void MoveCursorDown();
	 void MoveCursorLeft();
	 void MoveCursorRight();
	 void Return();						// Return parent menu if screen is submenu, and change origin menu if screen is an origin menu
	 void Enter();
	 void UpdateScreen();				// Update changed content on LCD
	 void SetCurrentMenu(AbstractMenu* menu);	// Set menu need to display
	 void TurnCursor(bool state);
	 void ExecuteEffect();	
	 void ReLoadMenu();
	 
	 LiquidCrystal_I2C* LCD;
	 Point CurrentCursor;
	 bool IsCursorOn;

	 OriginMenu** OriginMenuArray;
	 uint8_t OriginMenuNumber = 0;

	 AbstractMenu* AccessingTree[10];
	 int8_t BrandOrder = -1;
	 int8_t Index = -1;
 private:
	 void eraseText(DisplayElement* procEle);
	 AbstractMenu* currentMenu;
	 VariableText* blinkVariableText;

	 
};

extern LCDMenuClass LCDMenu;

#endif

