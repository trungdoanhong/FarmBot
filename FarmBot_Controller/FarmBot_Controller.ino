#include <Wire.h> 
#include "LiquidCrystal_I2C.h"
#include "LCDMenu.h"
#include "StableButton.h"
#include "Time.h"
#include "DS1307RTC.h"
#include "TaskScheduler.h"
#include "SerialCommand.h"
#include <StandardCplusplus.h> // Copy StandardCplusplus folder to Mydocument\Arduino\libraries to use below libraries
#include <vector>

#define RETURN  7
#define LEFT    9
#define RIGHT   11
#define DOWN    10
#define UP      12
#define ENTER   8 

using namespace std;

SerialCommand SerialCMD;
SerialCommand SerialCMD1;

uint8_t ButtonArray[] = { RETURN, LEFT, RIGHT, UP, DOWN, ENTER };

LiquidCrystal_I2C lcd(0x27, 20, 4);

tmElements_t TodayTime;

typedef struct
{
	Label* lbTime;
	FunctionText* ftDelete;
} TimeControl;

OriginMenu* FirstMenu;
Label* lbToday;
Label* lbDateValue;
Label* lbTimeValue;

OriginMenu* SecondMenu;
Label* lbSeasonName;
SubMenu* smTree[3];

OriginMenu* ThirdMenu;
FunctionText* ftHome;
FunctionText* ftX;
FunctionText* ftY;
FunctionText* ftZ;
Label* lbMove;
VariableText* vtMoveValue;
Label* lbUnit;
Label* lbX;
Label* lbY;
Label* lbZ;
VariableText* vtX;
VariableText* vtY;
VariableText* vtZ;
FunctionText* ftPump;
VariableText* vtPumpValue;
FunctionText* ftVaccum;
FunctionText* ftLamp;
FunctionText* ftFan;
FunctionText* ftServo;


SubMenu* smWaterTime[3];
Label* lbMaxTemp[3];
Label* lbMaxHumi[3];
Label* lbMinHumi[3];
VariableText* vtMaxTempValue[3];
VariableText* vtMaxHumiValue[3];
VariableText* vtMinHumiValue[3];

FunctionText* ftAddTime[3];
VariableText* vtAddHour[3];
Label* lbAddColon[3];
VariableText* vtAddMinute[3];

void(*AddTimes[3])();
void(*DeleteTimes[3])();
vector<TimeControl> TimeControls[3];

void setup()
{
	AddTimes[0] = AddTime1;
	AddTimes[1] = AddTime2;
	AddTimes[2] = AddTime3;
	
	DeleteTimes[0] = DeleteTime1;
	DeleteTimes[1] = DeleteTime2;
	DeleteTimes[2] = DeleteTime3;

	Serial.begin(9600);
	Serial1.begin(9600);

	SerialCMD = SerialCommand(&Serial, 9600);
	SerialCMD1 = SerialCommand(&Serial1, 9600);

	SerialCMD.ForwardData(&Serial1, 9600);
	SerialCMD1.ForwardData(&Serial, 9600);

	

	FirstMenu = new OriginMenu();
	{
		lbToday = new Label(FirstMenu, "Today: ", 0, 0);
		lbDateValue = new Label(FirstMenu, "", 8, 0);
		lbTimeValue = new Label(FirstMenu, "07:33:10", 8, 1);
	}

	SecondMenu = new OriginMenu();
	{
		lbSeasonName = new Label(SecondMenu, "Season 1", 7, 0);

		for (uint8_t i = 0; i < 3; i++)
		{
			smTree[i] = new SubMenu(SecondMenu, "Tree" + String(i + 1), 7 * i, 2);
			{
				smWaterTime[i] = new SubMenu(smTree[i]->Container, "Time for water", 3, 0);
				{
					ftAddTime[i] = new FunctionText(smWaterTime[i]->Container, "Add", 0, 0);
					ftAddTime[i]->Function = AddTimes[i];

					vtAddHour[i] = new VariableText(smWaterTime[i]->Container, 12, 10, 0);
					lbAddColon[i] = new Label(smWaterTime[i]->Container, ":", 12, 0);
					vtAddMinute[i] = new VariableText(smWaterTime[i]->Container, 15, 13, 0);

					vtAddHour[i]->Max = 23;
					vtAddHour[i]->Min = 0;

					vtAddMinute[i]->Max = 59;
					vtAddMinute[i]->Min = 0;
				}

				lbMaxTemp[i] = new Label(smTree[i]->Container, "Max temp", 0, 1);

				vtMaxTempValue[i] = new VariableText(smTree[i]->Container, 40, 10, 1);

				lbMaxHumi[i] = new Label(smTree[i]->Container, "Max humi", 0, 2);

				vtMaxHumiValue[i] = new VariableText(smTree[i]->Container, 60, 10, 2);

				lbMinHumi[i] = new Label(smTree[i]->Container, "Min humi", 0, 3);

				vtMinHumiValue[i] = new VariableText(smTree[i]->Container, 40, 10, 3);
			}
		}
	}

	ThirdMenu = new OriginMenu();
	{
		ftHome = new FunctionText(ThirdMenu, "Home", 1, 0);
		ftX = new FunctionText(ThirdMenu, "X", 8, 0);
		ftY = new FunctionText(ThirdMenu, "Y", 12, 0);
		ftZ = new FunctionText(ThirdMenu, "Z", 16, 0);

		lbMove = new Label(ThirdMenu, "Move:", 1, 1);
		vtMoveValue = new VariableText(ThirdMenu, 1, 8, 1);
		lbUnit = new Label(ThirdMenu, "mm", 11, 1);

		lbX = new Label(ThirdMenu, "X", 0, 2);
		vtX = new VariableText(ThirdMenu, 0, 1, 2);
		lbY = new Label(ThirdMenu, "Y", 7, 2);
		vtY = new VariableText(ThirdMenu, 0, 8, 2);
		lbZ = new Label(ThirdMenu, "Z", 14, 2);
		vtZ = new VariableText(ThirdMenu, 0, 15, 2);

		ftPump = new FunctionText(ThirdMenu, "P", 0, 3);
		vtPumpValue = new VariableText(ThirdMenu, 1, 1, 3);
		ftVaccum = new FunctionText(ThirdMenu, "V", 6, 3);
		ftFan = new FunctionText(ThirdMenu, "F", 10, 3);
		ftLamp = new FunctionText(ThirdMenu, "L", 14, 3);
		ftServo = new FunctionText(ThirdMenu, "S", 18, 3);

		ftHome->Function = SendHomeGCode;
		vtX->HandleWhenValueChange = SendMoveXGCode;
		

	}
	
	LCDMenu.Init(&lcd, "FarmBot Controller");
	LCDMenu.AddMenu(FirstMenu);
	LCDMenu.AddMenu(SecondMenu);
	LCDMenu.AddMenu(ThirdMenu);
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
	SerialCMD.Execute();
	SerialCMD1.Execute();
}

