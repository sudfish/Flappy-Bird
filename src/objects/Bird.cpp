#include "definitions.hpp"
#include "objects/Bird.hpp"

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Transformable.hpp>


namespace flappy {
    Bird::Bird(GameDataRef data) : data(data) {
        y_velocity = 0;
        bird_sprite.setTexture(data->assets.GetTexture("Bird Frame 2"));
        bird_sprite.setOrigin(bird_sprite.getGlobalBounds().width/2, bird_sprite.getGlobalBounds().height/2);
        bird_sprite.setPosition(int(SCREEN_WIDTH/4), int(SCREEN_HEIGHT/2));
    }

    void Bird::Jump(){
        jump = true;
    }

    void Bird::MoveBird(float dt){
        if(IsWithinBounds()){
            if(jump && y_velocity < MAX_VELOCITY) {
                jump = false;
                y_velocity += BIRD_JUMP_VELOCITY;
            }
            if(y_velocity > MIN_VELOCITY) y_velocity += GRAVITY * dt;
            bird_sprite.move(0, -y_velocity);
        } 
    }

    void Bird::DrawBird(){
        if(y_velocity > 1.0f){
            bird_sprite.setTexture(data->assets.GetTexture("Bird Frame 3"));
            bird_sprite.setRotation(-BIRD_ROTATION_ANGLE);
        } else if (y_velocity > -1){
            bird_sprite.setTexture(data->assets.GetTexture("Bird Frame 2"));
            bird_sprite.setRotation(0);
        } else {
            bird_sprite.setTexture(data->assets.GetTexture("Bird Frame 1"));
            bird_sprite.setRotation(BIRD_ROTATION_ANGLE);
        }
        data->window.draw(bird_sprite);
    }

    bool Bird::IsWithinBounds(){
        return 
            (
             (bird_sprite.getPosition().y + int(bird_sprite.getGlobalBounds().height/2) < SCREEN_HEIGHT) 
             &&
             (bird_sprite.getPosition().y - int(bird_sprite.getGlobalBounds().height/2) >= 0)
            );
    }

    bool Bird::IntersectsWith(sf::FloatRect float_rect){
        return bird_sprite.getGlobalBounds().intersects(float_rect);
    }
}

