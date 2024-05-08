#include "states/GameOverState.hpp"
#include "states/GameState.hpp"
#include "definitions.hpp"
#include <SFML/Audio/Sound.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Sleep.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <string>

namespace flappy
{
    GameState::GameState(GameDataRef data) : data(data){ }

    void GameState::Init(){
        this->data->game_score = 0;
        this->paused = 0;
        this->speed = 0;

        this->data->assets.LoadFont("Flappy Font", FLAPPY_FONT_FILEPATH);
        this->data->assets.LoadFont("Marker Font", MARKER_FONT_FILEPATH);
        this->data->assets.LoadTexture("Game State Background", GAME_BACKGROUND_FILEPATH);
        this->data->assets.LoadTexture("Pipe Up", PIPE_UP_FILEPATH);
        this->data->assets.LoadTexture("Pipe Down", PIPE_DOWN_FILEPATH);
        this->data->assets.LoadTexture("Land", LAND_FILEPATH);
        this->data->assets.LoadTexture("Bird Frame 1", BIRD_1_FILEPATH);
        this->data->assets.LoadTexture("Bird Frame 2", BIRD_2_FILEPATH);
        this->data->assets.LoadTexture("Bird Frame 3", BIRD_3_FILEPATH);
        this->data->assets.LoadTexture("Pause Button", PAUSE_BUTTON);
        this->data->assets.LoadTexture("Unpause Button", UNPAUSE_BUTTON);
        this->data->assets.LoadTexture("Mute Button", MUTE_BUTTON);
        this->data->assets.LoadTexture("Unmute Button", UNMUTED_BUTTON);
        this->data->assets.LoadSoundBuffer("Hit Sound", HIT_SOUND_FILEPATH);
        this->data->assets.LoadSoundBuffer("Flap Sound", FLAP_SOUND_FILEPATH);
        this->data->assets.LoadSoundBuffer("Score Sound", POINT_SOUND_FILEPATH);

        this->bird = new Bird(this->data);
        this->land = new Land(this->data);
        this->pipe = new Pipe(this->data);

        this->background.setTexture(this->data->assets.GetTexture("Game State Background"));
        this->pause_button.setTexture(this->data->assets.GetTexture("Pause Button"));
        this->unpause_button.setTexture(this->data->assets.GetTexture("Unpause Button"));
        this->mute_button.setTexture(this->data->assets.GetTexture("Mute Button"));
        this->unmute_button.setTexture(this->data->assets.GetTexture("Unmute Button"));
        this->hit_sound.setBuffer(this->data->assets.GetSoundBuffer("Hit Sound"));
        this->flap_sound.setBuffer(this->data->assets.GetSoundBuffer("Flap Sound"));
        this->score_sound.setBuffer(this->data->assets.GetSoundBuffer("Score Sound"));

        this->score_text.setFont(this->data->assets.GetFont("Flappy Font"));
        this->score_text.setCharacterSize(SCORE_FONT_SIZE);
        this->score_text.setOrigin(this->score_text.getGlobalBounds().width/2, this->score_text.getGlobalBounds().height/2);
        this->score_text.setPosition(int(SCREEN_WIDTH/2), 10);

        this->pause_button.setPosition(10, 10);
        this->unpause_button.setPosition(10, 10);

        this->mute_button.setPosition(SCREEN_WIDTH-this->mute_button.getGlobalBounds().width-10, 10);
        this->unmute_button.setPosition(SCREEN_WIDTH-this->unmute_button.getGlobalBounds().width-10, 10);
    }

    void GameState::HandleInput(){
        sf::Event event;

        while(this->data->window.pollEvent(event)){
            switch(event.type){
                case sf::Event::Closed:
                    Quit();
                    break;
                
                case sf::Event::KeyPressed:
                    switch(event.key.code){
                        case sf::Keyboard::Space:       // <Space> => Jump
                            if(!this->paused){
                                if(!muted) this->flap_sound.play();
                                this->bird->Jump();
                            }
                            break;
                        case sf::Keyboard::Q:           // Q => Quit
                            Quit();
                            break;
                        case sf::Keyboard::P:           // P => Pause
                            Pause();
                            break;
                        case sf::Keyboard::M:           // M => Mute
                            Mute();
                            break;
                        default:
                            break;
                    }
                    break;

                default:
                    break;
            }
        }
    }

    void GameState::Update(float dt){
        if(!this->paused) {

            if(ExistsScoringCollision()){
                if(!muted) this->score_sound.play();
                this->data->game_score++;
                this->speed += 0.05;
            }

            if(ExistsEndingCollision()){
                if(!muted) this->hit_sound.play();
                sf::sleep(sf::seconds(0.5));
                this->data->assets.ClearSounds();
                SettleHighScores(this->data->game_score);
                this->clock.restart();
                this->data->machine.AddState(StateRef(new GameOverState(this->data)));
            }

            this->pipe->MovePipes(dt, this->speed);
            this->bird->MoveBird(dt);
            this->land->MoveLand(dt, this->speed);

            if(this->clock.getElapsedTime().asSeconds() > PIPE_SPAWN_FREQUENCY - this->speed){
                this->pipe->SpawnPipes();
                this->clock.restart();
            }

            this->score_text.setString(std::to_string(this->data->game_score));
        }
    }

    void GameState::Draw(float dt){
        this->data->window.clear();
        this->data->window.draw(background);
        this->pipe->DrawPipes();
        this->land->DrawLand();
        this->bird->DrawBird();
        this->data->window.draw(this->score_text);
        if(!this->paused) this->data->window.draw(this->pause_button);
        else this->data->window.draw(this->unpause_button);
        if(!this->muted) this->data->window.draw(this->unmute_button);
        else this->data->window.draw(this->mute_button);
        this->data->window.display();
    }

    bool GameState::ExistsEndingCollision(){
        for(unsigned short int i=0; i < this->pipe->pipe_sprites.size(); i++){
            if(this->bird->IntersectsWith(this->pipe->pipe_sprites.at(i).getGlobalBounds())) return true;
        }
        for(unsigned short int i=0; i < this->land->Sprites().size(); i++){
            if(this->bird->IntersectsWith(this->land->Sprites().at(i).getGlobalBounds())) return true;
        }
        return false;
    }

    bool GameState::ExistsScoringCollision(){
        for(unsigned short int i=0; i < this->pipe->score_boxes.size(); i++){
            if(this->bird->IntersectsWith(this->pipe->score_boxes.at(i).getGlobalBounds())){
                this->pipe->score_boxes.erase(this->pipe->score_boxes.begin() + i);
                return true;
            }
        }
        return false;
    }

    void GameState::SettleHighScores(int score){
        for (int i=0; i<3; i++) {
            if(score > this->data->scores[i]){
                int temp = this->data->scores[i];
                this->data->scores[i] = score;
                score = temp;
            }
        }
    }

    void GameState::Pause(){
       this->paused = !this->paused; 
    }

    void GameState::Mute(){
        this->muted = !this->muted; 
    }

    void GameState::Quit(){
        this->data->assets.ClearSounds();
        this->data->window.close();
    }
}
