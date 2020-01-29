#include "Timer.h"

timer::timer()
{
	timer::deltaTime_ = 0;
	timer::oldTick_ = 0;
}

float timer::GetAsSeconds()
{
	return deltaTime_ / 1000;
}

float timer::GetAsMiliSeconds()
{
	return deltaTime_;
}

void timer::Update()
{
	Uint32 tick = SDL_GetTicks();
	deltaTime_ = tick - oldTick_;
	oldTick_ = tick;
}
