#include <iostream>
#include <iomanip>
using namespace std;
#include <limits.h>
#include <float.h>

#include ".\timing.h"

extern HINSTANCE hInst;

CTiming::CTiming() 
{
	ticksPerSecond.QuadPart = 0;
	tick.QuadPart = 0; // a point in time
	time.QuadPart = 0;// for converting tick into real time

	startFrame.QuadPart = 0;
	stopFrame.QuadPart = 0;
	currentTick.QuadPart = 0;
	nFrames.QuadPart = 0;
	Ticks_To_Wait.QuadPart = 0;
	tickspassed.QuadPart = 0;
	ticksleft.QuadPart = 0;
	prev_frame.QuadPart = 0;
	framedelay.QuadPart = 0;

	done = 0;

	// Global variables for measuring fps
	lastUpdate        = 0.0f;
	fpsUpdateInterval = 0.5f;
	numFrames         = 0;
	fps               = 0.0f;
   // Set current and previous time to the clock time at initialisation. 
   // Otherwise mDelta = mCurrentTime - mPrevious in CalculateFrameRate() will 
   // give an absurd number during its first call and screw up all the physics
	if(!QueryPerformanceFrequency(&ticksPerSecond))
	{
		ticksPerSecond.QuadPart = 1000;
	}

	timeAtGameStart = 0.0f;
	timeAtGameStart = GetGameTime();

   QueryPerformanceCounter(&startFrame);
}

bool CTiming::FPSinfo()
{
//	cout << "Ticks per second: " << ticksPerSecond.QuadPart << endl;
//	cout << "star frame: " << startFrame.QuadPart << endl;
//	cout << "stop frame : " << stopFrame.QuadPart << endl;
//	cout << "current tick: " << currentTick.QuadPart << endl;
//	cout << "Number of frames:" << nFrames.QuadPart << endl;
//	cout << "Ticks to wait: " << Ticks_To_Wait.QuadPart << endl;
//	cout << "ticks passed: " << tickspassed.QuadPart << endl;
//	cout << "ticks left: " << ticksleft.QuadPart << endl;
//	cout << "previous frame: " << prev_frame.QuadPart << endl;
//	cout << "frame delay: " << framedelay.QuadPart << endl;
	
//	cout << "last update: " << lastUpdate<<endl;
//	cout << "fpsupdateinterval: " << fpsUpdateInterval<< endl;
//	cout << "numframes: " << numFrames << "-";
//	cout << "fps: " << fps << endl;

	return true;
}

CTiming::~CTiming(void)
{
	QueryPerformanceCounter(&stopFrame);
	cout << " " << stopFrame.QuadPart - startFrame.QuadPart;
}

void CTiming::Init()
{
	prev_frame.QuadPart = 0;
	ticksleft.QuadPart = 0;
}

void CTiming::StartTimer()
{
	nFps = QueryPerformanceCounter(&startFrame);
}

void CTiming::Wait(int MaxFrameRate)
{
	nFps = MaxFrameRate;
	Ticks_To_Wait.QuadPart = ticksPerSecond.QuadPart/MaxFrameRate;
}

void CTiming::FPSloop()
{
	do
	{
		QueryPerformanceCounter(&time);
		tickspassed.QuadPart = time.QuadPart - prev_frame.QuadPart;
		ticksleft.QuadPart = Ticks_To_Wait.QuadPart - tickspassed.QuadPart;

		if(time.QuadPart < prev_frame.QuadPart)
			done = 1;

		if(tickspassed.QuadPart >= Ticks_To_Wait.QuadPart)
			done = 1;
	}
	while(!done);

	prev_frame = time;
}

int CTiming::GetTicksToWait()
{
	return (int)((__int64)Ticks_To_Wait.QuadPart);
}

float CTiming::UpdateFPS()
{
	numFrames++;
	float currentUpdate = GetGameTime();
	
	if( currentUpdate - lastUpdate > fpsUpdateInterval )
	{
		cout << "Frames rendered during a" << fpsUpdateInterval << " seconds interval" << numFrames << endl;
		fps = numFrames / (currentUpdate - lastUpdate);
		lastUpdate = currentUpdate;
		numFrames = 0;

		cout << "FPS ____: " << fps << endl;
	}
	return fps;
}

float CTiming::SetSpeedFactor()
{
	QueryPerformanceCounter(&currentTick);
	speedfactor = (float)(currentTick.QuadPart-framedelay.QuadPart)/((float)ticksPerSecond.QuadPart/nFps);
	fps = nFps/speedfactor;
	if (speedfactor <= 0)
	    speedfactor = 1;

	framedelay = currentTick;
	return fps;
}

float CTiming::GetGameTime()
{
	UINT64 ticks;
	float time;
  
	//// This is the number of clock ticks since start
	//if( !QueryPerformanceCounter((LARGE_INTEGER *)&ticks) )
	//{
	//	ticks = (UINT64)timeGetTime();
	//}

	//// Divide by frequency to get the time in seconds
	//time = (float)(__int64)ticks/(float)(__int64)ticksPerSecond.QuadPart;
	//// Subtract the time at game start to get
	//// the time since the game started
	//time -= timeAtGameStart;

	return time;
}
