// Agent.h

#ifndef AGENT_H_INCLUDED
#define AGENT_H_INCLUDED

#include "FSM.h"
#include "Vector.h"
#include "Collider.h"

struct Sprite;

struct Agent : FSM
{
   Sprite* sprite_;
   RectangleCollider collider_;
   Vector2 position_;
   const char* species_;

   Agent(const char* filepath,
         State* startState,
         std::vector<State*> states,
         Vector2 startPos);
   ~Agent();
};

#endif //!AGENT_H_INCLUDED