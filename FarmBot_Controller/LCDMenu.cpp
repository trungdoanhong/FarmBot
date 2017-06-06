// 
// 
// 

#include "LCDMenu.h"

#pragma region LCDMenuClass

void LCDMenuClass::Init(LiquidCrystal_I2C* lcd, String intro = "LCD Menu")
{
	LCD = lcd;
	IsCursorOn = true;
	CurrentCursor.X = -1;
	CurrentCursor.Y = -1;

	LCD->init();
	LCD->backlight();
	LCD->cursor_on();
	LCD->setCursor(0, 0);
	LCD->print(intro);
	delay(1000);
	LCD->clear();

	Index = -1 ;
}

void LCDMenuClass::AddMenu(OriginMenu* menu)
{
	OriginMenuNumber++;
	OriginMenu** newOriginMenu = new OriginMenu*[OriginMenuNumber];
	
	for (uint8_t i = 0; i < OriginMenuNumber - 1; i++)
	{
		newOriginMenu[i] = OriginMenuArray[i];
	}
	
	if (OriginMenuArray != NULL)
	{
		delete[] OriginMenuArray;
	}

	OriginMenuArray = newOriginMenu;

	OriginMenuArray[OriginMenuNumber - 1] = menu;
}

void LCDMenuClass::eraseText(DisplayElement* procEle)
{
	String spaces = "";
	uint8_t numOfSpace = 0;
	if (procEle->oldText.length() == 0)
	{
		numOfSpace = procEle->Text.length();
	}
	else
	{
		numOfSpace = procEle->oldText.length();
	}
	for (uint8_t i = 0; i < numOfSpace; i++)
	{
		spaces = spaces + " ";
	}
	LCD->setCursor(procEle->Column, procEle->Row);
	LCD->print(spaces);
}

void LCDMenuClass::UpdateScreen()
{
	// If have no menu is added, display "No menu" on LCD
	if(Index == -1)
	{
		LCD->print("No menu");
	}

	DisplayElement* procEle;	// Processing Element
	for (uint8_t i = 0; i < currentMenu->DisEleNumber; i++)
	{
		procEle = currentMenu->DisEleArray[i];
		
		if (procEle->IsTextChanged == false)
			continue;			
		
		if (procEle->IsDisplay == false)
		{
			eraseText(procEle);
		}
		else
		{
			if (procEle->oldText.length() > procEle->Text.length())
			{
				eraseText(procEle);
			}
			LCD->setCursor(procEle->Column, procEle->Row);
			LCD->print(procEle->Text);
		}
		procEle->IsTextChanged = false;
	}

	LCD->setCursor(CurrentCursor.X, CurrentCursor.Y);
}

void LCDMenuClass::TurnCursor(bool state)
{
	IsCursorOn = state;
	if (IsCursorOn == true)
		LCD->cursor_on();
	else
		LCD->cursor_off();
}

void LCDMenuClass::SetCurrentMenu(AbstractMenu* menu)
{
	currentMenu = menu;

	for (uint8_t i = 0; i < currentMenu->DisEleNumber; i++)
	{
		if (currentMenu->DisEleArray[i]->GetElementType() != LABEL)
		{
			currentMenu->CursorEnable = true;
		}
	}
	
	// If menu is origin menu type, change index
	if (BrandOrder == -1)
	{
		bool isMenuExits = false;
		for (uint8_t i = 0; i < OriginMenuNumber; i++)
		{
			if (OriginMenuArray[i] == currentMenu)
			{
				isMenuExits = true;
				Index = i;
			}
		}

		if (isMenuExits == false)
			return;
	}

	// if menu is not have any display element, turn off cursor
	if (currentMenu->DisEleNumber == 0 || currentMenu->CursorEnable == false)
	{
		TurnCursor(false);
	}
	else
	{
		TurnCursor(true);

		DisplayElement* procEle;
		Point smallestCursor;
		smallestCursor.X = 100;
		smallestCursor.Y = 100;
		for (uint8_t i = 0; i < currentMenu->DisEleNumber; i++)
		{
			procEle = currentMenu->DisEleArray[i];
			if (procEle->GetElementType() == LABEL)
				continue;
			if ((procEle->Row == smallestCursor.Y && procEle->Column < smallestCursor.X) || (procEle->Row < smallestCursor.Y))
			{
				smallestCursor.X = procEle->Column;
				smallestCursor.Y = procEle->Row;
			}
		}
		CurrentCursor = smallestCursor;
	}

	// Change state display element in menu
	for (uint8_t i = 0; i < currentMenu->DisEleNumber; i++)
	{
		currentMenu->DisEleArray[i]->IsTextChanged = true;
	}

}

