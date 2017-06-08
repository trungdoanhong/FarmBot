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
#include <ArduinoJson.h>
#include "Season.h"
#include <EEPROM.h>
#include <string.h>

#define SEASON_ADDRESS 0

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
Label* lbVaccumValue;
FunctionText* ftLamp;
Label* lbLampValue;
FunctionText* ftFan;
Label* lbFanValue;
FunctionText* ftServo;
Label* lbServoValue;

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

OriginMenu* FourthMenu;
Label* lbCells;
Label* lbCellX;
Label* lbCellY;
VariableText* vtCellX;
VariableText* vtCellY;
FunctionText* ftMoveToCell;
FunctionText* ftMoveToBowl[3];
FunctionText* ftSowSeeds;

void(*AddTimes[3])();
void(*DeleteTimes[3])();
vector<TimeControl> TimeControls[3];

String JsonContainer;
char JsonStringPtr[550];
Season ProcessingSeason;

void(*MoveToBowls[3])();

// Take care of plants
bool IsTimeToWater[3] = { false, false, false };
bool IsWatering = false;
uint8_t cellOrder = 0;
uint8_t WaterManipulationOrder = 0;
uint8_t wateringTree = 0;

void setup()
{
	AddTimes[0] = AddTime1;
	AddTimes[1] = AddTime2;
	AddTimes[2] = AddTime3;
	
	DeleteTimes[0] = DeleteTime1;
	DeleteTimes[1] = DeleteTime2;
	DeleteTimes[2] = DeleteTime3;

	MoveToBowls[0] = MoveToBowl1;
	MoveToBowls[1] = MoveToBowl2;
	MoveToBowls[2] = MoveToBowl3;

	Serial.begin(9600);
	Serial1.begin(9600);

	SerialCMD = SerialCommand(&Serial, 9600);
	SerialCMD1 = SerialCommand(&Serial1, 9600);

	SerialCMD.ForwardData(&Serial1, 9600);
	SerialCMD1.ForwardData(&Serial, 9600);

	GetDataFromEeprom();

	SerialCMD.AddCommand("Json", JsonStringPtr);
	SerialCMD.AddCommand("Load", SendDataToSoftware);
	SerialCMD.AddCommand("UploadDone", ConvertJsonStringToDataStruct);
	SerialCMD.AddCommand("PrintEeprom", PrintDataStructFromEeprom);
	SerialCMD.AddCommand("PrintSeason", PrintProcessingSeason);
	SerialCMD.AddCommand("PrintJson", PrintJson);
	SerialCMD.AddCommand("IsFarmBot", Confirm);

	SerialCMD1.AddCommand("GcodeDone", WhenGcodeDone);

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

				vtMaxTempValue[i] = new VariableText(smTree[i]->Container, ProcessingSeason.Trees[i].MaxTemperature, 10, 1);

				lbMaxHumi[i] = new Label(smTree[i]->Container, "Max humi", 0, 2);

				vtMaxHumiValue[i] = new VariableText(smTree[i]->Container, ProcessingSeason.Trees[i].MaxHumidity, 10, 2);

				lbMinHumi[i] = new Label(smTree[i]->Container, "Min humi", 0, 3);

				vtMinHumiValue[i] = new VariableText(smTree[i]->Container, ProcessingSeason.Trees[i].MinHumidity, 10, 3);

				vtMaxTempValue[i]->SetExternalValue((uint16_t*)&ProcessingSeason.Trees[i].MaxTemperature);
				vtMaxHumiValue[i]->SetExternalValue((uint16_t*)&ProcessingSeason.Trees[i].MaxHumidity);
				vtMinHumiValue[i]->SetExternalValue((uint16_t*)&ProcessingSeason.Trees[i].MinHumidity);

				vtMaxHumiValue[i]->HandleWhenValueChange = SaveDataStructToEeprom;
				vtMaxHumiValue[i]->HandleWhenValueChange = SaveDataStructToEeprom;
				vtMinHumiValue[i]->HandleWhenValueChange = SaveDataStructToEeprom;
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
		lbUnit = new Label(ThirdMenu, "mm", 12, 1);

		lbX = new Label(ThirdMenu, "X", 0, 2);
		vtX = new VariableText(ThirdMenu, 0, 1, 2);
		lbY = new Label(ThirdMenu, "Y", 7, 2);
		vtY = new VariableText(ThirdMenu, 0, 8, 2);
		lbZ = new Label(ThirdMenu, "Z", 14, 2);
		vtZ = new VariableText(ThirdMenu, 0, 15, 2);

		ftPump = new FunctionText(ThirdMenu, "P", 0, 3);
		vtPumpValue = new VariableText(ThirdMenu, 1, 1, 3);
		ftVaccum = new FunctionText(ThirdMenu, "V", 4, 3);
		lbVaccumValue = new Label(ThirdMenu, "0", 5, 3);
		ftFan = new FunctionText(ThirdMenu, "F", 8, 3);
		lbFanValue = new Label(ThirdMenu, "0", 9, 3);
		ftLamp = new FunctionText(ThirdMenu, "L", 12, 3);
		lbLampValue = new Label(ThirdMenu, "0", 13, 3);
		ftServo = new FunctionText(ThirdMenu, "S", 16, 3);
		lbServoValue = new Label(ThirdMenu, "0", 17, 3);

		ftHome->Function = SendHomeGCode;
		ftX->Function = SendXHomeGCode;
		ftY->Function = SendYHomeGCode;
		ftZ->Function = SendZHomeGCode;
		vtMoveValue->Max = 100;
		vtMoveValue->Min = 1;
		vtMoveValue->HandleWhenValueChange = ChangeMovingWidth;
		vtX->HandleWhenValueChange = SendMoveXGCode;
		vtY->HandleWhenValueChange = SendMoveYGCode;
		vtZ->HandleWhenValueChange = SendMoveZGCode;
		ftPump->Function = SendPumpGcode;
		ftVaccum->Function = SendVaccumGcode;
		ftFan->Function = SendFanGcode;
		ftLamp->Function = SendLampGcode;
		ftServo->Function = SendServoGcode;
		vtPumpValue->Max = 0;
	}

	FourthMenu = new OriginMenu();
	{
		lbCells = new Label(FourthMenu, "Cells:", 0, 0);
		lbCellX = new Label(FourthMenu, "X", 8, 0);
		lbCellY = new Label(FourthMenu, "Y", 12, 0);
		vtCellX = new VariableText(FourthMenu, 1, 9, 0);
		vtCellY = new VariableText(FourthMenu, 1, 13, 0);

		ftMoveToCell = new FunctionText(FourthMenu, "Move", 16, 0);
		for (uint8_t i = 0; i < 3; i++)
		{
			ftMoveToBowl[i] = new FunctionText(FourthMenu, String("Bowl") + String(i + 1), i * 7, 1);
			ftMoveToBowl[i]->Function = MoveToBowls[i];
		}		

		ftSowSeeds = new FunctionText(FourthMenu, "Sow Seeds", 0, 2);

		ftSowSeeds->Function = SowSeeds;
		ftMoveToCell->Function = MoveToCell;

		vtCellX->Max = 3;
		vtCellX->Min = 1;

		vtCellY->Max = 8;
		vtCellY->Min = 1;
	}
	
	LCDMenu.Init(&lcd, "FarmBot Controller");
	LCDMenu.AddMenu(FirstMenu);
	LCDMenu.AddMenu(SecondMenu);
	LCDMenu.AddMenu(ThirdMenu);
	LCDMenu.AddMenu(FourthMenu);
	LCDMenu.SetCurrentMenu(FirstMenu);
	LCDMenu.UpdateScreen();

	UpdateDisplayParameter();

	StableButton.Init(ButtonArray, 6);

	TaskScheduler.Init();
	TaskScheduler.Add(UpdateTimeInDay, 1000);
	TaskScheduler.Add(UpdateDateInMonth, 1000);
	TaskScheduler.Add(CheckTimeToWater, 10000);
	TaskScheduler.Add(WaterWhenItsTime, 10000);

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
	GetGcodeState();
	
}

