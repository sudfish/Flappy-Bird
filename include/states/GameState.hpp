#pragma once

#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include "objects/Pipe.hpp"
#include "machine/State.hpp"
#include "objects/Game.hpp"
#include "objects/Land.hpp"
#include "objects/Bird.hpp"

namespace flappy
{
    class GameState : public State {
        public:
            GameState(GameDataRef data);

            void Init();
            void HandleInput();
            void Update(float dt);
            void Draw(float dt);
            void Pause();
            void Mute();
            void Quit();

        private:
            sf::Clock clock;
            GameDataRef data;
            Bird *bird;
            Land *land;
            Pipe *pipe;
            sf::Sprite background, pause_button, unpause_button, mute_button, unmute_button;
            sf::Sound hit_sound, flap_sound, score_sound;
            sf::Text score_text;
            float speed;
            bool paused, muted = false;

            bool ExistsEndingCollision();
            bool ExistsScoringCollision();
            void SettleHighScores(int score);
    };
}