void LCDMenuClass::ReLoadMenu()
{
	LCD->clear();
	SetCurrentMenu(currentMenu);
}

void LCDMenuClass::MoveCursorLeft()
{
	if (blinkVariableText != NULL)
		return;

	Point nearestEle;
	nearestEle.X = -1;
	nearestEle.Y = -1;
	DisplayElement* procEle;

	for (uint8_t i = 0; i < currentMenu->DisEleNumber; i++)
	{
		procEle = currentMenu->DisEleArray[i];

		if (procEle->GetElementType() == LABEL)
			continue;
		if (procEle->Row < CurrentCursor.Y || (procEle->Row == CurrentCursor.Y && procEle->Column < CurrentCursor.X))
		{
			if (procEle->Row > nearestEle.Y || (procEle->Row == nearestEle.Y && procEle->Column > nearestEle.X))
			{
				nearestEle.X = procEle->Column;
				nearestEle.Y = procEle->Row;
			}
		}
	}

	if (nearestEle.X == -1)
		return;

	CurrentCursor = nearestEle;
	LCD->setCursor(CurrentCursor.X, CurrentCursor.Y);
}

void LCDMenuClass::MoveCursorRight()
{
	if (blinkVariableText != NULL)
		return;

	Point nearestEle;
	nearestEle.X = 125;
	nearestEle.Y = 125;
	DisplayElement* procEle;

	for (uint8_t i = 0; i < currentMenu->DisEleNumber; i++)
	{
		procEle = currentMenu->DisEleArray[i];
		if (procEle->GetElementType() == LABEL)
			continue;
		if (procEle->Row > CurrentCursor.Y || ( procEle->Row == CurrentCursor.Y && procEle->Column > CurrentCursor.X))
		{
			if (procEle->Row < nearestEle.Y || (procEle->Row == nearestEle.Y && procEle->Column < nearestEle.X))
			{
				nearestEle.X = procEle->Column;
				nearestEle.Y = procEle->Row;
			}
		}
	}

	if (nearestEle.X == 125)
		return;

	CurrentCursor = nearestEle;
	LCD->setCursor(CurrentCursor.X, CurrentCursor.Y);
}

void LCDMenuClass::ExecuteEffect()
{
	
	if (currentMenu->DisEleNumber != 0 && currentMenu->CursorEnable == true)
	{
		static unsigned long lasttime = millis();
		if (millis() - lasttime > 500)
		{
			lasttime = millis();
			if (IsCursorOn == false)
			{
				TurnCursor(true);
			}
			else
			{
				TurnCursor(false);
			}
		}
	}

	if (blinkVariableText == NULL)
		return;
	static unsigned long lasttime2 = millis();
	if (millis() - lasttime2 > 200)
	{
		lasttime2 = millis();
		blinkVariableText->IsTextChanged = true;
		if (blinkVariableText->IsDisplay == false)
		{
			blinkVariableText->IsDisplay = true;			
		}			
		else
		{
			blinkVariableText->IsDisplay = false;
		}
			
		UpdateScreen();
	}
	
}

void LCDMenuClass::MoveCursorUp()
{
	if (blinkVariableText == NULL)
		return;

	blinkVariableText->Increase();
	UpdateScreen();
}

void LCDMenuClass::MoveCursorDown()
{
	if (blinkVariableText == NULL)
		return;

	blinkVariableText->Decrease();
	UpdateScreen();
}

