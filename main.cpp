#include <iostream>
#include <string>
#include "game/Game.hpp"
#include "gui/sfml.hpp"

using namespace std;

int main()
{
    Game game;

    return startSfmlWindow(game);
}
