#include "definitions.hpp"
#include "objects/Land.hpp"
#include "objects/Game.hpp"

#include <SFML/Graphics/Sprite.hpp>

#include <vector>


namespace flappy
{
    Land::Land(GameDataRef data) : data(data) {
        sf::Sprite sprite_1(data->assets.GetTexture("Land"));
        sf::Sprite sprite_2(data->assets.GetTexture("Land"));

        sprite_1.setPosition(0, data->window.getSize().y - sprite_1.getGlobalBounds().height);
        sprite_2.setPosition(sprite_1.getGlobalBounds().width, data->window.getSize().y - sprite_2.getGlobalBounds().height);

        land_sprites.push_back(sprite_1);
        land_sprites.push_back(sprite_2);
    }

    void Land::MoveLand(float dt, float speed){
        for(unsigned short int i=0; i<land_sprites.size(); i++){
            if(land_sprites.at(i).getPosition().x + land_sprites.at(i).getGlobalBounds().width < 0){
                land_sprites.at(i).move(land_sprites.at(i).getGlobalBounds().width*2, 0);
            }

            float movement = PIPE_MOVEMENT_SPEED * dt + speed;
            land_sprites.at(i).move(-movement, 0);
        } 
    }

    void Land::DrawLand(){
        for(unsigned short int i = 0; i < land_sprites.size(); i++){
            data->window.draw(land_sprites.at(i));
        } 
    }

    std::vector<sf::Sprite> Land::Sprites(){
        return this->land_sprites;
    }
}