uint32_t lastTime = 0;

void GetGcodeState()
{
	if (millis() - lastTime < 1000)
		return;

	lastTime = millis();
	Serial1.print("State\n");
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

	ProcessingSeason.Trees[treeOrder].TimesForWater[TimeControls[treeOrder].size() - 1].Hour = (uint8_t)vtAddHour[treeOrder]->GetValue();
	ProcessingSeason.Trees[treeOrder].TimesForWater[TimeControls[treeOrder].size() - 1].Minute = (uint8_t)vtAddMinute[treeOrder]->GetValue();

	SaveDataStructToEeprom();
}

void DeleteTime(uint8_t treeOrder)
{
	uint8_t selectedTimeOrder = (LCDMenu.CurrentCursor.Y - 1) * 2 + (LCDMenu.CurrentCursor.X - 6) / 10;

	smWaterTime[treeOrder]->Container->DeleteElement(TimeControls[treeOrder][selectedTimeOrder].lbTime);
	smWaterTime[treeOrder]->Container->DeleteElement(TimeControls[treeOrder][selectedTimeOrder].ftDelete);

	TimeControls[treeOrder].erase(TimeControls[treeOrder].begin() + selectedTimeOrder);
	UpdatePositionTimeControl(treeOrder);
	DeleteTimeAndUpdateOrderTimeStruct(treeOrder, selectedTimeOrder);
	SaveDataStructToEeprom();

	LCDMenu.ReLoadMenu();
}

