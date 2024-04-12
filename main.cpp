#include "Game.h"

int main() {
    globalType::windowHeight = 750;
    globalType::windowWidth  = 1000;
    try
    {
        Game game;
        game.run();
    }
    catch(globalType::errorType &e)
    {
        std::cout<<e.errorMessage;
    }
    return 0;
}
