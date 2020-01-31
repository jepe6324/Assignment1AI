// Agent.h

#ifndef AGENT_H_INCLUDED
#define AGENT_H_INCLUDED

#include "FSM.h"
#include "State.h"
#include "Vector.h"
#include "Collider.h"

struct Sprite;
struct DeltaTime;
struct SDL_Renderer;

struct Agent : FSM
{
   Sprite* sprite_;
   RectangleCollider collider_;
   Vector2 position_;
   const char* species_;

   AgentState* currentState_;
   std::vector<AgentState*> stateList_;

   Agent(const char* filepath,
         AgentState* startState,
         std::vector<AgentState*> states,
         Vector2 startPos);
   ~Agent();

	void Render(SDL_Renderer* renderer_);

   void Update(float dt);
};

#endif //!AGENT_H_INCLUDED