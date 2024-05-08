#include "objects/Game.hpp"
#include "states/SplashState.hpp"

#include <stdlib.h>
#include <time.h>


namespace flappy
{
    Game::Game(int width, int height, std::string title){
       for (int i=0; i<3; i++) {
           this->data->scores[i] = 0;
       } 
        srand(time(NULL));
        data->window.create(sf::VideoMode(width, height), title, sf::Style::Close | sf::Style::Titlebar);
        data->machine.AddState(StateRef(new SplashState(this->data)));
        this->Run();
    }

    void Game::Run(){
        float new_time, frame_time, interpolation;
        float current_time = this->clock.getElapsedTime().asSeconds();
        float accumulator = 0.0f;

        while(this->data->window.isOpen()){
            this->data->machine.ProcessStateChanges();
            new_time = this->clock.getElapsedTime().asSeconds();
            frame_time = new_time - current_time;
            
            if(frame_time > 0.25f) frame_time = 0.25f;

            current_time = new_time;
            accumulator += frame_time;

            while(accumulator >= dt){
                this->data->machine.GetActiveState()->HandleInput();
                this->data->machine.GetActiveState()->Update(dt);
                accumulator -= dt;
            }

            interpolation = accumulator/dt;
            this->data->machine.GetActiveState()->Draw(interpolation);
        }
    }
}
