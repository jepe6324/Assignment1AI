//TILE_H_INCLUDED

#ifndef TILE_H_INCLUDED
#define TILE_H_INCLUDED

#include <SDL.h>
#include "Sprite.h"
#include "Grass.h"

struct Grass;

struct Tile {

   Grass* grass_; // if nullptr it's dirt

	SDL_Rect bounds_;
	Sprite* currentSprite_;

	void Create(const char* p_textureFilePath,int xPos, int yPos, int height, int width);
	void Render(SDL_Renderer* renderer_);
};

#endif // !TILE_H_INCLUDED