void LCDMenuClass::Enter()
{
	DisplayElement* procEle;

	for (uint8_t i = 0; i < currentMenu->DisEleNumber; i++)
	{
		procEle = currentMenu->DisEleArray[i];
		if (CurrentCursor.X == procEle->Column && CurrentCursor.Y == procEle->Row)
		{
			DisplayElementType eleType;
			eleType = procEle->GetElementType();

			switch (eleType)
			{
			case SUBMENU:			
				LCD->clear();
				BrandOrder++;
				AccessingTree[BrandOrder] = currentMenu;
				SetCurrentMenu(((SubMenu*)procEle)->Container);
				UpdateScreen();
				return;							
				break;
			case FUNCTIONTEXT:
				if (((FunctionText*)procEle)->Function == NULL)
					break;
				((FunctionText*)procEle)->Function();
				break;
			case VARIABLETEXT:
				blinkVariableText = (VariableText*)procEle;
				if (blinkVariableText->IsSelected == false)
				{
					blinkVariableText->IsSelected = true;
				}					
				else
				{
					blinkVariableText->IsSelected = false;
					blinkVariableText->IsDisplay = true;
					blinkVariableText->IsTextChanged = true;
					UpdateScreen();
					blinkVariableText = NULL;
				}
				break;
			default:
				break;
			}

		}
	}
}

void LCDMenuClass::Return()
{	
	if (blinkVariableText != NULL)
		return;

	LCD->clear();

	// If screen is origin menu, change other origin menu
	if (BrandOrder == -1)
	{
		Index++;
		if (OriginMenuNumber == Index)
		{
			Index = 0;
		}
		SetCurrentMenu(OriginMenuArray[Index]);
		UpdateScreen();
		return;
	}

	//SetCurrentMenu(currentMenu->Parent);
	SetCurrentMenu(AccessingTree[BrandOrder]);
	BrandOrder--;
	UpdateScreen();
}

LCDMenuClass LCDMenu;

#pragma endregion LCDMenuClass

#pragma region DisplayElement

DisplayElement::DisplayElement(AbstractMenu* parent, String text, uint8_t col, uint8_t row)
{
	parent->AddElement(this);
	SetText(text);
	Column = col;
	Row = row;
}

DisplayElement::~DisplayElement()
{
}

DisplayElementType DisplayElement::GetElementType()
{

}

void DisplayElement::SetText(String text)
{
	oldText = Text;
	Text = text;
	IsTextChanged = true;
}

void DisplayElement::SetPosition(uint8_t col, uint8_t row)
{
	Column = col;
	Row = row;
}

#pragma endregion DisplayElement

#pragma region AbstractMenu

AbstractMenu::AbstractMenu()
{
	DisEleNumber = 0;
	CursorEnable = false;
}

AbstractMenu::~AbstractMenu()
{
	for (uint8_t i = 0; i < DisEleNumber; i++)
	{
		delete DisEleArray[i];
	}
	delete[] DisEleArray;
}

void AbstractMenu::AddElement(DisplayElement* element)
{
	DisEleNumber++;
	DisplayElement** newDisEleArray = new DisplayElement*[DisEleNumber];

	for (uint8_t i = 0; i < DisEleNumber - 1; i++)
	{
		newDisEleArray[i] = DisEleArray[i];
	}

	if (DisEleArray != NULL)
	{
		delete[] DisEleArray;
	}

	DisEleArray = newDisEleArray;

	DisEleArray[DisEleNumber - 1] = element;
	
}

void AbstractMenu::DeleteElement(DisplayElement* element)
{
	int eleOrder = -1;
	for (uint8_t i = 0; i < DisEleNumber; i++)
	{
		if (DisEleArray[i] == element)
		{
			eleOrder = i;
		}
	}

	// If have no element need delete in array, exit function

	if (eleOrder == -1)
		return;

	// Decrease display element number
	if (DisEleNumber > 0)
	{
		DisEleNumber--;
	}

	DisplayElement** newDisEleArray = new DisplayElement*[DisEleNumber];
	uint8_t newDisEleOrder = 0;

	// copy old elements into temporary unless element need to delete
	for (uint8_t i = 0; i < DisEleNumber + 1; i++)
	{
		if (i == eleOrder)
		{
			continue;
		}
		newDisEleArray[newDisEleOrder] = DisEleArray[i];
		newDisEleOrder++;
	}

	// delete Display Element Array
	if (DisEleArray != NULL)
	{
		delete[] DisEleArray;
	}

	DisEleArray = newDisEleArray;

	delete element;
}

