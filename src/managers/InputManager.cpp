#include "managers/InputManager.hpp"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Mouse.hpp>

namespace flappy {
    bool InputManager::IsSpriteClicked(sf::Sprite object, sf::Mouse::Button button, sf::RenderWindow &window){
        if(sf::Mouse::isButtonPressed(button)){
            sf::IntRect temp_rect(object.getPosition().x, object.getPosition().y, object.getGlobalBounds().width, object.getGlobalBounds().height);
            if(temp_rect.contains(sf::Mouse::getPosition(window))) return true;
        } 
        return false;
    }

    sf::Vector2i InputManager::GetMousePosition(sf::RenderWindow &window){
        return sf::Mouse::getPosition(window);
    }
}
