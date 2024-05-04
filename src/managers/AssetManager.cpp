#include "managers/AssetManager.hpp"
#include <SFML/Audio/SoundBuffer.hpp>

namespace flappy
{
    void AssetManager::LoadTexture(std::string name, std::string filename){
        sf::Texture texture;
        if(texture.loadFromFile(filename)) this->textures[name] = texture;
    }

    sf::Texture &AssetManager::GetTexture(std::string name){
        return this->textures.at(name);
    }

    void AssetManager::LoadFont(std::string name, std::string filename){
        sf::Font font;
        if(font.loadFromFile(filename)) this->fonts[name] = font;
    }

    sf::Font &AssetManager::GetFont(std::string name){
        return this->fonts.at(name);
    }

    void AssetManager::LoadSoundBuffer(std::string name, std::string filename){
        sf::SoundBuffer buffer;
        if(buffer.loadFromFile(filename)) this->sounds[name] = buffer;
    }

    sf::SoundBuffer &AssetManager::GetSoundBuffer(std::string name){
        return this->sounds.at(name);
    }

    void AssetManager::ClearSounds(){
        sounds.clear();
    }
}
