#include "objects/Pipe.hpp"
#include "definitions.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>

namespace flappy{
    Pipe::Pipe(GameDataRef data) : data(data){
        this->offset = 0;
    }

    void Pipe::SpawnBottomPipe(){
        sf::Sprite sprite(this->data->assets.GetTexture("Pipe Up"));
        sprite.setPosition(this->data->window.getSize().x, this->data->window.getSize().y - sprite.getGlobalBounds().height - this->offset);
        this->pipe_sprites.push_back(sprite);
    }

    void Pipe::SpawnTopPipe(){
        sf::Sprite sprite(this->data->assets.GetTexture("Pipe Down"));
        sprite.setPosition(this->data->window.getSize().x, -this->offset);
        this->pipe_sprites.push_back(sprite);
    }

    void Pipe::SpawnScorePipe(){
        sf::Sprite top_pipe = this->pipe_sprites.at(this->pipe_sprites.size()-2);
        sf::Sprite bottom_pipe = this->pipe_sprites.at(this->pipe_sprites.size()-1);

        sf::RectangleShape score_box;
        score_box.setSize(sf::Vector2f(
                top_pipe.getGlobalBounds().width,
                (
                 (bottom_pipe.getPosition().y) 
                 - 
                 (top_pipe.getPosition().y + top_pipe.getGlobalBounds().height)
                )));
        score_box.setPosition(
                top_pipe.getPosition().x,
                top_pipe.getPosition().y + top_pipe.getGlobalBounds().height
                );
        score_box.setFillColor(sf::Color(0,0,0, 0));
        this->score_boxes.push_back(score_box);
    }

    void Pipe::SpawnPipes(){
        this->RandomizeOffset();
        this->SpawnTopPipe();
        this->SpawnBottomPipe();
        this->SpawnScorePipe();
    }

    void Pipe::MovePipes( float dt, float speed ){
        float movement = PIPE_MOVEMENT_SPEED * dt + speed;
        for(unsigned short int i = 0; i < this->pipe_sprites.size(); i++){
            this->pipe_sprites.at(i).move(-movement, 0);
        }
        for(unsigned short int i = 0; i < this->score_boxes.size(); i++){
            this->score_boxes.at(i).move(-movement, 0);
        }
    }
    
    void Pipe::DrawPipes(){
        for(unsigned short int i=0; i < this->pipe_sprites.size(); i++){
            if(this->pipe_sprites.at(i).getPosition().x + this->pipe_sprites.at(i).getGlobalBounds().width < 0){
                this->pipe_sprites.erase(this->pipe_sprites.begin() + i);
                continue;
            }
            this->data->window.draw(pipe_sprites.at(i));
        }

        for(unsigned short int i=0; i < this->score_boxes.size(); i++){
            if(this->score_boxes.at(i).getPosition().x + this->score_boxes.at(i).getGlobalBounds().width < 0){
                this->score_boxes.erase(this->score_boxes.begin() + i);
                continue;
            }
            this->data->window.draw(this->score_boxes.at(i));
        }
    }

    void Pipe::RandomizeOffset(){
        this->offset = rand() % (this->data->assets.GetTexture("Land").getSize().y + 1);
    }
}
