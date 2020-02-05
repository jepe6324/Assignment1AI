//GRASS_H_INCLUDED

#ifndef GRASS_H_INCLUDED
#define GRASS_H_INCLUDED

#include "Sprite.h"
#include "Grid.h"
#include "Agent.h"
#include "Timer.h"

enum GrassState {
	GROWING,
	TRAMPLED,
	SPREADING,
	DYING,
   DEAD,
	EATEN
};

struct Grid;

struct Grass {	
	Grass();

	void Create(const char* p_textureFilePath, int xPos, int yPos);
	void Render(SDL_Renderer* renderer_);
	void Sense(float dt);
	void Decide(float dt);
   void Act(float dt);
	float Eaten(float biteSize);
	Timer EatenTimer_;

	Sprite* currentSprite_;
	SDL_Rect bounds_;
	GrassState currentState_;
	float minHealth_;
	float health_;
   Grid* grid_;

   float decideAccumulator;
	float maturityAccumulator;
	float tileToSpread;

   int x_, y_; // grid placement
};
#endif // !GRASS_H_INCLUDED