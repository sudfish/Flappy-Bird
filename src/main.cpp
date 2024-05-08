#include "definitions.hpp"
#include "objects/Game.hpp"
#include <string>

using namespace std;
int main(int argc, char *argv[]){
    flappy::Game(SCREEN_WIDTH, SCREEN_HEIGHT, "Flappy Bird");
    return EXIT_SUCCESS;
}
