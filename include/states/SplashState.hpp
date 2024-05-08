#pragma once

#include "machine/State.hpp"
#include "objects/Game.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

namespace flappy
{
    class SplashState : public State{
        public:
            SplashState(GameDataRef data);

            void Init();

            void HandleInput();
            void Update(float dt);
            void Draw(float dt);

        private:
            GameDataRef data;
            bool skipped = false;
            sf::Clock clock;
            sf::Sprite background;
            sf::Texture background_texture;
    };
}
