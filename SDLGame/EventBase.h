#ifndef EVENTBASE_H_
#define EVENTBASE_H_

#include "stdafx.h"

class EventBase
{
protected:
	std::string s_eventID;

public:
	virtual std::string getStateID() const { return s_eventID; }
	virtual void operator()() = 0;
};

#endif // EVENTBASE_H_