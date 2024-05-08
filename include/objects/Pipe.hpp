#pragma once

#include "objects/Game.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include <vector>


namespace flappy{
    class Pipe{
        public:
            std::vector<sf::Sprite> pipe_sprites;
            std::vector<sf::RectangleShape> score_boxes;
            
            Pipe(GameDataRef data);
            
            void SpawnPipes();
            void MovePipes( float dt, float speed );
            void DrawPipes();
            void RandomizeOffset();

        private:
            GameDataRef data;
            unsigned short int offset;

            void SpawnBottomPipe();
            void SpawnTopPipe();
            void SpawnScorePipe();
    };
}
