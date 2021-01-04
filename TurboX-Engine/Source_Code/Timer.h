#ifndef __TIMER_H__
#define __TIMER_H__

#include "Globals.h"
#include "Libraries\SDL\include\SDL.h"

class Timer
{
public:

	// Constructor
	Timer();

	void Start();
	void Stop();

	Uint32 Read();
	float ReadSec();

	void Resume();
	void ResetTimer();
private:

	bool	running;
	float	started_at;
	float	stopped_at;
	float	resumed_at;
};

#endif //__TIMER_H__