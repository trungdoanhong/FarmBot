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

void(*AddTimes[3])();
void(*DeleteTimes[3])();
vector<TimeControl> TimeControls[3];

String JsonContainer;
char JsonStringPtr[800];
Season ProcessingSeason;

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
	//SerialCMD1.ForwardData(&Serial, 9600);

	GetDataFromEeprom();

	SerialCMD.AddCommand("Json", JsonStringPtr);
	SerialCMD.AddCommand("Load", SendDataToSoftware);
	SerialCMD.AddCommand("UploadDone", ConvertJsonStringToDataStruct);
	SerialCMD.AddCommand("PrintEeprom", PrintDataStructFromEeprom);
	SerialCMD.AddCommand("PrintSeason", PrintProcessingSeason);
	SerialCMD.AddCommand("PrintJson", PrintJson);
	SerialCMD.AddCommand("IsFarmBot", Confirm);

	

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

					for (uint8_t timeOrder = 0; timeOrder < 6; timeOrder++)
					{
						if (ProcessingSeason.Trees[i].TimesForWater[timeOrder].Hour == NULL_TIME)
							break;

						uint8_t x = (TimeControls[i].size() % 2) * 10;
						uint8_t y = TimeControls[i].size() / 2 + 1;

						TimeControl addingTimeControl;

						String hour(ProcessingSeason.Trees[i].TimesForWater[timeOrder].Hour);
						String minute(ProcessingSeason.Trees[i].TimesForWater[timeOrder].Minute);

						if (hour.length() == 1)
							hour = String("0") + hour;
						if (minute.length() == 1)
							minute = String("0") + minute;

						addingTimeControl.lbTime = new Label(smWaterTime[i]->Container, hour + ":" + minute, x, y);
						addingTimeControl.ftDelete = new FunctionText(smWaterTime[i]->Container, "x", x + 6, y);
						addingTimeControl.ftDelete->Function = DeleteTimes[i];

						TimeControls[i].push_back(addingTimeControl);
					}
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

void GetDataFromEeprom()
{
	EEPROM.get(SEASON_ADDRESS, ProcessingSeason);
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

	ProcessingSeason.Trees[treeOrder].TimesForWater[TimeControls[treeOrder].size() - 1].Hour = vtAddHour[treeOrder]->GetValue();
	ProcessingSeason.Trees[treeOrder].TimesForWater[TimeControls[treeOrder].size() - 1].Minute = vtAddMinute[treeOrder]->GetValue();

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
	Serial1.println("G28 X");
	vtX->SetValue(0);
}

void SendYHomeGCode()
{
	Serial1.println("G28 Y");
	vtY->SetValue(0);
}

void SendZHomeGCode()
{
	Serial1.println("G28 Z");
	vtZ->SetValue(0);
}

void SendMoveXGCode()
{
	String gcode = String("") + "G00 X" + String((int)vtX->GetValue());
	Serial1.println(gcode);
}

void SendMoveYGCode()
{
	String gcode = String("") + "G00 Y" + String((int)vtY->GetValue());
	Serial1.println(gcode);
}

void SendMoveZGCode()
{
	String gcode = String("") + "G00 Z" + String((int)vtZ->GetValue());
	Serial1.println(gcode);
}

void ChangeMovingWidth()
{
	vtX->Resolution = vtMoveValue->GetValue();
	vtY->Resolution = vtMoveValue->GetValue();
	vtZ->Resolution = vtMoveValue->GetValue();
}

void SendPumpGcode()
{
	String gcode = String("") + "G41 P" + String((int)vtPumpValue->GetValue()*1000);
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

	String gcode = String("") + "G42 V" + lbVaccumValue->Text;
	Serial1.println(gcode);
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

	String gcode = String("") + "G40 S" + lbServoValue->Text;
	Serial1.println(gcode);
}

