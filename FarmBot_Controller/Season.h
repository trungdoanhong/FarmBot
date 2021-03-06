#define NULL_TIME 24

typedef struct
{
	uint8_t Hour = NULL_TIME;
	uint8_t Minute = 0;
} Time;

typedef struct
{
	char Name[30];
	int16_t MaxTemperature;
	int16_t MaxHumidity;
	int16_t MinHumidity;
	Time TimesForWater[6];
} Tree;


typedef struct
{
	uint8_t Id;
	char Name[30];
	uint8_t Garden[24];
	Tree Trees[3];
} Season;