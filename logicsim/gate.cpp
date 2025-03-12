#include <vector>
#include <random>
#include <iostream>

#include "gate.h"
#include "wire.h"

Gate::Gate(int num_inputs, Wire* output) 
	: m_output(output), m_inputs(num_inputs), m_delay(0), m_current_state('X')
{
    
}

Gate::~Gate(){}

void Gate::wireInput(unsigned int id, Wire* in)
{
    if(id < m_inputs.size())
    {
        m_inputs[id] = in;
    }
}

And2Gate::And2Gate(Wire* a, Wire* b, Wire* o) : Gate(2,o)
{
    wireInput(0,a);
    wireInput(1,b);
}

Event* And2Gate::update(uint64_t current_time)
{
    
  char state = '1';
  Event* e = nullptr;
	for(auto w : m_inputs)
	{
		char in = w->getState();
		if(in == '0')
		{
			state = '0';
			break;
		}
		else if(in == 'X')
		{
			state = 'X';
		}
	}
    if(state != m_current_state)
	{
    m_current_state = state;
    uint64_t next = current_time + m_delay;
		e = new Event {next,m_output,state};
         
	}
    return e;
}

Or2Gate::Or2Gate(Wire* a, Wire* b, Wire* o) : Gate(2,o)
{
    wireInput(0,a);
    wireInput(1,b);
}

Event* Or2Gate::update(uint64_t current_time)
{
    
  char state = '0';
  Event* e = nullptr;
	for(auto w : m_inputs)
	{
		char in = w->getState();
		if(in == '1')
		{
			state = '1';
			break;
		}
		else if(in == 'X')
		{
			state = 'X';
		}
	}
  if(state != m_current_state)
	{
    m_current_state = state;
		uint64_t next = current_time + m_delay;
		e = new Event {next,m_output,state};
         
	}
  return e;
}

// ctor for NOT gate
NotGate::NotGate(Wire* input, Wire* output) : Gate(1, output)
{
	wireInput(0, input);
}

// update func for NOT gate
Event* NotGate::update(uint64_t current_time)
{

	char state = 'X';
	Event* e = nullptr;
	
	// check input state and update
	for(auto w : m_inputs)
	{
		char in = w->getState();
		if(in == '1')
		{
			state = '0';
			break;
		}
		else if(in == '0')
		{
			state = '1';
		}
	}

	// change state
	if(state != m_current_state)
	{
		m_current_state = state;
		uint64_t next = current_time + m_delay;
		e = new Event {next, m_output,state};	
	}
	
	return e;


	/*
	char state = m_inputs[0]->getState(); // read input state
    char newState;

    // apply NOT truth table
    if (state == '0') {
		newState = '1';
	}
    else if (state == '1'){
		newState = '0';
	}
    else {
		// undefined still undefined
		newState = 'X';
	}

    if (newState != m_current_state)  // only trigger if state changes
    {
        m_current_state = newState;
        uint64_t next_time = current_time + m_delay;
        return new Event {next_time, m_output, newState}; // schedule event
    }
    
    return nullptr;
	*/
}
