#ifndef __j1TIMER_H__
#define __j1TIMER_H__

#include "p2Defs.h"

class j1Timer
{
public:

	// Constructor
	j1Timer();

	void Start();
	void Stop();
	uint32 Read() const;
	float ReadSec() const;
	void SetFlag(bool state) {
		flag = state;
	}

private:
	bool flag = false;
	uint32	started_at;
};

#endif //__j1TIMER_H__