void ClearTimeControls()
{
	for (uint8_t treeOrder = 0; treeOrder < 3; treeOrder++)
	{
		for (uint8_t timeOrder = 0; timeOrder < TimeControls[treeOrder].size(); timeOrder++)
		{
			smWaterTime[treeOrder]->Container->DeleteElement(TimeControls[treeOrder][timeOrder].lbTime);
			smWaterTime[treeOrder]->Container->DeleteElement(TimeControls[treeOrder][timeOrder].ftDelete);
		}
		TimeControls[treeOrder].clear();
	}
	
}

void DeleteTimeAndUpdateOrderTimeStruct(uint8_t treeOrder, uint8_t timeOrder)
{
	for (uint8_t i = timeOrder; i < 5; i++)
	{
		ProcessingSeason.Trees[treeOrder].TimesForWater[i].Hour = ProcessingSeason.Trees[treeOrder].TimesForWater[i + 1].Hour;
		ProcessingSeason.Trees[treeOrder].TimesForWater[i].Minute = ProcessingSeason.Trees[treeOrder].TimesForWater[i + 1].Minute;
	}

	ProcessingSeason.Trees[treeOrder].TimesForWater[6].Hour = NULL_TIME;
	ProcessingSeason.Trees[treeOrder].TimesForWater[6].Minute = 0;
}

