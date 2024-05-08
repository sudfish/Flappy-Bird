#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Mouse.hpp>

namespace flappy 
{
    class InputManager{
        public:
            InputManager(){}
            ~InputManager(){}

            bool IsSpriteClicked(sf::Sprite object, sf::Mouse::Button button, sf::RenderWindow &window);
            sf::Vector2i GetMousePosition(sf::RenderWindow &window);
    };
}
