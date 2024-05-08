#pragma once

#include "machine/StateMachine.hpp"
#include "managers/AssetManager.hpp"
#include "managers/InputManager.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>


namespace flappy
{
    struct GameData{
        StateMachine machine;
        sf::RenderWindow window;
        AssetManager assets;
        InputManager input;
        unsigned short int game_score;
        unsigned short int scores[3];
    };

    typedef std::shared_ptr<GameData> GameDataRef;

    class Game{
        public:
            Game(int width, int height, std::string title);

        private:
            const float dt = 1.0f/60.0f;
            sf::Clock clock;
            GameDataRef data = std::make_shared<GameData>();

            void Run();
    };
}
