#include <Wire.h> 
#include "LiquidCrystal_I2C.h"
#include "LCDMenu.h"
#include "StableButton.h"
#include "Time.h"
#include "DS1307RTC.h"
#include "TaskScheduler.h"

#define RETURN  7
#define LEFT    9
#define RIGHT   11
#define DOWN    10
#define UP      12
#define ENTER   8 

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

SubMenu* smWaterTime1;
Label* lbMaxTemp1;
Label* lbMaxHumi1;
VariableText* vtMaxTempValue1;
VariableText* vtMaxHumiValue1;

SubMenu* smWaterTime2;
Label* lbMaxTemp2;
Label* lbMaxHumi2;
VariableText* vtMaxTempValue2;
VariableText* vtMaxHumiValue2;

SubMenu* smWaterTime3;
Label* lbMaxTemp3;
Label* lbMaxHumi3;
VariableText* vtMaxTempValue3;
VariableText* vtMaxHumiValue3;

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
		{
			smWaterTime1 = new SubMenu(smTree1->Container, "Time for water", 3, 0);
			lbMaxTemp1 = new Label(smTree1->Container, "Max temp", 0, 1);
			vtMaxTempValue1 = new VariableText(smTree1->Container, 33, 10, 1); 
			lbMaxHumi1 = new Label(smTree1->Container, "Max humi" ,0 , 2);
			vtMaxHumiValue1 = new VariableText(smTree1->Container, 60, 10, 2); 
		}
		smTree2 = new SubMenu(SecondMenu, "Tree 2", 7, 2);
		{
			smWaterTime2 = new SubMenu(smTree2->Container, "Time for water", 3, 0);
			lbMaxTemp2 = new Label(smTree2->Container, "Max temp", 0, 1);
			vtMaxTempValue2 = new VariableText(smTree2->Container, 33, 10, 1);
			lbMaxHumi2 = new Label(smTree2->Container, "Max humi", 0, 2);
			vtMaxHumiValue2 = new VariableText(smTree2->Container, 60, 10, 2);
		}
		smTree3 = new SubMenu(SecondMenu, "Tree 3", 14, 2);
		{
			smWaterTime3 = new SubMenu(smTree3->Container, "Time for water", 3, 0);
			lbMaxTemp3 = new Label(smTree3->Container, "Max temp", 0, 1);
			vtMaxTempValue3 = new VariableText(smTree3->Container, 33, 10, 1);
			lbMaxHumi3 = new Label(smTree3->Container, "Max humi", 0, 2);
			vtMaxHumiValue3 = new VariableText(smTree3->Container, 60, 10, 2);
		}
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
