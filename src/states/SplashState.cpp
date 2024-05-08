#include "objects/Game.hpp"
#include "states/SplashState.hpp"
#include "states/MainMenuState.hpp"
#include "definitions.hpp"
#include <SFML/Window/Event.hpp>

namespace flappy
{
    SplashState::SplashState(GameDataRef data) : data(data){
        
    }

    void SplashState::Init(){
        data->assets.LoadTexture("Splash State Background", SPLASH_SCENE_BACKGROUND_FILEPATH);
        background.setTexture(this->data->assets.GetTexture("Splash State Background"));
    }

    void SplashState::HandleInput(){
        sf::Event event;

        while(data->window.pollEvent(event)){
            switch(event.type){
                case sf::Event::Closed:
                    data->window.close();
                    break;
                
                case sf::Event::KeyPressed:
                    skipped = true;
                    break;

                default:
                    break;
            }
        }
    }

    void SplashState::Update(float dt){
        if(skipped || clock.getElapsedTime().asSeconds() > SPLASH_STATE_SHOW_TIME){
            data->machine.AddState(StateRef(new MainMenuState(data)), true);
        }
    }

    void SplashState::Draw(float dt){
        data->window.clear();
        data->window.draw(background);
        data->window.display();
    }
}
