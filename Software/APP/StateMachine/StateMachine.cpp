/**
 * StateMachine.cpp
 *
 *  Created on: 10-03-2019
 *  @author: Paweł Warzecha
 */

#include "StateMachine.hpp"
#include "DataContainer.hpp"

#include "StateMachine.hpp"

StateMachine::StateMachine(TransitionMatrix transitionMatrix, State * startState) : transitionMatrix_(transitionMatrix), currentState_(startState)
{
}
