#pragma once

#include <vector>
#include <string>

struct State;

struct FSM // Finite State Machine
{
	std::vector<State*> m_states;
	State* m_currentState;

	FSM();
   virtual ~FSM();

	virtual void Update();
   virtual void AddState(State* p_state);
   virtual void RemoveState(State* p_state);
   virtual void SetState(State* p_state);
   virtual void SwitchState(State* p_state);
};