void UpdatePositionTimeControl(uint8_t treeOrder)
{
	for (uint8_t i = 0; i < TimeControls[treeOrder].size(); i++)
	{
		uint8_t x = (i % 2) * 10;
		uint8_t y = i / 2 + 1;

		TimeControls[treeOrder][i].lbTime->SetPosition(x, y);
		TimeControls[treeOrder][i].ftDelete->SetPosition(x + 6, y);
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
	vtX->SetValue(0);
	vtY->SetValue(0);
	vtZ->SetValue(0);
}

void SendXHomeGCode()
{
	for (uint8_t i = 0; i < 5; i++)
	{
		Serial1.println("G28 X");
	}
	vtX->SetValue(0);
}

void SendYHomeGCode()
{
	Serial1.println("G28 Y");
	vtY->SetValue(0);
}

void SendZHomeGCode()
{
	for (uint8_t i = 0; i < 5; i++)
	{
		Serial1.println("G28 Z");
	}
	vtZ->SetValue(0);
}

void SendMoveXGCode()
{
	String gcode = String("G00 X") + String((int)vtX->GetValue());
	Serial1.println(gcode);
}

void SendMoveYGCode()
{
	String gcode = String("G00 Y") + String((int)vtY->GetValue());
	Serial1.println(gcode);
}

void SendMoveZGCode()
{
	String gcode = String("G00 Z") + String((int)vtZ->GetValue());
	Serial1.println(gcode);
}

void SendPauseGCode(uint16_t sec, uint16_t milisec = 0)
{
	String gcode = String("G04 P") + String(milisec) + " S" + String(sec);
	Serial1.println(gcode);
}

void SendPumpGcode(uint8_t value)
{
	String gcode = String("G41 P") + String(value * 1000);
	Serial1.println(gcode);
}

void SendPumpGcode()
{
	SendPumpGcode((int)vtPumpValue->GetValue());
}

void SendVaccumGcode(uint8_t value)
{
	String gcode = String("") + "G42 V" + String(value);
	Serial1.println(gcode);
}

void SendVaccumGcode()
{
	if (lbVaccumValue->Text == "0")
	{
		lbVaccumValue->SetText("1");
	}
	else
	{
		lbVaccumValue->SetText("0");
	}

	SendVaccumGcode(lbVaccumValue->Text.toInt());
}

void SendFanGcode()
{
	if (lbFanValue->Text == "0")
	{
		lbFanValue->SetText("1");
	}
	else
	{
		lbFanValue->SetText("0");
	}

	String gcode = String("") + "G43 F" + lbFanValue->Text;
	Serial1.println(gcode);
}

void SendLampGcode()
{
	if (lbLampValue->Text == "0")
	{
		lbLampValue->SetText("1");
	}
	else
	{
		lbLampValue->SetText("0");
	}

	String gcode = String("") + "G44 L" + lbLampValue->Text;
	Serial1.println(gcode);
}

void SendServoGcode(uint8_t value)
{
	String gcode = String("") + "G40 S" + String(value);
	Serial1.println(gcode);
}

void SendServoGcode()
{
	if (lbServoValue->Text == "0")
	{
		lbServoValue->SetText("90");
	}
	else
	{
		lbServoValue->SetText("0");
	}

	SendServoGcode(lbServoValue->Text.toInt());
}

void ChangeMovingWidth()
{
	vtX->Resolution = vtMoveValue->GetValue();
	vtY->Resolution = vtMoveValue->GetValue();
	vtZ->Resolution = vtMoveValue->GetValue();
}

void ConvertJsonStringToDataStruct()
{
	//DynamicJsonBuffer jsonBuffer;
	StaticJsonBuffer<1400> jsonBuffer;

	JsonObject& root = jsonBuffer.parseObject(JsonStringPtr);

	if (!root.success()) 
	{
		Serial.println("parseObject() failed");
		return;
	}
	else
	{
		Serial.println("parseObject() success");
	}

	ProcessingSeason.Id = root["I"];
	strcpy(ProcessingSeason.Name, root["N"]);

	for (uint8_t i = 0; i < 24; i++)
	{
		ProcessingSeason.Garden[i] = root["G"][i];
	}


	for (uint8_t i = 0; i < 3; i++)
	{
		strcpy(ProcessingSeason.Trees[i].Name, root["Tree"][i]["N"]);
		ProcessingSeason.Trees[i].MaxTemperature = root["T"][i]["MaxT"];
		ProcessingSeason.Trees[i].MaxHumidity = root["T"][i]["MaxH"];
		ProcessingSeason.Trees[i].MinHumidity = root["T"][i]["MinH"];

		for (uint8_t j = 0; j < 6; j++)
		{
			if (j < root["Tree"][i]["TimeForWaterList"].size())
			{
				ProcessingSeason.Trees[i].TimesForWater[j].Hour = root["T"][i]["Times"][j]["H"];
				ProcessingSeason.Trees[i].TimesForWater[j].Minute = root["T"][i]["Times"][j]["M"];
			}
			else
			{
				ProcessingSeason.Trees[i].TimesForWater[j].Hour = NULL_TIME;
				ProcessingSeason.Trees[i].TimesForWater[j].Minute = 0;
			}
		}
	
	}

	SaveDataStructToEeprom();
	UpdateDisplayParameter();
}

void PrintSeason(Season season)
{
	Serial.print("Id : ");
	Serial.println(season.Id);
	Serial.print("Name : ");
	Serial.println(season.Name);
	Serial.print("Garden : ");
	for (uint8_t i = 0; i < 24; i++)
	{
		Serial.print(season.Garden[i]);
		if (i == 23)
		{
			Serial.println();
			break;
		}
		Serial.print(",");
	}

	for (uint8_t i = 0; i < 3; i++)
	{
		Serial.print("Tree Name : ");
		Serial.println(season.Trees[i].Name);
		Serial.print("MaxTemperature : ");
		Serial.println(season.Trees[i].MaxTemperature);
		Serial.print("MaxHumidity : ");
		Serial.println(season.Trees[i].MaxHumidity);
		Serial.print("MinHumidity : ");
		Serial.println(season.Trees[i].MinHumidity);

		for (uint8_t j = 0; j < 6; j++)
		{
			if (season.Trees[i].TimesForWater[j].Hour == NULL_TIME)
				break;
			Serial.print(season.Trees[i].TimesForWater[j].Hour);
			Serial.print(":");
			Serial.println(season.Trees[i].TimesForWater[j].Minute);
		}
	}
}

void SendDataToSoftware()
{
	// Send sequence

	Serial.print("Json-{\"T\":[");
	for (uint8_t i = 0; i < 3; i++)
	{
		Serial.print("{");
		Serial.print("\"Times\":[");
		for (uint8_t j = 0; j < 6; j++)
		{
			if (ProcessingSeason.Trees[i].TimesForWater[j].Hour == NULL_TIME)
				break;
			if (j != 0)
				Serial.print(",");
			Serial.print("{");
			Serial.print("\"H\":");
			Serial.print(ProcessingSeason.Trees[i].TimesForWater[j].Hour);
			Serial.print(",\"M\":");
			Serial.print(ProcessingSeason.Trees[i].TimesForWater[j].Minute);
			Serial.print("}");
			
		}
		Serial.print("], \"N\":");
		Serial.print(String("\"") + ProcessingSeason.Trees[i].Name + String("\""));
		Serial.print(", \"MaxT\":");
		Serial.print(String("\"") + ProcessingSeason.Trees[i].MaxTemperature + String("\""));
		Serial.print(", \"MaxH\":");
		Serial.print(String("\"") + ProcessingSeason.Trees[i].MaxHumidity + String("\""));
		Serial.print(", \"MinH\":");
		Serial.print(String("\"") + ProcessingSeason.Trees[i].MinHumidity + String("\""));
		Serial.print("}");
		if (i != 2)
			Serial.print(",");
	}
	Serial.print("],\"G\":[");
	for (uint8_t i = 0; i < 24; i++)
	{
		Serial.print(ProcessingSeason.Garden[i]);
		if (i != 23)
			Serial.print(",");
	}
	Serial.print("]");
	Serial.print(", \"N\":"); 
	Serial.print(String("\"") + ProcessingSeason.Name + String("\""));
	Serial.print(", \"I\":");
	Serial.print(String("\"") + ProcessingSeason.Id + String("\""));
	Serial.println("}");

}

void GetDataFromEeprom()
{
	EEPROM.get(SEASON_ADDRESS, ProcessingSeason);
}

void SaveDataStructToEeprom()
{
	EEPROM.put(SEASON_ADDRESS, ProcessingSeason);
}

void PrintDataStructFromEeprom()
{
	Season eepromSeason;
	EEPROM.get(SEASON_ADDRESS, eepromSeason);
	PrintSeason(eepromSeason);
}

void Confirm()
{
	Serial.println("YesFarmBot");
}

void PrintJson()
{
	Serial.println(JsonStringPtr);
}

void UpdateDisplayParameter()
{
	ClearTimeControls();

	for (uint8_t treeOrder = 0; treeOrder < 3; treeOrder++)
	{
		float maxTemp = ProcessingSeason.Trees[treeOrder].MaxTemperature;
		float maxHumi = ProcessingSeason.Trees[treeOrder].MaxHumidity;
		float minHumi = ProcessingSeason.Trees[treeOrder].MinHumidity;

		vtMaxTempValue[treeOrder]->SetValue(maxTemp);
		vtMaxHumiValue[treeOrder]->SetValue(maxHumi);
		vtMinHumiValue[treeOrder]->SetValue(minHumi);

		for (uint8_t timeOrder = 0; timeOrder < 6; timeOrder++)
		{
			if (ProcessingSeason.Trees[treeOrder].TimesForWater[timeOrder].Hour == NULL_TIME)
				break;

			uint8_t x = (TimeControls[treeOrder].size() % 2) * 10;
			uint8_t y = TimeControls[treeOrder].size() / 2 + 1;

			TimeControl addingTimeControl;

			String hour(ProcessingSeason.Trees[treeOrder].TimesForWater[timeOrder].Hour);
			String minute(ProcessingSeason.Trees[treeOrder].TimesForWater[timeOrder].Minute);

			if (hour.length() == 1)
				hour = String("0") + hour;
			if (minute.length() == 1)
				minute = String("0") + minute;

			addingTimeControl.lbTime = new Label(smWaterTime[treeOrder]->Container, hour + ":" + minute, x, y);
			addingTimeControl.ftDelete = new FunctionText(smWaterTime[treeOrder]->Container, "x", x + 6, y);
			addingTimeControl.ftDelete->Function = DeleteTimes[treeOrder];

			TimeControls[treeOrder].push_back(addingTimeControl);
		}
	}

	LCDMenu.ReLoadMenu();
}

void PrintProcessingSeason()
{
	PrintSeason(ProcessingSeason);
}

// Garden Moving

#define BOWL_NUMBER 3
#define AXIS_NUMBER 3
#define CELL_EDGE_LENGTH 100
#define SHORT_EDGE_CELL_NUMBER 3
#define LONG_EDGE_CELL_NUMBER 8
#define X_AXIS 0
#define Y_AXIS 1
#define Z_AXIS 2

#define HEIGHT_WHEN_MOVE 100
#define HEIGHT_WHEN_MEASURE 200

enum END_ACTUATOR
{
	VACCUM = 0,
	PUMP,
	SENSOR
};

int16_t VaccumOffset[2] = { 0, 0 };
int16_t PumpOffset[2] = { -30, 30};
int16_t SensorOffset[2] = { 10, 50 };
int16_t GeneralOffset[2] = { -5, 5 };

uint16_t SeedBowlPosition[BOWL_NUMBER][AXIS_NUMBER] = { { 100, 0, 150 }, { 150, 0, 150 }, { 200, 0, 150 } };

void MoveToCell(uint8_t cellX, uint8_t cellY, END_ACTUATOR endActuator = VACCUM)
{
	uint16_t xPos = 0;
	uint16_t yPos = 0;
	uint16_t zPos = 0;

	int16_t offset[2] = { 0, 0 };

	switch (endActuator)
	{
	case VACCUM:
		offset[X_AXIS] += VaccumOffset[X_AXIS];
		offset[Y_AXIS] += VaccumOffset[Y_AXIS];
		break;
	case PUMP:
		offset[X_AXIS] += PumpOffset[X_AXIS];
		offset[Y_AXIS] += PumpOffset[Y_AXIS];
		break;
	case SENSOR:
		offset[X_AXIS] += SensorOffset[X_AXIS];
		offset[Y_AXIS] += SensorOffset[Y_AXIS];
		break;
	default:
		break;
	}

	offset[X_AXIS] += GeneralOffset[X_AXIS];
	offset[Y_AXIS] += GeneralOffset[Y_AXIS];

	xPos = (cellX * CELL_EDGE_LENGTH) + (CELL_EDGE_LENGTH / 2) + offset[X_AXIS];
	yPos = (cellY * CELL_EDGE_LENGTH) + (CELL_EDGE_LENGTH / 2) + offset[Y_AXIS];
	zPos = HEIGHT_WHEN_MOVE;

	Serial1.println(String("G00 Z") + String(zPos));

	Serial1.println(String("G00 X") + String(xPos) + " Y" + String(yPos));

	vtX->SetValue(xPos);
	vtY->SetValue(yPos);
	vtZ->SetValue(zPos);

}

void MoveToCell()
{
	MoveToCell(vtCellX->GetValue() - 1, vtCellY->GetValue() - 1);
}

void MoveToBowl(uint8_t cupOrder)
{
	uint16_t xPos = SeedBowlPosition[cupOrder][X_AXIS] + GeneralOffset[X_AXIS] + VaccumOffset[X_AXIS];
	uint16_t yPos = SeedBowlPosition[cupOrder][Y_AXIS] + GeneralOffset[Y_AXIS] + VaccumOffset[Y_AXIS];

	Serial1.println(String("G00 Z") + String(HEIGHT_WHEN_MOVE));

	Serial1.println(String("G00 X") + String(xPos) + " Y" + String(yPos));

	Serial1.println(String("G00 Z") + String(SeedBowlPosition[cupOrder][Z_AXIS]));

	vtX->SetValue(xPos);
	vtY->SetValue(yPos);
	vtZ->SetValue(SeedBowlPosition[cupOrder][Z_AXIS]);
}

void MoveToBowl1()
{
	MoveToBowl(0);
}

void MoveToBowl2()
{
	MoveToBowl(1);
}

void MoveToBowl3()
{
	MoveToBowl(2);
}

uint8_t SowingCellOrder = 0;
bool IsSowingSeeds = false;
uint8_t SowSeedManipulationOrder = 0;

void WhenGcodeDone()
{
	//Serial.println("WhenGcodeDone");
	if (IsSowingSeeds == true)
	{
		SowSeed();
	}

	if (IsWatering == true)
	{
		ImplementWatering(wateringTree);
	}
}

void SowSeeds()
{
	IsSowingSeeds = true;
	SowingCellOrder = 0;
	SowSeedManipulationOrder = 0;
	//SendHomeGCode();
	SowSeed();
}

void SowSeed()
{
	while (ProcessingSeason.Garden[SowingCellOrder] == 0)
	{
		SowingCellOrder++;
	}

	switch (SowSeedManipulationOrder)
	{
	case 0:
		MoveToBowl(ProcessingSeason.Garden[SowingCellOrder] - 1);		
		SowSeedManipulationOrder++;
		break;
	case 1:
		SendVaccumGcode(1);
		SendPauseGCode(1000);
		SowSeedManipulationOrder++;
		break;
	case 2:
		MoveToCell(SowingCellOrder % 3, SowingCellOrder / 3);
		SowSeedManipulationOrder++;
		break;
	case 3:
		SendVaccumGcode(0);
		SendPauseGCode(500);
		SowSeedManipulationOrder++;
		break;
	case 4:
		MoveToCell(SowingCellOrder % 3, SowingCellOrder / 3, PUMP);
		SowSeedManipulationOrder++;
	case 5:
		SendPumpGcode(3);
		SendPauseGCode(5000);
		//SendHomeGCode();

		SowSeedManipulationOrder = 0;
		SowingCellOrder++;
		if (SowingCellOrder == 24)
		{
			IsSowingSeeds = false;
		}
		break;
	default:
		break;
	}	
}

// Take care of plane

void CheckTimeToWater()
{
	for (uint8_t i = 0; i < 3; i++)
	{
		for (uint8_t j = 0; j < 6; j++)
		{
			if (ProcessingSeason.Trees[i].TimesForWater[j].Hour == NULL_TIME)
				break;
			if (TodayTime.Hour == ProcessingSeason.Trees[i].TimesForWater[j].Hour && TodayTime.Minute == ProcessingSeason.Trees[i].TimesForWater[j].Minute)
			{
				IsTimeToWater[i] = true;
			}
		}
	}
}

void WaterWhenItsTime()
{
	if (IsWatering == true)
	{
		return;
	}

	for (uint8_t i = 0; i < 3; i++)
	{
		if (IsTimeToWater[i] == true)
		{
			IsWatering == true;
			cellOrder = 0;
			WaterManipulationOrder = 0;
			wateringTree = i;
			ImplementWatering(wateringTree);
			return;
		}
	}

	
}

void ImplementWatering(uint8_t treeOrder)
{
	while (ProcessingSeason.Garden[cellOrder] != (treeOrder + 1))
	{
		cellOrder++;
	}

	switch (WaterManipulationOrder)
	{
	case 0:
		MoveToCell(cellOrder % 3, cellOrder / 3, PUMP);
		WaterManipulationOrder++;
		break;
	case 1:
		SendPumpGcode(3);
		SendPauseGCode(5000);

		WaterManipulationOrder = 0;
		cellOrder++;
		if (cellOrder == 24)
		{
			cellOrder = 0;
			IsWatering = false;
			IsTimeToWater[wateringTree] = false;
		}
		break;
	default:
		break;
	}	
}
