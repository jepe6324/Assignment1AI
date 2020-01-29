#pragma once

#include "State.h"
#include <array>
#include "Grid.h"
#include "Grass.h"
#include "DeltaTime.h"


struct SDL_Renderer;
class Sound;

class TEST_STATE_1 : public State
{
	unsigned int m_playerOneScore;
	unsigned int m_playerTwoScore;
	SDL_Renderer* m_renderer;
	Sound* m_sound;
	int m_timer;
	Grid grid_;
	std::vector<Grass*> Grass_;
   DeltaTime deltaTime_;
public:
	TEST_STATE_1(SDL_Renderer& p_renderer); 
	void Enter();
	bool Update();
	void Exit();
};
