#include "TEST_STATE_1.h"
#include "Service.h"
#include "SoundHandler.h"
#include "CollisionHandler.h"
#include "InputHandler.h"
#include "Sound.h"
#include <iostream>
#include "Config.h"
#include <time.h>

TEST_STATE_1::TEST_STATE_1(SDL_Renderer& p_renderer) : m_renderer(&p_renderer)
{
	m_sound = Service<SoundHandler>::Get()->CreateSound("../Assets/plopp.wav");
	m_name = "TEST_STATE_1";
}

void TEST_STATE_1::Enter()
{
	srand(time(NULL));
	std::cout << "TEST_STATE_1::Enter" << std::endl;
	grid_.Create();
   grid_.grass_ = &Grass_;
	int size = grid_.Tiles_.size();
	
	for (int i = 0; i < 10; i++)
	{
      int randomNumber = rand()% (size + 1);
		Grass* tmp = new Grass;
		tmp->Create("../Assets/grass.png", grid_.Tiles_.at(randomNumber)->bounds_.x, grid_.Tiles_.at(randomNumber)->bounds_.y);
      grid_.Tiles_.at(randomNumber)->grass_ = tmp;
		Grass_.push_back(tmp);
      tmp->x_ = tmp->bounds_.x / Config::TILE_SIZE;
      tmp->y_ = tmp->bounds_.y / Config::TILE_SIZE;
      tmp->grid_ = &grid_;
	}
}

bool TEST_STATE_1::Update()
{

   deltaTime_.Update();

	grid_.Render(m_renderer);
	for (int i = 0; i < Grass_.size(); i++)
	{
		Grass_.at(i)->Sense(deltaTime_.AsSeconds());
      Grass_.at(i)->Decide(deltaTime_.AsSeconds());
      Grass_.at(i)->Act(deltaTime_.AsSeconds());
      Grass_.at(i)->Render(m_renderer);
	}
	return true;
}

void TEST_STATE_1::Exit()
{
	std::cout << "TEST_STATE_1::Exit" << std::endl;
}
