#include "definitions.hpp"
#include "machine/StateMachine.hpp"
#include "objects/Game.hpp"
#include "states/GameState.hpp"
#include "states/GameOverState.hpp"

#include <SFML/Window/Keyboard.hpp>

#include <string>


namespace flappy
{
    GameOverState::GameOverState(GameDataRef data) : data(data){
        
    }

    void GameOverState::Init(){
        this->data->assets.LoadTexture("Game Over State Background", GAME_OVER_BACKGROUND_FILEPATH);
        this->data->assets.LoadTexture("Game Over Title", GAME_OVER_TITLE_FILEPATH);
        this->data->assets.LoadTexture("Game Over Body", GAME_OVER_BODY_FILEPATH);
        this->data->assets.LoadTexture("Gold Medal", GOLD_MEDAL_FILEPATH);
        this->data->assets.LoadTexture("Silver Medal", SILVER_MEDAL_FILEPATH);
        this->data->assets.LoadTexture("Bronze Medal", BRONZE_MEDAL_FILEPATH);
        this->data->assets.LoadTexture("Play Button", PLAY_BUTTON_FILEPATH);

        this->background.setTexture(this->data->assets.GetTexture("Game Over State Background"));
        this->title.setTexture(this->data->assets.GetTexture("Game Over Title"));
        this->title.setOrigin(
                this->title.getGlobalBounds().width/2,
                this->title.getGlobalBounds().height/2
                );
        this->title.setPosition(
                int(SCREEN_WIDTH/2),
                int(SCREEN_HEIGHT/5)
                );
        this->body.setTexture(this->data->assets.GetTexture("Game Over Body"));
        this->body.setOrigin(
                this->body.getGlobalBounds().width/2,
                this->body.getGlobalBounds().height/2
                );
        this->body.setPosition(
                int(SCREEN_WIDTH/2),
                int(SCREEN_HEIGHT/2)
                );

        this->best_score.setFont(this->data->assets.GetFont("Flappy Font"));
        this->best_score.setCharacterSize(SCORE_FONT_SIZE);
        this->best_score.setString(std::to_string(this->data->scores[0]));
        this->best_score.setOrigin(this->best_score.getGlobalBounds().width, this->best_score.getGlobalBounds().height);
        this->best_score.setPosition(int(3*SCREEN_WIDTH/4), int(SCREEN_HEIGHT/2)+85);

        this->game_score.setFont(this->data->assets.GetFont("Flappy Font"));
        this->game_score.setCharacterSize(SCORE_FONT_SIZE);
        this->game_score.setString(std::to_string(this->data->game_score));
        this->game_score.setOrigin(this->game_score.getGlobalBounds().width, this->game_score.getGlobalBounds().height);
        this->game_score.setPosition(int(3*SCREEN_WIDTH/4), int(SCREEN_HEIGHT/2)-15);

        if(this->data->game_score == this->data->scores[0]){
            this->medal.setTexture(this->data->assets.GetTexture("Gold Medal"));
        } else if (this->data->game_score == this->data->scores[1]){
            this->medal.setTexture(this->data->assets.GetTexture("Silver Medal"));
        } else if (this->data->game_score == this->data->scores[2]){
            this->medal.setTexture(this->data->assets.GetTexture("Bronze Medal"));
        }
        this->medal.setOrigin(
                this->medal.getGlobalBounds().width/2,
                this->medal.getGlobalBounds().height/2
                );
        this->medal.setPosition(
                int(SCREEN_WIDTH/2)-150,
                int(SCREEN_HEIGHT/2)+20
                );

        this->play_button.setTexture(data->assets.GetTexture("Play Button"));
        this->play_button.setPosition(
                (SCREEN_WIDTH/2) - (this->play_button.getGlobalBounds().width/2),
                (SCREEN_HEIGHT/2) - (this->play_button.getGlobalBounds().height/2) + 300
        );
    }

    void GameOverState::HandleInput(){
        sf::Event event;

        while(this->data->window.pollEvent(event)){
            switch (event.type){
                case sf::Event::Closed:
                    this->data->window.close();
                    break;
                case sf::Event::KeyReleased:
                    switch(event.key.code){
                        case sf::Keyboard::Q:
                            this->data->window.close();
                            break;
                        case sf::Keyboard::R:       // R => Restart
                            RestartGame();
                            break;
                        default:
                            break;
                    }
                default:
                    break;
            }
        }


        if(data->input.IsSpriteClicked(play_button, sf::Mouse::Left, data->window)){
            RestartGame();
        }
    }

    void GameOverState::Update(float dt){

    }

    void GameOverState::Draw(float dt){
        this->data->window.clear();
        this->data->window.draw(background);
        this->data->window.draw(title);
        this->data->window.draw(body);
        this->data->window.draw(medal);
        this->data->window.draw(this->best_score);
        this->data->window.draw(this->game_score);
        this->data->window.draw(this->play_button);
        this->data->window.display();
    }

    void GameOverState::RestartGame(){
       this->data->machine.AddState(StateRef(new GameState(data)), true); 
    }
}
