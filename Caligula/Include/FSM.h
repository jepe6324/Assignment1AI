#pragma once

#include <vector>
#include <string>

class State;

class FSM // Finite State Machine
{
	std::vector<State*> m_states;
	State* m_currentState;
	void SwitchState(State* p_state);
public:
	FSM();
	~FSM();
	void Update();
	void AddState(State* p_state);
	void RemoveState(State* p_state);
	void SetState(State* p_state);
};