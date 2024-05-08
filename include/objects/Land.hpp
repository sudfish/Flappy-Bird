#pragma once

#include "objects/Game.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <vector>


namespace flappy {
    class Land {
        public:
            Land (GameDataRef data);
            void MoveLand( float dt, float speed );
            void DrawLand();
            std::vector<sf::Sprite> Sprites();

        private:
            GameDataRef data;
            std::vector<sf::Sprite> land_sprites;
    };
}
