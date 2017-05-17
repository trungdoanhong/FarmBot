//
//// Copy StandardCplusplus folder to Mydocument\Arduino\libraries to use below libraries
//#include <StandardCplusplus.h>
//#include <vector>
//
//
//using namespace std;
//
//class Gcode
//{
//public:
//	int Id;
//};
//
//class Execute
//{
//public:
//	void ChangeId(int* id)
//	{
//		*id = 10;
//	}
//	void SetQueue(vector<String>* queue)
//	{
//		GcodeQueue = queue;
//	}
//	void PushGcode(String gcode)
//	{
//		GcodeQueue->push_back(gcode);
//	}
//
//	vector<String>* GcodeQueue;
//};
//
//
//void setup()
//{
//	Serial.begin(9600);
//
//	vector<String> gcodeQueue;
//	gcodeQueue.push_back("G1");
//	gcodeQueue.push_back("G0");
//
//	Gcode gcodeObj;
//	Execute executeObj;
//
//	executeObj.SetQueue(&gcodeQueue);
//	executeObj.PushGcode("M20");
//	gcodeQueue.push_back("G10");
//	gcodeQueue.push_back("G110");
//
//	for (int i = 0; i < gcodeQueue.size(); i++)
//	{
//		Serial.println(gcodeQueue[i]);
//	}
//
//	gcodeQueue.erase(gcodeQueue.begin() + 2);
//
//	Serial.println();
//
//	for (int i = 0; i < gcodeQueue.size(); i++)
//	{
//		Serial.println(gcodeQueue[i]);
//	}
//}
//
//void loop()
//{
//
//}