#include "states/MainMenuState.hpp"
#include "definitions.hpp"
#include "states/GameState.hpp"
#include "machine/StateMachine.hpp"
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>

namespace flappy
{
    MainMenuState::MainMenuState(GameDataRef data) : data(data){

    }

    void MainMenuState::Init(){
        data->assets.LoadTexture("Main Menu Background", MAIN_MENU_BACKGROUND_FILEPATH);
        data->assets.LoadTexture("Title", GAME_TITLE_FILEPATH);
        data->assets.LoadTexture("Play Button", PLAY_BUTTON_FILEPATH);

        background.setTexture(data->assets.GetTexture("Main Menu Background"));
        title.setTexture(data->assets.GetTexture("Title"));
        play_button.setTexture(data->assets.GetTexture("Play Button"));

        title.setPosition( 
                (SCREEN_WIDTH/2)-(title.getGlobalBounds().width/2),
                (title.getGlobalBounds().height/2));
        play_button.setPosition(
                (SCREEN_WIDTH/2) - (play_button.getGlobalBounds().width/2),
                (SCREEN_HEIGHT/2) - (play_button.getGlobalBounds().height/2));
    }

    void MainMenuState::HandleInput(){
        sf::Event event;
        while(data->window.pollEvent(event)){
            switch (event.type) {
                case sf::Event::Closed:
                    data->window.close();
                    break;

                case sf::Event::KeyReleased:
                    switch(event.key.code){
                        case sf::Keyboard::Enter:
                            data->machine.AddState(StateRef(new GameState(data)));
                            break;

                        default:
                            break;
                    }

                default:
                    break;
            }

            if(data->input.IsSpriteClicked(play_button, sf::Mouse::Left, data->window)){
                data->machine.AddState(StateRef(new GameState(data)));
            }
        }
    }

    void MainMenuState::Update(float dt){

    }

    void MainMenuState::Draw(float dt){
        data->window.clear();

        data->window.draw(background);
        data->window.draw(title);
        data->window.draw(play_button);

        data->window.display();
    }

    void MainMenuState::Pause(){

    }

    void MainMenuState::Resume(){

    }
}
