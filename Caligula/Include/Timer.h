//TIMER_H_INCLUDED
#ifndef TIMER_H_INCLUDED
#define TIMER_H_INCLUDED

#include <SDL.h>

struct timer
{
	timer();

	/*timer operator+(const timer& rhs) const;
	timer operator-(const timer& rhs) const;
	timer& operator+=(const timer& rhs);
	timer& operator-=(const timer& rhs);

	bool operator<(const timer& rhs) const;
	bool operator>(const timer& rhs) const;
	bool operator==(const timer& rhs) const;
	bool operator!=(const timer& rhs) const;*/

	float deltaTime_;
	float oldTick_;
	
	float GetAsSeconds();
	float GetAsMiliSeconds();
	void Update();
};

#endif // !TIMER_H_INCLUDED