#pragma endregion AbstractMenu

SubMenu::SubMenu(AbstractMenu* parent, String text, uint8_t col, uint8_t row) : DisplayElement(parent, text, col, row)
{
	Container = new OriginMenu();
}

SubMenu::~SubMenu()
{
	delete Container;
}

DisplayElementType SubMenu::GetElementType()
{
	return SUBMENU;
}

Label::Label(AbstractMenu* parent, String text, uint8_t col, uint8_t row) : DisplayElement(parent, text, col, row)
{

}

DisplayElementType Label::GetElementType()
{
	return LABEL;
}

VariableText::VariableText(AbstractMenu* parent, float value, uint8_t col, uint8_t row) : DisplayElement(parent, "", col, row)
{
	Max = 0;
	Min = 0;
	if (value - (int)value == 0)
	{
		Resolution = 1;
	}		
	else
	{
		uint8_t numForCheck = (int)(value / 0.01) % 10;
		if (numForCheck == 0)
		{
			Resolution = 0.1;
		}
		else
		{
			Resolution = 0.01;
		}
	}

	mValue = value;
	if ((Resolution - (int)Resolution) == 0)
	{
		SetText(String((int)mValue));
	}
	else
	{
		SetText(String(mValue));
	}
	IsSelected = false;

	HandleWhenValueChange = NULL;

	pExternalValue_float = NULL;
	pExternalValue_int = NULL;
}

DisplayElementType VariableText::GetElementType()
{
	return VARIABLETEXT;
}

void VariableText::SetExternalValue(float* pExVal)
{
	this->pExternalValue_float = pExVal;
}

void VariableText::SetExternalValue(uint16_t* pExVal)
{
	this->pExternalValue_int = pExVal;
}

void VariableText::SetValue(float value)
{ 
	mValue = value;

	if (pExternalValue_float != NULL)
	{
		*pExternalValue_float = mValue;
	}
	if (pExternalValue_int != NULL)
	{
		*pExternalValue_int = mValue;
	}

	if (HandleWhenValueChange != NULL)
	{
		HandleWhenValueChange();
	}
	
	if ((Resolution - (int)Resolution) == 0)
	{
		SetText(String((int)mValue));
	}
	else
	{
		SetText(String(mValue));
	}
}

float VariableText::GetValue()
{
	return mValue;
}

void VariableText::Decrease()
{
	mValue = mValue - Resolution;

	if (mValue < Min && Min < Max)
	{
		mValue = Max;
	}

	if (pExternalValue_float != NULL)
	{
		*pExternalValue_float = mValue;
	}

	if (pExternalValue_int != NULL)
	{
		*pExternalValue_int = mValue;
	}

	if (HandleWhenValueChange != NULL)
	{
		HandleWhenValueChange();
	}

	if ((Resolution - (int)Resolution) == 0)
	{
		SetText(String((int)mValue));
	}
	else
	{
		SetText(String(mValue));
	}

	
}

void VariableText::Increase()
{
	mValue = mValue + Resolution;

	if (mValue > Max && Min < Max)
	{
		mValue = Min;
	}

	if (pExternalValue_float != NULL)
	{
		*pExternalValue_float = mValue;
	}

	if (pExternalValue_int != NULL)
	{
		*pExternalValue_int = mValue;
	}

	if (HandleWhenValueChange != NULL)
	{
		HandleWhenValueChange();
	}

	if ((Resolution - (int)Resolution) == 0)
	{
		SetText(String((int)mValue));
	}
	else
	{
		SetText(String(mValue));
	}
}

void VariableText::SetText(String text)
{
	String space = "";
	if (Max > Min)
	{
		for (uint8_t i = 0; i < String((int)Max).length() - text.length(); i++)
		{
			space = space + "0";
		}
	}
	oldText = Text;
	Text = space + text;
	IsTextChanged = true;
}

FunctionText::FunctionText(AbstractMenu* parent, String text, uint8_t col, uint8_t row) : DisplayElement(parent, text, col, row)
{
	Function = NULL;
}

DisplayElementType FunctionText::GetElementType()
{
	return FUNCTIONTEXT;
}


