#include "TEST_STATE_1.h"
#include "Service.h"
#include "SoundHandler.h"
#include "CollisionHandler.h"
#include "InputHandler.h"
#include "Sound.h"
#include <iostream>
#include "Config.h"
#include <time.h>
#include <WanderState.h>


TEST_STATE_1::TEST_STATE_1(SDL_Renderer& p_renderer) : m_renderer(&p_renderer)
{
	m_sound = Service<SoundHandler>::Get()->CreateSound("../Assets/plopp.wav");
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
      int randomNumber = rand()% (size);
		Grass* tmp = new Grass;
		tmp->Create("../Assets/grass.png", grid_.Tiles_.at(randomNumber)->bounds_.x, grid_.Tiles_.at(randomNumber)->bounds_.y);
      grid_.Tiles_.at(randomNumber)->grass_ = tmp;
		Grass_.push_back(tmp);
      tmp->x_ = tmp->bounds_.x / Config::TILE_SIZE;
      tmp->y_ = tmp->bounds_.y / Config::TILE_SIZE;
      tmp->grid_ = &grid_;
	}
	for (int i = 0; i < 1; i++)
	{
		std::vector<AgentState*> yeet;
		Agent* tmpSheep = new Agent("../Assets/sheep.png", new WanderState(), yeet, Vector2(13, 14));
      tmpSheep->currentState_->agent_ = tmpSheep;
      tmpSheep->grid_ = &grid_;
      int index = grid_.GetTileIndex(13, 14);
		grid_.Tiles_[index]->agents_[0] = tmpSheep;
		Sheep_.push_back(tmpSheep);
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

      if (Grass_.at(i)->currentState_ == DEAD)
      {
         Grass* grass = Grass_.at(i);
         int tileIndex = grid_.GetTileIndex(grass->x_, grass->y_);
         grid_.Tiles_.at(tileIndex)->grass_ = nullptr;
         Grass_.erase(Grass_.begin()+i);
      }
	}
	for (int i = 0; i < Sheep_.size(); i++)
	{
		Sheep_.at(i)->Render(m_renderer);
		Sheep_.at(i)->Update(deltaTime_.AsSeconds());
	}
	return true;
}

void TEST_STATE_1::Exit()
{
	std::cout << "TEST_STATE_1::Exit" << std::endl;
}
