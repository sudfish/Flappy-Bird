#pragma once

/**
 * @brief Defines a state in our state machine. 
 *
 * Virtual functions that defines all functions that each state in our 
 * state machine need to have. 
 */

namespace flappy{
    class State{
        public:
            virtual void Init()=0;
            virtual void HandleInput()=0;
            virtual void Update(float dt)=0;
            virtual void Draw(float dt)=0;

            virtual void Pause();
            virtual void Resume();
    };
}
