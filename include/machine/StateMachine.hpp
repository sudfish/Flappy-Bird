#pragma once

#include "machine/State.hpp"

#include <memory>
#include <stack>


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
