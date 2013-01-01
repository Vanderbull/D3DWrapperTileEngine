#ifndef _TIMING_H_ 
#define _TIMING_H_ 

#include <windows.h>
#include <dinput.h>
#include <string>
#include <vector>
#include <time.h>
#include <sstream>
using namespace std;

class CTiming 
{ 
public:
	~CTiming(void);
	CTiming();
	float  timeAtGameStart;

	LARGE_INTEGER ticksPerSecond; //frequency
	LARGE_INTEGER tick; // a point in time
	LARGE_INTEGER time;// used for converting tick into real time

	LARGE_INTEGER startFrame;
	LARGE_INTEGER stopFrame;
	LARGE_INTEGER currentTick;
	LARGE_INTEGER nFrames;
	LARGE_INTEGER Ticks_To_Wait;
	LARGE_INTEGER tickspassed;
	LARGE_INTEGER ticksleft;
	LARGE_INTEGER prev_frame;
	LARGE_INTEGER framedelay;

	LARGE_INTEGER Fps;
	LARGE_INTEGER LastUpdate;

	unsigned int  numFrames;
	float speedfactor;
	float lastUpdate;
	float fpsUpdateInterval;
	float fps;
	int nFps;

	int done;

	bool FPSinfo();
	void Init();
	void StartTimer();
	void Wait(int MaxFrameRate);
	void FPSloop();
	float UpdateFPS();	
	float GetGameTime();
	float SetSpeedFactor();
	int GetTicksToWait();
}; 
#endif