void ConvertJsonStringToDataStruct()
{
	//DynamicJsonBuffer jsonBuffer;
	StaticJsonBuffer<1800> jsonBuffer;

	JsonObject& root = jsonBuffer.parseObject(JsonStringPtr);

	if (!root.success()) {
		Serial.println("parseObject() failed");
		return;
	}
	else
	{
		Serial.println("parseObject() success");
	}

	ProcessingSeason.Id = root["Id"];
	strcpy(ProcessingSeason.Name, root["Name"]);

	for (uint8_t i = 0; i < 24; i++)
	{
		ProcessingSeason.Garden[i] = root["Garden"][i];
	}


	for (uint8_t i = 0; i < 3; i++)
	{
		strcpy(ProcessingSeason.Trees[i].Name, root["Tree"][i]["Name"]);
		ProcessingSeason.Trees[i].MaxTemperature = root["Tree"][i]["MaxTemperature"];
		ProcessingSeason.Trees[i].MaxHumidity = root["Tree"][i]["MaxHumidity"];
		ProcessingSeason.Trees[i].MinHumidity = root["Tree"][i]["MinHumidity"];

		for (uint8_t j = 0; j < root["Tree"][i]["TimeForWaterList"].size(); j++)
		{
			ProcessingSeason.Trees[i].TimesForWater[j].Hour = root["Tree"][i]["TimeForWaterList"][j]["Hour"];
			ProcessingSeason.Trees[i].TimesForWater[j].Minute = root["Tree"][i]["TimeForWaterList"][j]["Minute"];
		}
		for (uint8_t j = root["Tree"][i]["TimeForWaterList"].size(); j < 6; j++)
		{
			ProcessingSeason.Trees[i].TimesForWater[j].Hour = NULL_TIME;
			ProcessingSeason.Trees[i].TimesForWater[j].Minute = NULL_TIME;
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

	Serial.print("Json-{\"Tree\":[");
	for (uint8_t i = 0; i < 3; i++)
	{
		Serial.print("{");
		Serial.print("\"TimeForWaterList\":[");
		for (uint8_t j = 0; j < 6; j++)
		{
			if (ProcessingSeason.Trees[i].TimesForWater[j].Hour == NULL_TIME)
				break;
			if (j != 0)
				Serial.print(",");
			Serial.print("{");
			Serial.print("\"Hour\":");
			Serial.print(ProcessingSeason.Trees[i].TimesForWater[j].Hour);
			Serial.print(",\"Minute\":");
			Serial.print(ProcessingSeason.Trees[i].TimesForWater[j].Minute);
			Serial.print("}");
			
		}
		Serial.print("], \"Name\":");
		Serial.print(String("\"") + ProcessingSeason.Trees[i].Name + String("\""));
		Serial.print(", \"MaxTemperature\":");
		Serial.print(String("\"") + ProcessingSeason.Trees[i].MaxTemperature + String("\""));
		Serial.print(", \"MaxHumidity\":");
		Serial.print(String("\"") + ProcessingSeason.Trees[i].MaxHumidity + String("\""));
		Serial.print(", \"MinHumidity\":");
		Serial.print(String("\"") + ProcessingSeason.Trees[i].MinHumidity + String("\""));
		Serial.print("}");
		if (i != 2)
			Serial.print(",");
	}
	Serial.print("],\"Garden\":[");
	for (uint8_t i = 0; i < 24; i++)
	{
		Serial.print(ProcessingSeason.Garden[i]);
		if (i != 23)
			Serial.print(",");
	}
	Serial.print("]");
	Serial.print(", \"Name\":"); 
	Serial.print(String("\"") + ProcessingSeason.Name + String("\""));
	Serial.print(", \"Id\":");
	Serial.print(String("\"") + ProcessingSeason.Id + String("\""));
	Serial.println("}");

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
	for (uint8_t i = 0; i < 3; i++)
	{
		vtMaxTempValue[i]->SetValue(ProcessingSeason.Trees[i].MaxTemperature);
		vtMaxHumiValue[i]->SetValue(ProcessingSeason.Trees[i].MaxHumidity);
		vtMinHumiValue[i]->SetValue(ProcessingSeason.Trees[i].MinHumidity);
	}
	LCDMenu.UpdateScreen();
}

void PrintProcessingSeason()
{
	PrintSeason(ProcessingSeason);
}