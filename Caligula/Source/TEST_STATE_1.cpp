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
#include <BreedState.h>


TEST_STATE_1::TEST_STATE_1(SDL_Renderer& p_renderer) : m_renderer(&p_renderer)
{
	m_sound = Service<SoundHandler>::Get()->CreateSound("../Assets/plopp.wav");
}

void TEST_STATE_1::Enter()
{
	srand(time(NULL));
	std::cout << "TEST_STATE_1::Enter" << std::endl;
	grid_.Create();
   grid_.grass_ = new std::vector<Grass*>;
	int size = grid_.tiles_.size();
	
	for (int i = 0; i < 10; i++)
	{
      int randomNumber = rand()% (size);
		Grass* tmp = new Grass();
		tmp->Create("../Assets/grass.png", grid_.tiles_.at(randomNumber)->bounds_.x, grid_.tiles_.at(randomNumber)->bounds_.y);
      grid_.tiles_.at(randomNumber)->grass_ = tmp;
      grid_.grass_->push_back(tmp);
      tmp->position_.x_ = tmp->bounds_.x / Config::TILE_SIZE;
      tmp->position_.y_ = tmp->bounds_.y / Config::TILE_SIZE;
      tmp->grid_ = &grid_;
	}
	for (int i = 0; i < 1; i++)
	{
		Agent* tmpSheep = new Agent("../Assets/sheep.png", new WanderState(), Vector2(13, 14));
      tmpSheep->species_ = Agent::SHEEP;

      tmpSheep->grid_ = &grid_;
      int index = grid_.GetTileIndex(13, 14);// Hard coded spawn point
		grid_.tiles_[index]->agents_[0] = tmpSheep;
      grid_.agents_->push_back(tmpSheep);
	}
}

bool TEST_STATE_1::Update()
{

   deltaTime_.Update();

	grid_.Render(m_renderer);
	for (int i = 0; i < grid_.grass_->size(); i++)
	{
      grid_.grass_->at(i)->Sense(deltaTime_.AsSeconds());
      grid_.grass_->at(i)->Decide(deltaTime_.AsSeconds());
      grid_.grass_->at(i)->Act(deltaTime_.AsSeconds());
      grid_.grass_->at(i)->Render(m_renderer);

      if (grid_.grass_->at(i)->currentState_ == DEAD)
      {
         Grass* grass = grid_.grass_->at(i);
         int tileIndex = grid_.GetTileIndex(grass->position_);
         grid_.tiles_.at(tileIndex)->grass_ = nullptr;
         grid_.grass_->erase(grid_.grass_->begin()+i);
         delete grass;
      }
	}
	for (int i = 0; i < grid_.agents_->size(); i++)
	{
		grid_.agents_->at(i)->Render(m_renderer);
      grid_.agents_->at(i)->Update(deltaTime_.AsSeconds());
	}
	return true;
}

void TEST_STATE_1::Exit()
{
	std::cout << "TEST_STATE_1::Exit" << std::endl;
}
