#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <string>

/**
 * @brief In charge of loading assets.
 *
 * Manager for all assets, including sound, font, images, etc. 
 */

namespace flappy
{
    class AssetManager{
        public:
            AssetManager(){}
            ~AssetManager(){}

            void LoadTexture(std::string name, std::string filename);
            sf::Texture &GetTexture(std::string name);

            void LoadFont(std::string name, std::string filename);
            sf::Font &GetFont(std::string name);

            void LoadSoundBuffer(std::string name, std::string filename);
            sf::SoundBuffer &GetSoundBuffer(std::string name);

            void ClearSounds();

        private:
            std::map<std::string, sf::Texture> textures;
            std::map<std::string, sf::Font> fonts;
            std::map<std::string, sf::SoundBuffer> sounds;
    };
}
