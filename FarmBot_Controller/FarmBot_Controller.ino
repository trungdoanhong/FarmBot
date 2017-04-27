#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include "LCDMenu.h"
#include "StableButton.h"
#include "Time.h"
#include "DS1307RTC.h"
#include "TaskScheduler.h"

#define RETURN 7
#define LEFT 9
#define RIGHT 11
#define DOWN 10
#define UP 12
#define ENTER 8 

uint8_t ButtonArray[] = { RETURN, LEFT, RIGHT, UP, DOWN, ENTER };

LiquidCrystal_I2C lcd(0x27, 16, 4);

tmElements_t TodayTime;

OriginMenu* FirstMenu;
Label* lbToday;
Label* lbDateValue;
Label* lbTimeValue;

OriginMenu* SecondMenu;
Label* lbSeasonName;
SubMenu* smTree1;
SubMenu* smTree2;
SubMenu* 

void setup()
{
	FirstMenu = new OriginMenu();
	{
		lbToday = new Label(FirstMenu, "Today: ", 0, 0);
		lbDateValue = new Label(FirstMenu, "27/4/2017", 8, 0);
		lbTimeValue = new Label(FirstMenu, "20:33:23", 8, 1);
	}

	SecondMenu = new OriginMenu();
	{

	}

	Serial.begin(9600);
	
	LCDMenu.Init(&lcd, "FarmBot Controller");
	LCDMenu.AddMenu(FirstMenu);
	LCDMenu.SetCurrentMenu(FirstMenu);
	LCDMenu.UpdateScreen();

	StableButton.Init(ButtonArray, 6);

	TaskScheduler.Init();
	TaskScheduler.Add(UpdateTimeInDay, 1000);
	TaskScheduler.Add(UpdateDateInMonth, 1000);

	TaskScheduler.Run();

}

void loop()
{
	ReadTime();
	ExecuteMenuButton();
	LCDMenu.ExecuteEffect();	
	LCDMenu.UpdateScreen();
}

void ReadTime()
{
	RTC.read(TodayTime);
}

void UpdateTimeInDay()
{
	lbTimeValue->SetText(String(TodayTime.Hour) + ":" + String(TodayTime.Minute) + ":" + String(TodayTime.Second));
	
}

void UpdateDateInMonth()
{
	lbDateValue->SetText(String(TodayTime.Day) + "/" + String(TodayTime.Month) + "/20" + String(TodayTime.Year-30));
}

void ExecuteMenuButton()
{
	if (StableButton.IsPressed(LEFT))
	{
		LCDMenu.MoveCursorLeft();
	}

	if (StableButton.IsPressed(RIGHT))
	{
		LCDMenu.MoveCursorRight();
	}

	if (StableButton.IsPressed(UP))
	{
		LCDMenu.MoveCursorUp();
	}

	if (StableButton.IsPressed(DOWN))
	{
		LCDMenu.MoveCursorDown();
	}

	if (StableButton.IsPressed(RETURN))
	{
		LCDMenu.Return();
	}

	if (StableButton.IsPressed(ENTER))
	{
		LCDMenu.Enter();
	}
}
