#include "machine/StateMachine.hpp"

namespace flappy{
    void StateMachine::AddState(StateRef new_state, bool is_replacing){
        this->is_adding = true;
        this->is_replacing = is_replacing;
        this->new_state = std::move(new_state);
    }

    void StateMachine::RemoveState(){
        this->is_removing = true;
    }

    void StateMachine::ProcessStateChanges(){
        if(this->is_removing && !this->states.empty()){
            this->states.pop();
            
            if(!this->states.empty()){
                this->states.top()->Resume();
            }

            this->is_removing = false;
        }

        if(this->is_adding){
            if(!this->states.empty()){
                if(this->is_replacing) this->states.pop();           
                else this->states.top()->Pause();
            }
            this->states.push(std::move(this->new_state));
            this->states.top()->Init();
            this->is_adding = false;
        }
    }

    StateRef &StateMachine::GetActiveState(){
        return this->states.top();
    }
}
