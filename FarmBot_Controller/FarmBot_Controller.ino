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
SubMenu* smTree3;

void setup()
{
	Serial.begin(9600);

	FirstMenu = new OriginMenu();
	{
		lbToday = new Label(FirstMenu, "Today: ", 0, 0);
		lbDateValue = new Label(FirstMenu, "", 8, 0);
		lbTimeValue = new Label(FirstMenu, "07:33:10", 8, 1);
	}

	SecondMenu = new OriginMenu();
	{
		lbSeasonName = new Label(SecondMenu, "Season 1", 7, 0);
		smTree1 = new SubMenu(SecondMenu, "Tree 1", 0, 2);
		smTree2 = new SubMenu(SecondMenu, "Tree 2", 7, 2);
		smTree3 = new SubMenu(SecondMenu, "Tree 3", 14, 2);
	}
	
	LCDMenu.Init(&lcd, "FarmBot Controller");
	LCDMenu.AddMenu(FirstMenu);
	LCDMenu.AddMenu(SecondMenu);
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
	String hour = String(TodayTime.Hour);
	String minute = String(TodayTime.Minute);
	String second = String(TodayTime.Second);

	if (hour.length() == 1)
	{
		hour = String("0") + hour;
	}
	if (minute.length() == 1)
	{
		minute = String("0") + minute;
	}
	if (second.length() == 1)
	{
		second = String("0") + second;
	}
	lbTimeValue->SetText(hour + ":" + minute + ":" + second);
	
}

void UpdateDateInMonth()
{
	String day = String(TodayTime.Day);
	String month = String(TodayTime.Month);
	String year = String("20") + String(abs(TodayTime.Year - 30));

	if (day.length() == 1)
	{
		day = String("0") + day;
	}
	if (month.length() == 1)
	{
		month = String("0") + month;
	}

	lbDateValue->SetText(day + "/" + month + "/" + year);
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
