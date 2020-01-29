#pragma once

#include <SDL.h>

enum COLLIDERTYPE
{
	RECTANGLE
};

class Collider
{
protected:
	SDL_Rect m_bounds;
	COLLIDERTYPE m_type;
public:
	void SetPosition(int p_x, int p_y);
	virtual SDL_Rect GetBounds() = 0;
	COLLIDERTYPE GetType() { return m_type; };
	Collider() {};
	virtual ~Collider() {};
};

class RectangleCollider : public Collider
{
public:
	SDL_Rect GetBounds();
	RectangleCollider(int p_x, int p_y, int p_w, int p_h);
	~RectangleCollider();
};

