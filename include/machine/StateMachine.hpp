#pragma once

#include <memory>
#include <stack>
#include "machine/State.hpp"

/**
 * @brief State manager. 
 *
 * State machine, a queue to manage individual states in game. Each game state
 * can be thought of as having it's own logic, this machine will process the 
 * logic of the current state we are in, while maintaining game data. 
 */

namespace flappy
{
    typedef std::unique_ptr<State> StateRef;

    class StateMachine{
        public:
            StateMachine(){}
            ~StateMachine(){}
            void AddState(StateRef new_state, bool is_replacing = true);
            void RemoveState();
            void ProcessStateChanges();
            StateRef &GetActiveState();

        private: 
            std::stack<StateRef> states;
            StateRef new_state;
            bool is_removing;
            bool is_adding;
            bool is_replacing;
    };
}
