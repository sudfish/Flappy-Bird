#pragma once

#include "objects/Game.hpp"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics.hpp>

namespace flappy
{
    class Bird{
        public:
            Bird(GameDataRef data);
            sf::Sprite bird_sprite;
            void DrawBird();
            bool IsWithinBounds();
            bool IntersectsWith(sf::FloatRect float_rect);
            void Jump();
            void MoveBird( float dt );

        private:
            GameDataRef data;
            bool jump;
            float y_velocity;
    };
}
