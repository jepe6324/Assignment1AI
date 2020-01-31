// Agent.h

#ifndef AGENT_H_INCLUDED
#define AGENT_H_INCLUDED

struct SDL_Renderer;
struct Sprite;
struct Collider;
struct State;

struct Agent{
   virtual ~Agent(){};

   virtual void Update() = 0;
   virtual void Render(SDL_Renderer *renderer) = 0;

   Sprite* sprite_;
   Collider* collider_;
   State* state_;
};

#endif //AGENT_H_INCLUDED