void AddTime(uint8_t treeOrder)
{
	if (TimeControls[treeOrder].size() == 6)
				return;

	uint8_t x = (TimeControls[treeOrder].size() % 2) * 10;
	uint8_t y = TimeControls[treeOrder].size() / 2 + 1;

	TimeControl addingTimeControl;
	addingTimeControl.lbTime = new Label(smWaterTime[treeOrder]->Container, vtAddHour[treeOrder]->Text + ":" + vtAddMinute[treeOrder]->Text, x, y);
	addingTimeControl.ftDelete = new FunctionText(smWaterTime[treeOrder]->Container, "x", x + 6, y);
	addingTimeControl.ftDelete->Function = DeleteTimes[treeOrder];

	TimeControls[treeOrder].push_back(addingTimeControl);

}

void DeleteTime(uint8_t treeOder)
{
	uint8_t selectedTimeOrder = (LCDMenu.CurrentCursor.Y - 1) * 2 + (LCDMenu.CurrentCursor.X - 6) / 10;

	smWaterTime[treeOder]->Container->DeleteElement(TimeControls[treeOder][selectedTimeOrder].lbTime);
	smWaterTime[treeOder]->Container->DeleteElement(TimeControls[treeOder][selectedTimeOrder].ftDelete);

	TimeControls[treeOder].erase(TimeControls[treeOder].begin() + selectedTimeOrder);
	UpdatePositionTimeControl(treeOder);
	LCDMenu.ReLoadMenu();
}

void UpdatePositionTimeControl(uint8_t treeOder)
{
	for (uint8_t i = 0; i < TimeControls[treeOder].size(); i++)
	{
		uint8_t x = (i % 2) * 10;
		uint8_t y = i / 2 + 1;

		TimeControls[treeOder][i].lbTime->SetPosition(x, y);
		TimeControls[treeOder][i].ftDelete->SetPosition(x + 6, y);
	}
}

void DeleteTime1()
{
	DeleteTime(0);
}

void DeleteTime2()
{
	DeleteTime(1);
}

void DeleteTime3()
{
	DeleteTime(2);
}

void AddTime1()
{
	AddTime(0);
}

void AddTime2()
{
	AddTime(1);
}

void AddTime3()
{
	AddTime(2);
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

void SendHomeGCode()
{
	Serial1.println("G28 Z");
	Serial1.println("G28 X Y");
}

void SendXHomeGCode()
{
	Serial1.println("G28 X");
}

void SendYHomeGCode()
{
	Serial1.println("G28 Y");
}

void SendZHomeGCode()
{
	Serial1.println("G28 Z");
}

void SendMoveXGCode()
{
	String gcode = String("") + "G00 X" + String((int)vtX->GetValue());
	Serial1.println(gcode);
}

void SendMoveYGCode()
{

}

void SendMoveZGCode()
{

}

void SendPumpGcode()
{

}

void SendVaccumGcode()
{

}

void SendFanGcode()
{

}

void SendLampGcode()
{

}

void SendServoGcode()
{

}